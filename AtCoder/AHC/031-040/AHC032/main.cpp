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

template <int mod> struct ModInt {
	int x;
	ModInt() : x(0) {}
	ModInt(int64_t y) : x(y >= 0 ? y % mod : (mod - (-y) % mod) % mod) {}
	explicit operator bool() const { return x != 0; }
	explicit operator int64_t() const { return x; }
	ModInt operator+(const ModInt &p) const { return ModInt(*this) += p; }
	ModInt operator-(const ModInt &p) const { return ModInt(*this) -= p; }
	ModInt operator-() const { return ModInt(-x); }
	ModInt &operator+=(const ModInt &p) { if((x += p.x) >= mod) x -= mod; return *this; }
	ModInt &operator-=(const ModInt &p) { if((x += mod - p.x) >= mod) x -= mod; return *this; }
	friend ModInt operator+(int64_t a, const ModInt &p) { return p+a; }
	friend ModInt operator-(int64_t a, const ModInt &p) { return -p+a; }
	bool operator==(const ModInt &p) const { return x == p.x; }
	bool operator!=(const ModInt &p) const { return x != p.x; }
	bool operator<(const ModInt &p) const { return x < p.x; }
	friend istream &operator>>(istream &is, ModInt &p) { int64_t t; is >> t; p = ModInt(t); return is; }
	friend ostream &operator<<(ostream &os, const ModInt &p) { return os << p.x; }
};
using mymint = ModInt<MOD>;
using vm = vector<mymint>;
using vvm = vector<vm>;
mymint operator"" _m(unsigned long long a){ return mymint(a); }



const int n=9,m=20,k=81;
using Field = valarray<ll>;
using Action = tuple<int,int,int>;
vector<Action> output;

const int STAMP_MAX = 5;


const auto applyMod = [](Field& f) {
	rep(i,n*n) f[i] %= MOD;
};

