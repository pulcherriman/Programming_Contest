#include <bits/stdc++.h>
using namespace std;
using ll=long long;
#define rep(i,n) for(int i=0;i<n;i++)
#define range(i,a,n) for(int i=a;i<n;i++)
const ll MOD=(998244353);

class Fermat{
  private:
	int z;
	vector<ll> fact_mod, fact_invmod;
	ll modpow(ll a, ll n){
		if(n==1)return a;
		ll half=modpow(a,n/2);
		return half*half%MOD*(n%2?a:1)%MOD;
	}
  public:
	Fermat(int Z):z(Z){
		fact_mod=vector<ll>(z+1,1);
		fact_invmod.resize(z+1);
		range(i,1,z+1) fact_mod[i]=fact_mod[i-1]*i%MOD;
		fact_invmod[z]=modpow(fact_mod[z],MOD-2);
		for(int i=z-1;i>=0;i--) fact_invmod[i]=fact_invmod[i+1]*(i+1)%MOD;
	}
	ll comb(int n,int r){return fact_mod[n] * fact_invmod[r]%MOD * fact_invmod[n-r]%MOD;}
};

int main(){
    ll n,a,b,k;
    cin>>n>>a>>b>>k;
    if(b<a)swap(a,b);
    
    Fermat f(n);
    ll ans=0;
    rep(i,n+1){
        if((k-a*i)%b==0 and (k-a*i)/b>=0 and (k-a*i)/b<=n){
            ans=(ans+f.comb(n,i)*f.comb(n,(k-a*i)/b))%MOD;
        }
    }
    cout<<ans<<endl;
	return 0;
}
