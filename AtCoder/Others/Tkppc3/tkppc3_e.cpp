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
 * Eratosthenes erat(100);  //100までの数の素数判定をする。O(nlogn)
 * erat.isPrime[100]        //添え字の数が素数かどうかbool値で得る。O(1)
 * erat.primeArray()        //2~nまでの素数列を得る。 O(n)
 */


int main(){
	cin.tie(0);
   	ios::sync_with_stdio(false);
   	
	int n;
	cin>>n;
	
	vd p(n,1.0/n);
   	range(i,1,n) p[i]=p[i-1]*(n-i)/n;
   	
	double ans=0;
    range(d,1,n+1){
        ans+=p[d-1]*d*d*(n+1)/2;
    }
    fcout(14)<<ans<<endl;
	return 0;
	
}
