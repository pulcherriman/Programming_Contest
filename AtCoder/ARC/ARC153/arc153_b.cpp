// @prefix _template
// @description 新テンプレート

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
template<class K> using HashSet=__gnu_pbds::gp_hash_table<K,__gnu_pbds::null_type,hash<K>>;
template<class K,class V> using IndexedMap=__gnu_pbds::tree<K,V,less<K>,__gnu_pbds::rb_tree_tag,__gnu_pbds::tree_order_statistics_node_update>;
template<class K,class V> using HashMap=__gnu_pbds::gp_hash_table<K,V,hash<K>>;
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
template<class T>constexpr bool chmax(T&a,T b){return a<b?a=b,1:0;}
template<class T>constexpr bool chmin(T&a,T b){return a>b?a=b,1:0;}
template<class S>S sum(vector<S>&a){return accumulate(all(a),S());}
template<class S>S max(vector<S>&a){return *max_element(all(a));}
template<class S>S min(vector<S>&a){return *min_element(all(a));}
ll sumAtoB(ll a,ll b){return (a+b)*(b-a+1)/2;}

namespace IO {
	// container detection
	template<typename T, typename _=void> struct is_container : false_type {};
	template<> struct is_container<string> : false_type {};
	template<class T> struct is_container<valarray<T>> : true_type {};
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
		if(auto b=begin(t), e=end(t) ; t.size()) for(os<<(*b++);b!=e;os<<Separator<<(*b++)) ;
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

using i64 = long long;
using u64 = unsigned long long;


struct SplayTreeByIndex{
  struct S{ u64 x,z; };
  struct F{ u64 a,b; };
  static S op(S l, S r){ return { (l.x+r.x)%MOD, l.z+r.z }; }
  static S e(){ return {0,0}; }
  static S mapping(F f, S x){ return { (x.x*f.a+x.z*f.b)%MOD, x.z }; }
  static F composite(F f, F x){ return { x.a*f.a%MOD, (x.b*f.a+f.b)%MOD }; }
  static F id(){ return { 1,0 }; }
  struct Node{
    int i = -1;
    Node *l = 0, *r = 0, *p = 0;
    int z = 0, sumz = 0;
    S a = e();
    S prod = e();
    F f = id();
    int rev = 0;
  };
  
  using pNode = unique_ptr<Node>;
  pNode pNIL;
  Node * NIL = 0;
  vector<pNode> A;
  Node *R = 0;
  
  SplayTreeByIndex(){
    pNIL = make_unique<Node>();
    NIL = pNIL.get();
    NIL->l = NIL->r = NIL->p = NIL;
    R = NIL;
  }
  
  void prepareDown(Node* c){
    auto cl = c->l;
    auto cr = c->r;
    auto cf = c->f;
    if(cl != NIL){
      cl->a = mapping(cf, cl->a);
      cl->prod = mapping(cf, cl->prod);
      cl->f = composite(cf, cl->f);
    }
    if(cr != NIL){
      cr->a = mapping(cf, cr->a);
      cr->prod = mapping(cf, cr->prod);
      cr->f = composite(cf, cr->f);
    }
    c->f = id();
    if(c->rev){
      if(cl != NIL) cl->rev ^= 1;
      if(cr != NIL) cr->rev ^= 1;
      swap(c->l, c->r);
    }
    c->rev = 0;
  }
  void prepareUp(Node* c){
    c->prod = op(op(c->l->prod, c->a) , c->r->prod);
    c->sumz = c->l->sumz + c->z + c->r->sumz;
  }
  
  Node*& parentchild(Node* c){
    if(c->p == NIL) return R;
    if(c->p->l == c) return c->p->l;
    return c->p->r;
  }
  
  void rotL(Node* c){
    auto p = c->p;
    parentchild(p) = c;
    c->p = p->p;
    p->p = c;
    p->r = c->l;
    c->l = p;
    if(p->r != NIL) p->r->p = p;
  }
  void rotR(Node* c){
    auto p = c->p;
    parentchild(p) = c;
    c->p = p->p;
    p->p = c;
    p->l = c->r;
    c->r = p;
    if(p->l != NIL) p->l->p = p;
  }
  
