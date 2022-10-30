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

struct Setup_io {
	Setup_io() {
		ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
		cout<<fixed<<setprecision(11);
	}
} setup_io;

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

/*
 * Macros
 */
#define all(a) a.begin(),a.end()
#define rall(a) a.rbegin(),a.rend()
#define __LOOPSWITCH(_1, _2, _3, __LOOPSWITCH, ...) __LOOPSWITCH
#define rep(...) __LOOPSWITCH(__VA_ARGS__, __RANGE, __REP, __LOOP) (__VA_ARGS__)
#define rrep(...) __LOOPSWITCH(__VA_ARGS__, __RRANGE, __RREP, __LOOP) (__VA_ARGS__)
#define __LOOP(q) __LOOP2(q, __LINE__)
#define __LOOP2(q,l) __LOOP3(q,l)
#define __LOOP3(q,l) __REP(_lp ## l,q)
#define __REP(i,n) __RANGE(i,0,n)
#define __RANGE(i,a,n) for(int i=((ll)a);i<((ll)n);++i)
#define __RREP(i,n) __RRANGE(i,0,n)
#define __RRANGE(i,a,n) for(int i=((ll)n-1);i>=((ll)a);--i)
#define repsq(i,n) for(ll i=0;i*i<=n;++i)
#define each(v,a) for(auto v:a)
#define eachref(v,a) for(auto&v:a)
#define fcout(a) cout<<setprecision(a)<<fixed

/*
 * Constants
 */
constexpr ll LINF=1ll<<60;
constexpr int INF=1<<30;
constexpr double EPS=(1e-14);
constexpr ll MOD=998244353ll;
constexpr long double PI=3.14159265358979323846;

/*
 * Output Assist
 */
template<class T>struct hasItr{
	template<class U>static constexpr true_type check(class U::iterator*);
	template<class U>static constexpr false_type check(...);
	static constexpr bool v=decltype(check<T>(nullptr))::value;
};
template<>struct hasItr<string>{static constexpr bool v=false;};

template<class T>void puta(T&t,false_type,ostream&os,[[maybe_unused]]char el){os<<t;}
template<class T>void puta(T&t,true_type,ostream&os,char el){
	constexpr bool h=hasItr<typename T::value_type>::v;
	bool F=true,I;
	for(auto&i:t){
		if(!F)os<<' ';
		puta(i,bool_constant<h>(),os,el);
		F=I=h;
	}
	if(!I)os<<el;
}
template<class T>void puta(const T&t, ostream&os=cout, char el='\n'){
	puta(t,bool_constant<hasItr<T>::v>(),os,el);
	if(!hasItr<T>::v)os<<el;
}
template<class H,class...T>void puta(const H&h,const T&...t){cout<<h<<' ';puta(t...);}
template<size_t i,class...T>void puta(tuple<T...>const&t, ostream&os){
	if constexpr(i==sizeof...(T)-1)puta(get<i>(t),os);
	else{os<<get<i>(t)<<' ';puta<i+1>(t,os);}
}
template<class...T>void puta(tuple<T...>const&t, ostream&os=cout){puta<0>(t,os);}
template<class S,class T>constexpr ostream&operator<<(ostream&os,pair<S,T>p){
	os<<'['<<p.first<<", ";
	if constexpr(hasItr<T>::v)puta(p.second,bool_constant<true>(),os,']');
	else os<<p.second<<']';
	return os;
};
template<class...T>constexpr ostream&operator<<(ostream&os,tuple<T...>t){puta(t,os); return os;}
void YN(bool b){puta(b?"YES":"NO");}
void Yn(bool b){puta(b?"Yes":"No");}

#ifdef _DEBUG
template<class T>void dump_f(const T&t){puta(t,cerr);}
template<class H,class...T>void dump_f(const H&h,const T&...t){cerr<<h<<' ';dump_f(t...);}
template<class...T>void dump_f(tuple<T...>const&t){puta(t,cerr);}
#define dump(...)cerr<<"  "<<string(#__VA_ARGS__)<<": ["<<to_string(__LINE__)<<":"<<__FUNCTION__<<"]\n    ",dump_f(__VA_ARGS__)
#else
#define dump(...)                                                              
#endif

