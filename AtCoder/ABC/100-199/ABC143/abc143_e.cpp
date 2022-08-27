#ifdef _DEBUG
// #define _GLIBCXX_DEBUG 1
#else
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("inline")
#endif
#pragma GCC target ("avx2") 
/* 
 * Include Headers
 */
#if defined(EVAL) || defined(ONLINE_JUDGE) || defined(_DEBUG)
// #include <atcoder/all>
// using namespace atcoder;
#endif
#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;

/*
 * Additional Type Definition
 */
using ll=long long;
using ld=long double;
using ull=unsigned long long;
using vb=vector<bool>;
using vvb=vector<vb>;
using vd=vector<ld>;
using vvd=vector<vd>;
using vi=vector<int>;
using vvi=vector<vi>;
using vl=vector<ll>;
using vvl=vector<vl>;
using pii=pair<int,int>;
using pll=pair<ll,ll>;
using vp=vector<pll>;
using tl2=tuple<ll,ll>;
using tl3=tuple<ll,ll,ll>;
using vs=vector<string>;
template<class K> using IndexedSet=__gnu_pbds::tree<K,__gnu_pbds::null_type,less<K>,__gnu_pbds::rb_tree_tag,__gnu_pbds::tree_order_statistics_node_update>;
template<class K> using HashSet=__gnu_pbds::gp_hash_table<K,__gnu_pbds::null_type>;
template<class K,class V> using IndexedMap=__gnu_pbds::tree<K,V,less<K>,__gnu_pbds::rb_tree_tag,__gnu_pbds::tree_order_statistics_node_update>;
template<class K,class V> using HashMap=__gnu_pbds::gp_hash_table<K,V>;
template<class V> using minpq = priority_queue<V, vector<V>, greater<V>>;

#define all(a) begin(a),end(a)
#define rall(a) rbegin(a),rend(a)
#define __LOOPSWITCH(_1, _2, _3, __LOOPSWITCH, ...) __LOOPSWITCH
#define rep(...) __LOOPSWITCH(__VA_ARGS__, __RANGE, __REP, __LOOP) (__VA_ARGS__)
#define rrep(...) __LOOPSWITCH(__VA_ARGS__, __RRANGE, __RREP, __LOOP) (__VA_ARGS__)
#define __LOOP(q) __LOOP2(q, __LINE__)
#define __LOOP2(q,l) __LOOP3(q,l)
#define __LOOP3(q,l) __REP(_lp ## l,q)
#define __REP(i,n) __RANGE(i,0,n)
#define __RANGE(i,a,n) for(ll i=((ll)a);i<((ll)n);++i)
#define __RREP(i,n) __RRANGE(i,0,n)
#define __RRANGE(i,a,n) for(ll i=((ll)(n)-1);i>=((ll)a);--i)
#define sz(a) ((ll)(a).size())

/*
 * Constants
 */
constexpr ll LINF=1ll<<60;
constexpr int INF=1<<30;
constexpr double EPS=(1e-14);
constexpr ll MOD=998244353ll;
constexpr long double PI=3.14159265358979323846;

/*
 * Utilities
 */
template<class T>constexpr bool chmax(T&a,T b){return a<b?a=b,1:0;}
template<class T>constexpr bool chmin(T&a,T b){return a>b?a=b,1:0;}
template<class S>S sum(vector<S>&a){return accumulate(all(a),S());}
template<class S>S max(vector<S>&a){return *max_element(all(a));}
template<class S>S min(vector<S>&a){return *min_element(all(a));}

namespace IO {
	// container detection
	template<typename T, typename _=void> struct is_container : false_type {};
	template<> struct is_container<string> : false_type {};
	template<typename...Ts> struct is_container_helper {};
	template<typename T> struct is_container<T, conditional_t<
		true, void, is_container_helper<
			typename T::value_type, typename T::size_type, typename T::iterator,
			decltype(declval<T>().size()),
			decltype(declval<T>().begin()),
			decltype(declval<T>().end()) >>> : public true_type {};
	template<typename T,
		typename enable_if<is_container<T>{}, nullptr_t>::type = nullptr,
		char Separator = is_container<typename T::value_type>{} ? '\n' : ' ' >
	constexpr ostream&operator<<(ostream&os, T t){
		if(auto b=begin(t), e=end(t) ; !t.empty()) for(os<<(*b++);b!=e;os<<Separator<<(*b++)) ;
		return os;
	}

	// output
	template<class T, class...Ts> constexpr ostream& pargs(ostream&os, T&&t, Ts&&...args); // support clang
	template<class S,class T>constexpr ostream&operator<<(ostream&os,pair<S,T>p){ return os<<'['<<p.first<<", "<<p.second<<']'; };
	template<class...Ts>constexpr ostream&operator<<(ostream&os,tuple<Ts...>t){
		return apply([&os](auto&&t,auto&&...args)->ostream&{return pargs(os, t, args...);}, t);
	};
	template<class T, class...Ts> constexpr ostream& pargs(ostream&os, T&&t, Ts&&...args) {
		return ((os<<t)<<...<<(os<<' ', args));
	}

	template<class...Ts> constexpr ostream& out(Ts...args) { return pargs(cout, args...)<<'\n'; }
	template<class...Ts> constexpr ostream& debug_f(Ts...args) { return pargs(cerr, args...)<<'\n'; }
	#ifdef _DEBUG
	template<class...Ts> constexpr ostream& debug(Ts...args) { return pargs(cerr, args...)<<'\n'; }
	#else
	#define debug(...) if(false)debug_f(__VA_ARGS__)
	#endif
	void Yn(bool f) { out(f?"Yes":"No"); }

