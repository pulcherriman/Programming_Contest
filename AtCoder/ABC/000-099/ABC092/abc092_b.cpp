#include <bits/stdc++.h>
using namespace std;

int main(){
	int n,d,x;
  	cin>>n>>d>>x;
  	int ans=x;
  	for(int i=0;i<n;i++){
      	int p;
      	cin>>p;
      	ans+=(d-1)/p+1;
    }
  	cout<<ans<<endl;
}