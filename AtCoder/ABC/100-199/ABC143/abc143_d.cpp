#include "bits/stdc++.h"
using namespace std;
#define rep(i,n) for(int i=0;i<n;i++)
#define all(a) a.begin(),a.end()
int main(){
  int n;
  cin>>n;
  vector<int> a(n);
  rep(i,n)cin>>a[i];
  sort(all(a));
  int ans=0;
  rep(i,n)rep(j,n)if(i<j){
    int u=lower_bound(all(a),a[j]+a[i])-a.begin();
    
    ans+=max(u-1-j,0);
    
  }
  cout<<ans<<endl;
}