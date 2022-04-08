 
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
	int h,w,d; cin>>h>>w>>d;
	vector<pii> a(h*w+1);
	rep(i,h)rep(j,w){
		int t; cin>>t;
		a[t]={i,j};
	}
	vvi ps(d);
	ps[0].push_back(0);
	range(i,1,h*w+1){
		auto md=a[i];
		if(i>d) md.first-=a[i-d].first, md.second-=a[i-d].second;
		ps[i%d].push_back(abs(md.first)+abs(md.second));
	}
	for(auto&l:ps) partial_sum(all(l),l.begin());
	int m; cin>>m;
	rep(i,m){
		int l,r; cin>>l>>r;
		//for(auto i:ps[r%d])cout<<i<<",";cout<<endl;
		cout<<ps[r%d][r/d]-ps[r%d][l/d]<<endl;
	}
	return 0;
}
