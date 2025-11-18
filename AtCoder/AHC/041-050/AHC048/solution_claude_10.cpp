#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("inline")

#define NANOFLANN_NO_THREADS 1
/***********************************************************************
 * Software License Agreement (BSD License)
 *
 * Copyright 2008-2009  Marius Muja (mariusm@cs.ubc.ca). All rights reserved.
 * Copyright 2008-2009  David G. Lowe (lowe@cs.ubc.ca). All rights reserved.
 * Copyright 2011-2025  Jose Luis Blanco (joseluisblancoc@gmail.com).
 *   All rights reserved.
 *
 * THE BSD LICENSE
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *************************************************************************/

/** \mainpage nanoflann C++ API documentation
 *  nanoflann is a C++ header-only library for building KD-Trees, mostly
 *  optimized for 2D or 3D point clouds.
 *
 *  nanoflann does not require compiling or installing, just an
 *  #include <nanoflann.hpp> in your code.
 *
 *  See:
 *   - [Online README](https://github.com/jlblancoc/nanoflann)
 *   - [C++ API documentation](https://jlblancoc.github.io/nanoflann/)
 */

#include <algorithm>
#include <array>
#include <atomic>
#include <cassert>
#include <cmath>  // for abs()
#include <cstdint>
#include <cstdlib>  // for abs()
#include <functional>  // std::reference_wrapper
#include <future>
#include <istream>
#include <limits>  // std::numeric_limits
#include <ostream>
#include <stdexcept>
#include <unordered_set>
#include <vector>

/** Library version: 0xMmP (M=Major,m=minor,P=patch) */
#define NANOFLANN_VERSION 0x171

// Avoid conflicting declaration of min/max macros in Windows headers
#if !defined(NOMINMAX) && \
    (defined(_WIN32) || defined(_WIN32_) || defined(WIN32) || defined(_WIN64))
#define NOMINMAX
#ifdef max
#undef max
#undef min
#endif
#endif
// Avoid conflicts with X11 headers
#ifdef None
#undef None
#endif

namespace nanoflann
{
/** @addtogroup nanoflann_grp nanoflann C++ library for KD-trees
 *  @{ */

/** the PI constant (required to avoid MSVC missing symbols) */
template <typename T>
T pi_const()
{
    return static_cast<T>(3.14159265358979323846);
}

/**
 * Traits if object is resizable and assignable (typically has a resize | assign
 * method)
 */
template <typename T, typename = int>
struct has_resize : std::false_type
{
};

template <typename T>
struct has_resize<T, decltype((void)std::declval<T>().resize(1), 0)>
    : std::true_type
{
};

template <typename T, typename = int>
struct has_assign : std::false_type
{
};

template <typename T>
struct has_assign<T, decltype((void)std::declval<T>().assign(1, 0), 0)>
    : std::true_type
{
};

/**
 * Free function to resize a resizable object
 */
template <typename Container>
inline typename std::enable_if<has_resize<Container>::value, void>::type resize(
    Container& c, const size_t nElements)
{
    c.resize(nElements);
}

/**
 * Free function that has no effects on non resizable containers (e.g.
 * std::array) It raises an exception if the expected size does not match
 */
template <typename Container>
inline typename std::enable_if<!has_resize<Container>::value, void>::type
    resize(Container& c, const size_t nElements)
{
    if (nElements != c.size())
        throw std::logic_error("Try to change the size of a std::array.");
}

/**
 * Free function to assign to a container
 */
template <typename Container, typename T>
inline typename std::enable_if<has_assign<Container>::value, void>::type assign(
    Container& c, const size_t nElements, const T& value)
{
    c.assign(nElements, value);
}

/**
 * Free function to assign to a std::array
 */
template <typename Container, typename T>
inline typename std::enable_if<!has_assign<Container>::value, void>::type
    assign(Container& c, const size_t nElements, const T& value)
{
    for (size_t i = 0; i < nElements; i++) c[i] = value;
}

/** operator "<" for std::sort() */
struct IndexDist_Sorter
{
    /** PairType will be typically: ResultItem<IndexType,DistanceType> */
    template <typename PairType>
    bool operator()(const PairType& p1, const PairType& p2) const
    {
        return p1.second < p2.second;
    }
};

/**
 * Each result element in RadiusResultSet. Note that distances and indices
 * are named `first` and `second` to keep backward-compatibility with the
 * `std::pair<>` type used in the past. In contrast, this structure is ensured
 * to be `std::is_standard_layout` so it can be used in wrappers to other
 * languages.
 * See: https://github.com/jlblancoc/nanoflann/issues/166
 */
template <typename IndexType = size_t, typename DistanceType = double>
struct ResultItem
{
    ResultItem() = default;
    ResultItem(const IndexType index, const DistanceType distance)
        : first(index), second(distance)
    {
    }

    IndexType    first;  //!< Index of the sample in the dataset
    DistanceType second;  //!< Distance from sample to query point
};

/** @addtogroup result_sets_grp Result set classes
 *  @{ */

/** Result set for KNN searches (N-closest neighbors) */
template <
    typename _DistanceType, typename _IndexType = size_t,
    typename _CountType = size_t>
class KNNResultSet
{
   public:
    using DistanceType = _DistanceType;
    using IndexType    = _IndexType;
    using CountType    = _CountType;

   private:
    IndexType*    indices;
    DistanceType* dists;
    CountType     capacity;
    CountType     count;

   public:
    explicit KNNResultSet(CountType capacity_)
        : indices(nullptr), dists(nullptr), capacity(capacity_), count(0)
    {
    }

    void init(IndexType* indices_, DistanceType* dists_)
    {
        indices = indices_;
        dists   = dists_;
        count   = 0;
    }

    CountType size() const { return count; }
    bool      empty() const { return count == 0; }
    bool      full() const { return count == capacity; }

    /**
     * Called during search to add an element matching the criteria.
     * @return true if the search should be continued, false if the results are
     * sufficient
     */
    bool addPoint(DistanceType dist, IndexType index)
    {
        CountType i;
        for (i = count; i > 0; --i)
        {
            /** If defined and two points have the same distance, the one with
             *  the lowest-index will be returned first. */
#ifdef NANOFLANN_FIRST_MATCH
            if ((dists[i - 1] > dist) ||
                ((dist == dists[i - 1]) && (indices[i - 1] > index)))
            {
#else
            if (dists[i - 1] > dist)
            {
#endif
                if (i < capacity)
                {
                    dists[i]   = dists[i - 1];
                    indices[i] = indices[i - 1];
                }
            }
            else
                break;
        }
        if (i < capacity)
        {
            dists[i]   = dist;
            indices[i] = index;
        }
        if (count < capacity) count++;

        // tell caller that the search shall continue
        return true;
    }

    //! Returns the worst distance among found solutions if the search result is
    //! full, or the maximum possible distance, if not full yet.
    DistanceType worstDist() const
    {
        return (count < capacity || !count)
                   ? std::numeric_limits<DistanceType>::max()
                   : dists[count - 1];
    }

    void sort()
    {
        // already sorted
    }
};

/** Result set for RKNN searches (N-closest neighbors with a maximum radius) */
template <
    typename _DistanceType, typename _IndexType = size_t,
    typename _CountType = size_t>
class RKNNResultSet
{
   public:
    using DistanceType = _DistanceType;
    using IndexType    = _IndexType;
    using CountType    = _CountType;

   private:
    IndexType*    indices;
    DistanceType* dists;
    CountType     capacity;
    CountType     count;
    DistanceType  maximumSearchDistanceSquared;

   public:
    explicit RKNNResultSet(
        CountType capacity_, DistanceType maximumSearchDistanceSquared_)
        : indices(nullptr),
          dists(nullptr),
          capacity(capacity_),
          count(0),
          maximumSearchDistanceSquared(maximumSearchDistanceSquared_)
    {
    }

    void init(IndexType* indices_, DistanceType* dists_)
    {
        indices = indices_;
        dists   = dists_;
        count   = 0;
        if (capacity) dists[capacity - 1] = maximumSearchDistanceSquared;
    }

    CountType size() const { return count; }
    bool      empty() const { return count == 0; }
    bool      full() const { return count == capacity; }

    /**
     * Called during search to add an element matching the criteria.
     * @return true if the search should be continued, false if the results are
     * sufficient
     */
    bool addPoint(DistanceType dist, IndexType index)
    {
        CountType i;
        for (i = count; i > 0; --i)
        {
            /** If defined and two points have the same distance, the one with
             *  the lowest-index will be returned first. */
#ifdef NANOFLANN_FIRST_MATCH
            if ((dists[i - 1] > dist) ||
                ((dist == dists[i - 1]) && (indices[i - 1] > index)))
            {
#else
            if (dists[i - 1] > dist)
            {
#endif
                if (i < capacity)
                {
                    dists[i]   = dists[i - 1];
                    indices[i] = indices[i - 1];
                }
            }
            else
                break;
        }
        if (i < capacity)
        {
            dists[i]   = dist;
            indices[i] = index;
        }
        if (count < capacity) count++;

        // tell caller that the search shall continue
        return true;
    }

    //! Returns the worst distance among found solutions if the search result is
    //! full, or the maximum possible distance, if not full yet.
    DistanceType worstDist() const
    {
        return (count < capacity || !count) ? maximumSearchDistanceSquared
                                            : dists[count - 1];
    }

    void sort()
    {
        // already sorted
    }
};

/**
 * A result-set class used when performing a radius based search.
 */
template <typename _DistanceType, typename _IndexType = size_t>
class RadiusResultSet
{
   public:
    using DistanceType = _DistanceType;
    using IndexType    = _IndexType;

   public:
    const DistanceType radius;

    std::vector<ResultItem<IndexType, DistanceType>>& m_indices_dists;

    explicit RadiusResultSet(
        DistanceType                                      radius_,
        std::vector<ResultItem<IndexType, DistanceType>>& indices_dists)
        : radius(radius_), m_indices_dists(indices_dists)
    {
        init();
    }

    void init() { clear(); }
    void clear() { m_indices_dists.clear(); }

    size_t size() const { return m_indices_dists.size(); }
    size_t empty() const { return m_indices_dists.empty(); }

    bool full() const { return true; }

    /**
     * Called during search to add an element matching the criteria.
     * @return true if the search should be continued, false if the results are
     * sufficient
     */
    bool addPoint(DistanceType dist, IndexType index)
    {
        if (dist < radius) m_indices_dists.emplace_back(index, dist);
        return true;
    }

    DistanceType worstDist() const { return radius; }

    /**
     * Find the worst result (farthest neighbor) without copying or sorting
     * Pre-conditions: size() > 0
     */
    ResultItem<IndexType, DistanceType> worst_item() const
    {
        if (m_indices_dists.empty())
            throw std::runtime_error(
                "Cannot invoke RadiusResultSet::worst_item() on "
                "an empty list of results.");
        auto it = std::max_element(
            m_indices_dists.begin(), m_indices_dists.end(), IndexDist_Sorter());
        return *it;
    }

    void sort()
    {
        std::sort(
            m_indices_dists.begin(), m_indices_dists.end(), IndexDist_Sorter());
    }
};

/** @} */

/** @addtogroup loadsave_grp Load/save auxiliary functions
 * @{ */
template <typename T>
void save_value(std::ostream& stream, const T& value)
{
    stream.write(reinterpret_cast<const char*>(&value), sizeof(T));
}

template <typename T>
void save_value(std::ostream& stream, const std::vector<T>& value)
{
    size_t size = value.size();
    stream.write(reinterpret_cast<const char*>(&size), sizeof(size_t));
    stream.write(reinterpret_cast<const char*>(value.data()), sizeof(T) * size);
}

template <typename T>
void load_value(std::istream& stream, T& value)
{
    stream.read(reinterpret_cast<char*>(&value), sizeof(T));
}

template <typename T>
void load_value(std::istream& stream, std::vector<T>& value)
{
    size_t size;
    stream.read(reinterpret_cast<char*>(&size), sizeof(size_t));
    value.resize(size);
    stream.read(reinterpret_cast<char*>(value.data()), sizeof(T) * size);
}
/** @} */

/** @addtogroup metric_grp Metric (distance) classes
 * @{ */

struct Metric
{
};

/** Manhattan distance functor (generic version, optimized for
 * high-dimensionality data sets). Corresponding distance traits:
 * nanoflann::metric_L1
 *
 * \tparam T Type of the elements (e.g. double, float, uint8_t)
 * \tparam DataSource Source of the data, i.e. where the vectors are stored
 * \tparam _DistanceType Type of distance variables (must be signed)
 * \tparam IndexType Type of the arguments with which the data can be
 * accessed (e.g. float, double, int64_t, T*)
 */
template <
    class T, class DataSource, typename _DistanceType = T,
    typename IndexType = uint32_t>
struct L1_Adaptor
{
    using ElementType  = T;
    using DistanceType = _DistanceType;

    const DataSource& data_source;

    L1_Adaptor(const DataSource& _data_source) : data_source(_data_source) {}

    DistanceType evalMetric(
        const T* a, const IndexType b_idx, size_t size,
        DistanceType worst_dist = -1) const
    {
        DistanceType result    = DistanceType();
        const T*     last      = a + size;
        const T*     lastgroup = last - 3;
        size_t       d         = 0;

        /* Process 4 items with each loop for efficiency. */
        while (a < lastgroup)
        {
            const DistanceType diff0 =
                std::abs(a[0] - data_source.kdtree_get_pt(b_idx, d++));
            const DistanceType diff1 =
                std::abs(a[1] - data_source.kdtree_get_pt(b_idx, d++));
            const DistanceType diff2 =
                std::abs(a[2] - data_source.kdtree_get_pt(b_idx, d++));
            const DistanceType diff3 =
                std::abs(a[3] - data_source.kdtree_get_pt(b_idx, d++));
            result += diff0 + diff1 + diff2 + diff3;
            a += 4;
            if ((worst_dist > 0) && (result > worst_dist)) { return result; }
        }
        /* Process last 0-3 components.  Not needed for standard vector lengths.
         */
        while (a < last)
        {
            result += std::abs(*a++ - data_source.kdtree_get_pt(b_idx, d++));
        }
        return result;
    }

    template <typename U, typename V>
    DistanceType accum_dist(const U a, const V b, const size_t) const
    {
        return std::abs(a - b);
    }
};

/** **Squared** Euclidean distance functor (generic version, optimized for
 * high-dimensionality data sets). Corresponding distance traits:
 * nanoflann::metric_L2
 *
 * \tparam T Type of the elements (e.g. double, float, uint8_t)
 * \tparam DataSource Source of the data, i.e. where the vectors are stored
 * \tparam _DistanceType Type of distance variables (must be signed)
 * \tparam IndexType Type of the arguments with which the data can be
 * accessed (e.g. float, double, int64_t, T*)
 */
template <
    class T, class DataSource, typename _DistanceType = T,
    typename IndexType = uint32_t>
struct L2_Adaptor
{
    using ElementType  = T;
    using DistanceType = _DistanceType;

    const DataSource& data_source;

    L2_Adaptor(const DataSource& _data_source) : data_source(_data_source) {}