  void splay(Node* c){
    prepareDown(c);
    while(c->p != NIL){
      auto p = c->p;
      auto pp = p->p;
      if(pp != NIL) prepareDown(pp);
      prepareDown(p);
      prepareDown(c);
      if(p->l == c){
        if(pp == NIL){ rotR(c); }
        else if(pp->l == p){ rotR(p); rotR(c); }
        else{ rotR(c); rotL(c); }
      }
      else{
        if(pp == NIL){ rotL(c); }
        else if(pp->r == p){ rotL(p); rotL(c); }
        else{ rotL(c); rotR(c); }
      }
      if(pp != NIL) prepareUp(pp);
      prepareUp(p);
      prepareUp(c);
    }
    prepareUp(c);
  }
  
  Node* kth_element(int k){
    auto c = R;
    while(true){
      prepareDown(c);
      if(c->l->sumz == k) break;
      if(c->l->sumz < k){
        k -= c->l->sumz + 1;
        c = c->r;
      }
      else{
        c = c->l;
      }
    }
    splay(c);
    return c;
  }
  
  void insert_at(int k, S x){
    pNode pnx = make_unique<Node>(*NIL);
    Node* nx = pnx.get();
    nx->i = A.size();
    nx->z = nx->sumz = 1;
    nx->a = nx->prod = x;
    A.emplace_back(move(pnx));
    if(k == 0){
      nx->r = R;
      if(R != NIL) R->p = nx;
      R = nx;
      prepareUp(R);
      return;
    }
    if(k == R->sumz){
      nx->l = R;
      if(R != NIL) R->p = nx;
      R = nx;
      prepareUp(R);
      return;
    }
    kth_element(k);
    auto r = R;
    prepareDown(r);
    auto l = r->l;
    r->l = NIL;
    nx->l = l;
    nx->r = r;
    if(l != NIL) l->p = nx;
    r->p = nx;
    R = nx;
    prepareUp(r);
    prepareUp(nx);
  }
  
  void erase_at(int k){
    auto c = kth_element(k);
    if(k == 0){
      R = c->r;
      if(R != NIL) R->p = NIL;
    }
    else if(k == R->sumz-1){
      R = c->l;
      if(R != NIL) R->p = NIL;
    }
    else{
      auto l = c->l;
      auto r = c->r;
      r->p = NIL;
      R = r;
      kth_element(0);
      r = R;
      r->l = l;
      l->p = r;
      prepareUp(r);
    }
    swap(c->i, A.back()->i);
    swap(A[c->i], A[A.back()->i]);
    A.pop_back();
  }
  
  Node* between(int l, int r){
    if(l == 0 && r == R->sumz) return R;
    if(l == 0) return kth_element(r)->l;
    if(r == R->sumz) return kth_element(l-1)->r;
    kth_element(r);
    auto rp = R;
    auto lp = rp->l;
    lp->p = NIL;
    R = lp;
    kth_element(l-1);
    lp = R;
    rp->l = lp;
    lp->p = rp;
    R = rp;
    prepareUp(rp);
    return lp->r;
  }
  
  void reverse(int l, int r){
    auto c = between(l,r);
    c->rev ^= 1;
    splay(c);
  }
  void apply(int l, int r, F f){
    auto c = between(l,r);
    c->a = mapping(f, c->a);
    c->prod = mapping(f, c->prod);
    c->f = composite(f, c->f);
    splay(c);
  }
  S prod(int l, int r){
    return between(l,r)->prod;
  }
};


int main() {
	/*$1*/
	def(ll,h,w);
	vs s(h); in(s);
	SplayTreeByIndex H,W;
	rep(i,h){
		H.insert_at(i,{(ull)i,1});
	}
	rep(i,w){
		W.insert_at(i,{(ull)i,1});
	}

	def(ll,q);
	rep(q){
		def(ll,y,x);
		H.reverse(0,y);
		H.reverse(y,h);
		W.reverse(0,x);
		W.reverse(x,w);
	}

	vi ah(h), aw(w);
	rep(i,h){
		ah[i] = H.between(i,i+1)->a.x;
	}
	rep(i,w){
		aw[i] = W.between(i,i+1)->a.x;
	}
	debug(ah);
	debug(aw);
	rep(i,h){
		rep(j,w){
			cout << s[ah[i]][aw[j]];
		}
		cout << endl;
	}

	
}