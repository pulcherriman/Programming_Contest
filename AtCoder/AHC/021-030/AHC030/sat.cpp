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
	uint64_t get() const { return (getClocks()-start)/ClocksPerMsec; }
	operator bool() const { return getClocks()<limit; }
	float persentile() const { return (float)get()/limit; }
};
void wait(const int&msec){Timer tm(msec); while(tm);}

struct Mgr {
	static const int TLE = 20000;
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


// SAT Solver
// CDCL Solver
// Author togatoga
// https://github.com/togatoga/togasat
// modified by plcherrim.
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
    vector<Lit> data;  //(x1 v x2 v not x3)
    Clause() {}
    Clause(const vector<Lit> &ps, bool learnt) {
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

  CRef allocClause(vector<Lit> &ps, bool learnt = false) {
    static CRef res = 0;
    ca[res] = move(Clause(ps, learnt));
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

  bool addClause_(vector<Lit> &ps) {
    // sort(ps.begin(), ps.end());
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

  HashMap<CRef, Clause> ca;  // store clauses
  HashSet<CRef> clauses;     // original problem;
  HashSet<CRef> learnts;
  HashMap<int, vector<Watcher>> watches;
  vector<VarData> vardata;  // store reason and level for each variable
  vector<bool> polarity;    // The preferred polarity of each variable
  vector<bool> decision;
  vector<bool> seen;
  // Todo
  int qhead;
  vector<Lit> trail;
  vector<int> trail_lim;
  // Todo rename(not heap)
  IndexedSet<pair<double, Var>> order_heap;
  vector<double> activity;
  double var_inc;
  vector<Lit> model;
  vector<Lit> conflict;
  int nVars() const { return vardata.size(); }
  int decisionLevel() const { return trail_lim.size(); }
  void newDecisionLevel() { trail_lim.emplace_back(trail.size()); }

  inline CRef reason(Var x) const { return vardata[x].reason; }
  inline int level(Var x) const { return vardata[x].level; }
  inline void varBumpActivity(Var v) {
    pair<double, Var> p = make_pair(activity[v], v);
    activity[v] += var_inc;
    if (order_heap.erase(p) == 1) {
      order_heap.insert(make_pair(activity[v], v));
    }

    if (activity[v] > 1e100) {
      // Rescale
      IndexedSet<pair<double, Var>> tmp_order;
      tmp_order = move(order_heap);
      order_heap.clear();
      for (int i = 0; i < nVars(); i++) {
        activity[i] *= 1e-100;
      }
      for (auto &val : tmp_order) {
        order_heap.insert(make_pair(activity[val.second], val.second));
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
    order_heap.insert(make_pair(0.0, v));
  }
  void uncheckedEnqueue(Lit p, CRef from = CRef_Undef) {
    assert(value(p) == l_Undef);
    assigns[var(p)] = sign(p);
    vardata[var(p)] = move(mkVarData(from, decisionLevel()));
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
  void analyze(CRef confl, vector<Lit> &out_learnt, int &out_btlevel) {
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
        order_heap.insert(make_pair(activity[x], x));
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
      vector<Watcher> &ws = watches[p.x];
      vector<Watcher>::iterator i, j, end;
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
    vector<Lit> learnt_clause;
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
  vector<lbool> assigns;  // The current assignments (ex assigns[0] = 0 ->
                               // X1 = True, assigns[1] = 1 -> X2 = False)
  lbool answer;                // SATISFIABLE 0 UNSATISFIABLE 1 UNKNOWN 2
  Solver() { qhead = 0; }
  void reset() {
	// all member
	assigns.clear();
	ca.clear();
	clauses.clear();
	learnts.clear();
	watches.clear();
	vardata.clear();
	polarity.clear();
	decision.clear();
	seen.clear();
	trail.clear();
	trail_lim.clear();
	order_heap.clear();
	activity.clear();
	var_inc = 1.0;
	model.clear();
	conflict.clear();
	answer = l_Undef;
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
	  if(!Mgr::timer) {
		return answer = l_Undef;
	  }
    }
    answer = status;
    return status;
  };

  void addClause(vector<int> &clause) {
    vector<Lit> lits;
    lits.resize(clause.size());
    for (int i = 0; i < clause.size(); i++) {
      int var = abs(clause[i]) - 1;
      while (var >= nVars()) newVar();
      lits[i] =
          move((clause[i] > 0 ? mkLit(var, false) : mkLit(var, true)));
    }
    addClause_(lits);
  }
};
}  // namespace togasat

template<class T=ll>
struct ZobristHash {
	ZobristHash() {}
	ll get_or_create(T key) {
		if(mp.find(key)==mp.end())mp[key]=Random(1ll,numeric_limits<ll>::max());
		return mp[key];
	}
	ll calc_hash(vector<T>&v) {
		ll ret=0;
		for(auto&a:v){
			ret^=get_or_create(a);
		}
		return ret;
	}
	// vの先頭からi-1番目までの集合のハッシュ 同じ数字はスルー
	vector<ll> calc_hash_seq(vector<T>&v) {
		HashSet<T> hs;
		vector<ll> ret(1,0);
		for(auto&a:v){
			ret.emplace_back(ret.back());
			if(hs.find(a)==hs.end()){
				ret.back()^=get_or_create(a);
				hs.insert(a);
			}
		}
		return ret;
	}
private:
	HashMap<T,ll> mp;
};


const int n=20;
int main() { /**/
	def(int,__,m); {float _; in(_);}
	vi height(m,0), width(m,0), cnt(m);
	vector<bitset<n*n>> item(m);;

	rep(i,m) {
		cin>>cnt[i];
		item[i].reset();

		rep(cnt[i]){
			def(int,y,x);
			chmax(height[i],y+1);
			chmax(width[i],x+1);
			item[i][y*n+x]=1;
		}
	}
	rep(m){
		def(int,_,__);
	}
	vvi answer(n,vi(n,-1)); in(answer);



	togasat::Solver solver;
	vvi rule_backup;
	ZobristHash<int> zobrist;
	HashSet<ll> hss;
	bool started = false;
	const auto addClause = [&](vi&clause) {
		auto hs = zobrist.calc_hash(clause);
		if(hss.find(hs) != hss.end()) return;
		hss.insert(hs);
		solver.addClause(clause);
		rule_backup.push_back(clause);
	};

	rep(i,m){
		// あるアイテムは、一つの場所のみに置かれる
		{
			vi rules(n*n); iota(all(rules),n*n*i+1);
			addClause(rules);
		}
		{
			rep(j,n*n)rep(k,j+1,n*n) {
				vi rules{-(n*n*i+j+1), -(n*n*i+k+1)};
				addClause(rules);
			}
		}
		{
			rep(j,n-height[i]+1, n)rep(k,n-width[i]+1, n) {
				vi rules{-(n*n*i+j*n+k+1)};
				addClause(rules);
			}
		}
	}

	// if ((solverStatus = solver.solve()) == 0) {
	// 	rep(i,m)rep(j,n*n){
	// 		if(solver.assigns[n*n*i+j] == 0){
	// 			out(i,j/n,j%n);
	// 		}
	// 	}
	// }else{
	// 	out("unsat");
	// }

	const auto checkUnique = [&]() {
		togasat::Solver testSolver = solver;
		// for(auto&rule:rule_backup){
		// 	testSolver.addClause(rule);
		// }

		togasat::lbool solverStatus = false;
		if ((solverStatus = testSolver.solve()) == 0) {
			vi rules;
			rep(i,m)rep(j,n*n){
				if(testSolver.assigns[n*n*i+j] == 0){
					rules.pb(-(n*n*i+j+1));
				}
			}

			testSolver.addClause(rules);
			if (testSolver.solve() == 0) {
				return false;
			} else {
				return true;
			}
		} else return false;
	};
	
	// while(true){
	// 	def(int,y,x);
	rep(y,n)rep(x,n){
		int v = answer[y][x];
		debug_f(y,x);
		started = true;	

		if(v==0){
			rep(i,m){
				rep(j,n-height[i]+1)rep(k,n-width[i]+1){
					if((j*n+k ? (item[i]<<(j*n+k)) : item[i]).test(y*n+x)){
						vi rules;
						rules.pb(-(n*n*i+j*n+k+1));
						addClause(rules);
					}
				}
			}
		}
		if(v==1){
			vi positions;
			rep(i,m){
				rep(j,n-height[i]+1)rep(k,n-width[i]+1){
					if((j*n+k ? (item[i]<<(j*n+k)) : item[i]).test(y*n+x)){
						positions.push_back(n*n*i+j*n+k+1);
					}
				}
			}
			addClause(positions);
			rep(i,sz(positions))rep(j,i+1,sz(positions)){
				vi rules{-positions[i], -positions[j]};
				addClause(rules);
			}
		}
		
		if(checkUnique()){
			out_f("unique");
			rep(i,m)rep(j,n*n){
				if(solver.assigns[n*n*i+j] == 0){
					out_f(i,j/n,j%n);
				}
			}
			return 0;
		}
	}
}