    DistanceType evalMetric(
        const T* a, const IndexType b_idx, size_t size,
        DistanceType worst_dist = -1) const
    {
        DistanceType result    = DistanceType();
        const T*     last      = a + size;
        const T*     lastgroup = last - 3;
        size_t       d         = 0;

        /* Process 4 items with each loop for efficiency. */
        while (a < lastgroup)
        {
            const DistanceType diff0 =
                a[0] - data_source.kdtree_get_pt(b_idx, d++);
            const DistanceType diff1 =
                a[1] - data_source.kdtree_get_pt(b_idx, d++);
            const DistanceType diff2 =
                a[2] - data_source.kdtree_get_pt(b_idx, d++);
            const DistanceType diff3 =
                a[3] - data_source.kdtree_get_pt(b_idx, d++);
            result +=
                diff0 * diff0 + diff1 * diff1 + diff2 * diff2 + diff3 * diff3;
            a += 4;
            if ((worst_dist > 0) && (result > worst_dist)) { return result; }
        }
        /* Process last 0-3 components.  Not needed for standard vector lengths.
         */
        while (a < last)
        {
            const DistanceType diff0 =
                *a++ - data_source.kdtree_get_pt(b_idx, d++);
            result += diff0 * diff0;
        }
        return result;
    }

    template <typename U, typename V>
    DistanceType accum_dist(const U a, const V b, const size_t) const
    {
        return (a - b) * (a - b);
    }
};

/** **Squared** Euclidean (L2) distance functor (suitable for low-dimensionality
 * datasets, like 2D or 3D point clouds) Corresponding distance traits:
 * nanoflann::metric_L2_Simple
 *
 * \tparam T Type of the elements (e.g. double, float, uint8_t)
 * \tparam DataSource Source of the data, i.e. where the vectors are stored
 * \tparam _DistanceType Type of distance variables (must be signed)
 * \tparam IndexType Type of the arguments with which the data can be
 * accessed (e.g. float, double, int64_t, T*)
 */
template <
    class T, class DataSource, typename _DistanceType = T,
    typename IndexType = uint32_t>
struct L2_Simple_Adaptor
{
    using ElementType  = T;
    using DistanceType = _DistanceType;

    const DataSource& data_source;

    L2_Simple_Adaptor(const DataSource& _data_source)
        : data_source(_data_source)
    {
    }

    DistanceType evalMetric(
        const T* a, const IndexType b_idx, size_t size) const
    {
        DistanceType result = DistanceType();
        for (size_t i = 0; i < size; ++i)
        {
            const DistanceType diff =
                a[i] - data_source.kdtree_get_pt(b_idx, i);
            result += diff * diff;
        }
        return result;
    }

    template <typename U, typename V>
    DistanceType accum_dist(const U a, const V b, const size_t) const
    {
        return (a - b) * (a - b);
    }
};

/** SO2 distance functor
 *  Corresponding distance traits: nanoflann::metric_SO2
 *
 * \tparam T Type of the elements (e.g. double, float, uint8_t)
 * \tparam DataSource Source of the data, i.e. where the vectors are stored
 * \tparam _DistanceType Type of distance variables (must be signed) (e.g.
 * float, double) orientation is constrained to be in [-pi, pi]
 * \tparam IndexType Type of the arguments with which the data can be
 * accessed (e.g. float, double, int64_t, T*)
 */
template <
    class T, class DataSource, typename _DistanceType = T,
    typename IndexType = uint32_t>
struct SO2_Adaptor
{
    using ElementType  = T;
    using DistanceType = _DistanceType;

    const DataSource& data_source;

    SO2_Adaptor(const DataSource& _data_source) : data_source(_data_source) {}

    DistanceType evalMetric(
        const T* a, const IndexType b_idx, size_t size) const
    {
        return accum_dist(
            a[size - 1], data_source.kdtree_get_pt(b_idx, size - 1), size - 1);
    }

    /** Note: this assumes that input angles are already in the range [-pi,pi]
     */
    template <typename U, typename V>
    DistanceType accum_dist(const U a, const V b, const size_t) const
    {
        DistanceType result = DistanceType();
        DistanceType PI     = pi_const<DistanceType>();
        result              = b - a;
        if (result > PI)
            result -= 2 * PI;
        else if (result < -PI)
            result += 2 * PI;
        return result;
    }
};

/** SO3 distance functor (Uses L2_Simple)
 *  Corresponding distance traits: nanoflann::metric_SO3
 *
 * \tparam T Type of the elements (e.g. double, float, uint8_t)
 * \tparam DataSource Source of the data, i.e. where the vectors are stored
 * \tparam _DistanceType Type of distance variables (must be signed) (e.g.
 * float, double)
 * \tparam IndexType Type of the arguments with which the data can be
 * accessed (e.g. float, double, int64_t, T*)
 */
template <
    class T, class DataSource, typename _DistanceType = T,
    typename IndexType = uint32_t>
struct SO3_Adaptor
{
    using ElementType  = T;
    using DistanceType = _DistanceType;

    L2_Simple_Adaptor<T, DataSource, DistanceType, IndexType>
        distance_L2_Simple;

    SO3_Adaptor(const DataSource& _data_source)
        : distance_L2_Simple(_data_source)
    {
    }

    DistanceType evalMetric(
        const T* a, const IndexType b_idx, size_t size) const
    {
        return distance_L2_Simple.evalMetric(a, b_idx, size);
    }

    template <typename U, typename V>
    DistanceType accum_dist(const U a, const V b, const size_t idx) const
    {
        return distance_L2_Simple.accum_dist(a, b, idx);
    }
};

/** Metaprogramming helper traits class for the L1 (Manhattan) metric */
struct metric_L1 : public Metric
{
    template <class T, class DataSource, typename IndexType = uint32_t>
    struct traits
    {
        using distance_t = L1_Adaptor<T, DataSource, T, IndexType>;
    };
};
/** Metaprogramming helper traits class for the L2 (Euclidean) **squared**
 * distance metric */
struct metric_L2 : public Metric
{
    template <class T, class DataSource, typename IndexType = uint32_t>
    struct traits
    {
        using distance_t = L2_Adaptor<T, DataSource, T, IndexType>;
    };
};
/** Metaprogramming helper traits class for the L2_simple (Euclidean)
 * **squared** distance metric */
struct metric_L2_Simple : public Metric
{
    template <class T, class DataSource, typename IndexType = uint32_t>
    struct traits
    {
        using distance_t = L2_Simple_Adaptor<T, DataSource, T, IndexType>;
    };
};
/** Metaprogramming helper traits class for the SO3_InnerProdQuat metric */
struct metric_SO2 : public Metric
{
    template <class T, class DataSource, typename IndexType = uint32_t>
    struct traits
    {
        using distance_t = SO2_Adaptor<T, DataSource, T, IndexType>;
    };
};
/** Metaprogramming helper traits class for the SO3_InnerProdQuat metric */
struct metric_SO3 : public Metric
{
    template <class T, class DataSource, typename IndexType = uint32_t>
    struct traits
    {
        using distance_t = SO3_Adaptor<T, DataSource, T, IndexType>;
    };
};

/** @} */

/** @addtogroup param_grp Parameter structs
 * @{ */

enum class KDTreeSingleIndexAdaptorFlags
{
    None                  = 0,
    SkipInitialBuildIndex = 1
};

inline std::underlying_type<KDTreeSingleIndexAdaptorFlags>::type operator&(
    KDTreeSingleIndexAdaptorFlags lhs, KDTreeSingleIndexAdaptorFlags rhs)
{
    using underlying =
        typename std::underlying_type<KDTreeSingleIndexAdaptorFlags>::type;
    return static_cast<underlying>(lhs) & static_cast<underlying>(rhs);
}

/**  Parameters (see README.md) */
struct KDTreeSingleIndexAdaptorParams
{
    KDTreeSingleIndexAdaptorParams(
        size_t                        _leaf_max_size = 10,
        KDTreeSingleIndexAdaptorFlags _flags =
            KDTreeSingleIndexAdaptorFlags::None,
        unsigned int _n_thread_build = 1)
        : leaf_max_size(_leaf_max_size),
          flags(_flags),
          n_thread_build(_n_thread_build)
    {
    }

    size_t                        leaf_max_size;
    KDTreeSingleIndexAdaptorFlags flags;
    unsigned int                  n_thread_build;
};

/** Search options for KDTreeSingleIndexAdaptor::findNeighbors() */
struct SearchParameters
{
    SearchParameters(float eps_ = 0, bool sorted_ = true)
        : eps(eps_), sorted(sorted_)
    {
    }

    float eps;  //!< search for eps-approximate neighbours (default: 0)
    bool  sorted;  //!< only for radius search, require neighbours sorted by
                  //!< distance (default: true)
};
/** @} */

/** @addtogroup memalloc_grp Memory allocation
 * @{ */

/**
 * Pooled storage allocator
 *
 * The following routines allow for the efficient allocation of storage in
 * small chunks from a specified pool.  Rather than allowing each structure
 * to be freed individually, an entire pool of storage is freed at once.
 * This method has two advantages over just using malloc() and free().  First,
 * it is far more efficient for allocating small objects, as there is
 * no overhead for remembering all the information needed to free each
 * object or consolidating fragmented memory.  Second, the decision about
 * how long to keep an object is made at the time of allocation, and there
 * is no need to track down all the objects to free them.
 *
 */
class PooledAllocator
{
    static constexpr size_t WORDSIZE  = 16;  // WORDSIZE must >= 8
    static constexpr size_t BLOCKSIZE = 8192;

    /* We maintain memory alignment to word boundaries by requiring that all
        allocations be in multiples of the machine wordsize.  */
    /* Size of machine word in bytes.  Must be power of 2. */
    /* Minimum number of bytes requested at a time from	the system.  Must be
     * multiple of WORDSIZE. */

    using Size = size_t;

    Size  remaining_ = 0;  //!< Number of bytes left in current block of storage
    void* base_ = nullptr;  //!< Pointer to base of current block of storage
    void* loc_  = nullptr;  //!< Current location in block to next allocate

    void internal_init()
    {
        remaining_   = 0;
        base_        = nullptr;
        usedMemory   = 0;
        wastedMemory = 0;
    }

   public:
    Size usedMemory   = 0;
    Size wastedMemory = 0;

    /**
        Default constructor. Initializes a new pool.
     */
    PooledAllocator() { internal_init(); }

    /**
     * Destructor. Frees all the memory allocated in this pool.
     */
    ~PooledAllocator() { free_all(); }

    /** Frees all allocated memory chunks */
    void free_all()
    {
        while (base_ != nullptr)
        {
            // Get pointer to prev block
            void* prev = *(static_cast<void**>(base_));
            ::free(base_);
            base_ = prev;
        }
        internal_init();
    }

    /**
     * Returns a pointer to a piece of new memory of the given size in bytes
     * allocated from the pool.
     */
    void* malloc(const size_t req_size)
    {
        /* Round size up to a multiple of wordsize.  The following expression
            only works for WORDSIZE that is a power of 2, by masking last bits
           of incremented size to zero.
         */
        const Size size = (req_size + (WORDSIZE - 1)) & ~(WORDSIZE - 1);

        /* Check whether a new block must be allocated.  Note that the first
           word of a block is reserved for a pointer to the previous block.
         */
        if (size > remaining_)
        {
            wastedMemory += remaining_;

            /* Allocate new storage. */
            const Size blocksize =
                size > BLOCKSIZE ? size + WORDSIZE : BLOCKSIZE + WORDSIZE;

            // use the standard C malloc to allocate memory
            void* m = ::malloc(blocksize);
            if (!m)
            {
                fprintf(stderr, "Failed to allocate memory.\n");
                throw std::bad_alloc();
            }

            /* Fill first word of new block with pointer to previous block. */
            static_cast<void**>(m)[0] = base_;
            base_                     = m;

            remaining_ = blocksize - WORDSIZE;
            loc_       = static_cast<char*>(m) + WORDSIZE;
        }
        void* rloc = loc_;
        loc_       = static_cast<char*>(loc_) + size;
        remaining_ -= size;

        usedMemory += size;

        return rloc;
    }

    /**
     * Allocates (using this pool) a generic type T.
     *
     * Params:
     *     count = number of instances to allocate.
     * Returns: pointer (of type T*) to memory buffer
     */
    template <typename T>
    T* allocate(const size_t count = 1)
    {
        T* mem = static_cast<T*>(this->malloc(sizeof(T) * count));
        return mem;
    }
};
/** @} */

/** @addtogroup nanoflann_metaprog_grp Auxiliary metaprogramming stuff
 * @{ */

/** Used to declare fixed-size arrays when DIM>0, dynamically-allocated vectors
 * when DIM=-1. Fixed size version for a generic DIM:
 */
template <int32_t DIM, typename T>
struct array_or_vector
{
    using type = std::array<T, DIM>;
};
/** Dynamic size version */
template <typename T>
struct array_or_vector<-1, T>
{
    using type = std::vector<T>;
};

/** @} */

/** kd-tree base-class
 *
 * Contains the member functions common to the classes KDTreeSingleIndexAdaptor
 * and KDTreeSingleIndexDynamicAdaptor_.
 *
 * \tparam Derived The name of the class which inherits this class.
 * \tparam DatasetAdaptor The user-provided adaptor, which must be ensured to
 *         have a lifetime equal or longer than the instance of this class.
 * \tparam Distance The distance metric to use, these are all classes derived
 * from nanoflann::Metric
 * \tparam DIM Dimensionality of data points (e.g. 3 for 3D points)
 * \tparam IndexType Type of the arguments with which the data can be
 * accessed (e.g. float, double, int64_t, T*)
 */
template <
    class Derived, typename Distance, class DatasetAdaptor, int32_t DIM = -1,
    typename index_t = uint32_t>
class KDTreeBaseClass
{
   public:
    /** Frees the previously-built index. Automatically called within
     * buildIndex(). */
    void freeIndex(Derived& obj)
    {
        obj.pool_.free_all();
        obj.root_node_           = nullptr;
        obj.size_at_index_build_ = 0;
    }

    using ElementType  = typename Distance::ElementType;
    using DistanceType = typename Distance::DistanceType;
    using IndexType    = index_t;

    /**
     *  Array of indices to vectors in the dataset_.
     */
    std::vector<IndexType> vAcc_;

    using Offset    = typename decltype(vAcc_)::size_type;
    using Size      = typename decltype(vAcc_)::size_type;
    using Dimension = int32_t;

    /*---------------------------
     * Internal Data Structures
     * --------------------------*/
    struct Node
    {
        /** Union used because a node can be either a LEAF node or a non-leaf
         * node, so both data fields are never used simultaneously */
        union
        {
            struct leaf
            {
                Offset left, right;  //!< Indices of points in leaf node
            } lr;
            struct nonleaf
            {
                Dimension divfeat;  //!< Dimension used for subdivision.
                /// The values used for subdivision.
                DistanceType divlow, divhigh;
            } sub;
        } node_type;

        /** Child nodes (both=nullptr mean its a leaf node) */
        Node *child1 = nullptr, *child2 = nullptr;
    };

    using NodePtr      = Node*;
    using NodeConstPtr = const Node*;

    struct Interval
    {
        ElementType low, high;
    };

    NodePtr root_node_ = nullptr;

    Size leaf_max_size_ = 0;

    /// Number of thread for concurrent tree build
    Size n_thread_build_ = 1;
    /// Number of current points in the dataset
    Size size_ = 0;
    /// Number of points in the dataset when the index was built
    Size      size_at_index_build_ = 0;
    Dimension dim_                 = 0;  //!< Dimensionality of each data point

    /** Define "BoundingBox" as a fixed-size or variable-size container
     * depending on "DIM" */
    using BoundingBox = typename array_or_vector<DIM, Interval>::type;

