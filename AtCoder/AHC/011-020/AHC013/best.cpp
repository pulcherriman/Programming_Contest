#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("inline")

#pragma GCC diagnostic ignored "-Wunused-value"
#ifdef _DEBUG
// #define _GLIBCXX_DEBUG 1
#endif

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
#include <ext/pb_ds/assoc_container.hpp>
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
Random(1);
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
	static const int TLE = 3000;
	static inline Timer timer = Timer(TLE-20);
	Mgr() {
		ios_base::sync_with_stdio(0); cin.tie(0);
		cerr<<fixed<<setprecision(3);
	}
	~Mgr(){
		debug_f(timer.get(), "ms")<<flush;
	}
} _manager;

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

const int dy[]={0,1,0,-1};
const int dx[]={1,0,-1,0};

int n, k;
vs field;

using ConnectKey = tuple<int,int,int,int>;
vvb edge;
pair<int, vector<ConnectKey>> createTree(char c='1'){
	int score=0;
	vector<ConnectKey> ret;
	UnionFind uf((n+2)*(n+2));

	rep(i,1,n+1)rep(j,1,n+1)if(field[i][j]==c){
		int xMax=j;
		rep(v,2){
			int y=i, x=j;
			do{
				y+=dy[v], x+=dx[v];
				if(edge[y][x])break;
				if(field[y][x]!='0'){
					chmax(xMax,x);
					if(field[y][x]!=c) break;
					if(!uf.unite(i*(n+2)+j,y*(n+2)+x))break;
					ret.emplace_back(i,j,y,x);
					if(v==0){
						rep(l,j+1,x) edge[y][l]=true;
					}else{
						rep(l,i+1,y) edge[l][x]=true;
					}
					break;
				}
			}while(field[y][x]=='0');
		}
		chmax(j,xMax-1);
	}

	vi mp(101,0);
	rep(i,uf.par.size()) mp[uf.size(i)]++;
	rep(i,2,101) score+=(i*(i-1)/2)*(mp[i]/i);
	return {score, ret};
}

pair<int, int> calcConnectivity(string numbers){
	rep(i,1,n+1)rep(j,1,n+1)edge[i][j]=false;
	int score=0, conSize=0;

	for(auto&c:numbers){
		auto[sc, con]=createTree(c);
		score+=sc;
		conSize+=con.size();
	}
	return {score, conSize};
}

pair<int, vector<ConnectKey>> getConnectivity(string numbers){
	rep(i,1,n+1)rep(j,1,n+1)edge[i][j]=false;

	int score=0;
	vector<ConnectKey> connect;
	connect.reserve(100*k);

	for(auto&c:numbers){
		auto[sc, con]=createTree(c);
		score+=sc;
		connect.insert(connect.end(), con.begin(), con.end());
	}
	return {score, connect};
}


tuple<int, string> collectNumber(){
	string s(k, '0');
	iota(all(s),'1');
	// shuffle(all(s),Random);
	// auto[sc, _]=calcConnectivity(s);
	// return {sc, s};

	vi length = {0,0,2,2,2,3};

	int score=0;
	string numbers;
	do {
		auto[sc, _]=calcConnectivity(s.substr(0,length[k]));
		if(chmax(score, sc)) numbers = s;
	}while(next_permutation(all(s)));
	return {score, numbers};
}

int test=0;
tuple<int, vector<ConnectKey>, vector<ConnectKey>> yakinamashi(int initScore){
	auto[score, numbers]=collectNumber();
	debug("INIT", score, numbers.size());
	vector<ConnectKey> moves;
	int conSize=0;

	vp num;
	rep(i,1,n+1)rep(j,1,n+1)if(field[i][j]!='0')num.emplace_back(i,j);

	vi dir(4); iota(all(dir),0);
	int threshold=300/k;

	while(Mgr::timer){
		debug("th",threshold);
		int suc=0;
		shuffle(all(num), Random);
		int maxDiff = 0, failedDiff=0;

		rep(i,num.size()){
			if(!Mgr::timer) break;
			auto[y,x]=num[i];
			for(auto&v:dir){
				int maxLen=0;
				rep(d,1,2+1){
					if(field[y+dy[v]*d][x+dx[v]*d]=='0'){
						maxLen++;
					}else break;
				}

				bool isMoved=false;
				chmin(maxLen,2);

				rep(len,1,maxLen+1) {
					// if(moves.size()+len >= 40*k)break;
					if(!Mgr::timer) break;
					const int ny=y+dy[v]*len, nx=x+dx[v]*len;

					test++;

					swap(field[y][x], field[ny][nx]);
					auto[nxtScore, nxtConSize]=calcConnectivity(numbers);
					if(moves.size()+len+nxtConSize > 100*k){
						swap(field[y][x], field[ny][nx]);
						continue;
					}
					chmax(maxDiff, nxtScore-score);

					if(score+threshold < nxtScore 
						or (conSize > nxtConSize+1 and score-2 <= nxtScore)){
						debug(Mgr::timer.get(), test, score,"(",i,y,x,v,") =>",nxtScore-score);
						score=nxtScore;
						rep(d,len){
							moves.emplace_back(y+dy[v]*d,x+dx[v]*d,y+dy[v]*(d+1),x+dx[v]*(d+1));
						}
						num[i] = {ny,nx};
						suc++;
						i--;
						conSize = nxtConSize;
						isMoved = true;
						goto goNext;
					}else{
						chmax(failedDiff, nxtScore-score);
						swap(field[y][x], field[ny][nx]);
					}
				}
				if(isMoved) break;
			}
			goNext:;
		}

		if(suc==0){
			if(threshold==0) break;
			if(maxDiff==0) break;
			threshold = maxDiff-1;
		}else{
			if(threshold>0) threshold--;
		}
	}

	vector<ConnectKey> connect;
	tie(score, connect)=getConnectivity(numbers);

	return {score, moves, connect};
}

int main() {
	cin>>n>>k;
	edge.resize(n+2, vb(n+2, false));
	field.resize(n+2, string(n+2,'#'));
	rep(i,1,n+1){
		cin>>field[i];
		field[i]="#"+field[i]+"#";
	}
	auto init = field;

	int bestScore=0;
	vector<ConnectKey> bestConnect, bestMoves;
	while(Mgr::timer){
		field = init;
		auto[score, moves, connect]=yakinamashi(bestScore);
		if(chmax(bestScore, score)){
			bestConnect=connect;
			bestMoves=moves;
		}
		// break;
	}

	out(bestMoves.size());
	for(auto[a,b,c,d]:bestMoves){
		out(a-1,b-1,c-1,d-1);
	}
	out(bestConnect.size());
	for(auto[a,b,c,d]:bestConnect){
		out(a-1,b-1,c-1,d-1);
	}
	debug_f(test);

}

// 少ない回数の移動で、各数字が良い感じに偏るようにさせる焼き鈍し？