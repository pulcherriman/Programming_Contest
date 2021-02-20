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
	int n; cin>>n;
	vvi aList(n+1);
	rep(i,n-1){
		int a,b; cin>>a>>b;
		aList[a].push_back(b);
		aList[b].push_back(a);
	}
	vvi ans(2,vi(n+1,-1));
	rep(p,2){
		queue<int> q;
		q.push(p?n:1);
		ans[p][p?n:1]=0;
		while(!q.empty()){
			int t=q.front(); q.pop();
			for(auto adj:aList[t]){
				if(ans[p][adj]==-1){
					ans[p][adj]=ans[p][t]+1;
					q.push(adj);
				}
			}
		}
	}
	int res=0;
	rep(i,n) if(ans[0][i+1]<=ans[1][i+1]) res++;
	if(res>n-res)cout<<"Fennec"<<endl;
	else cout<<"Snuke"<<endl;
	return 0;
}
