#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using vi=vector<int>;
using vvi=vector<vi>;
using vd=vector<double>;
using vvd=vector<vd>;
using vl=vector<ll>;
using vvl=vector<vl>;
using pii=pair<int,int>;
using vs=vector<string>;
#define rep(i,n) range(i,0,n)
#define range(i,a,n) for(int i=a;i<n;i++)
#define all(a) a.begin(),a.end()
#define LINF    	((ll)1ll<60)
#define INF     	((int)1<<30)
#define EPS     	(1e-9)
#define MOD     	(1000000007)
#define fcout(a)	cout<<setprecision(a)<<fixed
#define fs 			first
#define sc			second
#define PI			3.141592653589793

template<class S,class T>ostream& operator<<(ostream&os,pair<S,T>p){os<<"["<<p.first<<", "<<p.second<<"]";return os;};
template<class S>auto&operator<<(ostream&os,vector<S>t){bool a=1; for(auto s:t){os<<(a?"":" ")<<setw(3)<<s; a=0;} return os;}

int main(){
	cin.tie(0);
   	ios::sync_with_stdio(false);
	
	int n,m;cin>>n>>m;
	vl a(n+1,0);rep(i,n)cin>>a[i+1];
	partial_sum(all(a),a.begin());

    map<ll,ll> mp;
	rep(i,n+1){
	    a[i]%=m;
	    if(mp.find(a[i])==mp.end())mp[a[i]]=0;
	    mp[a[i]]++;
	}

	ll ans=0;
	for(auto m:mp){
	    if(m.second==1)continue;
	    ans+=m.second*(m.second-1)/2;
	}
	cout<<ans<<endl;
	return 0;
}
