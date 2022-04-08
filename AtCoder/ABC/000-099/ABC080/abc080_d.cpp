#include <bits/stdc++.h>
using namespace std;
#define rep(i,n) for(int i=0;i<n;i++)
#define all(a) a.begin(),a.end()

int main(){
	int n,c;
	cin>>n>>c;
	vector<valarray<int>> tm(c+1,valarray<int>(0,100001));
	rep(i,n){
		int s,t,cc; cin>>s>>t>>cc;
		tm[cc][s-1]++;  tm[cc][t]--;
	}
	for(auto&p:tm){
		partial_sum(begin(p),end(p),begin(p));
		p=p.apply([](int x){return x?1:0;});
	}
	cout<<accumulate(all(tm),tm[0]).max()<<endl;

	return 0;
}
