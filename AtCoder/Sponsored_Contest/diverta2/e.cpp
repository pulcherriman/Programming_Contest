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
#define rrep(i,n) for(ll i=(n)-1;i>=0;i--)
#define range(i,a,n) for(ll i=(a);i<(n);i++)
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

mint solve(ll n, ll h, ll d){
	mint ans=0;
	




	return ans;
}

int main(){
	cin.tie(0);
	ios::sync_with_stdio(false);
	ll n,h.d;
	cin>>n>>h>>d;
	puta(solve(n,h,d));
	return 0;
}