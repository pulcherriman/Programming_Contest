#include <bits/stdc++.h>
#if defined(ONLINE_JUDGE) || defined(_DEBUG)
#include <atcoder/all>
using namespace atcoder;
#endif

using namespace std;
using ll=long long;
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

#define all(a) a.begin(),a.end()
#define rall(a) a.rbegin(),a.rend()
#define rep(i,n) range(i,0,n)
#define rrep(i,n) rrange(i,0,n)
#define range(i,a,n) for(ll i=((ll)a);i<((ll)n);++i)
#define rrange(i,a,n) for(ll i=((ll)n-1);i>=((ll)a);--i)
#define repsq(i,n) for(ll i=0;i*i<=n;++i)
#define LINF ((ll)1ll<<60)
#define INF ((int)1<<30)
#define EPS (1e-9)
#define MOD (1000000007ll)
#define fcout(a) cout<<setprecision(a)<<fixed
#define PI (3.1415926535897932384)

int dx[]={1,0,-1,0,1,-1,-1,1},dy[]={0,1,0,-1,1,1,-1,-1};
template<class T>bool chmax(T&a,T b){if(a<b){a=b; return true;}return false;}
template<class T>bool chmin(T&a,T b){if(a>b){a=b; return true;}return false;}
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
template<class T>void dump(const T&t){puta(t,cerr);}
template<class H,class...T>void dump(const H&h,const T&...t){cerr<<h<<' ';dump(t...);}
template<class...T>void dump(tuple<T...>const&t){puta(t,cerr);}
template<class S,class T>constexpr ostream&operator<<(ostream&os,pair<S,T>p){
    os<<'['<<p.first<<", ";
    if constexpr(hasItr<T>::v)puta(p.second,bool_constant<true>(),os,']');
    else os<<p.second<<']';
    return os;
};
template<class...T>constexpr ostream&operator<<(ostream&os,tuple<T...>t){
    puta(t,os); return os;
}

void YN(bool b){puta(b?"YES":"NO");}
void Yn(bool b){puta(b?"Yes":"No");}

#ifndef _DEBUG
#define dump(...) 
#endif

//input
template<class S>auto&operator>>(istream&is,vector<S>&t){for(S&a:t)cin>>a;return is;}
// #define geta(t,n,...) t n;cin>>n;geta(t,__VA_ARGS__)
// #define vec(t,a,h,...) vector<t>a(h);rep(i,n)a[i]=t(__VA_ARGS__);rep(i,n)cin>>a[i]
template<typename...S>void geta_(S&...s){((cin>>s),...);}

#define geta(t,...) t __VA_ARGS__;geta_(__VA_ARGS__)

int mpow(int v, ll a) {
    ll x = v, n = a, res = 1;
    while ( n ) {
        if ( n & 1 )res = res*x%MOD;
        x = x*x%MOD;
        n >>= 1;
    }
    return res;
}

