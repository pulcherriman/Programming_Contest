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
template<class S>auto&operator<<(ostream&os,vector<S>t){bool a=1; for(auto s:t){os<<(a?"":" ")<<s; a=0;} return os;}

int main(){
	cin.tie(0);
   	ios::sync_with_stdio(false);
	int h,w;
	cin>>h>>w;
	vvl f(h+2,vl(w+2,0));
	vvl l(h+2,vl(w+2,0));
	vvl t(h+2,vl(w+2,0));
	vvl r(h+2,vl(w+2,0));
	vvl b(h+2,vl(w+2,0));
	range(i,1,h+1)range(j,1,w+1){
	    char c;cin>>c;
	    if(c=='.')f[i][j]=1;
	}
	rep(i,h+2){
	    int len=0;
	    rep(j,w+2){
	        if(f[i][j]==1) l[i][j]=++len;
	        else len=0;
	    }
	}
	rep(i,h+2){
	    int len=0;
	    for(int j=w+1;j>=0;j--){
	        if(f[i][j]==1) r[i][j]=++len;
	        else len=0;
	    }
	}
	rep(j,w+2){
	    int len=0;
	    rep(i,h+2){
	        if(f[i][j]==1) t[i][j]=++len;
	        else len=0;
	    }
	}
	rep(j,w+2){
	    int len=0;
	    for(int i=h+1;i>=0;i--){
	        if(f[i][j]==1) b[i][j]=++len;
	        else len=0;
	    }
	}
	ll ans=0;
	rep(i,h+2)rep(j,w+2)if(f[i][j]==1){
	    ans+=(l[i][j]-1)*(b[i][j]-1);
	    ans+=(r[i][j]-1)*(t[i][j]-1);
	    ans+=(b[i][j]-1)*(r[i][j]-1);
	    ans+=(t[i][j]-1)*(l[i][j]-1);
	}
	cout<<ans<<endl;
	return 0;
}