/*
 * Input Assist
 */
template<class S,class T>auto&operator>>(istream&is,pair<S,T>&p){is>>p.first>>p.second;return is;}
template<class S>auto&operator>>(istream&is,vector<S>&t){for(S&a:t)is>>a;return is;}
template<typename...S>void geta_(S&...s){((cin>>s),...);}
#define geta(t,...) t __VA_ARGS__;geta_(__VA_ARGS__)
template<class T,class...Args>auto vec(T x,int arg,Args...args){if constexpr(sizeof...(args)==0)return vector(arg,x);else return vector(arg,vec(x,args...));}
#define getv(a,...) auto a=vec(__VA_ARGS__);cin>>a

/*
 * Utilities
 */
template<class T>constexpr bool chmax(T&a,T b){return a<b?a=b,1:0;}
template<class T>constexpr bool chmin(T&a,T b){return a>b?a=b,1:0;}
template<class S>S sum(vector<S>&a){return accumulate(all(a),S());}
template<class S>S max(vector<S>&a){return *max_element(all(a));}
template<class S>S min(vector<S>&a){return *min_element(all(a));}
template<class T>T gcd(vector<T> v){return accumulate(all(v),T(),gcd<T,T>);}
template<class T> pair<int,T> getMaxAndIndex(vector<T> a){
	int p=-1; T v=numeric_limits<T>::min();
	rep(i,a.size())if(chmax(v,a[i]))p=i;
	return {p,v};
}
template<class T> vector<pair<T,int>> addIndex(vector<T> a){
	vector<pair<T,int>> r;
	rep(i,a.size())r.emplace_back(a[i],i);
	return r;
}

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
	Timer(uint64_t _limit): start(getClocks()),limit(start+_limit*ClocksPerMsec) {}
	uint64_t get() const{return (getClocks()-start)/ClocksPerMsec;}
	operator bool()const{return getClocks()<limit;}
};
void wait(const int&msec){Timer tm(msec); while(tm);}


// ここにライブラリを貼る
const int N=20;
using ROW=array<int, N>;
const ROW defaultRow={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};

