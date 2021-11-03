/*
 * Unsecured Optimization
 */
// #pragma GCC target "avx" /* SIMD(ベクトル化) */
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native") /* 浮動小数点数のSIMD */
// #pragma GCC optimize "O3" /* 最適化 */
// #pragma GCC optimize "fast-math"
// #pragma GCC optimize "unroll-loops" /* ループの展開 */
//#define _GLIBCXX_DEBUG 1

/* 
 * Include Headers
 */
#include<bits/stdc++.h>

using namespace std;

void Main();
int main(){cin.tie(nullptr);ios::sync_with_stdio(false);Main();return 0;}

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
using pll=pair<ll,ll>;
using vp=vector<pll>;
using tl2=tuple<ll,ll>;
using tl3=tuple<ll,ll,ll>;
using vs=vector<string>;


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
#define __RANGE(i,a,n) for(ll i=((ll)a);i<((ll)n);++i)
#define __RREP(i,n) __RRANGE(i,0,n)
#define __RRANGE(i,a,n) for(ll i=((ll)n-1);i>=((ll)a);--i)
#define repsq(i,n) for(ll i=0;i*i<=n;++i)
#define each(v,a) for(auto v:a)
#define eachref(v,a) for(auto&v:a)
#define fcout(a) cout<<setprecision(a)<<fixed

/*
 * Constants
 */
constexpr ll LINF=1ll<<60;
constexpr int INF=1<<30;
constexpr double EPS=(1e-9);
constexpr ll MOD=1000000007ll;
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

// ここにライブラリを貼る

void Main(){
  geta(ll,n,k);
  ll ans=k%5; k=k/5*5;
  vector<deque<ll>> w(5);
  rep(i,n){
    geta(ll,t);
    w[(5-t%5)%5].push_back((t+4)/5*5);
  }
  rep(i,5){
    sort(all(w[i]));
  }

// 価値12を達成する重さ最小の選択を求める
  const vvi sp={
    {12,0,0,0},
    {10,1,0,0},
    {9,0,1,0},
    {8,2,0,0},
    {8,0,0,1},
    {7,1,1,0},
    {6,3,0,0},
    {6,0,2,0},
    {6,1,0,1},
    {5,2,1,0},
    {5,0,1,1},
    {4,4,0,0},
    {4,2,0,1},
    {4,0,0,2},
    {4,1,2,0},
    {3,3,1,0},
    {3,1,1,1},
    {3,0,3,0},
    {2,5,0,0},
    {2,3,0,1},
    {2,1,0,2},
    {2,2,2,0},
    {2,0,2,1},
    {1,4,1,0},
    {1,2,1,1},
    {1,0,1,2},
    {1,1,3,0},
    {0,6,0,0},
    {0,4,0,1},
    {0,2,0,2},
    {0,0,0,3},
    {0,3,2,0},
    {0,1,2,1},
    {0,0,4,0},
  };

  while(true){
    vvl wsum(4,vl(1,0));
    rep(i,4){
        rep(j,min(12/(i+1), (ll)w[i+1].size())){
          wsum[i].push_back(wsum[i][j]+w[i+1][j]);
        }
        rep(j, 12)wsum[i].push_back(LINF);
    }

    ll minWeight=LINF, minIndex=0;
    rep(i,sp.size()){
      bool ok=true;
      rep(j,4)if(w[j+1].size()<sp[i][j])ok=false;
      if(!ok)continue;
      ll v=0;
      rep(j,4)v+=wsum[j][sp[i][j]];
      if(chmin(minWeight, v))minIndex=i;
    }
    if(minWeight>k)break;
    k-=minWeight;
    ans+=12;
    rep(i,4)rep(sp[minIndex][i])w[i+1].pop_front();
  }
  
  // dp[i][j]=i番目まで見て、価値jを達成するような最小の重さw
  rep(i,5){
    w[i].push_front(0);
    partial_sum(all(w[i]),w[i].begin());
  }
  
  
  // ^OK
  
  const int MVAL=11;
  vl dp(MVAL+1,LINF);
  dp[0]=0;

  rep(W,1,5){
    auto ndp=dp;
    rep(i,w[W].size()){
      rep(j,12)if(j+W*i<=MVAL){
        chmin(ndp[j+W*i],dp[j]+w[W][i]); 
      }
    }
    dp=ndp;
  }
  
  // ^NG

  
  ll val=0;
  rep(i,MVAL+1)if(dp[i]!=LINF){
	if(dp[i]>k) break;
    val=i;
  }
  puta(ans+val);
}
