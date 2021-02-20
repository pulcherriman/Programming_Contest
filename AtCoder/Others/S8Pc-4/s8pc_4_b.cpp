 
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
	int n,k;
	cin>>n>>k;
	vi h(n);
	for(auto&i:h)cin>>i;
	ll res=1000000000000ll;
	rep(i,1<<n){
		if(__builtin_popcount(i)!=k) continue;
		vi s;
		rep(j,n) if((1<<j)&i)s.push_back(j);
		ll ans=0, t=(s[0]==0?0:*max_element(h.begin(),h.begin()+s[0]));
		rep(j,k){
			if(t>=h[s[j]]){
				t++;
				ans+=t-h[s[j]];
			}else t=h[s[j]];
			if(j+1!=k and s[j]+1!=s[j+1]){
				int m=*max_element(h.begin()+s[j]+1, h.begin()+s[j+1]);
				if(t<m){
					ans+=m-t;
					t=m;
				}
			}
		}
		res=min(res,ans);
	}
	cout<<res<<endl;
	return 0;
}