    /** Define "distance_vector_t" as a fixed-size or variable-size container
     * depending on "DIM" */
    using distance_vector_t = typename array_or_vector<DIM, DistanceType>::type;

    /** The KD-tree used to find neighbours */
    BoundingBox root_bbox_;

    /**
     * Pooled memory allocator.
     *
     * Using a pooled memory allocator is more efficient
     * than allocating memory directly when there is a large
     * number small of memory allocations.
     */
    PooledAllocator pool_;

    /** Returns number of points in dataset  */
    Size size(const Derived& obj) const { return obj.size_; }

    /** Returns the length of each point in the dataset */
    Size veclen(const Derived& obj) { return DIM > 0 ? DIM : obj.dim; }

    /// Helper accessor to the dataset points:
    ElementType dataset_get(
        const Derived& obj, IndexType element, Dimension component) const
    {
        return obj.dataset_.kdtree_get_pt(element, component);
    }

    /**
     * Computes the inde memory usage
     * Returns: memory used by the index
     */
    Size usedMemory(Derived& obj)
    {
        return obj.pool_.usedMemory + obj.pool_.wastedMemory +
               obj.dataset_.kdtree_get_point_count() *
                   sizeof(IndexType);  // pool memory and vind array memory
    }

    void computeMinMax(
        const Derived& obj, Offset ind, Size count, Dimension element,
        ElementType& min_elem, ElementType& max_elem)
    {
        min_elem = dataset_get(obj, vAcc_[ind], element);
        max_elem = min_elem;
        for (Offset i = 1; i < count; ++i)
        {
            ElementType val = dataset_get(obj, vAcc_[ind + i], element);
            if (val < min_elem) min_elem = val;
            if (val > max_elem) max_elem = val;
        }
    }

    /**
     * Create a tree node that subdivides the list of vecs from vind[first]
     * to vind[last].  The routine is called recursively on each sublist.
     *
     * @param left index of the first vector
     * @param right index of the last vector
     */
    NodePtr divideTree(
        Derived& obj, const Offset left, const Offset right, BoundingBox& bbox)
    {
        assert(left < obj.dataset_.kdtree_get_point_count());

        NodePtr node = obj.pool_.template allocate<Node>();  // allocate memory
        const auto dims = (DIM > 0 ? DIM : obj.dim_);

        /* If too few exemplars remain, then make this a leaf node. */
        if ((right - left) <= static_cast<Offset>(obj.leaf_max_size_))
        {
            node->child1 = node->child2 = nullptr; /* Mark as leaf node. */
            node->node_type.lr.left     = left;
            node->node_type.lr.right    = right;

            // compute bounding-box of leaf points
            for (Dimension i = 0; i < dims; ++i)
            {
                bbox[i].low  = dataset_get(obj, obj.vAcc_[left], i);
                bbox[i].high = dataset_get(obj, obj.vAcc_[left], i);
            }
            for (Offset k = left + 1; k < right; ++k)
            {
                for (Dimension i = 0; i < dims; ++i)
                {
                    const auto val = dataset_get(obj, obj.vAcc_[k], i);
                    if (bbox[i].low > val) bbox[i].low = val;
                    if (bbox[i].high < val) bbox[i].high = val;
                }
            }
        }
        else
        {
            Offset       idx;
            Dimension    cutfeat;
            DistanceType cutval;
            middleSplit_(obj, left, right - left, idx, cutfeat, cutval, bbox);

            node->node_type.sub.divfeat = cutfeat;

            BoundingBox left_bbox(bbox);
            left_bbox[cutfeat].high = cutval;
            node->child1 = this->divideTree(obj, left, left + idx, left_bbox);

            BoundingBox right_bbox(bbox);
            right_bbox[cutfeat].low = cutval;
            node->child2 = this->divideTree(obj, left + idx, right, right_bbox);

            node->node_type.sub.divlow  = left_bbox[cutfeat].high;
            node->node_type.sub.divhigh = right_bbox[cutfeat].low;

            for (Dimension i = 0; i < dims; ++i)
            {
                bbox[i].low  = std::min(left_bbox[i].low, right_bbox[i].low);
                bbox[i].high = std::max(left_bbox[i].high, right_bbox[i].high);
            }
        }

        return node;
    }

    /**
     * Create a tree node that subdivides the list of vecs from vind[first] to
     * vind[last] concurrently.  The routine is called recursively on each
     * sublist.
     *
     * @param left index of the first vector
     * @param right index of the last vector
     * @param thread_count count of std::async threads
     * @param mutex mutex for mempool allocation
     */
    NodePtr divideTreeConcurrent(
        Derived& obj, const Offset left, const Offset right, BoundingBox& bbox,
        std::atomic<unsigned int>& thread_count, std::mutex& mutex)
    {
        std::unique_lock<std::mutex> lock(mutex);
        NodePtr node = obj.pool_.template allocate<Node>();  // allocate memory
        lock.unlock();

        const auto dims = (DIM > 0 ? DIM : obj.dim_);

        /* If too few exemplars remain, then make this a leaf node. */
        if ((right - left) <= static_cast<Offset>(obj.leaf_max_size_))
        {
            node->child1 = node->child2 = nullptr; /* Mark as leaf node. */
            node->node_type.lr.left     = left;
            node->node_type.lr.right    = right;

            // compute bounding-box of leaf points
            for (Dimension i = 0; i < dims; ++i)
            {
                bbox[i].low  = dataset_get(obj, obj.vAcc_[left], i);
                bbox[i].high = dataset_get(obj, obj.vAcc_[left], i);
            }
            for (Offset k = left + 1; k < right; ++k)
            {
                for (Dimension i = 0; i < dims; ++i)
                {
                    const auto val = dataset_get(obj, obj.vAcc_[k], i);
                    if (bbox[i].low > val) bbox[i].low = val;
                    if (bbox[i].high < val) bbox[i].high = val;
                }
            }
        }
        else
        {
            Offset       idx;
            Dimension    cutfeat;
            DistanceType cutval;
            middleSplit_(obj, left, right - left, idx, cutfeat, cutval, bbox);

            node->node_type.sub.divfeat = cutfeat;

            std::future<NodePtr> right_future;

            BoundingBox right_bbox(bbox);
            right_bbox[cutfeat].low = cutval;
            if (++thread_count < n_thread_build_)
            {
                // Concurrent right sub-tree
                right_future = std::async(
                    std::launch::async, &KDTreeBaseClass::divideTreeConcurrent,
                    this, std::ref(obj), left + idx, right,
                    std::ref(right_bbox), std::ref(thread_count),
                    std::ref(mutex));
            }
            else { --thread_count; }

            BoundingBox left_bbox(bbox);
            left_bbox[cutfeat].high = cutval;
            node->child1            = this->divideTreeConcurrent(
                           obj, left, left + idx, left_bbox, thread_count, mutex);

            if (right_future.valid())
            {
                // Block and wait for concurrent right sub-tree
                node->child2 = right_future.get();
                --thread_count;
            }
            else
            {
                node->child2 = this->divideTreeConcurrent(
                    obj, left + idx, right, right_bbox, thread_count, mutex);
            }

            node->node_type.sub.divlow  = left_bbox[cutfeat].high;
            node->node_type.sub.divhigh = right_bbox[cutfeat].low;

            for (Dimension i = 0; i < dims; ++i)
            {
                bbox[i].low  = std::min(left_bbox[i].low, right_bbox[i].low);
                bbox[i].high = std::max(left_bbox[i].high, right_bbox[i].high);
            }
        }

        return node;
    }

    void middleSplit_(
        const Derived& obj, const Offset ind, const Size count, Offset& index,
        Dimension& cutfeat, DistanceType& cutval, const BoundingBox& bbox)
    {
        const auto  dims     = (DIM > 0 ? DIM : obj.dim_);
        const auto  EPS      = static_cast<DistanceType>(0.00001);
        ElementType max_span = bbox[0].high - bbox[0].low;
        for (Dimension i = 1; i < dims; ++i)
        {
            ElementType span = bbox[i].high - bbox[i].low;
            if (span > max_span) { max_span = span; }
        }
        ElementType max_spread = -1;
        cutfeat                = 0;
        ElementType min_elem = 0, max_elem = 0;
        for (Dimension i = 0; i < dims; ++i)
        {
            ElementType span = bbox[i].high - bbox[i].low;
            if (span >= (1 - EPS) * max_span)
            {
                ElementType min_elem_, max_elem_;
                computeMinMax(obj, ind, count, i, min_elem_, max_elem_);
                ElementType spread = max_elem_ - min_elem_;
                if (spread > max_spread)
                {
                    cutfeat    = i;
                    max_spread = spread;
                    min_elem   = min_elem_;
                    max_elem   = max_elem_;
                }
            }
        }
        // split in the middle
        DistanceType split_val = (bbox[cutfeat].low + bbox[cutfeat].high) / 2;

        if (split_val < min_elem)
            cutval = min_elem;
        else if (split_val > max_elem)
            cutval = max_elem;
        else
            cutval = split_val;

        Offset lim1, lim2;
        planeSplit(obj, ind, count, cutfeat, cutval, lim1, lim2);

        if (lim1 > count / 2)
            index = lim1;
        else if (lim2 < count / 2)
            index = lim2;
        else
            index = count / 2;
    }

    /**
     *  Subdivide the list of points by a plane perpendicular on the axis
     * corresponding to the 'cutfeat' dimension at 'cutval' position.
     *
     *  On return:
     *  dataset[ind[0..lim1-1]][cutfeat]<cutval
     *  dataset[ind[lim1..lim2-1]][cutfeat]==cutval
     *  dataset[ind[lim2..count]][cutfeat]>cutval
     */
    void planeSplit(
        const Derived& obj, const Offset ind, const Size count,
        const Dimension cutfeat, const DistanceType& cutval, Offset& lim1,
        Offset& lim2)
    {
        /* Move vector indices for left subtree to front of list. */
        Offset left  = 0;
        Offset right = count - 1;
        for (;;)
        {
            while (left <= right &&
                   dataset_get(obj, vAcc_[ind + left], cutfeat) < cutval)
                ++left;
            while (right && left <= right &&
                   dataset_get(obj, vAcc_[ind + right], cutfeat) >= cutval)
                --right;
            if (left > right || !right)
                break;  // "!right" was added to support unsigned Index types
            std::swap(vAcc_[ind + left], vAcc_[ind + right]);
            ++left;
            --right;
        }
        /* If either list is empty, it means that all remaining features
         * are identical. Split in the middle to maintain a balanced tree.
         */
        lim1  = left;
        right = count - 1;
        for (;;)
        {
            while (left <= right &&
                   dataset_get(obj, vAcc_[ind + left], cutfeat) <= cutval)
                ++left;
            while (right && left <= right &&
                   dataset_get(obj, vAcc_[ind + right], cutfeat) > cutval)
                --right;
            if (left > right || !right)
                break;  // "!right" was added to support unsigned Index types
            std::swap(vAcc_[ind + left], vAcc_[ind + right]);
            ++left;
            --right;
        }
        lim2 = left;
    }

    DistanceType computeInitialDistances(
        const Derived& obj, const ElementType* vec,
        distance_vector_t& dists) const
    {
        assert(vec);
        DistanceType dist = DistanceType();

        for (Dimension i = 0; i < (DIM > 0 ? DIM : obj.dim_); ++i)
        {
            if (vec[i] < obj.root_bbox_[i].low)
            {
                dists[i] =
                    obj.distance_.accum_dist(vec[i], obj.root_bbox_[i].low, i);
                dist += dists[i];
            }
            if (vec[i] > obj.root_bbox_[i].high)
            {
                dists[i] =
                    obj.distance_.accum_dist(vec[i], obj.root_bbox_[i].high, i);
                dist += dists[i];
            }
        }
        return dist;
    }

    static void save_tree(
        const Derived& obj, std::ostream& stream, const NodeConstPtr tree)
    {
        save_value(stream, *tree);
        if (tree->child1 != nullptr) { save_tree(obj, stream, tree->child1); }
        if (tree->child2 != nullptr) { save_tree(obj, stream, tree->child2); }
    }

    static void load_tree(Derived& obj, std::istream& stream, NodePtr& tree)
    {
        tree = obj.pool_.template allocate<Node>();
        load_value(stream, *tree);
        if (tree->child1 != nullptr) { load_tree(obj, stream, tree->child1); }
        if (tree->child2 != nullptr) { load_tree(obj, stream, tree->child2); }
    }

    /**  Stores the index in a binary file.
     *   IMPORTANT NOTE: The set of data points is NOT stored in the file, so
     * when loading the index object it must be constructed associated to the
     * same source of data points used while building it. See the example:
     * examples/saveload_example.cpp \sa loadIndex  */
    void saveIndex(const Derived& obj, std::ostream& stream) const
    {
        save_value(stream, obj.size_);
        save_value(stream, obj.dim_);
        save_value(stream, obj.root_bbox_);
        save_value(stream, obj.leaf_max_size_);
        save_value(stream, obj.vAcc_);
        if (obj.root_node_) save_tree(obj, stream, obj.root_node_);
    }

