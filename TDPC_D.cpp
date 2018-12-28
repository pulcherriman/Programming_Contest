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

template<typename A, size_t N, typename T>
void Fill(A (&array)[N], const T &val){
	fill( (T*)array, (T*)(array+N), val );
}

int main(){
	cin.tie(0);
	ios::sync_with_stdio(false);
	ll n,k;
	cin>>n>>k;
	vl p{2,3,5}; vector<int> w{0,0,0};
	rep(i,3){
		while(k%p[i]==0){
			k/=p[i];
			w[i]++;
		}
	}
	if(k!=1){
		cout<<0<<endl;
		return 0;
	}
	vector<vector<vvd>> dp(2,vector<vvd>(w[0]+1,vvd(w[1]+1,vd(w[2]+1,0.0))));
	dp[0][0][0][0]=1;
	rep(i,n){
		rep(j,w[0]+1){
			rep(k,w[1]+1){
				rep(l,w[2]+1){
					int i1=i&1;
					int i2=i1^1;
					int j1=min(j+1,w[0]);
					int j2=min(j+2,w[0]);
					int k1=min(k+1,w[1]);
					int l1=min(l+1,w[2]);
					dp[i2][j][k][l]+=dp[i1][j][k][l]/6;
					dp[i2][j1][k][l]+=dp[i1][j][k][l]/6;
					dp[i2][j][k1][l]+=dp[i1][j][k][l]/6;
					dp[i2][j2][k][l]+=dp[i1][j][k][l]/6;
					dp[i2][j][k][l1]+=dp[i1][j][k][l]/6;
					dp[i2][j1][k1][l]+=dp[i1][j][k][l]/6;
					dp[i1][j][k][l]=0;
				}
			}
		}
	}
	fcout(10)<<dp[n&1][w[0]][w[1]][w[2]]<<endl;

	return 0;
}