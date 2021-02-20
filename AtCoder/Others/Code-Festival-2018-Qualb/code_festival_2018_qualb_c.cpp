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
	
	int n,l;
	cin>>n;
	l=n/5*5;
	using vb=vector<bool>;
	using vvb=vector<vb>;
	
	vvb a(n,vb(n,false));
	rep(i,n){
	    rep(j,n){
	        if(i%5==0 && j%5==0) a[i][j]=true;
	        if(i%5==1 && j%5==3) a[i][j]=true;
	        if(i%5==2 && j%5==1) a[i][j]=true;
	        if(i%5==3 && j%5==4) a[i][j]=true;
	        if(i%5==4 && j%5==2) a[i][j]=true;
	    }
	}
    rep(i,n){
        if(i%5==3)a[i][0]=true;
    }
    rep(j,n){
        if(j%5==2)a[0][j]=true;
    }
    rep(i,n){
        if(a[i][n-1])continue;
        if(i!=0 && a[i-1][n-1])continue;
        if(i!=n-1 && a[i+1][n-1])continue;
        a[i][n-1]=true;
    }
    rep(j,n){
        if(a[n-1][j])continue;
        if(j!=0 && a[n-1][j-1])continue;
        if(j!=n-1 && a[n-1][j+1])continue;
        a[n-1][j]=true;
    }
    
	rep(i,n){
	    rep(j,n){
	        cout<<(a[i][j]?"X":".");
	    }
	    cout<<endl;
	}
	return 0;
}
