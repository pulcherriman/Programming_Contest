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
template<class K> using HashSet=__gnu_pbds::gp_hash_table<K,__gnu_pbds::null_type,hash<K>>;
template<class K,class V> using IndexedMap=__gnu_pbds::tree<K,V,less<K>,__gnu_pbds::rb_tree_tag,__gnu_pbds::tree_order_statistics_node_update>;
template<class K,class V> using HashMap=__gnu_pbds::gp_hash_table<K,V,hash<K>>;
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
	float persentile() const { return (float)(getClocks()-start)/(limit-start); }
};
void wait(const int&msec){Timer tm(msec); while(tm);}

struct Mgr {
	static const int TLE = 2000;
	static inline Timer timer = Timer(TLE-70);
	Mgr() {
		ios_base::sync_with_stdio(0); cin.tie(0);
		cout<<fixed<<setprecision(11);
		cerr<<fixed<<setprecision(3);
	}
	~Mgr(){
		cout<<flush;
		// debug_f(timer.get(), "ms")<<flush;
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


const int n=200, m=10, s=20;
vvi a_base(m, vi(s));

using Actions=vector<pair<int,int>>;
int solveCount = 0;
pair<int,Actions> solve(vvi a, int threshold, Actions decidedActions, int ashikiri=0, int nxtTgt=-1){
	solveCount++;
	Actions actions;
	int score=10000;
	vi exist(n);
	rep(i,m) rep(j,s) exist[a[i][j]]=i;
	
	const auto act_move = [&](int val, int moveTo){
		int tgt = exist[val];
		int idx = find(all(a[tgt]), val) - a[tgt].begin();
		actions.eb(val+1, moveTo+1);
		score -= sz(a[tgt]) - idx + 1;
		a[moveTo].insert(a[moveTo].end(), a[tgt].begin()+idx, a[tgt].end());
		rep(i,idx,sz(a[tgt])) exist[a[tgt][i]]=moveTo;
		a[tgt].resize(idx);
	};

	const auto act_put = [&](int val){
		int tgt = exist[val];
		actions.eb(val+1, 0);
		a[tgt].pop_back();
	};

	int startIndex = 0, skips=0;
	if(!decidedActions.empty()){
		rep(i,sz(decidedActions)-1) {
			if(decidedActions[i].second == 0) {
				act_put(decidedActions[i].first-1);
				startIndex++;
			} else {
				act_move(decidedActions[i].first-1, decidedActions[i].second-1);
			}
		}

		auto [ai,bi] = decidedActions.back();
		int c=Random(0,m);
		while(c==exist[ai-1] or c==bi-1) c=Random(0,m);
		if(nxtTgt!=-1) c=nxtTgt;
		if(c==exist[ai-1] or c==bi-1) return {0, actions};
		act_move(ai-1, c);
	}

	rep(i,startIndex,n){
		int tgt=exist[i];
		if(a[tgt].back() == i){
			act_put(i);
			continue;
		}
		int cnt=0;

		rrep(j,1,sz(a[tgt])){
			if(a[tgt][j-1]==i or (a[tgt][j] > a[tgt][j-1] and skips-- <= 0)) {
				cnt=j; break;
			}
		}

		int moveTo=0, bestDiff=INF;
		rep(j,m)if(j!=tgt){
			int diff=a[j].empty() ? -INF : a[j].back()-a[tgt][cnt];
			if(diff<0 and diff!=-INF) {
				diff = -diff + a[tgt].size() - cnt + threshold;
			}
			if(chmin(bestDiff,diff)) moveTo=j;
		}
		act_move(a[tgt][cnt], moveTo);
		if(a[tgt].back()==i){
			act_put(i);
		} else {
			i--;
		}
		if(score < ashikiri) {
			return {0, actions};
		}
	}
	return {score, actions};
}
pair<int,Actions> solve2(vvi a, int threshold, Actions decidedActions, int ashikiri=0, int nxtTgt=-1){
	solveCount++;
	Actions actions;
	int score=10000;
	vi exist(n);
	rep(i,m) rep(j,s) exist[a[i][j]]=i;
	
	const auto act_move = [&](int val, int moveTo){
		int tgt = exist[val];
		int idx = find(all(a[tgt]), val) - a[tgt].begin();
		actions.eb(val+1, moveTo+1);
		score -= sz(a[tgt]) - idx + 1;
		a[moveTo].insert(a[moveTo].end(), a[tgt].begin()+idx, a[tgt].end());
		rep(i,idx,sz(a[tgt])) exist[a[tgt][i]]=moveTo;
		a[tgt].resize(idx);
	};

	const auto act_put = [&](int val){
		int tgt = exist[val];
		actions.eb(val+1, 0);
		a[tgt].pop_back();
	};

	int startIndex = 0, skips=0;
	if(!decidedActions.empty()){
		rep(i,sz(decidedActions)-1) {
			if(decidedActions[i].second == 0) {
				act_put(decidedActions[i].first-1);
				startIndex++;
			} else {
				act_move(decidedActions[i].first-1, decidedActions[i].second-1);
			}
		}
		auto [ai,bi] = decidedActions.back();
		int cnt = 0;
		int tgt=exist[ai-1];
		rrep(j,1,sz(a[tgt])){
			if(a[tgt][j-1]==startIndex) {
				break;
			}
			if(a[tgt][j] > a[tgt][j-1]) cnt++;
		}
		if(cnt<2) return {0, actions};
		if(cnt < nxtTgt+1) return {0, actions};
		skips+= nxtTgt+1;
	}

	rep(i,startIndex,n){
		int tgt=exist[i];
		if(a[tgt].back() == i){
			act_put(i);
			continue;
		}
		int cnt=0;

		rrep(j,1,sz(a[tgt])){
			if(a[tgt][j-1]==i or (a[tgt][j] > a[tgt][j-1] and skips-- <= 0)) {
				cnt=j; break;
			}
		}

		int moveTo=0, bestDiff=INF;
		rep(j,m)if(j!=tgt){
			int diff=a[j].empty() ? -INF : a[j].back()-a[tgt][cnt];
			if(diff<0 and diff!=-INF) {
				diff = -diff + a[tgt].size() - cnt + threshold;
			}
			if(chmin(bestDiff,diff)) moveTo=j;
		}
		act_move(a[tgt][cnt], moveTo);
		if(a[tgt].back()==i){
			act_put(i);
		} else {
			i--;
		}
		if(score < ashikiri) {
			return {0, actions};
		}
	}
	return {score, actions};
}

int main() { /**/
	{def(int,_,__);}
	in(a_base);
	rep(i,m) rep(j,s) a_base[i][j]--;
	int bestScore = 0; Actions bestMove;
	int TbestScore = 0; Actions TbestMove;

	int bestThr = 0;
	rep(thr,1000){
		auto [score, move] = solve(a_base, thr, {});
		if(chmax(bestScore, score)) {
			bestMove = move;
			bestThr = thr;
		}
	}
	tie(TbestScore, TbestMove) = {bestScore, bestMove};

	int beforeIndex=-1, nxtTgt=-1;
	while(Mgr::timer){
		int index = (sz(bestMove)-10) * Mgr::timer.persentile();
		while(bestMove[index].second == 0) index--;
		auto defaultMove = bestMove; defaultMove.resize(index+1);
		++nxtTgt;
		if(beforeIndex!=index){
			beforeIndex=index;
			nxtTgt=0;
		}

		auto [score, move] = solve(a_base, nxtTgt/m, defaultMove, bestScore, nxtTgt%m);

		// double startTemp   =  0.0;
		// double endTemp     =  0;
		// double temp        = startTemp + (endTemp - startTemp) * Mgr::timer.persentile();
		// double probability = exp((score - bestScore) / temp);
		// bool FORCE_NEXT    = probability > Random(0.0, 1.0);

		if(bestScore < score ) { //or FORCE_NEXT
			// if(TbestScore < score) debug("Accepted!", TbestScore, bestScore, score, probability);
			bestScore = score;
			bestMove = move;
		}
		if(chmax(TbestScore, score)) TbestMove = move;

		if(!Mgr::timer) break;

		tie(score, move) = solve2(a_base, nxtTgt/5, defaultMove, bestScore, nxtTgt%5);

		if(bestScore < score ) { //or FORCE_NEXT
			// if(TbestScore < score) debug("Accepted!", TbestScore, bestScore, score, probability);
			bestScore = score;
			bestMove = move;
		}
		if(chmax(TbestScore, score)) TbestMove = move;

	}

	debug_f(bestScore, solveCount);
	for(auto [a,b]:bestMove) out(a,b);


}