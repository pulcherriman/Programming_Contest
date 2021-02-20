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
	vi a(n);
	vi b(5,0);
	int ans=0;
	rep(i,n){
	    cin>>a[i];
	    b[a[i]]++;
	}
	ans+=b[4];
	ans+=b[2]/2;
	b[2]%=2;
	ans+=b[3];
    b[1]-=b[3];
	if(b[2]){
	    ans++;
	    b[1]-=2;
	}
	if(b[1]>0){
	    ans+=b[1]/4;
	    b[1]%=4;
	    if(b[1])ans++;
	}
	cout<<ans<<endl;
	return 0;
}
