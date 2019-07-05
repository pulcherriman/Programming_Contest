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
	ll n,m,l;
	cin>>n>>m>>l;
	vl k(n), s(m+1,0);
	cin>>k; rep(i,m)cin>>s[i+1];
	partial_sum(all(s),s.begin());

	sort(rall(k));
	vvl dp(n, vl(n, LINF));
	dp[0][1]=dp[1][0]=(s[k[0]]-s[k[1]-1])/l;
	range(len,3,n+1){
		rep(i,len-2){
			ll j=(i+1==len-1 ? max(i-1,0) : len-2);
			chmin(dp[i][len-1], dp[i][j] + (s[k[j]] - s[k[len-1]-1]) / l );
			chmin(dp[len-1][j], dp[i][j] + (s[k[i]] - s[k[len-1]-1]) / l );
			chmin(dp[j][len-1], dp[j][i] + (s[k[i]] - s[k[len-1]-1]) / l );
			chmin(dp[len-1][i], dp[j][i] + (s[k[j]] - s[k[len-1]-1]) / l );
		}
	}
	ll ans=LINF;
	rep(i,n)range(j,i+1,n)if(i==n-1 or j==n-1){
		chmin(ans, dp[i][j]+(s[k[i]] - s[k[j]-1])/l);
	}
	puta(ans);
	return 0;
}