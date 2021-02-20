#include <bits/stdc++.h>
#define rep(i,n) range(i,0,n)
#define range(i,a,n) for(int i=a;i<(n);i++)
using namespace std;

int main(){
	int n,k,ans=0;
	cin>>n>>k;
	rep(i,77)if(i*9%11==k&&i%7>1){
	    ans+=floor(((n-1)*7.0-i)/77.0)-(i<7?1:0)+1;
	}
	cout<<ans<<endl;
	return 0;
}
