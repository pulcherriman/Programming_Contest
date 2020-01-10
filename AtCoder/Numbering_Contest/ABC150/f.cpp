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