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
	
	char c,cb;
	int n6=0,n11=0,i=0;
	while(cin>>c){
	    int p=c-'0';
	    n6+=p;
	    if(i%2==0)n11+=p; else n11-=p;
	    i++;
	    cb=c;
	}
    cout<<((cb-'0')%2==0 and n6%3==0 ? "yES" : "nO" )<<endl; 
    cout<<(abs(n11)%11==0 ? "yES" : "nO" )<<endl; 
	
	return 0;
}
