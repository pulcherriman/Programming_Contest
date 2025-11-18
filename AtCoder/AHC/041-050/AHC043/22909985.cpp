/**
 * C++23 Template @ AtCoder
 * - official support library
 *   - AC Library@1.5.1
 *   - Boost@1.82.0
 *   - GMP@6.2.1
 *   - Eigen@3.4.0-2ubuntu2
 * - compile option
 *   ```
 *     g++-12 -std=gnu++2b -O2 -DONLINE_JUDGE -DATCODER \
 *      -Wall -Wextra \
 *      -mtune=native -march=native \
 *      -fconstexpr-depth=2147483647 -fconstexpr-loop-limit=2147483647 -fconstexpr-ops-limit=2147483647 \
 *      -I/opt/ac-library -I/opt/boost/gcc/include -L/opt/boost/gcc/lib \
 *      -o a.out Main.cpp \
 *      -lgmpxx -lgmp \
 *      -I/usr/include/eigen3
 *   ```
 * - compiler information: https://docs.google.com/spreadsheets/d/1HXyOXt5bKwhKWXruzUvfMFHQtBxfZQ0047W7VVObnXI/edit#gid=408033513&range=F43
 */

#ifdef _DEBUG
// #define _GLIBCXX_DEBUG 1
// #undef _DEBUG
#else
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("inline")
#endif

/* 
 * Include Headers
 */
#if defined(EVAL) || defined(ATCODER) || defined(_DEBUG)
#include <atcoder/all>
using namespace atcoder;
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

#ifndef _GLIBCXX_DEBUG
template<class K> using IndexedSet=__gnu_pbds::tree<K,__gnu_pbds::null_type,less<K>,__gnu_pbds::rb_tree_tag,__gnu_pbds::tree_order_statistics_node_update>;
template<class K,class V> using IndexedMap=__gnu_pbds::tree<K,V,less<K>,__gnu_pbds::rb_tree_tag,__gnu_pbds::tree_order_statistics_node_update>;
template<class K,class V> struct HashMap : __gnu_pbds::gp_hash_table<K,V,hash<K>> {
	bool contains(const K&k) const { return this->find(k) != this->end(); }
};
template<class K> struct HashSet : __gnu_pbds::gp_hash_table<K,__gnu_pbds::null_type,hash<K>> {
	bool contains(const K&k) const { return this->find(k) != this->end(); }
};
#else
template<class K> using IndexedSet=set<K>;
template<class K> using HashSet=unordered_set<K>;
template<class K,class V> using IndexedMap=map<K,V>;
template<class K,class V> using HashMap=unordered_map<K,V>;
#endif
template<class V> using maxpq = priority_queue<V>;
template<class V> using minpq = priority_queue<V, vector<V>, greater<V>>;

#define all(a) begin(a),end(a)
#define rall(a) rbegin(a),rend(a)
#define __LOOPSWITCH(_1, _2, _3, __LOOPSWITCH, ...) __LOOPSWITCH
#define rep(...) __LOOPSWITCH(__VA_ARGS__, __RANGE, __REP, __LOOP) (__VA_ARGS__)
#define rrep(...) __LOOPSWITCH(__VA_ARGS__, __RRANGE, __RREP, __LOOP) (__VA_ARGS__)
#define __LOOP(q) for([[maybe_unused]] int _lp ## __LINE__ : views::iota(0, q))
#define __LOOP2(q,l) __LOOP3(q,l)
#define __LOOP3(q,l) __REP(_lp ## l,q)
#define __REP(i,n) __RANGE(i,0,n)
#define __RANGE(i,a,n) for(int i=((int)a);i<((int)n);++i)
#define __RREP(i,n) __RRANGE(i,0,n)
#define __RRANGE(i,a,n) for(int i=((int)(n)-1);i>=((int)a);--i)
#define sz(a) ((int)(a).size())
#define pb push_back
#define eb emplace_back

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
template<class T,class...Args>auto vec(T x,int arg,Args...args){
	if constexpr(sizeof...(args)==0) return vector(arg,x);
	else return vector(arg,vec(x,args...));
}
template<class T>constexpr bool chmax(T&a, type_identity_t<T> b){return a<b?a=b,1:0;}
template<class T>constexpr bool chmin(T&a, type_identity_t<T> b){return a>b?a=b,1:0;}
template<class S>S sum(vector<S>&a){return accumulate(all(a),S());}
template<class S>S max(vector<S>&a){return *max_element(all(a));}
template<class S>S min(vector<S>&a){return *min_element(all(a));}
ll sumAtoB(ll a,ll b){return (a+b)*(b-a+1)/2;}

namespace IO {
	// concepts定義
	template<typename T> concept Iterable = ranges::range<T> && !is_convertible_v<T, string_view>;
	template<typename T> concept RecursiveIterable = Iterable<T> && ranges::range<ranges::range_value_t<T>>;
	template<typename T> concept TupleLike = !Iterable<T> && requires(T a) {
		tuple_size<T>::value;
		get<0>(a);
		!is_convertible_v<T, string_view>;
	};

