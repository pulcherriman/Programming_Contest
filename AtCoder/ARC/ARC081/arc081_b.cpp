#include <bits/stdc++.h>
using namespace std;
using ll=long long;
#define rep(i,n) for(int i=0;i<n;i++)
#define MOD (ll)(1e9+7)

ll ans=1;
void mul(int x){ans=ans*x%MOD;}

int main(){
	int n,prev=0, x[3][3]={{0,3,6},{0,2,2},{0,1,3}};
	cin>>n;
	vector<string> s(2);
	cin>>s[0]>>s[1];
	
	rep(i,n){
		int type=(s[0][i]==s[1][i]?1:2);
		mul(x[prev][type]);
		prev=type;
		if(type==2)i++;
	}
	cout<<ans<<endl;
	return 0;
}
