 
#include <bits/stdc++.h>
using namespace std;
using vi=vector<int>;
using vvi=vector<vi>;
using vs=vector<string>;
using msi=map<string,int>;
using mii=map<int,int>;
using pii=pair<int,int>;
using vlai=valarray<int>;
using ll=long long;
#define rep(i,n) for(int i=0;i<n;i++)
#define range(i,s,n) for(int i=s;i<n;i++)
#define all(a) a.begin(),a.end()
#define rall(a) a.rbegin(),a.rend()
#define fs first
#define sc second
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define INF 1e9
#define EPS 1e-9

int main(){
    ll n,ans=0;
    cin>>n;
    vector<ll> a(n),b(n);
    rep(i,n) cin>>a[n-1-i]>>b[n-1-i];
    rep(i,n) {
        ll tmp=b[i]-(a[i]+ans)%b[i];
        if(tmp==b[i])tmp=0;
        ans+=tmp;
    }
    cout<<ans;
	return 0;
}
