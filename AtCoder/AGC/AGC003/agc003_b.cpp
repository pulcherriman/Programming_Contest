#include <bits/stdc++.h>
#define rep(i,n) range(i,0,n)
#define range(i,a,n) for(int i=a;i<(n);i++)
#define all(a) a.begin(),a.end()
using namespace std;
using ll=long long;
using vi=vector<int>;
using vvi=vector<vi>;

int main(){
    int n;
    ll ans=0,sum=0;
    cin>>n;
    rep(i,n){
        ll t; cin>>t;
        sum+=t;
        if(t==0 or i+1==n){
            ans+=sum/2;
            sum=0;
        }
    }
    cout<<ans<<endl;
}