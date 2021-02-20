#include <bits/stdc++.h>
using namespace std;
using vi=vector<int>;
#define rep(i,n) for(int i=0;i<n;i++)
#define all(a) a.begin(),a.end()

int main(){
	int n,t; cin>>n>>t;
	vi v(n),mx(n,0);
	for(auto&i:v)cin>>i;
	mx[n-1]=v[n-1];
	for(int i=n-2;i>=0;i--) mx[i]=max(mx[i+1],v[i]);
	rep(i,n) mx[i]-=v[i];
	cout<<count(all(mx),*max_element(all(mx)))<<endl;
	return 0;
}
