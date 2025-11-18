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
	static const int TLE = 2000;
	#else
	static const int TLE = 2000;
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

/**
 * 方針案
 * 鬼にindexを振り、落とす順番を焼きなます
 * 
 */

const int N = 20;

struct Oni {
	int r,c;
	bool alive;
};

vector<HashSet<int>> oniv(N), fukuv(N), onih(N), fukuh(N);
vector<Oni> demons;

// 列cを、vec方向にdistだけ動かした時、fukuが外に出ずに動かせるか？
auto canMoveVertical(int c, int vec, int dist) {
	bool ok=true;
	// fukuv[c] の各要素について、+dist*vec した時に範囲外になるかどうか
	for(auto r : fukuv[c]) {
		if(r+dist*vec<0 || N<=r+dist*vec) {
			ok=false;
			break;
		}
	}
	return ok;
}

// 行rを、vec方向にdistだけ動かした時、fukuが外に出ずに動かせるか？
auto canMoveHorizontal(int r, int vec, int dist) {
	bool ok=true;
	// fukuh[r] の各要素について、+dist*vec した時に範囲外になるかどうか
	for(auto c : fukuh[r]) {
		if(c+dist*vec<0 || N<=c+dist*vec) {
			ok=false;
			break;
		}
	}
	return ok;
}

// vec方向に動かした時、oniだけ落とせるか? [落とせる鬼の数, 動かすべきマス数]を返す
auto canEscape(const HashSet<int> &fuku, const HashSet<int> &oni, int vec, int tgt) {
	bool ok=false;
	int cnt=0, dist=0, lastOniDist=0;
	int val= vec==1 ? N-1 : 0;
	while(0<=val && val<N) {
		if(fuku.contains(val)) break;
		dist++;
		if(oni.contains(val)) {
			if(val==tgt) ok=true;
			cnt++;
			lastOniDist = dist;
		}
		val-=vec;
	}
	if(!ok) cnt=0;
	return make_pair(cnt,lastOniDist);
}

auto canEscape2(const HashSet<int> &fuku, const HashSet<int> &oni, int vec, int tgt) {
	bool ok=false;
	int cnt=0, dist=0, lastOniDist=0;
	int val= vec==1 ? N-1 : 0;
	while(0<=val && val<N) {
		if(fuku.contains(val)) break;
		dist++;
		if(oni.contains(val)) {
			if(val==tgt) ok=true;
			cnt++;
			lastOniDist = dist;
		}
		val-=vec;
	}
	if(!ok) cnt=0;
	return make_tuple(cnt,lastOniDist, dist);
}


void moveVertical(int c, int vec, int dist) {
	int val = vec==1 ? N-1 : 0;
	vi oniMap(N,-1);
	rep(d,demons.size()) {
		if(demons[d].c==c && demons[d].alive) {
			oniMap[demons[d].r] = d;
		}
	}
	rep(dist) {
		if(oniv[c].contains(val)) {
			oniv[c].erase(val);
			onih[val].erase(c);
			demons[oniMap[val]].alive = false;
		}
		val-=vec;
	}
	while(0<=val && val<N) {
		if(oniMap[val]!=-1) {
			demons[oniMap[val]].r += dist * vec;
			oniv[c].erase(val);
			oniv[c].insert(val+dist*vec);
			onih[val].erase(c);
			onih[val+dist*vec].insert(c);
		}else if(fukuv[c].contains(val)) {
			fukuv[c].erase(val);
			fukuv[c].insert(val+dist*vec);
			fukuh[val].erase(c);
			fukuh[val+dist*vec].insert(c);
		}
		val-=vec;
	}
}

void moveHorizontal(int r, int vec, int dist) {
	int val = vec==1 ? N-1 : 0;
	vi oniMap(N,-1);
	rep(d,demons.size()) {
		if(demons[d].r==r && demons[d].alive) {
			oniMap[demons[d].c] = d;
		}
	}
	rep(dist) {
		if(onih[r].contains(val)) {
			onih[r].erase(val);
			oniv[val].erase(r);
			demons[oniMap[val]].alive = false;
		}
		val-=vec;
	}
	while(0<=val && val<N) {
		if(oniMap[val]!=-1) {
			demons[oniMap[val]].c += dist * vec;
			onih[r].erase(val);
			onih[r].insert(val+dist*vec);
			oniv[val].erase(r);
			oniv[val+dist*vec].insert(r);
		}else if(fukuh[r].contains(val)) {
			fukuh[r].erase(val);
			fukuh[r].insert(val+dist*vec);
			fukuv[val].erase(r);
			fukuv[val+dist*vec].insert(r);
		}
		val-=vec;
	}
}



