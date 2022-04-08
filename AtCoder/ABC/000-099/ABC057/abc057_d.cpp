 
#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using vi=vector<int>;
#define rep(i,n) for(int i=0;i<n;i++)
#define all(a) a.begin(),a.end()
#define rall(a) a.rbegin(),a.rend()

int main(){
	int n,a,b;
	cin>>n>>a>>b;
	vector<ll> v(n);
	for(auto&i:v)cin>>i;
	sort(rall(v));
	ll aval=-1, ax=1;
	ll anum=0, c[51][51];
	rep(i,n+1)rep(j,i+1) if(!j or j==i){
		c[i][j]=1;
	}else c[i][j]=c[i-1][j-1]+c[i-1][j];
	
	
	for(int i=a;i<=b;i++){
		ll val=0;
		int w=0;
		for(int j=0;j<i;j++){
			val+=v[j];
			w++;
			if(j and v[j]!=v[j-1]) w=1;
		}
		if(val*ax>aval*i){
			aval=val;
			anum=0;
			ax=i;
		}
		if(val*ax==aval*i) {
			int x=count(all(v),v[i-1]);
			anum+=c[x][w];
		}
	}
	cout<<fixed<<setprecision(7)<<(double)aval/ax<<endl;
	cout<<anum<<endl;
		
	return 0;
}


