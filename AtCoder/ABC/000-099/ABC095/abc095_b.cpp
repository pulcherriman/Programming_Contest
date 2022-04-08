#include <bits/stdc++.h>
using namespace std;
#define rep(i,n) for(int i=0;i<n;i++)
int main(){
  	int n,p; cin>>n>>p;
  	vector<int> m(n); 
  	rep(i,n)cin>>m[i];
  	p-=accumulate(m.begin(), m.end(),0);
  	cout<<n+p/(*min_element(m.begin(), m.end()))<<endl;
	return 0;
}
