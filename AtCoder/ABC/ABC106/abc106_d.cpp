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
	int n,m,q;
	cin>>n>>m>>q;
	vvi a(n+1,vi(n+1,0));
	rep(i,m){
	    int l,r;
	    cin>>l>>r;
	    a[l][r]++;
	}

	rep(i,n+1)rep(j,n)a[i][j+1]+=a[i][j];
	rep(j,n+1)rep(i,n)a[i+1][j]+=a[i][j];

	rep(i,q){
	    int p,q;
	    cin>>p>>q;
	    p--;
	    cout<<a[q][q]-a[p][q]-a[q][p]+a[p][p]<<endl;
	}
}
