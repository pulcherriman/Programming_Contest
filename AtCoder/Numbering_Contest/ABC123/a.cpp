#include <bits/stdc++.h>
using namespace std;
using ll=long long;
int main(){
	vector<long> a(5);
	ll k;
	cin>>a[0]>>a[1]>>a[2]>>a[3]>>a[4]>>k;
	cout<<(a[4]-a[0]<=k?"Yay!":":(")<<endl;
}