#include <bits/stdc++.h>
#define rep(i,n) range(i,0,n)
#define range(i,a,n) for(int i=a;i<(n);i++)
using namespace std;

int main(){
	int n,t,ans=0;
  	cin>>n>>t;
  	rep(_,n){
    	int p; cin>>p;
      	ans+=(t*100000+p-ans)%t;
    }
  	cout<<ans<<endl;
	return 0;
}
