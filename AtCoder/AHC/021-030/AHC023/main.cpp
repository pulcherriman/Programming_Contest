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
} Random(1);

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
	static inline Timer timer = Timer(TLE-20);
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


struct UnionFind{
	vi par;
	UnionFind(int x){par.assign(x,-1);}
	int find(int x){return par[x]<0?x:find(par[x]);}
	bool same(int x,int y){return find(x)==find(y);}
	int size(int x){return -par[find(x)];}
	bool unite(int x, int y){
		x=find(x); y=find(y);
		if(x==y)return false;
		if(size(x)<size(y)){swap(x,y);}
		par[x]+=par[y]; par[y]=x;
		return true;
	}
};

const int turn=100, n=20;
int door;
array<vector<int>, n*n> connect;

struct Crops {
	int crop;
	using Crop = pair<int, int>;
	vector<Crop> dates;
	array<vector<int>, turn> byStartDay;

	void input() {
		cin>>crop;
		rep(i, crop) {
			int s, d;
			cin>>s>>d;
			dates.eb(s-1, d-1);
			byStartDay[s-1].pb(i);
		}
		rep(i,turn){
			sort(all(byStartDay[i]), [&](int a, int b){
				return dates[a].second > dates[b].second;
			});
		}
	}
} crops;

array<int, n*n> field;

// 関節点の列挙
HashSet<int> getArticulationPoints() {
	HashSet<int> articulationPoints;
	vector<int> order(n*n);
	vector<int> low(n*n);
	vector<bool> visited(n*n);
	int ord = 0;

	const auto dfs = [&](auto&&dfs, int p, int prev) -> void{
		visited[p] = true;
		order[p] = ord++;
		low[p] = order[p];

		int cnt = 0;
		bool isArticulationPoint = false;
		for(auto&nxt : connect[p]) {
			if (field[nxt]) continue;
			if(!visited[nxt]) {
				cnt++;
				dfs(dfs, nxt, p);
				low[p] = min(low[p], low[nxt]);
				if (prev != -1 && order[p] <= low[nxt]) {
					isArticulationPoint = true;
				}
			} else if (nxt != prev) {
				low[p] = min(low[p], order[nxt]);
			}
		}
		if (prev == -1 && cnt > 1) {
			isArticulationPoint = true;
		}
		if (isArticulationPoint) {
			articulationPoints.insert(p);
		}
	};

	dfs(dfs, door, -1);
	return articulationPoints;
}


