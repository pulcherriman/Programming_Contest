#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("inline")

#pragma GCC diagnostic ignored "-Wunused-value"
#ifdef _DEBUG
// #undef _DEBUG
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


const int h = 10;
const int w = 10;
const int n = h*w;
array<int,n> candies;
float score_base = 1e6;
array<vi, 3> candy_indices;
array<int, 4> candy_score_multiplier;

using Field = array<int, h>;
void print_d(Field&f) {
	cerr<<"===========\n";
	rep(i, h) {
		rep(j, w) {
			cerr<<(f[i]>>(j*2)&3)<<" ";
		}
		cerr<<'\n';
	}
	cerr<<"===========\n";
}
int getTypeOfPos(Field&f, int i, int j) {
	return f[i] >> (j*2) & 3;
}
void place(Field&f, int i, int j, int c) {
	f[i] |= c<<(j*2);
}
pii getBlankPos(Field&f, int p) {
	int y=0, x=0;
	while(true){
		if(getTypeOfPos(f, y, x) == 0) {
			if(--p == 0) return {y, x};
		}
		++x;
		if(x == w) x=0, ++y;
	}
}
const int dy[] = {-1,0,1,0}, dx[] = {0,1,0,-1};
const string move_char = "FRBL";

map<Field, int> memo_score;
int score(Field&f){
	if(memo_score.count(f)) return memo_score[f];
	bitset<n> used;
	used.reset();
	int score = 0;
	rep(i,h)rep(j,w)if(!used[i*w+j]){
		int c = getTypeOfPos(f, i, j);
		if(c == 0) continue;
		int cnt = 0;
		queue<pii> q;
		q.push({i, j});
		while(!q.empty()) {
			auto [y, x] = q.front(); q.pop();
			if(used[y*w+x]) continue;
			used[y*w+x] = true;
			++cnt;
			rep(k,4){
				int ny = y+dy[k], nx = x+dx[k];
				if(ny < 0 || ny >= h || nx < 0 || nx >= w) continue;
				if(getTypeOfPos(f, ny, nx) == c) q.push({ny, nx});
			}
		}
		score += cnt*cnt*candy_score_multiplier[c];
	}
	return memo_score[f] = round(score_base * score);
}

Field getMoved(Field&f, int t) {
	// fをt方向に傾ける
	Field ret;
	fill(all(ret), 0);

	if(t==0){
		rep(j,w){
			int bc = 0;
			rep(i,h){
				int c=getTypeOfPos(f, i, j);
				if(c == 0) ++bc;
				else place(ret, i-bc, j, c);
			}
		}
	}else if(t==1){
		rep(i,h){
			int bc = 0;
			for(int j=w-1; j>=0; --j){
				int c=getTypeOfPos(f, i, j);
				if(c == 0) ++bc;
				else place(ret, i, j+bc, c);
			}
		}
	}else if(t==2){
		rep(j,w){
			int bc = 0;
			for(int i=h-1; i>=0; --i){
				int c=getTypeOfPos(f, i, j);
				if(c == 0) ++bc;
				else place(ret, i+bc, j, c);
			}
		}
	}else if(t==3){
		rep(i,h){
			int bc = 0;
			rep(j,w){
				int c=getTypeOfPos(f, i, j);
				if(c == 0) ++bc;
				else place(ret, i, j-bc, c);
			}
		}
	}
	return ret;
}

map<Field, int> getNexts(Field&f, int c, int t) {
	map<Field, int> ret;
	rep(i,h)rep(j,w)if(getTypeOfPos(f, i, j) == 0) {
		Field nf = f;
		place(nf, i, j, c);
		ret[getMoved(nf, t)]++;
	}
	return ret;
}

//盤面fでturnターン目を終えた時、得られるスコアの期待値を返す
array<map<Field, float>, n*10> memo_sim;
float simulate(Field&f, int turn, int simulate_turn = 1){
	if(simulate_turn == 0 or turn+1 >= n) return score(f);
	if(memo_sim[simulate_turn * n + turn].count(f)) return memo_sim[simulate_turn * n + turn][f];
	float best_score = 0;
	rep(dir_next, 4){
		// debug("  dir_next", dir_next);
		float score_sum = 0;
		auto nexts = getNexts(f, candies[turn+1], dir_next);
		int patterns = n-1-turn;
		Field nf; int cnt;
		for(auto&p : nexts) {
			tie(nf, cnt) = p;
			// debug("    prob:", (float)cnt/patterns, "score:", simulate(nf, turn+1, simulate_turn-1));
			score_sum += (float)cnt * simulate(nf, turn+1, simulate_turn-1) / patterns;
		}
		// debug("  -> score_sum:", score_sum);
		chmax(best_score, score_sum);
	}
	return memo_sim[simulate_turn * n + turn][f] = best_score;
}

int main() {
	in(candies);
	rep(i,n){
		candy_indices[candies[i]-1].push_back(i);
	}

	{
		int norm_2 = 0;
		rep(i,3)norm_2 += candy_indices[i].size()*candy_indices[i].size();
		score_base /= norm_2;
		fill(all(candy_score_multiplier), 2);

		int min_index = (min_element(all(candy_indices), [](auto&a, auto&b){return a.size() < b.size();}) - candy_indices.begin());
		candy_score_multiplier[min_index + 1] = 1;
		int max_index = (max_element(all(candy_indices), [](auto&a, auto&b){return a.size() < b.size();}) - candy_indices.begin());
		candy_score_multiplier[max_index + 1] = 3;
		// rep(i,1,4){
		// 	candy_score_multiplier[i] = candy_indices[i-1].size() * candy_indices[i-1].size();
		// }
	}

	Field current;
	fill(all(current), 0);

	int p;
	rep(turn, n-1) {
		cin>>p;
		auto [y,x] = getBlankPos(current, p);
		place(current, y, x, candies[turn]);
		
		int best_type = 0;
		float best_score = 0;

		int sim_depth = 2;
		if(turn >= 84) sim_depth = 3;
		if(turn >= 92) sim_depth = 4;
		if(turn >= 95) sim_depth = 5;
		rep(dir,4){
			Field moved = getMoved(current, dir);
			auto next_score = simulate(moved, turn, sim_depth);
			// debug("!!! dir:", dir, "score:", next_score);
			if(chmax(best_score, next_score)) best_type = dir;
		}
		cout<<move_char[best_type]<<endl<<flush;
		current = getMoved(current, best_type);
	}

	// 最終ターン
	cin>>p;
	auto [y,x] = getBlankPos(current, p);
	place(current, y, x, candies[n-1]);
	debug("finalScore", score(current));
	print_d(current);

}
