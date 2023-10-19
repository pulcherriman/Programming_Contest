#include <memory>
#include <string>
#include <utility>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <map>
#include <exception>
#include <functional>
#include <limits>
#include <iostream>
#include <sstream>
/*-----------------------------------------------------------------------------
| The Loki Library
| Copyright (c) 2001 by Andrei Alexandrescu
| This code accompanies the book:
| Alexandrescu, Andrei. "Modern C++ Design: Generic Programming and Design
|   Patterns Applied". Copyright (c) 2001. Addison-Wesley.
| Permission to use, copy, modify, distribute and sell this software for any
|   purpose is hereby granted without fee, provided that the above copyright
|   notice appear in all copies and that both that copyright notice and this
|   permission notice appear in supporting documentation.
| The author or Addison-Wesley Longman make no representations about the
|   suitability of this software for any purpose. It is provided "as is"
|   without express or implied warranty.
|------------------------------------------------------------------------------
| Updated 2019 by Matthieu Dartiailh for C++11 compliancy
|----------------------------------------------------------------------------*/
namespace Loki {
namespace Private {
template <class Value, class C, class K>
class AssocVectorCompare : public C {
  typedef std::pair<K, Value> Data;
  typedef K first_argument_type;
 public:
  AssocVectorCompare() {}
  AssocVectorCompare(const C &src) : C(src) {}
  bool operator()(const first_argument_type &lhs,
                  const first_argument_type &rhs) const {
    return C::operator()(lhs, rhs);
  }
  bool operator()(const Data &lhs, const Data &rhs) const {
    return operator()(lhs.first, rhs.first);
  }
  bool operator()(const Data &lhs, const first_argument_type &rhs) const {
    return operator()(lhs.first, rhs);
  }
  bool operator()(const first_argument_type &lhs, const Data &rhs) const {
    return operator()(lhs, rhs.first);
  }
};
}  // namespace Private
template <class K, class V, class C = std::less<K>,
          class A = std::allocator<std::pair<K, V>>>
class AssocVector : private std::vector<std::pair<K, V>, A>,
                    private Private::AssocVectorCompare<V, C, K> {
  typedef std::vector<std::pair<K, V>, A> Base;
  typedef Private::AssocVectorCompare<V, C, K> MyCompare;
 public:
  typedef K key_type;
  typedef V mapped_type;
  typedef typename Base::value_type value_type;
  typedef C key_compare;
  typedef A allocator_type;
  typedef typename Base::iterator iterator;
  typedef typename Base::const_iterator const_iterator;
  typedef typename Base::size_type size_type;
  typedef typename Base::difference_type difference_type;
  typedef typename Base::reverse_iterator reverse_iterator;
  typedef typename Base::const_reverse_iterator const_reverse_iterator;
  class value_compare : public std::function<bool(value_type, value_type)>,
                        private key_compare {
    friend class AssocVector;
   protected:
    value_compare(key_compare pred) : key_compare(pred) {}
   public:
    bool operator()(const value_type &lhs, const value_type &rhs) const {
      return key_compare::operator()(lhs.first, rhs.first);
    }
  };
  explicit AssocVector(const key_compare &comp = key_compare(),
                       const A &alloc = A())
      : Base(alloc), MyCompare(comp) {}
  template <class InputIterator>
  AssocVector(InputIterator first, InputIterator last,
              const key_compare &comp = key_compare(), const A &alloc = A())
      : Base(first, last, alloc), MyCompare(comp) {
    MyCompare &me = *this;
    std::sort(begin(), end(), me);
  }
  AssocVector &operator=(const AssocVector &rhs) {
    AssocVector(rhs).swap(*this);
    return *this;
  }
  iterator begin() { return Base::begin(); }
  const_iterator begin() const { return Base::begin(); }
  iterator end() { return Base::end(); }
  const_iterator end() const { return Base::end(); }
  reverse_iterator rbegin() { return Base::rbegin(); }
  const_reverse_iterator rbegin() const { return Base::rbegin(); }
  reverse_iterator rend() { return Base::rend(); }
  const_reverse_iterator rend() const { return Base::rend(); }
  bool empty() const { return Base::empty(); }
  size_type size() const { return Base::size(); }
  size_type max_size() { return Base::max_size(); }
  mapped_type &operator[](const key_type &key) {
    return insert(value_type(key, mapped_type())).first->second;
  }
  std::pair<iterator, bool> insert(const value_type &val) {
    bool found(true);
    iterator i(lower_bound(val.first));
    if (i == end() || this->operator()(val.first, i->first)) {
      i = Base::insert(i, val);
      found = false;
    }
    return std::make_pair(i, !found);
  }
  iterator insert(iterator pos, const value_type &val) {
    if ((pos == begin() || this->operator()(*(pos - 1), val)) &&
        (pos == end() || this->operator()(val, *pos))) {
      return Base::insert(pos, val);
    }
    return insert(val).first;
  }
  template <class InputIterator>
  void insert(InputIterator first, InputIterator last) {
    for (; first != last; ++first) insert(*first);
  }
  void erase(iterator pos) { Base::erase(pos); }
  size_type erase(const key_type &k) {
    iterator i(find(k));
    if (i == end()) return 0;
    erase(i);
    return 1;
  }
  void erase(iterator first, iterator last) { Base::erase(first, last); }
  void swap(AssocVector &other) {
    Base::swap(other);
    MyCompare &me = *this;
    MyCompare &rhs = other;
    std::swap(me, rhs);
  }
  void clear() { Base::clear(); }
  key_compare key_comp() const { return *this; }
  value_compare value_comp() const {
    const key_compare &comp = *this;
    return value_compare(comp);
  }
  iterator find(const key_type &k) {
    iterator i(lower_bound(k));
    if (i != end() && this->operator()(k, i->first)) {
      i = end();
    }
    return i;
  }
  const_iterator find(const key_type &k) const {
    const_iterator i(lower_bound(k));
    if (i != end() && this->operator()(k, i->first)) {
      i = end();
    }
    return i;
  }
  size_type count(const key_type &k) const { return find(k) != end(); }
  iterator lower_bound(const key_type &k) {
    MyCompare &me = *this;
    return std::lower_bound(begin(), end(), k, me);
  }
  const_iterator lower_bound(const key_type &k) const {
    const MyCompare &me = *this;
    return std::lower_bound(begin(), end(), k, me);
  }
  iterator upper_bound(const key_type &k) {
    MyCompare &me = *this;
    return std::upper_bound(begin(), end(), k, me);
  }
  const_iterator upper_bound(const key_type &k) const {
    const MyCompare &me = *this;
    return std::upper_bound(begin(), end(), k, me);
  }
  std::pair<iterator, iterator> equal_range(const key_type &k) {
    MyCompare &me = *this;
    return std::equal_range(begin(), end(), k, me);
  }
  std::pair<const_iterator, const_iterator> equal_range(
      const key_type &k) const {
    const MyCompare &me = *this;
    return std::equal_range(begin(), end(), k, me);
  }
  template <class K1, class V1, class C1, class A1>
  friend bool operator==(const AssocVector<K1, V1, C1, A1> &lhs,
                         const AssocVector<K1, V1, C1, A1> &rhs);
  bool operator<(const AssocVector &rhs) const {
    const Base &me = *this;
    const Base &yo = rhs;
    return me < yo;
  }
  template <class K1, class V1, class C1, class A1>
  friend bool operator!=(const AssocVector<K1, V1, C1, A1> &lhs,
                         const AssocVector<K1, V1, C1, A1> &rhs);
  template <class K1, class V1, class C1, class A1>
  friend bool operator>(const AssocVector<K1, V1, C1, A1> &lhs,
                        const AssocVector<K1, V1, C1, A1> &rhs);
  template <class K1, class V1, class C1, class A1>
  friend bool operator>=(const AssocVector<K1, V1, C1, A1> &lhs,
                         const AssocVector<K1, V1, C1, A1> &rhs);
  template <class K1, class V1, class C1, class A1>
  friend bool operator<=(const AssocVector<K1, V1, C1, A1> &lhs,
                         const AssocVector<K1, V1, C1, A1> &rhs);
};
template <class K, class V, class C, class A>
inline bool operator==(const AssocVector<K, V, C, A> &lhs,
                       const AssocVector<K, V, C, A> &rhs) {
  const std::vector<std::pair<K, V>, A> &me = lhs;
  return me == rhs;
}
template <class K, class V, class C, class A>
inline bool operator!=(const AssocVector<K, V, C, A> &lhs,
                       const AssocVector<K, V, C, A> &rhs) {
  return !(lhs == rhs);
}
template <class K, class V, class C, class A>
inline bool operator>(const AssocVector<K, V, C, A> &lhs,
                      const AssocVector<K, V, C, A> &rhs) {
  return rhs < lhs;
}
template <class K, class V, class C, class A>
inline bool operator>=(const AssocVector<K, V, C, A> &lhs,
                       const AssocVector<K, V, C, A> &rhs) {
  return !(lhs < rhs);
}
template <class K, class V, class C, class A>
inline bool operator<=(const AssocVector<K, V, C, A> &lhs,
                       const AssocVector<K, V, C, A> &rhs) {
  return !(rhs < lhs);
}
template <class K, class V, class C, class A>
void swap(AssocVector<K, V, C, A> &lhs, AssocVector<K, V, C, A> &rhs) {
  lhs.swap(rhs);
}
}  // namespace Loki

