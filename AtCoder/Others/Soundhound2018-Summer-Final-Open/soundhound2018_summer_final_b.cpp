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

ll LLMIN=-1*(1ll<<62);
int main(){
	cin.tie(0);
   	ios::sync_with_stdio(false);
	
	int n,k;
	cin>>n>>k;
	vl a(n);
	rep(i,n)cin>>a[i];
	vvl dp(n+1,vl(2,LLMIN));
	dp[0][1]=0;
	rep(i,n){
	    if(dp[i][0]!=LLMIN)dp[i+1][1]=max(dp[i+1][1],dp[i][0]+a[i]);   //i番目を使う場合 1つ前を使っていない場合
	    if(dp[i][1]!=LLMIN)dp[i+1][1]=max(dp[i+1][1],dp[i][1]+a[i]);   //i番目を使う場合 1つ前を使っている場合
	    if(dp[i][0]!=LLMIN)dp[i+1][0]=max(dp[i+1][0],dp[i][0]);        //i番目を使わない場合 1つ前も使っていない場合
	    if(i+k<=n and dp[i][1]!=LLMIN)dp[i+k][0]=max(dp[i+k][0],dp[i][1]);        //i番目を使わない場合 1つ前を使っている場合
	}
	cout<<max(dp[n][0],dp[n][1])<<endl;
}