	// output
	constexpr ostream&operator<<(ostream&os, Iterable auto a){
		if(auto b=begin(a), e=end(a) ; a.size()) for(os<<(*b++);b!=e;os<<' '<<(*b++)) ;
		return os;
	}
	constexpr ostream&operator<<(ostream&os, RecursiveIterable auto a){
		if(auto b=begin(a), e=end(a) ; a.size()) for(os<<(*b++);b!=e;os<<'\n'<<(*b++)) ;
		return os;
	}
	constexpr ostream&operator<<(ostream&os, TupleLike auto a){
		apply([&](auto&&...args){((os<<args<<' '),...);}, a);
		return os;
	}

	template<class T, class...Ts> constexpr ostream& pargs(ostream&os, T&&t, Ts&&...args) {
		return ((os<<t)<<...<<(os<<' ', args));
	}
	template<class...Ts> constexpr ostream& out(Ts...args) { return pargs(cout, args...)<<'\n'; }
	template<class...Ts> constexpr ostream& out_f(Ts...args) { return pargs(cout, args...)<<'\n'<<flush; }
	template<class...Ts> constexpr ostream& debug_f(Ts...args) { return pargs(cerr, args...)<<'\n'<<flush; }
	#ifdef _DEBUG
	template<class...Ts> constexpr ostream& debug(Ts...args) { return pargs(cerr, args...)<<'\n'; }
	#else
	#define debug(...) if(false)debug_f(__VA_ARGS__)
	#endif
	void Yn(bool f) { out(f?"Yes":"No"); }

	// input
	constexpr auto&operator>>(istream&is, Iterable auto&t){ for(auto&a:t)is>>a; return is; }
	constexpr auto&operator>>(istream&is, TupleLike auto&t){
		apply([&](auto&&...args){((is>>args),...);}, t);
		return is;
	};

	template<class T, class...Ts> constexpr istream& gargs(istream&is, T&&t, Ts&&...args) {
		return ((is>>t)>>...>>args);
	}
	template<typename...S>auto&in(S&...s){return gargs(cin, s...);}
	#define def(t,...) t __VA_ARGS__; in(__VA_ARGS__)
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
} 

#ifdef _DEBUG
Random(1);
#else
Random(0);
#endif

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
	uint64_t get() const { return (getClocks()-start)/ClocksPerMsec; }
	operator bool() const { return getClocks()<limit; }
	float persentile() const { return (float)get()/limit; }
};
void wait(const int&msec){Timer tm(msec); while(tm);}

struct Mgr {
	#ifdef _DEBUG
	static const int TLE = 3000;
	#else
	static const int TLE = 3000;
	#endif
	static inline Timer timer = Timer(TLE-70);
	Mgr() {
		ios_base::sync_with_stdio(0); cin.tie(0);
		cout<<fixed<<setprecision(11);
		cerr<<fixed<<setprecision(3);
	}
	~Mgr(){
		cout<<flush;
		debug_f(timer.get(), "ms")<<flush;
	}
} _manager;

namespace std {
	template<class T>
	struct hash_base {
		const static inline size_t hash_value = 0x9e3779b9;
		static inline size_t hash_rnd = Random(0, numeric_limits<size_t>::max());
		template<class V, class P=remove_const_t<remove_reference_t<V>>> static size_t& do_hash(size_t&seed, V&v) {
			return seed ^= hash<P>{}(v) + hash_value + (seed<<6) + (seed>>2);
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

	template<class...Ts>
	struct hash<tuple<Ts...>> : public hash_base<tuple<Ts...>> {
		size_t operator()(tuple<Ts...> t) const {
			return apply([&](auto&&...args)->size_t{
				size_t seed = 0;
				for(auto&&v : {args...}) this->do_hash(seed, v);
				return this->do_hash(seed, this->hash_value);
			}, t);
		}
	};
}


namespace togasat {
using Var = int;
using CRef = int;
using lbool = int;
const CRef CRef_Undef = -1;
class Solver {
 private:
  const lbool l_True = 0;
  const lbool l_False = 1;
  const lbool l_Undef = 2;

  const int var_Undef = -1;

  // Literal
  struct Lit {
    int x;
    inline bool operator==(Lit p) const { return x == p.x; }
    inline bool operator!=(Lit p) const { return x != p.x; }
    inline bool operator<(Lit p) const { return x < p.x; }
    inline Lit operator~() {
      Lit q;
      q.x = x ^ 1;
      return q;
    }
  };

  inline Lit mkLit(Var var, bool sign) {
    Lit p;
    p.x = var + var + sign;
    return p;
  };
  inline bool sign(Lit p) const { return p.x & 1; }
  inline int var(Lit p) const { return p.x >> 1; }
  inline int toInt(Var v) { return v; }
  inline int toInt(Lit p) { return p.x; }
  inline Lit toLit(int x) {
    Lit p;
    p.x = x;
    return p;
  }
  const Lit lit_Undef = {-2};
  const Lit lit_Error = {-1};

  // lifted boolean
  // VarData
  struct VarData {
    CRef reason;
    int level;
  };
  inline VarData mkVarData(CRef cr, int l) {
    VarData d = {cr, l};
    return d;
  }
  // Watcher
  struct Watcher {
    CRef cref;
    Lit blocker;
    Watcher() {}
    Watcher(CRef cr, Lit p) : cref(cr), blocker(p) {}
    bool operator==(const Watcher &w) const { return cref == w.cref; }
    bool operator!=(const Watcher &w) const { return cref != w.cref; }
  };