tuple<int,vi,vi> create(int n, int current, int nxt){
	array<HashMap<int, pair<ROW,ROW>>, 3> stage;
	stage[0][nxt]={defaultRow, defaultRow};
	
	array<vi, N+1> dp;
	fill(all(dp), vi(1<<n, -INF));
	dp[0][nxt]=0;

	int maxValue=0;
	rep(i,n){
		rep(s,1<<n){
			if(dp[i][s]>=maxValue-1 and chmax(dp[i+1][s], dp[i][s]))stage[(i+1)%3][s]=stage[i%3][s];
		}
		if(current&(1<<i)){
			//すでにcurrentのi番目が使用済なら、次のマスに進む
			continue;
		}
		auto stage0=stage[(i)%3];
		auto& stage1=stage[(i+1)%3];
		auto& stage2=stage[(i+2)%3];
		rep(s,1<<n)if(dp[i][s]>=maxValue-1){
			// すでにnxtの行の集合sが埋まっている状況でcurrentのiを埋める

			// 次の行がある
			if(i+1<n){
				// 隣りも空いてる
				if (!(current&(1<<(i+1)))) {
					/* ..i
						xx
						 x */
					if(!(s&(1<<(i)))){
						if(chmax(dp[i+2][s|(1<<(i))], dp[i][s]+1)){
							chmax(maxValue, dp[i][s]+1);
							stage2[s|(1<<(i))]=stage0[s];
							stage2[s|(1<<(i))].first[i]=dp[i][s];
							stage2[s|(1<<(i))].first[i+1]=dp[i][s];
							stage2[s|(1<<(i))].second[i]=dp[i][s];
						}
					}
					/* ..i
						xx
						x  */
					if(!(s&(1<<(i+1)))){
						if(chmax(dp[i+2][s|(1<<(i+1))], dp[i][s]+1)){
							chmax(maxValue, dp[i][s]+1);
							stage2[s|(1<<(i+1))]=stage0[s];
							stage2[s|(1<<(i+1))].first[i]=dp[i][s];
							stage2[s|(1<<(i+1))].first[i+1]=dp[i][s];
							stage2[s|(1<<(i+1))].second[i+1]=dp[i][s];
						}
					}
				}
				/* ..i
					 x
					xx */
				if(!(s&(1<<(i))) and !(s&(1<<(i+1)))){
					if(chmax(dp[i+1][s|(1<<(i))|(1<<(i+1))], dp[i][s]+1)){
						chmax(maxValue, dp[i][s]+1);
						stage1[s|(1<<(i))|(1<<(i+1))]=stage0[s];
						stage1[s|(1<<(i))|(1<<(i+1))].first[i]=dp[i][s];
						stage1[s|(1<<(i))|(1<<(i+1))].second[i]=dp[i][s];
						stage1[s|(1<<(i))|(1<<(i+1))].second[i+1]=dp[i][s];
					}
				}
			}
			/* ..i
				 x
				 xx */
			if(i>0 and !(s&(1<<(i))) and !(s&(1<<(i-1)))){
				if(chmax(dp[i+1][s|(1<<(i))|(1<<(i-1))], dp[i][s]+1)){
					chmax(maxValue, dp[i][s]+1);
					stage1[s|(1<<(i))|(1<<(i-1))]=stage0[s];
					stage1[s|(1<<(i))|(1<<(i-1))].first[i]=dp[i][s];
					stage1[s|(1<<(i))|(1<<(i-1))].second[i]=dp[i][s];
					stage1[s|(1<<(i))|(1<<(i-1))].second[i-1]=dp[i][s];
				}
			}
		}
		rep(s,1<<n)if(dp[i+1][s]>=0){
			// puta(bitset<20>(s).to_string(), dp[i+1][s]);
		}
	}

	vector<tl3> v;
	rep(s,1<<n)if(dp[n][s]>=0){
		v.emplace_back(dp[n][s], -__builtin_popcount(s), s);
		sort(all(v));
	}
	// puta(v);
	auto [r,_,c]=v.back();
	// auto[c,r]=getMaxAndIndex(dp[n]);
	// rep(s,1<<n){
	// 	puta(bitset<6>(s).to_string(), dp[n][s]);
	// }
	vi l1(all(stage[n%3][c].first));
	vi l2(all(stage[n%3][c].second));
	l1.resize(n);
	l2.resize(n);
	
	reverse(all(l1));
	reverse(all(l2));
	return {r, l1, l2};
}

vs pre(int n, vs f){
	return f;
	// vs r(n, string(n, '.'));
	// rep(i,n)rep(j,n)r[i][j]=f[i][n-j-1];
	// return r;
}

int main(){
	geta(ll, n);
	vs initial(n);
	cin>>initial;

	auto ans=pre(n, initial);
	vi f(n);
	rep(i,n){
		int b=0;
		rep(j,n){
			b<<=1;
			if(ans[i][j]=='#')b++;
		}
		f[i]=b;
	}

	const string alphabet="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

	Timer timer(1000000);
	int total=0;
	rep(i,n-1){
		// puta("START");
		// puta(bitset<10>(f[i]).to_string());
		// puta(bitset<10>(f[i+1]).to_string());
		auto [cnt,l1,l2]=create(n, f[i], f[i+1]);
		// puta(l1);
		// puta(l2);
		rep(j,n){
			if(l1[j]>=0)ans[i][j]=alphabet[total+l1[j]];
			if(l2[j]>=0){
				ans[i+1][j]=alphabet[total+l2[j]];
				f[i+1]|=(1<<(n-j-1));
			}
		}
		// puta("RESULT");
		// puta(bitset<10>(f[i]).to_string());
		// puta(bitset<10>(f[i+1]).to_string());
		total+=cnt;
	}
	ans=pre(n,ans);

	if(total==0){
		puta("No");
	}else{
		puta("Yes");
		rep(i,n)puta(ans[i]);
	}
	dump(timer.get(), total);
}