// 列cをvec方向に動かして、demons[tgt]を落としたい。この時に必要な動かしかたを返す
// この時、落とす過程で他のラインの鬼も合流できそうなら混ざる。
// 「合流できそう」の基準... その鬼がいる列と、動かす列の距離が2以下かつ、合流するように動かした時に福が飛び出さない
tuple<int, int, vector<tuple<int,int,int>>> optimizeEscapeVertical(int c, int vec, int tgt) {
	auto copiedOniv = oniv, copiedFukuv = fukuv;
	auto copiedOnih = onih, copiedFukuh = fukuh;
	auto copiedDemons = demons;

	vi oniMap(N,-1);
	rep(d,demons.size()) {
		if(demons[d].c==c && demons[d].alive) {
			oniMap[demons[d].r] = d;
		}
	}

	vector<tuple<int,int,int>> actions;
	auto [oniCount,oniDist, dist] = canEscape2(fukuv[c],oniv[c], vec, demons[tgt].r);
	if(oniCount==0) return make_tuple(0, 0, actions);

	vector<HashSet<int>> onihi(N);
	rep(d,demons.size()) {
		if(demons[d].alive) {
			onihi[demons[d].r].insert(d);
		}
	}

	int count=0, actionLength=0;
	int unmeanedCount=0;
	rep(lp,dist) {
		// いまの対象列の、空白な行に他の鬼を入れてみようとする
		rep(i, dist-lp) {
			int r=(vec==1 ? N-1 : 0) - i*vec;
			if(oniMap[r]!=-1) continue;
			// 行rの最も近い鬼を探す
			int nearOni = -1, nearDist = 3; //TODO
			for(auto d : onihi[r]) {
				if(demons[d].c==c) continue;
				if(abs(demons[d].c-c)<nearDist) {
					auto horVec = demons[d].c<c ? 1 : -1;
					auto available = canMoveHorizontal(demons[d].r, horVec, abs(demons[d].c-c));
					if(available) {
						nearDist = abs(demons[d].c-c);
						nearOni = d;
						if(nearDist==1) break;
					}
				}
			}

			if(nearOni==-1) continue;
			// 鬼を移動させる
			actions.eb(r, demons[nearOni].c < c ? 3 : 1, nearDist);
			actionLength+=nearDist;
			moveHorizontal(demons[nearOni].r, demons[nearOni].c < c ? 1 : -1, nearDist);
			oniMap[r] = nearOni;
		}

		// いまの対象列を動かす
		actions.eb(c, vec==1 ? 2 : 0, 1);
		actionLength++;
		moveVertical(c, vec, 1);
		// oniMapを1つずらす
		if(vec==1){
			if(oniMap[N-1]!=-1) {
				count++;
				unmeanedCount=0;
			} else {
				unmeanedCount++;
			}
			rrep(i,1,N) oniMap[i] = oniMap[i-1];
			oniMap[0] = -1;
		}else if(vec==-1){
			if(oniMap[0]!=-1) {
				count++;
				unmeanedCount=0;
			} else {
				unmeanedCount++;
			}
			rep(i,N-1) oniMap[i] = oniMap[i+1];
			oniMap[N-1] = -1;
		}
	}
	rep(unmeanedCount) {
		actions.pop_back();
	}

	// 戻す
	oniv = copiedOniv;
	fukuv = copiedFukuv;
	onih = copiedOnih;
	fukuh = copiedFukuh;
	demons = copiedDemons;

	return make_tuple(count, actionLength, actions);
}

