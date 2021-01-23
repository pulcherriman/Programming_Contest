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
void OUT(bool b){cout<<(b?"YES":"NO")<<endl;}
void Out(bool b){cout<<(b?"Yes":"No")<<endl;}
void out(bool b){cout<<(b?"yes":"no")<<endl;}
int popcnt(int x){return __builtin_popcount(x);}
int popcnt(ll x){return __builtin_popcountll(x);}
int bsr(int x){return 31 - __builtin_clz(x);}
int bsr(ll x){return 63 - __builtin_clzll(x);}
int bsf(int x){return __builtin_ctz(x);}
int bsf(ll x){return __builtin_ctzll(x);}

/*他のライブラリを入れる場所*/
template<ll _MOD=MOD>class modint {
public:
	modint() {
		this->number = 0;
	}
	modint(const ll src) {
		this->number = opposit(src);
	}
	modint(const modint<_MOD> &src) {
		this->number = src.number;
	}
 
	modint<_MOD>& operator += (const modint<_MOD>& obj) {
		this->number = san2(this->number + obj.number);
		return *this;
	}
	modint<_MOD>& operator -= (const modint<_MOD>& obj) {
		this->number = san2(this->number - obj.number + _MOD);
		return *this;
	}
	modint<_MOD>& operator *= (const modint<_MOD>& obj) {
		this->number = (this->number * obj.number) % _MOD;
		return *this;
	}
	modint<_MOD>& operator /= (const modint<_MOD>& obj) {
		this->number = (this->number * inverse(obj.number)) % _MOD;
		return *this;
	}
	modint<_MOD>& operator += (const ll n) {
		this->number = san2(this->number + opposit(n));
		return *this;
	}
	modint<_MOD>& operator -= (const ll n) {
		this->number = san2(this->number - opposit(n) + _MOD);
		return *this;
	}
	modint<_MOD>& operator *= (const ll n) {
		this->number = (this->number * opposit(n)) % _MOD;
		return *this;
	}
	modint<_MOD>& operator /= (const ll n) {
		this->number = (this->number * inverse(n)) % _MOD;
		return *this;
	}
 
	modint<_MOD> operator + (const modint<_MOD> obj) { modint<_MOD>re(*this); return re += obj; }
	modint<_MOD> operator - (const modint<_MOD> obj) { modint<_MOD>re(*this); return re -= obj; }
	modint<_MOD> operator * (const modint<_MOD> obj) { modint<_MOD>re(*this); return re *= obj; }
	modint<_MOD> operator / (const modint<_MOD> obj) { modint<_MOD>re(*this); return re /= obj; }
	modint<_MOD> operator + (const ll n) { modint<_MOD>re(*this); return re += n; }
	modint<_MOD> operator - (const ll n) { modint<_MOD>re(*this); return re -= n; }
	modint<_MOD> operator * (const ll n) { modint<_MOD>re(*this); return re *= n; }
	modint<_MOD> operator / (const ll n) { modint<_MOD>re(*this); return re /= n; }
 
	modint<_MOD> operator = (const ll n) {
		this->number = opposit(n);
		return *this;
	}
	ll get() {
		return number;
	}
	friend ostream& operator<<(ostream&os, const modint& obj){
		return os<<obj.number;
	}
private:
	ll number;
 
	ll opposit(ll n) {
		if (n < 0)n = _MOD - ((-n) % _MOD);
		return n % _MOD;
	}
	ll inverse(ll n) {
		n = opposit(n);
		ll result = 1;
		for (ll i = _MOD - 2; i; i /= 2) {
			if (i % 2)result = (result * n) % _MOD;
			n = (n * n) % _MOD;
		}
		return result;
	}
	inline ll san2(const ll n) {
		return _MOD <= n ? n - _MOD : n;
	}
};
using mint=modint<>;

int main(){
	cin.tie(0);
	ios::sync_with_stdio(false);
	int n,m;
	cin>>n>>m;
	vl x(n),y(m);
	rep(i,n)cin>>x[i];
	rep(i,m)cin>>y[i];
	/*
		sig(i=0..n-1)sig(j=0..m-1)(面積:dx[i]*dy[j])*(回数:c[i]*c[j])
		sig(i=0..n-1)sig(j=0..m-1)dx[i]*c[i]*dy[j]*c[j]
		(sig(i=0..n-1)dx[i]*c[i]) * (sig(j=0..m-1)dy[j]*c[j])
	*/
	mint ax=0,ay=0;
	rep(i,n-1){
		mint v=x[i+1]-x[i];
		v*=(i+1)*(n-i-1);
		ax+=v;
	}
	rep(i,m-1){
		mint v=y[i+1]-y[i];
		v*=(i+1)*(m-i-1);
		ay+=v;
	}
	cout<<ax*ay<<endl;
	return 0;
}