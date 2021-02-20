#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using vi=vector<ll>;
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
	
	ll n;
	cin>>n;
	if(n==1){
	    cout<<"Yes"<<endl;
	    cout<<2<<endl;
	    cout<<"1 1"<<endl;
	    cout<<"1 1"<<endl;
	    return 0;
	}
	if(n==2){
	    cout<<"No"<<endl;
	    return 0;
	}
	ll d=floor(sqrt(n*2))+1;
	if(d*d-d!=n*2){
	    cout<<"No"<<endl;
	    return 0;
	}
	vvi ans(d);
	int p=0,q=1;
	rep(i,n){
	    ans[p].push_back(i+1);
	    ans[q].push_back(i+1);
	    if(++q==d){
	        q=++p+1;
	    }
	}
    cout<<"Yes"<<endl;
    cout<<d<<endl;
    rep(i,d){
        cout<<ans[i].size()<<" "<<ans[i]<<endl;
    }
	return 0;
}
