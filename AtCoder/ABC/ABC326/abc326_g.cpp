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
template<class K> using IndexedSet=__gnu_pbds::tree<K,__gnu_pbds::null_type,less<K>,__gnu_pbds::rb_tree_tag,__gnu_pbds::tree_order_statistics_node_update>;
template<class K> using HashSet=__gnu_pbds::gp_hash_table<K,__gnu_pbds::null_type,hash<K>>;
template<class K,class V> using IndexedMap=__gnu_pbds::tree<K,V,less<K>,__gnu_pbds::rb_tree_tag,__gnu_pbds::tree_order_statistics_node_update>;
template<class K,class V> using HashMap=__gnu_pbds::gp_hash_table<K,V,hash<K>>;
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

/**
 * 基本的な辺の引き方
 * - Sは常に0,Tは常に1の頂点と考える
 * - 0に割り当て->1に割り当て の時、容量が損失
 * - 利得は事前に獲得しておいて、逆の事象が満たされたときに損失
 * @ref https://kanpurin.hatenablog.com/entry/moyasu-umeru#submodular2
 * @ref https://ei1333.github.io/luzhiled/snippets/memo/project-selection.html
 * @tparam Cap 
 */
template<class Cap=ll>
struct ProjectSelectionProblem {
private:
	int S, T;
	static const Cap INF_VAL = numeric_limits<Cap>::max()/2;
	HashMap<int, int> idx;
	Cap baseValue = 0;
	int autoCreated = numeric_limits<int>::min();

	int getIdx(int i) {
		if(idx.find(i) == idx.end()) idx[i] = idx.size();
		return idx[i];
	}
	[[nodiscard("expect least 2 edges by node.")]] int createNode() {
		idx[autoCreated] = idx.size();
		return autoCreated++;
	}

	vector<tuple<int,int,Cap>> edges;
	void add_edge(int from, int to, Cap cap) {
		edges.emplace_back(getIdx(from), getIdx(to), cap);
	}

public:
	ProjectSelectionProblem() {
		S = createNode();
		T = createNode();
	}

	Cap Solve() {
		mf_graph<Cap> g(idx.size());
		for(auto [from, to, cap] : edges) g.add_edge(from, to, cap);
		return baseValue - g.flow(getIdx(S), getIdx(T));
	}

	// あるxについて
	void LostIf_Xis0(int x, Cap v=INF_VAL) {
		if(v<0) [[unlikely]] {
			GetIf_Xis0(x, -v);
			return;
		}
		add_edge(x,T,v);
	}
	void LostIf_Xis1(int x, Cap v=INF_VAL) {
		if(v<0) [[unlikely]] {
			GetIf_Xis1(x, -v);
			return;
		}
		add_edge(S,x,v);
	}
	void GetIf_Xis0(int x, Cap v) {
		if(v<0) [[unlikely]] {
			LostIf_Xis0(x, -v);
			return;
		}
		baseValue += v;
		LostIf_Xis1(x,v);
	}
	void GetIf_Xis1(int x, Cap v) {
		if(v<0) [[unlikely]] {
			LostIf_Xis1(x, -v);
			return;
		}
		baseValue += v;
		LostIf_Xis0(x,v);
	}

	// 2変数x,yについて
	void LostIf_Xis0_Yis1(int x, int y, Cap v=INF_VAL) {
		if (v<0) [[unlikely]] {
			assert(0 && "cannot express");
			return;
		}
		add_edge(x,y,v);
	}
	void LostIf_XisA_YisB(int x, int y, Cap v00=0, Cap v01=0, Cap v10=0, Cap v11=0) {
		assert(v01+v10-v00-v11 >= 0 && "cannot express");
		baseValue -= v00;
		LostIf_Xis1(x, v10-v00);
		LostIf_Xis1(y, v11-v10);
		LostIf_Xis0_Yis1(x, y, v01+v10-v00-v11);
	}

	// 全てのx:xsについて
	template<ranges::range Ts>
	[[deprecated("illegal operation")]] void LostIf_All0(Ts&&xs, Cap v) {
		if (v<0) [[unlikely]] {
			GetIf_All0(xs, -v);
			return;
		}
		assert(0 && "maybe cannot express");
	}
	template<ranges::range Ts>
	[[deprecated("illegal operation")]] void LostIf_All1(Ts&&xs, Cap v) {
		if (v<0) [[unlikely]] {
			GetIf_All1(xs, -v);
			return;
		}
		assert(0 && "maybe cannot express");
	}

