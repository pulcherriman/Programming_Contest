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
	
	int h,w,k;
	cin>>h>>w>>k;
	vvl dp(h+1,vl(w,0ll));
	dp[0][0]=1;
	rep(i,h){
	    rep(s,1<<(w-1)){
	        bool ok=true;
	        rep(j,w-2){
	            ok&=((s&(3<<j))!=(3<<j));
	        }
	        if(!ok)continue;
//	        cout<<bitset<7>(s).to_string()<<endl;
    	    rep(j,w){
    	        if(j>0 and s&(1<<(j-1))){
    	            dp[i+1][j-1]+=dp[i][j];
    	        }else if(j<w-1 and s&(1<<(j))){
    	            dp[i+1][j+1]+=dp[i][j];
    	        }else{
        	        dp[i+1][j]+=dp[i][j];
    	        }
    	    }
	    }
	    rep(j,w)dp[i+1][j]%=MOD;
	}
	cout<<dp[h][k-1]<<endl;
	//for(auto&l:dp)cout<<l<<endl;
}
