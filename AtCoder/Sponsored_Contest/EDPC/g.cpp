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
template<class T>T chmax(T&a,T b){return a=a>b?a:b;}
template<class T>T chmin(T&a,T b){return a=a<b?a:b;}

/*他のライブラリを入れる場所*/

int main(){
	cin.tie(0);
	ios::sync_with_stdio(false);
	int n,m;
	cin>>n>>m;
	vvi e(n);
	set<int> s;
	rep(i,n)s.insert(i);
	rep(i,m){
		int x,y;cin>>x>>y;
		e[x-1].push_back(y-1);
		s.erase(y-1);
	}
	vi ans(n,-1);
	vi delay(n,0);
	for(auto&st:s){
		queue<int> q;
		q.push(st);
		ans[st]=0;
		while(!q.empty()){
			int ind=q.front();
			q.pop();
			for(auto&nx:e[ind]){
				if(ans[nx]<ans[ind]+1){
					if(ans[nx]==-1){
						ans[nx]=ans[ind]+1;
						q.push(nx);
					}else{
						chmax(delay[nx],ans[ind]+1-ans[nx]);
					}
				}
			}
		}
	}
	vi fans(n,-1);
	for(auto&st:s){
		queue<int> q;
		q.push(st);
		ans[st]=0;
		while(!q.empty()){
			int ind=q.front();
			q.pop();
			for(auto&nx:e[ind]){
				if(ans[nx]<ans[ind]+1){
					if(ans[nx]==-1){
						ans[nx]=ans[ind]+1;
						q.push(nx);
					}else{
						chmax(delay[nx],ans[ind]+1-ans[nx]);
					}
				}
			}
		}
	}
	cout<<*max_element(all(ans))<<endl;

	return 0;
}