class mint {
private:
    ll v;
public:
    static ll mod(ll a) { return ( a % MOD + MOD ) % MOD; }
    mint(ll a = 0) { this->v = mod(a); };
    mint(const mint &a) { v = a.v; }
    mint operator+(const mint &a) { return mint(v + a.v); }
    mint operator+(const ll a) { return mint(v + a % MOD); }
    mint operator+(const signed a) { return mint(v + a % MOD); }
    friend mint operator+(const ll a, const mint &b) { return mint(a % MOD + b.v); }
    void operator+=(const mint &a) { v = ( v + a.v ) % MOD; }
    void operator+=(const ll a) { v = mod(v + a % MOD); }
    void operator+=(const signed a) { v = mod(v + a % MOD); }
    friend void operator+=(ll &a, const mint &b) { a = mod(a % MOD + b.v); }
    mint operator-(const mint &a) { return mint(v - a.v); }
    mint operator-(const ll a) { return mint(v - a % MOD); }
    mint operator-(const signed a) { return mint(v - a % MOD); }
    friend mint operator-(const ll a, const mint &b) { return mint(a % MOD - b.v); }
    void operator-=(const mint &a) { v = mod(v - a.v); }
    void operator-=(const ll a) { v = mod(v - a % MOD); }
    void operator-=(const signed a) { v = mod(v - a % MOD); }
    friend void operator-=(ll &a, const mint &b) { a = mod(a % MOD - b.v); }
    mint operator*(const mint &a) { return mint(v * a.v); }
    mint operator*(const ll a) { return mint(v * ( a % MOD )); }
    mint operator*(const signed a) { return mint(v * ( a % MOD )); }
    friend mint operator*(const ll a, const mint &b) { return mint(a % MOD * b.v); }
    void operator*=(const mint &a) { v = ( v * a.v ) % MOD; }
    void operator*=(const ll a) { v = mod(v * ( a % MOD )); }
    void operator*=(const signed a) { v = mod(v * ( a % MOD )); }
    friend void operator*=(ll &a, const mint &b) { a = mod(a % MOD * b.v); }
    mint operator/(const mint &a);
    mint operator/(const ll a);
    mint operator/(const signed a);
    friend mint operator/(const ll a, const mint &b);
    void operator/=(const mint &a);
    void operator/=(const ll a);
    void operator/=(const signed a);
    friend void operator/=(ll &a, const mint &b);
    mint operator^(const mint &a) { return mpow(v, a.v); };
    mint operator^(const ll a) { return mpow(v, a); };
    mint operator^(const signed a) { return mpow(v, a); };
    friend mint operator^(const ll a, const mint &b) { return mpow(a, b.v); };
    void operator^=(const mint &a) { v = mpow(v, a.v); }
    void operator^=(const ll a) { v = mpow(v, a); }
    void operator^=(const signed a) { v = mpow(v, a); }
    mint operator+() { return *this; }
    mint operator++() { v++; return *this; }
    mint operator++(signed d) { mint res = *this; v++; return res;}
    mint operator-() { return operator*(-1); }
    mint operator--() { v--; return *this; }
    mint operator--(signed d) { mint res = *this; v--; return res;}
    bool operator==(mint &a) { return v == a.v; }
    bool operator==(signed a) { return v == a; }
    friend bool operator==(signed a, mint &b) { return a == b.v; }
    bool operator!=(mint &a) { return v != a.v; }
    bool operator!=(signed a) { return v != a; }
    friend bool operator!=(signed a, mint &b) { return a != b.v; }
    operator int() { return v; }
};
const int setModMax = 510000;
mint fac[setModMax], finv[setModMax], inv[setModMax];
void setMod() {
    fac[0] = fac[1] = finv[0] = finv[1] = inv[1] = 1;
    for ( int i = 2; i < setModMax; i++ ) {
        fac[i] = fac[i - 1] * i % MOD;
        inv[i] = MOD - inv[MOD % i] * ( MOD / i ) % MOD;
        finv[i] = finv[i - 1] * inv[i] % MOD;
    }
}
mint minv(ll a) {
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

mint mint::operator/(const mint &a) { return mint(v * minv(a.v)); }
mint mint::operator/(const ll a) { return mint(v * minv(a)); }
mint mint::operator/(const signed a) { return mint(v * minv(a)); }
mint operator/(const ll a, const mint &b) { return mint(a % MOD * minv(b.v)); }
void mint::operator/=(const mint &a) { v = ( v * minv(a.v) ) % MOD; }
void mint::operator/=(const ll a) { v = mod(v * minv(a)); }
void mint::operator/=(const signed a) { v = mod(v * minv(a)); }
void operator/=(ll &a, const mint &b) { a = mint::mod(a % MOD * minv(b.v)); }
auto&operator>>(istream&is,mint&t){ll a; cin>>a; t=a; return is;};
auto&operator<<(ostream&os,mint&t){cout<<((int)t); return os;};
mint operator"" _m(unsigned long long a){return mint(a);}
using vm=vector<mint>;
using vvm=vector<vm>;
mint nCr(ll n,ll r){
    if ( fac[0] == 0 )setMod();
    return fac[n]*finv[r]*finv[n-r];
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    geta(string,s);
    geta(ll, k);
    ll n=s.size();

    vvm dp(n+1,vm(2,0));
    vl used(16,0);

    mint ans=0;
    rep(i,n){
        ll d=s[i]-'0';
        if(!(0<=d and d<=9))d=s[i]-'A'+10;
        if(i==0){
            ans+=(d-1)*nCr(15,k-1)*fac[n-1];
            used[d]=1;
            puta((ll)ans);
            continue;
        }

        ll lcnt=0;
        rep(j,d)lcnt+=used[j];
        ans += fac[n-i-1] * nCr(16-lcnt,k-lcnt) * lcnt;
        if(lcnt<k){
            ans += fac[n-i-1] * nCr(16-lcnt-1,min(k-lcnt-1,d)) * (k-lcnt-1);
        }
        used[d]=1;
        puta((ll)ans);
    }
    if(n-1>=k){
        ans+=15*fac[n-2]*nCr(15,k-1);
    }
    puta((ll)ans);
    return 0;
}