    /**  Loads a previous index from a binary file.
     *   IMPORTANT NOTE: The set of data points is NOT stored in the file, so
     * the index object must be constructed associated to the same source of
     * data points used while building the index. See the example:
     * examples/saveload_example.cpp \sa loadIndex  */
    void loadIndex(Derived& obj, std::istream& stream)
    {
        load_value(stream, obj.size_);
        load_value(stream, obj.dim_);
        load_value(stream, obj.root_bbox_);
        load_value(stream, obj.leaf_max_size_);
        load_value(stream, obj.vAcc_);
        load_tree(obj, stream, obj.root_node_);
    }
};

/** @addtogroup kdtrees_grp KD-tree classes and adaptors
 * @{ */

/** kd-tree static index
 *
 * Contains the k-d trees and other information for indexing a set of points
 * for nearest-neighbor matching.
 *
 *  The class "DatasetAdaptor" must provide the following interface (can be
 * non-virtual, inlined methods):
 *
 *  \code
 *   // Must return the number of data poins
 *   size_t kdtree_get_point_count() const { ... }
 *
 *
 *   // Must return the dim'th component of the idx'th point in the class:
 *   T kdtree_get_pt(const size_t idx, const size_t dim) const { ... }
 *
 *   // Optional bounding-box computation: return false to default to a standard
 * bbox computation loop.
 *   //   Return true if the BBOX was already computed by the class and returned
 * in "bb" so it can be avoided to redo it again.
 *   //   Look at bb.size() to find out the expected dimensionality (e.g. 2 or 3
 * for point clouds) template <class BBOX> bool kdtree_get_bbox(BBOX &bb) const
 *   {
 *      bb[0].low = ...; bb[0].high = ...;  // 0th dimension limits
 *      bb[1].low = ...; bb[1].high = ...;  // 1st dimension limits
 *      ...
 *      return true;
 *   }
 *
 *  \endcode
 *
 * \tparam DatasetAdaptor The user-provided adaptor, which must be ensured to
 *         have a lifetime equal or longer than the instance of this class.
 * \tparam Distance The distance metric to use: nanoflann::metric_L1,
 * nanoflann::metric_L2, nanoflann::metric_L2_Simple, etc. \tparam DIM
 * Dimensionality of data points (e.g. 3 for 3D points) \tparam IndexType Will
 * be typically size_t or int
 */
template <
    typename Distance, class DatasetAdaptor, int32_t DIM = -1,
    typename index_t = uint32_t>
class KDTreeSingleIndexAdaptor
    : public KDTreeBaseClass<
          KDTreeSingleIndexAdaptor<Distance, DatasetAdaptor, DIM, index_t>,
          Distance, DatasetAdaptor, DIM, index_t>
{
   public:
    /** Deleted copy constructor*/
    explicit KDTreeSingleIndexAdaptor(
        const KDTreeSingleIndexAdaptor<
            Distance, DatasetAdaptor, DIM, index_t>&) = delete;

    /** The data source used by this index */
    const DatasetAdaptor& dataset_;

    const KDTreeSingleIndexAdaptorParams indexParams;

    Distance distance_;

    using Base = typename nanoflann::KDTreeBaseClass<
        nanoflann::KDTreeSingleIndexAdaptor<
            Distance, DatasetAdaptor, DIM, index_t>,
        Distance, DatasetAdaptor, DIM, index_t>;

    using Offset    = typename Base::Offset;
    using Size      = typename Base::Size;
    using Dimension = typename Base::Dimension;

    using ElementType  = typename Base::ElementType;
    using DistanceType = typename Base::DistanceType;
    using IndexType    = typename Base::IndexType;

    using Node    = typename Base::Node;
    using NodePtr = Node*;

    using Interval = typename Base::Interval;

    /** Define "BoundingBox" as a fixed-size or variable-size container
     * depending on "DIM" */
    using BoundingBox = typename Base::BoundingBox;

    /** Define "distance_vector_t" as a fixed-size or variable-size container
     * depending on "DIM" */
    using distance_vector_t = typename Base::distance_vector_t;

    /**
     * KDTree constructor
     *
     * Refer to docs in README.md or online in
     * https://github.com/jlblancoc/nanoflann
     *
     * The KD-Tree point dimension (the length of each point in the datase, e.g.
     * 3 for 3D points) is determined by means of:
     *  - The \a DIM template parameter if >0 (highest priority)
     *  - Otherwise, the \a dimensionality parameter of this constructor.
     *
     * @param inputData Dataset with the input features. Its lifetime must be
     *  equal or longer than that of the instance of this class.
     * @param params Basically, the maximum leaf node size
     *
     * Note that there is a variable number of optional additional parameters
     * which will be forwarded to the metric class constructor. Refer to example
     * `examples/pointcloud_custom_metric.cpp` for a use case.
     *
     */
    template <class... Args>
    explicit KDTreeSingleIndexAdaptor(
        const Dimension dimensionality, const DatasetAdaptor& inputData,
        const KDTreeSingleIndexAdaptorParams& params, Args&&... args)
        : dataset_(inputData),
          indexParams(params),
          distance_(inputData, std::forward<Args>(args)...)
    {
        init(dimensionality, params);
    }

    explicit KDTreeSingleIndexAdaptor(
        const Dimension dimensionality, const DatasetAdaptor& inputData,
        const KDTreeSingleIndexAdaptorParams& params = {})
        : dataset_(inputData), indexParams(params), distance_(inputData)
    {
        init(dimensionality, params);
    }

   private:
    void init(
        const Dimension                       dimensionality,
        const KDTreeSingleIndexAdaptorParams& params)
    {
        Base::size_                = dataset_.kdtree_get_point_count();
        Base::size_at_index_build_ = Base::size_;
        Base::dim_                 = dimensionality;
        if (DIM > 0) Base::dim_ = DIM;
        Base::leaf_max_size_ = params.leaf_max_size;
        if (params.n_thread_build > 0)
        {
            Base::n_thread_build_ = params.n_thread_build;
        }
        else
        {
            Base::n_thread_build_ =
                std::max(std::thread::hardware_concurrency(), 1u);
        }

        if (!(params.flags &
              KDTreeSingleIndexAdaptorFlags::SkipInitialBuildIndex))
        {
            // Build KD-tree:
            buildIndex();
        }
    }

   public:
    /**
     * Builds the index
     */
    void buildIndex()
    {
        Base::size_                = dataset_.kdtree_get_point_count();
        Base::size_at_index_build_ = Base::size_;
        init_vind();
        this->freeIndex(*this);
        Base::size_at_index_build_ = Base::size_;
        if (Base::size_ == 0) return;
        computeBoundingBox(Base::root_bbox_);
        // construct the tree
        if (Base::n_thread_build_ == 1)
        {
            Base::root_node_ =
                this->divideTree(*this, 0, Base::size_, Base::root_bbox_);
        }
        else
        {
#ifndef NANOFLANN_NO_THREADS
            std::atomic<unsigned int> thread_count(0u);
            std::mutex                mutex;
            Base::root_node_ = this->divideTreeConcurrent(
                *this, 0, Base::size_, Base::root_bbox_, thread_count, mutex);
#else /* NANOFLANN_NO_THREADS */
            throw std::runtime_error("Multithreading is disabled");
#endif /* NANOFLANN_NO_THREADS */
        }
    }

    /** \name Query methods
     * @{ */

    /**
     * Find set of nearest neighbors to vec[0:dim-1]. Their indices are stored
     * inside the result object.
     *
     * Params:
     *     result = the result object in which the indices of the
     * nearest-neighbors are stored vec = the vector for which to search the
     * nearest neighbors
     *
     * \tparam RESULTSET Should be any ResultSet<DistanceType>
     * \return  True if the requested neighbors could be found.
     * \sa knnSearch, radiusSearch
     *
     * \note If L2 norms are used, all returned distances are actually squared
     *       distances.
     */
    template <typename RESULTSET>
    bool findNeighbors(
        RESULTSET& result, const ElementType* vec,
        const SearchParameters& searchParams = {}) const
    {
        assert(vec);
        if (this->size(*this) == 0) return false;
        if (!Base::root_node_)
            throw std::runtime_error(
                "[nanoflann] findNeighbors() called before building the "
                "index.");
        float epsError = 1 + searchParams.eps;

        // fixed or variable-sized container (depending on DIM)
        distance_vector_t dists;
        // Fill it with zeros.
        auto zero = static_cast<typename RESULTSET::DistanceType>(0);
        assign(dists, (DIM > 0 ? DIM : Base::dim_), zero);
        DistanceType dist = this->computeInitialDistances(*this, vec, dists);
        searchLevel(result, vec, Base::root_node_, dist, dists, epsError);

        if (searchParams.sorted) result.sort();

        return result.full();
    }

    /**
     * Find the "num_closest" nearest neighbors to the \a query_point[0:dim-1].
     * Their indices and distances are stored in the provided pointers to
     * array/vector.
     *
     * \sa radiusSearch, findNeighbors
     * \return Number `N` of valid points in the result set.
     *
     * \note If L2 norms are used, all returned distances are actually squared
     *       distances.
     *
     * \note Only the first `N` entries in `out_indices` and `out_distances`
     *       will be valid. Return is less than `num_closest` only if the
     *       number of elements in the tree is less than `num_closest`.
     */
    Size knnSearch(
        const ElementType* query_point, const Size num_closest,
        IndexType* out_indices, DistanceType* out_distances) const
    {
        nanoflann::KNNResultSet<DistanceType, IndexType> resultSet(num_closest);
        resultSet.init(out_indices, out_distances);
        findNeighbors(resultSet, query_point);
        return resultSet.size();
    }

    /**
     * Find all the neighbors to \a query_point[0:dim-1] within a maximum
     * radius. The output is given as a vector of pairs, of which the first
     * element is a point index and the second the corresponding distance.
     * Previous contents of \a IndicesDists are cleared.
     *
     *  If searchParams.sorted==true, the output list is sorted by ascending
     * distances.
     *
     *  For a better performance, it is advisable to do a .reserve() on the
     * vector if you have any wild guess about the number of expected matches.
     *
     *  \sa knnSearch, findNeighbors, radiusSearchCustomCallback
     * \return The number of points within the given radius (i.e. indices.size()
     * or dists.size() )
     *
     * \note If L2 norms are used, search radius and all returned distances
     *       are actually squared distances.
     */
    Size radiusSearch(
        const ElementType* query_point, const DistanceType& radius,
        std::vector<ResultItem<IndexType, DistanceType>>& IndicesDists,
        const SearchParameters& searchParams = {}) const
    {
        RadiusResultSet<DistanceType, IndexType> resultSet(
            radius, IndicesDists);
        const Size nFound =
            radiusSearchCustomCallback(query_point, resultSet, searchParams);
        return nFound;
    }

    /**
     * Just like radiusSearch() but with a custom callback class for each point
     * found in the radius of the query. See the source of RadiusResultSet<> as
     * a start point for your own classes. \sa radiusSearch
     */
    template <class SEARCH_CALLBACK>
    Size radiusSearchCustomCallback(
        const ElementType* query_point, SEARCH_CALLBACK& resultSet,
        const SearchParameters& searchParams = {}) const
    {
        findNeighbors(resultSet, query_point, searchParams);
        return resultSet.size();
    }

    /**
     * Find the first N neighbors to \a query_point[0:dim-1] within a maximum
     * radius. The output is given as a vector of pairs, of which the first
     * element is a point index and the second the corresponding distance.
     * Previous contents of \a IndicesDists are cleared.
     *
     * \sa radiusSearch, findNeighbors
     * \return Number `N` of valid points in the result set.
     *
     * \note If L2 norms are used, all returned distances are actually squared
     *       distances.
     *
     * \note Only the first `N` entries in `out_indices` and `out_distances`
     *       will be valid. Return is less than `num_closest` only if the
     *       number of elements in the tree is less than `num_closest`.
     */
    Size rknnSearch(
        const ElementType* query_point, const Size num_closest,
        IndexType* out_indices, DistanceType* out_distances,
        const DistanceType& radius) const
    {
        nanoflann::RKNNResultSet<DistanceType, IndexType> resultSet(
            num_closest, radius);
        resultSet.init(out_indices, out_distances);
        findNeighbors(resultSet, query_point);
        return resultSet.size();
    }

    /** @} */

   public:
    /** Make sure the auxiliary list \a vind has the same size than the current
     * dataset, and re-generate if size has changed. */
    void init_vind()
    {
        // Create a permutable array of indices to the input vectors.
        Base::size_ = dataset_.kdtree_get_point_count();
        if (Base::vAcc_.size() != Base::size_) Base::vAcc_.resize(Base::size_);
        for (IndexType i = 0; i < static_cast<IndexType>(Base::size_); i++)
            Base::vAcc_[i] = i;
    }

    void computeBoundingBox(BoundingBox& bbox)
    {
        const auto dims = (DIM > 0 ? DIM : Base::dim_);
        resize(bbox, dims);
        if (dataset_.kdtree_get_bbox(bbox))
        {
            // Done! It was implemented in derived class
        }
        else
        {
            const Size N = dataset_.kdtree_get_point_count();
            if (!N)
                throw std::runtime_error(
                    "[nanoflann] computeBoundingBox() called but "
                    "no data points found.");
            for (Dimension i = 0; i < dims; ++i)
            {
                bbox[i].low = bbox[i].high =
                    this->dataset_get(*this, Base::vAcc_[0], i);
            }
            for (Offset k = 1; k < N; ++k)
            {
                for (Dimension i = 0; i < dims; ++i)
                {
                    const auto val =
                        this->dataset_get(*this, Base::vAcc_[k], i);
                    if (val < bbox[i].low) bbox[i].low = val;
                    if (val > bbox[i].high) bbox[i].high = val;
                }
            }
        }
    }

    /**
     * Performs an exact search in the tree starting from a node.
     * \tparam RESULTSET Should be any ResultSet<DistanceType>
     * \return true if the search should be continued, false if the results are
     * sufficient
     */
    template <class RESULTSET>
    bool searchLevel(
        RESULTSET& result_set, const ElementType* vec, const NodePtr node,
        DistanceType mindist, distance_vector_t& dists,
        const float epsError) const
    {
        /* If this is a leaf node, then do check and return. */
        if ((node->child1 == nullptr) && (node->child2 == nullptr))
        {
            DistanceType worst_dist = result_set.worstDist();
            for (Offset i = node->node_type.lr.left;
                 i < node->node_type.lr.right; ++i)
            {
                const IndexType accessor = Base::vAcc_[i];  // reorder... : i;
                DistanceType    dist     = distance_.evalMetric(
                           vec, accessor, (DIM > 0 ? DIM : Base::dim_));
                if (dist < worst_dist)
                {
                    if (!result_set.addPoint(dist, Base::vAcc_[i]))
                    {
                        // the resultset doesn't want to receive any more
                        // points, we're done searching!
                        return false;
                    }
                }
            }
            return true;
        }

        /* Which child branch should be taken first? */
        Dimension    idx   = node->node_type.sub.divfeat;
        ElementType  val   = vec[idx];
        DistanceType diff1 = val - node->node_type.sub.divlow;
        DistanceType diff2 = val - node->node_type.sub.divhigh;

        NodePtr      bestChild;
        NodePtr      otherChild;
        DistanceType cut_dist;
        if ((diff1 + diff2) < 0)
        {
            bestChild  = node->child1;
            otherChild = node->child2;
            cut_dist =
                distance_.accum_dist(val, node->node_type.sub.divhigh, idx);
        }
        else
        {
            bestChild  = node->child2;
            otherChild = node->child1;
            cut_dist =
                distance_.accum_dist(val, node->node_type.sub.divlow, idx);
        }

        /* Call recursively to search next level down. */
        if (!searchLevel(result_set, vec, bestChild, mindist, dists, epsError))
        {
            // the resultset doesn't want to receive any more points, we're done
            // searching!
            return false;
        }

        DistanceType dst = dists[idx];
        mindist          = mindist + cut_dist - dst;
        dists[idx]       = cut_dist;
        if (mindist * epsError <= result_set.worstDist())
        {
            if (!searchLevel(
                    result_set, vec, otherChild, mindist, dists, epsError))
            {
                // the resultset doesn't want to receive any more points, we're
                // done searching!
                return false;
            }
        }
        dists[idx] = dst;
        return true;
    }

   public:
    /**  Stores the index in a binary file.
     *   IMPORTANT NOTE: The set of data points is NOT stored in the file, so
     * when loading the index object it must be constructed associated to the
     * same source of data points used while building it. See the example:
     * examples/saveload_example.cpp \sa loadIndex  */
    void saveIndex(std::ostream& stream) const
    {
        Base::saveIndex(*this, stream);
    }

    /**  Loads a previous index from a binary file.
     *   IMPORTANT NOTE: The set of data points is NOT stored in the file, so
     * the index object must be constructed associated to the same source of
     * data points used while building the index. See the example:
     * examples/saveload_example.cpp \sa loadIndex  */
    void loadIndex(std::istream& stream) { Base::loadIndex(*this, stream); }

};  // class KDTree

/** kd-tree dynamic index
 *
 * Contains the k-d trees and other information for indexing a set of points
 * for nearest-neighbor matching.
 *
 * The class "DatasetAdaptor" must provide the following interface (can be
 * non-virtual, inlined methods):
 *
 *  \code
 *   // Must return the number of data poins
 *   size_t kdtree_get_point_count() const { ... }
 *
 *   // Must return the dim'th component of the idx'th point in the class:
 *   T kdtree_get_pt(const size_t idx, const size_t dim) const { ... }
 *
 *   // Optional bounding-box computation: return false to default to a standard
 * bbox computation loop.
 *   //   Return true if the BBOX was already computed by the class and returned
 * in "bb" so it can be avoided to redo it again.
 *   //   Look at bb.size() to find out the expected dimensionality (e.g. 2 or 3
 * for point clouds) template <class BBOX> bool kdtree_get_bbox(BBOX &bb) const
 *   {
 *      bb[0].low = ...; bb[0].high = ...;  // 0th dimension limits
 *      bb[1].low = ...; bb[1].high = ...;  // 1st dimension limits
 *      ...
 *      return true;
 *   }
 *
 *  \endcode
 *
 * \tparam DatasetAdaptor The user-provided adaptor (see comments above).
 * \tparam Distance The distance metric to use: nanoflann::metric_L1,
 * nanoflann::metric_L2, nanoflann::metric_L2_Simple, etc.
 * \tparam DIM Dimensionality of data points (e.g. 3 for 3D points)
 * \tparam IndexType Type of the arguments with which the data can be
 * accessed (e.g. float, double, int64_t, T*)
 */
template <
    typename Distance, class DatasetAdaptor, int32_t DIM = -1,
    typename IndexType = uint32_t>
class KDTreeSingleIndexDynamicAdaptor_
    : public KDTreeBaseClass<
          KDTreeSingleIndexDynamicAdaptor_<
              Distance, DatasetAdaptor, DIM, IndexType>,
          Distance, DatasetAdaptor, DIM, IndexType>
{
   public:
    /**
     * The dataset used by this index
     */
    const DatasetAdaptor& dataset_;  //!< The source of our data

    KDTreeSingleIndexAdaptorParams index_params_;

    std::vector<int>& treeIndex_;

    Distance distance_;

    using Base = typename nanoflann::KDTreeBaseClass<
        nanoflann::KDTreeSingleIndexDynamicAdaptor_<
            Distance, DatasetAdaptor, DIM, IndexType>,
        Distance, DatasetAdaptor, DIM, IndexType>;

    using ElementType  = typename Base::ElementType;
    using DistanceType = typename Base::DistanceType;

    using Offset    = typename Base::Offset;
    using Size      = typename Base::Size;
    using Dimension = typename Base::Dimension;

    using Node    = typename Base::Node;
    using NodePtr = Node*;

    using Interval = typename Base::Interval;
    /** Define "BoundingBox" as a fixed-size or variable-size container
     * depending on "DIM" */
    using BoundingBox = typename Base::BoundingBox;

    /** Define "distance_vector_t" as a fixed-size or variable-size container
     * depending on "DIM" */
    using distance_vector_t = typename Base::distance_vector_t;

    /**
     * KDTree constructor
     *
     * Refer to docs in README.md or online in
     * https://github.com/jlblancoc/nanoflann
     *
     * The KD-Tree point dimension (the length of each point in the datase, e.g.
     * 3 for 3D points) is determined by means of:
     *  - The \a DIM template parameter if >0 (highest priority)
     *  - Otherwise, the \a dimensionality parameter of this constructor.
     *
     * @param inputData Dataset with the input features. Its lifetime must be
     *  equal or longer than that of the instance of this class.
     * @param params Basically, the maximum leaf node size
     */
    KDTreeSingleIndexDynamicAdaptor_(
        const Dimension dimensionality, const DatasetAdaptor& inputData,
        std::vector<int>&                     treeIndex,
        const KDTreeSingleIndexAdaptorParams& params =
            KDTreeSingleIndexAdaptorParams())
        : dataset_(inputData),
          index_params_(params),
          treeIndex_(treeIndex),
          distance_(inputData)
    {
        Base::size_                = 0;
        Base::size_at_index_build_ = 0;
        for (auto& v : Base::root_bbox_) v = {};
        Base::dim_ = dimensionality;
        if (DIM > 0) Base::dim_ = DIM;
        Base::leaf_max_size_ = params.leaf_max_size;
        if (params.n_thread_build > 0)
        {
            Base::n_thread_build_ = params.n_thread_build;
        }
        else
        {
            Base::n_thread_build_ =
                std::max(std::thread::hardware_concurrency(), 1u);
        }
    }

    /** Explicitly default the copy constructor */
    KDTreeSingleIndexDynamicAdaptor_(
        const KDTreeSingleIndexDynamicAdaptor_& rhs) = default;

    /** Assignment operator definiton */
    KDTreeSingleIndexDynamicAdaptor_ operator=(
        const KDTreeSingleIndexDynamicAdaptor_& rhs)
    {
        KDTreeSingleIndexDynamicAdaptor_ tmp(rhs);
        std::swap(Base::vAcc_, tmp.Base::vAcc_);
        std::swap(Base::leaf_max_size_, tmp.Base::leaf_max_size_);
        std::swap(index_params_, tmp.index_params_);
        std::swap(treeIndex_, tmp.treeIndex_);
        std::swap(Base::size_, tmp.Base::size_);
        std::swap(Base::size_at_index_build_, tmp.Base::size_at_index_build_);
        std::swap(Base::root_node_, tmp.Base::root_node_);
        std::swap(Base::root_bbox_, tmp.Base::root_bbox_);
        std::swap(Base::pool_, tmp.Base::pool_);
        return *this;
    }

    /**
     * Builds the index
     */
    void buildIndex()
    {
        Base::size_ = Base::vAcc_.size();
        this->freeIndex(*this);
        Base::size_at_index_build_ = Base::size_;
        if (Base::size_ == 0) return;
        computeBoundingBox(Base::root_bbox_);
        // construct the tree
        if (Base::n_thread_build_ == 1)
        {
            Base::root_node_ =
                this->divideTree(*this, 0, Base::size_, Base::root_bbox_);
        }
        else
        {
#ifndef NANOFLANN_NO_THREADS
            std::atomic<unsigned int> thread_count(0u);
            std::mutex                mutex;
            Base::root_node_ = this->divideTreeConcurrent(
                *this, 0, Base::size_, Base::root_bbox_, thread_count, mutex);
#else /* NANOFLANN_NO_THREADS */
            throw std::runtime_error("Multithreading is disabled");
#endif /* NANOFLANN_NO_THREADS */
        }
    }

    /** \name Query methods
     * @{ */

    /**
     * Find set of nearest neighbors to vec[0:dim-1]. Their indices are stored
     * inside the result object.
     * This is the core search function, all others are wrappers around this
     * one.
     *
     * \param result The result object in which the indices of the
     *               nearest-neighbors are stored.
     * \param vec    The vector of the query point for which to search the
     *               nearest neighbors.
     * \param searchParams Optional parameters for the search.
     *
     * \tparam RESULTSET Should be any ResultSet<DistanceType>
     * \return True if the requested neighbors could be found.
     *
     * \sa knnSearch(), radiusSearch(), radiusSearchCustomCallback()
     *
     * \note If L2 norms are used, all returned distances are actually squared
     *       distances.
     */
    template <typename RESULTSET>
    bool findNeighbors(
        RESULTSET& result, const ElementType* vec,
        const SearchParameters& searchParams = {}) const
    {
        assert(vec);
        if (this->size(*this) == 0) return false;
        if (!Base::root_node_) return false;
        float epsError = 1 + searchParams.eps;

        // fixed or variable-sized container (depending on DIM)
        distance_vector_t dists;
        // Fill it with zeros.
        assign(
            dists, (DIM > 0 ? DIM : Base::dim_),
            static_cast<typename distance_vector_t::value_type>(0));
        DistanceType dist = this->computeInitialDistances(*this, vec, dists);
        searchLevel(result, vec, Base::root_node_, dist, dists, epsError);
        return result.full();
    }

    /**
     * Find the "num_closest" nearest neighbors to the \a query_point[0:dim-1].
     * Their indices are stored inside the result object. \sa radiusSearch,
     * findNeighbors
     * \return Number `N` of valid points in
     * the result set.
     *
     * \note If L2 norms are used, all returned distances are actually squared
     *       distances.
     *
     * \note Only the first `N` entries in `out_indices` and `out_distances`
     *       will be valid. Return may be less than `num_closest` only if the
     *       number of elements in the tree is less than `num_closest`.
     */
    Size knnSearch(
        const ElementType* query_point, const Size num_closest,
        IndexType* out_indices, DistanceType* out_distances,
        const SearchParameters& searchParams = {}) const
    {
        nanoflann::KNNResultSet<DistanceType, IndexType> resultSet(num_closest);
        resultSet.init(out_indices, out_distances);
        findNeighbors(resultSet, query_point, searchParams);
        return resultSet.size();
    }

    /**
     * Find all the neighbors to \a query_point[0:dim-1] within a maximum
     * radius. The output is given as a vector of pairs, of which the first
     * element is a point index and the second the corresponding distance.
     * Previous contents of \a IndicesDists are cleared.
     *
     * If searchParams.sorted==true, the output list is sorted by ascending
     * distances.
     *
     * For a better performance, it is advisable to do a .reserve() on the
     * vector if you have any wild guess about the number of expected matches.
     *
     *  \sa knnSearch, findNeighbors, radiusSearchCustomCallback
     * \return The number of points within the given radius (i.e. indices.size()
     * or dists.size() )
     *
     * \note If L2 norms are used, search radius and all returned distances
     *       are actually squared distances.
     */
    Size radiusSearch(
        const ElementType* query_point, const DistanceType& radius,
        std::vector<ResultItem<IndexType, DistanceType>>& IndicesDists,
        const SearchParameters& searchParams = {}) const
    {
        RadiusResultSet<DistanceType, IndexType> resultSet(
            radius, IndicesDists);
        const size_t nFound =
            radiusSearchCustomCallback(query_point, resultSet, searchParams);
        return nFound;
    }

    /**
     * Just like radiusSearch() but with a custom callback class for each point
     * found in the radius of the query. See the source of RadiusResultSet<> as
     * a start point for your own classes. \sa radiusSearch
     */
    template <class SEARCH_CALLBACK>
    Size radiusSearchCustomCallback(
        const ElementType* query_point, SEARCH_CALLBACK& resultSet,
        const SearchParameters& searchParams = {}) const
    {
        findNeighbors(resultSet, query_point, searchParams);
        return resultSet.size();
    }

    /** @} */

   public:
    void computeBoundingBox(BoundingBox& bbox)
    {
        const auto dims = (DIM > 0 ? DIM : Base::dim_);
        resize(bbox, dims);

        if (dataset_.kdtree_get_bbox(bbox))
        {
            // Done! It was implemented in derived class
        }
        else
        {
            const Size N = Base::size_;
            if (!N)
                throw std::runtime_error(
                    "[nanoflann] computeBoundingBox() called but "
                    "no data points found.");
            for (Dimension i = 0; i < dims; ++i)
            {
                bbox[i].low = bbox[i].high =
                    this->dataset_get(*this, Base::vAcc_[0], i);
            }
            for (Offset k = 1; k < N; ++k)
            {
                for (Dimension i = 0; i < dims; ++i)
                {
                    const auto val =
                        this->dataset_get(*this, Base::vAcc_[k], i);
                    if (val < bbox[i].low) bbox[i].low = val;
                    if (val > bbox[i].high) bbox[i].high = val;
                }
            }
        }
    }

    /**
     * Performs an exact search in the tree starting from a node.
     * \tparam RESULTSET Should be any ResultSet<DistanceType>
     */
    template <class RESULTSET>
    void searchLevel(
        RESULTSET& result_set, const ElementType* vec, const NodePtr node,
        DistanceType mindist, distance_vector_t& dists,
        const float epsError) const
    {
        /* If this is a leaf node, then do check and return. */
        if ((node->child1 == nullptr) && (node->child2 == nullptr))
        {
            DistanceType worst_dist = result_set.worstDist();
            for (Offset i = node->node_type.lr.left;
                 i < node->node_type.lr.right; ++i)
            {
                const IndexType index = Base::vAcc_[i];  // reorder... : i;
                if (treeIndex_[index] == -1) continue;
                DistanceType dist = distance_.evalMetric(
                    vec, index, (DIM > 0 ? DIM : Base::dim_));
                if (dist < worst_dist)
                {
                    if (!result_set.addPoint(
                            static_cast<typename RESULTSET::DistanceType>(dist),
                            static_cast<typename RESULTSET::IndexType>(
                                Base::vAcc_[i])))
                    {
                        // the resultset doesn't want to receive any more
                        // points, we're done searching!
                        return;  // false;
                    }
                }
            }
            return;
        }

        /* Which child branch should be taken first? */
        Dimension    idx   = node->node_type.sub.divfeat;
        ElementType  val   = vec[idx];
        DistanceType diff1 = val - node->node_type.sub.divlow;
        DistanceType diff2 = val - node->node_type.sub.divhigh;

        NodePtr      bestChild;
        NodePtr      otherChild;
        DistanceType cut_dist;
        if ((diff1 + diff2) < 0)
        {
            bestChild  = node->child1;
            otherChild = node->child2;
            cut_dist =
                distance_.accum_dist(val, node->node_type.sub.divhigh, idx);
        }
        else
        {
            bestChild  = node->child2;
            otherChild = node->child1;
            cut_dist =
                distance_.accum_dist(val, node->node_type.sub.divlow, idx);
        }

        /* Call recursively to search next level down. */
        searchLevel(result_set, vec, bestChild, mindist, dists, epsError);

        DistanceType dst = dists[idx];
        mindist          = mindist + cut_dist - dst;
        dists[idx]       = cut_dist;
        if (mindist * epsError <= result_set.worstDist())
        {
            searchLevel(result_set, vec, otherChild, mindist, dists, epsError);
        }
        dists[idx] = dst;
    }

   public:
    /**  Stores the index in a binary file.
     *   IMPORTANT NOTE: The set of data points is NOT stored in the file, so
     * when loading the index object it must be constructed associated to the
     * same source of data points used while building it. See the example:
     * examples/saveload_example.cpp \sa loadIndex  */
    void saveIndex(std::ostream& stream) { saveIndex(*this, stream); }

    /**  Loads a previous index from a binary file.
     *   IMPORTANT NOTE: The set of data points is NOT stored in the file, so
     * the index object must be constructed associated to the same source of
     * data points used while building the index. See the example:
     * examples/saveload_example.cpp \sa loadIndex  */
    void loadIndex(std::istream& stream) { loadIndex(*this, stream); }
};

/** kd-tree dynaimic index
 *
 * class to create multiple static index and merge their results to behave as
 * single dynamic index as proposed in Logarithmic Approach.
 *
 *  Example of usage:
 *  examples/dynamic_pointcloud_example.cpp
 *
 * \tparam DatasetAdaptor The user-provided adaptor (see comments above).
 * \tparam Distance The distance metric to use: nanoflann::metric_L1,
 * nanoflann::metric_L2, nanoflann::metric_L2_Simple, etc. \tparam DIM
 * Dimensionality of data points (e.g. 3 for 3D points) \tparam IndexType
 * Will be typically size_t or int
 */
template <
    typename Distance, class DatasetAdaptor, int32_t DIM = -1,
    typename IndexType = uint32_t>
class KDTreeSingleIndexDynamicAdaptor
{
   public:
    using ElementType  = typename Distance::ElementType;
    using DistanceType = typename Distance::DistanceType;

