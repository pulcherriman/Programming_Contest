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
/*
 * 自明
 */

constexpr ll gcd(ll a,ll b){return b?gcd(b,a%b):a;}
constexpr ll lcm(ll a,ll b){return a*b/gcd(a,b);}

int main(){
	cin.tie(0);
   	ios::sync_with_stdio(false);
	
	ll n,k;
	cin>>n>>k;
	if(k%2==1){
	    ll p=0;
	    for(int i=k;i<=n;i+=k)p++;
	    cout<<p*p*p<<endl;
	}else{
	    ll p=0,q=0;
	    for(int i=k;i<=n;i+=k)p++;
	    for(int i=k/2;i<=n;i+=k)q++;
	    cout<<p*p*p+q*q*q<<endl;
	}
	
}
