 
#include <bits/stdc++.h>
using namespace std;
using vi=vector<int>;
using vvi=vector<vi>;
using vs=vector<string>;
using msi=map<string,int>;
using mii=map<int,int>;
using pii=pair<int,int>;
using vlai=valarray<int>;
using ll=long long;
#define rep(i,n) for(int i=0;i<n;i++)
#define range(i,s,n) for(int i=s;i<n;i++)
#define all(a) a.begin(),a.end()
#define rall(a) a.rbegin(),a.rend()
#define fs first
#define sc second
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define INF 1e9
#define EPS 1e-9
#define MOD (1e9+7)
void bulk(){}template<class H,class...T>void bulk(H&h,T&...t){cin>>h;bulk(t...);}
#define get(...) int __VA_ARGS__; bulk(__VA_ARGS__);


int main(){
    get(n);
	vvi p(2,vi(n+1,0));
	rep(i,n)cin>>p[0][i+1];
	rep(i,n)cin>>p[1][i+1];
	partial_sum(all(p[0]),p[0].begin());
	partial_sum(all(p[1]),p[1].begin());
	int ans=-1;
	rep(i,n){
	    ans=max(ans,p[0][i+1]-p[0][0]+p[1][n]-p[1][i]);
	}
	cout<<ans<<endl;
	return 0;
}