  // Clause
  class Clause {
   public:
    struct {
      bool learnt;
      int size;
    } header;
    std::vector<Lit> data;  //(x1 v x2 v not x3)
    Clause() {}
    Clause(const std::vector<Lit> &ps, bool learnt) {
      header.learnt = learnt;
      header.size = ps.size();
      // data = move(ps);
      data.resize(header.size);
      for (int i = 0; i < ps.size(); i++) {
        data[i] = ps[i];
        //   //data.emplace_back(ps[i]);
      }
    }

    int size() const { return header.size; }
    bool learnt() const { return header.learnt; }
    Lit &operator[](int i) { return data[i]; }
    Lit operator[](int i) const { return data[i]; }
  };

  CRef allocClause(std::vector<Lit> &ps, bool learnt = false) {
    static CRef res = 0;
    ca[res] = std::move(Clause(ps, learnt));
    return res++;
  }

  Var newVar(bool sign = true, bool dvar = true) {
    int v = nVars();

    assigns.emplace_back(l_Undef);
    vardata.emplace_back(mkVarData(CRef_Undef, 0));
    activity.emplace_back(0.0);
    seen.push_back(false);
    polarity.push_back(sign);
    decision.push_back(0);
    setDecisionVar(v, dvar);
    return v;
  }

  bool addClause_(std::vector<Lit> &ps) {
    // std::sort(ps.begin(), ps.end());
    // empty clause
    if (ps.size() == 0) {
      return false;
    } else if (ps.size() == 1) {
      uncheckedEnqueue(ps[0]);
    } else {
      CRef cr = allocClause(ps, false);
      // clauses.insert(cr);
      attachClause(cr);
    }

    return true;
  }
  void attachClause(CRef cr) {
    const Clause &c = ca[cr];

    assert(c.size() > 1);

    watches[(~c[0]).x].emplace_back(Watcher(cr, c[1]));
    watches[(~c[1]).x].emplace_back(Watcher(cr, c[0]));
  }

  // Input
  void readClause(const std::string &line, std::vector<Lit> &lits) {
    lits.clear();
    int parsed_lit, var;
    parsed_lit = var = 0;
    bool neg = false;
    std::stringstream ss(line);
    while (ss) {
      int val;
      ss >> val;
      if (val == 0) break;
      var = abs(val) - 1;
      while (var >= nVars()) {
        newVar();
      }
      lits.emplace_back(val > 0 ? mkLit(var, false) : mkLit(var, true));
    }
  }

  std::unordered_map<CRef, Clause> ca;  // store clauses
  std::unordered_set<CRef> clauses;     // original problem;
  std::unordered_set<CRef> learnts;
  std::unordered_map<int, std::vector<Watcher>> watches;
  std::vector<VarData> vardata;  // store reason and level for each variable
  std::vector<bool> polarity;    // The preferred polarity of each variable
  std::vector<bool> decision;
  std::vector<bool> seen;
  // Todo
  int qhead;
  std::vector<Lit> trail;
  std::vector<int> trail_lim;
  // Todo rename(not heap)
  std::set<std::pair<double, Var>> order_heap;
  std::vector<double> activity;
  double var_inc;
  std::vector<Lit> model;
  std::vector<Lit> conflict;
  int nVars() const { return vardata.size(); }
  int decisionLevel() const { return trail_lim.size(); }
  void newDecisionLevel() { trail_lim.emplace_back(trail.size()); }

