#include <bits/stdc++.h>
using namespace std;

using ll=long long;
using ld=long double;
using vl=vector<ll>;
using vvl=vector<vl>;
using vs=vector<string>;
using vb=vector<bool>;
using vvb=vector<vb>;
using pll=pair<ll,ll>;

#define all(a) a.begin(),a.end()
#define rep(i,n) range(i,0,n)
#define range(i,a,n) for(ll i=(a);i<n;i++)
#define LINF ((ll)1ll<<60)
#define fcout(a) cout<<setprecision(a)<<fixed
#define fs first
#define sc second

template<class T> bool chmin(T&a, T b){if(a<b){a=b; return true;} return false;}


int main(){
    cin.tie(0);
    // ios:sync_with_stdio(false);
    ll n,W,H;
    cin>>n>>W>>H;
    vl y(H+1,0),x(W+1,0);
    rep(i,n){
        ll a,b,w;
        cin>>a>>b>>w;
        y[max(b-w,0ll)]+=1;
        y[min(b+w,H)]-=1;
        x[max(a-w,0ll)]+=1;
        x[min(a+w,W)]-=1;
    }
    bool ok=true,ok2=true;
    partial_sum(all(y),y.begin());
    partial_sum(all(x),x.begin());
    rep(i,H)if(y[i]<=0)ok=false;
    rep(i,W)if(x[i]<=0)ok2=false;
    cout<<((ok||ok2)?"Yes":"No")<<endl;
}