vector<array<int, 4>> actions;
// TODO: 終点早い順に400個、初日に全部埋める！みたいな　特定の関節点より先だけで適用するとか
// 植える
void place(int t){
	/**
	 * 作物Aを植えるとき、ある作物Bについて
	 *   - Aの方が収穫が早い（A.d < B.d）とき、
	 *     - Bは通行不可
	 *   - AとBの収穫日が同じ（A.d == B.d）とき、
	 *     - Bは通行可
	 *   - Aの方が収穫が遅い（A.d > B.d）とき、
	 *     - Bは通行可だが、Aを配置することでBを収穫できなくなる時、配置できない
	 * 収穫可能かどうかの判定
	 *   - Aが関節点であり、Aによって到達不能になる各作物について、その中で最も収穫が早い作物Bを考える
	 *     - A.d <= B.d なら収穫可能
	 *     - そうでない場合収穫不可能だが、Bの方が退場が早いので、Bの場所にAを置いて、Bを別の場所に配置するアプローチも？
	 *   - 最初は実装をサボって、関節点ならダメとしてしまってもいいかも
	 * 配置場所について
	 *   - 配置可能なすべての場所について、
	 *     - dが遅いほど"遠く"がいい
	 *       - 入り口からの距離より、始点から最初に到達する関節点からの距離の方が良さそう
	 *     - 関節点を増やさない方がいい
	 */
	const auto placeCrop = [&](int crop){
		const auto articulationPoints = getArticulationPoints();
		array<int, n*n> dist;
		dist.fill(-1);
		{
			queue<pair<int, int>> q;
			q.emplace(door, -1);
			while(!q.empty()){
				auto [p, d] = q.front(); q.pop();
				if(dist[p] != -1) continue;
				dist[p] = max(d, 0);
				for(auto&nxt : connect[p]){
					if(dist[nxt] != -1) continue;
					if(field[nxt]) continue;
					if(d==-1){
						if(articulationPoints.find(nxt) != articulationPoints.end()) q.emplace(nxt, 0);
						else q.emplace(nxt, -1);
					} else {
						q.emplace(nxt, d+1);
					}
					// q.emplace(nxt, d+1);
				}
			}

			rep(i,n*n) dist[i] = dist[i]*100 + Random(-3, 4);
		}

		const auto [s, d] = crops.dates[crop];

		vi targets;
		rep(i,n*n){
			if(field[i]==0 and dist[i] >= 0 and i!=door) targets.pb(i);
		}
		sort(all(targets), [&](int a, int b){
			if(dist[a] != dist[b]) return dist[a] > dist[b];
			return a > b;
		});

		map<int, vector<int>> cropMap;
		UnionFind __uf(n*n);
		rep(i,n*n){
			if(field[i]) {
				if(crops.dates[field[i]-1].second >= d) continue;
				cropMap[crops.dates[field[i]-1].second].pb(i);
			} else {
				for(auto&nxt : connect[i]){
					if(field[nxt]) continue;
					__uf.unite(i, nxt);
				}
			}
		}

		for(auto&p:targets){
			bool ok = articulationPoints.find(p) == articulationPoints.end();
			if(ok) {
				field[p] = crop+1;

				// 植えられている作物を回収日順にMap
				UnionFind uf = __uf;

				for(auto&[d2,cropList]: cropMap) {
					for(auto&r:cropList){
						for(auto&nxt : connect[r]){
							if(field[nxt] and crops.dates[field[nxt]-1].second > d2) [[likely]] continue;
							uf.unite(r, nxt);
						}
					}

					for(auto&r:cropList){
						ok &= uf.same(r, door);
						if(!ok) [[unlikely]] break;
					}
					if(!ok) [[unlikely]] break;
				}

				field[p] = 0;
			}

			if(ok) [[unlikely]] {
				return p;
			}
		}
		return -1;
	};

	for(auto&target: crops.byStartDay[t]){
		auto pos = placeCrop(target);
		if(pos == -1) continue;
		field[pos] = target+1;
		actions.pb({target+1, pos/n, pos%n, t+1});
	}
}

int harvest(int t){
	array<bool, n*n> visited;
	visited.fill(false);
	queue<int> q;
	q.push(door);

	int score = 0;

	while(!q.empty()){
		int p = q.front(); q.pop();
		if(visited[p]) continue;
		visited[p] = true;
		for(auto&nxt : connect[p]){
			if(visited[nxt]) continue;
			if(field[nxt]) {
				if (crops.dates[field[nxt]-1].second == t) {
					score += crops.dates[field[nxt]-1].second - crops.dates[field[nxt]-1].first + 1;
					field[nxt] = 0;
				}
			}
			if(field[nxt] == 0) {
				q.push(nxt);
			}
		}
	}

	rep(i,n*n) {
		if(field[i] and crops.dates[field[i]-1].second == t) {
			return -1;
		}
	}

	return score;
}


int main() {
	field.fill(0);

	{int _; cin>>_>>_>>_;}
	cin>>door;
	door *= n;

	// 横方向の壁 ---
	rep(i,n-1){
		string s; cin>>s;
		rep(j,n) if(s[j]=='0') {
			connect[i*n+j].pb((i+1)*n+j);
			connect[(i+1)*n+j].pb(i*n+j);
		}
	}

	// 縦方向の壁 |||
	rep(i,n){
		string s; cin>>s;
		rep(j,n-1) if(s[j]=='0') {
			connect[i*n+j].pb(i*n+j+1);
			connect[i*n+j+1].pb(i*n+j);
		}
	}

	// 作物
	crops.input();

	auto bestActions = actions;
	float bestScore = 0;

	const auto simulate = [&](){
		field.fill(0);
		actions.clear();
		int score = 0;
		rep(i,turn){
			place(i);
			auto result = harvest(i);
			if(harvest(i) == -1) {
				debug("harvest failed");
				break;
			}
			score += result;
		}
		return (1000000.0f * score / n / n / turn);
	};

	ull msec = 0, csec=0;
	while(true) {
		auto score = simulate();
		if(chmax(bestScore, score)) {
			bestActions = actions;
		}
		chmax(msec, Mgr::timer.get()-csec);
		csec = Mgr::timer.get();
		if(1950 - csec < msec + 10) break;
	}


	out(bestActions.size());
	for(auto&[crop, x, y, t] : bestActions) {
		out(crop, x, y, t);
	}
	debug(bestScore);
}