#include<bits/stdc++.h>
using namespace std;

using ll=long long;
using vl=vector<ll>;
#define rep(i,n) for(int i=0;i<((int)n);++i)
#define range(i,a,n) 

int main(){
	int n,m; cin>>n>>m;

	vl edge(n);
	rep(i,n)edge[i]=1ll<<i;

	rep(i,m){
		int a,b; cin>>a>>b;
		edge[a]|=(1ll<<b);
		edge[b]|=(1ll<<a);
	}

	int maxcnt=0;
	vl ans;
	rep(i,n)rep(j,i)rep(k,j){
		int cnt=__builtin_popcountll(edge[i] | edge[j] | edge[k]);
		if(maxcnt<cnt){
			maxcnt=cnt;
			ans={k, j, i};
		}
	}
	cout<<ans[0]<<" "<<ans[1]<<" "<<ans[2]<<endl;
	

}