/*-----------------------------------------------------------------------------
| Copyright (c) 2013-2017, Nucleic Development Team.
|
| Distributed under the terms of the Modified BSD License.
|
| The full license is in the file LICENSE, distributed with this software.
|----------------------------------------------------------------------------*/
namespace kiwi {
class SharedData {
 public:
  SharedData() : m_refcount(0) {}
  SharedData(const SharedData &other) = delete;
  SharedData(SharedData &&other) = delete;
  int m_refcount;
  SharedData &operator=(const SharedData &other) = delete;
  SharedData &operator=(SharedData &&other) = delete;
};
template <typename T>
class SharedDataPtr {
 public:
  using Type = T;
  SharedDataPtr() : m_data(nullptr) {}
  explicit SharedDataPtr(T *data) : m_data(data) { incref(m_data); }
  ~SharedDataPtr() { decref(m_data); }
  T *data() { return m_data; }
  const T *data() const { return m_data; }
  operator T *() { return m_data; }
  operator const T *() const { return m_data; }
  T *operator->() { return m_data; }
  const T *operator->() const { return m_data; }
  T &operator*() { return *m_data; }
  const T &operator*() const { return *m_data; }
  bool operator!() const { return !m_data; }
  bool operator<(const SharedDataPtr<T> &other) const {
    return m_data < other.m_data;
  }
  bool operator==(const SharedDataPtr<T> &other) const {
    return m_data == other.m_data;
  }
  bool operator!=(const SharedDataPtr<T> &other) const {
    return m_data != other.m_data;
  }
  SharedDataPtr(const SharedDataPtr<T> &other) : m_data(other.m_data) {
    incref(m_data);
  }
  SharedDataPtr(SharedDataPtr &&other) noexcept : m_data(other.m_data) {
    other.m_data = nullptr;
  }
  SharedDataPtr<T> &operator=(const SharedDataPtr<T> &other) {
    if (m_data != other.m_data) {
      T *temp = m_data;
      m_data = other.m_data;
      incref(m_data);
      decref(temp);
    }
    return *this;
  }
  SharedDataPtr<T> &operator=(SharedDataPtr<T> &&other) noexcept {
    if (m_data != other.m_data) {
      T *temp = m_data;
      m_data = other.m_data;
      other.m_data = nullptr;
      decref(temp);
    }
    return *this;
  }
  SharedDataPtr<T> &operator=(T *other) {
    if (m_data != other) {
      T *temp = m_data;
      m_data = other;
      incref(m_data);
      decref(temp);
    }
    return *this;
  }
 private:
  static void incref(T *data) {
    if (data) ++data->m_refcount;
  }
  static void decref(T *data) {
    if (data && --data->m_refcount == 0) delete data;
  }
  T *m_data;
};
}  // namespace kiwi
namespace kiwi {
class Variable {
 public:
  class Context {
   public:
    Context() = default;
    virtual ~Context() {}
  };
  Variable(Context *context = 0) : m_data(new VariableData("", context)) {}
  Variable(std::string name, Context *context = 0)
      : m_data(new VariableData(std::move(name), context)) {}
  Variable(const char *name, Context *context = 0)
      : m_data(new VariableData(name, context)) {}
  Variable(const Variable &) = default;
  Variable(Variable &&) noexcept = default;
  ~Variable() = default;
  const std::string &name() const { return m_data->m_name; }
  void setName(const char *name) { m_data->m_name = name; }
  void setName(const std::string &name) { m_data->m_name = name; }
  Context *context() const { return m_data->m_context.get(); }
  void setContext(Context *context) { m_data->m_context.reset(context); }
  double value() const { return m_data->m_value; }
  void setValue(double value) { m_data->m_value = value; }
  bool equals(const Variable &other) { return m_data == other.m_data; }
  Variable &operator=(const Variable &) = default;
  Variable &operator=(Variable &&) noexcept = default;
 private:
  class VariableData : public SharedData {
   public:
    VariableData(std::string name, Context *context)
        : SharedData(),
          m_name(std::move(name)),
          m_context(context),
          m_value(0.0) {}
    VariableData(const char *name, Context *context)
        : SharedData(), m_name(name), m_context(context), m_value(0.0) {}
    ~VariableData() = default;
    std::string m_name;
    std::unique_ptr<Context> m_context;
    double m_value;
   private:
    VariableData(const VariableData &other);
    VariableData &operator=(const VariableData &other);
  };
  SharedDataPtr<VariableData> m_data;
  friend bool operator<(const Variable &lhs, const Variable &rhs) {
    return lhs.m_data < rhs.m_data;
  }
};
}  // namespace kiwi
namespace kiwi {
class Term {
 public:
  Term(Variable variable, double coefficient = 1.0)
      : m_variable(std::move(variable)), m_coefficient(coefficient) {}
  Term(const std::pair<const Variable, double> &pair)
      : m_variable(pair.first), m_coefficient(pair.second) {}
  Term(const Term &) = default;
  Term(Term &&) noexcept = default;
  ~Term() = default;
  const Variable &variable() const { return m_variable; }
  double coefficient() const { return m_coefficient; }
  double value() const { return m_coefficient * m_variable.value(); }
  Term &operator=(const Term &) = default;
  Term &operator=(Term &&) noexcept = default;
 private:
  Variable m_variable;
  double m_coefficient;
};
}  // namespace kiwi
namespace kiwi {
class Expression {
 public:
  Expression(double constant = 0.0) : m_constant(constant) {}
  Expression(const Term &term, double constant = 0.0)
      : m_terms(1, term), m_constant(constant) {}
  Expression(std::vector<Term> terms, double constant = 0.0)
      : m_terms(std::move(terms)), m_constant(constant) {}
  Expression(const Expression &) = default;
  Expression(Expression &&) = default;
  ~Expression() = default;
  const std::vector<Term> &terms() const { return m_terms; }
  double constant() const { return m_constant; }
  double value() const {
    double result = m_constant;
    for (const Term &term : m_terms) result += term.value();
    return result;
  }
  Expression &operator=(const Expression &) = default;
  Expression &operator=(Expression &&) = default;
 private:
  std::vector<Term> m_terms;
  double m_constant;
};
}  // namespace kiwi
namespace kiwi {
namespace strength {
inline double create(double a, double b, double c, double w = 1.0) {
  double result = 0.0;
  result += std::max(0.0, std::min(1000.0, a * w)) * 1000000.0;
  result += std::max(0.0, std::min(1000.0, b * w)) * 1000.0;
  result += std::max(0.0, std::min(1000.0, c * w));
  return result;
}
const double required = create(1000.0, 1000.0, 1000.0);
const double strong = create(1.0, 0.0, 0.0);
const double medium = create(0.0, 1.0, 0.0);
const double weak = create(0.0, 0.0, 1.0);
inline double clip(double value) {
  return std::max(0.0, std::min(required, value));
}
}  // namespace strength
}  // namespace kiwi
namespace kiwi {
namespace impl {
inline bool nearZero(double value) {
  const double eps = 1.0e-8;
  return value < 0.0 ? -value < eps : value < eps;
}
}  // namespace impl
}  // namespace kiwi
namespace kiwi {
enum RelationalOperator { OP_LE, OP_GE, OP_EQ };
class Constraint {
 public:
  Constraint() = default;
  Constraint(const Expression &expr, RelationalOperator op,
             double strength = strength::required)
      : m_data(new ConstraintData(expr, op, strength)) {}
  Constraint(const Constraint &other, double strength)
      : m_data(new ConstraintData(other, strength)) {}
  Constraint(const Constraint &) = default;
  Constraint(Constraint &&) noexcept = default;
  ~Constraint() = default;
  const Expression &expression() const { return m_data->m_expression; }
  RelationalOperator op() const { return m_data->m_op; }
  double strength() const { return m_data->m_strength; }
  bool violated() const {
    switch (m_data->m_op) {
      case OP_EQ:
        return !impl::nearZero(m_data->m_expression.value());
      case OP_GE:
        return m_data->m_expression.value() < 0.0;
      case OP_LE:
        return m_data->m_expression.value() > 0.0;
    }
    std::abort();
  }
  bool operator!() const { return !m_data; }
  Constraint &operator=(const Constraint &) = default;
  Constraint &operator=(Constraint &&) noexcept = default;
 private:
  static Expression reduce(const Expression &expr) {
    std::map<Variable, double> vars;
    for (const auto &term : expr.terms())
      vars[term.variable()] += term.coefficient();
    std::vector<Term> terms(vars.begin(), vars.end());
    return Expression(std::move(terms), expr.constant());
  }
  class ConstraintData : public SharedData {
   public:
    ConstraintData(const Expression &expr, RelationalOperator op,
                   double strength)
        : SharedData(),
          m_expression(reduce(expr)),
          m_strength(strength::clip(strength)),
          m_op(op) {}
    ConstraintData(const Constraint &other, double strength)
        : SharedData(),
          m_expression(other.expression()),
          m_strength(strength::clip(strength)),
          m_op(other.op()) {}
    ~ConstraintData() = default;
    Expression m_expression;
    double m_strength;
    RelationalOperator m_op;
   private:
    ConstraintData(const ConstraintData &other);
    ConstraintData &operator=(const ConstraintData &other);
  };
  SharedDataPtr<ConstraintData> m_data;
  friend bool operator<(const Constraint &lhs, const Constraint &rhs) {
    return lhs.m_data < rhs.m_data;
  }
  friend bool operator==(const Constraint &lhs, const Constraint &rhs) {
    return lhs.m_data == rhs.m_data;
  }
  friend bool operator!=(const Constraint &lhs, const Constraint &rhs) {
    return lhs.m_data != rhs.m_data;
  }
};
}  // namespace kiwi
namespace kiwi {
class UnsatisfiableConstraint : public std::exception {
 public:
  UnsatisfiableConstraint(Constraint constraint)
      : m_constraint(std::move(constraint)) {}
  ~UnsatisfiableConstraint() noexcept {}
  const char *what() const noexcept {
    return "The constraint can not be satisfied.";
  }
  const Constraint &constraint() const { return m_constraint; }
 private:
  Constraint m_constraint;
};
class UnknownConstraint : public std::exception {
 public:
  UnknownConstraint(Constraint constraint)
      : m_constraint(std::move(constraint)) {}
  ~UnknownConstraint() noexcept {}
  const char *what() const noexcept {
    return "The constraint has not been added to the solver.";
  }
  const Constraint &constraint() const { return m_constraint; }
 private:
  Constraint m_constraint;
};
class DuplicateConstraint : public std::exception {
 public:
  DuplicateConstraint(Constraint constraint)
      : m_constraint(std::move(constraint)) {}
  ~DuplicateConstraint() noexcept {}
  const char *what() const noexcept {
    return "The constraint has already been added to the solver.";
  }
  const Constraint &constraint() const { return m_constraint; }
 private:
  Constraint m_constraint;
};
class UnknownEditVariable : public std::exception {
 public:
  UnknownEditVariable(Variable variable) : m_variable(std::move(variable)) {}
  ~UnknownEditVariable() noexcept {}
  const char *what() const noexcept {
    return "The edit variable has not been added to the solver.";
  }
  const Variable &variable() const { return m_variable; }
 private:
  Variable m_variable;
};
class DuplicateEditVariable : public std::exception {
 public:
  DuplicateEditVariable(Variable variable) : m_variable(std::move(variable)) {}
  ~DuplicateEditVariable() noexcept {}
  const char *what() const noexcept {
    return "The edit variable has already been added to the solver.";
  }
  const Variable &variable() const { return m_variable; }
 private:
  Variable m_variable;
};
class BadRequiredStrength : public std::exception {
 public:
  BadRequiredStrength() {}
  ~BadRequiredStrength() noexcept {}
  const char *what() const noexcept {
    return "A required strength cannot be used in this context.";
  }
};
class InternalSolverError : public std::exception {
 public:
  InternalSolverError() : m_msg("An internal solver error ocurred.") {}
  InternalSolverError(const char *msg) : m_msg(msg) {}
  InternalSolverError(std::string msg) : m_msg(std::move(msg)) {}
  ~InternalSolverError() noexcept {}
  const char *what() const noexcept { return m_msg.c_str(); }
 private:
  std::string m_msg;
};
}  // namespace kiwi
namespace kiwi {
namespace impl {
template <typename K, typename V, typename C = std::less<K>,
          typename A = std::allocator<std::pair<K, V>>>
using MapType = Loki::AssocVector<K, V, C, A>;
}
}  // namespace kiwi
namespace kiwi {
namespace impl {
class Symbol {
 public:
  using Id = unsigned long long;
  enum Type { Invalid, External, Slack, Error, Dummy };
  Symbol() : m_id(0), m_type(Invalid) {}
  Symbol(Type type, Id id) : m_id(id), m_type(type) {}
  ~Symbol() = default;
  Id id() const { return m_id; }
  Type type() const { return m_type; }
 private:
  Id m_id;
  Type m_type;
  friend bool operator<(const Symbol &lhs, const Symbol &rhs) {
    return lhs.m_id < rhs.m_id;
  }
  friend bool operator==(const Symbol &lhs, const Symbol &rhs) {
    return lhs.m_id == rhs.m_id;
  }
};
}  // namespace impl
}  // namespace kiwi
namespace kiwi {
namespace impl {
class Row {
 public:
  using CellMap = MapType<Symbol, double>;
  Row() : Row(0.0) {}
  Row(double constant) : m_constant(constant) {}
  Row(const Row &other) = default;
  ~Row() = default;
  const CellMap &cells() const { return m_cells; }
  double constant() const { return m_constant; }
  double add(double value) { return m_constant += value; }
  void insert(const Symbol &symbol, double coefficient = 1.0) {
    if (nearZero(m_cells[symbol] += coefficient)) m_cells.erase(symbol);
  }
  void insert(const Row &other, double coefficient = 1.0) {
    m_constant += other.m_constant * coefficient;
    for (const auto &cellPair : other.m_cells) {
      double coeff = cellPair.second * coefficient;
      if (nearZero(m_cells[cellPair.first] += coeff))
        m_cells.erase(cellPair.first);
    }
  }
  void remove(const Symbol &symbol) {
    auto it = m_cells.find(symbol);
    if (it != m_cells.end()) m_cells.erase(it);
  }
  void reverseSign() {
    m_constant = -m_constant;
    for (auto &cellPair : m_cells) cellPair.second = -cellPair.second;
  }
  void solveFor(const Symbol &symbol) {
    double coeff = -1.0 / m_cells[symbol];
    m_cells.erase(symbol);
    m_constant *= coeff;
    for (auto &cellPair : m_cells) cellPair.second *= coeff;
  }
  void solveFor(const Symbol &lhs, const Symbol &rhs) {
    insert(lhs, -1.0);
    solveFor(rhs);
  }
  double coefficientFor(const Symbol &symbol) const {
    CellMap::const_iterator it = m_cells.find(symbol);
    if (it == m_cells.end()) return 0.0;
    return it->second;
  }
  void substitute(const Symbol &symbol, const Row &row) {
    auto it = m_cells.find(symbol);
    if (it != m_cells.end()) {
      double coefficient = it->second;
      m_cells.erase(it);
      insert(row, coefficient);
    }
  }
 private:
  CellMap m_cells;
  double m_constant;
};
}  // namespace impl
}  // namespace kiwi
namespace kiwi {
namespace impl {
class SolverImpl {
  friend class DebugHelper;
  struct Tag {
    Symbol marker;
    Symbol other;
  };
  struct EditInfo {
    Tag tag;
    Constraint constraint;
    double constant;
  };
  using VarMap = MapType<Variable, Symbol>;
  using RowMap = MapType<Symbol, Row *>;
  using CnMap = MapType<Constraint, Tag>;
  using EditMap = MapType<Variable, EditInfo>;
  struct DualOptimizeGuard {
    DualOptimizeGuard(SolverImpl &impl) : m_impl(impl) {}
    ~DualOptimizeGuard() { m_impl.dualOptimize(); }
    SolverImpl &m_impl;
  };
 public:
  SolverImpl() : m_objective(new Row()), m_id_tick(1) {}
  SolverImpl(const SolverImpl &) = delete;
  SolverImpl(SolverImpl &&) = delete;
  ~SolverImpl() { clearRows(); }
  void addConstraint(const Constraint &constraint) {
    if (m_cns.find(constraint) != m_cns.end())
      throw DuplicateConstraint(constraint);
    Tag tag;
    std::unique_ptr<Row> rowptr(createRow(constraint, tag));
    Symbol subject(chooseSubject(*rowptr, tag));
    if (subject.type() == Symbol::Invalid && allDummies(*rowptr)) {
      if (!nearZero(rowptr->constant()))
        throw UnsatisfiableConstraint(constraint);
      else
        subject = tag.marker;
    }
    if (subject.type() == Symbol::Invalid) {
      if (!addWithArtificialVariable(*rowptr))
        throw UnsatisfiableConstraint(constraint);
    } else {
      rowptr->solveFor(subject);
      substitute(subject, *rowptr);
      m_rows[subject] = rowptr.release();
    }
    m_cns[constraint] = tag;
    optimize(*m_objective);
  }
  void removeConstraint(const Constraint &constraint) {
    auto cn_it = m_cns.find(constraint);
    if (cn_it == m_cns.end()) throw UnknownConstraint(constraint);
    Tag tag(cn_it->second);
    m_cns.erase(cn_it);
    removeConstraintEffects(constraint, tag);
    auto row_it = m_rows.find(tag.marker);
    if (row_it != m_rows.end()) {
      std::unique_ptr<Row> rowptr(row_it->second);
      m_rows.erase(row_it);
    } else {
      row_it = getMarkerLeavingRow(tag.marker);
      if (row_it == m_rows.end())
        throw InternalSolverError("failed to find leaving row");
      Symbol leaving(row_it->first);
      std::unique_ptr<Row> rowptr(row_it->second);
      m_rows.erase(row_it);
      rowptr->solveFor(leaving, tag.marker);
      substitute(tag.marker, *rowptr);
    }
    optimize(*m_objective);
  }
  bool hasConstraint(const Constraint &constraint) const {
    return m_cns.find(constraint) != m_cns.end();
  }
  void addEditVariable(const Variable &variable, double strength) {
    if (m_edits.find(variable) != m_edits.end())
      throw DuplicateEditVariable(variable);
    strength = strength::clip(strength);
    if (strength == strength::required) throw BadRequiredStrength();
    Constraint cn(Expression(variable), OP_EQ, strength);
    addConstraint(cn);
    EditInfo info;
    info.tag = m_cns[cn];
    info.constraint = cn;
    info.constant = 0.0;
    m_edits[variable] = info;
  }
  void removeEditVariable(const Variable &variable) {
    auto it = m_edits.find(variable);
    if (it == m_edits.end()) throw UnknownEditVariable(variable);
    removeConstraint(it->second.constraint);
    m_edits.erase(it);
  }
  bool hasEditVariable(const Variable &variable) const {
    return m_edits.find(variable) != m_edits.end();
  }
  void suggestValue(const Variable &variable, double value) {
    auto it = m_edits.find(variable);
    if (it == m_edits.end()) throw UnknownEditVariable(variable);
    DualOptimizeGuard guard(*this);
    EditInfo &info = it->second;
    double delta = value - info.constant;
    info.constant = value;
    auto row_it = m_rows.find(info.tag.marker);
    if (row_it != m_rows.end()) {
      if (row_it->second->add(-delta) < 0.0)
        m_infeasible_rows.push_back(row_it->first);
      return;
    }
    row_it = m_rows.find(info.tag.other);
    if (row_it != m_rows.end()) {
      if (row_it->second->add(delta) < 0.0)
        m_infeasible_rows.push_back(row_it->first);
      return;
    }
    for (const auto &rowPair : m_rows) {
      double coeff = rowPair.second->coefficientFor(info.tag.marker);
      if (coeff != 0.0 && rowPair.second->add(delta * coeff) < 0.0 &&
          rowPair.first.type() != Symbol::External)
        m_infeasible_rows.push_back(rowPair.first);
    }
  }
  void updateVariables() {
    auto row_end = m_rows.end();
    for (auto &varPair : m_vars) {
      Variable &var = varPair.first;
      auto row_it = m_rows.find(varPair.second);
      if (row_it == row_end)
        var.setValue(0.0);
      else
        var.setValue(row_it->second->constant());
    }
  }
  void reset() {
    clearRows();
    m_cns.clear();
    m_vars.clear();
    m_edits.clear();
    m_infeasible_rows.clear();
    m_objective.reset(new Row());
    m_artificial.reset();
    m_id_tick = 1;
  }
  SolverImpl &operator=(const SolverImpl &) = delete;
  SolverImpl &operator=(SolverImpl &&) = delete;
 private:
  struct RowDeleter {
    template <typename T>
    void operator()(T &pair) {
      delete pair.second;
    }
  };
  void clearRows() {
    std::for_each(m_rows.begin(), m_rows.end(), RowDeleter());
    m_rows.clear();
  }
  Symbol getVarSymbol(const Variable &variable) {
    auto it = m_vars.find(variable);
    if (it != m_vars.end()) return it->second;
    Symbol symbol(Symbol::External, m_id_tick++);
    m_vars[variable] = symbol;
    return symbol;
  }
  std::unique_ptr<Row> createRow(const Constraint &constraint, Tag &tag) {
    const Expression &expr(constraint.expression());
    std::unique_ptr<Row> row(new Row(expr.constant()));
    for (const auto &term : expr.terms()) {
      if (!nearZero(term.coefficient())) {
        Symbol symbol(getVarSymbol(term.variable()));
        auto row_it = m_rows.find(symbol);
        if (row_it != m_rows.end())
          row->insert(*row_it->second, term.coefficient());
        else
          row->insert(symbol, term.coefficient());
      }
    }
    switch (constraint.op()) {
      case OP_LE:
      case OP_GE: {
        double coeff = constraint.op() == OP_LE ? 1.0 : -1.0;
        Symbol slack(Symbol::Slack, m_id_tick++);
        tag.marker = slack;
        row->insert(slack, coeff);
        if (constraint.strength() < strength::required) {
          Symbol error(Symbol::Error, m_id_tick++);
          tag.other = error;
          row->insert(error, -coeff);
          m_objective->insert(error, constraint.strength());
        }
        break;
      }
      case OP_EQ: {
        if (constraint.strength() < strength::required) {
          Symbol errplus(Symbol::Error, m_id_tick++);
          Symbol errminus(Symbol::Error, m_id_tick++);
          tag.marker = errplus;
          tag.other = errminus;
          row->insert(errplus, -1.0);
          row->insert(errminus, 1.0);
          m_objective->insert(errplus, constraint.strength());
          m_objective->insert(errminus, constraint.strength());
        } else {
          Symbol dummy(Symbol::Dummy, m_id_tick++);
          tag.marker = dummy;
          row->insert(dummy);
        }
        break;
      }
    }
    if (row->constant() < 0.0) row->reverseSign();
    return row;
  }
  Symbol chooseSubject(const Row &row, const Tag &tag) const {
    for (const auto &cellPair : row.cells()) {
      if (cellPair.first.type() == Symbol::External) return cellPair.first;
    }
    if (tag.marker.type() == Symbol::Slack ||
        tag.marker.type() == Symbol::Error) {
      if (row.coefficientFor(tag.marker) < 0.0) return tag.marker;
    }
    if (tag.other.type() == Symbol::Slack ||
        tag.other.type() == Symbol::Error) {
      if (row.coefficientFor(tag.other) < 0.0) return tag.other;
    }
    return Symbol();
  }
  bool addWithArtificialVariable(const Row &row) {
    Symbol art(Symbol::Slack, m_id_tick++);
    m_rows[art] = new Row(row);
    m_artificial.reset(new Row(row));
    optimize(*m_artificial);
    bool success = nearZero(m_artificial->constant());
    m_artificial.reset();
    auto it = m_rows.find(art);
    if (it != m_rows.end()) {
      std::unique_ptr<Row> rowptr(it->second);
      m_rows.erase(it);
      if (rowptr->cells().empty()) return success;
      Symbol entering(anyPivotableSymbol(*rowptr));
      if (entering.type() == Symbol::Invalid) return false;
      rowptr->solveFor(art, entering);
      substitute(entering, *rowptr);
      m_rows[entering] = rowptr.release();
    }
    for (auto &rowPair : m_rows) rowPair.second->remove(art);
    m_objective->remove(art);
    return success;
  }
  void substitute(const Symbol &symbol, const Row &row) {
    for (auto &rowPair : m_rows) {
      rowPair.second->substitute(symbol, row);
      if (rowPair.first.type() != Symbol::External &&
          rowPair.second->constant() < 0.0)
        m_infeasible_rows.push_back(rowPair.first);
    }
    m_objective->substitute(symbol, row);
    if (m_artificial.get()) m_artificial->substitute(symbol, row);
  }
  void optimize(const Row &objective) {
    while (true) {
      Symbol entering(getEnteringSymbol(objective));
      if (entering.type() == Symbol::Invalid) return;
      auto it = getLeavingRow(entering);
      if (it == m_rows.end())
        throw InternalSolverError("The objective is unbounded.");
      Symbol leaving(it->first);
      Row *row = it->second;
      m_rows.erase(it);
      row->solveFor(leaving, entering);
      substitute(entering, *row);
      m_rows[entering] = row;
    }
  }
  void dualOptimize() {
    while (!m_infeasible_rows.empty()) {
      Symbol leaving(m_infeasible_rows.back());
      m_infeasible_rows.pop_back();
      auto it = m_rows.find(leaving);
      if (it != m_rows.end() && !nearZero(it->second->constant()) &&
          it->second->constant() < 0.0) {
        Symbol entering(getDualEnteringSymbol(*it->second));
        if (entering.type() == Symbol::Invalid)
          throw InternalSolverError("Dual optimize failed.");
        Row *row = it->second;
        m_rows.erase(it);
        row->solveFor(leaving, entering);
        substitute(entering, *row);
        m_rows[entering] = row;
      }
    }
  }
  Symbol getEnteringSymbol(const Row &objective) const {
    for (const auto &cellPair : objective.cells()) {
      if (cellPair.first.type() != Symbol::Dummy && cellPair.second < 0.0)
        return cellPair.first;
    }
    return Symbol();
  }
  Symbol getDualEnteringSymbol(const Row &row) const {
    Symbol entering;
    double ratio = std::numeric_limits<double>::max();
    for (const auto &cellPair : row.cells()) {
      if (cellPair.second > 0.0 && cellPair.first.type() != Symbol::Dummy) {
        double coeff = m_objective->coefficientFor(cellPair.first);
        double r = coeff / cellPair.second;
        if (r < ratio) {
          ratio = r;
          entering = cellPair.first;
        }
      }
    }
    return entering;
  }
  Symbol anyPivotableSymbol(const Row &row) const {
    for (const auto &cellPair : row.cells()) {
      const Symbol &sym(cellPair.first);
      if (sym.type() == Symbol::Slack || sym.type() == Symbol::Error)
        return sym;
    }
    return Symbol();
  }
  RowMap::iterator getLeavingRow(const Symbol &entering) {
    double ratio = std::numeric_limits<double>::max();
    auto end = m_rows.end();
    auto found = m_rows.end();
    for (auto it = m_rows.begin(); it != end; ++it) {
      if (it->first.type() != Symbol::External) {
        double temp = it->second->coefficientFor(entering);
        if (temp < 0.0) {
          double temp_ratio = -it->second->constant() / temp;
          if (temp_ratio < ratio) {
            ratio = temp_ratio;
            found = it;
          }
        }
      }
    }
    return found;
  }
  RowMap::iterator getMarkerLeavingRow(const Symbol &marker) {
    const double dmax = std::numeric_limits<double>::max();
    double r1 = dmax;
    double r2 = dmax;
    auto end = m_rows.end();
    auto first = end;
    auto second = end;
    auto third = end;
    for (auto it = m_rows.begin(); it != end; ++it) {
      double c = it->second->coefficientFor(marker);
      if (c == 0.0) continue;
      if (it->first.type() == Symbol::External) {
        third = it;
      } else if (c < 0.0) {
        double r = -it->second->constant() / c;
        if (r < r1) {
          r1 = r;
          first = it;
        }
      } else {
        double r = it->second->constant() / c;
        if (r < r2) {
          r2 = r;
          second = it;
        }
      }
    }
    if (first != end) return first;
    if (second != end) return second;
    return third;
  }
  void removeConstraintEffects(const Constraint &cn, const Tag &tag) {
    if (tag.marker.type() == Symbol::Error)
      removeMarkerEffects(tag.marker, cn.strength());
    if (tag.other.type() == Symbol::Error)
      removeMarkerEffects(tag.other, cn.strength());
  }
  void removeMarkerEffects(const Symbol &marker, double strength) {
    auto row_it = m_rows.find(marker);
    if (row_it != m_rows.end())
      m_objective->insert(*row_it->second, -strength);
    else
      m_objective->insert(marker, -strength);
  }
  bool allDummies(const Row &row) const {
    for (const auto &rowPair : row.cells()) {
      if (rowPair.first.type() != Symbol::Dummy) return false;
    }
    return true;
  }
  CnMap m_cns;
  RowMap m_rows;
  VarMap m_vars;
  EditMap m_edits;
  std::vector<Symbol> m_infeasible_rows;
  std::unique_ptr<Row> m_objective;
  std::unique_ptr<Row> m_artificial;
  Symbol::Id m_id_tick;
};
}  // namespace impl
}  // namespace kiwi
namespace kiwi {
namespace impl {
class DebugHelper {
 public:
  static void dump(const SolverImpl &solver, std::ostream &out) {
    out << "Objective" << std::endl;
    out << "---------" << std::endl;
    dump(*solver.m_objective, out);
    out << std::endl;
    out << "Tableau" << std::endl;
    out << "-------" << std::endl;
    dump(solver.m_rows, out);
    out << std::endl;
    out << "Infeasible" << std::endl;
    out << "----------" << std::endl;
    dump(solver.m_infeasible_rows, out);
    out << std::endl;
    out << "Variables" << std::endl;
    out << "---------" << std::endl;
    dump(solver.m_vars, out);
    out << std::endl;
    out << "Edit Variables" << std::endl;
    out << "--------------" << std::endl;
    dump(solver.m_edits, out);
    out << std::endl;
    out << "Constraints" << std::endl;
    out << "-----------" << std::endl;
    dump(solver.m_cns, out);
    out << std::endl;
    out << std::endl;
  }
  static void dump(const SolverImpl::RowMap &rows, std::ostream &out) {
    for (const auto &rowPair : rows) {
      dump(rowPair.first, out);
      out << " | ";
      dump(*rowPair.second, out);
    }
  }
  static void dump(const std::vector<Symbol> &symbols, std::ostream &out) {
    for (const auto &symbol : symbols) {
      dump(symbol, out);
      out << std::endl;
    }
  }
  static void dump(const SolverImpl::VarMap &vars, std::ostream &out) {
    for (const auto &varPair : vars) {
      out << varPair.first.name() << " = ";
      dump(varPair.second, out);
      out << std::endl;
    }
  }
  static void dump(const SolverImpl::CnMap &cns, std::ostream &out) {
    for (const auto &cnPair : cns) dump(cnPair.first, out);
  }
  static void dump(const SolverImpl::EditMap &edits, std::ostream &out) {
    for (const auto &editPair : edits)
      out << editPair.first.name() << std::endl;
  }
  static void dump(const Row &row, std::ostream &out) {
    for (const auto &rowPair : row.cells()) {
      out << " + " << rowPair.second << " * ";
      dump(rowPair.first, out);
    }
    out << std::endl;
  }
  static void dump(const Symbol &symbol, std::ostream &out) {
    switch (symbol.type()) {
      case Symbol::Invalid:
        out << "i";
        break;
      case Symbol::External:
        out << "v";
        break;
      case Symbol::Slack:
        out << "s";
        break;
      case Symbol::Error:
        out << "e";
        break;
      case Symbol::Dummy:
        out << "d";
        break;
      default:
        break;
    }
    out << symbol.id();
  }
  static void dump(const Constraint &cn, std::ostream &out) {
    for (const auto &term : cn.expression().terms()) {
      out << term.coefficient() << " * ";
      out << term.variable().name() << " + ";
    }
    out << cn.expression().constant();
    switch (cn.op()) {
      case OP_LE:
        out << " <= 0 ";
        break;
      case OP_GE:
        out << " >= 0 ";
        break;
      case OP_EQ:
        out << " == 0 ";
        break;
      default:
        break;
    }
    out << " | strength = " << cn.strength() << std::endl;
  }
};
}  // namespace impl
namespace debug {
template <typename T>
void dump(const T &value) {
  impl::DebugHelper::dump(value, std::cout);
}
template <typename T>
void dump(const T &value, std::ostream &out) {
  impl::DebugHelper::dump(value, out);
}
template <typename T>
std::string dumps(const T &value) {
  std::stringstream stream;
  impl::DebugHelper::dump(value, stream);
  return stream.str();
}
}  // namespace debug
}  // namespace kiwi
namespace kiwi {
class Solver {
 public:
  Solver() = default;
  ~Solver() = default;
  void addConstraint(const Constraint &constraint) {
    m_impl.addConstraint(constraint);
  }
  void removeConstraint(const Constraint &constraint) {
    m_impl.removeConstraint(constraint);
  }
  bool hasConstraint(const Constraint &constraint) const {
    return m_impl.hasConstraint(constraint);
  }
  void addEditVariable(const Variable &variable, double strength) {
    m_impl.addEditVariable(variable, strength);
  }
  void removeEditVariable(const Variable &variable) {
    m_impl.removeEditVariable(variable);
  }
  bool hasEditVariable(const Variable &variable) const {
    return m_impl.hasEditVariable(variable);
  }
  void suggestValue(const Variable &variable, double value) {
    m_impl.suggestValue(variable, value);
  }
  void updateVariables() { m_impl.updateVariables(); }
  void reset() { m_impl.reset(); }
  void dump() { debug::dump(m_impl); }
  void dump(std::ostream &out) { debug::dump(m_impl, out); }
  std::string dumps() { return debug::dumps(m_impl); }
 private:
  Solver(const Solver &);
  Solver &operator=(const Solver &);
  impl::SolverImpl m_impl;
};
}  // namespace kiwi
namespace kiwi {
inline Term operator*(const Variable &variable, double coefficient) {
  return Term(variable, coefficient);
}
inline Term operator/(const Variable &variable, double denominator) {
  return variable * (1.0 / denominator);
}
inline Term operator-(const Variable &variable) { return variable * -1.0; }
inline Term operator*(const Term &term, double coefficient) {
  return Term(term.variable(), term.coefficient() * coefficient);
}
inline Term operator/(const Term &term, double denominator) {
  return term * (1.0 / denominator);
}
inline Term operator-(const Term &term) { return term * -1.0; }
inline Expression operator*(const Expression &expression, double coefficient) {
  std::vector<Term> terms;
  terms.reserve(expression.terms().size());
  for (const Term &term : expression.terms())
    terms.push_back(term * coefficient);
  return Expression(std::move(terms), expression.constant() * coefficient);
}
inline Expression operator/(const Expression &expression, double denominator) {
  return expression * (1.0 / denominator);
}
inline Expression operator-(const Expression &expression) {
  return expression * -1.0;
}
inline Expression operator*(double coefficient, const Expression &expression) {
  return expression * coefficient;
}
inline Term operator*(double coefficient, const Term &term) {
  return term * coefficient;
}
inline Term operator*(double coefficient, const Variable &variable) {
  return variable * coefficient;
}
inline Expression operator+(const Expression &first, const Expression &second) {
  std::vector<Term> terms;
  terms.reserve(first.terms().size() + second.terms().size());
  terms.insert(terms.begin(), first.terms().begin(), first.terms().end());
  terms.insert(terms.end(), second.terms().begin(), second.terms().end());
  return Expression(std::move(terms), first.constant() + second.constant());
}
inline Expression operator+(const Expression &first, const Term &second) {
  std::vector<Term> terms;
  terms.reserve(first.terms().size() + 1);
  terms.insert(terms.begin(), first.terms().begin(), first.terms().end());
  terms.push_back(second);
  return Expression(std::move(terms), first.constant());
}
inline Expression operator+(const Expression &expression,
                            const Variable &variable) {
  return expression + Term(variable);
}
inline Expression operator+(const Expression &expression, double constant) {
  return Expression(expression.terms(), expression.constant() + constant);
}
inline Expression operator-(const Expression &first, const Expression &second) {
  return first + -second;
}
inline Expression operator-(const Expression &expression, const Term &term) {
  return expression + -term;
}
inline Expression operator-(const Expression &expression,
                            const Variable &variable) {
  return expression + -variable;
}
inline Expression operator-(const Expression &expression, double constant) {
  return expression + -constant;
}
inline Expression operator+(const Term &term, const Expression &expression) {
  return expression + term;
}
inline Expression operator+(const Term &first, const Term &second) {
  return Expression({first, second});
}
inline Expression operator+(const Term &term, const Variable &variable) {
  return term + Term(variable);
}
inline Expression operator+(const Term &term, double constant) {
  return Expression(term, constant);
}
inline Expression operator-(const Term &term, const Expression &expression) {
  return -expression + term;
}
inline Expression operator-(const Term &first, const Term &second) {
  return first + -second;
}
inline Expression operator-(const Term &term, const Variable &variable) {
  return term + -variable;
}
inline Expression operator-(const Term &term, double constant) {
  return term + -constant;
}
inline Expression operator+(const Variable &variable,
                            const Expression &expression) {
  return expression + variable;
}
inline Expression operator+(const Variable &variable, const Term &term) {
  return term + variable;
}
inline Expression operator+(const Variable &first, const Variable &second) {
  return Term(first) + second;
}
inline Expression operator+(const Variable &variable, double constant) {
  return Term(variable) + constant;
}
inline Expression operator-(const Variable &variable,
                            const Expression &expression) {
  return variable + -expression;
}
inline Expression operator-(const Variable &variable, const Term &term) {
  return variable + -term;
}
inline Expression operator-(const Variable &first, const Variable &second) {
  return first + -second;
}
inline Expression operator-(const Variable &variable, double constant) {
  return variable + -constant;
}
inline Expression operator+(double constant, const Expression &expression) {
  return expression + constant;
}
inline Expression operator+(double constant, const Term &term) {
  return term + constant;
}
inline Expression operator+(double constant, const Variable &variable) {
  return variable + constant;
}
inline Expression operator-(double constant, const Expression &expression) {
  return -expression + constant;
}
inline Expression operator-(double constant, const Term &term) {
  return -term + constant;
}
inline Expression operator-(double constant, const Variable &variable) {
  return -variable + constant;
}
inline Constraint operator==(const Expression &first,
                             const Expression &second) {
  return Constraint(first - second, OP_EQ);
}
inline Constraint operator==(const Expression &expression, const Term &term) {
  return expression == Expression(term);
}
inline Constraint operator==(const Expression &expression,
                             const Variable &variable) {
  return expression == Term(variable);
}
inline Constraint operator==(const Expression &expression, double constant) {
  return expression == Expression(constant);
}
inline Constraint operator<=(const Expression &first,
                             const Expression &second) {
  return Constraint(first - second, OP_LE);
}
inline Constraint operator<=(const Expression &expression, const Term &term) {
  return expression <= Expression(term);
}
inline Constraint operator<=(const Expression &expression,
                             const Variable &variable) {
  return expression <= Term(variable);
}
inline Constraint operator<=(const Expression &expression, double constant) {
  return expression <= Expression(constant);
}
inline Constraint operator>=(const Expression &first,
                             const Expression &second) {
  return Constraint(first - second, OP_GE);
}
inline Constraint operator>=(const Expression &expression, const Term &term) {
  return expression >= Expression(term);
}
inline Constraint operator>=(const Expression &expression,
                             const Variable &variable) {
  return expression >= Term(variable);
}
inline Constraint operator>=(const Expression &expression, double constant) {
  return expression >= Expression(constant);
}
inline Constraint operator==(const Term &term, const Expression &expression) {
  return expression == term;
}
inline Constraint operator==(const Term &first, const Term &second) {
  return Expression(first) == second;
}
inline Constraint operator==(const Term &term, const Variable &variable) {
  return Expression(term) == variable;
}
inline Constraint operator==(const Term &term, double constant) {
  return Expression(term) == constant;
}
inline Constraint operator<=(const Term &term, const Expression &expression) {
  return expression >= term;
}
inline Constraint operator<=(const Term &first, const Term &second) {
  return Expression(first) <= second;
}
inline Constraint operator<=(const Term &term, const Variable &variable) {
  return Expression(term) <= variable;
}
inline Constraint operator<=(const Term &term, double constant) {
  return Expression(term) <= constant;
}
inline Constraint operator>=(const Term &term, const Expression &expression) {
  return expression <= term;
}
inline Constraint operator>=(const Term &first, const Term &second) {
  return Expression(first) >= second;
}
inline Constraint operator>=(const Term &term, const Variable &variable) {
  return Expression(term) >= variable;
}
inline Constraint operator>=(const Term &term, double constant) {
  return Expression(term) >= constant;
}
inline Constraint operator==(const Variable &variable,
                             const Expression &expression) {
  return expression == variable;
}
inline Constraint operator==(const Variable &variable, const Term &term) {
  return term == variable;
}
inline Constraint operator==(const Variable &first, const Variable &second) {
  return Term(first) == second;
}
inline Constraint operator==(const Variable &variable, double constant) {
  return Term(variable) == constant;
}
inline Constraint operator<=(const Variable &variable,
                             const Expression &expression) {
  return expression >= variable;
}
inline Constraint operator<=(const Variable &variable, const Term &term) {
  return term >= variable;
}
inline Constraint operator<=(const Variable &first, const Variable &second) {
  return Term(first) <= second;
}
inline Constraint operator<=(const Variable &variable, double constant) {
  return Term(variable) <= constant;
}
inline Constraint operator>=(const Variable &variable,
                             const Expression &expression) {
  return expression <= variable;
}
inline Constraint operator>=(const Variable &variable, const Term &term) {
  return term <= variable;
}
inline Constraint operator>=(const Variable &first, const Variable &second) {
  return Term(first) >= second;
}
inline Constraint operator>=(const Variable &variable, double constant) {
  return Term(variable) >= constant;
}
inline Constraint operator==(double constant, const Expression &expression) {
  return expression == constant;
}
inline Constraint operator==(double constant, const Term &term) {
  return term == constant;
}
inline Constraint operator==(double constant, const Variable &variable) {
  return variable == constant;
}
inline Constraint operator<=(double constant, const Expression &expression) {
  return expression >= constant;
}
inline Constraint operator<=(double constant, const Term &term) {
  return term >= constant;
}
inline Constraint operator<=(double constant, const Variable &variable) {
  return variable >= constant;
}
inline Constraint operator>=(double constant, const Expression &expression) {
  return expression <= constant;
}
inline Constraint operator>=(double constant, const Term &term) {
  return term <= constant;
}
inline Constraint operator>=(double constant, const Variable &variable) {
  return variable <= constant;
}
inline Constraint operator|(const Constraint &constraint, double strength) {
  return Constraint(constraint, strength);
}
inline Constraint operator|(double strength, const Constraint &constraint) {
  return constraint | strength;
}
}  // namespace kiwi
#define KIWI_MAJOR_VERSION 1
#define KIWI_MINOR_VERSION 4
#define KIWI_MICRO_VERSION 2
#define KIWI_VERSION_HEX 0x010402
#define KIWI_VERSION "1.4.2"
