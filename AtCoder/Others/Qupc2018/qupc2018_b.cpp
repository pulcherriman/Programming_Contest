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
	
	int n;
	cin>>n;
	rep(_,n){
	    ll a,b,c,t;
	    cin>>a>>b>>c;
	    bool ok=true;
	    t=a*100+b*10+c;
	    if(t%2)ok=false;
	    t/=2;
	    if(t/100<=a){
	        t%=100;
	    }else{
	        t-=a*100;
	    }
	    if(t/10<=b){
	        t%=10;
	    }else{
	        t-=b*10;
	    }
	    if(t>c)ok=false;
	    cout<<(ok?"Yes":"No")<<endl;
	}
	return 0;
}