    using Offset = typename KDTreeSingleIndexDynamicAdaptor_<
        Distance, DatasetAdaptor, DIM>::Offset;
    using Size = typename KDTreeSingleIndexDynamicAdaptor_<
        Distance, DatasetAdaptor, DIM>::Size;
    using Dimension = typename KDTreeSingleIndexDynamicAdaptor_<
        Distance, DatasetAdaptor, DIM>::Dimension;

   protected:
    Size leaf_max_size_;
    Size treeCount_;
    Size pointCount_;

    /**
     * The dataset used by this index
     */
    const DatasetAdaptor& dataset_;  //!< The source of our data

    /** treeIndex[idx] is the index of tree in which point at idx is stored.
     * treeIndex[idx]=-1 means that point has been removed. */
    std::vector<int>        treeIndex_;
    std::unordered_set<int> removedPoints_;

    KDTreeSingleIndexAdaptorParams index_params_;

    Dimension dim_;  //!< Dimensionality of each data point

    using index_container_t = KDTreeSingleIndexDynamicAdaptor_<
        Distance, DatasetAdaptor, DIM, IndexType>;
    std::vector<index_container_t> index_;

   public:
    /** Get a const ref to the internal list of indices; the number of indices
     * is adapted dynamically as the dataset grows in size. */
    const std::vector<index_container_t>& getAllIndices() const
    {
        return index_;
    }