	// input
	template<class T, class...Ts> constexpr istream& gargs(istream&is, T&&t, Ts&&...args) {
		return ((is>>t)>>...>>args);
	}
	template<class S,class T>auto&operator>>(istream&is,pair<S,T>&p){return is>>p.first>>p.second;}
	template<class...Ts>constexpr istream&operator>>(istream&is,tuple<Ts...>&t){
		return apply([&is](auto&&t,auto&&...args)->istream&{return gargs(is, t, args...);}, t);
	};

	template<typename...S>auto&in(S&...s){return gargs(cin, s...);}
	#define def(t,...) t __VA_ARGS__; in(__VA_ARGS__)
	template<typename T, typename enable_if<is_container<T>{}, nullptr_t>::type = nullptr>
	auto&operator>>(istream&is,T&t){for(auto&a:t)is>>a; return is;}
}
using namespace IO;

class Random {
public:
	typedef uint_fast32_t result_type;
	constexpr result_type operator()(){return operator()((ll)min(),(ll)max());}
	static constexpr result_type max(){return numeric_limits<result_type>::max();}
	static constexpr result_type min(){return 0;}
	constexpr Random(const bool&isDeterministic):y(isDeterministic?2463534242:chrono::system_clock::now().time_since_epoch().count()){}
	constexpr int operator()(int a,int b){return next()%(b-a)+a;}
	constexpr ll operator()(ll a,ll b){return (((ull)next())<<32|next())%(b-a)+a;}
	constexpr double operator()(double a,double b){return (b-a)*next()/4294967296.0+a;}
private:
	result_type y;
	constexpr result_type next(){return y^=(y^=(y^=y<<13)>>17)<<5;}
} Random(0);

class Timer {
	#ifdef _DEBUG
	static constexpr uint64_t ClocksPerMsec = 3587000;
	#else
	static constexpr uint64_t ClocksPerMsec = 2987000;
	#endif
	const uint64_t start,limit;
	uint64_t getClocks() const{
		unsigned int lo,hi;
		__asm__ volatile ("rdtsc" : "=a" (lo), "=d" (hi));
		return((uint64_t)hi<<32)|lo;
	}
public:
	Timer(uint64_t _limit=1970): start(getClocks()),limit(start+_limit*ClocksPerMsec) {}
	uint64_t get() const{return (getClocks()-start)/ClocksPerMsec;}
	operator bool()const{return getClocks()<limit;}
};
void wait(const int&msec){Timer tm(msec); while(tm);}

struct Mgr {
	static const int TLE = 2000;
	static inline Timer timer = Timer(TLE-20);
	Mgr() {
		ios_base::sync_with_stdio(0); cin.tie(0);
		cout<<fixed<<setprecision(11);
		cerr<<fixed<<setprecision(3);
	}
	~Mgr(){
		debug_f(timer.get(), "ms")<<flush;
	}
} _manager;

namespace std::tr1 {
	template<class T>
	struct hash_base {
		const static inline size_t hash_value = 0x9e3779b9;
		static inline size_t hash_rnd = Random(0, numeric_limits<size_t>::max());
		template<class V> static size_t& do_hash(size_t&seed, V&v) {
			return seed ^= hash<V>{}(v) + hash_value + (seed<<6) + (seed>2);
		}
		virtual size_t operator()(T p) const = 0;
	};

	template<class S, class T>
	struct hash<pair<S,T>> : public hash_base<pair<S,T>> {
		size_t operator()(pair<S,T> p) const {
			size_t seed = 0;
			this->do_hash(seed, p.first);
			this->do_hash(seed, p.second);
			return this->do_hash(seed, this->hash_value);
		}
	};
}


