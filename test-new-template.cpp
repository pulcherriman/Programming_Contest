#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("inline")
#ifdef _DEBUG
// #define _GLIBCXX_DEBUG 1
#endif

/* 
 * Include Headers
 */
#if defined(EVAL) || defined(ONLINE_JUDGE) || defined(_DEBUG)
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
template<class K> using IndexedSet=__gnu_pbds::tree<K,__gnu_pbds::null_type,less<K>,__gnu_pbds::rb_tree_tag,__gnu_pbds::tree_order_statistics_node_update>;
template<class K> using HashSet=__gnu_pbds::gp_hash_table<K,__gnu_pbds::null_type>;
template<class K,class V> using IndexedMap=__gnu_pbds::tree<K,V,less<K>,__gnu_pbds::rb_tree_tag,__gnu_pbds::tree_order_statistics_node_update>;
template<class K,class V> using HashMap=__gnu_pbds::gp_hash_table<K,V>;
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
#define __RANGE(i,a,n) for(int i=((int)a);i<((int)n);++i)
#define __RREP(i,n) __RRANGE(i,0,n)
#define __RRANGE(i,a,n) for(int i=((int)n-1);i>=((int)a);--i)
#define sz(a) ((int)(a).size())


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
template<class T>constexpr bool chmax(T&a,T b){return a<b?a=b,1:0;}
template<class T>constexpr bool chmin(T&a,T b){return a>b?a=b,1:0;}
template<class S>S sum(vector<S>&a){return accumulate(all(a),S());}
template<class S>S max(vector<S>&a){return *max_element(all(a));}
template<class S>S min(vector<S>&a){return *min_element(all(a));}

namespace IO {
	namespace IO_Inner {
		template<class T, class...Ts> constexpr ostream& print_args(ostream&os, T&&t, Ts&&...args) {
			return ((os<<t)<<...<<(os<<' ', args));
		}
	}

	template<class...Ts> constexpr ostream& print(Ts...args) {
		return IO_Inner::print_args(cout, args...)<<'\n';
	}
	template<class...Ts> constexpr ostream& debug_f(Ts...args) {
		return IO_Inner::print_args(cerr, args...)<<'\n';
	}
	#ifdef _DEBUG
	template<class...Ts> constexpr ostream& debug(Ts...args) {
		return IO_Inner::print_args(cerr, args...)<<'\n';
	}
	#else
	static inline ostream& debug(...) { return cerr; }
	#endif

	template<class S,class T>constexpr ostream&operator<<(ostream&os,pair<S,T>p){
		return os<<'['<<p.first<<", "<<p.second<<']';
	};
	template<class...Ts>constexpr ostream&operator<<(ostream&os,tuple<Ts...>t){
		return apply([&os](auto&&t,auto&&...args)->ostream&{return IO_Inner::print_args(os, t, args...);}, t);
	};

	template<typename T, typename _=void> struct is_container : false_type {};
	template<> struct is_container<string> : false_type {};
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
		if(t.empty()) return os;
		auto b=begin(t); os<<(*b++);
		for(const auto&&e=end(t);b!=e;++b) os<<Separator<<(*b);
		return os;
	}
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
	uint64_t get() const{return (getClocks()-start)/ClocksPerMsec;}
	operator bool()const{return getClocks()<limit;}
};
void wait(const int&msec){Timer tm(msec); while(tm);}

struct Manager {
	static const int TLE = 2000;
	static inline Timer baseTimer = Timer(TLE);
	Manager() {
		ios_base::sync_with_stdio(0), cin.tie(0);
		cout<<fixed<<setprecision(11);
	}
	~Manager(){
		debug_f(baseTimer.get(), "ms")<<flush;
	}
} _manager;

namespace std::tr1 {
	template<class T>
	struct hash_base {
		static inline size_t hash_value = 0x9e3779b9;
		static inline size_t hash_rnd = Random(0, numeric_limits<size_t>::max());
		template<class V> static size_t& do_hash(size_t&seed, V&v) {
			return seed ^= hash<V>{}(v) + hash_value + (seed<<6) + (seed>2);
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
}

void output() {
	auto output_test = [](auto&&t){
		cout<<t<<endl;
		debug(t);
	};

	// primitive
	print(false, 1, 2.3, "abc", 'D');

	// pair, tuple
	output_test(make_pair("XYZ", LINF));
	output_test(make_tuple("tuple", "of", "taputapu"));

	// string, char*
	auto test = "HOGE";
	string str = "PIYO";
	output_test(test);		// const char *
	output_test("FUGA");	// const char(&)[5]
	output_test(str);		// std::string
	output_test("POYA"s);	// std::__cxx11::basic_string<char>

	// iterator
	deque<int> d1(10); iota(all(d1), 0);
	output_test(d1);

	array<int,10> d2; iota(all(d2), 10);
	output_test(d2);
	
	// nested iterator
	vector<array<int, 10>> d3(10); rep(i,10)iota(all(d3[i]), 100+i*10);
	output_test(d3);

	// map, set
	map<int, string> m1;
	m1[0] = "ABC";
	m1[1] = "DEF";
	m1[2] = "GHI";
	output_test(m1);

	set<ld> s1;
	s1.insert(1.1);
	s1.insert(2.2);
	s1.insert(3.3);
	output_test(s1);

	unordered_set<ld> us1(all(s1));
	output_test(us1);

	HashSet<ld> hs1(all(s1));
	output_test(hs1);

	// empty data
	s1.clear();
	output_test(s1);
}

void hashable(){
	auto hash_test = [](auto&&t){
		cout<<t<<endl;
		debug(t);
	};
	HashSet<int> hs1;
	hs1.insert(1);
	hs1.insert(2);
	hash_test(hs1);

	HashSet<pii> hs2;
	hs2.insert(make_pair(1,2));
	hs2.insert(make_pair(3,4));
	hash_test(hs2);
}

int main() {
	output();
	hashable();
}