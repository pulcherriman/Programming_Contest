#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define in(n) cin>>n
#define REP(sfx,n) for(sfx=0;sfx<n;sfx++)
#define FOR(sfx,arr) for(auto &sfx:arr)
#define ITR(arr) (arr.begin()),(ar.end())

int main(){
	int n;
	in(n);
	vector<int> a(n);
	FOR(i,a) {
    	in(i);
    }
    for(int i=0;i<a.size();i++){
    	cout<<a[i];
        if(i+1!=a.size())
        	cout<<",";
    }
}