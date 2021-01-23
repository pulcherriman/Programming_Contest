#include <bits/stdc++.h>
using namespace std;
using ll=long long;
#define rep(i,n) for(int i=0;i<n;i++)
int main(){
	vector<long> a(5);
	cin>>a[0]>>a[1]>>a[2]>>a[3]>>a[4];
	ll ans=1000000;
	rep(i,5){
		ll cnt=0;
		rep(j,5){
			if(i==j)cnt+=a[j];
			else cnt+=(a[j]%10==0?a[j]:(a[j]/10+1)*10);
		}
		ans=min(ans,cnt);
	}
	cout<<ans<<endl;
}