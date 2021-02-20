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
	
	vd x(3),y(3),e(3);
	cin>>x[0]>>y[0]>>x[1]>>y[1]>>x[2]>>y[2];
	e[0]=hypot(x[0]-x[1],y[0]-y[1]);
	e[1]=hypot(x[2]-x[1],y[2]-y[1]);
	e[2]=hypot(x[0]-x[2],y[0]-y[2]);
	double m=*max_element(all(e));
	double s=(e[0]+e[1]+e[2])/2;
	double S=sqrt(s*(s-e[0]))*sqrt((s-e[1])*(s-e[2]));
	double R=S/s;
	double l=0,r=1000;
	while(abs(r-l)>EPS){
	    double d=(r+l)/2;
	    double x=(R-d)*m/R;
	    if(x>=d*2){
	        l=d;
	    }else{
	        r=d;
	    }
	}
	fcout(12)<<l<<endl;
	return 0;
}
