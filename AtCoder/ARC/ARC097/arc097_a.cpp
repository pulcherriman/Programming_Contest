#include <bits/stdc++.h>
#define rep(i,n) range(i,0,n)
#define range(i,a,n) for(int i=a;i<(n);i++)
using namespace std;

int main(){
    int k;
	string s; cin>>s>>k;
	vector<set<int>> a(26);
	rep(i,s.size()) a[s[i]-'a'].insert(i);

	set<string> ans;
	rep(p,26){
	    range(l,1,k+1){
    	    for(auto i:a[p]) if(i+l<=s.size()) ans.insert(s.substr(i,l));
	    }
	    if(ans.size()>=k) break;
	}
	auto itr=ans.begin();
	rep(i,k-1)itr++;
    cout<<*itr<<endl;
	return 0;
}