   private:
    /** finds position of least significant unset bit */
    int First0Bit(IndexType num)
    {
        int pos = 0;
        while (num & 1)
        {
            num = num >> 1;
            pos++;
        }
        return pos;
    }

    /** Creates multiple empty trees to handle dynamic support */
    void init()
    {
        using my_kd_tree_t = KDTreeSingleIndexDynamicAdaptor_<
            Distance, DatasetAdaptor, DIM, IndexType>;
        std::vector<my_kd_tree_t> index(
            treeCount_,
            my_kd_tree_t(dim_ /*dim*/, dataset_, treeIndex_, index_params_));
        index_ = index;
    }

   public:
    Distance distance_;

    /**
     * KDTree constructor
     *
     * Refer to docs in README.md or online in
     * https://github.com/jlblancoc/nanoflann
     *
     * The KD-Tree point dimension (the length of each point in the datase, e.g.
     * 3 for 3D points) is determined by means of:
     *  - The \a DIM template parameter if >0 (highest priority)
     *  - Otherwise, the \a dimensionality parameter of this constructor.
     *
     * @param inputData Dataset with the input features. Its lifetime must be
     *  equal or longer than that of the instance of this class.
     * @param params Basically, the maximum leaf node size
     */
    explicit KDTreeSingleIndexDynamicAdaptor(
        const int dimensionality, const DatasetAdaptor& inputData,
        const KDTreeSingleIndexAdaptorParams& params =
            KDTreeSingleIndexAdaptorParams(),
        const size_t maximumPointCount = 1000000000U)
        : dataset_(inputData), index_params_(params), distance_(inputData)
    {
        treeCount_  = static_cast<size_t>(std::log2(maximumPointCount)) + 1;
        pointCount_ = 0U;
        dim_        = dimensionality;
        treeIndex_.clear();
        if (DIM > 0) dim_ = DIM;
        leaf_max_size_ = params.leaf_max_size;
        init();
        const size_t num_initial_points = dataset_.kdtree_get_point_count();
        if (num_initial_points > 0) { addPoints(0, num_initial_points - 1); }
    }

    /** Deleted copy constructor*/
    explicit KDTreeSingleIndexDynamicAdaptor(
        const KDTreeSingleIndexDynamicAdaptor<
            Distance, DatasetAdaptor, DIM, IndexType>&) = delete;

    /** Add points to the set, Inserts all points from [start, end] */
    void addPoints(IndexType start, IndexType end)
    {
        const Size count    = end - start + 1;
        int        maxIndex = 0;
        treeIndex_.resize(treeIndex_.size() + count);
        for (IndexType idx = start; idx <= end; idx++)
        {
            const int pos           = First0Bit(pointCount_);
            maxIndex                = std::max(pos, maxIndex);
            treeIndex_[pointCount_] = pos;

            const auto it = removedPoints_.find(idx);
            if (it != removedPoints_.end())
            {
                removedPoints_.erase(it);
                treeIndex_[idx] = pos;
            }

            for (int i = 0; i < pos; i++)
            {
                for (int j = 0; j < static_cast<int>(index_[i].vAcc_.size());
                     j++)
                {
                    index_[pos].vAcc_.push_back(index_[i].vAcc_[j]);
                    if (treeIndex_[index_[i].vAcc_[j]] != -1)
                        treeIndex_[index_[i].vAcc_[j]] = pos;
                }
                index_[i].vAcc_.clear();
            }
            index_[pos].vAcc_.push_back(idx);
            pointCount_++;
        }

        for (int i = 0; i <= maxIndex; ++i)
        {
            index_[i].freeIndex(index_[i]);
            if (!index_[i].vAcc_.empty()) index_[i].buildIndex();
        }
    }

    /** Remove a point from the set (Lazy Deletion) */
    void removePoint(size_t idx)
    {
        if (idx >= pointCount_) return;
        removedPoints_.insert(idx);
        treeIndex_[idx] = -1;
    }

    /**
     * Find set of nearest neighbors to vec[0:dim-1]. Their indices are stored
     * inside the result object.
     *
     * Params:
     *     result = the result object in which the indices of the
     * nearest-neighbors are stored vec = the vector for which to search the
     * nearest neighbors
     *
     * \tparam RESULTSET Should be any ResultSet<DistanceType>
     * \return  True if the requested neighbors could be found.
     * \sa knnSearch, radiusSearch
     *
     * \note If L2 norms are used, all returned distances are actually squared
     *       distances.
     */
    template <typename RESULTSET>
    bool findNeighbors(
        RESULTSET& result, const ElementType* vec,
        const SearchParameters& searchParams = {}) const
    {
        for (size_t i = 0; i < treeCount_; i++)
        {
            index_[i].findNeighbors(result, &vec[0], searchParams);
        }
        return result.full();
    }
};

/** An L2-metric KD-tree adaptor for working with data directly stored in an
 * Eigen Matrix, without duplicating the data storage. You can select whether a
 * row or column in the matrix represents a point in the state space.
 *
 * Example of usage:
 * \code
 * Eigen::Matrix<num_t,Eigen::Dynamic,Eigen::Dynamic>  mat;
 *
 * // Fill out "mat"...
 * using my_kd_tree_t = nanoflann::KDTreeEigenMatrixAdaptor<
 *   Eigen::Matrix<num_t,Dynamic,Dynamic>>;
 *
 * const int max_leaf = 10;
 * my_kd_tree_t mat_index(mat, max_leaf);
 * mat_index.index->...
 * \endcode
 *
 *  \tparam DIM If set to >0, it specifies a compile-time fixed dimensionality
 * for the points in the data set, allowing more compiler optimizations.
 * \tparam Distance The distance metric to use: nanoflann::metric_L1,
 * nanoflann::metric_L2, nanoflann::metric_L2_Simple, etc.
 * \tparam row_major If set to true the rows of the matrix are used as the
 *         points, if set to false  the columns of the matrix are used as the
 *         points.
 */
template <
    class MatrixType, int32_t DIM = -1, class Distance = nanoflann::metric_L2,
    bool row_major = true>
struct KDTreeEigenMatrixAdaptor
{
    using self_t =
        KDTreeEigenMatrixAdaptor<MatrixType, DIM, Distance, row_major>;
    using num_t     = typename MatrixType::Scalar;
    using IndexType = typename MatrixType::Index;
    using metric_t  = typename Distance::template traits<
        num_t, self_t, IndexType>::distance_t;

    using index_t = KDTreeSingleIndexAdaptor<
        metric_t, self_t,
        row_major ? MatrixType::ColsAtCompileTime
                  : MatrixType::RowsAtCompileTime,
        IndexType>;

    index_t* index_;  //! The kd-tree index for the user to call its methods as
                      //! usual with any other FLANN index.

    using Offset    = typename index_t::Offset;
    using Size      = typename index_t::Size;
    using Dimension = typename index_t::Dimension;

    /// Constructor: takes a const ref to the matrix object with the data points
    explicit KDTreeEigenMatrixAdaptor(
        const Dimension                                 dimensionality,
        const std::reference_wrapper<const MatrixType>& mat,
        const int leaf_max_size = 10, const unsigned int n_thread_build = 1)
        : m_data_matrix(mat)
    {
        const auto dims = row_major ? mat.get().cols() : mat.get().rows();
        if (static_cast<Dimension>(dims) != dimensionality)
            throw std::runtime_error(
                "Error: 'dimensionality' must match column count in data "
                "matrix");
        if (DIM > 0 && static_cast<int32_t>(dims) != DIM)
            throw std::runtime_error(
                "Data set dimensionality does not match the 'DIM' template "
                "argument");
        index_ = new index_t(
            dims, *this /* adaptor */,
            nanoflann::KDTreeSingleIndexAdaptorParams(
                leaf_max_size, nanoflann::KDTreeSingleIndexAdaptorFlags::None,
                n_thread_build));
    }

   public:
    /** Deleted copy constructor */
    KDTreeEigenMatrixAdaptor(const self_t&) = delete;

    ~KDTreeEigenMatrixAdaptor() { delete index_; }

    const std::reference_wrapper<const MatrixType> m_data_matrix;

    /** Query for the \a num_closest closest points to a given point (entered as
     * query_point[0:dim-1]). Note that this is a short-cut method for
     * index->findNeighbors(). The user can also call index->... methods as
     * desired.
     *
     * \note If L2 norms are used, all returned distances are actually squared
     *       distances.
     */
    void query(
        const num_t* query_point, const Size num_closest,
        IndexType* out_indices, num_t* out_distances) const
    {
        nanoflann::KNNResultSet<num_t, IndexType> resultSet(num_closest);
        resultSet.init(out_indices, out_distances);
        index_->findNeighbors(resultSet, query_point);
    }

    /** @name Interface expected by KDTreeSingleIndexAdaptor
     * @{ */

    const self_t& derived() const { return *this; }
    self_t&       derived() { return *this; }

    // Must return the number of data points
    Size kdtree_get_point_count() const
    {
        if (row_major)
            return m_data_matrix.get().rows();
        else
            return m_data_matrix.get().cols();
    }

    // Returns the dim'th component of the idx'th point in the class:
    num_t kdtree_get_pt(const IndexType idx, size_t dim) const
    {
        if (row_major)
            return m_data_matrix.get().coeff(idx, IndexType(dim));
        else
            return m_data_matrix.get().coeff(IndexType(dim), idx);
    }

    // Optional bounding-box computation: return false to default to a standard
    // bbox computation loop.
    //   Return true if the BBOX was already computed by the class and returned
    //   in "bb" so it can be avoided to redo it again. Look at bb.size() to
    //   find out the expected dimensionality (e.g. 2 or 3 for point clouds)
    template <class BBOX>
    bool kdtree_get_bbox(BBOX& /*bb*/) const
    {
        return false;
    }

    /** @} */

};  // end of KDTreeEigenMatrixAdaptor
/** @} */

/** @} */  // end of grouping
}  // namespace nanoflann
using namespace nanoflann;


#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <functional>
#include <chrono>
#include <queue>
#include <array>
#include <cstring>
using namespace std;

using pii = pair<int, int>;
#define rep(i, n) for(int i = 0; i < (int)(n); ++i)

const int N = 20, H = 1000;
const int GRID_ROWS = 5, GRID_COLS = 10;  // パレット分割数
const int MAX_WELL_CAPACITY = 8;  // 各ウェルの最大容量（固定値）
const int MAX_PRECOMPUTE_TIME_MS = 600;  // 前処理制限時間をさらに短縮（0.6秒）
int K, T, D;
int actual_max_precompute_grams = 8;  // 実際に前処理できた最大グラム数

// 色を表現する構造体
struct Color {
    double c, m, y;
    Color() : c(0), m(0), y(0) {}
    Color(double c_, double m_, double y_) : c(c_), m(m_), y(y_) {}
    
    Color operator+(const Color& other) const {
        return Color(c + other.c, m + other.m, y + other.y);
    }
    
    Color operator-(const Color& other) const {
        return Color(c - other.c, m - other.m, y - other.y);
    }
    
    Color operator*(double scalar) const {
        return Color(c * scalar, m * scalar, y * scalar);
    }
    
    Color operator/(double scalar) const {
        return Color(c / scalar, m / scalar, y / scalar);
    }
    
    double distanceSquared(const Color& other) const {
        double dc = c - other.c;
        double dm = m - other.m;
        double dy = y - other.y;
        return dc*dc + dm*dm + dy*dy;
    }
    
    double distance(const Color& other) const {
        return sqrt(distanceSquared(other));
    }
};

vector<Color> tubes;
vector<Color> targets;

// デバッグ用カウンタ
long long findClosestMix_calls = 0;
long long total_distance_calculations = 0;

// 事前計算済み混色データ - C++23高性能版
struct alignas(64) PrecomputedMix {
    // SIMD最適化のためのアライメント
    Color color;
    std::array<int, N> recipe;  // 固定サイズ配列でキャッシュ効率向上
    
    // キャッシュされたハッシュ値（FNV-1a算法）
    mutable size_t cached_hash = 0;
    mutable bool hash_valid = false;
    
    // デフォルトコンストラクタ
    PrecomputedMix() noexcept : color{}, recipe{} {}
    
    // パラメータ化コンストラクタ - 完全転送
    template<typename ColorType, typename RecipeType>
    PrecomputedMix(ColorType&& c, RecipeType&& r) noexcept 
        : color(std::forward<ColorType>(c)), recipe{}, cached_hash(0), hash_valid(false) {
        std::copy(r.begin(), r.end(), recipe.begin());
    }
    
    // copy コンストラクタ - std::vector互換性のため
    PrecomputedMix(const PrecomputedMix& other) noexcept
        : color(other.color), recipe(other.recipe), 
          cached_hash(other.cached_hash), hash_valid(other.hash_valid) {}
    
    // copy代入演算子 - std::vector互換性のため
    PrecomputedMix& operator=(const PrecomputedMix& other) noexcept {
        if (this != &other) {
            color = other.color;
            recipe = other.recipe;
            cached_hash = other.cached_hash;
            hash_valid = other.hash_valid;
        }
        return *this;
    }
    
    // move コンストラクタ
    PrecomputedMix(PrecomputedMix&& other) noexcept 
        : color(std::move(other.color)), recipe(std::move(other.recipe)),
          cached_hash(other.cached_hash), hash_valid(other.hash_valid) {}
    
    // move代入演算子  
    PrecomputedMix& operator=(PrecomputedMix&& other) noexcept {
        if (this != &other) {
            color = std::move(other.color);
            recipe = std::move(other.recipe);
            cached_hash = other.cached_hash;
            hash_valid = other.hash_valid;
        }
        return *this;
    }
    
    // ハッシュ値計算（FNV-1a算法）
    [[nodiscard]] size_t hash() const noexcept {
        if (hash_valid) [[likely]] return cached_hash;
        
        const size_t FNV_PRIME = 1099511628211ULL;
        const size_t FNV_OFFSET = 14695981039346656037ULL;
        
        size_t h = FNV_OFFSET;
        
        // colorのハッシュ化（bit表現を使用）
        auto hash_double = [&](double d) {
            uint64_t bits;
            std::memcpy(&bits, &d, sizeof(bits));
            h ^= bits;
            h *= FNV_PRIME;
        };
        
        hash_double(color.c);
        hash_double(color.m);
        hash_double(color.y);
        
        // レシピのハッシュ化
        for (int val : recipe) {
            h ^= static_cast<size_t>(val);
            h *= FNV_PRIME;
        }
        
        cached_hash = h;
        hash_valid = true;
        return h;
    }
    
