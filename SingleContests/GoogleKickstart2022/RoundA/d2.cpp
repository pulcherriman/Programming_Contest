/*
 * Unsecured Optimization
 */
#pragma GCC optimize "O3" /* 最適化 */
#pragma GCC target "avx" /* SIMD(ベクトル化) */
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native") /* 浮動小数点数のSIMD */
// #pragma GCC optimize "fast-math"
// #pragma GCC optimize "unroll-loops" /* ループの展開 */
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
		template<class T, class...Args> constexpr ostream& print_args(ostream&os, T&&t, Args&&...args) {
			return ((os<<t)<<...<<(os<<' ', args));
		}
	}

	constexpr char CHAR_BR='\n';
	template<class...Args> constexpr ostream& print(Args...args) {
		return IO_Inner::print_args(cout, args...)<<CHAR_BR;
	}
	template<class...Args> constexpr ostream& debug_f(Args...args) {
		return IO_Inner::print_args(cerr, args...)<<CHAR_BR;
	}
	#ifdef _DEBUG
	template<class...Args> constexpr ostream& debug(Args...args) {
		return IO_Inner::print_args(cerr, args...)<<CHAR_BR;
	}
	#else
	static inline ostream& debug(...) { return cerr; }
	#endif

	// pair
	template<class S,class T>constexpr ostream&operator<<(ostream&os,pair<S,T>p){
		return os<<'['<<p.first<<", "<<p.second<<']';
	};

	// tuple
	template<class...Args>constexpr ostream&operator<<(ostream&os,tuple<Args...>t){
		return apply([&os](auto&&t,auto&&...args)->ostream&{return IO_Inner::print_args(os, t, args...);}, t);
	};

	template<typename T, typename _=void> struct is_container : false_type {};
	template<typename... Ts> struct is_container_helper {};
	template<> struct is_container<string> : false_type {};
	template<typename T>
	struct is_container<T, conditional_t<
		false,
		is_container_helper<
			typename T::value_type,
			typename T::size_type,
			typename T::iterator,
			typename T::const_iterator,
			decltype(declval<T>().size()),
			decltype(declval<T>().begin()),
			decltype(declval<T>().end()),
			decltype(declval<T>().cbegin()),
			decltype(declval<T>().cend())
		>, void>> : public true_type {};
	template<typename T> using is_container_t = typename is_container<T>::type;

	// iterable
	template<
		typename T,
		typename enable_if<is_container<T>{}, nullptr_t>::type = nullptr,
		char Separator = is_container<typename T::value_type>{} ? '\n' : ' '
	>
	constexpr ostream&operator<<(ostream&os, T t){
		auto b=begin(t); os<<(*b++);
		for(const auto&&e=end(t);b!=e;++b) os<<Separator<<(*b);
		return os;
	}
}
using namespace IO;

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

HashMap<ll,ll> memo;
map<vi,ll> dpmemo1;

ll calc(ll n){
	if(n==0)return 0;
	if(memo.find(n)!=memo.end())return memo[n];
	string s=to_string(n);
	ll ans=0;
	int d=s.size();
	map<vi, ll> dp10, dp11, dp20, dp21;
	dp10[vi(10,0)]=1;
	rep(di,d){
		for(auto p: dp10){
			vi used=p.first;
			ll value=p.second;

			rep(k,1,10){//次に使う数
				used[k]++;
				if(k==s[di]-'0'){
					dp20[used]+=value;
				}else if(k<s[di]-'0'){
					dp21[used]+=value;
				}
				used[k]--;
			}
			if(sum(used)==used[0]){
				if(0==s[di]-'0'){
					dp20[used]+=value;
				}else if(0<s[di]-'0'){
					dp21[used]+=value;
				}
			} else {
				if(0==s[di]-'0'){
					ll val = 1;
					rep(d-di-1)val*=10;
					ans+=1+n%val;
				}else if(0<s[di]-'0'){
					ll val = value;
					rep(d-di-1)val*=10;
					ans+=val;
				}
			}
		}

		for(auto p: dp11){
			vi used=p.first;
			ll value=p.second;

			rep(k,1,10){//次に使う数
				used[k]++;
				dp21[used]+=value;
				used[k]--;
			}
			if(sum(used)==used[0]){
				dp21[used]+=value;
			} else {
				ll val = value;
				rep(d-di-1)val*=10;
				ans+=val;
			}
		}
		dp10.clear();
		dp11.clear();
		swap(dp10,dp20);
		swap(dp11,dp21);
		// print(dp);
	}
	for(auto&dp:{dp10,dp11})
	for(auto [used, value]: dp)if(value!=0){
		bool sat=false;
		if(used[0]>0){
			sat=true;
		}else{
			ll pr=1,sm=0;
			rep(i,10){
				rep(used[i]){
					pr*=i;
					sm+=i;
				}
			}
			if(sm!=0 and pr%sm==0)sat=true;
		}

		if(sat) ans+=value;
	}

	// i桁目まで見て、すでに下回っている/いない
	// if(n==1000000000000ll)ans++;
	debug(n,ans);

	return memo[n]=ans;
}

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

int main() {
	/**/
	int t; cin>>t;

	// t=10;
	rep(ti,t){
		cout<<"Case #"<<ti+1<<": ";
		ll a,b; cin>>a>>b;
		// a=Random(100000000000, 1000000000000);
		// b=Random(a,1000000000001);
		// debug(a,b);
		print(calc(b)-calc(a-1));

	}
}