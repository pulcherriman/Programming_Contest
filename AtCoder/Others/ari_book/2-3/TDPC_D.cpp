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
using tlll=tuple<ll,ll,ll>;
using vs=vector<string>;
#define all(a) a.begin(),a.end()
#define rall(a) a.rbegin(),a.rend()
#define rep(i,n) range(i,0,n)
#define rrep(i,n) for(ll i=(n)-1;i>=0;i--)
#define range(i,a,n) for(ll i=(a);i<(n);i++)
#define LINF ((ll)1ll<<60)
#define INF ((int)1<<30)
#define EPS (1e-9)
#define MOD (1000000007ll)
#define fcout(a) cout<<setprecision(a)<<fixed
#define fs first
#define sc second
#define PI (3.1415926535897932384)

int dx[]={1,0,-1,0,1,-1,-1,1},dy[]={0,1,0,-1,1,1,-1,-1};
template<class T>bool chmax(T&a,T b){if(a<b){a=b; return true;}return false;}
template<class T>bool chmin(T&a,T b){if(a>b){a=b; return true;}return false;}
template<class S>S sum(vector<S>&a){return accumulate(all(a),S());}
template<class S>S max(vector<S>&a){return *max_element(all(a));}
template<class S>S min(vector<S>&a){return *min_element(all(a));}
ll max(int a,ll b){return max((ll)a,b);} ll max(ll a,int b){return max(a,(ll)b);}

template<class T>void puta(T&&t){cout<<t<<"\n";}
template<class H,class...T>void puta(H&&h,T&&...t){cout<<h<<' ';puta(t...);}
template<class S,class T>void tf(bool b,S t,T f){if(b)puta(t);else puta(f);}
void YN(bool b){tf(b,"YES","NO");}
void Yn(bool b){tf(b,"Yes","No");}
void yn(bool b){tf(b,"yes","no");}
template<class S,class T>ostream&operator<<(ostream&os,pair<S,T>p){os<<"["<<p.first<<", "<<p.second<<"]";return os;};
template<class S>auto&operator<<(ostream&os,vector<S>t){bool a=1;for(auto s:t){os<<(a?"":" ")<<s;a=0;}return os;}
template<class S>auto&operator>>(istream&is,vector<S>&t){for(S&a:t)cin>>a;return is;}

/*他のライブラリを入れる場所*/


int main(){
	cin.tie(0);
	ios::sync_with_stdio(false);
	ll n,d;
	cin>>n>>d;


	vl need(3,0);
	while(d%2==0){need[0]++;d/=2;}
	while(d%3==0){need[1]++;d/=3;}
	while(d%5==0){need[2]++;d/=5;}
	if(d!=1){
		fcout(10)<<0<<endl;
		return 0;
	}

	vector<vector<vvd>> dp(2,vector<vvd>(need[0]+1,vvd(need[1]+1,vd(need[2]+1,0.0))));
	dp[0][0][0][0]=1.0;

	rep(i,n){
		int f=i%2,t=1-i%2;
		rep(j,need[0]+1)rep(k,need[1]+1)rep(l,need[2]+1){
			dp[t][j][k][l]+=dp[f][j][k][l]/6;
			dp[t][min(j+1,need[0])][k][l]+=dp[f][j][k][l]/6;
			dp[t][j][min(k+1,need[1])][l]+=dp[f][j][k][l]/6;
			dp[t][min(j+2,need[0])][k][l]+=dp[f][j][k][l]/6;
			dp[t][j][k][min(l+1,need[2])]+=dp[f][j][k][l]/6;
			dp[t][min(j+1,need[0])][min(k+1,need[1])][l]+=dp[f][j][k][l]/6;
			dp[f][j][k][l]=0;
		}
	}
	
	fcout(10)<<dp[n%2][need[0]][need[1]][need[2]]<<endl;
	return 0;
}