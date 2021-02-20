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
#define rrep(i,n) for(ll i=(n)-1;i>=0;i--)
#define range(i,a,n) for(ll i=(a);i<n;i++)
#define LINF ((ll)1ll<<60)
#define fcout(a) cout<<setprecision(a)<<fixed
#define fs first
#define sc second

template<class T> bool chmin(T&a, T b){if(a>b){a=b; return true;} return false;}


int main(){
    cin.tie(0);
    int n;
    cin>>n;
    vl a(n),l(n),r(n);
    rep(i,n)cin>>a[i];
    ll cnt=0, ans=0;
    rep(i,n){
        cnt--;
        if(a[i]<0){
            chmin(cnt,-a[i]);
        }else if(a[i]==0){
            cnt=LINF;
        }
        l[i]=cnt;
    }
    cnt=0;
    rrep(i,n){
        cnt--;
        if(a[i]<0){
            chmin(cnt,-a[i]);
        }else if(a[i]==0){
            cnt=LINF;
        }
        r[i]=cnt;
    }
    rep(i,n){
        if(a[i]>0){
            ans+=min(a[i],max(max(l[i],r[i]),0ll));
        }
    }
    // rep(i,n)cout<<l[i]<<",";cout<<endl;
    // rep(i,n)cout<<r[i]<<",";cout<<endl;
    cout<<ans<<endl;
}