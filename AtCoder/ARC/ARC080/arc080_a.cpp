#include <bits/stdc++.h>
using namespace std;
#define rep(i,n) for(int i=0;i<n;i++)

int main(){
	int n; cin>>n;
	int a[]={0,0,0};
	rep(i,n){
		int t; cin>>t;
		a[t%4?t%2?0:1:2]++;
	}
	if(a[0]-a[2]>1 or (a[0]-a[2]==1 and a[1]))cout<<"No"<<endl;
	else cout<<"Yes"<<endl;
	return 0;
}