tuple<int, int, vector<tuple<int,int,int>>> optimizeEscapeHorizontal(int r, int vec, int tgt) {
	auto copiedOniv = oniv, copiedFukuv = fukuv;
	auto copiedOnih = onih, copiedFukuh = fukuh;
	auto copiedDemons = demons;

	vi oniMap(N,-1);
	rep(d,demons.size()) {
		if(demons[d].r==r && demons[d].alive) {
			oniMap[demons[d].c] = d;
		}
	}

	vector<tuple<int,int,int>> actions;
	auto [oniCount,oniDist, dist] = canEscape2(fukuh[r],onih[r], vec, demons[tgt].c);
	if(oniCount==0) return make_tuple(0, 0, actions);

	vector<HashSet<int>> onivi(N);
	rep(d,demons.size()) {
		if(demons[d].alive) {
			onivi[demons[d].c].insert(d);
		}
	}

	int count=0, actionLength=0;
	int unmeanedCount=0;
	rep(lp,dist) {
		// いまの対象列の、空白な行に他の鬼を入れてみようとする
		rep(i, dist-lp) {
			int c=(vec==1 ? N-1 : 0) - i*vec;
			if(oniMap[c]!=-1) continue;
			// 行rの最も近い鬼を探す
			int nearOni = -1, nearDist = 3; //TODO
			for(auto d : onivi[c]) {
				if(demons[d].r==r) continue;
				if(abs(demons[d].r-r)<nearDist) {
					auto verVec = demons[d].r<r ? 1 : -1;
					auto available = canMoveVertical(demons[d].c, verVec, abs(demons[d].r-r));
					if(available) {
						nearDist = abs(demons[d].r-r);
						nearOni = d;
						if(nearDist==1) break;
					}
				}
			}

			if(nearOni==-1) continue;
			// 鬼を移動させる
			actions.eb(c, demons[nearOni].r < r ? 2 : 0, nearDist);
			actionLength+=nearDist;
			moveVertical(demons[nearOni].c, demons[nearOni].r < r ? 1 : -1, nearDist);
			oniMap[c] = nearOni;
		}

		// いまの対象列を動かす
		actions.eb(r, vec==1 ? 3 : 1, 1);
		actionLength++;
		moveHorizontal(r, vec, 1);
		// oniMapを1つずらす
		if(vec==1){
			if(oniMap[N-1]!=-1) {
				count++;
				unmeanedCount=0;
			} else {
				unmeanedCount++;
			}
			rrep(i,1,N) oniMap[i] = oniMap[i-1];
			oniMap[0] = -1;
		}else if(vec==-1){
			if(oniMap[0]!=-1) {
				count++;
				unmeanedCount=0;
			} else {
				unmeanedCount++;
			}
			rep(i,N-1) oniMap[i] = oniMap[i+1];
			oniMap[N-1] = -1;
		}
	}

	rep(unmeanedCount) {
		actions.pop_back();
	}

	// 戻す
	oniv = copiedOniv;
	fukuv = copiedFukuv;
	onih = copiedOnih;
	fukuh = copiedFukuh;
	demons = copiedDemons;

	return make_tuple(count, actionLength, actions);
}



void appliedActions(vector<tuple<int,int,int>> actions) {
	for(auto [a,b,c] : actions) {
		if(b%2==0) {
			moveVertical(a, b==0 ? -1 : 1, c);
		}else {
			moveHorizontal(a, b==1 ? -1 : 1, c);
		}
	}
}

auto escapeVertical(int c, int vec, int dist) {
	int val = vec==1 ? N-1 : 0;
	vi oniMap(N,-1);
	rep(d,demons.size()) {
		if(demons[d].c==c && demons[d].alive) {
			oniMap[demons[d].r] = d;
		}
	}
	rep(dist) {
		if(oniv[c].contains(val)) {
			oniv[c].erase(val);
			onih[val].erase(c);
			demons[oniMap[val]].alive = false;
		}
		val-=vec;
	}
	while(0<=val && val<N) {
		if(oniMap[val]!=-1) {
			demons[oniMap[val]].r += dist * vec;
			oniv[c].erase(val);
			oniv[c].insert(val+dist*vec);
			onih[val].erase(c);
			onih[val+dist*vec].insert(c);
		}else if(fukuv[c].contains(val)) {
			fukuv[c].erase(val);
			fukuv[c].insert(val+dist*vec);
			fukuh[val].erase(c);
			fukuh[val+dist*vec].insert(c);
		}
		val-=vec;
	}
}