#include <immintrin.h>
namespace quick_floyd_warshall {
namespace vectorize {

// instruction set for vectorization
enum class InstSet {
	DEFAULT,
	SSE4_2,
	AVX2,
	AVX512
};
std::string inst_set_to_str(InstSet inst_set) {
	if (inst_set == InstSet::DEFAULT) return "DEFAULT";
	if (inst_set == InstSet::SSE4_2 ) return "SSE4_2";
	if (inst_set == InstSet::AVX2   ) return "AVX2";
	if (inst_set == InstSet::AVX512 ) return "AVX512";
	return "";
}

// wrapper of sse/avx intrinsics
template<InstSet inst_set> class vector_base_t;
template<> class vector_base_t<InstSet::SSE4_2> {
public:
	static constexpr int SIZE = 16;
	using internal_vector_t = __m128i;
	internal_vector_t vec;
	
	vector_base_t ()  = default;
	vector_base_t (internal_vector_t vec_) : vec(vec_) {}
	vector_base_t (void *ptr) : vec(_mm_load_si128((internal_vector_t *) ptr)) {}
	vector_base_t &store(void *ptr) { _mm_store_si128((internal_vector_t *) ptr, vec); return *this; }
};
template<InstSet inst_set> class vector_base_t;
template<> class vector_base_t<InstSet::AVX2> {
public:
	static constexpr int SIZE = 32;
	using internal_vector_t = __m256i;
	internal_vector_t vec;
	
	vector_base_t ()  = default;
	vector_base_t (internal_vector_t vec_) : vec(vec_) {}
	vector_base_t (void *ptr) : vec(_mm256_load_si256((internal_vector_t *) ptr)) {}
	vector_base_t &store(void *ptr) { _mm256_store_si256((internal_vector_t *) ptr, vec); return *this; }
};
template<> class vector_base_t<InstSet::AVX512> {
public:
	static constexpr int SIZE = 64;
	using internal_vector_t = __m512i;
	internal_vector_t vec;
	
	vector_base_t ()  = default;
	vector_base_t (internal_vector_t vec_) : vec(vec_) {}
	vector_base_t (void *ptr) : vec(_mm512_load_si512((internal_vector_t *) ptr)) {}
	vector_base_t &store(void *ptr) { _mm512_store_si512((internal_vector_t *) ptr, vec); return *this; }
};

template<InstSet inst_set, typename T> class vector_t;

/*
	vec.chmin_store(mem): mem[i] = min(mem[i], vec[i])
	vec.chmax_store(mem): mem[i] = max(mem[i], vec[i])
*/


// DEFAULT / *
template<typename T> class vector_t<InstSet::DEFAULT, T> {
	static_assert(std::is_same<T, int16_t>::value || std::is_same<T, int32_t>::value || std::is_same<T, int64_t>::value, "");
public:
	static constexpr int SIZE = sizeof(T);
	T val;
	vector_t &store(void *ptr) { *((T *) ptr) = val; return *this; }
	vector_t (void *val) : val(*((T *)val)) {}
	vector_t (T val) : val(val) {}
	vector_t operator + (const vector_t &rhs) const { return { T(val + rhs.val) }; }
	vector_t operator - (const vector_t &rhs) const { return { T(val - rhs.val) }; }
	vector_t operator - () const { return { -val }; }
	friend vector_t min(const vector_t &lhs, const vector_t &rhs) { return { std::min(lhs.val, rhs.val) }; }
	friend vector_t max(const vector_t &lhs, const vector_t &rhs) { return { std::max(lhs.val, rhs.val) }; }
	vector_t &chmin_store(void *ptr) { if (*((T *) ptr) > val) store(ptr); return *this; }
	vector_t &chmax_store(void *ptr) { if (*((T *) ptr) < val) store(ptr); return *this; }
};



// SSE4.2 / int16_t
template<> class vector_t<InstSet::SSE4_2, int16_t> : public vector_base_t<InstSet::SSE4_2> {
public:
	using vector_base_t<InstSet::SSE4_2>::vector_base_t;
	vector_t (int16_t val) : vector_base_t(_mm_set1_epi16(val)) {}
	vector_t operator + (const vector_t &rhs) const { return { _mm_add_epi16(vec, rhs.vec) }; }
	vector_t operator - (const vector_t &rhs) const { return { _mm_sub_epi16(vec, rhs.vec) }; }
	vector_t operator - () const { return { _mm_sub_epi16(_mm_setzero_si128(), vec) }; }
	friend vector_t min(const vector_t &lhs, const vector_t &rhs) { return { _mm_min_epi16(lhs.vec, rhs.vec) }; }
	friend vector_t max(const vector_t &lhs, const vector_t &rhs) { return { _mm_max_epi16(lhs.vec, rhs.vec) }; }
	vector_t &chmin_store(void *ptr) { min(*this, vector_t(ptr)).store(ptr); return *this; }
	vector_t &chmax_store(void *ptr) { max(*this, vector_t(ptr)).store(ptr); return *this; }
};
// SSE4.2 / int32_t
template<> class vector_t<InstSet::SSE4_2, int32_t> : public vector_base_t<InstSet::SSE4_2> {
public:
	using vector_base_t<InstSet::SSE4_2>::vector_base_t;
	vector_t (int32_t val) : vector_base_t(_mm_set1_epi32(val)) {}
	vector_t operator + (const vector_t &rhs) const { return { _mm_add_epi32(vec, rhs.vec) }; }
	vector_t operator - (const vector_t &rhs) const { return { _mm_sub_epi32(vec, rhs.vec) }; }
	vector_t operator - () const { return { _mm_sub_epi32(_mm_setzero_si128(), vec) }; }
	friend vector_t min(const vector_t &lhs, const vector_t &rhs) { return { _mm_min_epi32(lhs.vec, rhs.vec) }; }
	friend vector_t max(const vector_t &lhs, const vector_t &rhs) { return { _mm_max_epi32(lhs.vec, rhs.vec) }; }
	vector_t &chmin_store(void *ptr) { min(*this, vector_t(ptr)).store(ptr); return *this; }
	vector_t &chmax_store(void *ptr) { max(*this, vector_t(ptr)).store(ptr); return *this; }
};
// SSE4.2 / int64_t
template<> class vector_t<InstSet::SSE4_2, int64_t> : public vector_base_t<InstSet::SSE4_2> {
public:
	using vector_base_t<InstSet::SSE4_2>::vector_base_t;
	vector_t (int64_t val) : vector_base_t(_mm_set1_epi64((__m64) val)) {}
	vector_t operator + (const vector_t &rhs) const { return { _mm_add_epi64(vec, rhs.vec) }; }
	vector_t operator - (const vector_t &rhs) const { return { _mm_sub_epi64(vec, rhs.vec) }; }
	vector_t operator - () const { return { _mm_sub_epi64(_mm_setzero_si128(), vec) }; }
	// SSE4 doesn't have _mm_min_epi64 / _mm_max_epi64
	friend vector_t min(const vector_t &lhs, const vector_t &rhs) { return {
		_mm_blendv_epi8(lhs.vec, rhs.vec, _mm_cmpgt_epi64(lhs.vec, rhs.vec))
	}; }
	friend vector_t max(const vector_t &lhs, const vector_t &rhs) { return {
		_mm_blendv_epi8(lhs.vec, rhs.vec, _mm_cmpgt_epi64(rhs.vec, lhs.vec))
	}; }
	vector_t &chmin_store(void *ptr) { min(*this, vector_t(ptr)).store(ptr); return *this; }
	vector_t &chmax_store(void *ptr) { max(*this, vector_t(ptr)).store(ptr); return *this; }
};



// AVX2 / int16_t
template<> class vector_t<InstSet::AVX2, int16_t> : public vector_base_t<InstSet::AVX2> {
public:
	using vector_base_t<InstSet::AVX2>::vector_base_t;
	vector_t (int16_t val) : vector_base_t(_mm256_set1_epi16(val)) {}
	vector_t operator + (const vector_t &rhs) const { return { _mm256_add_epi16(vec, rhs.vec) }; }
	vector_t operator - (const vector_t &rhs) const { return { _mm256_sub_epi16(vec, rhs.vec) }; }
	vector_t operator - () const { return { _mm256_sub_epi16(_mm256_setzero_si256(), vec) }; }
	friend vector_t min(const vector_t &lhs, const vector_t &rhs) { return { _mm256_min_epi16(lhs.vec, rhs.vec) }; }
	friend vector_t max(const vector_t &lhs, const vector_t &rhs) { return { _mm256_max_epi16(lhs.vec, rhs.vec) }; }
	vector_t &chmin_store(void *ptr) { min(*this, vector_t(ptr)).store(ptr); return *this; }
	vector_t &chmax_store(void *ptr) { max(*this, vector_t(ptr)).store(ptr); return *this; }
};
// AVX2 / int32_t
template<> class vector_t<InstSet::AVX2, int32_t> : public vector_base_t<InstSet::AVX2> {
public:
	using vector_base_t<InstSet::AVX2>::vector_base_t;
	vector_t (int32_t val) : vector_base_t(_mm256_set1_epi32(val)) {}
	vector_t operator + (const vector_t &rhs) const { return { _mm256_add_epi32(vec, rhs.vec) }; }
	vector_t operator - (const vector_t &rhs) const { return { _mm256_sub_epi32(vec, rhs.vec) }; }
	vector_t operator - () const { return { _mm256_sub_epi32(_mm256_setzero_si256(), vec) }; }
	friend vector_t min(const vector_t &lhs, const vector_t &rhs) { return { _mm256_min_epi32(lhs.vec, rhs.vec) }; }
	friend vector_t max(const vector_t &lhs, const vector_t &rhs) { return { _mm256_max_epi32(lhs.vec, rhs.vec) }; }
	vector_t &chmin_store(void *ptr) { min(*this, vector_t(ptr)).store(ptr); return *this; }
	vector_t &chmax_store(void *ptr) { max(*this, vector_t(ptr)).store(ptr); return *this; }
};
// AVX2 / int64_t
template<> class vector_t<InstSet::AVX2, int64_t> : public vector_base_t<InstSet::AVX2> {
public:
	using vector_base_t<InstSet::AVX2>::vector_base_t;
	vector_t (int64_t val) : vector_base_t(_mm256_set1_epi64x(val)) {}
	vector_t operator + (const vector_t &rhs) const { return { _mm256_add_epi64(vec, rhs.vec) }; }
	vector_t operator - (const vector_t &rhs) const { return { _mm256_sub_epi64(vec, rhs.vec) }; }
	vector_t operator - () const { return { _mm256_sub_epi64(_mm256_setzero_si256(), vec) }; }
	// avx2 doesn't have _mm256_min_epi64 / _mm256_max_epi64
	friend vector_t min(const vector_t &lhs, const vector_t &rhs) { return {
		_mm256_blendv_epi8(lhs.vec, rhs.vec, _mm256_cmpgt_epi64(lhs.vec, rhs.vec))
	}; }
	friend vector_t max(const vector_t &lhs, const vector_t &rhs) { return {
		_mm256_blendv_epi8(lhs.vec, rhs.vec, _mm256_cmpgt_epi64(rhs.vec, lhs.vec))
	}; }
	vector_t &chmin_store(void *ptr) { // slower because of separate load instruction in the 1st operand of cmpgt
		_mm256_maskstore_epi64((long long *) ptr, _mm256_cmpgt_epi64(vector_t(ptr).vec, vec), vec);
		return *this;
	}
	vector_t &chmax_store(void *ptr) { // faster because cmpgt allows memory address as the 2nd operand
		_mm256_maskstore_epi64((long long *) ptr, _mm256_cmpgt_epi64(vec, vector_t(ptr).vec), vec);
		return *this;
	}
};



// AVX512 / int16_t
template<> class vector_t<InstSet::AVX512, int16_t> : public vector_base_t<InstSet::AVX512> {
public:
	using vector_base_t<InstSet::AVX512>::vector_base_t;
	vector_t (int16_t val) : vector_base_t(_mm512_set1_epi16(val)) {}
	vector_t operator + (const vector_t &rhs) const { return { _mm512_add_epi16(vec, rhs.vec) }; }
	vector_t operator - (const vector_t &rhs) const { return { _mm512_sub_epi16(vec, rhs.vec) }; }
	vector_t operator - () const { return { _mm512_sub_epi16(_mm512_setzero_si512(), vec) }; }
	friend vector_t min(const vector_t &lhs, const vector_t &rhs) { return { _mm512_min_epi16(lhs.vec, rhs.vec) }; }
	friend vector_t max(const vector_t &lhs, const vector_t &rhs) { return { _mm512_max_epi16(lhs.vec, rhs.vec) }; }
	vector_t &chmin_store(void *ptr) {
		_mm512_mask_storeu_epi16((internal_vector_t *) (ptr),
			_mm512_cmp_epi16_mask(vec, _mm512_load_si512((internal_vector_t *) ptr), _MM_CMPINT_LT), vec);
		return *this;
	}
	vector_t &chmax_store(void *ptr) {
		_mm512_mask_storeu_epi16((internal_vector_t *) (ptr),
			_mm512_cmp_epi16_mask(vec, _mm512_load_si512((internal_vector_t *) ptr), _MM_CMPINT_GT), vec);
		return *this;
	}
};
// AVX512 / int32_t
template<> class vector_t<InstSet::AVX512, int32_t> : public vector_base_t<InstSet::AVX512> {
public:
	using vector_base_t<InstSet::AVX512>::vector_base_t;
	vector_t (int32_t val) : vector_base_t(_mm512_set1_epi32(val)) {}
	vector_t operator + (const vector_t &rhs) const { return { _mm512_add_epi32(vec, rhs.vec) }; }
	vector_t operator - (const vector_t &rhs) const { return { _mm512_sub_epi32(vec, rhs.vec) }; }
	vector_t operator - () const { return { _mm512_sub_epi32(_mm512_setzero_si512(), vec) }; }
	friend vector_t min(const vector_t &lhs, const vector_t &rhs) { return { _mm512_min_epi32(lhs.vec, rhs.vec) }; }
	friend vector_t max(const vector_t &lhs, const vector_t &rhs) { return { _mm512_max_epi32(lhs.vec, rhs.vec) }; }
	vector_t &chmin_store(void *ptr) {
		_mm512_mask_store_epi32((internal_vector_t *) (ptr),
			_mm512_cmp_epi32_mask(vec, _mm512_load_si512((internal_vector_t *) ptr), _MM_CMPINT_LT), vec);
		return *this;
	}
	vector_t &chmax_store(void *ptr) {
		_mm512_mask_store_epi32((internal_vector_t *) (ptr),
			_mm512_cmp_epi32_mask(vec, _mm512_load_si512((internal_vector_t *) ptr), _MM_CMPINT_GT), vec);
		return *this;
	}
};
// AVX512 / int64_t
template<> class vector_t<InstSet::AVX512, int64_t> : public vector_base_t<InstSet::AVX512> {
public:
	using vector_base_t<InstSet::AVX512>::vector_base_t;
	vector_t (int64_t val) : vector_base_t(_mm512_set1_epi64(val)) {}
	vector_t operator + (const vector_t &rhs) const { return { _mm512_add_epi64(vec, rhs.vec) }; }
	vector_t operator - (const vector_t &rhs) const { return { _mm512_sub_epi64(vec, rhs.vec) }; }
	vector_t operator - () const { return { _mm512_sub_epi64(_mm512_setzero_si512(), vec) }; }
	friend vector_t min(const vector_t &lhs, const vector_t &rhs) { return { _mm512_min_epi64(lhs.vec, rhs.vec) }; }
	friend vector_t max(const vector_t &lhs, const vector_t &rhs) { return { _mm512_max_epi64(lhs.vec, rhs.vec) }; }
	vector_t &chmin_store(void *ptr) {
		_mm512_mask_store_epi64((internal_vector_t *) (ptr),
			_mm512_cmp_epi64_mask(vec, _mm512_load_si512((internal_vector_t *) ptr), _MM_CMPINT_LT), vec);
		return *this;
	}
	vector_t &chmax_store(void *ptr) {
		_mm512_mask_store_epi64((internal_vector_t *) (ptr),
			_mm512_cmp_epi64_mask(vec, _mm512_load_si512((internal_vector_t *) ptr), _MM_CMPINT_GT), vec);
		return *this;
	}
};


template<InstSet inst_set, typename T> vector_t<inst_set, T> &operator += (
	vector_t<inst_set, T> &lhs, const vector_t<inst_set, T> &rhs) {
	lhs = lhs + rhs;
	return lhs;
}
template<InstSet inst_set, typename T> vector_t<inst_set, T> &operator -= (
	vector_t<inst_set, T> &lhs, const vector_t<inst_set, T> &rhs) {
	lhs = lhs - rhs;
	return lhs;
}

} // namespace vectorize
} // namespace quick_floyd_warshall


