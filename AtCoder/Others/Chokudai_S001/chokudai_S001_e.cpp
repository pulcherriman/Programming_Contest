#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define in(n) cin>>n
#define REP(sfx,n) for(sfx=0;sfx<n;sfx++)
#define FOR(sfx,arr) for(auto &sfx:arr)
#define ITR(arr) (arr.begin()),(arr.end())

int main(){
	int n,ans=0;
	in(n);
	vector<int> a(n);
	FOR(i,a) {
	    ans++;
    	in(i);
        if(i==1){
        	cout<<ans;
            break;
        }
    }
}