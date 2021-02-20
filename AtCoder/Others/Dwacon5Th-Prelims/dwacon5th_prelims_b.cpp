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
	
	int n,k;
	cin>>n>>k;
	vl a(n),b(n+1,0);
	rep(i,n){cin>>a[i];b[i+1]=a[i];}
	partial_sum(all(b),b.begin());
	vl s;
	rep(i,n+1)rep(j,i){
	    s.push_back(b[i]-b[j]);
	}
	sort(all(s));
	ll ans=0;
    for(int i=41;i>=0;i--){
        ll m=1ll<<i;
        vl s2;
        for(auto&d:s){
            if(d&m){
                s2.push_back(d);
            }
        }
        if(s2.size()>=k){
            s=s2;
            ans|=m;
        }
    }
    cout<<ans<<endl;
	return 0;
}
