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
constexpr ll MOD=998244353;
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
int mpow(int v, ll a) {
    ll x = v, n = a, res = 1;
    while ( n ) {
        if ( n & 1 )res = res*x%MOD;
        x = x*x%MOD;
        n >>= 1;
    }
    return res;
}

class mymint {
private:
    ll v;
public:
    static ll mod(ll a) { return ( a % MOD + MOD ) % MOD; }
    mymint(ll a = 0) { this->v = mod(a); };
    mymint(const mymint &a) { v = a.v; }
    mymint operator+(const mymint &a) { return mymint(v + a.v); }
    mymint operator+(const ll a) { return mymint(v + a % MOD); }
    mymint operator+(const signed a) { return mymint(v + a % MOD); }
    friend mymint operator+(const ll a, const mymint &b) { return mymint(a % MOD + b.v); }
    void operator+=(const mymint &a) { v = ( v + a.v ) % MOD; }
    void operator+=(const ll a) { v = mod(v + a % MOD); }
    void operator+=(const signed a) { v = mod(v + a % MOD); }
    friend void operator+=(ll &a, const mymint &b) { a = mod(a % MOD + b.v); }
    mymint operator-(const mymint &a) { return mymint(v - a.v); }
    mymint operator-(const ll a) { return mymint(v - a % MOD); }
    mymint operator-(const signed a) { return mymint(v - a % MOD); }
    friend mymint operator-(const ll a, const mymint &b) { return mymint(a % MOD - b.v); }
    void operator-=(const mymint &a) { v = mod(v - a.v); }
    void operator-=(const ll a) { v = mod(v - a % MOD); }
    void operator-=(const signed a) { v = mod(v - a % MOD); }
    friend void operator-=(ll &a, const mymint &b) { a = mod(a % MOD - b.v); }
    mymint operator*(const mymint &a) { return mymint(v * a.v); }
    mymint operator*(const ll a) { return mymint(v * ( a % MOD )); }
    mymint operator*(const signed a) { return mymint(v * ( a % MOD )); }
    friend mymint operator*(const ll a, const mymint &b) { return mymint(a % MOD * b.v); }
    void operator*=(const mymint &a) { v = ( v * a.v ) % MOD; }
    void operator*=(const ll a) { v = mod(v * ( a % MOD )); }
    void operator*=(const signed a) { v = mod(v * ( a % MOD )); }
    friend void operator*=(ll &a, const mymint &b) { a = mod(a % MOD * b.v); }
    mymint operator/(const mymint &a);
    mymint operator/(const ll a);
    mymint operator/(const signed a);
    friend mymint operator/(const ll a, const mymint &b);
    void operator/=(const mymint &a);
    void operator/=(const ll a);
    void operator/=(const signed a);
    friend void operator/=(ll &a, const mymint &b);
    mymint operator^(const mymint &a) { return mpow(v, a.v); };
    mymint operator^(const ll a) { return mpow(v, a); };
    mymint operator^(const signed a) { return mpow(v, a); };
    friend mymint operator^(const ll a, const mymint &b) { return mpow(a, b.v); };
    void operator^=(const mymint &a) { v = mpow(v, a.v); }
    void operator^=(const ll a) { v = mpow(v, a); }
    void operator^=(const signed a) { v = mpow(v, a); }
    mymint operator+() { return *this; }
    mymint operator++() { v++; return *this; }
    mymint operator++(signed d) { mymint res = *this; v++; return res;}
    mymint operator-() { return operator*(-1); }
    mymint operator--() { v--; return *this; }
    mymint operator--(signed d) { mymint res = *this; v--; return res;}
    bool operator==(mymint &a) { return v == a.v; }
    bool operator==(signed a) { return v == a; }
    friend bool operator==(signed a, mymint &b) { return a == b.v; }
    bool operator!=(mymint &a) { return v != a.v; }
    bool operator!=(signed a) { return v != a; }
    friend bool operator!=(signed a, mymint &b) { return a != b.v; }
    operator int() { return v; }
};
const int setModMax = 510000;
mymint fac[setModMax], finv[setModMax], inv[setModMax];
void setMod() {
    fac[0] = fac[1] = finv[0] = finv[1] = inv[1] = 1;
    for ( int i = 2; i < setModMax; i++ ) {
        fac[i] = fac[i - 1] * i % MOD;
        inv[i] = MOD - inv[MOD % i] * ( MOD / i ) % MOD;
        finv[i] = finv[i - 1] * inv[i] % MOD;
    }
}
mymint minv(ll a) {
    if ( fac[0] == 0 )setMod();
    if ( a < setModMax ) return inv[a];
    a %= MOD;
    ll b = MOD, x = 1, y = 0;
    while ( b ) {
        ll t = a / b;
        a -= t*b; swap(a, b);
        x -= t*y; swap(x, y);
    }
    return ( x % MOD + MOD ) % MOD;
}

mymint mymint::operator/(const mymint &a) { return mymint(v * minv(a.v)); }
mymint mymint::operator/(const ll a) { return mymint(v * minv(a)); }
mymint mymint::operator/(const signed a) { return mymint(v * minv(a)); }
mymint operator/(const ll a, const mymint &b) { return mymint(a % MOD * minv(b.v)); }
void mymint::operator/=(const mymint &a) { v = ( v * minv(a.v) ) % MOD; }
void mymint::operator/=(const ll a) { v = mod(v * minv(a)); }
void mymint::operator/=(const signed a) { v = mod(v * minv(a)); }
void operator/=(ll &a, const mymint &b) { a = mymint::mod(a % MOD * minv(b.v)); }
auto&operator>>(istream&is,mymint&t){ll a; cin>>a; t=a; return is;};
auto&operator<<(ostream&os,mymint&t){cout<<((int)t); return os;};
mymint operator"" _m(unsigned long long a){return mymint(a);}
using vm=vector<mymint>;
using vvm=vector<vm>;
mymint nCr(ll n,ll r){
    if ( fac[0] == 0 )setMod();
    return fac[n]*finv[r]*finv[n-r];
}

void Main(){
    geta(ll, n);
    getv(a,0,n);
    sort(rall(a));
    mymint s=0,d=1;
    rep(i,n){
        s+=a[i]*d;
        d*=2;
    }

    mymint ans=0;
    rep(i,n){
        s-=a[i];
        s/=2;
        auto v=(s+a[i])*a[i];
        ans+=v;
        // puta(i,(ll)v);
    }


    puta((ll)ans);
}
