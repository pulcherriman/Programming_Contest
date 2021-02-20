#include<bits/stdc++.h>
using namespace std;
#define rep(i,n) for(int i=0;i<n;i++)
int main(){
int n;
cin>>n;
vector<int> p(n);
rep(i,n)cin>>p[i];
vector<vector<int>> dp(n+1,vector<int>(10001,0));
dp[0][0]=1;
rep(i,n)rep(j,10000)if(dp[i][j])dp[i+1][j+p[i]]=dp[i+1][j]=1;
cout<<accumulate(dp[n].begin(),dp[n].end(),0)<<endl;
}