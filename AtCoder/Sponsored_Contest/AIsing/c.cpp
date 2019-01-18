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
template<class T>T chmax(T&a,T b){return a=a>b?a:b;}
template<class T>T chmin(T&a,T b){return a=a<b?a:b;}

/*他のライブラリを入れる場所*/

int main(){
	cin.tie(0);
	ios::sync_with_stdio(false);
	int h,w;
	cin>>h>>w;
	vs a(h);
	rep(i,h)cin>>a[i];
	vvi is(h,vi(w,0));
	queue<pll> q;
	ll ans=0;
	rep(i,h)rep(j,w)if(!is[i][j]){
		q.emplace(i,j);
		ll d=0,e=0;
		while(!q.empty()){
			int y,x;
			tie(y,x)=q.front(); q.pop();
			if(is[y][x])continue;
			is[y][x]=1;
			if(a[y][x]=='.')d++;
			else e++;
			rep(v,4){
				int ny=y+dy[v];
				int nx=x+dx[v];
				if(ny<0 or ny>=h or nx<0 or nx>=w)continue;
				if(is[ny][nx])continue;
				if(a[y][x]==a[ny][nx])continue;
				q.emplace(ny,nx);
			}
		}
		ans+=d*e;
	}
	cout<<ans<<endl;
	return 0;
}