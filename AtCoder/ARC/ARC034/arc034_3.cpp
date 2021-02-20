#include <bits/stdc++.h>
using namespace std;
using ll=long long;
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
#define rrep(i,n) for(ll i=((ll)n)-1;i>=0;i--)
#define range(i,a,n) for(ll i=((ll)a);i<((ll)n);i++)
#define LINF ((ll)1ll<<60)
#define INF ((int)1<<30)
#define EPS (1e-9)
#define MOD (1000000007ll)
#define fcout(a) cout<<setprecision(a)<<fixed
#define fs first
#define sc second
#define PI (3.1415926535897932384)

int dx[]={1,0,-1,0,1,-1,-1,1},dy[]={0,1,0,-1,1,1,-1,-1};
template<class T>bool chmax(T&a,T b){if(a<b){a=b; return true;}return false;}
template<class T>bool chmin(T&a,T b){if(a>b){a=b; return true;}return false;}
template<class S>S sum(vector<S>&a){return accumulate(all(a),S());}
template<class S>S max(vector<S>&a){return *max_element(all(a));}
template<class S>S min(vector<S>&a){return *min_element(all(a));}
ll max(int a,ll b){return max((ll)a,b);} ll max(ll a,int b){return max(a,(ll)b);}
int sgn(const double&r){return (r>EPS)-(r<-EPS);} // a>0  : sgn(a)>0
int sgn(const double&a,const double&b){return sgn(a-b);} // b<=c : sgn(b,c)<=0

template<class T>void puta(T&&t){cout<<t<<"\n";}
template<class H,class...T>void puta(H&&h,T&&...t){cout<<h<<' ';puta(t...);}
template<class S,class T>void tf(bool b,S t,T f){if(b)puta(t);else puta(f);}
void YN(bool b){tf(b,"YES","NO");}
void Yn(bool b){tf(b,"Yes","No");}
void yn(bool b){tf(b,"yes","no");}
template<class S,class T>ostream&operator<<(ostream&os,pair<S,T>p){os<<"["<<p.first<<", "<<p.second<<"]";return os;};
template<class S>auto&operator<<(ostream&os,vector<S>t){bool a=1;for(auto s:t){os<<(a?"":" ")<<s;a=0;}return os;}
template<class S>auto&operator>>(istream&is,vector<S>&t){for(S&a:t)cin>>a;return is;}

/*他のライブラリを入れる場所*/
class _Prime{
public:
ll target,c,block=2*3*5*7*11*13*17*2;
vb firstb;
vector<short> al;
vi pr,li;
vl primes,pr_default;
void calc(){
    firstb.assign(block,false);
    al.assign(block,0);
    primes.clear();
    li.clear();
    c=0;
    firstcalc();
    for(ll i=block;i<target;i+=block)calc(i);
}
void firstcalc(){
    for(int&p:vi{2,3,5,7,11,13,17}){
        if(p>target)break;
        add(p);
        if((ll)p*p<target){
            pr.push_back(p);
            for(ll j=p*2;j<block;j+=p)firstb[j]=true;
        }
    }
    c++;
    li.push_back(1);
    range(i,19,block){
        if(firstb[i])continue;
        li.push_back(i);
        if(al[i]==c)continue;
        if(i>target)break;
        add(i);
        if((ll)i*i<=target){
            pr.push_back(i);
            for(ll j=i*2;j<block;j+=i)al[j]=c;
        }
    }
}

void calc(ll b){
    c++;
    ll mv=b+block;
    for(int&p:pr){
        if((ll)p*p>mv)break;
        ll f=b%p;
        if(f)f=p-f;
        if((f&1)==0)f+=p;
        for(ll j=f;j<block;j+=p*2)al[j]=c;
    }
    for(int&i:li){
        if(al[i]==c)continue;
        if(b+i>target)break;
        add(b+i);
    }
}
void seg(ll l, ll r){
    chmax(l,2ll);
    firstb.assign(r-l,true);
    primes.clear();
    for(ll i=0,j;pr_default[i]*pr_default[i]<r;++i){
        if(pr_default[i]>=l)j=pr_default[i]*pr_default[i];
        else if(l%pr_default[i]==0)j=l;
        else j=l-(l%pr_default[i])+pr_default[i];
        for(;j<r;j+=pr_default[i])firstb[j-l]=false;
    }
    range(i,l,r)if(firstb[i-l])add(i);
}


void add(ll a){primes.push_back(a);}

public:
_Prime(){target=block;calc();pr_default=primes;}
vl sequence(ll n=100){
    assert(n<=100'000'000);
    target=n;
    if(n<=block)primes.assign(pr_default.begin(),find_if_not(all(pr_default),[&](ll x){return x<=n;}));
    else calc();return primes;
}
vl segment(ll l=1000, ll r=1100){
    assert(r<=block*block); //1'0424'8184'0400ll ~= 10^12
    assert(r-l<=100'000'000);
    seg(l,r);return primes;
}
bool isPrime(ll n){
    assert(n<=block*block); //1'0424'8184'0400ll ~= 10^12
    for(ll&p:pr_default){if(n%p==0)return false;if(p*p>n)break;}
    return true;
}
map<ll,ll> factor(ll n){
    map<ll,ll> ret;
    if(n<=block)for(ll&p:pr_default)while(n%p==0){ret[p]++;n/=p;}
    else for(ll p=2;p*p<=n;p++)while(n%p==0){ret[p]++;n/=p;}
    if(n!=1)ret[n]++;
    return ret;
}
};
_Prime Prime;

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
    ll a,b;
    cin>>a>>b;
    map<ll,ll> mp;
    range(i,b+1,a+1){
        for(auto&p:Prime.factor(i))mp[p.fs]+=p.sc;
    }
    mint ans=1;
    for(auto&p:mp){
        ans*=(p.sc+1);
        // puta(p);
    }
    puta(ans);
    return 0;
}