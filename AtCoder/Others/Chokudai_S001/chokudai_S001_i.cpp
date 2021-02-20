#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define in(n) cin>>n
#define REP(sfx,n) for(auto sfx=0;sfx<n;sfx++)
#define FOR(sfx,arr) for(auto &sfx:arr)
#define ITR(arr) (arr.begin()),(arr.end())

int main(){
	int n,ans=0,d=0,st=0;
	in(n);
	vector<int> a(n);
	FOR(i,a) {
    	in(i);
    }
    REP(i,a.size()){
        d+=a[i];
        while(d>n){
            d-=a[st++];
        }
        if(d==n)
            ans++;
    }
    cout<<ans;
}