auto escapeHorizontal(int r, int vec, int dist) {
	int val = vec==1 ? N-1 : 0;
	vi oniMap(N,-1);
	rep(d,demons.size()) {
		if(demons[d].r==r && demons[d].alive) {
			oniMap[demons[d].c] = d;
		}
	}
	rep(dist) {
		if(onih[r].contains(val)) {
			onih[r].erase(val);
			oniv[val].erase(r);
			demons[oniMap[val]].alive = false;
		}
		val-=vec;
	}
	while(0<=val && val<N) {
		if(oniMap[val]!=-1) {
			demons[oniMap[val]].c += dist * vec;
			onih[r].erase(val);
			onih[r].insert(val+dist*vec);
			oniv[val].erase(r);
			oniv[val+dist*vec].insert(r);
		}else if(fukuh[r].contains(val)) {
			fukuh[r].erase(val);
			fukuh[r].insert(val+dist*vec);
			fukuv[val].erase(r);
			fukuv[val+dist*vec].insert(r);
		}
		val-=vec;
	}
}

auto simulate(vector<int> order) {
	// debug(order);
	int score=0;
	vector<tuple<int,int,int>> actions;
	// 後ろからpopして処理
	int failedCount=0;
	while(!order.empty()) {
		int idx = order.back();
		order.pop_back();
		// debug("idx", idx, demons[idx].alive);
		if(!demons[idx].alive) continue;

		// ベストな方向を決める
		int dir = -1, bestOniCount=0, bestDist = INF;

		int oniCount,dist;
		vector<tuple<int,int,int>> bestOptActions, optActions;
		int bestMode=0;
		rep(d,4) {	// U,L,D,R
			if(d%2==0) {
				// tie(oniCount,dist) = canEscape(fukuv[demons[idx].c],oniv[demons[idx].c], d==0 ? -1 : 1, demons[idx].r);
				tie(oniCount,dist,optActions) = optimizeEscapeVertical(demons[idx].c, d==0 ? -1 : 1, demons[idx].r);
			} else {
				// tie(oniCount,dist) = canEscape(fukuh[demons[idx].r],onih[demons[idx].r], d==1 ? -1 : 1, demons[idx].c);
				tie(oniCount,dist,optActions) = optimizeEscapeHorizontal(demons[idx].r, d==1 ? -1 : 1, demons[idx].c);
			}
			
			if(oniCount>bestOniCount || (oniCount==bestOniCount && dist<bestDist)) {
				// debug("  ","ULDR"[d], oniCount, dist);
				bestOniCount = oniCount;
				bestDist = dist;
				bestOptActions = optActions;
				dir = d;
				bestMode = 0;
			}

			if(d%2==0) {
				tie(oniCount,dist) = canEscape(fukuv[demons[idx].c],oniv[demons[idx].c], d==0 ? -1 : 1, demons[idx].r);
				// tie(oniCount,dist,optActions) = optimizeEscapeVertical(demons[idx].c, d==0 ? -1 : 1, demons[idx].r);
			} else {
				tie(oniCount,dist) = canEscape(fukuh[demons[idx].r],onih[demons[idx].r], d==1 ? -1 : 1, demons[idx].c);
				// tie(oniCount,dist,optActions) = optimizeEscapeHorizontal(demons[idx].r, d==1 ? -1 : 1, demons[idx].c);
			}
			// debug("  ","ULDR"[d], oniCount, dist);
			if(oniCount==0)continue;
			if(oniCount>bestOniCount || (oniCount==bestOniCount && dist<bestDist)) {
				bestOniCount = oniCount;
				bestDist = dist;
				bestOptActions = optActions;
				dir = d;
				bestMode = 1;
			}
		}
		// debug("=", idx, dir, bestOniCount, bestDist);

		// 落とす
		if(dir==-1) {
			// insert front idx
			order.insert(order.begin(), idx);
			failedCount++;
			if(failedCount>order.size()) {
				// debug("Failed");
				return make_pair(INF,actions);
			}
			continue;
		}
		failedCount=0;
		score+=bestDist;
		if(dir%2==0) {
			if(bestMode==0) {
				actions.insert(actions.end(), bestOptActions.begin(), bestOptActions.end());
				appliedActions(bestOptActions);
			} else {
				actions.eb(demons[idx].c, dir, bestDist);
				escapeVertical(demons[idx].c, dir==0 ? -1 : 1, bestDist);
			}
		} else {
			if(bestMode==0) {
				actions.insert(actions.end(), bestOptActions.begin(), bestOptActions.end());
				appliedActions(bestOptActions);
			} else {
				actions.eb(demons[idx].r, dir, bestDist);
				escapeHorizontal(demons[idx].r, dir==1 ? -1 : 1, bestDist);
			}
		}

		// {
		// 	int oc=0, oc2=0;
		// 	vs field(N), field2(N);
		// 	rep(i,N){
		// 		field[i] = string(N,'.');
		// 		field2[i] = string(N,'.');
		// 	}
		// 	rep(i,N){
		// 		for(auto r : onih[i]) {
		// 			field[i][r] = 'x';
		// 			oc++;
		// 		}
		// 		for(auto r : fukuh[i]) field[i][r] = 'o';
		// 		for(auto r : oniv[i]) field2[r][i] = 'x';
		// 		for(auto r : fukuv[i]) field2[r][i] = 'o';
		// 	}
		// 	out_f("Actions", idx, dir, bestDist);
		// 	out_f("is_same", field==field2);
		// 	out_f(field);
		// 	rep(i,2*N) {
		// 		if(demons[i].alive) {
		// 			out("demon", i, demons[i].r, demons[i].c, demons[i].alive);
		// 			oc2++;
		// 			if(field[demons[i].r][demons[i].c]!='x') {
		// 				out("error", i, demons[i].r, demons[i].c);
		// 			}
		// 		}
		// 	}
		// 	out("oc", oc, oc2);
		// 	out_f("====");
		// 	if(field!=field2 or oc!=oc2) {
		// 		debug("error");
		// 		exit(1);
		// 	}
		// }
	}

	return make_pair(score,actions);

}

