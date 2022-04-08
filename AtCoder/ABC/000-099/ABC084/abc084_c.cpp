#include <bits/stdc++.h>
using namespace std;

int main(){
	int n;
	cin>>n;
	vector<int> c(n,0),s(n,0),f(n,0);
	for(int i=0;i<n-1;i++){
		cin>>c[i]>>s[i]>>f[i];
	}
	for(int st=0;st<n;st++){
		int t=0;
		for(int cur=st;cur<n-1;cur++){
			t=s[cur]+ max(0,f[cur]* (int)ceil((double)(t-s[cur])/f[cur]))+c[cur];
		}
		cout<<t<<endl;
	}
	return 0;
}
