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
	static const int TLE = 2000;
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

const int dy[] = {0, 1, 0, -1}, dx[] = {1, 0, -1, 0};

const int N = 6, M = 15, T = 10;
const int S = 2*N*(N-1);
using Power = array<int, M>;
using Gene = vector<vector<string>>;

vector<Power> initPower(S);
Power initMaxPower;

vector<Gene> _debug_u, _debug_v;
int _debug_t = 0;
vector<Power> sendSeed(vector<Power>& power, vvi&field) {
	vector<Power> result(S);
	out_f(field);
	#ifdef _DEBUG
	rep(i,N)rep(j,N-1){
		string rel = _debug_u[_debug_t][i][j];
		auto l = power[field[i][j]], r = power[field[i][j+1]];
		Power p = l;
		rep(k,M) if(rel[k] == '1') p[k] = r[k];
		result[i*(N-1)+j] = p;
	}
	rep(i,N-1)rep(j,N){
		string rel = _debug_v[_debug_t][i][j];
		auto l = power[field[i][j]], r = power[field[i+1][j]];
		Power p = l;
		rep(k,M) if(rel[k] == '1') p[k] = r[k];
		result[N*(N-1)+i*N+j] = p;
	}
	#else
	in(result);
	#endif
	_debug_t++;
	return result;
}

int calcScore(vector<Power>&power) {
	int maxResult = 0;
	rep(i,S) {
		chmax(maxResult, accumulate(all(power[i]), 0));
	}

	debug_f(maxResult, accumulate(all(initMaxPower), 0));
	return round(1e6 * maxResult / accumulate(all(initMaxPower), 0));
}

int target = 0;

// その種の評価値を返す。合計でいいのかは諸説
using PowerScore = int;
PowerScore getPowerScore (Power& power, vector<Power>&powers) {
	int sum = 0;
	rep(i,M) {
		int maxCount = 0;
		rep(j,S) {
			if(initMaxPower[i] == powers[j][i]) maxCount++;
		}
		if(maxCount == 1 && power[i] == initMaxPower[i]) sum += 100000;
		if(i != target){
			sum += 1000 / (initMaxPower[i] - power[i] + 1);
		}
	}
	sum += power[target] * 100000;
	return sum;
}

// 合計値が大きい順に並び替えた時の順位を返す
vi analyze_MaxScore(vector<Power> power) {
	vector<PowerScore> sumPower(S, 0);
	rep(i,S) {
		sumPower[i] = getPowerScore(power[i], power);
	}

	vi result(S);
	iota(all(result), 0);
	sort(all(result), [&](int a, int b) {
		return sumPower[a] > sumPower[b];
	});
	return result;
}

// 最小値が大きい順に並び替えた時の順位を返す
vvi analyze(vector<Power> power) {
	vi flatField(N*N);

	// while(true) {
	// 	auto cp=power;
	// 	sort(all(cp), [&](Power a, Power b) {
	// 		return a[target] > b[target];
	// 	});
	// 	if(initMaxPower[target] - cp[N*N-1][target] <= 2) {
	// 		target = (target + 1) % M;
	// 		if(target==0)break;
	// 	} else break;
	// }
	target++;


	vi scoreSums(S, 0);
	rep(i,S) {
		scoreSums[i] = accumulate(all(power[i]), 0);
	}

	const auto calcInnerScore = [&power, &scoreSums](vi&field) {
		// if(_debug_t == 9) {
		// 	int maxSum = 0;
		// 	rep(i,N)rep(j,N-1){
		// 		int sum = scoreSums[field[i*N+j]] + scoreSums[field[i*N+j+1]];
		// 		chmax(maxSum, sum);
		// 	}
		// 	rep(i,N-1)rep(j,N){
		// 		int sum = scoreSums[field[i*N+j]] + scoreSums[field[(i+1)*N+j]];
		// 		chmax(maxSum, sum);
		// 	}
		// 	return maxSum;
		// }
		// int score = 0;
		// rep(i,N)rep(j,N){
		// 	int odds = 4;
		// 	if(i==0 || i==N-1) odds--;
		// 	if(j==0 || j==N-1) odds--;
		// 	score += scoreSums[field[i*N+j]] * odds;
		// }
		int score = 0;
		rep(i,N)rep(j,N-1){
			auto l = power[field[i*N+j]], r = power[field[i*N+j+1]];
			score += abs(l[target] - r[target]);
		}
		rep(i,N-1)rep(j,N){
			auto l = power[field[i*N+j]], r = power[field[(i+1)*N+j]];
			score += abs(l[target] - r[target]);
		}
		return score;
	};

	vi finalField = flatField;
	auto finalScore = -INF;
	rep(i,M){
		{
			auto result = analyze_MaxScore(power);
			rep(i,N)rep(j,N) flatField[i*N+j] = result[i*N+j];
		}
		int bestScore = -INF;
		rep(1000) {
			vi testField = flatField;
			shuffle(all(testField), Random);
			auto score = calcInnerScore(testField);
			if(chmax(bestScore, score)) flatField = testField;
		}

		int counter = 0;
		while(counter < 100000){
			bool isChanged = false;
			rep(i,sz(flatField))rep(j,i) {
				counter++;
				vi swappedField = flatField;
				swap(swappedField[i], swappedField[j]);
				auto score = calcInnerScore(swappedField);
				if(chmax(bestScore, score)) {
					flatField = swappedField;
					isChanged = true;
				}
			}
			if(!isChanged) break;
		}
		debug(_debug_t, target, bestScore);

		if(chmax(finalScore, bestScore)) {
			finalField = flatField;
		}
	}
	

	vvi field(N, vi(N));
	rep(i,N)rep(j,N) field[i][j] = finalField[i*N+j];
	return field;
}


int main() {
	{
		def(int, _, __, ___);
		in(initPower);
		#ifdef _DEBUG
		rep(i,T){
			vector<vector<string>> u(N, vs(N-1)), v(N-1, vs(N));
			in(u, v);
			_debug_u.pb(u);
			_debug_v.pb(v);
		}
		#endif
		rep(i,M) initMaxPower[i] = 0;
		rep(i,S) {
			rep(j,M){
				chmax(initMaxPower[j], initPower[i][j]);
			}
		}
	}
	
	vector<Power> power = initPower;

	rep(T) {
		auto field = analyze(power);
		power = sendSeed(power, field);
	}


	debug_f(calcScore(power));

}



/*

0,1,2,3....,35 : 143,047,940 (548936)
sum降順: 209,668,175 (719149)


 */