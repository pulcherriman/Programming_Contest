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
using ll = int;
using vl = vector<ll>;
using vvl = vector<vl>;
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
constexpr int INF=1<<29;
constexpr int LINF=1<<29;

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
	static constexpr result_type max(){return numeric_limits<result_type>::max();}
	static constexpr result_type min(){return 0;}
	constexpr Random(const bool&isDeterministic):y(isDeterministic?2463534242ll:chrono::system_clock::now().time_since_epoch().count()){}
	constexpr int operator()(int a, int b){return next()%(b-a)+a;}
	constexpr double operator()(double a,double b){return (b-a)*next()/4294967296.0+a;}
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
	static const int TLE = 1800;
	static inline Timer timer = Timer(TLE);
	Mgr() {
		ios_base::sync_with_stdio(0); cin.tie(0);
		cerr<<fixed<<setprecision(3);
	}
	~Mgr(){
		// debug_f(timer.get(), "ms")<<flush;
	}
} _manager;

namespace std::tr1 {
	template<class S, class T>
	struct hash<pair<S,T>> {
		size_t operator()(pair<S,T> p) const {
			return (p.first << 7) ^ p.second;
		}
	};
}


const int n=30;
vvi ball(n);
void input() {
	rep(i,n){
		ball[i].resize(i+1);
		in(ball[i]);
	}
}

vvi action;
void act(int y, int x, int ny, int nx) {
	action.push_back({y, x, ny, nx});
	swap(ball[y][x], ball[ny][nx]);
}

void serveTop(int y, int x){
	if(y==0)return;

	const auto apply = [&](int y, int x, int ny, int nx){
		if(ball[y][x] > ball[ny][nx]) return;
		act(y, x, ny, nx);
		serveTop(ny, nx);
	};

	if (x==0) {
		apply(y, x, y-1, x);
		return;
	}
	if(x==y){
		apply(y, x, y-1, x-1);
		return;
	}
	if(ball[y-1][x-1] < ball[y-1][x]){
		apply(y, x, y-1, x);
		return;
	}
	apply(y, x, y-1, x-1);
}

void serveBottom(int y, int x){
	if(y==n-1)return;

	const auto apply = [&](int y, int x, int ny, int nx){
		if(ball[y][x] < ball[ny][nx]) return;
		act(y, x, ny, nx);
		serveBottom(ny, nx);
	};

	if(ball[y+1][x] < ball[y+1][x+1]){
		apply(y, x, y+1, x);
		return;
	}
	apply(y, x, y+1, x+1);
}

int serveTopSim(int y, int x){
	auto ball2 = ball;

	const auto inner = [&](int y, int x) {
		if(y==0)return 0;

		const auto apply = [&](int y, int x, int ny, int nx){
			if(ball2[y][x] > ball2[ny][nx]) return 0;
			swap(ball2[y][x], ball2[ny][nx]);
			return serveTopSim(ny, nx) + 1;
		};

		if (x==0) {
			return apply(y, x, y-1, x);
		}
		if(x==y){
			return apply(y, x, y-1, x-1);
		}
		if(ball2[y-1][x-1] < ball2[y-1][x]){
			return apply(y, x, y-1, x);
		}
		return apply(y, x, y-1, x-1);
	};

	return inner(y, x);
}

int serveBottomSim(int y, int x){
	auto ball2 = ball;

	const auto inner = [&](int y, int x) {
		if(y==n-1)return 0;

		const auto apply = [&](int y, int x, int ny, int nx){
			if(ball2[y][x] < ball2[ny][nx]) return 0;
			swap(ball2[y][x], ball2[ny][nx]);
			return serveBottomSim(ny, nx) + 1;
		};

		if(ball2[y+1][x] < ball2[y+1][x+1]){
			return apply(y, x, y+1, x);
		}
		return apply(y, x, y+1, x+1);
	};

	return inner(y, x);
}




void challenge(vb isFront) {
	deque<int> q;
	rep(i,465) q.push_back(i);

	rep(t,465){
		int y=0,x=0;
		rep(i,n){
			rep(j,i+1){
				if(isFront[t] and ball[i][j]==q.front()) {
					y=i, x=j;
				}else if(!isFront[t] and ball[i][j]==q.back()){
					y=i, x=j;
				}
			}
		}
		if(isFront[t]){
			serveTop(y,x);
			q.pop_front();
		}else{
			serveBottom(y,x);
			q.pop_back();
		}
	}
}

int main() {
	input();

	auto baseball = ball;
	vb isFront(465, true);
	challenge(isFront);

	int answer = LINF;
	auto answerAction = action;
	vvi fixedact;


	int cnt = 0, bestScore = siz(action)*5;

	vvi results(2,vi(3,0));
	while(Mgr::timer){
		cnt++;
		action.clear();
		ball = baseball;
		for(auto& v:fixedact){
			act(v[0],v[1],v[2],v[3]);
		}

		int mode = Random(0, 2);

		int t = min(min(Random(0, 465), Random(0,465)), INF);
		// int t = Random(0, 464);
		int cy = Random(1, n);
		int cx = Random(0, cy);
		if(mode==0){
			isFront[t] = !isFront[t];
		}else{
			act(cy,cx,cy,cx+1);
		}
		challenge(isFront);

		int score = siz(action)*5;

		double init = 4, fin = 0.1;
		double temp = init - (init-fin) * Mgr::timer.get() / Mgr::TLE;
		double prob = exp(min(0.0, fin * (bestScore - score) / temp));

		if(Random(0.0, 1.0) > prob){
			results[mode][0]++;
			if(mode==0){
				isFront[t] = !isFront[t];
			}else{
				act(cy,cx,cy,cx+1);
			}
		}else{
			results[mode][bestScore > score ? 2 : 1]++;
			if(mode==1 and siz(answerAction) > siz(action)){
				fixedact.push_back({cy,cx,cy,cx+1});
			}
			bestScore = score;
		}
		if(chmin(answer, score)) {
			answerAction = action;
		}
	}

	while(Mgr::timer.get() <= 1980){
		rep(cy,1,n){
			if(Mgr::timer.get() > 1980)break;
			rep(cx,0,cy){
				if(Mgr::timer.get() > 1980)break;
				cnt++;
				action.clear();
				ball = baseball;
				for(auto& v:fixedact){
					act(v[0],v[1],v[2],v[3]);
				}

				act(cy,cx,cy,cx+1);
				challenge(isFront);

				int score = siz(action)*5;

				if(score > bestScore){
					act(cy,cx,cy,cx+1);
				}else{
					fixedact.push_back({cy,cx,cy,cx+1});
					bestScore = score;
				}
				if(chmin(answer, score)) {
					answerAction = action;
				}
			}
		}
	}

	out(answerAction.size());
	for(auto&v:answerAction) out(v);
	// debug(results);
}
