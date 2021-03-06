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
template<class T>
void puta(T&&t){cout<<t<<endl;}
template<class H,class...T>
void puta(H&&h,T&&...t){cout<<h<<' ';puta(t...);}

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
	ll n,w;
	cin>>n>>w;
	vector<deque<ll>> v(4);
	ll w0=0;
	rep(i,n){
		ll W,V;
		cin>>W>>V;
		if(i==0){
			w0=W;
		}
		v[W-w0].push_back(V);
	}
	rep(i,4){
		sort(rall(v[i]));
		v[i].push_front(0);
		partial_sum(all(v[i]),v[i].begin());
	}
	ll ans=-1;
	rep(i,v[0].size())
	rep(j,v[1].size())
	rep(k,v[2].size())
	rep(l,v[3].size()){
		if(i*w0+j*(w0+1)+k*(w0+2)+l*(w0+3)>w)continue;
		ans=max(ans,v[0][i]+v[1][j]+v[2][k]+v[3][l]);
	}
	cout<<ans<<endl;
	return 0;
}