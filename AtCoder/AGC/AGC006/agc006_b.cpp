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
	
	int n,x;
	cin>>n>>x;
	if(x==1 or x==2*n-1){
		cout<<"No"<<endl;
		return 0;
	}
	cout<<"Yes"<<endl;
	if(n==2){
		cout<<1<<endl;
		cout<<2<<endl;
		cout<<3<<endl;
		return 0;
	}
	if(x==2){
		rep(i,n-3){
			cout<<5+i<<endl;
		}
		cout<<3<<endl;
		cout<<2<<endl;
		cout<<1<<endl;
		cout<<4<<endl;
		rep(i,n-2){
			cout<<2*n-1-i<<endl;
		}
	}else{
		int p=1;
		rep(i,n-3){
			if(p==x-2)p=x+2;
			cout<<p<<endl;
			p++;
		}
		cout<<x-1<<endl;
		cout<<x<<endl;
		cout<<x+1<<endl;
		cout<<x-2<<endl;
		rep(i,n-2){
			if(p==x-2)p=x+2;
			cout<<p<<endl;
			p++;
		}
	}
	return 0;
}