    // 等価比較演算子
    [[nodiscard]] bool operator==(const PrecomputedMix& other) const noexcept {
        // 色の高速比較
        if (std::memcmp(&color, &other.color, sizeof(Color)) != 0) return false;
        
        // レシピの比較
        return recipe == other.recipe;
    }
};

// std::hash特殊化
namespace std {
    template<>
    struct hash<PrecomputedMix> {
        [[nodiscard]] size_t operator()(const PrecomputedMix& mix) const noexcept {
            return mix.hash();
        }
    };
}

// nanoflann用のPointCloudアダプター
struct PointCloud {
    std::vector<PrecomputedMix>& mixes;

    explicit PointCloud(std::vector<PrecomputedMix>& mixes_ref) : mixes(mixes_ref) {}

    inline size_t kdtree_get_point_count() const { return mixes.size(); }

    inline double kdtree_get_pt(const size_t idx, const size_t dim) const {
        const auto& c = mixes[idx].color;
        return (dim == 0) ? c.c : (dim == 1 ? c.m : c.y);
    }

    template <class BBOX>
    bool kdtree_get_bbox(BBOX&) const { return false; }
};

// KD-Treeを管理するクラス
class KDTree {
private:
    using KDTreeType = KDTreeSingleIndexAdaptor<L2_Simple_Adaptor<double, PointCloud>, PointCloud, 3>;
    KDTreeType* kd_tree;
    std::vector<PrecomputedMix> mixes_storage;
    PointCloud cloud;

public:
    KDTree() : kd_tree(nullptr), mixes_storage(), cloud(mixes_storage) {}

    ~KDTree() {
        delete kd_tree;
    }    void build(std::vector<PrecomputedMix>& mixes) {
        mixes_storage = std::move(mixes);
        cloud.mixes = mixes_storage;
        kd_tree = new KDTreeType(3, cloud, KDTreeSingleIndexAdaptorParams(3));
        kd_tree->buildIndex();
    }

    const PrecomputedMix* findNearest(const Color& target) const {
        if (!kd_tree || cloud.mixes.empty()) return nullptr;

        size_t ret_index;
        double out_dist_sqr;
        double query_pt[3] = {target.c, target.m, target.y};

        KNNResultSet<double> resultSet(1);
        resultSet.init(&ret_index, &out_dist_sqr);
        kd_tree->findNeighbors(resultSet, &query_pt[0], nanoflann::SearchParameters(0.1));

        return &cloud.mixes[ret_index];
    }
};

// グラム数別の事前計算済み混色テーブル
vector<vector<PrecomputedMix>> precomputed_colors;  // precomputed_colors[grams] = 該当グラム数の全混色
vector<KDTree> kdtrees;  // グラム数別のKD-Tree

// 数学的に重複組み合わせを生成する関数（最適化版 - std::function削除）
void generate_multiset_combinations(int total_grams, int num_tubes, vector<vector<int>>& recipes) {
    // total_gramsをnum_tubes個の非負整数に分割する全ての方法を生成
    // 理論組み合わせ数: C(total_grams + num_tubes - 1, num_tubes - 1)
    
    // 予想される組み合わせ数を事前計算して容量を予約
    size_t expected_size = 1;
    for (int i = 0; i < min(num_tubes - 1, total_grams); i++) {
        expected_size = expected_size * (total_grams + num_tubes - 1 - i) / (i + 1);
    }
    recipes.reserve(expected_size);
    
    vector<int> current_recipe(num_tubes, 0);
    
    // 再帰関数をクラス内で定義（std::function削除）
    class Generator {
    public:
        vector<vector<int>>& recipes;
        vector<int>& current_recipe;
        int num_tubes;
        
        Generator(vector<vector<int>>& r, vector<int>& cr, int nt) 
            : recipes(r), current_recipe(cr), num_tubes(nt) {}
        
        void generate(int tube_idx, int remaining_grams) {
            if (tube_idx == num_tubes - 1) {
                // 最後のチューブに残りのグラムを全て割り当て
                current_recipe[tube_idx] = remaining_grams;
                recipes.push_back(current_recipe);
                return;
            }
            
            // 現在のチューブに0～remaining_gramsを割り当て
            for (int use_grams = 0; use_grams <= remaining_grams; use_grams++) {
                current_recipe[tube_idx] = use_grams;
                generate(tube_idx + 1, remaining_grams - use_grams);
            }
        }
    };
    
    Generator gen(recipes, current_recipe, num_tubes);
    gen.generate(0, total_grams);
}

// 時間制限付き事前計算: 数学的組み合わせ生成による最適化版
bool precomputeAllMixtures() {
	static bool initialized = false;
	if (initialized) return true;  // 既に初期化済みなら何もしない
	initialized = true;  // 初期化済みフラグを立てる
    auto start_time = chrono::high_resolution_clock::now();
    
    precomputed_colors.resize(MAX_WELL_CAPACITY + 1);
    kdtrees.resize(MAX_WELL_CAPACITY + 1);
	int counted = 0;
    
    // 各グラム数に対して数学的に組み合わせを生成
    for (int total_grams = 1; total_grams <= 4; total_grams++) {
        auto current_time = chrono::high_resolution_clock::now();
        auto elapsed_ms = chrono::duration_cast<chrono::milliseconds>(current_time - start_time);
        
        if (elapsed_ms.count() > MAX_PRECOMPUTE_TIME_MS) {
            actual_max_precompute_grams = total_grams - 1;
            // cerr << "Precomputation stopped at grams=" << actual_max_precompute_grams 
                //  << " due to time limit (" << elapsed_ms.count() << "ms)" << endl;
            return false;
        }
        
        vector<vector<int>> recipes;
        recipes.reserve(2000); // 容量予約で高速化
        
        // 数学的組み合わせ生成を使用（従来の指数的再帰を置換）
        generate_multiset_combinations(total_grams, K, recipes);
        
        // cerr << "Generated " << recipes.size() << " recipes for " << total_grams << " grams" << endl;
        
        // 各レシピから色を計算
        precomputed_colors[total_grams].reserve(recipes.size()); // 容量予約で高速化
        for (const auto& r : recipes) {
            Color mixed_color;
            int total = 0;
            
            // ループアンローリングで高速化
            const int k_unroll = K & ~3; // 4の倍数部分
            int i = 0;
            for (; i < k_unroll; i += 4) {
                if (r[i] > 0) {
                    mixed_color = mixed_color + tubes[i] * r[i];
                    total += r[i];
                }
                if (r[i+1] > 0) {
                    mixed_color = mixed_color + tubes[i+1] * r[i+1];
                    total += r[i+1];
                }
                if (r[i+2] > 0) {
                    mixed_color = mixed_color + tubes[i+2] * r[i+2];
                    total += r[i+2];
                }
                if (r[i+3] > 0) {
                    mixed_color = mixed_color + tubes[i+3] * r[i+3];
                    total += r[i+3];
                }
            }
            // 残りの要素を処理
            for (; i < K; i++) {
                if (r[i] > 0) {
                    mixed_color = mixed_color + tubes[i] * r[i];
                    total += r[i];
                }
            }
              if (total > 0) {
                mixed_color = mixed_color / total;
                precomputed_colors[total_grams].emplace_back(mixed_color, r);
				counted++;
            }
			if(counted >= 1000) {
				break;
			}
        }
        
        // KD-Treeを構築
        if (!precomputed_colors[total_grams].empty()) {
            kdtrees[total_grams].build(precomputed_colors[total_grams]);
        }
        
        actual_max_precompute_grams = total_grams;

		if(counted >= 1000) {
			break;
		}

	}
	cerr<<counted<<endl;
    
    return true;
}

// 理想の追加色ベクトルを計算 (インライン化で高速化)
inline Color computeIdealAdditionColor(const Color& current_color, int current_grams, const Color& target_color, int add_grams) {
    if (current_grams == 0) {
        return target_color;  // 空のウェルの場合、目標色をそのまま
    }
    
    int total_grams = current_grams + add_grams;
    // target = (current * current_grams + ideal_add * add_grams) / total_grams
    // 解く: ideal_add = (target * total_grams - current * current_grams) / add_grams
    return (target_color * total_grams - current_color * current_grams) / add_grams;
}

// 事前計算済み色の中から最も近いものを検索（KD-Tree使用, インライン化で高速化）
inline const PrecomputedMix* findClosestMix(int grams, const Color& target_color) {
    findClosestMix_calls++;
    
    // 配列外アクセス防止
    if (grams <= 0 || grams > actual_max_precompute_grams) {
        return nullptr;
    }
    
    return kdtrees[grams].findNearest(target_color);
}

// 50個のウェル管理（10x5分割）
struct Well {
    Color currentColor;
    int currentGrams;
    pii position;
    
    Well() : currentGrams(0), position({-1, -1}) {}
    Well(pii pos) : currentGrams(0), position(pos) {}
    
    bool isEmpty() const { return currentGrams == 0; }
    bool isAvailable() const { return position.first >= 0; }
      // 絵の具を追加 (インライン化で高速化)
    inline void addPaint(int tubeId, int grams) {
        Color newTotal = currentColor * currentGrams + tubes[tubeId] * grams;
        currentGrams += grams;
        currentColor = newTotal / currentGrams;
    }
    
    // 1グラム消費 (インライン化で高速化)
    inline void consume() {
        if (currentGrams > 0) {
            currentGrams--;
        }
    }
    
    // 指定量廃棄 (インライン化で高速化)
    inline void dispose(int grams) {
        currentGrams = max(0, currentGrams - grams);
    }
};

// パレット管理クラス（10x5分割版）
class AdvancedPalette {
public:
    vector<Well> wells;
    int total_turns_used = 0;  // 使用済みターン数の追跡
	double error_param = 50000.0;
	int depthPower  = 8;
    
    AdvancedPalette(double error_param_ = 50000.0, int _depthPower=8) : error_param(error_param_), depthPower(_depthPower) {
        wells.resize(GRID_ROWS * GRID_COLS);
        // 10x5グリッドに配置（各ウェルの容量 = MAX_WELL_CAPACITY）
        rep(i, GRID_ROWS * GRID_COLS) {
            int row = i / GRID_COLS;
            int col = i % GRID_COLS;
            int cell_height = N / GRID_ROWS;
            int cell_width = N / GRID_COLS;
            wells[i] = Well({row * cell_height + 1, col * cell_width + 1});
        }
    }
    
    // パレット設定を出力（GRID_COLS x GRID_ROWS分割）
    void printPalette() {
        int cell_width = N / GRID_COLS;
        int cell_height = N / GRID_ROWS;
        
        // 縦の壁 (N行, N-1列)
        rep(i, N) {
            rep(j, N-1) {
                cout << ((j % cell_width == cell_width - 1) ? 1 : 0);
                if (j < N-2) cout << " ";
            }
            cout << "\n";
        }
        
        // 横の壁 (N-1行, N列)
        rep(i, N-1) {
            rep(j, N) {
                cout << ((i % cell_height == cell_height - 1) ? 1 : 0);
                if (j < N-1) cout << " ";
            }
            cout << "\n";
        }
    }
      // 指定されたターゲット色に対して最適な行動を計算（ターン数ペナルティ対応）
    struct Action {
        int wellId;
        vector<pii> additions; // {tubeId, grams}
        int disposalAmount; // 事前廃棄量
        double score; // D*(操作回数-1) + 10000*誤差 + turn_penalty_weight*ターン数
        Color resultColor;
        int turnCount; // このアクションで消費するターン数
        
        Action() : wellId(-1), disposalAmount(0), score(1e9), turnCount(0) {}
          // ターン数を計算 (インライン化で高速化)
        inline void calculateTurnCount() {
            turnCount = disposalAmount; // 廃棄操作
            for (const auto& [tubeId, grams] : additions) {
                turnCount += grams; // 追加操作
            }
            turnCount += 1; // 消費操作
        }
    };

	// 上位X個の候補を取得する関数（priority_queue最適化版）
    vector<Action> findTopActions(const Color& target, int num_candidates = 10, double turn_penalty_weight = 0.0, int remaining_targets = 0) {
        // priority_queueを使って上位num_candidates件のみを保持
        // 最大ヒープ（デフォルト）なので、スコアが大きい順に取り出される
        // 最悪スコアを先頭に持つために、greater比較を使う
        priority_queue<Action, vector<Action>, function<bool(const Action&, const Action&)>> 
            topActions([](const Action& a, const Action& b) { return a.score < b.score; });
        
        // 残りターン数制約をチェック
        int remaining_turns = T - total_turns_used;
        int max_allowed_turns_per_target = remaining_targets > 0 ? 
            max(1, remaining_turns / remaining_targets) : remaining_turns;
        
        // 空ウェルへの操作を1回だけ実行するためのフラグ
        bool empty_well_processed = false;

		int empty_well_count=0;
		rep(wellId, GRID_ROWS * GRID_COLS) {
            Well& well = wells[wellId];
			if(well.isEmpty()) {
				empty_well_count++;
			}
		}
        
        rep(wellId, GRID_ROWS * GRID_COLS) {
            Well& well = wells[wellId];
            
            // 1. 現在の色をそのまま使用（廃棄なし、追加なし）
            if (!well.isEmpty()) {
                Action action;
                action.wellId = wellId;
                action.resultColor = well.currentColor;
                action.turnCount = 1; // 消費のみ                      // ターン数制約チェック
                    if (action.turnCount <= max_allowed_turns_per_target) {
                        double distance_squared = target.distanceSquared(well.currentColor);
                        action.score = error_param * sqrt(distance_squared) 
                                     + turn_penalty_weight * action.turnCount;
                        
                        // priority_queueに追加（サイズ制限付き）
                        if (topActions.size() < num_candidates) {
                            topActions.push(action);
                        } else if (action.score < topActions.top().score) {
                            topActions.pop();
                            topActions.push(action);
                        }
                    }
            }
            
            // 2. 新しいアルゴリズム: (ウェル, 追加グラム数)でループ
            // 空ウェルの場合は最初の1つのウェルでのみ処理
            if (well.isEmpty() && empty_well_processed) {
                continue; // 空ウェルは既に処理済みなのでスキップ
            }
            
            // ターン数制約が厳しい場合は追加グラム数を制限
            int max_add_grams = std::min({MAX_WELL_CAPACITY, actual_max_precompute_grams, max_allowed_turns_per_target - 1});
            
            for (int add_grams = 1; add_grams <= max_add_grams; add_grams++) {
                // 現在のウェル容量制限チェック
                if (well.currentGrams + add_grams > MAX_WELL_CAPACITY) continue;
                
                // 理想の追加色ベクトルを計算
                Color ideal_add_color = computeIdealAdditionColor(
                    well.currentColor, well.currentGrams, target, add_grams
                );
                
                // 事前計算済みの色から最適なものを検索
                const PrecomputedMix* best_mix = findClosestMix(
                    add_grams, ideal_add_color
                );
                
                if (best_mix != nullptr) {
                    // 実際の結果色を計算
                    Color result_color;
                    if (well.currentGrams == 0) {
                        result_color = best_mix->color;
                    } else {
                        Color total_color = well.currentColor * well.currentGrams + best_mix->color * add_grams;
                        result_color = total_color / (well.currentGrams + add_grams);
                    }
                      // アクションを構築
                    Action action;
                    action.wellId = wellId;
                    action.resultColor = result_color;
                    
                    // レシピをadditionsに変換（高速化）
                    action.additions.reserve(K); // 最大サイズを事前予約
                    for (int i = 0; i < K; i++) {
                        if (best_mix->recipe[i] > 0) {
                            action.additions.emplace_back(i, best_mix->recipe[i]);
                        }
                    }
                    
                    action.calculateTurnCount();                      // ターン数制約チェック
                    if (action.turnCount <= max_allowed_turns_per_target) {
                        double distance_squared = target.distanceSquared(result_color);
                        action.score = D * add_grams + error_param * sqrt(distance_squared)
                                     + turn_penalty_weight * action.turnCount;
                        
						// 空ウェルに対する操作にボーナス
						if (well.isEmpty()) {
							action.score *= 0.5 + 0.5 * (50 - empty_well_count) / 50;  // 空ウェルへの操作はスコアを半分に
						}

                        // priority_queueに追加（サイズ制限付き）
                        if (topActions.size() < num_candidates) {
                            topActions.push(action);
                        } else if (action.score < topActions.top().score) {
                            topActions.pop();
                            topActions.push(action);
                        }
                    }
                }
            }
              // 空ウェルの処理が完了したことをマーク
            if (well.isEmpty()) {
                empty_well_processed = true;
            }
            
            // 3. 廃棄戦略: 制約が緩い場合のみ実行
            if (!well.isEmpty() && turn_penalty_weight < D * 5.0) {
                for (int dispose_grams = 1; dispose_grams <= min(well.currentGrams,1); dispose_grams++) {
                    int remaining_grams = well.currentGrams - dispose_grams;
                    
                    int max_add_after_dispose = min({MAX_WELL_CAPACITY - remaining_grams, 
                                                   actual_max_precompute_grams, 
                                                   max_allowed_turns_per_target - dispose_grams - 1});
                    
                    for (int add_grams = 1; add_grams <= max_add_after_dispose; add_grams++) {
                        // 廃棄後の理想の追加色ベクトルを計算
                        Color ideal_add_color = computeIdealAdditionColor(
                            well.currentColor, remaining_grams, target, add_grams
                        );
                        
                        const PrecomputedMix* best_mix = findClosestMix(
                            add_grams, ideal_add_color
                        );
                        
                        if (best_mix != nullptr) {
                            Color result_color;                            if (remaining_grams == 0) {
                                result_color = best_mix->color;
                            } else {
                                Color total_color = well.currentColor * remaining_grams + best_mix->color * add_grams;
                                result_color = total_color / (remaining_grams + add_grams);                            }
                            
                            Action action;
                            action.wellId = wellId;
                            action.disposalAmount = dispose_grams;
                            action.resultColor = result_color;
                            
                            // レシピを事前に構築してからadditionsに追加（高速化）
                            action.additions.reserve(K); // 最大サイズを事前予約
                            for (int j = 0; j < K; j++) {
                                if (best_mix->recipe[j] > 0) {
                                    action.additions.emplace_back(j, best_mix->recipe[j]);
                                }
                            }
                            
                            action.calculateTurnCount();
                            // ターン数制約チェック
                            if (action.turnCount <= max_allowed_turns_per_target) {
                                double distance_squared = target.distanceSquared(result_color);
                                action.score = D * (dispose_grams + add_grams) + error_param * sqrt(distance_squared)
                                             + turn_penalty_weight * action.turnCount;
                                
                                // priority_queueに追加（サイズ制限付き）
                                if (topActions.size() < static_cast<size_t>(num_candidates)) {
                                    topActions.push(action);
                                } else if (action.score < topActions.top().score) {
                                    topActions.pop();
                                    topActions.push(action);
                                }
                            }
                        }
                    }
                }
            }
        }
        
        // priority_queueから結果を取り出してvectorに変換
        vector<Action> result;
        result.reserve(topActions.size());
        
        while (!topActions.empty()) {
            result.push_back(topActions.top());
            topActions.pop();
        }
        
        // priority_queueは最大ヒープなので、スコアの昇順にするため逆順にする
        reverse(result.begin(), result.end());
        
        return result;
    }
    
