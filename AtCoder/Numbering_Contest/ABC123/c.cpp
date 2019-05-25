#include <bits/stdc++.h>
using namespace std;
using ll=long long;
#define rep(i,n) for(int i=0;i<n;i++)
int main(){
	ll n;
	vector<ll> a(5);
	cin>>n>>a[0]>>a[1]>>a[2]>>a[3]>>a[4];
	
	cout<<4+ll(ceil(n*1.0/(*min_element(a.begin(),a.end()))))<<endl;
}