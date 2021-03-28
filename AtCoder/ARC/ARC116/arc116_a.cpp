// #pragma GCC target("avx")
// #pragma GCC optimize("O3,inline,omit-frame-pointer,no-asynchronous-unwind-tables,fast-math")
// #pragma GCC optimize("unroll-loops")

#define _USE_MATH_DEFINES
#ifndef _DEBUG
#define NDEBUG
#endif
#if defined(ONLINE_JUDGE) || defined(_DEBUG)
#include <atcoder/all>
using namespace atcoder;
#endif
#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using ll=long long;
using ld=long double;
using ull=unsigned long long;
using vb=vector<bool>;
using vvb=vector<vb>;
using vd=vector<double>;
using vvd=vector<vd>;
using vi=vector<int>;
using vvi=vector<vi>;
using vl=vector<ll>;
using vvl=vector<vl>;
using pll=pair<ll,ll>;
using tll=tuple<ll,ll>;
using tlll=tuple<ll,ll,ll>;
using vs=vector<string>;
template<class K> using IndexedSet=__gnu_pbds::tree<K,__gnu_pbds::null_type,less<K>,__gnu_pbds::rb_tree_tag,__gnu_pbds::tree_order_statistics_node_update>;
template<class K> using HashSet=__gnu_pbds::gp_hash_table<K,__gnu_pbds::null_type>;
template<class K,class V> using IndexedMap=__gnu_pbds::tree<K,V,less<K>,__gnu_pbds::rb_tree_tag,__gnu_pbds::tree_order_statistics_node_update>;
template<class K,class V> using HashMap=__gnu_pbds::gp_hash_table<K,V>;

#define all(a) a.begin(),a.end()
#define rall(a) a.rbegin(),a.rend()
#define loop(q) __loop(q, __LINE__)
#define __loop(q,l) __loop2(q,l)
#define __loop2(q,l) rep(_lp ## l,q)
#define rep(i,n) range(i,0,n)
#define rrep(i,n) rrange(i,0,n)
#define range(i,a,n) for(ll i=((ll)a);i<((ll)n);++i)
#define rrange(i,a,n) for(ll i=((ll)n-1);i>=((ll)a);--i)
#define repsq(i,n) for(ll i=0;i*i<=n;++i)
#define each(v,a) for(auto v:a)
#define eachref(v,a) for(auto&v:a)
#define fcout(a) cout<<setprecision(a)<<fixed
constexpr ll LINF=1ll<<60;
constexpr int INF=1<<30;
constexpr double EPS=(1e-9);
constexpr ll MOD=1000000007ll;
constexpr double PI=3.1415926535897932384;

void Main();
int main(){cin.tie(nullptr);ios::sync_with_stdio(false);Main();return 0;}
template<class T>constexpr bool chmax(T&a,T b){return a<b?a=b,1:0;}
template<class T>constexpr bool chmin(T&a,T b){return a>b?a=b,1:0;}
template<class S>S sum(vector<S>&a){return accumulate(all(a),S());}
template<class S>S max(vector<S>&a){return *max_element(all(a));}
template<class S>S min(vector<S>&a){return *min_element(all(a));}

//output
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

//input
template<class S>auto&operator>>(istream&is,vector<S>&t){for(S&a:t)cin>>a;return is;}
template<typename...S>void geta_(S&...s){((cin>>s),...);}
#define geta(t,...) t __VA_ARGS__;geta_(__VA_ARGS__)
template<class T,class...Args>auto vec(T x,int arg,Args...args){if constexpr(sizeof...(args)==0)return vector(arg,x);else return vector(arg,vec(x,args...));}
#define getv(a,...) auto a=vec(__VA_ARGS__);cin>>a

// ライブラリ貼るスペース
struct _Prime{
    bool IsPrime(ll n){
        if(n<2)return false;
        if(~n&1)return n==2;
        if(n<=INT_MAX)return IsPrime<int,ll>(n);
        return IsPrime<ll,__int128_t>(n);
    }
    map<ll,int> Factorize(ll n){
        map<ll,int> r;
        if(n!=1){
            if(ll x=pollard_single(n);x==n)r[x]=1;
            else{
                r=Factorize(x);
                for(const auto&v:Factorize(n/x))r[v.first]+=v.second;
            }
        }
        return r;
    }
    vl Divisor(ll n){
        vl r(1,1);
        for(const auto&[v,c]:Factorize(n))for(int i=0,l=r.size();i<l;++i)rep(j,c)r.push_back(r[i]*pmod(v,j+1,LLONG_MAX));
        return r;
    }

    private:
    template<class T>static constexpr int arr[]={2,7,61};
    template<class T,class U>
    static T pmod(T x,U n,T p) {
        T r=1%p;
        while(x%=p,n){if(n&1)r=r*x%p;x*=x;n>>=1;}
        return r;
    }
    template<class T,class U>static bool IsPrime(T n){
        for(const int&a:arr<T>){
            bool c=true;
            ll m=n-1;
            while(~m&1)c&=pmod<U>(a,m>>=1,n)!=n-1;
            c&=pmod<U>(a,m?:1,n)!=1;
            if(c)return n<=a;
        }
        return true;
    }

    ll fast_gcd(ll _a, ll _b) {
        ll a=abs(_a),b=abs(_b);
        if(a==0||b==0)return a+b;
        int n=__builtin_ctzll(a),m=__builtin_ctzll(b);
        a>>=n;b>>=m;
        while(a!=b){
            int x=__builtin_ctzll(a-b);
            ll c=a>b?a:b;
            a=(c-=b=a>b?b:a)>>x;
        }
        return a<<min(n,m);
    }
    ll pollard_single(ll n){
        const static auto f=[&n](ll x){return(__int128_t(x)*x+1)%n;};
        if(~n&1)return 2;
        if(IsPrime(n))return n;
        ll st=0;
        while(true){
            ll x=++st,y=f(x);
            while(true){
                ll p=fast_gcd(y-x+n,n);
                if(p==0||p==n)break;
                if(p!=1)return p;
                x=f(x);
                y=f(f(y));
            }
        }
    }
};
template<>constexpr int _Prime::arr<ll>[]={2,325,9375,28178,450775,9780504,1795265022};
_Prime Prime;

void Main(){
    geta(ll, t);
    loop(t){
        geta(ll,n);
        if(n%2==1)puta("Odd");
        else{
            if(n%4!=0)puta("Same");
            else puta("Even");
        }
    }
}
