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

int n;

bool inner(int x,int y){
    return ((abs(x-n/2.0)+abs(y-n/2.0))*2<=n);
}

bool judge(int a,int b,int c,int d){
    return (inner(a,b) and inner(a,d) and inner(c,b) and inner(c,d));
}

int main(){
	cin.tie(0);
   	ios::sync_with_stdio(false);
	
	cin>>n;
	int ans=0;
	rep(i,n)rep(j,n){
	    ans+=judge(i,j,i+1,j+1);
	}
	cout<<ans<<endl;
	
	return 0;
}
