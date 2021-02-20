#include <bits/stdc++.h>
using namespace std;
using vi=vector<int>;
using vd=vector<double>;
#define rep(i,n) for(int i=0;i<n;i++)
#define all(a) a.begin(),a.end()

int main(){
	int k,n;
	cin>>k; n=1<<k;
	vi rate(n); rep(i,n)cin>>rate[i];
	
	vector<vd> dp(k+1,vd(n,1.0));
	rep(i,k){
		int b=1<<i;
		rep(j,n){	//jがたたかう
			int s=((j/b)^1)*b;
			dp[i+1][j]=0.0;
			for(int k=s;k<s+b;k++){
				dp[i+1][j]+=dp[i][j]*dp[i][k]/(1+pow(10,(rate[k]-rate[j])/400.0));
			}
		}
	}
	
	cout.precision(9);
	rep(i,n){
		cout<<fixed<<dp[k][i]<<endl;
	}
	
	return 0;
}
