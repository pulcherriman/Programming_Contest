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

int main(){
	cin.tie(0);
	ios::sync_with_stdio(false);
	string s;
	int x,y;
	cin>>s>>x>>y;
	int t=0;
	vi a(1,0),b;
	rep(i,s.size()){
		if(s[i]=='T'){
			t++;
			(t%2?b:a).push_back(0);
		}else{
			(t%2?b:a).back()++;
		}
	}
	int n=s.size();
	vvi dp(2,vi(n*2+1,0));
	dp[0][n]=1;
	rep(i,a.size()){
		rep(j,n*2+1){
			if(dp[i%2][j]){
				if(i==0 and s[0]=='F'){
					dp[(i%2)^1][j+a[i]]=1;
				}else{
					dp[(i%2)^1][j+a[i]]=1;
					dp[(i%2)^1][j-a[i]]=1;
				}
			}
			dp[i%2][j]=0;
		}
	}
	vvi dp2(2,vi(n*2+1,0));
	dp2[0][n]=1;
	rep(i,b.size()){
		rep(j,n*2+1){
			if(dp2[i%2][j]){
				dp2[(i%2)^1][j+b[i]]=1;
				dp2[(i%2)^1][j-b[i]]=1;
			}
			dp2[i%2][j]=0;
		}
	}
	Out(dp[a.size()%2][x+n] and dp2[b.size()%2][y+n]);
	return 0;
}