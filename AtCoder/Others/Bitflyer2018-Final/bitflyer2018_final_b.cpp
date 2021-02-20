#include <bits/stdc++.h>
#include <cxxabi.h>
using namespace std;
using ll=long long;
using vi=vector<int>;
using vvi=vector<vi>;
using pii=pair<int,int>;
#define rep(i,n) range(i,0,n)
#define range(i,a,n) for(int i=a;i<n;i++)
#define all(a) a.begin(),a.end()
#define LINF    ((ll)1ll<60)
#define INF     ((int)1<<30)
#define EPS     (1e-9)
#define MOD     (1000000007)
template<class S,class T>ostream& operator<<(ostream&os,pair<S,T>p){os<<"["<<p.first<<", "<<p.second<<"]";return os;};
template<class S>auto&operator<<(ostream&os,vector<S>t){bool b=1;for(auto s:t)os<<(exchange(b,0)||strlen(abi::__cxa_demangle(typeid(S).name(),0,0,0))>20?"":" ")<<s;return os<<endl;}

int main(){
	cin.tie(0);
   	ios::sync_with_stdio(false);
	
	ll n,q;
	cin>>n>>q;
	vector<ll> x(n),y(n+1,0);
	rep(i,n){
		cin>>x[i];
		y[i+1]=x[i];
	}
	partial_sum(all(y),y.begin());
	rep(_,q){
		ll c,d;
		cin>>c>>d;
		ll m=lower_bound(all(x),c)-x.begin();
		ll l=lower_bound(all(x),c-d)-x.begin();
		ll r=upper_bound(all(x),c+d)-x.begin()-1;
		ll ans=d*(l+n-r-1);
		if(m==n){
			ans+=c*(r-l+1)-(y[r+1]-y[l]);
		}else if(m==0){
			ans+=(y[r+1]-y[l])-c*(r-l+1);
		}else{
			ans+=(m-l)*c-(y[m]-y[l]);
			ans+=(y[r+1]-y[m])-(r+1-m)*c;
		}
		cout<<ans<<endl;
	}
	return 0;
}
 
