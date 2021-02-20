#include <bits/stdc++.h>
using namespace std;
using vi=vector<int>;
using vvi=vector<vi>;
using vs=vector<string>;
using msi=map<string,int>;
using pii=pair<int,int>;
using vlai=valarray<int>;
using ll=long long;
#define rep(i,n) for(int i=0;i<n;i++)
#define range(i,s,n) for(int i=s;i<n;i++)
#define all(a) a.begin(),a.end()
#define rall(a) a.rbegin(),a.rend()

int main(void){
    int n;cin>>n;
    map<int,int> v;
    rep(i,n){
        int p;cin>>p;
        if(v.find(p)==v.end())v[p]=0;
        v[p]++;
    }
    int ans=0;
    for(auto p : v){
        if(p.second>p.first){
            ans+=p.second-p.first;
        }
        if(p.second<p.first){
            ans+=p.second;
        }
    }
    cout<<ans;
}
