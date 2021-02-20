#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define in(n) cin>>n
#define REP(sfx,n) for(sfx=0;sfx<n;sfx++)
#define FOR(sfx,arr) for(auto &sfx:arr)
#define ITR(arr) (arr.begin()),(arr.end())

int main(){
	ull n,ans=0;
	in(n);
	vector<ll> a(n);
	FOR(i,a) {
    	in(i);
        ans=ans*pow(10,((int)log10(i)+1))+i;
        ans%=1000000007;
    }
    cout<<ans;
}