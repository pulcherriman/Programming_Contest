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
	vi par; vector<T> dist;
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
		if(exist[i][j]){
			for(auto [dy,dx]:neighbor){
				int ny=i+dy,nx=j+dx;
				if(ny<0 || nx<0 || ny>=N || nx>=N) continue;
				reachableStations[ny][nx].push_back(stations.back());
			}
		}
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
vector<tuple<int,int,int>> actions, bestActions(0);
UnionFind uf(N*N);
vector<pair<int,int>> placedStations;
array<vector<pair<int,int>>,N*N> reachablePlacedStations;
enum STATE_TYPE {SAVE, LOAD, DIFF};
auto keepState(STATE_TYPE type) {
	static auto _field = field;
	static auto _actions = actions;
	static auto _uf = uf;
	static auto _placedStations = placedStations;
	static auto _reachablePlacedStations = reachablePlacedStations;
	if(type == SAVE){
		_field = field;
		// ここで候補を確定
		int cnt = actions.size() - _actions.size();
		rep(i,cnt){
			auto act = actions.back();
			actions.pop_back();
			_actions.push_back(act);
		}
		actions = _actions;
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

void placeWait(int cnt) {
	rep(i,cnt){
		actions.emplace_back(EMPTY, 0, 0);
	}
}

void placeItem(int y, int x, RAILS type) {
	static int cnt = 0;
	if(type==STATION){
		if(field[y][x]==STATION) return;
		placedStations.emplace_back(y,x);
		for(auto&[dy,dx]:neighbor){
			int ny=y+dy,nx=x+dx;
			if(ny<0 || nx<0 || ny>=N || nx>=N) continue;
			reachablePlacedStations[ny*N+nx].push_back({y,x});
		}
	}else{
		if(field[y][x]!=EMPTY) return;
	}

	actions.emplace_back(type, y, x);
	field[y][x]=type;
	cnt++;
	int p=y*N+x;
	for(auto [dy,dx]:railNeighbor[type]){
		int ny=y+dy,nx=x+dx;
		if(ny<0 || nx<0 || ny>=N || nx>=N) continue;
		int np=ny*N+nx;
		bool railOk = false;
		railOk |= (ny-y==1 && (field[ny][nx]==RAILS::UD || field[ny][nx]==RAILS::LU || field[ny][nx]==RAILS::RU || field[ny][nx]==RAILS::STATION));
		railOk |= (ny-y==-1 && (field[ny][nx]==RAILS::UD || field[ny][nx]==RAILS::LD || field[ny][nx]==RAILS::RD || field[ny][nx]==RAILS::STATION));
		railOk |= (nx-x==1 && (field[ny][nx]==RAILS::LR || field[ny][nx]==RAILS::LU || field[ny][nx]==RAILS::LD || field[ny][nx]==RAILS::STATION));
		railOk |= (nx-x==-1 && (field[ny][nx]==RAILS::LR || field[ny][nx]==RAILS::RU || field[ny][nx]==RAILS::RD || field[ny][nx]==RAILS::STATION));
		if(railOk){
			uf.unite(p,np);
		}
	}
}

// 座標(y,x)をカバーする駅を候補から選び、必要なら設置し、座標を返す
pair<int,int> setStations(int y, int x){
	const auto&sta = reachableStations[y][x];
	for(auto&[ny,nx]:sta){
		if(field[ny][nx]==RAILS::STATION) {
			return {ny,nx};
		}
	}
	const auto selectedStation = sta[0];
	placeItem(selectedStation.first,selectedStation.second,RAILS::STATION);
	// 既存の駅と連結していれば置く
	// for(auto&[dy,dx]:railNeighbor[RAILS::STATION]){
	// 	int ny=selectedStation.first+dy,nx=selectedStation.second+dx;
	// 	if(ny<0 || nx<0 || ny>=N || nx>=N) continue;
	// 	if(field[ny][nx]==RAILS::STATION){
	// 		debug_f("UNITE", y,x,"->",ny,nx);
	// 		wait(1000);
	// 		uf.unite(y*N+x,ny*N+nx);
	// 	}
	// }
	return selectedStation; // TODO: 最適な駅の選び方があるかも
}

// (sy,sx)から(ty,tx)へ線路を引く。既存の線路は上書きできない
bool createRailway(int sy, int sx, int ty, int tx) {
    const int size = N * N;
    // 各セルの距離（未到達なら INF）と直前セルを管理する配列
    vector<int> d(size, INF);
    vector<int> pr(size, -1);
    int start = sy * N + sx;
    int target = ty * N + tx;
    d[start] = 0;
    
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
    
    // 各方向で許容するレール種類をビットマスクで定義（STATIONは常に許容）
    // ※ field の値は enum RAILS {ERR=-1, EMPTY, STATION, LR, UD, LD, LU, RU, RD} に従う
    // 下方向 (ady == 1): UD(3), LU(5), RU(6)
    constexpr int mask_down  = (1 << 3) | (1 << 5) | (1 << 6);
    // 上方向 (ady == -1): UD(3), LD(4), RD(7)
    constexpr int mask_up    = (1 << 3) | (1 << 4) | (1 << 7);
    // 右方向 (adx == 1): LR(2), LU(5), LD(4)
    constexpr int mask_right = (1 << 2) | (1 << 5) | (1 << 4);
    // 左方向 (adx == -1): LR(2), RU(6), RD(7)
    constexpr int mask_left  = (1 << 2) | (1 << 6) | (1 << 7);
    

    deque<int> que;
    que.push_back(start);
    
    while (!que.empty()) {
        int p = que.front();
        que.pop_front();
        if (p == target) break;
        int y = pos[p].first, x = pos[p].second;
        
        // 駅セルの場合、全体の placedStations を走査する
        if (field[y][x] == STATION) {
            for (auto &st : placedStations) {
                int idx = st.first * N + st.second;
                if (uf.same(p, idx) && d[idx] == INF) {
                    d[idx] = d[p]; // コストは 0
                    pr[idx] = p;
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
                pr[np] = p;
                que.push_back(np);
                continue;
            }

            int cell = field[ny][nx];
            bool railOk = cell == STATION;
            if (!railOk) {
                int ady = ny - y, adx = nx - x;
                if (ady == 1) {
                    railOk = (mask_down & (1 << cell)) != 0;
                } else if (ady == -1) {
                    railOk = (mask_up & (1 << cell)) != 0;
                } else if (adx == 1) {
                    railOk = (mask_right & (1 << cell)) != 0;
                } else if (adx == -1) {
                    railOk = (mask_left & (1 << cell)) != 0;
                }
            }

            if (railOk) {
                d[np] = d[p];
                pr[np] = p;
                que.push_front(np);
            }
        }
    }
    
    if (d[target] == INF) return false;
    
    // 経路復元：target から start まで pr[] をたどる
    int p_idx = target;
    pii prevPos = {-1, -1};
    while (p_idx != start) {
        int y = pos[p_idx].first, x = pos[p_idx].second;
        int pprev = pr[p_idx];
        int py = pos[pprev].first, px = pos[pprev].second;
        if (prevPos.first != -1) {
            if (field[y][x] != EMPTY) {
                prevPos = {y, x};
                p_idx = pprev;
                continue;
            }
            RAILS type = getRailType(prevPos.first, prevPos.second, y, x, py, px);
            if (type == ERR) {
                prevPos = {y, x};
                p_idx = pprev;
                continue;
            }
            placeItem(y, x, type);
        }
        prevPos = {y, x};
        p_idx = pprev;
    }
    return true;
}



// 既存の線路を壊さずに、(sy,sx)から(ty,tx)へ線路を引く
// 既につながっている駅間は移動できる
bool connect(int sy, int sx, int ty, int tx) {
	const auto sSta = setStations(sy,sx);
	const auto tSta = setStations(ty,tx);
	return createRailway(sSta.first,sSta.second,tSta.first,tSta.second);
}

int main() {
	{
		int _, __;
		cin>>_>>M>>K>>__;

		people.resize(M);
		rep(i,M){
			cin>>people[i].sy>>people[i].sx>>people[i].ty>>people[i].tx;
			people[i].income=abs(people[i].sx-people[i].tx)+abs(people[i].sy-people[i].ty);
		}
		rep(i,N)rep(j,N) field[i][j]=EMPTY;
	}

	decideStations();
	
	sort(rall(people),[](const Person&a,const Person&b){
		return a.income<b.income;
	});

	int minimumCost = INF;

	while(actions.size() < T) {
		debug("start turn:", actions.size(), K, "/ (+", totalIncome,")");
		// 前ターン、終了しなかった
		if(minimumCost!=INF){
			int remain = minimumCost - K;
			int waitCount = (remain + totalIncome - 1) / totalIncome;
			debug("force wait", minimumCost, remain, waitCount);
			placeWait(waitCount);
			K += waitCount * totalIncome;
			keepState(SAVE);
			minimumCost = INF;
			// continue;
		}

		bool decided = false;
		minimumCost = INF;

		map<Person*, int> addIncomes;

		keepState(SAVE);
		for(auto&p:people){
			if(p.connected==true) continue;
			auto result = connect(p.sy,p.sx,p.ty,p.tx);
			if(!result) {
				keepState(LOAD);
				continue;
			}
			const auto cost = keepState(DIFF);
			if(K>=cost) {
				int addIncome = p.income;

				// 今回の通路追加でついでに繋がるようになった要素が無いか確認
				for(auto&p2:people){// 1600
					if(p2.connected) continue;
					for(auto&ss:reachablePlacedStations[p2.sy*N+p2.sx]){
						for(auto&ts:reachablePlacedStations[p2.ty*N+p2.tx]){
							if(uf.same(ss.first*N+ss.second,ts.first*N+ts.second)){
								addIncome += p2.income;
								goto LABEL_ADD_INCOME;
							}
						}
					}
					LABEL_ADD_INCOME:
						;
				}
				addIncomes[&p] = addIncome * (T-actions.size()+1); //NOTE : 掛けていいかは諸説（多分いい）
				decided = true;
			}else{
				chmin(minimumCost, cost);
			}
			keepState(LOAD);
		}
		if(decided) {
			minimumCost = INF;

			Person&p = *max_element(all(addIncomes), [](const auto& a, const auto& b){return a.second < b.second;})->first;
			connect(p.sy,p.sx,p.ty,p.tx);
			const auto cost = keepState(DIFF);
			p.connected=true;
			K-=cost;
			totalIncome += p.income;
			bool remainPeople = false;
			for(auto&p2:people){
				if(p2.connected) continue;
				for(auto&ss:reachablePlacedStations[p2.sy*N+p2.sx]){
					for(auto&ts:reachablePlacedStations[p2.ty*N+p2.tx]){
						if(uf.same(ss.first*N+ss.second,ts.first*N+ts.second)){
							p2.connected=true;
							totalIncome += p2.income;
							break;
						}
					}
					if(p2.connected) break;
				}
				if(!p2.connected) remainPeople = true;
			}

			keepState(SAVE);

			K += totalIncome;
			debug("decided:", actions.size(), K, "/ (+", totalIncome,")", "cost", cost);

			if(!remainPeople) break;
		}
	}
	

	actions = bestActions;
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