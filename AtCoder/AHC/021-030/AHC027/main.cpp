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
using ull=unsigned long long;
using vb=vector<bool>;
using vvb=vector<vb>;
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

#define all(a) a.begin(),a.end()
#define rall(a) rbegin(a),rend(a)
#define __LOOPSWITCH(_1, _2, _3, __LOOPSWITCH, ...) __LOOPSWITCH
#define rep(...) __LOOPSWITCH(__VA_ARGS__, __RANGE, __REP, __LOOP) (__VA_ARGS__)
#define rrep(...) __LOOPSWITCH(__VA_ARGS__, __RRANGE, __RREP, __LOOP) (__VA_ARGS__)
#define __LOOP(q) for([[maybe_unused]] int _lp ## __LINE__ : views::iota(0, q))
#define __LOOP2(q,l) __LOOP3(q,l)
#define __LOOP3(q,l) __REP(_lp ## l,q)
#define __REP(i,n) __RANGE(i,0,n)
#define __RANGE(i,a,n) for(int i=((ll)a);i<((ll)n);++i)
#define __RREP(i,n) __RRANGE(i,0,n)
#define __RRANGE(i,a,n) for(int i=((ll)(n)-1);i>=((ll)a);--i)
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
		uint_fast32_t lo,hi;
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
	static inline Timer timer = Timer(TLE-250);
	static inline Timer severeTimer = Timer(TLE-100);
	Mgr() {
		ios_base::sync_with_stdio(0); cin.tie(0);
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

int n;
#define C(i,j) ((i)*n+(j))

struct BitFlag {
	int n;
	vector<uint64_t> data;
	BitFlag(int _n): n(_n), data((_n+63)/64, 0) {}
	void set(int i) { data[i>>6] |= 1ull<<(i&63); }
	void reset(int i) { data[i>>6] &= ~(1ull<<(i&63)); }
	bool get(int i) { return data[i>>6]>>(i&63)&1; }
};

using UnWeightedGraph = vector< vector< int > >;
template< typename G >
struct LowLink {
	const G &g;
	vector< int > used, ord, low;
	vector< int > articulation;
	vector< pair< int, int > > bridge;
	
	LowLink(const G &g) : g(g) {}
	
	int dfs(int idx, int k, int par) {
		used[idx] = true;
		ord[idx] = k++;
		low[idx] = ord[idx];
		bool is_articulation = false;
		int cnt = 0;
		for(auto &to : g[idx]) {
			if(!used[to]) {
				++cnt;
				k = dfs(to, k, idx);
				low[idx] = min(low[idx], low[to]);
				is_articulation |= ~par && low[to] >= ord[idx];
				if(ord[idx] < low[to]) bridge.emplace_back(minmax(idx, (int) to));
			} else if(to != par) {
				low[idx] = min(low[idx], ord[to]);
			}
		}
		is_articulation |= par == -1 && cnt > 1;
		if(is_articulation) articulation.push_back(idx);
		return k;
	}
	
	virtual void build() {
		used.assign(g.size(), 0);
		ord.assign(g.size(), 0);
		low.assign(g.size(), 0);
		int k = 0;
		rep(i,g.size()) if(!used[i]) k = dfs(i, k, -1);
	}
};

template< typename G >
struct TwoEdgeConnectedComponents : LowLink< G > {
	using LL = LowLink< G >;
	vector< int > comp;
	vi representative;
	
	TwoEdgeConnectedComponents(const G &g) : LL(g) {}
	
	int operator[](const int &k) { return comp[k]; }
	
	void dfs(int idx, int par, int &k) {
		if(~par && this->ord[par] >= this->low[idx]) comp[idx] = comp[par];
		else comp[idx] = k++;
		for(auto &to : this->g[idx]) if(comp[to] == -1) dfs(to, idx, k);
	}
	
	HashMap<int, HashSet<int>> build(UnWeightedGraph &t) {
		LL::build();
		comp.assign(this->g.size(), -1);
		int k = 0;
		rep(i,comp.size()) if(comp[i] == -1) {
			representative.pb(i);
			dfs(i, -1, k);
		}
		t.resize(k);
		HashMap<int, HashSet<int>> bridge;
		for(auto &e : this->bridge) {
			int x = comp[e.first], y = comp[e.second];
			t[x].push_back(y);
			t[y].push_back(x);
			bridge[e.first].insert(e.second);
			bridge[e.second].insert(e.first);
		}

		return bridge;
	}
	
	tuple<UnWeightedGraph,HashMap<int,int>,vi> getPartialGraph(int idx) {
		UnWeightedGraph t;
		HashMap<int,int> zip; vi unzip;
		int k = 0;
		rep(i,comp.size()) if(comp[i] == idx) {
			zip[i] = k++;
			unzip.pb(i);
		}
		t.resize(k);
		for(auto &from : unzip) {
			for(auto &to : this->g[from]) {
				if(zip.contains(to)) {
					t[zip[from]].pb(zip[to]);
				}
			}
		}

		return {t, zip, unzip};
	}
};

vi emplacePath(vi path, int tgt, vi additional) {
	path.insert(path.begin()+tgt+1, all(additional));
	return path;
}

template< typename G >
struct ShortestTour {
	const G &g;
	
	ShortestTour(const G &g) : g(g) {}

	vi get(int start, HashMap<int,int> zip, vi unzip) { // unzipされたものを返す
		if(g.size() == 1) return {unzip[0]};
		vi path;
		// 最小の閉路を作る
		vi dist(g.size(), INF), prev(g.size(), -1);
		queue< int > que;
		que.emplace(start);
		dist[start] = 0;
		prev[start] = -1;
		while(!que.empty()) {
			int idx = que.front();
			que.pop();
			for(auto &to : g[idx]) {
				if(dist[to] > dist[idx] + 1) {
					dist[to] = dist[idx] + 1;
					prev[to] = idx;
					que.emplace(to);
				} else if(to != prev[idx]) {
					// 始点 ~ prev[idx] ~ idx ~ to ~ 始点 が閉路
					int cur = idx;
					while(cur != -1) {
						path.emplace_back(cur);
						cur = prev[cur];
					}
					reverse(all(path));
					cur = to;
					while(cur != -1) {
						path.emplace_back(cur);
						cur = prev[cur];
					}
					break;
				}
			}
			if(!path.empty()) break;
		}

		// pathは小さい閉路。これを拡張して全頂点を通る閉路を構築
		HashMap<int, HashSet<int>> edges;
		rep(i,g.size()) {
			for(auto&to:g[i]) {
				edges[unzip[i]].insert(unzip[to]);
			}
		}
		HashSet<int> unzippedIsland;
		for(auto&v:unzip) unzippedIsland.insert(v);
		HashSet<int> used;
		rep(i,path.size()) {
			used.insert(path[i] = unzip[path[i]]);
		}

		/**
		 * 12345 を 12367 にする
		 *            45
		 */
		int baseTgt = 0;
		while(used.size() != g.size()){
			{
				int tgt = baseTgt;
				while(tgt != sz(path)-1){
					auto e1 = path[tgt], e2 = path[tgt+1];

					vector<pair<int,int>> cand;
					if(abs(e1-e2) == 1) {
						if(e1/n+1 != n) cand.pb({e1+n,e2+n});
						if(e1/n != 0) cand.pb({e1-n,e2-n});
					} else {
						if(e1%n+1 != n) cand.pb({e1+1,e2+1});
						if(e1%n != 0) cand.pb({e1-1,e2-1});
					}
					bool ok=false;
					for(auto&[ne1,ne2] : cand) {
						if(!edges[e1].contains(ne1) || !edges[e2].contains(ne2)) continue;
						if(!edges[ne1].contains(ne2)) continue;
						if(!unzippedIsland.contains(ne1) || !unzippedIsland.contains(ne2)) continue;
						if(used.contains(ne1) || used.contains(ne2)) continue;
						path.insert(path.begin()+tgt+1, ne1);
						path.insert(path.begin()+tgt+2, ne2);
						used.insert(ne1);
						used.insert(ne2);
						ok=true;
						break;
					}
					if(!ok) tgt++;
				}
			}
			/**
			 * 12345 を 12(35)67 にする
			 *             4
			 */
			{
				int tgt = baseTgt;
				while(tgt != sz(path)){
					auto e1 = path[tgt];

					vector<int> cand;
					if(e1%n+1 != n) cand.pb(e1+1);
					if(e1%n != 0) cand.pb(e1-1);
					if(e1/n+1 != n) cand.pb(e1+n);
					if(e1/n != 0) cand.pb(e1-n);

					bool ok=false;
					for(auto& ne1 : cand) {
						if(!edges[e1].contains(ne1)) continue;
						if(!unzippedIsland.contains(ne1)) continue;
						if(used.contains(ne1)) continue;
						path.insert(path.begin()+tgt+1, ne1);
						path.insert(path.begin()+tgt+2, e1);
						used.insert(ne1);
						ok=true;
						break;
					}

					if(!ok) tgt++;
					else {
						baseTgt = tgt;
						break;
					}
				}
			}
		}
		
		return path;
	}
};

constexpr int CMAX = 1600;
BitFlag connectivity(6400);
const bool checkConnectivity(int a, int b) {
	if(a-b==1) return connectivity.get(a*4+3);
	if(a-b==-1) return connectivity.get(a*4+1);
	if(a-b==n) return connectivity.get(a*4+0);
	if(a-b==-n) return connectivity.get(a*4+2);
	return false;
}
vi dirtLv;
UnWeightedGraph g, contractG;
TwoEdgeConnectedComponents tecc(g);
vvi allDistance;

void input() {
	cin>>n;
	g.resize(n*n);
	dirtLv.resize(n*n);
	rep(i,n-1){
		def(string,s);
		rep(j,n) if(s[j]=='0') {
			g[C(i,j)].pb(C(i+1,j));
			g[C(i+1,j)].pb(C(i,j));
		}
	}
	rep(i,n){
		def(string,s);
		rep(j,n-1) if(s[j]=='0') {
			g[C(i,j)].pb(C(i,j+1));
			g[C(i,j+1)].pb(C(i,j));
		}
	}
	in(dirtLv);

	rep(i,n*n) {
		sort(all(g[i]), [&](int a, int b){
			return dirtLv[a] > dirtLv[b];
		});
		for(auto&to:g[i]) {
			if(i-to==1){
				connectivity.set(i*4+3);
				connectivity.set(to*4+1);
			}else if(i-to==-1){
				connectivity.set(i*4+1);
				connectivity.set(to*4+3);
			}else if(i>to){
				connectivity.set(i*4+0);
				connectivity.set(to*4+2);
			}else{
				connectivity.set(i*4+2);
				connectivity.set(to*4+0);
			}
		}
	}

	

}

string pathToStr(vi&path) {
	string ret;
	rep(i,path.size()-1) {
		const int x1 = path[i]/n, y1 = path[i]%n;
		const int x2 = path[i+1]/n, y2 = path[i+1]%n;
		if(x1 == x2) {
			if(y1 < y2) ret += 'R';
			else ret += 'L';
		} else {
			if(x1 < x2) ret += 'D';
			else ret += 'U';
		}
	}
	return ret;
}

int getDirtSum(vi tgts) {
	int dirtSum = 0;
	for(auto&i:tgts) dirtSum += dirtLv[i];
	return dirtSum;
}

vi getInitialPath() {
	auto connection = tecc.build(contractG);

	vi largePath;
	BitFlag used(contractG.size());
	
	vector<tuple<UnWeightedGraph, HashMap<int, int>, vi>> partialGraphs;
	rep(i,contractG.size()) {
		if(used.get(i)) continue;
		partialGraphs.pb(tecc.getPartialGraph(i));
	}

	function<void(int, int)> rec = [&](int cur, int start){
		used.set(cur);
		auto [t, zip, unzip] = partialGraphs[cur];
		auto path = ShortestTour(t).get(zip[start], zip, unzip);
		for(auto&v:path) {
			largePath.pb(v);

			if(connection.contains(v)) {
				// v から connection[v] に寄り道
				for(auto&to:connection[v]) {
					if(used.get(tecc.comp[to]))continue;
					rec(tecc.comp[to], to);
					largePath.pb(v);
				}
			}
		}
	};
	rec(0, 0);

	return largePath;
}

// array<int, 1600> firstVisit, lastVisit;
int calcScore(vi&path, ll uchikiri = -1) {
	const ll threshold = uchikiri == -1 ? LINF : uchikiri * 2ll * (sz(path) - 1);

	array<int, 1600> firstVisit{}, lastVisit;

	ll dirtSum = 0;
	rep(i,sz(path)-1){
		if(firstVisit[path[i]] == 0) firstVisit[path[i]] = i+1;
		else {
			const int t = i - lastVisit[path[i]];
			dirtSum += (ll)dirtLv[path[i]] * t * (t-1);
			if(dirtSum > threshold) {
				return INF;
			}
		}
		lastVisit[path[i]] = i;
	}
	rep(i,n*n){
		const int t = firstVisit[i]-1 + sz(path) - 1 - lastVisit[i];
		dirtSum += (ll)dirtLv[i] * t * (t-1);
		if(dirtSum > threshold) {
			return INF;
		}
	}
	return round(dirtSum / 2.0 / (sz(path) - 1));
}

tuple<int,int,int> getHeaviest(vi&path, int idx) {
	array<int, 1600> fv, lv;
	if(sz(path) <= idx+1) return {-1,-1,-1};
	fv.fill(-1);

	vector<tuple<ll,int,int,int>> heaviest; heaviest.reserve(sz(path)); 
	rep(i,sz(path)-1){
		if(fv[path[i]] == -1) fv[path[i]] = i;
		else {
			const int t = i - lv[path[i]];
			heaviest.emplace_back((ll)dirtLv[path[i]] * t * (t-1), path[i], lv[path[i]], i);
		}
		lv[path[i]] = i;
	}

	rep(i,n*n){
		int t = fv[i] + sz(path) - 1 - lv[i];
		heaviest.emplace_back((ll)dirtLv[i] * t * (t-1), i, lv[i], fv[i] + sz(path) - 1);
	}

	partial_sort(heaviest.begin(), heaviest.begin()+idx+1, heaviest.end(), greater<>());
	return {get<1>(heaviest[idx]), get<2>(heaviest[idx]), get<3>(heaviest[idx])};
}

constexpr int THRESHOLD = 10;
const bool checkExtendPath2(int a, int b, int c, int d) {
	return b!=-1 
	and (dirtLv[b] > THRESHOLD or dirtLv[c] > THRESHOLD)
	and checkConnectivity(a, b)
	and checkConnectivity(b, c)
	and checkConnectivity(c, d);
}

pair<bool, vi> extendPath2A(vi&path, int tgt) {
	if(tgt+1 >= sz(path)) return {false, {}};
	const int e1 = path[tgt], e2 = path[tgt+1]; int ne1 = -1, ne2 = -1;
	if(abs(e1-e2) == 1) {
		if(e1/n+1 != n) ne1 = e1+n, ne2 = e2+n;
	} else {
		if(e1%n+1 != n) ne1 = e1+1, ne2 = e2+1;
	}
	if(!checkExtendPath2(e1, ne1, ne2, e2)) return {false, {}};
	return {true, emplacePath(path, tgt, {ne1, ne2})};
}

pair<bool, vi> extendPath2B(vi&path, int tgt) {
	if(tgt+1 >= sz(path)) return {false, {}};
	const int e1 = path[tgt], e2 = path[tgt+1]; int ne1 = -1, ne2 = -1;
	if(abs(e1-e2) == 1) {
		if(e1/n != 0) ne1 = e1-n, ne2 = e2-n;
	} else {
		if(e1%n != 0) ne1 = e1-1, ne2 = e2-1;
	}
	
	if(!checkExtendPath2(e1, ne1, ne2, e2)) return {false, {}};
	return {true, emplacePath(path, tgt, {ne1, ne2})};
}

pair<bool, vi> shorterPath1(vi&path, int tgt) {
	if(tgt+1 >= sz(path)) return {false, {}};
	// 0(1320)45...を削除
	BitFlag st(n*n); int stc=0;

	int decidedNxt=-1, zero=-1;
	rep(i,sz(path)-1){
		int nxt=(tgt+i+1)%(sz(path)-1);
		if(decidedNxt!=-1) {
			if(!st.get(path[nxt])) stc++;
			st.set(path[nxt]);

			if(zero==-1 and path[nxt]==0) zero=nxt;
		} else if(path[nxt]==path[tgt]) decidedNxt=nxt;
	}
	if(decidedNxt==-1) return {false, {}};
	if(stc != n*n) return {false, {}};
	auto newPath = path;
	if(tgt > decidedNxt){
		newPath.erase(newPath.begin()+tgt+1, newPath.end());
		newPath.erase(newPath.begin(), newPath.begin()+decidedNxt+1);
		rotate(newPath.begin(), newPath.begin()+zero-decidedNxt-1, newPath.end());
		newPath.pb(0);
	}else{
		newPath.erase(newPath.begin()+tgt+1, newPath.begin()+decidedNxt+1);
	}
	return {true, newPath};
}

pair<bool, vi> shorterPath2(vi&path, int tgt) {
	if(tgt+4 > sz(path)) return {false, {}};
	// 012543を0143に
	if(abs(path[tgt]-path[tgt+3]) != 1 and abs(path[tgt]-path[tgt+3]) != n) return {false, {}};
	if(!checkConnectivity(path[tgt], path[tgt+3])) return {false, {}};

	BitFlag st(n*n); int stc=0;
	rep(i,sz(path)-1){
		if(i==tgt+1 or i==tgt+2) continue;
		if(!st.get(path[i])) stc++;
		st.set(path[i]);
		if(stc==n*n) break;
	}
	if(stc != n*n) return {false, {}};

	auto newPath = path;
	newPath.erase(newPath.begin()+tgt+1, newPath.begin()+tgt+3);
	return {true, newPath};
}


pair<bool, vi> shorterPath3(vi&path, int tgt) {
	if(tgt+1 >= sz(path)) return {false, {}};
	// 0(7326)145...を削除
	BitFlag st(n*n); int stc=0;

	int decidedNxt=-1, zero=-1;
	// rep(i,sz(path)-2){
	rep(i,sz(path)-4){
		if(i>=n*3 and decidedNxt==-1) return {false, {}};
		int nxt=(tgt+i+4)%(sz(path)-1);
		if(decidedNxt!=-1) {
			if(!st.get(path[nxt])) stc++;
			st.set(path[nxt]);
			if(zero==-1 and path[nxt]==0) zero=nxt;
			if(zero!=-1 and stc==n*n) break;
		} else if(path[nxt]!=path[tgt] and checkConnectivity(path[nxt],path[tgt])) {
			// out("!",sz(path), tgt,nxt,":",path[tgt],path[nxt]);
			decidedNxt=(nxt-2+sz(path))%(sz(path)-1);
			stc++;
			st.set(path[nxt]);
		}
	}
	if(decidedNxt==-1) return {false, {}};
	if(stc != n*n) return {false, {}};
	auto newPath = path;
	if(tgt > decidedNxt){
		newPath.erase(newPath.begin()+tgt+1, newPath.end());
		newPath.erase(newPath.begin(), newPath.begin()+decidedNxt+1);
		rotate(newPath.begin(), newPath.begin()+zero-decidedNxt-1, newPath.end());
		newPath.pb(0);
	}else{
		newPath.erase(newPath.begin()+tgt+1, newPath.begin()+decidedNxt+1);
	}

	return {true, newPath};
}

pair<bool, vi> shorterPath4(vi&path, int tgt) {
	if(tgt+1 >= sz(path)) return {false, {}};
	// (01320)45...を反転
	BitFlag st(n*n); int stc=0;

	int decidedNxt=-1, zero=-1;
	rep(i,sz(path)-3){
		int nxt=(tgt+i+3)%(sz(path)-1);
		if(decidedNxt!=-1) {
			if(!st.get(path[nxt])) stc++;
			st.set(path[nxt]);

			if(zero==-1 and path[nxt]==0) zero=nxt;
		} else {
			if(nxt==0) return {false, {}}; // 跨ぐ反転はめんどくさい
			if(path[nxt]==path[tgt]) {
				decidedNxt=nxt;
				{
					bool ok=false;
					rep(j,(decidedNxt-tgt)/2) if(path[tgt+j]!=path[decidedNxt-j]) {
						ok=true;
						break;
					}
					if(!ok) decidedNxt=-1;
				}
			}
		}
	}
	if(decidedNxt==-1) return {false, {}};
	if(stc != n*n) return {false, {}};
	auto newPath = path;	
	reverse(newPath.begin()+tgt, newPath.begin()+decidedNxt+1);
	return {true, newPath};
}

const bool checkExtendPath1(int a, int b) {
	return b!=-1 
	and dirtLv[b] > THRESHOLD
	and checkConnectivity(a, b);
}

pair<bool,vi> extendPath1A(vi&path, int tgt) {
	const int e1 = path[tgt], ne1 = e1+1;
	if(ne1%n==0 or !checkExtendPath1(e1, ne1)) return {false, {}};
	return {true, emplacePath(path, tgt, {ne1, e1})};
}

pair<bool,vi> extendPath1B(vi&path, int tgt) {
	const int e1 = path[tgt], ne1 = e1-1;
	if(e1%n==0 or !checkExtendPath1(e1, ne1)) return {false, {}};
	return {true, emplacePath(path, tgt, {ne1, e1})};
}

pair<bool,vi> extendPath1C(vi&path, int tgt) {
	const int e1 = path[tgt], ne1 = e1+n;
	if(e1/n+1==n or !checkExtendPath1(e1, ne1)) return {false, {}};
	return {true, emplacePath(path, tgt, {ne1, e1})};
}

pair<bool,vi> extendPath1D(vi&path, int tgt) {
	const int e1 = path[tgt], ne1 = e1-n;
	if(e1/n==0 or !checkExtendPath1(e1, ne1)) return {false, {}};
	return {true, emplacePath(path, tgt, {ne1, e1})};
}

const array Neighbor_Tier1 = {
	extendPath2A, extendPath2B,
};
const array Neighbor_Tier2 = {
	extendPath1A, extendPath1B, extendPath1C, extendPath1D,
};


HashMap<pair<int,int>, vi> shortestPathCache;
vi simpleShortestPath(int a, int b) {
	pii key{a,b};
	if(shortestPathCache.contains(key)) return shortestPathCache[key];
	vi path; path.reserve(n*n*2);
	queue<int> que;
	que.push(a);
	vi prev(n*n, -1);
	prev[a] = -2;
	while(!que.empty()) {
		int cur = que.front(); que.pop();
		if(cur == b) {
			while(cur != -2) {
				path.pb(cur);
				cur = prev[cur];
			}
			shortestPathCache[{b,a}] = path;
			reverse(all(path));
			return shortestPathCache[key] = path;
		}
		for(auto&to:g[cur]) {
			if(prev[to] != -1) continue;
			prev[to] = cur;
			que.push(to);
		}
	}
	return {};
}

auto getWeight(vi&path, int tgt, int mid) {
	// あるマスXで、tgtからXまでの距離D、Xに訪問した時間とmidの差が最小になる時間をTとする
	// Xに時刻Tに着いた時、tgtまで寄り道すると、2Dターンかかり、
	vi dist(n*n, INF);
	{
		queue<int> que;
		que.push(tgt);
		dist[tgt] = 0;
		while(!que.empty()) {
			int cur = que.front(); que.pop();
			for(auto&to:g[cur]) {
				if(dist[to] != INF) continue;
				dist[to] = dist[cur] + 1;
				que.push(to);
			}
		}
	}

	// TODO: mid時点から、xターン伸びると全体でいくら追加コストが生まれるかは計算が可能なはず
	int retVal=0, minVal = INF, DIST_WEIGHT = Random(30,100), DIFF_WEIGHT = Random(1,10);
	rep(i,sz(path)-1){
		if(chmin(minVal, dist[path[i]] * DIST_WEIGHT + min(abs(mid-i), abs(mid-i+sz(path))) * DIFF_WEIGHT)) retVal = i;
	}
	return retVal;
}

int main() {
	input();
	auto path = getInitialPath();
	int score = calcScore(path);

	bool modified = false;
	auto compare = [&](vi newPath) {
		int newScore = calcScore(newPath, score);
		if(chmin(score, newScore)) {
			score=	newScore;
			path = newPath;
			modified = true;
			return true;
		}
		return false;
	};

	// path.pop_back();
	// path.insert(path.end(), all(path));
	// path.push_back(0);

	while(Mgr::timer){
		modified = false;
		rep(i,sz(path)){
			for(auto&f:Neighbor_Tier1){
				auto [ok, newPath] = f(path, i);
				if(ok && compare(newPath)){
					i--;
					break;
				}
			}
		}
		if(!modified) break;
	}

	rep(5){
		auto bestScore = score;
		auto bestPath = path;
		rep(i,n*n)shuffle(all(g[i]), Random);
		path = getInitialPath();
		score = calcScore(path);
		while(Mgr::timer){
			modified = false;
			rep(i,sz(path)){
				for(auto&f:Neighbor_Tier1){
					auto [ok, newPath] = f(path, i);
					if(ok && compare(newPath)) {
						i--;
						break;
					}
				}
			}
			if(!modified) break;
		}
		if(!chmin(bestScore, score)) {
			path = bestPath;
			score = bestScore;
		}
	}

	rep(i,n*n)sort(all(g[i]), [&](int a, int b){
		return dirtLv[a] > dirtLv[b];
	});


	// 一番重いところを探して、一番重いrunの中間で切る

	int failed = 0, failed2 = 0, loopCnt = 0;
	while(Mgr::timer){
		auto bestScore = score;
		auto bestPath = path;

		auto [tgt, start, end] = getHeaviest(path, failed);
		if(tgt==-1)break;
		auto mid = ((start+end)/2+sz(path)) % sz(path);
		mid = getWeight(path, tgt, mid);

		// pathについて、mid番目を切る
		if(path[mid] == tgt) continue;
		auto addPath = simpleShortestPath(path[mid], tgt);
		if(sz(addPath)>2) addPath.insert(addPath.end(), addPath.rbegin()+1, addPath.rend()-1);
		path.insert(path.begin()+mid, all(addPath));

		score = calcScore(path);
		loopCnt++;

		vi totalVisited;
		rep(i,sz(path)) if(path[i]==tgt) totalVisited.pb(i);

		while(Mgr::timer){
			modified = false;
			int l = mid-n*3, r = mid+n*n/4;
			if(l>r) swap(l,r);
			// TODO:first,lastをこっちで保持？
			rep(_i,l,r){
				if(!Mgr::timer) break;
				int i=(_i+sz(path))%sz(path);
				for(auto&f:Neighbor_Tier1){
					auto [ok, newPath] = f(path, i);
					if(ok && compare(newPath)) {
						_i--;
						break;
					}
				}
			}
			if(!Mgr::timer) break;
			l = mid-n*3 + sz(path)/2, r = mid+n*n/4 + sz(path)/2;
			if(l>r) swap(l,r);
			rep(_i,l,r){
				if(!Mgr::timer) break;
				int i=(_i+sz(path))%sz(path);
				for(auto&f:Neighbor_Tier1){
					auto [ok, newPath] = f(path, i);
					if(ok && compare(newPath)) {
						_i--;
						break;
					}
				}
			}
			if(!Mgr::timer) break;
			if(!modified) break;
		}

		if(chmin(bestScore, score)) {
			failed = 0;

			while(Mgr::timer){
				modified = false;
				rep(i,sz(path)-3){
					if(!Mgr::timer) break;
					auto [ok, newPath] = shorterPath3(path, i);
					if(ok && compare(newPath)) {
						i--;
					}
				}
				if(!modified) break;
			}
			// while(Mgr::timer){
			// 	modified = false;
			// 	rep(i,sz(path)-3){
			// 		if(!Mgr::timer) break;
			// 		auto [ok, newPath] = shorterPath1(path, i);
			// 		if(ok && compare(newPath)) {
			// 			i--;
			// 		}
			// 	}
			// 	if(!modified) break;
			// }
			while(Mgr::timer){
				modified = false;
				rep(i,sz(path)-3){
					if(!Mgr::timer) break;
					auto [ok, newPath] = shorterPath2(path, i);
					if(ok && compare(newPath)) {
						i--;
					}
				}
				if(!modified) break;
			}
			while(Mgr::timer){
				modified = false;
				rep(i,sz(path)){
					if(!Mgr::timer) break;
					auto [ok, newPath] = shorterPath4(path, i);
					if(ok && compare(newPath)) {
						// i--;
					}
				}
				if(!modified) break;
			}

			bestPath = path;
		}else{
			failed++;
			score = bestScore;
			path = bestPath;
		}
	}

	while(Mgr::severeTimer){
		modified=false;
		rep(i,sz(path)-3){
			if(!Mgr::severeTimer) break;
			auto [ok, newPath] = shorterPath1(path, i);
			if(ok && compare(newPath)) i--;
		}
		if(!modified) break;
	}
	
	while(Mgr::severeTimer){
		modified=false;
		rep(i,sz(path)){
			for(auto&f:Neighbor_Tier1){
				if(!Mgr::severeTimer) break;
				auto [ok, newPath] = f(path, i);
				if(ok && compare(newPath)) {
					i--;
					break;
				}
			}
			if(!Mgr::severeTimer) break;
		}
		if(!modified) break;
	}

	while(Mgr::severeTimer){
		modified=false;
		rep(i,sz(path)){
			for(auto&f:Neighbor_Tier2){
				if(!Mgr::severeTimer) break;
				auto [ok, newPath] = f(path, i);
				if(ok && compare(newPath)) {
					i--;
					break;
				}
			}
			if(!Mgr::severeTimer) break;
		}
		if(!modified) break;
	}

	while(Mgr::severeTimer){
		modified=false;
		rep(i,sz(path)-3){
			if(!Mgr::severeTimer) break;
			auto [ok, newPath] = shorterPath2(path, i);
			if(ok && compare(newPath)) i--;
		}
		if(!modified) break;
	}
	while(Mgr::severeTimer){
		modified = false;
		rep(i,sz(path)){
			if(!Mgr::severeTimer) break;
			auto [ok, newPath] = shorterPath4(path, i);
			if(ok && compare(newPath)) {
				// i--;
			}
		}
		if(!modified) break;
	}
	
	out(pathToStr(path));
	debug_f(loopCnt, score);
}