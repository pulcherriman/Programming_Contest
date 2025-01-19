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
#define __RANGE(i,a,n) for(ll i=((ll)a);i<((ll)n);++i)
#define __RREP(i,n) __RRANGE(i,0,n)
#define __RRANGE(i,a,n) for(ll i=((ll)(n)-1);i>=((ll)a);--i)
#define sz(a) ((ll)(a).size())
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
	static const int TLE = 20000;
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


/*
277
PRRRQLLLPRRQLLPRQRPRRDDQLLUPRRDQLLLLUUPRRRRDDDQLLLLDPUUUURRRRQLLLLDPRRRRUQLLLDPRRRUQLLLLDPRRRRQLLLDPRRRUQLDPRUQLLLLDDPRRRRUUUQLLLLPDDRQLDDPRRRRUUQLDPUURQLLDPURRQLLLLDPDDQUPRRRRQLLLLUPDDRRRRQLLLLPRRRRQLLLPRRRQLLPRRQLLUPUUURRQLPDDDDRQLLLUUPRRRQLLLUUPDDDRRRQLDPURQLUUPDRQDLLLPRRRQ
PRRRQLLLPRRQLLPRQB
PRRRQLLLPRRQLLPRQB
PRRRQLLLPRRQLLPRQB
PRRRQLLLPRRQLLPRQB
*/

const int N = 5;
vector<vector<int>> containerInput(N, vector<int>(N));


int tumbleCount(vector<int> val){
	int cnt = 0;
	vb exist(N, false);
	for(auto&v: val) {
		v %= N;
		exist[v] = true;
	}
	rep(i,N) if(!exist[i]) val.pb(i);

	rep(i,N) rep(j,i) if(val[j] > val[i]) cnt++;
	return cnt;
}



struct Crane {
	using CraneState = tuple<bool, int, int, char>;
	
	bool isLarge = false, bombed = false;
	vector<CraneState> states;

	Crane(bool isLarge, int height) : isLarge(isLarge) {
		states.push_back({false, height, 0, ' '});
	}

	tuple<bool, int, int, char>& getCurrentState() {
		return states.back();
	}

	void move(int dy, int dx) {
		if(bombed) return;
		auto [isGrabbing, y, x, _] = getCurrentState();
		const char action = dy == 0 ? (dx == 1 ? 'R' : 'L') : (dy == 1 ? 'D' : 'U');
		states.push_back({isGrabbing, y + dy, x + dx, action});
	}

	void grab() {
		if(bombed) return;
		auto [isGrabbing, y, x, _] = getCurrentState();
		states.push_back({true, y, x, 'P'});
	}

	void drop() {
		if(bombed) return;
		auto [isGrabbing, y, x, _] = getCurrentState();
		states.push_back({false, y, x, 'Q'});
	}

	void keep() {
		if(bombed) return;
		auto [isGrabbing, y, x, _] = getCurrentState();
		states.push_back({isGrabbing, y, x, '.'});
	}

	void bomb() {
		if(bombed) return;
		auto [isGrabbing, y, x, _] = getCurrentState();
		states.push_back({false, y, x, 'B'});
		bombed = true;
	}
};

struct Series {
	const static int EMPTY = -1;
	int turn = 0, carryOutCount = 0;;
	vector<Crane> cranes;
	array<array<int, N>, N> field;
	array<array<bool, N>, N> grabbingField;
	vector<int> grabbingContainer;
	vector<vector<int>> container;
	vector<vector<int>> result;


	Series() {
		container = containerInput;
		cranes.emplace_back(true,0);
		rep(i,1,N) cranes.emplace_back(false,i);
		rep(i,N) rep(j,N) {
			field[i][j] = EMPTY;
			grabbingField[i][j] = false;
		}
		result.resize(N);
		grabbingContainer.resize(N, -1);
	}

	void carryIn() {
		rep(i,N) {
			if(field[i][0] == EMPTY and !container[i].empty()) {
				field[i][0] = container[i].back();
				container[i].pop_back();
			}
		}
	}

	void carryOut() {
		rep(i,N) {
			if(field[i][N-1] != EMPTY and !grabbingField[i][N-1]) {
				result[i].push_back(field[i][N-1]);
				field[i][N-1] = EMPTY;
				carryOutCount++;
			}
		}
	}

	void applyState(int idx, int targetTurn) {
		if(targetTurn-1 >= sz(cranes[idx].states)) return;
		auto [fromIsGrabbing, fromY, fromX, fromAction] = cranes[idx].states[targetTurn-1];
		if (fromAction == 'P') {
			grabbingContainer[idx] = field[fromY][fromX];
			field[fromY][fromX] = EMPTY;
		}
		if(fromAction == 'B') return;
		if(targetTurn >= sz(cranes[idx].states)) return;
		auto [toIsGrabbing, toY, toX, toAction] = cranes[idx].states[targetTurn];

		grabbingField[toY][toX] = toIsGrabbing;

		if (toAction == 'Q') {
			field[toY][toX] = grabbingContainer[idx];
			grabbingContainer[idx] = -1;
		}
	}

	void moveTo(int idx, int y, int x) {
		auto [_, fromY, fromX, __] = cranes[idx].getCurrentState();
		int dy = y - fromY, dx = x - fromX;
		int unitDY = dy == 0 ? 0 : dy / abs(dy);
		int unitDX = dx == 0 ? 0 : dx / abs(dx);
		rep(_, abs(dy)) cranes[idx].move(unitDY, 0);
		rep(_, abs(dx)) cranes[idx].move(0, unitDX);
	}

