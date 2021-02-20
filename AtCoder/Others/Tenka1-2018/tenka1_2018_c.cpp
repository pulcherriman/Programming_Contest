#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using vi=vector<ll>;
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
#define LINF    	((ll)1ll<<60)
#define INF     	((int)1<<30)
#define EPS     	(1e-9)
#define MOD     	(1000000007)
#define fcout(a)	cout<<setprecision(a)<<fixed
#define fs 			first
#define sc			second
#define PI			3.141592653589793

template<class S,class T>ostream& operator<<(ostream&os,pair<S,T>p){os<<"["<<p.first<<", "<<p.second<<"]";return os;};
template<class S>auto&operator<<(ostream&os,vector<S>t){bool a=1; for(auto s:t){os<<(a?"":" ")<<s; a=0;} return os;}

int main(){
	cin.tie(0);
   	ios::sync_with_stdio(false);
	
	ll n;
	cin>>n;
	vl a(n);
	rep(i,n)cin>>a[i];
	sort(all(a));
	ll t=n/2;
	ll ans=0;
	vl q,w;
	
	
	rep(i,n){
	    if(i<t)q.push_back(a[i]);
	    else w.push_back(a[i]);
	}
	if(t==n-t){
	    ll v=accumulate(all(w),0ll)*2-w.front();
	    ll z=accumulate(all(q),0ll)*2-q.back(); //-(q.size()>1?q[q.size()-2]:0)
	    ans=v-z;
	    //cout<<v<<","<<z<<endl;
	}else{
	    {
    	    ll v=accumulate(all(q),0ll)*2;
    	    ll z=accumulate(all(w),0ll)*2-w.front()-(w.size()>1?w[1]:0);
    	    ans=z-v;
	    }
	    {
	        q.clear(); w.clear();
	        rep(i,n){
        	    if(i<t+1)q.push_back(a[i]);
        	    else w.push_back(a[i]);
        	}
    	    ll v=accumulate(all(w),0ll)*2;
    	    ll z=accumulate(all(q),0ll)*2-q.back()-(q.size()>1?q[q.size()-2]:0);
    	    ans=max(ans,v-z);
	    }
	}
	if(ans<0)cout<<w[INF];
	cout<<ans<<endl;
	return 0;
}
