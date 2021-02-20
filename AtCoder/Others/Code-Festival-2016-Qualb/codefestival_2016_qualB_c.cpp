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
	using data=pair<ll,int>;
	int X,Y;
	cin>>X>>Y;
	vector<data> p;
	rep(i,X){
	    ll t;
	    cin>>t;
	    p.emplace_back(t,0);
	}
	rep(i,Y){
	    ll t;
	    cin>>t;
	    p.emplace_back(t,1);
	}
	sort(all(p));
	int usex=0,usey=0;
	ll ans=0;
	for(auto&d:p){
	    ll cost; int xy;
	    tie(cost,xy)=d;
	    if(xy==0){
    	    ans+=cost*(Y+1-usey);
    	    usex++;
	    }else{
    	    ans+=cost*(X+1-usex);
    	    usey++;
	    }
	}
	cout<<ans<<endl;
	return 0;
}
