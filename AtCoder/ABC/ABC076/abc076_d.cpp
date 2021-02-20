#include <bits/stdc++.h>
using namespace std;
using vi=vector<int>;
#define INF 1e9
#define rep(i,n) for(int i=0;i<n;i++)
#define range(i,a,n) for(int i=a;i<n;i++)
#define all(a) a.begin(),a.end()

int main(){
	int n;
	cin>>n;
	vi t(n+1,0), v(n+1,0);
	range(i,1,n+1){cin>>t[i]; t[i]*=2;}
	range(i,1,n+1){cin>>v[i]; v[i]*=2;}
	partial_sum(all(t),t.begin());
	vi m(t[n]+1,INF);
	rep(i,t[n]+1) m[i]=min(m[i],i);
	rep(i,t[n]+1) m[i]=min(m[i],t[n]-i);
	range(i,1,n+1){
		range(j,0,t[i-1]) m[j]=min(m[j],v[i]+t[i-1]-j);
		range(j,t[i-1],t[i]+1) m[j]=min(m[j],v[i]);
		range(j,t[i],t[n]+1) m[j]=min(m[j],v[i]+j-t[i]);
	}
	cout.precision(12);
	cout<<fixed<<accumulate(all(m),0)/4.0<<endl;
	return 0;
}
