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
#undef _DEBUG
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

struct Point {
	float x, y;
	float dist(Point p) {
		return sqrt((x-p.x)*(x-p.x) + (y-p.y)*(y-p.y));
	}
	friend Point operator-(const Point& p1, const Point& p2) {
		return {p1.x-p2.x, p1.y-p2.y};
	}
};
struct Speed {
	float x, y;
};
struct Edge {
	Point p1, p2;
};

const int n=10; int m;
float E,D;
Point s;
array<Point, n> p;
vector<Edge> edges;

#ifdef _DEBUG
vector<float> distError(5000);
vector<Speed> spdError(5000);
#endif

float Cross(const Point& a, const Point& b) {
    return a.x * b.y - a.y * b.x;
}

Point Intersection(const Point& a, const Point& b, const Point& c, const Point& d) {
    float s, t, deno = Cross(b - a, d - c);
    Point error = { 1e9, 1e9 };
    if (deno == 0.0) {
        // 線分が平行
        return error;
    }
    s = Cross(c - a, d - c) / deno;
    t = Cross(b - a, a - c) / deno;
    if (s < 0.0 || 1.0 < s || t < 0.0 || 1.0 < t) {
        // 線分が交差していない
        return error;
    }
    return { a.x + s * (b - a).x, a.y + s * (b - a).y };
}


// startから出て、target全てを訪問する最短経路を求める（startに帰る必要はない
vi tsp(Point start, array<Point,n> targets) {
	vector<pair<float, vi>> best(n, {1e9, vi(n)}); // 最短距離と訪問順
	vi perm(n); iota(all(perm), 0);
	do {
		float dist = 0;
		Point cur = start;
		rep(i,n) {
			dist += cur.dist(targets[perm[i]]);
			cur = targets[perm[i]];
		}
		if(chmin(best[perm[0]].first, dist)) best[perm[0]].second = perm;
	} while(next_permutation(all(perm)));

	return min(best).second;
}

struct Solver {
	int turn = 0;
	Point pos;
	Speed spd{0, 0};

	#ifdef _DEBUG
	Point strictPos;
	Speed strictSpeed;
	#endif

	float distance(float x, float y) {
		out("S", (int)x, (int)y)<<flush;
		float ret = 0;
		#ifdef _DEBUG
		ret = 1e9;
		for(auto&[p1, p2] : edges) {
			// strictPos から(x,y) 方向を見る。このとき、端点p1,p2で構成される辺と交差する場合、その点までの距離を求める

			// 交差するかどうか
			Point p3 = strictPos;
			Point p4 = {x, y};

			Point cross = Intersection(p1, p2, p3, p4);
			if(cross.x == 1e9) cross = {x, y};

			chmin(ret, strictPos.dist(cross));
		}
		ret = round(ret * distError[turn]);
		#else
		cin>>ret;
		#endif
		return ret;
	}

	void setSpd(float x, float y) {
		out("A", (int)x, (int)y)<<flush;
		spd.x += x;
		spd.y += y;
		#ifdef _DEBUG
		strictSpeed = spd;
		#endif
	}

	bool isCross(float x, float y) {
		// x,y に飛ばそうとしてぶつからないか easy
		auto dist = distance(x, y);
		auto predict = pos.dist({x, y});
		if(abs(dist-predict) < D*3) return  true;
		return false;
	}

