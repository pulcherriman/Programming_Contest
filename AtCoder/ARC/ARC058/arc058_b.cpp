#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using vl=vector<ll>;
using vvl=vector<vl>;
#define rep(i,n) for(int i=0;i<n;i++)
#define range(i,a,n) for(int i=a;i<n;i++)
#define MOD ((int)(1e9+7))
const int z=200001;

vl fact_mod(z,1), fact_invmod(z);

ll modpow(ll a, ll n){
	if(n==1)return a;
	ll half=modpow(a,n/2);
	return (n%2?modpow(a,n-1)*a:half*half)%MOD;
}

void calc(){
	range(i,1,z) fact_mod[i]=fact_mod[i-1]*i%MOD;
	fact_invmod[z-1]=modpow(fact_mod[z-1],MOD-2);
	for(int i=z-2;i>=0;i--) fact_invmod[i]=fact_invmod[i+1]*(i+1)%MOD;
}

ll nCr_mod(int n,int r){
	return fact_mod[n] * fact_invmod[r]%MOD * fact_invmod[n-r]%MOD;
}

int main(){
	calc();
	int h,w,a,b,n,r;
	cin>>h>>w>>a>>b;
	ll ans=0;
	rep(i,h-a){
		r=b-1;
		n=i+r;
		ll nCr_l=nCr_mod(n,r);
		r=w-b-1;
		n=h-i-1+r;
		ll nCr_r=nCr_mod(n,r);
		ans+=nCr_l*nCr_r%MOD;
	}
	cout<<ans%MOD<<endl;

	return 0;
}