int main() {
	vector<Oni> _demons;
	vector<HashSet<int>> _oniv(N), _fukuv(N), _onih(N), _fukuh(N);

	{
		def(int,_);
		rep(i,N){
			def(string,s);
			rep(j,N){
				if(s[j]=='o') {
					_fukuv[j].insert(i);
					_fukuh[i].insert(j);
				}
				if(s[j]=='x') {
					_oniv[j].insert(i);
					_onih[i].insert(j);
					_demons.push_back(Oni{i,j,true});
				}
			}
		}
	}

	vector<int> order(_demons.size());
	iota(all(order),0);


	int tried=0;
	int answerScore = INF;
	vector<tuple<int,int,int>> answerActions;

	while(Mgr::timer){
		int bestScore = INF;
		vector<tuple<int,int,int>> bestActions;

		shuffle(all(order), Random);

		while(Mgr::timer){
			tried++;
			oniv = _oniv;
			fukuv = _fukuv;
			onih = _onih;
			fukuh = _fukuh;
			demons = _demons;

			auto [score, actions] = simulate(order);
			if(chmin(bestScore, score)) {
				debug(score);
				bestActions = actions;
			}
			if(score!=INF) break;
			shuffle(all(order), Random);
		}

		int fail=0;
		while(Mgr::timer){
			tried++;
			oniv = _oniv;
			fukuv = _fukuv;
			onih = _onih;
			fukuh = _fukuh;
			demons = _demons;

			auto newOrder = order;
			int idx = Random(0, sz(order)-1);
			int idx2 = Random(idx+1, sz(order));
			swap(newOrder[idx], newOrder[idx2]);

			auto [score, actions] = simulate(newOrder);
			if(chmin(bestScore, score)) {
				fail=0;
				// debug("!", score);
				bestActions = actions;
				order=newOrder;
			}else{
				fail++;
				if(fail>1000) break;
			}
		}
		if(chmin(answerScore, bestScore)) {
			debug(bestScore);
			answerActions = bestActions;
		}

		break;

	}

	for(auto [idx, d, dist] : answerActions) {
		rep(dist){
			if(d%2==0) {
				out_f((d==0 ? 'U' : 'D'), idx);
			} else {
				out_f((d==1 ? 'L' : 'R'), idx);
			}
		}
	}

	debug("score", answerScore);
	debug("tried", tried);
	


}