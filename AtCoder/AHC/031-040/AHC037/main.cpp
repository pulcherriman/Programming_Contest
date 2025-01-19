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
	static const int TLE = 2000;
	static inline Timer timer = Timer(TLE-100);
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

#pragma message("use PBDS. Turn off _GLIBCXX_DEBUG.")
template<class T>class Compress{
	int _size;
	HashMap<T,int> _zip;
	vector<int> _unzip;
public:
	Compress(vector<T> in){
		sort(all(in));
		in.erase(unique(all(in)),in.end());
		_unzip.resize(_size=in.size());
		rep(i,_size){_unzip[_zip[in[i]] = i] = in[i];}
	}
	int size(){return _size;}
	int zip(T v){return _zip[v];}
	T unzip(int v){return _unzip[v];}
};

const int N=1000;
using Soda = pair<int,int>;
vector<Soda> sodaList(N);

void input() {
	def(int,_);
	rep(i,N) in(sodaList[i]);
}

auto solve(vector<Soda>&soda, vector<Soda> initialRelay, bool containRelays = false) {
	int n=soda.size();
	vector<Soda> relay(1, {0,0});
	for(auto&[x,y]:initialRelay) relay.pb({x,y});

	rep(i,n){
		int minDist = min(soda[i].first, soda[i].second);
		if(minDist == 0) continue;
		rep(j,n)if(i!=j){
			int dx = soda[i].first - soda[j].first;
			int dy = soda[i].second - soda[j].second;
			if(dx>=0 && dy>=0) chmin(minDist, dx+dy);
		}
		if(minDist == min(soda[i].first, soda[i].second)){
			if(soda[i].first < soda[i].second) relay.pb({0, soda[i].second});
			else relay.pb({soda[i].first, 0});
		}
	}

	int m=relay.size();

	vi parent(n+m, -1);
	vector<HashSet<int>> children(n+m);
	{
		rep(i,n){
			int minDist = 2000000001;
			rep(j,n)if(i!=j){
				int dx = soda[i].first - soda[j].first;
				int dy = soda[i].second - soda[j].second;
				if(dx>=0 && dy>=0) if(chmin(minDist, dx+dy)){
					parent[i] = j;
				}
			}
			rep(j,m){
				int dx = soda[i].first - relay[j].first;
				int dy = soda[i].second - relay[j].second;
				if(dx>=0 && dy>=0) if(chmin(minDist, dx+dy)){
					parent[i] = n+j;
				}
			}
		}
		rep(i,1,m){
			int minDist = 2000000001;
			rep(j,n){
				int dx = relay[i].first - soda[j].first;
				int dy = relay[i].second - soda[j].second;
				if(dx>=0 && dy>=0) if(chmin(minDist, dx+dy)){
					parent[n+i] = j;
				}
			}
			rep(j,m)if(i!=j){
				int dx = relay[i].first - relay[j].first;
				int dy = relay[i].second - relay[j].second;
				if(dx>=0 && dy>=0) if(chmin(minDist, dx+dy)){
					parent[n+i] = n+j;
				}
			}
		}

		rep(i,n+m)if(i!=n) children[parent[i]].insert(i);
	}
	auto calcCost = [&](int i, int threshold = 1) {
		vector<tuple<int,int,int>> candidateList;
		if(children[i].size() < 2) return candidateList;

		auto [x0, y0] = i<n ? soda[i] : relay[i-n];

		for(auto it1=children[i].begin(); it1!=children[i].end(); it1++){
			for(auto it2=it1; it2!=children[i].end(); it2++){
				if(it1 == it2) continue;
				auto [x1, y1] = *it1<n ? soda[*it1] : relay[*it1-n];
				auto [x2, y2] = *it2<n ? soda[*it2] : relay[*it2-n];
				int reduceCost = min(x1, x2)-x0 + min(y1, y2)-y0;
				if(reduceCost < threshold) continue;
				candidateList.eb(reduceCost, *it1, *it2);
			}
		}
		return candidateList;
	};

	set<tuple<int,int,int>> candidates;
	vector<vector<tuple<int,int,int>>> candidatesByIndex(n+m);

	rep(i,n+m){
		candidatesByIndex[i] = calcCost(i);
		candidates.insert(all(candidatesByIndex[i]));
	}
	while(candidates.size() > 4000) candidates.erase(candidates.begin());


	while(relay.size() < 4000) {
		auto [maxCost, c1, c2] = *candidates.rbegin();
		if(maxCost == 0) break;

		auto [x1, y1] = c1<n ? soda[c1] : relay[c1-n];
		auto [x2, y2] = c2<n ? soda[c2] : relay[c2-n];
		Soda newRelay = {min(x1, x2), min(y1, y2)};
		relay.pb(newRelay);
		m++;
		int newRelayIndex = n + m - 1;
		int selectedIndex = parent[c1];

		children.emplace_back();
		children[newRelayIndex].insert(c1);
		children[newRelayIndex].insert(c2);
		children[selectedIndex].erase(c1);
		children[selectedIndex].erase(c2);
		children[selectedIndex].insert(newRelayIndex);

		parent.push_back(selectedIndex);
		parent[c1] = newRelayIndex;
		parent[c2] = newRelayIndex;

		for(auto&t:candidatesByIndex[selectedIndex]) candidates.erase(t);
		// backから4000番目の値を取る
		candidatesByIndex[selectedIndex] = calcCost(selectedIndex, get<0>(*candidates.begin()));
		candidates.insert(all(candidatesByIndex[selectedIndex]));
		while(candidates.size() > 4000 - relay.size()) candidates.erase(candidates.begin());

		candidatesByIndex.emplace_back(calcCost(newRelayIndex, get<0>(*candidates.begin())));
		candidates.insert(all(candidatesByIndex[newRelayIndex]));	
		while(candidates.size() > 4000 - relay.size()) candidates.erase(candidates.begin());
	}

	{
		auto dfs = [&](auto self, int p) -> void {
			auto [x,y] = p<n ? soda[p] : relay[p-n];
			int minx=INF, miny=INF;
			if(children[p].empty()) return;
			for(auto&c : children[p]){
				auto [tx, ty] = c<n ? soda[c] : relay[c-n];
				chmin(minx, tx);
				chmin(miny, ty);
			}
			if(minx > x and miny > y) {
				m++;
				relay.eb(minx, miny);
				children.eb(children[p]);
				for(auto&c : children[p]){
					parent[c] = n+m-1;
				}
				children[p].clear();
				children[p].insert(n+m-1);
				parent.eb(p);
				self(self, n+m-1);
			}
		};
		dfs(dfs, n);
	}

	vi ignore(n+m, false);
	//dfsして、子がいないrelayを再帰的に削除
	auto dfs = [&](auto self, int p) -> void {
		bool hasChild = false;
		for(auto&c : children[p]) {
			self(self, c);
		}
		if(p<n) return;
		for(auto&c : children[p]) {
			if(!ignore[c]) hasChild = true;
		}
		if(!hasChild) ignore[p] = true;
	};
	dfs(dfs, n);
	
	queue<int> que; que.push(n);
	vector<tuple<int,int,int,int>> ans;
	ll cost = 0;
	while(!que.empty()){
		int p = que.front(); que.pop();
		if(ignore[p]) continue;
		auto [fx, fy] = p<n ? soda[p] : relay[p-n];
		for(auto&c : children[p]){
			if(ignore[c]) continue;
			auto [tx, ty] = c<n ? soda[c] : relay[c-n];
			ans.eb(fx, fy, tx, ty);
			cost += tx+ty - fx-fy;
			que.push(c);
		}
	}

	return make_pair(cost, ans);
}

