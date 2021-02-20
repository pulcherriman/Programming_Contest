 
#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using vi=vector<int>;
using vvi=vector<vi>;
using pii=pair<int,int>;
#define rep(i,n) for(int i=0;i<n;i++)
#define range(i,a,n) for(int i=a;i<n;i++)
#define all(a) a.begin(),a.end()
#define rall(a) a.rbegin(),a.rend()
#define INF 1e9
#define EPS 1e-9
#define MOD (1e9+7)
void put(string d){}template<class H,class...T>void put(string d,H&h,T&...t){cout<<h;if(sizeof...(t))cout<<d;put(d,t...);}
template<class T>void puti(T&a,string d=" "){bool f=1;for(auto&_:a)cout<<(exchange(f,0)?"":d)<<_;cout<<endl;}
template<class T>void putii(T&a,string d=" "){for(auto&_:a)puti(_,d);}

int main(){
	ll n,a,b; cin>>n>>a>>b;
	vi h(n);
	for(auto&i:h)cin>>i;
	
	ll l=0,r=1000000001;
	while(r-l>1){
		int m=(l+r)/2, t=m;
		auto cp=h;
		rep(i,n){
			if(cp[i]>b*m){
				cp[i]-=b*m;
				t-=ceil(cp[i]/(double)(a-b));
			}
		}
		(t>=0?r:l)=m; 
	}
	cout<<r<<endl;
	return 0;
}
