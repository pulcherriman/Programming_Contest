#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("inline")

/* 
 * Include Headers
 */
#include <algorithm>
#include <iostream>
#include <cstdio>
#include <map>
#include <numeric>
#include <cmath>
#include <set>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <complex>
#include <string.h>
#include <unordered_set>
#include <unordered_map>
#include <bitset>
#include <iomanip>
#include <sys/time.h>
#include <tuple>
#include <random>
#include <chrono>
using namespace std;

/*
 * Additional Type Definition
 */
using vb=vector<bool>;
using vvb=vector<vb>;
using vi=vector<int>;
using vvi=vector<vi>;
using pii=pair<int,int>;
using vp=vector<pii>;
using ti2=tuple<int,int>;
using ti3=tuple<int,int,int>;
using ti4=tuple<int,int,int,int>;
using vs=vector<string>;

#define all(a) begin(a),end(a)
#define rall(a) rbegin(a),rend(a)
#define __LOOPSWITCH(_1, _2, _3, __LOOPSWITCH, ...) __LOOPSWITCH
#define rep(...) __LOOPSWITCH(__VA_ARGS__, __RANGE, __REP, __LOOP) (__VA_ARGS__)
#define rrep(...) __LOOPSWITCH(__VA_ARGS__, __RRANGE, __RREP, __LOOP) (__VA_ARGS__)
#define __LOOP(q) __LOOP2(q, __LINE__)
#define __LOOP2(q,l) __LOOP3(q,l)
#define __LOOP3(q,l) __REP(_lp ## l,q)
#define __REP(i,n) __RANGE(i,0,n)
#define __RANGE(i,a,n) for(int i=((int)a);i<((int)n);++i)
#define __RREP(i,n) __RRANGE(i,0,n)
#define __RRANGE(i,a,n) for(int i=((int)((n)-1));i>=((int)a);--i)
#define siz(a) ((int)(a).size())

/*
 * Constants
 */
constexpr int INF=1<<30;

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
	template<class...Ts> constexpr ostream& debug(Ts...args) { 
		return pargs(cerr, args...)<<'\n';
	}
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
	using result_type = unsigned int;
	constexpr result_type operator()(){return operator()(min(),max());}
	static constexpr result_type max(){return numeric_limits<result_type>::max();}
	static constexpr result_type min(){return 0;}
	constexpr Random(const bool&isDeterministic):y(isDeterministic?2463534242ll:chrono::system_clock::now().time_since_epoch().count()){}
	constexpr result_type operator()(result_type a, result_type b){return next()%(b-a)+a;}
	result_type getSeed(){return y;}
	void setSeed(result_type seed){y=seed;}
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
	uint64_t get() const{return (getClocks()-start)/ClocksPerMsec;}
	operator bool()const{return getClocks()<limit;}
};
void wait(const int&msec){Timer tm(msec); while(tm);}

struct Mgr {
	static const int TLE = 1000 - 20;
	static inline Timer timer = Timer(TLE);
	Mgr() {
		ios_base::sync_with_stdio(0); cin.tie(0);
		cerr<<fixed<<setprecision(3);
	}
	~Mgr(){
		debug_f(timer.get(), "ms")<<flush;
	}
} _manager;

const int n = 150;
array<pii, n> points;
array<int, n+1> routes;


float calc(array<int, n+1> route){
	float dist = 0;
	rep(i, n) {
		auto [x1, y1] = points[route[i]];
		auto [x2, y2] = points[route[i+1]];
		dist += hypot(x1-x2, y1-y2);
	}
	return dist;
}

void two_opt(array<int, n+1>&route, float&currentScore, bool only =false) {
	int st1 = Random(0,n);
	int st2 = Random(0,n);
	if(st1 > st2) swap(st1, st2);
	if(st1+1 >= st2) return;

	float optScore = currentScore;

	auto [x1, y1] = points[route[st1]];	
	auto [x2, y2] = points[route[st1+1]];
	auto [x3, y3] = points[route[st2]];
	auto [x4, y4] = points[route[st2+1]];
	optScore -= hypot(x1-x2, y1-y2) + hypot(x3-x4, y3-y4);
	optScore += hypot(x1-x3, y1-y3) + hypot(x2-x4, y2-y4);
	if(optScore < currentScore) {
		currentScore = optScore;
		reverse(route.begin()+st1+1, route.begin()+st2+1);
		return;
	}else if(!only){
		// float temp = (100-pow(100,float(Mgr::timer.get())/Mgr::TLE))/100;
		float temp = (1 - float(Mgr::timer.get())/Mgr::TLE) / 1;
		float p = exp((currentScore-optScore)/temp);
		if(Random(0.0,1.0) < p) {
			currentScore = optScore;
			reverse(route.begin()+st1+1, route.begin()+st2+1);
			return;
		}
	}
	return;
}

struct UnionFind{
	vi par,dist;
	UnionFind(int x){par.assign(x,-1); dist.assign(x,0);}
	int find(int x){return par[x]<0?x:find(par[x]);}
	int depth(int x){return par[x]<0?0:depth(par[x])+dist[x];}
	bool same(int x,int y){return find(x)==find(y);}
	int size(int x){return -par[find(x)];}
	int diff(int x,int y){return same(x,y)?depth(x)-depth(y):INF;}
	bool unite(int x,int y,int k=0){
		k+=depth(y); k-=depth(x); k=-k;
		x=find(x); y=find(y);
		if(x==y)return false;
		if(size(x)<size(y)){swap(x,y);k=-k;}
		par[x]+=par[y]; par[y]=x; dist[y]=k;
		return true;
	}
};


UnionFind uf(n);
array<vi, n> mst;

auto route = routes;
bitset<n> used;
void dfs() {
	used.reset();
	int ind=0;
	stack<int> st;
	st.push(0);
	while(!st.empty()) {
		int v = st.top();
		st.pop();
		if(used[v]) continue;
		used[v] = true;
		route[ind++] = v;
		for(auto&u : mst[v]) if(!used[u]) st.push(u);
	}
};


int main() {
	def(int, _);
	in(points);
	float currentScore = 1e7;

	vector<tuple<int,int,int>> edge;
	rep(i,n)rep(j,i){
		int x=points[i].first-points[j].first, y=points[i].second-points[j].second;
		edge.emplace_back(x*x+y*y, i,j);
	}
	sort(all(edge));
	for(auto&[cost,from,to]:edge)if(uf.unite(from,to)){
		mst[from].push_back(to);
		mst[to].push_back(from);
	}		

	rep(i,50000){
		shuffle(all(mst[i%n]), Random);
		dfs();

		float score = calc(route);
		rep(100) two_opt(route, score, true);
		if(chmin(currentScore, score)) routes = route;
	}
	debug(Mgr::timer.get());

	while(Mgr::timer) {
		two_opt(routes, currentScore);
	}
	for(auto&i:routes) out(i+1);

	debug(currentScore);
	debug(calc(routes));


}