namespace quick_floyd_warshall {

template <class T, class = void> struct is_complete : std::false_type {};
template <class T> struct is_complete<T, decltype(void(sizeof(T)))> : std::true_type {};

template<typename T> struct floyd_warshall_naive {
	using value_t = T;
	static constexpr T INF = std::numeric_limits<T>::max() / 2;
	static std::string get_description() { return "naive<int" + std::to_string(sizeof(value_t) * 8) + "_t>"; }
	static void run(int n, const T *input_matrix, T *output_matrix, bool symmetric = false) {
		(void) symmetric;
		T *buf = (T *) malloc(n * n * sizeof(T));
		memcpy(buf, input_matrix, n * n * sizeof(T));
		for (int k = 0; k < n; k++) for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) 
			buf[i * n + j] = std::min<T>(buf[i * n + j], buf[i * n + k] + buf[k * n + j]);
		memcpy(output_matrix, buf, n * n * sizeof(T));
		free(buf);
	}
};

using InstSet = vectorize::InstSet;

template<InstSet inst_set, typename T, int unroll_type> struct floyd_warshall {
public:
	static constexpr T INF = std::numeric_limits<T>::max() / 2;
	using value_t = T;
	
	static std::string get_description() {
		return "opt<" + vectorize::inst_set_to_str(inst_set) + ", " "int" + std::to_string(sizeof(value_t) * 8) + "_t, "
			+ std::to_string(unroll_type) + ">"; 
	}
private:
	static constexpr int B = 64; // block size
	using vector_t = vectorize::vector_t<inst_set, T>;
	
	static_assert(is_complete<vector_t>::value, "Invalid inst_set or T");
	static_assert(B % (vector_t::SIZE / sizeof(T)) == 0, "Invalid B value");
	static_assert(unroll_type >= 0 && unroll_type <= 3, "Invalid unroll_type value");
	
	/*
		MaxPlusMul?(a, b, c) :
		 - [a, a + B * B), [b, b + B * B), [c, c + B * B) must not overlap
		 - equivalent to:
			for all i, j in [0, B):
				a[i * B + j] = max(a[i * B + j], max{b[i * B + k] + c[k * B + j] | k in [0, B)})
	*/
	static void MaxPlusMul0(T *a, T *b, T *c) {
		constexpr int n = B;
		for (int k = 0; k < n; k += 2) for (int i = 0; i < n; i += 2) {
			vector_t coef00(b[(i + 0) * n + (k + 0)]);
			vector_t coef01(b[(i + 0) * n + (k + 1)]);
			vector_t coef10(b[(i + 1) * n + (k + 0)]);
			vector_t coef11(b[(i + 1) * n + (k + 1)]);
			
			T *aa = a + i * n;
			T *bb = c + k * n;
			for (int j = 0; j < n; j += vector_t::SIZE / sizeof(T)) {
				vector_t t0(bb + j);
				vector_t t1(bb + n + j);
				max(t0 + coef00, t1 + coef01).chmax_store(aa + j);
				max(t0 + coef10, t1 + coef11).chmax_store(aa + n + j);
			}
		}
	}
	static void MaxPlusMul1(T *a, T *b, T *c) {
		constexpr int n = B;
		for (int k = 0; k < n; k += 4) for (int i = 0; i < n; i += 2) {
			vector_t coef00(b[(i + 0) * n + (k + 0)]);
			vector_t coef01(b[(i + 0) * n + (k + 1)]);
			vector_t coef02(b[(i + 0) * n + (k + 2)]);
			vector_t coef03(b[(i + 0) * n + (k + 3)]);
			vector_t coef10(b[(i + 1) * n + (k + 0)]);
			vector_t coef11(b[(i + 1) * n + (k + 1)]);
			vector_t coef12(b[(i + 1) * n + (k + 2)]);
			vector_t coef13(b[(i + 1) * n + (k + 3)]);
			
			T *aa = a + i * n;
			T *bb = c + k * n;
			for (int j = 0; j < n; j += vector_t::SIZE / sizeof(T)) {
				vector_t t0(bb + j);
				vector_t t1(bb + n + j);
				vector_t t2(bb + n + n + j);
				vector_t t3(bb + n + n + n + j);
				max(max(t0 + coef00, t1 + coef01), max(t2 + coef02, t3 + coef03)).chmax_store(aa + j);
				max(max(t0 + coef10, t1 + coef11), max(t2 + coef12, t3 + coef13)).chmax_store(aa + n + j);
			}
		}
	}
	static void MaxPlusMul2(T *a, T *b, T *c) {
		constexpr int n = B;
		for (int k = 0; k < n; k += 2) for (int i = 0; i < n; i += 4) {
			vector_t coef00(b[(i + 0) * n + (k + 0)]);
			vector_t coef01(b[(i + 0) * n + (k + 1)]);
			vector_t coef10(b[(i + 1) * n + (k + 0)]);
			vector_t coef11(b[(i + 1) * n + (k + 1)]);
			vector_t coef20(b[(i + 2) * n + (k + 0)]);
			vector_t coef21(b[(i + 2) * n + (k + 1)]);
			vector_t coef30(b[(i + 3) * n + (k + 0)]);
			vector_t coef31(b[(i + 3) * n + (k + 1)]);
			
			T *aa = a + i * n;
			T *bb = c + k * n;
			for (int j = 0; j < n; j += vector_t::SIZE / sizeof(T)) {
				vector_t t0(bb + j);
				vector_t t1(bb + n + j);
				max(t0 + coef00, t1 + coef01).chmax_store(aa + j);
				max(t0 + coef10, t1 + coef11).chmax_store(aa + n + j);
				max(t0 + coef20, t1 + coef21).chmax_store(aa + n + n + j);
				max(t0 + coef30, t1 + coef31).chmax_store(aa + n + n + n + j);
			}
		}
	}
	static void MaxPlusMul3(T *a, T *b, T *c) {
		constexpr int n = B;
		for (int k = 0; k < n; k += 4) for (int i = 0; i < n; i += 4) {
			vector_t coef00(b[(i + 0) * n + (k + 0)]);
			vector_t coef01(b[(i + 0) * n + (k + 1)]);
			vector_t coef02(b[(i + 0) * n + (k + 2)]);
			vector_t coef03(b[(i + 0) * n + (k + 3)]);
			vector_t coef10(b[(i + 1) * n + (k + 0)]);
			vector_t coef11(b[(i + 1) * n + (k + 1)]);
			vector_t coef12(b[(i + 1) * n + (k + 2)]);
			vector_t coef13(b[(i + 1) * n + (k + 3)]);
			vector_t coef20(b[(i + 2) * n + (k + 0)]);
			vector_t coef21(b[(i + 2) * n + (k + 1)]);
			vector_t coef22(b[(i + 2) * n + (k + 2)]);
			vector_t coef23(b[(i + 2) * n + (k + 3)]);
			vector_t coef30(b[(i + 3) * n + (k + 0)]);
			vector_t coef31(b[(i + 3) * n + (k + 1)]);
			vector_t coef32(b[(i + 3) * n + (k + 2)]);
			vector_t coef33(b[(i + 3) * n + (k + 3)]);
			
			T *aa = a + i * n;
			T *bb = c + k * n;
			for (int j = 0; j < n; j += vector_t::SIZE / sizeof(T)) {
				vector_t t0(bb + j);
				vector_t t1(bb + n + j);
				vector_t t2(bb + n + n + j);
				vector_t t3(bb + n + n + n + j);
				max(max(t0 + coef00, t1 + coef01), max(t2 + coef02, t3 + coef03)).chmax_store(aa + j);
				max(max(t0 + coef10, t1 + coef11), max(t2 + coef12, t3 + coef13)).chmax_store(aa + n + j);
				max(max(t0 + coef20, t1 + coef21), max(t2 + coef22, t3 + coef23)).chmax_store(aa + n + n + j);
				max(max(t0 + coef30, t1 + coef31), max(t2 + coef32, t3 + coef33)).chmax_store(aa + n + n + n + j);
			}
		}
	}
	static void FWI(T *a, T *b, T *c) {
		if (a != b && a != c && b != c) {
			if (unroll_type == 0) MaxPlusMul0(a, b, c);
			if (unroll_type == 1) MaxPlusMul1(a, b, c);
			if (unroll_type == 2) MaxPlusMul2(a, b, c);
			if (unroll_type == 3) MaxPlusMul3(a, b, c);
			return;
		}
		constexpr int n = B;
		for (int k = 0; k < n; k++) for (int i = 0; i < n; i++) {
			vector_t coef(b[i * n + k]);
			
			T *aa = a + i * n;
			T *bb = c + k * n;
			for (int j = 0; j < n; j += vector_t::SIZE / sizeof(T))
				(vector_t(bb + j) + coef).chmax_store(aa + j);
		}
	}
	static void FWR(int n_blocks_power2, int n_blocks, int block_index0, int block_index1, int block_index2,
		T **block_start, bool symmetric) {
		
		if (block_index0 >= n_blocks || block_index1 >= n_blocks || block_index2 >= n_blocks) return;
		if (n_blocks_power2 == 1) {
			FWI(
				block_start[block_index0 * n_blocks + block_index2],
				block_start[block_index0 * n_blocks + block_index1],
				block_start[block_index1 * n_blocks + block_index2]
			);
		} else {
			int half = n_blocks_power2 >> 1;
			if (!symmetric) {
				FWR(half, n_blocks, block_index0       , block_index1       , block_index2       , block_start, false);
				FWR(half, n_blocks, block_index0       , block_index1       , block_index2 + half, block_start, false);
				FWR(half, n_blocks, block_index0 + half, block_index1       , block_index2       , block_start, false);
				FWR(half, n_blocks, block_index0 + half, block_index1       , block_index2 + half, block_start, false);
				FWR(half, n_blocks, block_index0 + half, block_index1 + half, block_index2 + half, block_start, false);
				FWR(half, n_blocks, block_index0 + half, block_index1 + half, block_index2       , block_start, false);
				FWR(half, n_blocks, block_index0       , block_index1 + half, block_index2 + half, block_start, false);
				FWR(half, n_blocks, block_index0       , block_index1 + half, block_index2       , block_start, false);
			} else {
				// if symmetric, block_index0 = block_index1 = block_index2
				FWR(half, n_blocks, block_index0       , block_index1       , block_index2       , block_start, true);
				FWR(half, n_blocks, block_index0       , block_index1       , block_index2 + half, block_start, false);
				transpose_copy(half, n_blocks, block_index0, block_index0 + half, block_start);
				FWR(half, n_blocks, block_index0 + half, block_index1       , block_index2 + half, block_start, false);
				FWR(half, n_blocks, block_index0 + half, block_index1 + half, block_index2 + half, block_start, true);
				FWR(half, n_blocks, block_index0 + half, block_index1 + half, block_index2       , block_start, false);
				transpose_copy(half, n_blocks, block_index0 + half, block_index0, block_start);
				FWR(half, n_blocks, block_index0       , block_index1 + half, block_index2       , block_start, false);
			}
		}
	}
	// copy [block_row_offset:block_row_offset+n)[block_column_offset:block_column_offset+n) to its transposed posititon
	// anything outside n_blocks * n_blocks blocks is ignored
	static void transpose_copy(int n, int n_blocks, int block_row_offset, int block_column_offset, T **block_start) {
		for (int i = block_row_offset; i < block_row_offset + n && i < n_blocks; i++) 
			for (int j = block_column_offset; j < block_column_offset + n && j < n_blocks; j++) {
			
			T *src = block_start[i * n_blocks + j];
			T *dst = block_start[j * n_blocks + i];
			for (int y = 0; y < B; y++) for (int x = 0; x < B; x++) dst[x * B + y] = src[y * B + x];
		}
	}
	/*
		rev == false :
			Copy the n * n elements in src to dst in the order like this(each src[i][j] is a BxB block):
			dst: src[0][0], src[0][1], src[1][0], src[1][1],
				 src[0][2], src[0][3], src[1][2], src[1][3],
				 src[2][0], src[2][1], src[3][0], src[3][1],
				 src[2][2], src[2][3], src[3][2], src[3][3],
				 src[0][4], src[0][5], src[1][4], src[1][5], ...
			and returns the pointer to the next element of the last element written in dst.
			Elements outside the n_blocks * n_blocks blocks will be ignored
			Elements in dst corresponding to elements outside the src_n * src_n but in n_blocks * n_blocks
				will be filled
			block_start[i * n_blocks + j] will point to the starting element in dst corresponding to (i, j) block
		
		rev == true :
			same as rev == false except that the copy direction is reversed and
				elements in dst where INF would be contained if !rev are untouched
		
		This function negates all the element and FWR handles everything with max instead of min.
		This is because chmax(mem, reg) can be implemented faster than chmin(mem, reg) with avx2+int64_t
		The cost of negation should be negligible for other combinations, where this trick is irrelevant
	*/
	static T *reorder(int src_n, int n_blocks_power2, T *dst_head, T *src, T **block_start,
		int block_row, int block_column, bool rev) {
		
		int n_blocks = (src_n + B - 1) / B;
		if (block_row >= n_blocks || block_column >= n_blocks) return dst_head;
		if (n_blocks_power2 == 1) {
			T *src_base = src + (block_row * B * src_n + block_column * B);
			for (int i = 0; i < B; i++) {
				if (block_row * B + i < src_n) {
					int length = std::min(B, src_n - block_column * B);
					if (!rev) {
						for (int j = 0; j < length; j++) dst_head[i * B + j] = -src_base[i * src_n + j];
						for (int j = length; j < B; j++) dst_head[i * B + j] = -INF;
					} else {
						for (int j = 0; j < length; j++) src_base[i * src_n + j] = -dst_head[i * B + j];
					}
				} else {
					if (!rev) std::fill(dst_head + i * B, dst_head + (i + 1) * B, -INF);
				}
			}
			block_start[block_row * n_blocks + block_column] = dst_head;
			return dst_head + B * B;
		} else {
			int n_blocks_p2_half = n_blocks_power2 >> 1;
			// split into 2x2 recursively
			for (int i = 0; i < 2; i++) for (int j = 0; j < 2; j++)
				dst_head = reorder(src_n, n_blocks_p2_half, dst_head, src, block_start,
					block_row + i * n_blocks_p2_half, block_column + j * n_blocks_p2_half, rev);
			return dst_head;
		}
	}
public:
	static void run(int src_n, const T *input_matrix, T *output_matrix, bool symmetric = false) {
		assert(0 <= src_n && src_n < 65536);
		if (src_n == 0) return;
		int n_blocks = (src_n + B - 1) / B; // number of BxB blocks in a row
		int n_blocks_power2 = 1; // smallest power of 2 >= src_n / B
		while (n_blocks_power2 * B < src_n) n_blocks_power2 *= 2;
		
		// allocate and align the needed buffers
		const size_t reordered_needed_size = (B * n_blocks) * (B * n_blocks) * sizeof(T);
		size_t reordered_buffer_size = reordered_needed_size + 64;
		void *reordered_org = malloc(reordered_buffer_size);
		assert(reordered_org);
		void *reordered = reordered_org;
		assert(std::align(64, reordered_needed_size, reordered, reordered_buffer_size));
		// block_start[i][j] : pointer to the starting element of the (i, j) block in t 
		T **block_start = (T **) malloc(n_blocks * n_blocks * sizeof(T *));
		std::fill(block_start, block_start + n_blocks * n_blocks, nullptr);
		
		reorder(src_n, n_blocks_power2, (T *) reordered, const_cast<T *>(input_matrix), block_start, 0, 0, false);
		FWR(n_blocks_power2, n_blocks, 0, 0, 0, block_start, symmetric);
		reorder(src_n, n_blocks_power2, (T *) reordered, output_matrix, block_start, 0, 0, true);
		
		free(reordered_org);
		free(block_start);
	}
};

} // namespace quick_floyd_warshall

