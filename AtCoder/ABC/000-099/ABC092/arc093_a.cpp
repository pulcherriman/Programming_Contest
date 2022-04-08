#include <bits/stdc++.h>
using namespace std;
int main(void){
    int n;
    cin>>n;
    vector<int> a(n+2,0),d(n+2,0);
    for(int i=0;i<n;i++){
        cin>>a[i+1];
        d[i+1]=abs(a[i+1]-a[i]);
    }
    d[n+1]=abs(a[n]);
    partial_sum(d.begin(),d.end(),d.begin());
    for(int i=1;i<=n;i++){
        cout<<d[i-1]+d[n+1]-d[i+1]+abs(a[i-1]-a[i+1])<<endl;
    }
}