    // 従来のfindBestAction関数（互換性のため）
    Action findBestAction(const Color& target, double turn_penalty_weight = 0.0, int remaining_targets = 0) {
        vector<Action> topActions = findTopActions(target, 1, turn_penalty_weight, remaining_targets);
        if (topActions.empty()) {
            return Action(); // デフォルトアクション
        }
        return topActions[0];
    }
      // アクションを実行
    void executeAction(const Action& action) {
        if (action.wellId < 0) return;
        
        Well& well = wells[action.wellId];
        
        // 事前廃棄
        if (action.disposalAmount > 0) {
            rep(i, action.disposalAmount) {
                cout << "3 " << well.position.first << " " << well.position.second << "\n";
                total_turns_used++;
            }
            well.dispose(action.disposalAmount);
        }
        
        // 絵の具を追加
        for (const auto& [tubeId, grams] : action.additions) {
            rep(g, grams) {
                cout << "1 " << well.position.first << " " << well.position.second 
                     << " " << tubeId << "\n";
                total_turns_used++;
            }
            well.addPaint(tubeId, grams);
        }
        
        // 1グラム消費
        cout << "2 " << well.position.first << " " << well.position.second << "\n";
        well.consume();
        total_turns_used++;
    }

    
    // プレイアウト用のパレット状態をコピー
    AdvancedPalette copyPalette() const {
        AdvancedPalette copy;
		copy.error_param = this->error_param;
        copy.wells = this->wells;
        copy.total_turns_used = this->total_turns_used;
        return copy;
    }
      // アクションを実行（出力なし、プレイアウト用）
    void executeActionSilent(const Action& action) {
        if (action.wellId < 0) return;
        
        Well& well = wells[action.wellId];
        
        // 事前廃棄
        if (action.disposalAmount > 0) {
            total_turns_used += action.disposalAmount;
            well.dispose(action.disposalAmount);
        }
        
        // 絵の具を追加
        for (const auto& [tubeId, grams] : action.additions) {
            total_turns_used += grams;
            well.addPaint(tubeId, grams);
        }
        
        // 1グラム消費
        well.consume();
        total_turns_used++;
    }      // プレイアウト：指定アクションを実行後、残りターゲットに対して最善手を続けた場合の総合スコアを計算
    double evaluateWithPlayout(const Action& firstAction, const int remainingTargetIndex, double currentBestPlayoutScore) {
        // パレット状態を軽量コピー（参照を使って最適化）
        AdvancedPalette playoutPalette = *this; // shallow copy first
        playoutPalette.wells = this->wells; // 必要な部分のみディープコピー
        
        // 最初のアクションを実行
        playoutPalette.executeActionSilent(firstAction);
        
        double totalScore = 0.0;
        double errorSum = 0.0;
        int totalOperations = firstAction.turnCount - 1; // 消費分を除く
        
        // 最初のターゲットの誤差を追加
        double distance_squared = firstAction.resultColor.distanceSquared(targets[remainingTargetIndex]);
        double firstError = sqrt(distance_squared);
        errorSum += firstError;
        
        // 残りのターゲットに対してプレイアウト（効率化）
        int remainingTurns = T - playoutPalette.total_turns_used;
        int remainingTargetCount = H - remainingTargetIndex - 1;
        int processedTargets = min({depthPower, remainingTargetCount, remainingTurns});
        int processed = 0;
        
        // プレイアウトループの最適化：候補数を制限し、事前計算を活用
        for (int i = 1; i <= processedTargets; i++) {
            if (playoutPalette.total_turns_used >= T) break;
            
            // 早期打ち切り判定を前倒し
            double partialScore = 1.0 + D * totalOperations + error_param * errorSum;
            if (partialScore > currentBestPlayoutScore) {
                return 1e9; // スコアが悪化する場合は早期終了
            }
            
            int remaining = remainingTargetCount - i;
            
            // プレイアウト用に候補を1つに限定して高速化
            vector<Action> topActions = playoutPalette.findTopActions(targets[remainingTargetIndex+i], 1, 0.0, remaining);
            
            if (!topActions.empty() && playoutPalette.total_turns_used + topActions[0].turnCount <= T) {
                const Action& bestAction = topActions[0];
                playoutPalette.executeActionSilent(bestAction);
                
                double distance_squared = bestAction.resultColor.distanceSquared(targets[remainingTargetIndex+i]);
                double error = sqrt(distance_squared);
                errorSum += error;
                totalOperations += (bestAction.turnCount - 1); // 消費分を除く
                processed++;
            } else {
                // アクションが見つからない、またはターン数超過の場合、大きなペナルティ
                errorSum += 1.0;
                break; // プレイアウト中止
            }
        }
        
        // 未処理のターゲットに対するペナルティ
        int unprocessedTargets = remainingTargetCount - processed;
        if (unprocessedTargets > 0) {
            errorSum += unprocessedTargets * 1.0; // 未処理ペナルティ
        }
        
        // スコア計算：1 + D*(V-H) + round(10^4 * E)
        // V = totalOperations + remainingTargets.size() (消費ターン数)
        // H = remainingTargets.size()
        // なので D*(V-H) = D*totalOperations
        totalScore = 1.0 + D * totalOperations + error_param * errorSum;
        
        return totalScore;
    }
	double calc_true_score(const Action& action, const Color& target) {
		double distance_squared = action.resultColor.distanceSquared(target);
		double error = sqrt(distance_squared);
		return D * (action.turnCount - 1) + round(10000.0 * error);
	}

};

const int TLE = 2900;


const auto program_start_time = chrono::high_resolution_clock::now();
// 簡素化されたメインソルバー
class TurnConstrainedSolver {
public:
	double error_param = 50000.0;  // 誤差パラメータ
	int depthPower = 8;  // プレイアウト深さ制御
	TurnConstrainedSolver(double _error_param = 50000.0, int _depthPower=8 ): error_param(_error_param), depthPower(_depthPower) {
        // 入力読み込み
		if (tubes.empty()) {
			int _N, _H;
			cin >> _N >> K >> _H >> T >> D;
			
			tubes.resize(K);
			rep(i, K) {
				cin >> tubes[i].c >> tubes[i].m >> tubes[i].y;
			}
			targets.resize(_H);        rep(i, _H) {
				cin >> targets[i].c >> targets[i].m >> targets[i].y;
			}
		}
	}

	vector<AdvancedPalette::Action> actions;
	double true_score = 10000000000.0;
    void solve() {
		true_score = 0;

		// 事前計算を実行
        precomputeAllMixtures();
        
        // 前計算結果の統計を出力
        int total_mixes = 0;
        for (int g = 1; g <= actual_max_precompute_grams; g++) {
            total_mixes += precomputed_colors[g].size();
        }
        
        // ターン数制約の詳細分析
        int estimated_min_turns = targets.size();  // 各色最低1ターン
        double turn_constraint_ratio = (double)estimated_min_turns / T;
        double turn_penalty_weight = 0.0;

		if (turn_constraint_ratio > 0.3) {
            // ターン数制約が厳しい場合、ペナルティを適用
            turn_penalty_weight = D * min(10.0, turn_constraint_ratio * 20.0);
        } else if (turn_constraint_ratio > 0.2) {
            // 中程度のターン数制約
            turn_penalty_weight = D * 2.0;
        } else {
			// ターン数制約が緩い場合はペナルティなし
			turn_penalty_weight = 0.0;
        }
        
        // メイン処理開始（モンテカルロプレイアウト版）
        AdvancedPalette palette(error_param, depthPower);
        
        // モンテカルロプレイアウトを使った候補選択
        for (int targetIndex = 0; targetIndex < targets.size(); targetIndex++) {
            if (palette.total_turns_used >= T) break;

            
            Color currentTarget = targets[targetIndex];
            
              // 上位候補を取得（動的調整）
            int remainingTargetsCount = targets.size() - targetIndex;
            int numCandidates;
            
            if (remainingTargetsCount > 50) {
                numCandidates = 3;  // 多くのターゲットが残っている場合は高速化
            } else if (remainingTargetsCount > 20) {
                numCandidates = 4;  // 中程度の場合
            } else {
                numCandidates = min(10, remainingTargetsCount);  // 少ない場合は詳細評価
            }

			const auto current_time = chrono::high_resolution_clock::now();
			auto elapsed_ms = chrono::duration_cast<chrono::milliseconds>(current_time - program_start_time);
			if (elapsed_ms.count() > TLE) {
				numCandidates = 1;
				cerr<<"TLE"<<endl;
			}
            
            vector<AdvancedPalette::Action> topActions = palette.findTopActions(
                currentTarget, numCandidates, turn_penalty_weight, remainingTargetsCount
            );
            
            if (topActions.empty()) {
                break;
            }
            
            // プレイアウトによる評価
            double bestPlayoutScore = 1e9;
            int bestActionIndex = 0;

			if(numCandidates > 1){
				for (int i = 0; i < topActions.size(); i++) {
					double playoutScore = palette.evaluateWithPlayout(topActions[i], targetIndex, bestPlayoutScore);
					if (playoutScore < bestPlayoutScore) {
						bestPlayoutScore = playoutScore;
						bestActionIndex = i;
					}
				}
			}
            
            // 最良のアクションを実行
            AdvancedPalette::Action bestAction = topActions[bestActionIndex];
            
            palette.executeActionSilent(bestAction);
			actions.push_back(bestAction);

			true_score += palette.calc_true_score(bestAction, currentTarget);
        }
    }

	void print() {
		AdvancedPalette palette(error_param);
        palette.printPalette();

		for (const auto& action : actions) {
			palette.executeAction(action);
		}
	}
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

	// 時間をms単位で取得
	auto start_time = chrono::high_resolution_clock::now();


	// ソルバーを初期化して実行
	int try_count = 0, duration_sum = 0;
	TurnConstrainedSolver& best_solver = *new TurnConstrainedSolver(50000.0);
	auto precalced_time = chrono::high_resolution_clock::now();

	auto calc_best_error = [&](double e) {
		TurnConstrainedSolver solver(e, 0);
		solver.solve();
		cerr << "TRUE SCORE: " << e << " " << solver.true_score << endl;
		if (solver.true_score < best_solver.true_score) {
			best_solver = solver;
			cerr << "New best solver found with error_param: " << e << endl;
		}
		return solver.true_score;
	};

    // 最適なerrorを黄金分割探索（3分探索ではない）
	double error_l = 1000, error_r = 500000;
	while(error_r - error_l > 500) {
		double error_m1 = error_l + (error_r - error_l) * 0.382; // 黄金分割の左側
		double error_m2 = error_l + (error_r - error_l) * 0.618; // 黄金分割の右側

		double score_m1 = calc_best_error(error_m1);
		double score_m2 = calc_best_error(error_m2);

		if (score_m1 < score_m2) {
			error_r = error_m2; // 左側が良いので右端を縮める
		} else {
			error_l = error_m1; // 右側が良いので左端を縮める
		}
	}

	double best_error = (error_l + error_r) / 2.0;
	best_solver = TurnConstrainedSolver(best_error, 0);
	best_solver.solve();

	TurnConstrainedSolver solver(best_error, 18);
	solver.solve();

	if(solver.true_score < best_solver.true_score) {
		cerr << "depth search succeeded: " << best_solver.true_score << "->" << solver.true_score << endl;
		best_solver = solver;
	}else if(solver.true_score >= 1e9 - 1e-6){
		assert(false);
	}

	best_solver.print();
	cerr<< "Final best error_param: " << best_error << endl;
	cerr << "Final true score: " << best_solver.true_score << endl;

	auto finished_time = chrono::high_resolution_clock::now();
	auto elapsed_ms = chrono::duration_cast<chrono::milliseconds>(finished_time - start_time);
	cerr << elapsed_ms.count() << " ms" << endl;
    return 0;
}
