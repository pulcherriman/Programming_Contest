#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using vi=vector<int>;
using vvi=vector<vi>;
using pii=pair<int,int>;
#define rep(i,n) range(i,0,n)
#define range(i,a,n) for(int i=a;i<n;i++)
#define all(a) a.begin(),a.end()
#define INF ((int)1e9)
#define EPS (1e-9)
#define MOD (1000000007)
void put(string d){}template<class H,class...T>void put(string d,H&h,T&...t){cout<<h;if(sizeof...(t))cout<<d;put(d,t...);}
template<class T>void puti(T&a,string d=" "){bool f=1;for(auto&_:a)cout<<(exchange(f,0)?"":d)<<_;cout<<endl;}
template<class T>void putii(T&a,string d=" "){for(auto&_:a)puti(_,d);}
template<class S,class T>ostream& operator<<(ostream&os,pair<S,T>p){os<<"["<<p.first<<", "<<p.second<<"]";return os;};

int main(){
	cin.tie(0);
   	ios::sync_with_stdio(false);
	
	map<int,int> mp;
	int n,t;
	cin>>n;
	vi a(n),b(n),c(n);
	rep(i,n) {
		cin>>t;
		a[t-1]=t*40000+i, b[t-1]=(n-t+1)*40000;
	}
	puti(a);
	puti(b);
	
	return 0;
}