template<class T=int64_t>struct WarshallFloyd{
	using qwf = quick_floyd_warshall::floyd_warshall<quick_floyd_warshall::InstSet::AVX2, T, 3>;
	const T INF=qwf::INF;

	int n;
	bool symmetric=true;
	vector<T> edge;
	WarshallFloyd(int n): n(n){
		edge.resize(n*n, qwf::INF);
	}
	void set_edge(int u, int v, T c, bool directed = false){
		edge[u*n+v] = c;
		if(directed) symmetric = false;
		else edge[v*n+u] = c;
	}
	vector<vector<T>> calc(){
		vector<vector<T>> ans(n, vector<T>(n));
		vector<T> tmp(n*n);
		qwf::run(n, edge.data(), tmp.data(), symmetric);
		rep(i,n){
			copy(begin(tmp)+i*n, begin(tmp)+(i+1)*n, begin(ans[i]));
		}
		return ans;
	}
};

int main() {
	/**/
	def(ll,n,m,l);
	WarshallFloyd wf(n);
	rep(m){
		def(ll,a,b,c);
		a--;b--;
		if(c>l)continue;
		wf.set_edge(a,b,c);
	}

	auto dist = wf.calc();

	rep(i,n)rep(j,n){
		if(dist[i][j]>l)wf.set_edge(i,j,wf.INF);
		else wf.set_edge(i,j,1);
	}

	auto ans = wf.calc();

	def(int,q);
	rep(q){
		def(ll,s,t);
		s--;t--;

		if(ans[s][t]==wf.INF)out(-1);
		else out(ans[s][t]-1);
	}
	
}