  inline CRef reason(Var x) const { return vardata[x].reason; }
  inline int level(Var x) const { return vardata[x].level; }
  inline void varBumpActivity(Var v) {
    std::pair<double, Var> p = std::make_pair(activity[v], v);
    activity[v] += var_inc;
    if (order_heap.erase(p) == 1) {
      order_heap.emplace(std::make_pair(activity[v], v));
    }

    if (activity[v] > 1e100) {
      // Rescale
      std::set<std::pair<double, Var>> tmp_order;
      tmp_order = std::move(order_heap);
      order_heap.clear();
      for (int i = 0; i < nVars(); i++) {
        activity[i] *= 1e-100;
      }
      for (auto &val : tmp_order) {
        order_heap.emplace(std::make_pair(activity[val.second], val.second));
      }
      var_inc *= 1e-100;
    }
  }
  bool satisfied(const Clause &c) const {
    for (int i = 0; i < c.size(); i++) {
      if (value(c[i]) == l_True) {
        return true;
      }
    }
    return false;
  }
  lbool value(Var p) const { return assigns[p]; }
  lbool value(Lit p) const {
    if (assigns[var(p)] == l_Undef) {
      return l_Undef;
    }
    return assigns[var(p)] ^ sign(p);
  }
  void setDecisionVar(Var v, bool b) {
    decision[v] = b;
    order_heap.emplace(std::make_pair(0.0, v));
  }
  void uncheckedEnqueue(Lit p, CRef from = CRef_Undef) {
    assert(value(p) == l_Undef);
    assigns[var(p)] = sign(p);
    vardata[var(p)] = std::move(mkVarData(from, decisionLevel()));
    trail.emplace_back(p);
  }
  // decision
  Lit pickBranchLit() {
    Var next = var_Undef;
    while (next == var_Undef or value(next) != l_Undef) {
      if (order_heap.empty()) {
        next = var_Undef;
        break;
      } else {
        auto p = *order_heap.rbegin();
        next = p.second;
        order_heap.erase(p);
      }
    }
    return next == var_Undef ? lit_Undef : mkLit(next, polarity[next]);
  }
  // clause learning
  void analyze(CRef confl, std::vector<Lit> &out_learnt, int &out_btlevel) {
    int pathC = 0;
    Lit p = lit_Undef;
    int index = trail.size() - 1;
    out_learnt.emplace_back(mkLit(0, false));
    do {
      assert(confl != CRef_Undef);
      Clause &c = ca[confl];
      for (int j = (p == lit_Undef) ? 0 : 1; j < c.size(); j++) {
        Lit q = c[j];
        if (not seen[var(q)] and level(var(q)) > 0) {
          varBumpActivity(var(q));
          seen[var(q)] = 1;
          if (level(var(q)) >= decisionLevel()) {
            pathC++;
          } else {
            out_learnt.emplace_back(q);
          }
        }
      }
      while (not seen[var(trail[index--])])
        ;
      p = trail[index + 1];
      confl = reason(var(p));
      seen[var(p)] = 0;
      pathC--;
    } while (pathC > 0);

    out_learnt[0] = ~p;

    // unit clause
    if (out_learnt.size() == 1) {
      out_btlevel = 0;
    } else {
      int max_i = 1;
      for (int i = 2; i < out_learnt.size(); i++) {
        if (level(var(out_learnt[i])) > level(var(out_learnt[max_i]))) {
          max_i = i;
        }
      }

      Lit p = out_learnt[max_i];
      out_learnt[max_i] = out_learnt[1];
      out_learnt[1] = p;
      out_btlevel = level(var(p));
    }

    for (int i = 0; i < out_learnt.size(); i++) {
      seen[var(out_learnt[i])] = false;
    }
  }

  // backtrack
  void cancelUntil(int level) {
    if (decisionLevel() > level) {
      for (int c = trail.size() - 1; c >= trail_lim[level]; c--) {
        Var x = var(trail[c]);
        assigns[x] = l_Undef;
        polarity[x] = sign(trail[c]);
        order_heap.emplace(std::make_pair(activity[x], x));
      }
      qhead = trail_lim[level];
      trail.erase(trail.end() - (trail.size() - trail_lim[level]), trail.end());
      trail_lim.erase(trail_lim.end() - (trail_lim.size() - level),
                      trail_lim.end());
    }
  }
  CRef propagate() {
    CRef confl = CRef_Undef;
    int num_props = 0;
    while (qhead < trail.size()) {
      Lit p = trail[qhead++];  // 'p' is enqueued fact to propagate.
      std::vector<Watcher> &ws = watches[p.x];
      std::vector<Watcher>::iterator i, j, end;
      num_props++;

      for (i = j = ws.begin(), end = i + ws.size(); i != end;) {
        // Try to avoid inspecting the clause:
        Lit blocker = i->blocker;
        if (value(blocker) == l_True) {
          *j++ = *i++;
          continue;
        }

        CRef cr = i->cref;
        Clause &c = ca[cr];
        Lit false_lit = ~p;
        if (c[0] == false_lit) c[0] = c[1], c[1] = false_lit;
        assert(c[1] == false_lit);
        i++;

        Lit first = c[0];
        Watcher w = Watcher(cr, first);
        if (first != blocker && value(first) == l_True) {
          *j++ = w;
          continue;
        }

        // Look for new watch:
        for (int k = 2; k < c.size(); k++)
          if (value(c[k]) != l_False) {
            c[1] = c[k];
            c[k] = false_lit;
            watches[(~c[1]).x].emplace_back(w);
            goto NextClause;
          }
        *j++ = w;
        if (value(first) == l_False) {  // conflict
          confl = cr;
          qhead = trail.size();
          while (i < end) *j++ = *i++;
        } else {
          uncheckedEnqueue(first, cr);
        }
      NextClause:;
      }
      int size = i - j;
      ws.erase(ws.end() - size, ws.end());
    }
    return confl;
  }

  static double luby(double y, int x) {
    // Find the finite subsequence that contains index 'x', and the
    // size of that subsequence:
    int size, seq;
    for (size = 1, seq = 0; size < x + 1; seq++, size = 2 * size + 1)
      ;

    while (size - 1 != x) {
      size = (size - 1) >> 1;
      seq--;
      x = x % size;
    }

    return pow(y, seq);
  }

