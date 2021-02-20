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
using vs=vector<string>;
#define all(a) a.begin(),a.end()
#define rall(a) a.rbegin(),a.rend()
#define rep(i,n) range(i,0,n)
#define range(i,a,n) for(ll i=(a);i<(n);i++)
#define LINF ((ll)1ll<<60)
#define INF ((int)1<<30)
#define EPS (1e-9)
#define MOD (1000000007ll)
#define fcout(a) cout<<setprecision(a)<<fixed
#define fs first
#define sc second
#define PI 3.1415926535897932384

int dx[]={1,0,-1,0,1,-1,-1,1},dy[]={0,1,0,-1,1,1,-1,-1};
template<class S,class T>ostream&operator<<(ostream&os,pair<S,T>p){os<<"["<<p.first<<", "<<p.second<<"]";return os;};
template<class S>auto&operator<<(ostream&os,vector<S>t){bool a=1; for(auto s:t){os<<(a?"":" ")<<s;a=0;} return os;}
template<class S>void tf(bool b,S t,S f){cout<<(b?t:f)<<endl;}
void OUT(bool b){tf(b,"YES","NO");}
void Out(bool b){tf(b,"Yes","No");}
void out(bool b){tf(b,"yes","no");}
template<class T>void puta(T&&t){cout<<t<<endl;}
template<class H,class...T>void puta(H&&h,T&&...t){cout<<h<<' ';puta(t...);}

int popcnt(int x){return __builtin_popcount(x);}
int popcnt(ll x){return __builtin_popcountll(x);}
int bsr(int x){return 31 - __builtin_clz(x);}
int bsr(ll x){return 63 - __builtin_clzll(x);}
int bsf(int x){return __builtin_ctz(x);}
int bsf(ll x){return __builtin_ctzll(x);}
template<class T>bool chmax(T&a,T b){if(a<b){a=b; return true;}return false;}
template<class T>bool chmin(T&a,T b){if(a>b){a=b; return true;}return false;}

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

class Fermat{
  private:
	int z;
	vector<ll> fact_mod, fact_invmod;
	ll modpow(ll a, ll n){
		if(n==1)return a;
		ll half=modpow(a,n/2);
		return half*half%MOD*(n%2?a:1)%MOD;
	}
  public:
	Fermat(int Z):z(Z){
		fact_mod=vector<ll>(z+1,1);
		fact_invmod.resize(z+1);
		range(i,1,z+1) fact_mod[i]=fact_mod[i-1]*i%MOD;
		fact_invmod[z]=modpow(fact_mod[z],MOD-2);
		for(int i=z-1;i>=0;i--) fact_invmod[i]=fact_invmod[i+1]*(i+1)%MOD;
	}
	ll comb(int n,int r){return fact_mod[n] * /*fact_invmod[r]%MOD **/ fact_invmod[n-r]%MOD;}
};

int main(){
	cin.tie(0);
	ios::sync_with_stdio(false);
	int h,w;
	cin>>h>>w;
	vl a(h+1,LINF),b(w+1,LINF);
	rep(i,h)cin>>a[i];
	rep(i,w)cin>>b[i];

	sort(all(a));
	sort(all(b));
	rep(i,h-1)if(a[i]==a[i+1]){cout<<0<<endl;return 0;}
	rep(i,w-1)if(b[i]==b[i+1]){cout<<0<<endl;return 0;}
	int x=0,y=0,d=0;
	mint ans=1;
	Fermat fe(1000001);
	while(1){
		if(a[x]<b[y]){
			//(a[x]-d-1)P(w-y-1)*(w-y)
			if(a[x]-d-1<w-y-1){cout<<0<<endl;return 0;}
			mint p=fe.comb(a[x]-d-1,w-y-1);
			ans*=p*(w-y);
			x++;
			d+=w-y;
		}else if(a[x]>b[y]){
			//(b[y]-d-1)P(h-x-1)*(h-x)
			if(b[y]-d-1<h-x-1){cout<<0<<endl;return 0;}
			mint p=fe.comb(b[y]-d-1,h-x-1);
			ans*=p*(h-x);
			y++;
			d+=h-x;
		}else{
			if(a[x]==LINF)break;
			if(a[x]-d-1<w-y+h-x-2){cout<<0<<endl;return 0;}
			//(b[y]-d-1)P(w-y+h-x-2)
			mint p=fe.comb(b[y]-d-1,w-y+h-x-2);
			//cout<<ans<<endl;
			ans*=p;
			d+=w-y+h-x-1;
			x++; y++;
		}
	}
	cout<<ans<<endl;
	return 0;
}