int main() { /**/
	{
		def(int,_,__,___);
	}
	vvl a(n,vl(n));
	vvl stamp(m, vl(9));
	in(a); in(stamp);

	Field f(n*n);
	rep(i,n)rep(j,n) f[i*n+j] = a[i][j];
	vector<Field> s(m);
	rep(i,m){
		s[i].resize(n*n);
		rep(j,3)rep(k,3) s[i][j*n+k] = stamp[i][j*3+k];
	}

	debug("Base  :\t", f.sum());
	vector<pair<Field, vi>> multiStamp;
	multiStamp.pb({Field(0ll, 81), vi{}});
	rep(_c, STAMP_MAX){
		int csz=sz(multiStamp);
		rep(i,csz){
			auto [f, idx] = multiStamp[i];
			int startJ = idx.empty() ? 0 : idx.back();
			rep(j,startJ, m){
				auto nf = f + s[j];
				auto nidx = idx;
				nidx.pb(j);
				multiStamp.pb({nf, nidx});
			}
		}
		debug("Stamp Count:" , _c, sz(multiStamp)-csz);
	}
	debug(Mgr::timer.get(),"ms");

	const auto appendMultiStamp = [&multiStamp](Field&f, int idx, int y, int x) {
		f += multiStamp[idx].first.shift(-(y*n+x));
		for(auto i : multiStamp[idx].second) output.eb(i, y, x);
	};


	const function<pair<int,ll>(Field&,int,int,int,int,int,int,int)> searchBestMultiStamp = [&multiStamp](Field& f, int y, int x, int tt, int tb, int tl, int tr, int limit) {
		ll maxVal = 0, idx = -1;
		const ll rironchi = (MOD-1) * (tb-tt) * (tr-tl);
		rep(i,sz(multiStamp)){
			if(sz(multiStamp[i].second) > limit) break;
			ll val = 0, loss = 0;
			rep(j,tt,tb)rep(k,tl,tr){
				const int cellValue = (f[(y+j)*n+(x+k)] + multiStamp[i].first[j*n+k]) % MOD;
				val += cellValue;
				loss += MOD-1-cellValue;
				if(loss > rironchi-maxVal) {
					j=tb; break;
				}
			}
			if(chmax(maxVal, val)) idx = i;
		}
		//out(y,x,tt,tb,tl,tr,maxVal, idx);
		return make_pair(idx, maxVal);
	};

	const auto fillBestMultiStamp = [&searchBestMultiStamp, &appendMultiStamp](Field& f, int y, int x, int tt, int tb, int tl, int tr, int limit) {
		auto [idx, val] = searchBestMultiStamp(f, y, x, tt, tb, tl, tr, limit);
		if(idx != -1) {
			appendMultiStamp(f, idx, y, x);
		}
		return val;
	};

	const auto simulate1 = [&searchBestMultiStamp, &fillBestMultiStamp, &appendMultiStamp](Field&f, bool isttb, bool isltr, int limit) {
		output.clear();
		const int sTT = isttb ? 0 : 2;
		const int sTL = isltr ? 0 : 2;
		rep(_y,6){
			int y = isttb ? _y : 6-_y;
			rep(_x,6){
				int x = isltr ? _x : 6-_x;
				rep(lim,0,4){
					auto [idx, val] = searchBestMultiStamp(f, y, x, sTT, sTT+1, sTL, sTL+1, lim);
					if(val >= limit) {
						appendMultiStamp(f, idx, y, x);
						break;
					}
				}
			}
		}

		int baseMax = (k-sz(output)-STAMP_MAX) / 12;
		int remainAction = 12;

		const auto vertical = [&](int i) {
			baseMax = (k-sz(output)-STAMP_MAX) / remainAction;
			remainAction--;
			int y = isttb ? i : 6-i;
			int x = isltr ? 6 : 0;
			int sTT = isttb ? 0 : 2;
			fillBestMultiStamp(f, y, x, sTT,sTT+1, 0,3, (k-sz(output)-baseMax*remainAction-STAMP_MAX));
		};
		const auto horizontal = [&](int i) {
			baseMax = (k-sz(output)-STAMP_MAX) / remainAction;
			remainAction--;
			int y = isttb ? 6 : 0;
			int x = isltr ? i : 6-i;
			int sTL = isltr ? 0 : 2;
			fillBestMultiStamp(f, y, x, 0,3, sTL,sTL+1, (k-sz(output)-baseMax*remainAction-STAMP_MAX));
		};

		// uneffected
		rep(i,0,4) vertical(i);
		rep(i,0,4) horizontal(i);
		applyMod(f);
		
		ll retVal = 0;
		rep(h,6)rep(w,6){
			retVal += f[(isttb ? h+0 : h+3)*n+(isltr ? w+0 : w+3)];
		}
		rep(h,4)rep(w,3){
			retVal += f[(isttb ? h+0 : h+5)*n+(isltr ? w+6 : w+0)];
		}
		rep(h,3)rep(w,4){
			retVal += f[(isttb ? h+6 : h+0)*n+(isltr ? w+0 : w+5)];
		}
		return retVal;
	};
	

	const auto simulate2 = [&searchBestMultiStamp, &fillBestMultiStamp, &appendMultiStamp](Field&f, bool isttb, bool isltr, int v1, int v2) {
		int baseMax = (k-sz(output)-STAMP_MAX) / 4;
		int remainAction = 4;

		const auto vertical = [&](int i) {
			baseMax = (k-sz(output)-STAMP_MAX) / remainAction;
			remainAction--;
			int y = isttb ? i : 6-i;
			int x = isltr ? 6 : 0;
			int sTT = isttb ? 0 : 2;
			return fillBestMultiStamp(f, y, x, sTT,sTT+1, 0,3, (k-sz(output)-baseMax*remainAction-STAMP_MAX));
		};
		const auto horizontal = [&](int i) {
			baseMax = (k-sz(output)-STAMP_MAX) / remainAction;
			remainAction--;
			int y = isttb ? 6 : 0;
			int x = isltr ? i : 6-i;
			int sTL = isltr ? 0 : 2;
			return fillBestMultiStamp(f, y, x, 0,3, sTL,sTL+1, (k-sz(output)-baseMax*remainAction-STAMP_MAX));
		};

		// effected
		int hc=0;
		ll decidedScore = 0;
		rep(i,4){
			if(i==v1) decidedScore+=vertical(4);
			else if(i==v2) decidedScore+=vertical(5);	
			else  decidedScore+=horizontal(4+(hc++));
		}

		return decidedScore;
	};

	const auto simulate3 = [&fillBestMultiStamp](Field&f, bool isttb, bool isltr) {
		int y = isttb ? 6 : 0;
		int x = isltr ? 6 : 0;
		fillBestMultiStamp(f, y, x, 0,3, 0,3, k-sz(output));
		applyMod(f);
		return f.sum();
	};
	

	ll bestScore = 0;
	auto answer = output;
	vi limits = {
//		885000000,
		890000000,
//		895000000,
		900000000,
		905000000,
		910000000,
//		915000000,
		920000000,
//		925000000,
		930000000,
//		935000000,
		940000000,
//		945000000,
//		950000000,
	};

	const auto compare = [](const tuple<ll, bool, bool, Field, vector<Action>>& f1, tuple<ll, bool, bool, Field, vector<Action>>& f2) {
		return get<0>(f1) < get<0>(f2);
	};
	priority_queue<
		tuple<ll, bool, bool, Field, vector<Action>>,
		vector<tuple<ll, bool, bool, Field, vector<Action>>>,
		decltype(compare)> pq(compare);
	rep(isttb,2)rep(isltr,2)for(auto limit: limits){
		auto _f = f;
		auto decidedScore = simulate1(_f, isttb, isltr, limit);
		debug(isttb, isltr, limit, decidedScore);
		pq.emplace(decidedScore, isttb, isltr, _f, output);
	}

	ll prevScore1 = LINF;
	while(!pq.empty()){

		auto [_score, isttb, isltr, _f, prevOutput] = pq.top(); pq.pop();
		if(_score == prevScore1) continue;
		prevScore1 = _score;
		debug(_score,  isttb, isltr);

		unordered_set<ll> dScoreSet;;
		rep(v1,0,3)rep(v2,v1+1,4){
			if(Mgr::timer.get() >= 1800) {
				v1=v2=INF;
				break;
			}
			auto __f = _f;
			output = prevOutput;
			auto dScore = simulate2(__f, isttb, isltr, v1, v2);
			if(dScoreSet.contains(dScore)) continue;
			dScoreSet.insert(dScore);
			auto score = simulate3(__f, isttb, isltr);
			if(chmax(bestScore, score)) answer = output;
			debug(isttb, isltr, v1, v2, "\t ->", score, "\t (", Mgr::timer.get(), "ms)", dScore);
		}
		if(Mgr::timer.get() >= 1800) {
			break;
		}
	}

	out(answer.size());
	for(auto&[i,y,x] : answer) out(i, y, x);
}