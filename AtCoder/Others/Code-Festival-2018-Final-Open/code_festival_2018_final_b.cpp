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

vd fact_log10;

int main(){
	cin.tie(0);
   	ios::sync_with_stdio(false);
	
	int n,m,r;
	cin>>n>>m;
	fact_log10.resize(n+1,0);
    range(i,1,n+1){
        fact_log10[i]=fact_log10[i-1]+log10(i);
    }
	
	double ans=n*log10(m);
	rep(i,m){
	    cin>>r;
	    ans-=fact_log10[n]-(fact_log10[r]+fact_log10[n-r]);
        n-=r;
	}
	cout<<(int)ceil(ans)<<endl;
	return 0;
}