  lbool search(int nof_conflicts) {
    int backtrack_level;
    std::vector<Lit> learnt_clause;
    learnt_clause.emplace_back(mkLit(-1, false));
    int conflictC = 0;
    while (true) {
      CRef confl = propagate();

      if (confl != CRef_Undef) {
        // CONFLICT
        conflictC++;
        if (decisionLevel() == 0) return l_False;
        learnt_clause.clear();
        analyze(confl, learnt_clause, backtrack_level);
        cancelUntil(backtrack_level);
        if (learnt_clause.size() == 1) {
          uncheckedEnqueue(learnt_clause[0]);
        } else {
          CRef cr = allocClause(learnt_clause, true);
          // learnts.insert(cr);
          attachClause(cr);
          uncheckedEnqueue(learnt_clause[0], cr);
        }
        // varDecay
        var_inc *= 1.05;
      } else {
        // NO CONFLICT
        if ((nof_conflicts >= 0 and conflictC >= nof_conflicts)) {
          cancelUntil(0);
          return l_Undef;
        }
        Lit next = pickBranchLit();

        if (next == lit_Undef) {
          return l_True;
        }
        newDecisionLevel();
        uncheckedEnqueue(next);
      }
    }
  };

 public:
  std::vector<lbool> assigns;  // The current assignments (ex assigns[0] = 0 ->
                               // X1 = True, assigns[1] = 1 -> X2 = False)
  lbool answer;                // SATISFIABLE 0 UNSATISFIABLE 1 UNKNOWN 2
  Solver() { qhead = 0; }
  void parseDimacsProblem(std::string problem_name) {
    std::vector<Lit> lits;
    int vars = 0;
    int clauses = 0;
    std::string line;
    std::ifstream ifs(problem_name, std::ios_base::in);
    while (ifs.good()) {
      getline(ifs, line);
      if (line.size() > 0) {
        if (line[0] == 'p') {
          sscanf(line.c_str(), "p cnf %d %d", &vars, &clauses);
        } else if (line[0] == 'c' or line[0] == 'p') {
          continue;
        } else {
          readClause(line, lits);
          if (lits.size() > 0) addClause_(lits);
        }
      }
    }
    ifs.close();
  }
  lbool solve() {
    model.clear();
    conflict.clear();
    lbool status = l_Undef;
    answer = l_Undef;
    var_inc = 1.01;
    int curr_restarts = 0;
    double restart_inc = 2;
    double restart_first = 100;
    while (status == l_Undef) {
      double rest_base = luby(restart_inc, curr_restarts);
      status = search(rest_base * restart_first);
      curr_restarts++;
    }
    answer = status;
    return status;
  };