	void grabFromTo(int idx, int fromY, int fromX, int toY, int toX) {
		moveTo(idx, fromY, fromX);
		cranes[idx].grab();
		moveTo(idx, toY, toX);
		cranes[idx].drop();
	}

	void strategyInitialize() {
		rep(i,N) rep(j,3) grabFromTo(i, i, 0, i, 3-j);
		// rep(i,1,N) cranes[i].bomb();
	}

	void strategyBigCrane() {
		auto [_, fromY, fromX, __] = cranes[0].getCurrentState();

		{
			int itemC=-1, toY=-1, toX=-1, minDist=1e9;
			rep(c,N){
				if (!container[c].empty()) {
					rep(i,N)rep(j,N-1) if(field[i][j] == EMPTY){
						int dist = abs(fromY - c) + abs(c - i) + j;
						if(chmin(minDist, dist)) itemC = c, toY = i, toX = j;
					}
				}
			}
			if(minDist <= 3){
				grabFromTo(0, itemC, 0, toY, toX);
				return;
			}
		}

		using ItemPosition = tuple<int, int, int>;
		vector<ItemPosition> positions;
		rep(c,N) rep(i,N) rep(j,N) {
			if(field[i][j] == c*N + sz(result[c])) {
				positions.emplace_back(field[i][j], i, j);
			}
		}
		if(!positions.empty()) {
			int idx = 0, minDist = 1e9;
			rep(i,sz(positions)) {
				auto [containerIdx, toY, toX] = positions[i];
				int dist = abs(fromY - toY) + abs(fromX - toX) + containerIdx%5 * 2;
				if(chmin(minDist, dist)) idx = i;
			}
			auto [itemIdx, itemY, itemX] = positions[idx];
			grabFromTo(0, itemY, itemX, itemIdx/N, N-1);
			return;
		}

		{
			int itemC=-1, toY=-1, toX=-1, minDist=1e9;
			rep(c,N){
				if (!container[c].empty()) {
					rep(i,N)rep(j,N-1) if(field[i][j] == EMPTY){
						int dist = abs(fromY - c) + abs(c - i) + j;
						if(chmin(minDist, dist)) itemC = c, toY = i, toX = j;
					}
				}
			}
			if(itemC != -1) {
				grabFromTo(0, itemC, 0, toY, toX);
			}
		}

	}

	void applyTurn() {
		vector<pair<int,int>> alreadyExistCoor;
		vector<pair<int,int>> alreadyExistCoorStrict;


		rep(i,N) {
			if(sz(cranes[i].states) >= turn) {
				applyState(i, turn);
				auto [_, y, x, action] = cranes[i].states[turn-1];
				alreadyExistCoor.emplace_back(y, x);
				alreadyExistCoorStrict.emplace_back(y, x);
			} else {
				// このターンの行動が未定
				auto [_, y, x, action] = cranes[i].getCurrentState();
				bool ok = true, actionDecided = false;;
				for(auto [by, bx]: alreadyExistCoor) {
					if(by == y and bx == x) {
						ok = false;
						break;
					}
				}
				if(ok) {
					int dy[] = {0, 0, 1, -1};
					int dx[] = {1, -1, 0, 0};
					int nearest = 0, ady = -1, adx = -1;
					rep(j,4) {
						int ny = y + dy[j], nx = x + dx[j];
						if(ny < 0 or ny >= N or nx < 0 or nx >= N) continue;
						ok=true;
						for(auto [by, bx]: alreadyExistCoor) {
							if(by == ny and bx == nx) {
								ok=false;
								break;
							}
						}
						if(ok){
							int minDist = INF;
							for(auto [by, bx]: alreadyExistCoorStrict) {
								chmin(minDist, abs(by - ny) + abs(bx - nx));
							}
							if(chmax(nearest, minDist)) ady = dy[j], adx = dx[j];
						}
					}
					if(nearest != 0) {
						actionDecided = true;
						moveTo(i, y+ady, x+adx);
						applyState(i, turn);
						alreadyExistCoor.emplace_back(y+ady, x+adx);
						alreadyExistCoorStrict.emplace_back(y+ady, x+adx);
						break;
					}
				}
				if(!actionDecided) cranes[i].bomb();
			}
			{
				auto [_, y, x, action] = cranes[i].states[turn-2];
				alreadyExistCoor.emplace_back(y, x);
			}

		}
	}

	void act() {
		if(carryOutCount == N*N) return;
		if(sz(cranes[0].states) == turn) {
			strategyBigCrane();
		}
		turn++;
		carryIn();
		applyTurn();
		carryOut();
	}

	void output() {
		rep(i,N) {
			rep(j,1,sz(cranes[i].states)) {
				auto [_, y, x, action] = cranes[i].states[j];
				cout << action;
			}
			cout << endl;
		}
	}
};

struct ScoreCalculator {
	static int calc(Series& series) {
		int m0 = 0, m1 = 0, m2 = 0, m3 = 0;
		rep(i,N){
			chmax(m0, sz(series.cranes[i].states) - 1);
			m1 += tumbleCount(series.result[i]);
			for(auto&idx: series.result[i]){
				if(idx/N != i) m2 ++;
			}
			m3 += N - sz(series.result[i]);
		}
		return m0 + m1 * 100 + m2 * 10000 + m3 * 1000000;
	}
};

// 大クレーンだけ動く / 子供を蛇のように動かしながら浮気させる

int main() {
	def(int, _);
	rep(i, N) {
		rep(j, N) {
			cin >> containerInput[i][j];
		}
		reverse(all(containerInput[i]));
	}

	Series series;
	series.strategyInitialize();

	rep(10000) series.act();

	series.output();
	debug(ScoreCalculator::calc(series));



}