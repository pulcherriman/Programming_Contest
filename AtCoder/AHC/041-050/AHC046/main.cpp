/**
* C++23 Template @ AtCoder
* - official support library
*   - AC Library@1.5.1
*   - Boost@1.82.0
*   - GMP@6.2.1
*   - Eigen@3.4.0-2ubuntu2
* - compile option
*   g++-12 -std=gnu++2b -O2 -DONLINE_JUDGE -DATCODER \
*	  -Wall -Wextra \
*	  -mtune=native -march=native \
*	  -fconstexpr-depth=2147483647 -fconstexpr-loop-limit=2147483647 -fconstexpr-ops-limit=2147483647 \
*	  -I/opt/ac-library -I/opt/boost/gcc/include -L/opt/boost/gcc/lib \
*	  -o a.out Main.cpp \
*	  -lgmpxx -lgmp \
*	  -I/usr/include/eigen3
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
#include <bits/stdc++.h>
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
using vp=vector<pii>;
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
constexpr int INF=1000000;
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
template<class T>constexpr bool chmax(T&a, typename std::type_identity<T>::type b){return a<b?(a=b,true):false;}
template<class T>constexpr bool chmin(T&a, typename std::type_identity<T>::type b){return a>b?(a=b,true):false;}
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
	constexpr ostream&operator<<(ostream&os, TupleLike auto a){
		apply([&](auto&&...args){((os<<args<<' '),...);}, a);
		return os;
	}
	constexpr ostream&operator<<(ostream&os, Iterable auto a){
		if(!a.empty()){
			auto b=begin(a), e=end(a);
			os<<(*b++);
			while(b!=e){ os<<' '<<(*b++); }
		}
		return os;
	}
	constexpr ostream&operator<<(ostream&os, RecursiveIterable auto a){
		if(!a.empty()){
			auto b=begin(a), e=end(a);
			os<<(*b++);
			while(b!=e){ os<<'\n'<<(*b++); }
		}
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
	constexpr Random(const bool&isDeterministic):y(isDeterministic?2463534242:chrono::system_clock::now().time_since_epoch().count()){ }
	constexpr int operator()(int a,int b){return next()%(b-a)+a;}
	constexpr ll operator()(ll a,ll b){return (((ull)next())<<32|next())%(b-a)+a;}
	constexpr double operator()(double a,double b){
		// [a, b) の一様乱数
		double scale = (double)next() / (double)std::numeric_limits<uint_fast32_t>::max();
		return scale*(b - a) + a;
	}
private:
	result_type y;
	constexpr result_type next(){
		y ^= (y << 13);
		y ^= (y >> 17);
		y ^= (y << 5);
		return y;
	}
};

inline float t_sqrtF( const float& x )
{
	float xHalf = 0.5f * x;
	int   tmp   = 0x5f3700a0 - ( *(int*)&x >> 1 );
	float xRes  = *(float*)&tmp;
	xRes *= ( 1.5f - ( xHalf * xRes * xRes ) );
	return xRes * x;
}


#ifdef _DEBUG
Random rnd(1); // デバッグ時は固定シード
#else
Random rnd(0); // 本番用は可変シード
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
	float persentile() const { return (float)get()/((float)limit/ClocksPerMsec); }
};
void wait(const int&msec){Timer tm(msec); while(tm);}

struct Mgr {
	#ifdef _DEBUG
	static const int TLE = 2000; // ms
	#else
	static const int TLE = 2000; // ms
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
		static inline size_t hash_rnd = rnd(0,INF); // 適当に初期化
		static const inline size_t hash_value = 0x9e3779b9;
		template<class V, class P=remove_const_t<remove_reference_t<V>>>
		static size_t& do_hash(size_t&seed, V&v) {
			return seed ^= hash<P>{}(v) + hash_value + (seed<<6) + (seed>>2);
		}
	};

	template<class S, class T>
	struct hash<pair<S,T>> : public hash_base<pair<S,T>> {
		size_t operator()(pair<S,T> p) const {
			size_t seed= this->hash_rnd;
			this->do_hash(seed, p.first);
			this->do_hash(seed, p.second);
			return seed;
		}
	};

	template<class...Ts>
	struct hash<tuple<Ts...>> : public hash_base<tuple<Ts...>> {
		size_t operator()(tuple<Ts...> t) const {
			size_t seed= this->hash_rnd;
			apply([&](auto&&...args){
				((this->do_hash(seed, args)),...);
			}, t);
			return seed;
		}
	};
}

const int N=20, M=40;
array<pii, M> targets;
using Field = array<array<int, N>,N>;

// (type, x, y)
//  type==0: 壊す (x,y) の壁
//  type==1: (x,y) まで移動
using Action = tuple<int,int,int>;

void pushPosToVec(int y, int x, vector<pii>& vec) {
	if (y < 0 || y >= N || x < 0 || x >= N) return;
	vec.push_back({y, x});
}

struct Wish {
	pii from, to;
	vp place, noPlace;

	Wish(pii f, pii t): from(f), to(t) {
	}

	void think() {
		int dy = to.first - from.first, dx = to.second - from.second;
		int dyunit = dy ? dy / abs(dy) : 0, dxunit = dx ? dx / abs(dx) : 0;
		int dyabs = abs(dy), dxabs = abs(dx);

		if(dy!= 0 and dx != 0) {

			pushPosToVec(to.first + dyunit, to.second, place);
			pushPosToVec(to.first, to.second + dxunit, place);
			pushPosToVec(to.first + dyunit, from.second, place);
			pushPosToVec(from.first, to.second + dxunit, place);

			pushPosToVec(to.first - dyunit, to.second, noPlace);
			pushPosToVec(to.first, to.second - dxunit, noPlace);
			pushPosToVec(to.first- dyunit, to.second - dxunit, noPlace);
			pushPosToVec(to.first, to.second, noPlace);

		} else if(dy!=0) {
			pushPosToVec(to.first + dyunit, to.second, place);
			for(int i=from.first; i<to.first+dyunit; i+=dyunit) {
				pushPosToVec(i, from.second, noPlace);
			}
		} else if(dx!=0) {
			pushPosToVec(to.first, to.second + dxunit, place);
			for(int i=from.second; i<to.second+dxunit; i+=dxunit) {
				pushPosToVec(from.first, i, noPlace);
			}
		}
	}

	// fromからtoへの移動経路を計算
	// ただし、移動のコストは以下
	// 1. 上下左右隣接の空白マスにはコスト1
	// 2. 上下左右方向に、空白マスを一直線に壁にぶつかるまで出来るだけ進んだ時のコストは1
	// 3. 上下左右が壁の時、その壁を壊してそのマスに移動するのにコスト2
	// 4. 上下左右が壁の時、その壁を壊してその方向に限界まで移動するのにコスト2
    vector<tuple<int,int,int>> calcMove(const Field field) {
        static constexpr int INF_DIST = 1e9;
        static int dist[N][N];
        struct Parent { int px, py, type, dir; };
        static Parent parent[N][N];

        // 初期化
        for(int i=0;i<N;++i){
            for(int j=0;j<N;++j){
                dist[i][j] = INF_DIST;
                parent[i][j] = Parent{-1,-1,-1,-1};
            }
        }

        int sy = from.first, sx = from.second;
        int ty = to.first,   tx = to.second;
        dist[sy][sx] = 0;

        // priority_queue に vector<pii> broken を持たせるのは重いままですが，
        // dist/parent を固定配列化しただけで劇的に高速化します
        using State = tuple<int,int,int,vector<pii>>;
        priority_queue<State, vector<State>, greater<>> pq;
        pq.emplace(0, sy, sx, vector<pii>());

        static constexpr int dy4[4]={-1,1,0,0}, dx4[4]={0,0,-1,1};
        while(!pq.empty()){
            auto [d,y,x,broken] = pq.top(); pq.pop();
            if(d>dist[y][x]) continue;
            if(y==ty && x==tx) break;

            auto getField = [&](int yy,int xx){
                if(field[yy][xx]==0) return 0;
                for(auto &p:broken) if(p.first==yy&&p.second==xx) return 0;
                return 1;
            };

            for(int dir=0;dir<4;dir++){
                int nx=x+dx4[dir], ny=y+dy4[dir];
                // (1) 隣接移動
                if(0<=nx&&nx<N&&0<=ny&&ny<N && getField(ny,nx)==0){
                    int nd=d+1;
                    if(nd<dist[ny][nx]){
                        dist[ny][nx]=nd;
                        parent[ny][nx]={x,y,0,dir};
                        pq.emplace(nd,ny,nx,broken);
                    }
                }
                // (2) 滑走
                int sx2=x, sy2=y;
                while(true){
                    int xx=sx2+dx4[dir], yy=sy2+dy4[dir];
                    if(xx<0||xx>=N||yy<0||yy>=N) break;
                    if(getField(yy,xx)!=0) break;
                    sx2=xx; sy2=yy;
                }
                if(sx2!=x||sy2!=y){
                    int nd=d+1;
                    if(nd<dist[sy2][sx2]){
                        dist[sy2][sx2]=nd;
                        parent[sy2][sx2]={x,y,1,dir};
                        pq.emplace(nd,sy2,sx2,broken);
                    }
                }
                // (3)(4) 壁破壊
                if(0<=nx&&nx<N&&0<=ny&&ny<N && getField(ny,nx)==1){
                    auto broken2=broken;
                    broken2.emplace_back(ny,nx);
                    // 破壊ステップ
                    int nd=d+2;
                    if(nd<dist[ny][nx]){
                        dist[ny][nx]=nd;
                        parent[ny][nx]={x,y,2,dir};
                        pq.emplace(nd,ny,nx,broken2);
                    }
                    // 破壊滑走
                    sx2=nx; sy2=ny;
                    while(true){
                        int xx=sx2+dx4[dir], yy=sy2+dy4[dir];
                        if(xx<0||xx>=N||yy<0||yy>=N) break;
                        if(getField(yy,xx)!=0) break;
                        sx2=xx; sy2=yy;
                    }
                    if(nd<dist[sy2][sx2]){
                        dist[sy2][sx2]=nd;
                        parent[sy2][sx2]={x,y,3,dir};
                        pq.emplace(nd,sy2,sx2,broken2);
                    }
                }
            }
        }

        // 経路復元（元と同じロジック）
        vector<tuple<int,int,int>> actions;
        if(dist[ty][tx]==INF_DIST) return actions;
        int cx=tx, cy=ty;
        while(!(cx==sx&&cy==sy)){
            auto p=parent[cy][cx];
            int px=p.px, py=p.py, dir=p.dir, type=p.type;
            int bx=px+dx4[dir], by=py+dy4[dir];
            if(type==0||type==1){
                actions.emplace_back(1,cy, cx);
            } else if(type==2){
                actions.emplace_back(1,cy, cx);
                actions.emplace_back(0,by, bx);
            } else {
                actions.emplace_back(1,cy, cx);
                actions.emplace_back(0,by, bx);
            }
            cx=px; cy=py;
        }
        reverse(actions.begin(), actions.end());
        return actions;
    }

	vector<pair<char, char>> output;
	vp placedWalls;
	void applyOutput(char t, char d) {
		output.emplace_back(t, d);
	}
	void applyPlaceWall(int y, int x){
		placedWalls.emplace_back(y, x);
	}

	// actions を実行しつつ出力 & field 更新
	int applyMove(const vector<Action>& actions, Field& field,
		Field& desire
	) {
		static constexpr int dy[4] = { -1, +1,  0,  0 };
		static constexpr int dx[4] = {  0,  0, -1, +1 };
		static constexpr char dirs[4] = { 'U','D','L','R' };
	
		int cy = from.first, cx = from.second;
		for (int idx = 0; idx < (int)actions.size(); ++idx) {
			auto [type, ny, nx] = actions[idx];
			int ddx = nx - cx, ddy = ny - cy;  // ddx: cols, ddy: rows
	
			// 方向判定: ddx がゼロでないなら左右, そうでなければ上下
			int thisDir;
			if (ddy < 0)      thisDir = 0;  // 上
			else if (ddy > 0) thisDir = 1;  // 下
			else if (ddx < 0) thisDir = 2;  // 左
			else               thisDir = 3; // 右
			char dirChar = dirs[thisDir];
	
	
			if (type == 0) {
				// 移動のための破壊
				applyOutput('A', dirChar);
				field[ny][nx] = 0;
			} else {
				// 隣接セルを desire に従い調整（skipDir を除外）
				if(idx<actions.size()-1) {
					for (int d = 0; d < 4; ++d) {
						if (d == thisDir) continue;
						int ay = cy + dy[d], ax = cx + dx[d];
						if (ay < 0 || ay >= N || ax < 0 || ax >= N) continue;
		
						int v = desire[ay][ax];
						if (v == 1 && field[ay][ax] == 1) {
							applyOutput('A', dirs[d]);
							field[ay][ax] = 0;
						} else if (v == 2 && field[ay][ax] == 0) {
							applyOutput('A', dirs[d]);
							applyPlaceWall(ay, ax);
							field[ay][ax] = 1;
						}
					}
				}

				// 移動 or 滑走
				if (abs(ddx) + abs(ddy) >= 2) applyOutput('S', dirChar);
				else applyOutput('M', dirChar);
				cy = ny; cx = nx;
			}
		}
		return output.size();
	}
};


auto solve(int prevBestScoreOn50=INF) {
	int bestTotal = INF;
	vector<pair<char, char>> bestOutput;
	vp bestPlacedWalls;
	Field bestLock{};

	Timer test(0);

	int bestScoreOn50 = INF;

	rep(lp,300){
		if(lp==50) {
			if(prevBestScoreOn50 < bestTotal) {
				break;
			}
			bestScoreOn50 = bestTotal;
		}
		if(!Mgr::timer) break;
		auto newLock = bestLock;
		if(bestTotal!=INF) {
			auto [ty, tx] = bestPlacedWalls[rnd(0, bestPlacedWalls.size())];
			newLock[ty][tx] = (newLock[ty][tx] + rnd(1,3)) % 3;
			// newLock[ty][tx] = (newLock[ty][tx] + rnd(1,2)) % 2;
		}

		Field field{};
		vector<Wish> wishes;
		rep(i, M - 1) wishes.emplace_back(targets[i], targets[i + 1]);
		for (auto& w : wishes) w.think();
		int total = 0;
		rep(i, M - 1) {
			// out("start", i+1);
			// future の place/noPlace を欲求マップにまとめる
			Field desire{}; // 0 で初期化
			for (int j = i + 1; j < M - 1; ++j) {
				for (auto [py, px] : wishes[j].place) {
					if (desire[py][px] == 0) desire[py][px] = 2;
				}
				for (auto [ny, nx] : wishes[j].noPlace) {
					if (desire[ny][nx] == 0) desire[ny][nx] = 1;
				}
			}
			rep(i,N) rep(j,N) if(newLock[i][j]>0) {
				desire[i][j] = newLock[i][j];
			}

			auto actions = wishes[i].calcMove(field);
			total += wishes[i].applyMove(actions, field, desire);
		}


		if(chmin(bestTotal, total)) {
			bestOutput = wishes[0].output;
			for (int i = 1; i < M - 1; ++i) {
				bestOutput.insert(bestOutput.end(), all(wishes[i].output));
			}
			bestPlacedWalls.clear();
			for (int i = 0; i < M - 1; ++i) {
				bestPlacedWalls.insert(bestPlacedWalls.end(), all(wishes[i].placedWalls));
			}
			bestLock = newLock;
		}
	}
	debug(bestTotal);
	return make_tuple(bestTotal, bestOutput, bestScoreOn50);
}

int main() {
	def(int,_,__);
	rep(i,M) {
		int x,y; cin>>y>>x;
		targets[i] = {y,x};
	}

	int bestTotal = INF;
	int bestScoreOn50 = INF;
	vector<pair<char, char>> bestOutput;

	while(Mgr::timer){
		auto [total, output, on50] = solve(bestScoreOn50);
		if(chmin(bestTotal, total)) {
			bestScoreOn50 = on50;
			bestOutput = output;
		}
	}


	debug_f(M + 2*N*M - bestTotal);

	for(auto act: bestOutput) {
		out(act);
	}

	return 0;
}
