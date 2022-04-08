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

vl a,b;
ll solve(ll n, ll x){
    if(n==0) return x;
    if(x<=1) return 0;
    if(x<=1+a[n-1]) return solve(n-1,x-1);
    return b[n-1]+1+solve(n-1,min(x-a[n-1]-2,a[n-1]));
}

int main(){
	cin.tie(0);
   	ios::sync_with_stdio(false);
	
	ll n,x;
	cin>>n>>x;
	a=vl(n+1,0); a[0]=1;
	b=vl(n+1,0); b[0]=1;
	range(i,1,n+1){
	    a[i]=a[i-1]*2+3;
	    b[i]=b[i-1]*2+1;
	}
	cout<<solve(n,x)<<endl;
	return 0;
}
