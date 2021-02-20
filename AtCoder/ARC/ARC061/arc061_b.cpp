 
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
    ll h,w,n;
    cin>>h>>w>>n;
    map<pair<ll,ll>,int> m;
    rep(i,n){
        int y,x;cin>>y>>x;
        range(j,0,3)range(k,0,3){
            if(3<=y+j&&y+j<=h&&3<=x+k&&x+k<=w){
                //cout<<y+j<<","<<x+k<<endl;
                auto p=mp(y+j,x+k);
                if(m.find(p)==m.end()){
                    m[p]=0;
                }
                m[p]++;
            }
        }
    }
    vector<ll> a(10,0);
    ll total=0;
    for(auto p:m){
        a[p.second]++;
        total++;
    }
    a[0]=(h-2)*(w-2)-total;
    for(auto i:a)cout<<i<<endl;
	return 0;
}