vector<Soda> _initialRelay;
auto getInitialRelaysByLength() {
	if(_initialRelay.empty()){
		vector<tuple<int,int,int>> distList;
		rep(i,N){
			vector<tuple<int,int,int>> distListInner;
			rep(j,i){
				auto [x1,y1] = sodaList[i];
				auto [x2,y2] = sodaList[j];
				if(x1==0 or y1==0 or x2==0 or y2==0) continue;
				if((x1<x2 and y1>y2) or (x1>x2 and y1<y2)) {
					distListInner.emplace_back(abs(x1-x2) + abs(y1-y2), i,j);
				}
			}
			sort(all(distListInner));
			rep(j,2) if(j<distListInner.size()) distList.eb(distListInner[j]);
		}

		sort(all(distList));
		for(auto&[dist, p1, p2] : distList) {
			auto [x1,y1] = sodaList[p1];
			auto [x2,y2] = sodaList[p2];
			_initialRelay.emplace_back(min(x1,x2), min(y1,y2));
		}
	}
	return _initialRelay;
}

auto solveByInitialLength(int len, bool containRelays = false) {
	auto initialRelay = getInitialRelaysByLength();
	initialRelay.resize(len);
	return solve(sodaList, initialRelay, containRelays);
}

auto solveByTrinarySearch() {
	// cost は、下に凸の関数になるので三分探索で最小値を求める

	vector<tuple<ll,int,vector<tuple<int,int,int,int>>>> results;
	{
		int l=100, r = 1200;
		while(r-l>2) {
			int m1 = (l*2+r)/3;
			int m2 = (l+2*r)/3;
			auto [c1, _] = solveByInitialLength(m1);
			auto [c2, __] = solveByInitialLength(m2);
			results.eb(c1, m1, _);
			results.eb(c2, m2, __);
			if(c1 < c2) r = m2;
			else l = m1;
		}
	}

	return *min_element(all(results));
}

int main() {
	input();

	int lpCount = 0;

	auto [initialCost, initialLen, initialResult] = solveByTrinarySearch();
	auto bestResult = make_pair(initialCost, initialResult);
	vector<Soda> initialRelay = getInitialRelaysByLength();
	initialRelay.resize(initialLen);

	int relayLeft = 0;
	rep(i,initialRelay.size()) {
		auto [x,y] = initialRelay[i];
		if(x==0 or y==0) relayLeft++;
		else break;
	}

	while(Mgr::timer){
		lpCount++;
		if(lpCount % 2 == 0) {
			int i = Random(relayLeft, initialRelay.size());
			auto tgt = initialRelay[i];
			initialRelay.erase(initialRelay.begin() + i);
			auto tmp = solve(sodaList, initialRelay);
			if(!chmin(bestResult, tmp)) {
				initialRelay.push_back(tgt);
			}
		} else {
			int x = Random(0, 1000000000);
			int y = Random(0, 1000000000);

			initialRelay.eb(x, y);
			auto tmp = solve(sodaList, initialRelay);
			if(!chmin(bestResult, tmp)) {
				initialRelay.pop_back();
			}
		}
	}
	auto [cost, result] = bestResult;
	out(result.size());
	for(auto&[x1,y1,x2,y2] : result) out(x1,y1,x2,y2);

	debug(lpCount, cost);

}

// base:	997273043141	1002669
// greedy:	43850900145	22803065
// edge: 	Cost = 40384777401, Score = 24760194