	template<ranges::range Ts>
	void GetIf_All0(Ts&&xs, Cap v) {
		if (v<0) [[unlikely]] {
			LostIf_All0(xs, -v);
			return;
		}
		int w = createNode();
		for(auto x : xs) add_edge(w,x,INF_VAL);
		GetIf_Xis0(w,v);
	}
	template<ranges::range Ts>
	void GetIf_All1(Ts&&xs, Cap v) {
		if (v<0) [[unlikely]] {
			#pragma GCC diagnostic push
			#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
			LostIf_All1(xs, -v);
			#pragma GCC diagnostic pop
			return;
		}
		int w = createNode();
		for(auto x : xs) add_edge(x,w,INF_VAL);
		GetIf_Xis1(w,v);
	}

	// 少なくとも1つのx:xsについて
	// minimizeの、v0=INFの特殊化でもある
	template<ranges::range Ts>
	void LostIf_Any0(Ts&&xs, Cap v) {
		if (v<0) [[unlikely]] {
			GetIf_Any0(xs, -v);
			return;
		}
		int w = createNode();
		for(auto x : xs) add_edge(x,w,INF_VAL);
		LostIf_Xis0(w,v);
	}
	template<ranges::range Ts>
	void LostIf_Any1(Ts&&xs, Cap v) {
		if (v<0) [[unlikely]] {
			GetIf_Any1(xs, -v);
			return;
		}
		int w = createNode();
		for(auto x : xs) add_edge(w,x,INF_VAL);
		LostIf_Xis1(w,v);
	}
	template<ranges::range Ts>
	void GetIf_Any0(Ts&&xs, Cap v) {
		if (v<0) [[unlikely]] {
			LostIf_Any0(xs, -v);
			return;
		}
		baseValue += v;
		LostIf_Any1(xs,v);
	}
	template<ranges::range Ts>
	void GetIf_Any1(Ts&&xs, Cap v) {
		if (v<0) [[unlikely]] {
			LostIf_Any1(xs, -v);
			return;
		}
		baseValue += v;
		LostIf_Any0(xs,v);
	}

	// 最小化
	/**
	 * @brief 
	 * - [x0,v0]:xs0について、要素x0を0に割り当てるとv0失う
	 * - [x1,v1]:xs1について、要素x1を1に割り当てるとv1失う
	 * - ただし上限はv
	 * のとき、損失を最小化するように割り当てる
	 * @tparam Ts vector<pair<int,Cap>>
	 * @param xs0 
	 * @param xs1 
	 * @param v 
	 */
	template<ranges::range Ts> requires is_convertible_v<Ts::value_type, pair<int,Cap>>
	void MinimizeLost_01(Ts&&xs0, Ts&&xs1, Cap limit=INF_VAL) {
		__MinimizeLost_inner(xs0, xs1, limit, createNode(), createNode());
	}

	template<ranges::range Ts> requires is_convertible_v<Ts::value_type, pair<int,Cap>>
	void MinimizeLost_0(Ts&&xs0, Cap limit=INF_VAL) {
		__MinimizeLost_inner(xs0, {}, limit, createNode(), T);
	}

	template<ranges::range Ts> requires is_convertible_v<Ts::value_type, pair<int,Cap>>
	void MinimizeLost_1(Ts&&xs1, Cap limit=INF_VAL) {
		__MinimizeLost_inner({}, xs1, limit, S, createNode());
	}

	template<ranges::range Ts> requires is_convertible_v<Ts::value_type, pair<int,Cap>>
	void __MinimizeLost_inner(Ts&&xs0, Ts&&xs1, Cap limit, int u, int w) {
		for(auto [x,v] : xs0) add_edge(x,u,v);
		for(auto [x,v] : xs1) add_edge(w,x,v);
		add_edge(u,w,limit);
		add_edge(w,u,INF_VAL); // 多分いらない
	}
};

int main() { /**/
	def(ll,n,m);
	vl lv(n); in(lv);
	vl ac(m); in(ac);
	ProjectSelectionProblem<> psp;

	const auto getSkillLvIndex=[&](int skill, int lv){
		return skill*5+lv-1;
	};
	rep(i,n){
		rep(j,2,6){
			psp.LostIf_Xis1(getSkillLvIndex(i,j), lv[i]);
			psp.LostIf_Xis0_Yis1(getSkillLvIndex(i,j-1), getSkillLvIndex(i,j));
		}
	}

	rep(i,m){
		vl d(n); in(d);
		rep(i,n) d[i] = getSkillLvIndex(i,d[i]);
		psp.GetIf_All1(d, ac[i]);
	}
	
	out(psp.Solve());

}