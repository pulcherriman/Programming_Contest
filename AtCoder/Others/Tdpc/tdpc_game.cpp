#include <bits/stdc++.h>
using namespace std;
using vi=vector<int>;
using vvi=vector<vi>;
#define rep(i,n) for(int i=0;i<n;i++)
#define all(a) a.begin(),a.end()

int main(){
	int a,b;
	cin>>a>>b;
	vi va(a+1,0),sa(a+1),vb(b+1,0),sb(b+1);
	rep(i,a) cin>>va[i]; reverse(all(va)); partial_sum(all(va),sa.begin());
	rep(i,b) cin>>vb[i]; reverse(all(vb)); partial_sum(all(vb),sb.begin());
	
	vvi dp(a+1,vi(b+1,0));
	rep(i,a+1)rep(j,b+1){	
		if(i<a) dp[i+1][j]=max(dp[i+1][j], sa[i+1]+sb[j]-dp[i][j]);
		if(j<b) dp[i][j+1]=max(dp[i][j+1], sa[i]+sb[j+1]-dp[i][j]);
	}
	
	cout<<dp[a][b]<<endl;
	return 0;
}