	vector<bool> activated;
	int activatedCount = 0;
	bool move() {
		bool isCrossed = false;
		vi cleared;

		#ifdef _DEBUG
		for(auto&[p1, p2] : edges) {
			// strictPos から(x,y) 方向を見る。このとき、端点p1,p2で構成される辺と交差する場合、その点までの距離を求める

			// 交差するかどうか
			Point p3 = strictPos;
			Point p4 = {strictPos.x+strictSpeed.x, strictPos.y+strictSpeed.y};

			Point cross = Intersection(p1, p2, p3, p4);
			if(cross.x != 1e9) {
				isCrossed = true;
				break;
			}
		}
		if(!isCrossed) {
			strictSpeed.x += spdError[turn].x;
			strictSpeed.y += spdError[turn].y;
			strictPos.x += strictSpeed.x;
			strictPos.y += strictSpeed.y;
			rep(i,n) if(!activated[i] && strictPos.dist(p[i]) <= 1000) {
				cleared.pb(i);
			}
		}
		// out("#", pos.x+spd.x, pos.y+spd.y, "/", strictPos.x, strictPos.y, isCrossed, cleared)<<flush;
		#else
		def(int, b, c);
		isCrossed = b;
		if(c!=0){
			cleared.resize(c);
			in(cleared);
		}
		#endif

		if(isCrossed) {
			spd.x = 0;
			spd.y = 0;
			#ifdef _DEBUG
			strictSpeed.x = 0;
			strictSpeed.y = 0;
			#endif
		} else {
			pos.x += spd.x;
			pos.y += spd.y;
			for(auto&i : cleared) {
				if(!activated[i]){
					activated[i] = true;
					activatedCount++;
				}
			}
			if(activatedCount == n) exit(0);
		}
		turn++;
		if(turn >= 5000) exit(0);
		return isCrossed;
	}

	bool failsafeMove(int deg=0) {
		if(move()) {
			int currentPower = 500;
			float currentDegree = deg*PI/180;
			setSpd(currentPower*cos(currentDegree), currentPower*sin(currentDegree));
			failsafeMove(deg += 140);
			return true;
		}
		return false;
	}

	void setTarget(Point tgt) {
		Speed vc = {tgt.x-pos.x-spd.x, tgt.y-pos.y-spd.y};
		float x = sqrt(vc.x*vc.x + vc.y*vc.y);
		if(x >= 500) {
			vc.x /= (x / 500);
			vc.y /= (x / 500);
		}
		setSpd(vc.x, vc.y);
	}

	void solve() {
		pos = s;
		#ifdef _DEBUG
		strictPos = s;
		#endif
		activated.resize(n, false);

		auto ans = tsp(s, p);

		reverse(all(ans));
		vi queued;
		rep(n){
			int startTurn = turn;
			Point tgt = p[ans.back()]; 
			if(activated[ans.back()]) {
				ans.pop_back();
				continue;
			}
			while(!activated[ans.back()]) {
				setTarget(tgt);
				if(failsafeMove()){
					if(activated[ans.back()]) break;
				}
				if(pos.dist(tgt) <= 10) {
					while(!activated[ans.back()]) {
						setSpd(Random(-250, 250), Random(-250, 250));
						move();
					}
				}
				if(turn-startTurn >= 1000) {
					// 1000ターン経ってもクリアできない場合、次のターゲットに移動
					queued.pb(ans.back());
					break;
				}
				
			}
			ans.pop_back();
		}
		for(auto&i : queued) {
			if(activated[i]) continue;
			Point tgt = p[i];
			while(!activated[i]) {
				setTarget(tgt);
				if(failsafeMove()) {
					if(activated[i]) break;
				}
				if(pos.dist(tgt) <= 10) {
					while(!activated[i]) {
						setSpd(Random(-250, 250), Random(-250, 250));
						move();
					}
				}
			}
		}

	}
};

int main() { /**/
	{
		def(int,_);
		cin>>m>>E>>D;
		cin>>s.x>>s.y;
		rep(i,n) cin>>p[i].x>>p[i].y;

		edges.resize(m);
		rep(i,m) cin>>edges[i].p1.x>>edges[i].p1.y>>edges[i].p2.x>>edges[i].p2.y;
		edges.emplace_back(Point{-1e5, -1e5}, Point{1e5, -1e5});
		edges.emplace_back(Point{-1e5, -1e5}, Point{-1e5, 1e5});
		edges.emplace_back(Point{1e5, -1e5}, Point{1e5, 1e5});
		edges.emplace_back(Point{-1e5, 1e5}, Point{1e5, 1e5});

		#ifdef _DEBUG
		rep(i,5000) cin>>distError[i];
		rep(i,5000) cin>>spdError[i].x>>spdError[i].y;
		#endif

	}

	Solver solver;
	solver.solve();

	


}