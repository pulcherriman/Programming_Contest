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
#define range(i,a,n) for(int i=(a);i<(n);i++)
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

int main(){
	cin.tie(0);
	ios::sync_with_stdio(false);
	ll n,s;
	cin>>n>>s;
	/*
		nのb進表記が1桁：b>n
		nのb進表記が2桁：n>=b>√n
		nのb進表記がd桁：(d-1)√n>=b>d√n
	*/
	if(n==s){
		cout<<n+1<<endl;
		return 0;
	}
	if(n<s){
		cout<<-1<<endl;
		return 0;
	}
	//小さいbから全探索
	for(ll b=2;b*b<=n;b++){
		ll f=0,t=n;
		while(t){
			f+=t%b;
			t/=b;
		}
		if(f==s){
			cout<<b<<endl;
			return 0;
		}
	}
	/*
		b>√nなら、nは2桁以下
		x*b+y==n
		x+y==sより
		b-1==(n-s)/x, b==(n-s)/x+1  x<b -> x<√n
	*/
	for(ll x=(ll)ceil(sqrt(n))-1;x>0;x--){
		ll b=(n-s)/x+1;
		ll d=n%b+n/b;
		if(d==s){
			cout<<b<<endl;
			return 0;
		}
	}
	cout<<-1<<endl;
	return 0;
}