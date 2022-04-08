 
#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using vi=vector<int>;
using vvi=vector<vi>;
using pii=pair<int,int>;
#define rep(i,n) for(int i=0;i<n;i++)
#define all(a) a.begin(),a.end()
#define rall(a) a.rbegin(),a.rend()
#define INF 1e9
#define EPS 1e-9
#define MOD (1e9+7)
void put(string d){}template<class H,class...T>void put(string d,H&h,T&...t){cout<<h;if(sizeof...(t))cout<<d;put(d,t...);}
template<class T>void puti(T&a,string d=" "){bool f=1;for(auto&_:a)cout<<(exchange(f,0)?"":d)<<_;cout<<endl;}
template<class T>void putii(T&a,string d=" "){for(auto&_:a)puti(_,d);}

int main(){
	int n,ma,mb;
	cin>>n>>ma>>mb;
	vvi med(n,vi(3));
	for(auto&l:med)for(auto&i:l)cin>>i;
	
	int dp[n+1][401][401];
	fill(dp[0][0],dp[n+1][0],10000);
	dp[0][0][0]=0;
	
	for(int i=1;i<=n;i++){
		for(int j=0;j<=10*(i-1);j++){
			for(int k=0;k<=10*(i-1);k++){
				if(dp[i-1][j][k]!=10000){
					dp[i][j][k]=min(dp[i][j][k],dp[i-1][j][k]);
					dp[i][j+med[i-1][0]][k+med[i-1][1]]=
						min(dp[i][j+med[i-1][0]][k+med[i-1][1]],
							dp[i-1][j][k]+med[i-1][2]);
				}
			}
		}
	}
	int ans=10000;
	for(int i=1;i*max(ma,mb)<401;i++){
		ans=min(ans,dp[n][ma*i][mb*i]);
	}
	cout<<(ans==10000?-1:ans)<<endl;
	
	
	return 0;
}