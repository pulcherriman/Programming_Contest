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

int main(){
	cin.tie(0);
   	ios::sync_with_stdio(false);
   	int n;
   	cin>>n;
   	vl a(n);
   	rep(i,n)cin>>a[i];
   	ll ans=0;
   	vvl dp(n,vl(1000,0));
   	rep(i,a[0]+1){
   	    dp[0][i]=1;
   	}
   	range(i,0,n-1){
   	    rep(j,dp[i].size()){
   	        dp[i][j]%=MOD;
   	        if(j==1){
   	            ans+=dp[i][j];
   	            ans%=MOD;
   	            continue;
   	        }
   	        if(j%2==1) continue;
   	        rep(k,a[i+1]+1){
   	            dp[i+1][j/2+k]=(dp[i+1][j/2+k]+dp[i][j])%MOD;
   	        }
   	    }
   	}
   	rep(i,10){
   	    ans+=dp[n-1][1<<i];
        ans%=MOD;
   	}
   	cout<<ans<<endl;
}