  void addClause(std::vector<int> &clause) {
    std::vector<Lit> lits;
    lits.resize(clause.size());
    for (int i = 0; i < clause.size(); i++) {
      int var = abs(clause[i]) - 1;
      while (var >= nVars()) newVar();
      lits[i] =
          std::move((clause[i] > 0 ? mkLit(var, false) : mkLit(var, true)));
    }
    addClause_(lits);
  }
  void printAnswer() {
    if (answer == 0) {
      std::cout << "SAT" << std::endl;
      for (int i = 0; i < assigns.size(); i++) {
        if (assigns[i] == 0) {
          std::cout << (i + 1) << " ";
        } else {
          std::cout << -(i + 1) << " ";
        }
      }
      std::cout << "0" << std::endl;
    } else {
      std::cout << "UNSAT" << std::endl;
    }
  }
};
}  // namespace togasat

template<class T=int>
struct UnionFind{
	vi par; vector<T> dist;
	UnionFind(int x){par.assign(x,-1); dist.assign(x,T());}
	int find(int x){return par[x]<0?x:find(par[x]);}
	T depth(int x){return par[x]<0?T():depth(par[x])+dist[x];}
	bool same(int x,int y){return find(x)==find(y);}
	int size(int x){return -par[find(x)];}
	T diff(int x,int y){return same(x,y)?depth(x)-depth(y):LINF;}
	bool unite(int x, int y, T k=T()){
		k+=depth(y); k-=depth(x); k=-k;
		x=find(x); y=find(y);
		if(x==y)return false;
		if(size(x)<size(y)){swap(x,y);k=-k;}
		par[x]+=par[y]; par[y]=x; dist[y]=k;
		return true;
	}
	HashMap<int,vi> groups(){
		HashMap<int,vi> ret;
		rep(i,par.size()) ret[find(i)].push_back(i);
		return ret;
	}
};


const int N=50, T=800;
int M,K;

struct Person {
	int sx,sy,tx,ty;
	bool connected = false;
	int income;
	int dist;
};

vector<Person> people;

const pair<int,int> neighbor[] = {
	{-2,0},
	{-1,-1},
	{-1,0},
	{-1,1},
	{0,-2},
	{0,-1},
	{0,0},
	{0,1},
	{0,2},
	{1,-1},
	{1,0},
	{1,1},
	{2,0}
};

vector<pair<int,int>> stations;
array<array<vector<pair<int,int>>,N>,N> reachableStations;
void decideStations() {
	if(!stations.empty()) return;
	array<array<bool,N>,N> exist;
	array<array<vector<int>,N>,N> neighbors;
	rep(i,M){
		exist[people[i].sy][people[i].sx]=true;
		exist[people[i].ty][people[i].tx]=true;
	}

	rep(i,N)rep(j,N)if(exist[i][j]){
		for(auto [dy,dx]:neighbor){
			int ny=i+dy,nx=j+dx;
			if(ny<0 || nx<0 || ny>=N || nx>=N) continue;
			neighbors[i][j].push_back(ny*N+nx+1);
		}
	}

	vi answer;
	vb exclude(N*N, false);
	while(true){
		togasat::Solver solver;

		rep(i,N)rep(j,N){
			if(neighbors[i][j].size()>0){
				solver.addClause(neighbors[i][j]);
			}
		}
		rep(i,N*N)if(exclude[i]){
			vi clause(1, -i-1);
			solver.addClause(clause);
		}

		const auto status = solver.solve();
		if(status != 0){
			break;
		}

		bool excluded = false;
		vi values;
		rep(i,N)rep(j,N){
			if(solver.assigns[i*N+j]==0){
				values.push_back(i*N+j);
				if(neighbors[i][j].size()<=1 && !exclude[i*N+j]){
					exclude[i*N+j]=true;
					excluded=true;
				}
			}
		}
		if(values.size() <= answer.size() || answer.empty()){
			answer = values;
		}
		if(!excluded){
			break;
		}
	}

	for(auto&v:answer){
		stations.push_back({v/N,v%N});
		for(auto [dy,dx]:neighbor){
			int ny=v/N+dy,nx=v%N+dx;
			if(ny<0 || nx<0 || ny>=N || nx>=N) continue;
			reachableStations[ny][nx].push_back(stations.back());
		}
	}
}
int totalIncome;

enum RAILS {ERR=-1, EMPTY, STATION, LR, UD, LD, LU, RU, RD};
const string rails[] = {" ", "■", "━", "┃","┓",  "┛", "┗", "┏"};
const vector<pair<int,int>> railNeighbor[] = {
	{},
	{{0,1},{0,-1},{1,0},{-1,0}},
	{{0,1},{0,-1}},
	{{1,0},{-1,0}},
	{{0,-1},{1,0}},
	{{0,-1},{-1,0}},
	{{0,1},{-1,0}},
	{{0,1},{1,0}}
};
// (y1,x1) ~ (y2,x2) ~ (y3,x3) をつなぐために、(y2,x2) に置くべきレールの種類を返す
RAILS getRailType(int y1, int x1, int y2, int x2, int y3, int x3) {
	int d12 = abs(y1-y2)+abs(x1-x2);
	int d23 = abs(y2-y3)+abs(x2-x3);
	if(d12!=1 || d23!=1 || (y1==y3 && x1==x3)) return ERR;
	if(y1==y3){
		return RAILS::LR;
	}else if(x1==x3){
		return RAILS::UD;
	}else {
		if(y1>y3){
			swap(y1,y3);
			swap(x1,x3);
		}
		bool up = y1 < y2 || y3 < y2;
		bool left = x1 < x2 || x3 < x2;
		if(up && left) return RAILS::LU;
		bool right = x1 > x2 || x3 > x2;
		if(up && right) return RAILS::RU;
		bool down = y1 > y2 || y3 > y2;
		if(down && left) return RAILS::LD;
		if(down && right) return RAILS::RD;
		return ERR;
	}
}

array<array<int,N>,N> field;
int bestFinalScore = -1;
vector<tuple<int,int,int>> actions, bestActions(0);
UnionFind uf(N*N);
vector<pair<int,int>> placedStations;
enum STATE_TYPE {SAVE, LOAD, DIFF};
auto keepState(STATE_TYPE type) {
	static auto _field = field;
	static auto _actions = actions;
	static auto _uf = uf;
	static auto _placedStations = placedStations;
	if(type == SAVE){
		_field = field;
		// ここで候補を確定
		int cnt = actions.size() - _actions.size();
		rep(i,cnt){
			auto act = actions.back();
			actions.pop_back();
			_actions.push_back(act);
		}
		actions = _actions;
		_uf = uf;
		_placedStations = placedStations;

		int finalScore = K + (T-actions.size()+1)*totalIncome;
		if(chmax(bestFinalScore, finalScore)){
			bestActions = actions;
		}
		
		return 0;
	}else if(type == LOAD){
		field = _field;
		actions = _actions;
		uf = _uf;
		placedStations = _placedStations;
		return 0;
	} else if(type == DIFF){
		int cost = totalIncome;
		rep(i,_actions.size(), actions.size()){
			auto [type, y, x] = actions[i];
			if(type == STATION){
				cost += 5000 - totalIncome;
			}else{
				cost += 100 - totalIncome;
			}
		}
		return cost;
	} else return 0;
}

void printField() {
#ifdef _DEBUG
	cout<<"vvvvvvvvvv"<<endl;
	rep(i,N){
		rep(j,N){
			cout<<rails[field[i][j]];
		}
		cout<<endl;
	}
	cout<<"^^^^^^^^^^"<<endl;
#endif
}

void placeWait(int cnt) {
	rep(i,cnt){
		actions.emplace_back(EMPTY, 0, 0);
	}
}

void placeItem(int y, int x, RAILS type) {
	static int cnt = 0;
	if(type==STATION){
		if(field[y][x]==STATION) return;
		placedStations.emplace_back(y,x);
	}else{
		if(field[y][x]!=EMPTY) return;
	}

	actions.emplace_back(type, y, x);
	field[y][x]=type;
	cnt++;
	int p=y*N+x;
	for(auto [dy,dx]:railNeighbor[type]){
		int ny=y+dy,nx=x+dx;
		if(ny<0 || nx<0 || ny>=N || nx>=N) continue;
		int np=ny*N+nx;
		bool railOk = false;
		railOk |= (ny-y==1 && (field[ny][nx]==RAILS::UD || field[ny][nx]==RAILS::LU || field[ny][nx]==RAILS::RU || field[ny][nx]==RAILS::STATION));
		railOk |= (ny-y==-1 && (field[ny][nx]==RAILS::UD || field[ny][nx]==RAILS::LD || field[ny][nx]==RAILS::RD || field[ny][nx]==RAILS::STATION));
		railOk |= (nx-x==1 && (field[ny][nx]==RAILS::LR || field[ny][nx]==RAILS::LU || field[ny][nx]==RAILS::LD || field[ny][nx]==RAILS::STATION));
		railOk |= (nx-x==-1 && (field[ny][nx]==RAILS::LR || field[ny][nx]==RAILS::RU || field[ny][nx]==RAILS::RD || field[ny][nx]==RAILS::STATION));
		if(railOk){
			uf.unite(p,np);
		}
	}
}

// 座標(y,x)をカバーする駅を候補から選び、必要なら設置し、座標を返す
pair<int,int> setStations(int y, int x){
	const auto&sta = reachableStations[y][x];
	for(auto&[ny,nx]:sta){
		if(field[ny][nx]==RAILS::STATION) {
			return {ny,nx};
		}
	}
	const auto selectedStation = sta[0];
	placeItem(selectedStation.first,selectedStation.second,RAILS::STATION);
	// 既存の駅と連結していれば置く
	// for(auto&[dy,dx]:railNeighbor[RAILS::STATION]){
	// 	int ny=selectedStation.first+dy,nx=selectedStation.second+dx;
	// 	if(ny<0 || nx<0 || ny>=N || nx>=N) continue;
	// 	if(field[ny][nx]==RAILS::STATION){
	// 		debug_f("UNITE", y,x,"->",ny,nx);
	// 		wait(1000);
	// 		uf.unite(y*N+x,ny*N+nx);
	// 	}
	// }
	return selectedStation; // TODO: 最適な駅の選び方があるかも
}

// (sy,sx)から(ty,tx)へ線路を引く。既存の線路は上書きできない
bool createRailway(int sy, int sx, int ty, int tx) {
	// debug("  createRailway", sy, sx, ty, tx);
	array<array<tuple<int,int,int>,N>,N> prev; // prev[i][j]={始点からの距離、スコア、前の座標}
	rep(i,N)rep(j,N) prev[i][j]={INF,-1,-1};
	prev[sy][sx]={0,0,-1};
	deque<int> que; que.push_back(sy*N+sx);

	
	while(!que.empty()){
		int p=que.front(); que.pop_front();
		auto [dist,score,prevP]=prev[p/N][p%N];

		if(p==ty*N+tx) break;

		int y=p/N,x=p%N;
		// そこが駅なら、コスト0で連結している駅に移動できる
		if(field[y][x]==STATION){
			for(auto&[psy, psx]:placedStations){
				if(uf.same(p,psy*N+psx) && get<0>(prev[psy][psx])==INF){
					prev[psy][psx] = make_tuple(dist, score, p);
					que.push_front(psy*N+psx);
				}
			}
		}
		// 上下左右
		const auto adjacent = field[y][x] == EMPTY ? railNeighbor[1] : railNeighbor[field[y][x]];
		for(auto&[dy,dx]:adjacent){
			int ny=y+dy,nx=x+dx;
			if(ny<0 || nx<0 || ny>=N || nx>=N) continue;
			if(get<0>(prev[ny][nx])!=INF) continue;

			if(field[ny][nx]==EMPTY) {
				prev[ny][nx]={dist+1, score, p};
				que.emplace_back(ny*N+nx);
				continue;
			}

			bool railOk = false;
			railOk |= (ny-y==1 && (field[ny][nx]==RAILS::UD || field[ny][nx]==RAILS::LU || field[ny][nx]==RAILS::RU || field[ny][nx]==RAILS::STATION));
			railOk |= (ny-y==-1 && (field[ny][nx]==RAILS::UD || field[ny][nx]==RAILS::LD || field[ny][nx]==RAILS::RD || field[ny][nx]==RAILS::STATION));
			railOk |= (nx-x==1 && (field[ny][nx]==RAILS::LR || field[ny][nx]==RAILS::LU || field[ny][nx]==RAILS::LD || field[ny][nx]==RAILS::STATION));
			railOk |= (nx-x==-1 && (field[ny][nx]==RAILS::LR || field[ny][nx]==RAILS::RU || field[ny][nx]==RAILS::RD || field[ny][nx]==RAILS::STATION));

			if(railOk){
				prev[ny][nx]={dist, score, p};
				que.emplace_front(ny*N+nx);
			}
		}
	}
	
	if(get<0>(prev[ty][tx])==INF) return false;

	// debug("  createRailway place", get<0>(prev[ty][tx]), get<2>(prev[ty][tx]));

	// 後ろから辿って線路を引く
	int p=ty*N+tx;
	pair<int,int> prevPos= {-1,-1};
	int _c=0;
	while(p!=sy*N+sx){
		_c++;
		// if(_c>100) exit(1);
		auto [dist,score,prevP]=prev[p/N][p%N];
		int py=p/N,px=p%N;
		int prevy=prevP/N,prevx=prevP%N;
		// debug("    >> ", prevPos.first, prevPos.second, py, px, prevy, prevx);

		if(prevPos.first!=-1){
			if(field[py][px]!=EMPTY){
				prevPos={py,px};
				p=prevP;
				continue;
			}
			RAILS type = getRailType(prevPos.first, prevPos.second, py, px, prevy, prevx);
			if(type==ERR){
				prevPos={py,px};
				p=prevP;
				continue;
			}
			placeItem(py,px,type);
		}

		prevPos={py,px};
		p=prevP;
	}
	return true;

	// debug("  createRailway end");
}

// 既存の線路を壊さずに、(sy,sx)から(ty,tx)へ線路を引く
// 既につながっている駅間は移動できる
bool connect(int sy, int sx, int ty, int tx) {
	const auto sSta = setStations(sy,sx);
	const auto tSta = setStations(ty,tx);
	return createRailway(sSta.first,sSta.second,tSta.first,tSta.second);
}

int main() {
	{
		int _, __;
		cin>>_>>M>>K>>__;

		people.resize(M);
		rep(i,M){
			cin>>people[i].sy>>people[i].sx>>people[i].ty>>people[i].tx;
			people[i].income=abs(people[i].sx-people[i].tx)+abs(people[i].sy-people[i].ty);
		}
		rep(i,N)rep(j,N) field[i][j]=EMPTY;
	}

	decideStations();
	
	sort(rall(people),[](const Person&a,const Person&b){
		return a.income<b.income;
	});

	int minimumCost = INF;

	while(actions.size() < T) {
		debug("start turn:", actions.size(), K, "/ (+", totalIncome,")");
		// 前ターン、終了しなかった
		if(minimumCost!=INF){
			int remain = minimumCost - K;
			int waitCount = (remain + totalIncome - 1) / totalIncome;
			debug("force wait", minimumCost, remain, waitCount);
			placeWait(waitCount);
			K += waitCount * totalIncome;
			keepState(SAVE);
			minimumCost = INF;
			continue;
		}
		// printField();


		bool decided = false;
		minimumCost = INF;
		for(auto&p:people){
			if(p.connected==true) continue;
			keepState(SAVE);
			auto result = connect(p.sy,p.sx,p.ty,p.tx);
			if(!result) {
				keepState(LOAD);
				continue;
			}
			const auto cost = keepState(DIFF);
			if(K>=cost) {
				debug("cost", cost, "/", K);
				p.connected=true;
				K-=cost;
				totalIncome += p.income;
				decided = true;
				// printField();
				break;
			}else{
				if(chmin(minimumCost, cost)){
					// debug("minimumCost", minimumCost, "->", p.sy, p.sx, p.ty, p.tx);
				}
				keepState(LOAD);
			}
		}
		if(decided) {
			minimumCost = INF;
			debug("decided:", actions.size(), K, "/ (+", totalIncome,")");

			// TODO: 今回の通路追加でついでに繋がるようになった要素が無いか確認
			bool remainPeople = false;
			for(auto&p:people){
				if(p.connected) continue;
				const auto sSta = reachableStations[p.sy][p.sx];
				const auto tSta = reachableStations[p.ty][p.tx];
				for(auto&[sy,sx]:sSta)if(field[sy][sx]==STATION){
					for(auto&[ty,tx]:tSta)if(field[ty][tx]==STATION){
				// for(auto&[sdy,sdx]:neighbor){
				// 	for(auto&[tdy,tdx]:neighbor){
				// 		int sy=p.sy+sdy,sx=p.sx+sdx,ty=p.ty+tdy,tx=p.tx+tdx;
				// 		if(sy<0 || sx<0 || sy>=N || sx>=N) continue;
				// 		if(ty<0 || tx<0 || ty>=N || tx>=N) continue;
				// 		if(field[sy][sx]!=STATION || field[ty][tx]!=STATION) continue;
						if(uf.same(sy*N+sx,ty*N+tx)){ // TODO: 
							debug("!", p.sy, p.sx, p.ty, p.tx, p.income, "connected");
							p.connected=true;
							totalIncome += p.income;
							break;
						}
					}
					if(p.connected) break;
				}
				if(p.connected) continue;

				remainPeople = true;
			}

			keepState(SAVE);

			K += totalIncome;
			if(!remainPeople) break;
		}
	}
	

	actions = bestActions;
	if(T > actions.size()){
		placeWait(T-actions.size());
	}

	rep(i,T){
		auto&[type, y, x] = actions[i];
		if(type==EMPTY){
			out(-1);
		}else{
			out(type-1, y, x);
		}
	}
	debug("Final score: ", K);
	debug("Best score: ", bestFinalScore);
	debug("Best actions: ", bestActions.size());
}