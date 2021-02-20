#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using vi=vector<int>;
using vvi=vector<vi>;
using vd=vector<double>;
using vvd=vector<vd>;
using vl=vector<ll>;
using vvl=vector<vl>;
using pii=pair<int,int>;
using vs=vector<string>;
#define rep(i,n) range(i,0,n)
#define range(i,a,n) for(int i=a;i<n;i++)
#define all(a) a.begin(),a.end()
#define LINF    	((ll)1ll<<60)
#define INF     	((int)1<<30)
#define EPS     	(1e-9)
#define MOD     	(1000000007)
#define fcout(a)	cout<<setprecision(a)<<fixed
#define fs 			first
#define sc			second
#define PI			3.141592653589793

template<class S,class T>ostream& operator<<(ostream&os,pair<S,T>p){os<<"["<<p.first<<", "<<p.second<<"]";return os;};
template<class S>auto&operator<<(ostream&os,vector<S>t){bool a=1; for(auto s:t){os<<(a?"":" ")<<s; a=0;} return os;}
/* nCrを高速に求める
 * 前計算：O(n)
 * 本計算：O(1)
 *
 * Fermat fer(10);	//n,rは引数以下の値を使用できる。この例では、11C1などは計算できない
 * cout<<fer.comb(10,3)<<endl;
 */

int main(){
	cin.tie(0);
   	ios::sync_with_stdio(false);
	
	int n,d;
	cin>>n>>d;
	vi a(n);
	rep(i,n)cin>>a[i];
	vector<vvl> dp(n+1,vvl(n+1,vl(256,0)));//i番目まででj個使って、答えがkになる組合せの数
	dp[0][0][0]=1;
	rep(i,n){
	    rep(j,i+1){
    	    rep(k,256){
        	    dp[i+1][j][k]=(dp[i+1][j][k]+dp[i][j][k])%MOD;
    	        dp[i+1][j+1][k^a[i]]=(dp[i+1][j+1][k^a[i]]+dp[i][j][k])%MOD;
    	    }
	    }
	}

	vl fact(n+1,1);
	range(i,1,n+1){
	    fact[i]=fact[i-1]*i%MOD;
	}

	ll ans=0;
	rep(i,n+1){
	    ans=(ans+fact[i]*dp[n][i][d]%MOD)%MOD;
	}
	cout<<ans<<endl;
	return 0;
}
