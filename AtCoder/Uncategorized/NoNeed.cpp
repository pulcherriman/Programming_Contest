#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using vb=vector<bool>;
using vvb=vector<vb>;
using vd=vector<double>;
using vvd=vector<vd>;
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

int main(){
	cin.tie(0);
	ios::sync_with_stdio(false);
	int n,k;
	cin>>n>>k;
	vl a(n+1,0);
	rep(i,n)cin>>a[i+1];
	n++;
	sort(all(a));
	int l=0,r=n;
	while(r-l>1){
		int m=l+(r-l)/2;
		bool ok=true;
		vl ca;
		rep(i,n)if(i!=m)ca.push_back(a[i]);
		vvb dp(n,vb(k+1,false));
		dp[0][0]=true;
		rep(i,n-1)rep(j,k+1){
			int v=ca[i]+j;
			if(dp[i][j] and v<=k){
				dp[i+1][j]=dp[i+1][v]=true;
				if(k-a[m]<=v and v<k){
					ok=false;
					i=n;
					break;
				}
			}
		}
		if(ok){
			l=m;
		}else{
			r=m;
		}
	}
	cout<<l<<endl;
	return 0;
}