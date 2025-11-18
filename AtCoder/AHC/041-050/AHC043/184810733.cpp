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
// #undef _DEBUG
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
	uint64_t get() const { return (getClocks()-start)/ClocksPerMsec; }
	operator bool() const { return getClocks()<limit; }
	float persentile() const { return (float)get()/limit; }
};
void wait(const int&msec){Timer tm(msec); while(tm);}

struct Mgr {
	#ifdef _DEBUG
	static const int TLE = 3000;
	#else
	static const int TLE = 3000;
	#endif
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


template<class T=int>
struct UnionFind{
	vi par, sample; vector<T> dist;
	UnionFind(int x){par.assign(x,-1); dist.assign(x,T());}
	int find(int x) { return par[x] < 0 ? x : par[x] = find(par[x]); }
	T depth(int x){return par[x]<0?T():depth(par[x])+dist[x];}
	bool same(int x,int y){return find(x)==find(y);}
	int size(int x){return -par[find(x)];}
	T diff(int x,int y){return same(x,y)?depth(x)-depth(y):LINF;}
	bool unite(int x, int y, T k=T()){
		k+=depth(y); k-=depth(x); k=-k;
		x=find(x); y=find(y);
		if(x==y)return false;
		if(size(x)<size(y)){swap(x,y);k=-k;}
		if(size(x)==1 and size(y)==1) sample.push_back(x);
		par[x]+=par[y]; par[y]=x; dist[y]=k;
		return true;
	}
	HashMap<int,vi> groups(){
		HashMap<int,vi> ret;
		rep(i,par.size()) ret[find(i)].push_back(i);
		return ret;
	}
};


const int N=50, T=800;
int M,K;

struct Person {
	int sx,sy,tx,ty;
	bool connected = false;
	int income;
	int dist;
	int id;
};

vector<Person> people;

const pair<int,int> neighbor[] = {
	{-2,0},
	{-1,-1},
	{-1,0},
	{-1,1},
	{0,-2},
	{0,-1},
	{0,0},
	{0,1},
	{0,2},
	{1,-1},
	{1,0},
	{1,1},
	{2,0}
};

vector<pair<int,int>> stations;
array<array<vector<pair<int,int>>,N>,N> reachableStations;
void decideStations() {
	if(!stations.empty()) return;
	array<array<bool,N>,N> exist;
	array<array<vector<int>,N>,N> neighbors;
	rep(i,M){
		exist[people[i].sy][people[i].sx]=true;
		exist[people[i].ty][people[i].tx]=true;
	}
	
	rep(i,N)rep(j,N) {
		stations.push_back({i,j});
		// if(exist[i][j]){
			for(auto&[dy,dx]:neighbor){
				int ny=i+dy,nx=j+dx;
				if(ny<0 || nx<0 || ny>=N || nx>=N) continue;
				reachableStations[ny][nx].push_back(stations.back());
			}
		// }
	}

	array<array<int,N>,N> reachablePeopleCount;
	for(auto&p:people){
		for(auto&[ny,nx]:reachableStations[p.sy][p.sx]){
			reachablePeopleCount[ny][nx]++;
		}
		for(auto&[ny,nx]:reachableStations[p.ty][p.tx]){
			reachablePeopleCount[ny][nx]++;
		}
	}

	rep(i,N)rep(j,N){
		sort(rall(reachableStations[i][j]), [&](const auto&a, const auto&b){
			return reachablePeopleCount[a.first][a.second] < reachablePeopleCount[b.first][b.second];
		});
	}
}
int totalIncome;

enum RAILS {ERR=-1, EMPTY, STATION, LR, UD, LD, LU, RU, RD};

const string rails[] = {" ", "■", "━", "┃","┓",  "┛", "┗", "┏"};
const vector<pair<int,int>> railNeighbor[] = {
	{},
	{{0,1},{0,-1},{1,0},{-1,0}},
	{{0,1},{0,-1}},
	{{1,0},{-1,0}},
	{{0,-1},{1,0}},
	{{0,-1},{-1,0}},
	{{0,1},{-1,0}},
	{{0,1},{1,0}}
};
// (y1,x1) ~ (y2,x2) ~ (y3,x3) をつなぐために、(y2,x2) に置くべきレールの種類を返す
RAILS getRailType(int y1, int x1, int y2, int x2, int y3, int x3) {
	int d12 = abs(y1-y2)+abs(x1-x2);
	int d23 = abs(y2-y3)+abs(x2-x3);
	if(d12!=1 || d23!=1 || (y1==y3 && x1==x3)) return ERR;
	if(y1==y3){
		return RAILS::LR;
	}else if(x1==x3){
		return RAILS::UD;
	}else {
		if(y1>y3){
			swap(y1,y3);
			swap(x1,x3);
		}
		bool up = y1 < y2 || y3 < y2;
		bool left = x1 < x2 || x3 < x2;
		if(up && left) return RAILS::LU;
		bool right = x1 > x2 || x3 > x2;
		if(up && right) return RAILS::RU;
		bool down = y1 > y2 || y3 > y2;
		if(down && left) return RAILS::LD;
		if(down && right) return RAILS::RD;
		return ERR;
	}
}

array<array<int,N>,N> field;
int bestFinalScore = -1;
vector<tuple<int,int,int>> actions, bestActions(0), _actions;
UnionFind uf(N*N);
vector<pair<int,int>> placedStations;
array<vector<int>,N*N> reachablePlacedStations;
enum STATE_TYPE {SAVE, LOAD, DIFF};

inline bool isMargin() {
	return (totalIncome > 5000 || K >= 100000) and _actions.size() <= 650;
}

auto keepState(STATE_TYPE type) {
	static auto _field = field;
	static auto _uf = uf;
	static auto _placedStations = placedStations;
	static auto _reachablePlacedStations = reachablePlacedStations;
	if(type == SAVE){
		_field = field;
		// ここで候補を確定
		int cnt = actions.size() - _actions.size();
		if(totalIncome >= 5000 || K >= cnt * 100 + 20000) {
			_actions = actions;
		} else {
			rep(i,cnt){
				auto act = actions.back();
				actions.pop_back();
				_actions.push_back(act);
			}
			actions = _actions;
		}
		_uf = uf;
		_placedStations = placedStations;
		_reachablePlacedStations = reachablePlacedStations;

		int finalScore = K + (T-actions.size()+1)*totalIncome;
		if(chmax(bestFinalScore, finalScore)){
			bestActions = actions;
		}
		
		return 0;
	}else if(type == LOAD){
		field = _field;
		actions = _actions;
		uf = _uf;
		placedStations = _placedStations;
		reachablePlacedStations = _reachablePlacedStations;
		return 0;
	} else if(type == DIFF){
		int cost = totalIncome;
		rep(i,_actions.size(), actions.size()){
			auto [type, y, x] = actions[i];
			if(type == STATION){
				cost += 5000 - totalIncome;
			}else{
				cost += 100 - totalIncome;
			}
		}
		return cost;
	} else return 0;
}

void printField() {
#ifdef _DEBUG
	cout<<"vvvvvvvvvv"<<endl;
	rep(i,N){
		rep(j,N){
			cout<<rails[field[i][j]];
		}
		cout<<endl;
	}
	cout<<"^^^^^^^^^^"<<endl;
#endif
}

inline void placeWait(int cnt) {
	actions.insert(actions.end(), cnt, {EMPTY, 0, 0});
}

inline bool isRailOk(int y, int x, int ny, int nx) {
	constexpr int mask_down  = (1 << 3) | (1 << 5) | (1 << 6);
	constexpr int mask_up    = (1 << 3) | (1 << 4) | (1 << 7);
	constexpr int mask_right = (1 << 2) | (1 << 5) | (1 << 4);
	constexpr int mask_left  = (1 << 2) | (1 << 6) | (1 << 7);
	if(field[ny][nx]==STATION) return true;
	if(ny-y==1) return (mask_down >> field[ny][nx]) & 1;
	if(ny-y==-1) return (mask_up >> field[ny][nx]) & 1;
	if(nx-x==1) return (mask_right >> field[ny][nx]) & 1;
	if(nx-x==-1) return (mask_left >> field[ny][nx]) & 1;
	return false;
}

bool placeItem(int y, int x, RAILS type) {
	if(type==STATION){
		if(field[y][x]==STATION) return false;
		placedStations.emplace_back(y,x);
		for(auto&[dy,dx]:neighbor){
			int ny=y+dy,nx=x+dx;
			if(ny<0 || nx<0 || ny>=N || nx>=N) continue;
			reachablePlacedStations[ny*N+nx].push_back(y*N+x);
		}
	}else{
		if(field[y][x]!=EMPTY) return false;
	}

	actions.emplace_back(type, y, x);
	field[y][x]=type;

	for(auto&[dy,dx]:railNeighbor[type]){
		int ny=y+dy,nx=x+dx;
		if(ny<0 || nx<0 || ny>=N || nx>=N) continue;
		if(isRailOk(y,x,ny,nx)) uf.unite(y*N+x,ny*N+nx);
	}

	return true;
}

// 座標(y,x)をカバーする駅を候補から選び、必要なら設置し、座標を返す
pair<bool, pair<int,int>> setStations(int y, int x){
	const auto&sta = reachableStations[y][x];
	for(auto&[ny,nx]:sta){
		if(field[ny][nx]==RAILS::STATION) {
			return make_pair(false, pii{ny,nx});
		}
	}
	const auto selectedStation = sta[0];
	const auto placed = placeItem(selectedStation.first,selectedStation.second,RAILS::STATION);
	return make_pair(placed, selectedStation); // TODO: 最適な駅の選び方があるかも
}



// (sy,sx)から(ty,tx)へ線路を引く。既存の線路は上書きできない
bool createRailway(int sy, int sx, int ty, int tx) {
    const int size = N * N;
    // 各セルの距離（未到達なら INF）と直前セルを管理する配列
    vector<int> pr(size, -1);
    int start = sy * N + sx;
    int target = ty * N + tx;
    
    // 座標変換用のテーブル (pos[i] = {i/N, i%N}) を static に事前計算
    static bool posInitialized = false;
    static vector<pii> pos;
    if (!posInitialized) {
        pos.resize(size);
        for (int i = 0; i < size; i++) {
            pos[i] = { i / N, i % N };
        }
        posInitialized = true;
    }
	array<array<int,N>,N> fromNearestStation;
	{
		rep(i,N)rep(j,N) fromNearestStation[i][j] = INF;
		queue<int> que;
		for(auto&[y,x]:placedStations){
			que.push(y*N+x);
			fromNearestStation[y][x] = 0;
		}
		while(!que.empty()){
			int p = que.front(); que.pop();
			int y = p/N, x = p%N;
			for(auto&[dy,dx]:railNeighbor[STATION]){
				int ny=y+dy,nx=x+dx;
				if(ny<0 || nx<0 || ny>=N || nx>=N) continue;
				if(chmin(fromNearestStation[ny][nx], fromNearestStation[y][x]+1)){
					que.push(ny*N+nx);
				}
			}
		}
		// rep(i,N)rep(j,N) fromNearestStation[i][j];
	}


    minpq<tuple<int, int, int>> que;
    que.emplace(0,start,start);

	auto stationsGroups = uf.groups();
	HashMap<int,bool> stationsSearched;

    while (!que.empty()) {
        auto [w,prev,p] = que.top();
        que.pop();
		if(pr[p] != -1) continue;
		pr[p] = prev;
        if (p == target) break;

        int y = pos[p].first, x = pos[p].second;
        
        // 駅セルの場合、全体の placedStations を走査する
        if (field[y][x] == STATION && !stationsSearched.contains(uf.find(p))) {
			stationsSearched[uf.find(p)] = true;
            for (auto &idx : stationsGroups[uf.find(p)]) {
                if (uf.same(p, idx) && pr[idx] == -1) {
                    que.emplace(w, p, idx);
                }
            }
        }
        
        const auto &adj = (field[y][x] == EMPTY ? railNeighbor[1] : railNeighbor[field[y][x]]);
        for (auto &dir : adj) {
            int ny = y + dir.first, nx = x + dir.second;
            if (ny < 0 || nx < 0 || ny >= N || nx >= N) continue;
            int np = ny * N + nx;
            if (pr[np] != -1) continue;
            if (field[y][x] == STATION && field[ny][nx] != EMPTY && field[ny][nx] != STATION)
                continue;
            if (field[ny][nx] == EMPTY) {
                que.emplace(w + 10000 - fromNearestStation[ny][nx], p, np);
                continue;
            }

            if (isRailOk(y, x, ny, nx)) {
                que.emplace(w, p, np);
            }else {
				if(isMargin()){
					que.emplace(w + 10000 - fromNearestStation[ny][nx], p, np);
				}
			}
        }
    }
	
    if (pr[target] == -1) return false;
    
    // 経路復元：target から start まで pr[] をたどる
    int p_idx = target;
    pii prevPos = {-1, -1};
    while (p_idx != start) {
        int y = pos[p_idx].first, x = pos[p_idx].second;
        int pprev = pr[p_idx];
        int py = pos[pprev].first, px = pos[pprev].second;
        if (prevPos.first != -1) {
            RAILS type = getRailType(prevPos.first, prevPos.second, y, x, py, px);
            if (type == ERR) {
                prevPos = {y, x};
                p_idx = pprev;
                continue;
            }

            if (field[y][x] != EMPTY and field[y][x] != type) {
				if(field[y][x] != STATION) {
	                placeItem(y, x, STATION);
					for(auto&[dy,dx]:neighbor){
						int ny=y+dy,nx=x+dx;
						if(ny<0 || nx<0 || ny>=N || nx>=N) continue;
						fromNearestStation[ny][nx] = 0;
					}
				}
            } else {
				bool near_white = false;
				for(auto&[dy,dx]:neighbor){
					int ny=y+dy,nx=x+dx;
					if(ny<0 || nx<0 || ny>=N || nx>=N) continue;
					if(fromNearestStation[ny][nx]>=3){
						near_white = true;
						break;
					}
				}
				// if(isMargin() and near_white){
				// 	placeItem(y, x, STATION);
				// 	for(auto&[dy,dx]:neighbor){
				// 		int ny=y+dy,nx=x+dx;
				// 		if(ny<0 || nx<0 || ny>=N || nx>=N) continue;
				// 		fromNearestStation[ny][nx] = 0;
				// 	}
				// } else {
					placeItem(y, x, type);
				// }
			}
        }
        prevPos = {y, x};
        p_idx = pprev;
    }
    return true;
}



// 既存の線路を壊さずに、(sy,sx)から(ty,tx)へ線路を引く
// 既につながっている駅間は移動できる
bool applyDoubleStation = true;
bool connect(int sy, int sx, int ty, int tx) {
	const auto [sPlaced, sSta] = setStations(sy,sx);
	const auto [tPlaced, tSta] = setStations(ty,tx);
	// 既に線路があるのに、別の路線を作るのはNG
	if(!applyDoubleStation and sPlaced && tPlaced){
		return false;
	}
	return createRailway(sSta.first,sSta.second,tSta.first,tSta.second);
}

// createRailwayをシミュレーションし、ufとactionsの長さだけ正しい状態にして、引くレールの長さを返す
pair<int,int> createRailway_simulate(int sy, int sx, int ty, int tx) {
    const int size = N * N;
    // 各セルの距離（未到達なら INF）と直前セルを管理する配列
    vector<int> d(size, INF);
    vector<int> d_sta(size, INF);
    vector<int> pr(size, -1);
    int start = sy * N + sx;
    int target = ty * N + tx;
    d[start] = 0;
	d_sta[start] = 0;
	pr[start] = start;
    
    // 座標変換用のテーブル (pos[i] = {i/N, i%N}) を static に事前計算
    static bool posInitialized = false;
    static vector<pii> pos;
    if (!posInitialized) {
        pos.resize(size);
        for (int i = 0; i < size; i++) {
            pos[i] = { i / N, i % N };
        }
        posInitialized = true;
    }

	auto stationsGroups = uf.groups();
	HashMap<int,bool> stationsSearched;

    deque<int> que;
    que.push_back(start);
	vb popd(size, false);
    
    while (!que.empty()) {
        int p = que.front();
        que.pop_front();
        if (p == target) break;
		if(popd[p]) continue;
		popd[p] = true;


        int y = pos[p].first, x = pos[p].second;
		int pr_compressed = field[y][x] == STATION ? p : pr[p];

        // 駅セルの場合、全体の placedStations を走査する
        if (field[y][x] == STATION && !stationsSearched.contains(uf.find(p))) {
			stationsSearched[uf.find(p)] = true;
            for (auto &idx : stationsGroups[uf.find(p)]) {
                if (uf.same(p, idx) && d[idx] == INF) {
                    d[idx] = d[p]; // コストは 0
					d_sta[idx] = d_sta[p];
                    pr[idx] = pr_compressed;
					if(idx==target) goto LABEL_746;
                    que.push_front(idx);
                }
            }
        }
        
        const auto &adj = (field[y][x] == EMPTY ? railNeighbor[1] : railNeighbor[field[y][x]]);
        for (auto &dir : adj) {
            int ny = y + dir.first, nx = x + dir.second;
            if (ny < 0 || nx < 0 || ny >= N || nx >= N) continue;
            int np = ny * N + nx;
            if (d[np] != INF) continue;
            if (field[y][x] == STATION && field[ny][nx] != EMPTY && field[ny][nx] != STATION)
                continue;
            if (field[ny][nx] == EMPTY) {
                d[np] = d[p] + 1;
				d_sta[np] = d_sta[p];
                pr[np] = pr_compressed;
                que.push_back(np);
                continue;
            }

            if (isRailOk(y, x, ny, nx)) {
                d[np] = d[p];
				d_sta[np] = d_sta[p];
                pr[np] = pr_compressed;
				if(np==target) goto LABEL_746;
                que.push_front(np);
            } else if(isMargin()){
				d[np] = d[p]+1;
				d_sta[np] = d_sta[p]+1;
				pr[np] = pr_compressed;
				que.push_back(np);
			}
        }
    }
	LABEL_746:
    if (d[target] == INF) return {INF, INF};

    int p_idx = target;
    while (p_idx != start) {
        int pprev = pr[p_idx];
		uf.unite(p_idx, pprev);
        p_idx = pprev;
    }
	placeWait(d[target]);

    return {d[target], d_sta[target]};
}


// 既存の線路を壊さずに、(sy,sx)から(ty,tx)へ線路を引く
// 既につながっている駅間は移動できる
int connect_sim(int sy, int sx, int ty, int tx) {
	auto [sPlaced, sSta] = setStations(sy,sx);
	auto [tPlaced, tSta] = setStations(ty,tx);
	// 既に線路があるのに、別の路線を作るのはNG
	if(!applyDoubleStation and sPlaced && tPlaced){
		return INF;
	}
	if(sPlaced) {
		swap(sy,ty);
		swap(sx,tx);
		swap(sPlaced, tPlaced);
		swap(sSta, tSta);
	}

	auto [turn, station] = createRailway_simulate(sSta.first,sSta.second,tSta.first,tSta.second);
	if(turn==INF) return INF;
	return ((turn-station) * 100 + (station + sPlaced + tPlaced) * 5000) - totalIncome * (turn + sPlaced + tPlaced - 1);
}

// 線路がつなげるかは考えず、繋いだ時のuf構造と、だいたいの線路の長さを返す (income, turn)
pair<int, int> unstrictly_connect_sim(int sy, int sx, int ty, int tx) {
	const auto [sPlaced, sSta] = setStations(sy,sx);
	const auto [tPlaced, tSta] = setStations(ty,tx);

	// 初手で遠すぎるときはNG
	if(_actions.empty()){
		const int cost = (abs(sSta.first-tSta.first)+abs(sSta.second-tSta.second)-1)*100 + 10000;
		if(K<cost) return {INF, INF};
	}

	// 既に線路があるのに、別の路線を作るのはNG
	if(!applyDoubleStation and sPlaced && tPlaced){
		return {INF, INF};
	}

	const int sStaIdx = sSta.first*N+sSta.second;
	const int tStaIdx = tSta.first*N+tSta.second;
	for(auto&st:uf.sample) {
		uf.unite(st, sStaIdx);
	}
	uf.unite(sStaIdx, tStaIdx);

	int sDist = INF, tDist = INF;
	for(auto&st:placedStations){
		const int idx = st.first*N+st.second;
		if(idx!=sStaIdx && idx!=tStaIdx){
			chmin(sDist, abs(st.first-sSta.first)+abs(st.second-sSta.second));
			chmin(tDist, abs(st.first-tSta.first)+abs(st.second-tSta.second));
		}
	}

	int rail = abs(sSta.first-tSta.first)+abs(sSta.second-tSta.second)-1;
	if(sDist != INF) chmin(rail, sPlaced * sDist + tPlaced * tDist);
	int turn = rail + sPlaced + tPlaced;

	return make_pair((rail * 100 + (sPlaced + tPlaced) * 5000) - totalIncome * (rail + sPlaced + tPlaced - 1), turn);
}

float calcScore(int addIncome, int remainTurn, int requireTurn) {
	// return addIncome * remainTurn / sqrt(requireTurn);
	if(totalIncome <= 500) {
		return addIncome;
	}else {
		return addIncome / pow(requireTurn, 1);
	}
}

int main() {
	{
		int _, __;
		cin>>_>>M>>K>>__;

		people.resize(M);
		rep(i,M){
			cin>>people[i].sy>>people[i].sx>>people[i].ty>>people[i].tx;
			people[i].income=abs(people[i].sx-people[i].tx)+abs(people[i].sy-people[i].ty);
			people[i].id = i;
		}
		rep(i,N)rep(j,N) field[i][j]=EMPTY;
	}

	decideStations();
	
	sort(rall(people),[](const Person&a,const Person&b){
		return a.income<b.income;
	});

	int maximumScoreCost = INF;
	float maximumScore = -INF;
	int warningCount = 0;
	while(actions.size() < T) {
		int tm = Mgr::timer.get();

		debug("start turn:", actions.size(), K, "/ (+", totalIncome,")");
		// 前ターン、終了しなかった
		if(maximumScore!=-INF){
			int remain = maximumScoreCost - K;
			int waitCount = (remain + totalIncome - 1) / totalIncome;
			debug("force wait", maximumScoreCost, remain, waitCount);
			placeWait(waitCount);
			K += waitCount * totalIncome;
			keepState(SAVE);
			maximumScoreCost = INF;
			maximumScore = -INF;
			// continue;
		}

		bool decided = false;
		
		maximumScore = -INF;
		maximumScoreCost = INF;

		keepState(SAVE);
		// int _c=0;
		// auto tm = Mgr::timer.get();

		float bestIncome = -1;
		Person* bestPerson = nullptr;

		// peopleをunstrictly_connect_sim(p.sy,p.sx,p.ty,p.tx)の昇順にソート
		HashMap<int,int> peopleCost, peopleTurn;
		HashMap<int,float> peopleScore;
		for(auto&p:people){
			tie(peopleCost[p.id], peopleTurn[p.id]) = unstrictly_connect_sim(p.sy,p.sx,p.ty,p.tx);
			if(peopleCost[p.id]==INF) {
				peopleScore[p.id] = -INF;
				keepState(LOAD);
				continue;
			}

			int addIncome = p.income;
			for(auto&p2:people){// 1600
				if(p2.connected || p.id==p2.id) continue;
				for(auto&ss:reachablePlacedStations[p2.sy*N+p2.sx]){
					for(auto&ts:reachablePlacedStations[p2.ty*N+p2.tx]){
						if(uf.same(ss,ts)){
							addIncome += p2.income;
							goto LABEL_844;
						}
					}
				}
				LABEL_844:
					;
			}
			float score = calcScore(addIncome, T-actions.size()+1, peopleTurn[p.id]);
			peopleScore[p.id] = score;

			keepState(LOAD);
		}
		sort(all(people), [&](const Person&a, const Person&b){
			return peopleScore[a.id] > peopleScore[b.id];
		});

		int _c=0;

		// out("====");
		// printField();
		for(auto&p:people){
			if(peopleCost[p.id]==INF) continue;

			auto cost = connect_sim(p.sy,p.sx,p.ty,p.tx);

			if(T<actions.size()){
				keepState(LOAD);
				continue;
			}

			int addIncome = p.income;

			// 今回の通路追加でついでに繋がるようになった要素が無いか確認
			for(auto&p2:people){// 1600
				if(p2.connected or p.id == p2.id) continue;
				for(auto&ss:reachablePlacedStations[p2.sy*N+p2.sx]){
					for(auto&ts:reachablePlacedStations[p2.ty*N+p2.tx]){
						if(uf.same(ss,ts)){
							addIncome += p2.income;
							goto LABEL_ADD_INCOME;
						}
					}
				}
				LABEL_ADD_INCOME:
					;
			}

			_c++;
			float score = calcScore(addIncome, T-actions.size()+1, actions.size() - _actions.size());


			if(K<cost) {
				if(chmax(maximumScore, score)){
					maximumScoreCost = cost;
				}
				keepState(LOAD);
				continue;
			}

			// out(cost, "\t", peopleCost[p.id], "\t", score, "\t", peopleScore[p.id]);

			if(chmax(bestIncome, score)){
				bestPerson = &p;
			}
			if(actions.size() == _actions.size()) {
				goto LABEL_OUTPUT;
			}
			decided = true;

			keepState(LOAD);
			if(_c >= 10) break;
		}
		
		if(decided) {
			maximumScore = -INF;
			maximumScoreCost = INF;

			Person&p = *bestPerson;

			connect(p.sy,p.sx,p.ty,p.tx);

			out("# Turn:", _actions.size(),"|",  p.sy, p.sx, "->", p.ty, p.tx, "| length:", actions.size() - _actions.size(), "| time:", Mgr::timer.get()-tm);

			const auto cost = keepState(DIFF);
			const auto spent = cost + totalIncome * (actions.size() - _actions.size() - 1);
			keepState(SAVE);

			p.connected=true;
			K-=cost;
			int addIncome = p.income;
			for(auto&p2:people){
				if(p2.connected) continue;
				for(auto&ss:reachablePlacedStations[p2.sy*N+p2.sx]){
					for(auto&ts:reachablePlacedStations[p2.ty*N+p2.tx]){
						if(uf.same(ss,ts)){
							p2.connected=true;
							addIncome += p2.income;
							break;
						}
					}
					if(p2.connected) break;
				}
			}

			totalIncome += addIncome;
			K += totalIncome;
			debug("decided:", actions.size(), K, "/",totalIncome, "(+", addIncome,")", "| cost", cost,"| current best Score:", bestFinalScore, "| remain:", people.size());
			if(actions.size()>=650 and addIncome * (T-actions.size()+1) < spent) {
				if(++warningCount == 5) {
					debug_f("!!! maybe finish");
					break;
				}
			}else{
				warningCount = 0;
			}

			applyDoubleStation = false;
			// out(actions.size(), "\t", totalIncome);

			// peopleから、p.connect == trueのものを削除
			people.erase(remove_if(all(people), [](const Person&p){return p.connected;}), people.end());

			if(people.empty()) break;
		}else if(maximumScoreCost==INF){
			if(applyDoubleStation){
				debug_f("!!! no way to connect");
				break;
			}
			debug_f("!! unlock double station");
			applyDoubleStation = true;
		}
	}
	

	actions = bestActions;

LABEL_OUTPUT:

	if(T > actions.size()){
		placeWait(T-actions.size());
	}

	rep(i,T){
		auto&[type, y, x] = actions[i];
		if(type==EMPTY){
			out(-1);
		}else{
			out(type-1, y, x);
		}
	}
	debug("Final score: ", K);
	debug("Best score: ", bestFinalScore);
	debug("Best actions: ", bestActions.size());
}