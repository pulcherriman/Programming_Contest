 
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
	int n,k;cin>>n>>k;
	vvi s(k*2+1,vi(k*2+1,0));

    rep(i,n){
        int x,y;char c;
        cin>>x>>y>>c;
        if(c=='B')x+=k;
        x%=2*k,y%=2*k;
        s[y+1][x+1]++;
    }
    rep(i,k*2+1){
        partial_sum(all(s[i]),s[i].begin());
    }
    rep(i,k*2)rep(j,k*2+1){
        s[i+1][j]+=s[i][j];
    }
    int ans=0;
    rep(i,k+1){
        int xl=i,xr=i+k;
        rep(j,k+1){
            int yl=j,yr=j+k,a=0;
            //cout<<xl<<","<<xr<<","<<yl<<","<<yr<<endl;
            a+=s[yl][xl];
            a+=s[yr][xr]+s[yl][xl]-s[yl][xr]-s[yr][xl];
            a+=s[k*2][k*2]+s[yr][xr]-s[k*2][xr]-s[yr][k*2];
            a+=s[k*2][xl]-s[yr][xl];
            a+=s[yl][k*2]-s[yl][xr];
            ans=max(ans,a);
            ans=max(ans,n-a);
        }
    }
    cout<<ans<<endl;
	return 0;
}
