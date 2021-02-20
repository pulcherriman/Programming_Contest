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
template<class T>bool chmax(T&a,T b){if(a<b){a=b; return true;}return false;}
template<class T>bool chmin(T&a,T b){if(a>b){a=b; return true;}return false;}
template<class S>S sum(vector<S>&a){return accumulate(all(a),S());}
template<class S>S max(vector<S>&a){return *max_element(all(a));}
template<class S>S min(vector<S>&a){return *max_element(all(a));}

template<class T>void puta(T&&t){cout<<t<<endl;}
template<class H,class...T>void puta(H&&h,T&&...t){cout<<h<<' ';puta(t...);}
template<class S,class T>void tf(bool b,S t,T f){if(b)puta(t);else puta(f);}
void OUT(bool b){tf(b,"YES","NO");}
void Out(bool b){tf(b,"Yes","No");}
void out(bool b){tf(b,"yes","no");}
template<class S,class T>ostream&operator<<(ostream&os,pair<S,T>p){os<<"["<<p.first<<", "<<p.second<<"]";return os;};
template<class S>auto&operator<<(ostream&os,vector<S>t){bool a=1;for(auto s:t){os<<(a?"":" ")<<s;a=0;}return os;}
template<class S>auto&operator>>(istream&is,vector<S>&t){for(S&a:t)cin>>a;return is;}

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
	int h,w;
	cin>>h>>w;
	vs f(h+2);
	rep(i,h+2){
		if(i%(h+1)==0){
			f[i]=string(w+2,'X');
		}else{
			string s;cin>>s;
			f[i]="X"+s+"X";
		}
	}
	ll s,t;
	rep(i,h+2)rep(j,w+2){
		if(f[i][j]=='s'){s=i*1000+j; f[i][j]='.';}
		if(f[i][j]=='g'){t=i*1000+j; f[i][j]='.';}
	}
	priority_queue<pll> q;
	q.emplace(0,s);
	vl a(1000000,1);
	while(!q.empty()){
		ll c,p;
		tie(c,p)=q.top();
		q.pop();
		int y=p/1000, x=p%1000;
		if(a[p]!=1)continue;
		a[p]=c;
		rep(v,4){
			int ny=y+dy[v];
			int nx=x+dx[v];
			int np=ny*1000+nx;
			if(f[ny][nx]=='X')continue;
			if(a[np]!=1)continue;
			if(f[ny][nx]=='#' and c>-2){
				q.emplace(c-1,np);
			}
			if(f[ny][nx]=='.'){
				q.emplace(c,np);
			}
		}
	}
	OUT(a[t]!=1);
	return 0;
}