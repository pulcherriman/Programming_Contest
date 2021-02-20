 
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
    int w,h,n;cin>>w>>h>>n;
    int lim[4]={0,w,0,h};
    rep(i,n){
        int x,y,a;cin>>x>>y>>a;
        if(a%2){lim[a-1]=max(lim[a-1],a<3?x:y);}
        else {lim[a-1]=min(lim[a-1],a<3?x:y);}
    }
    cout<<(max(lim[1]-lim[0],0)*max(lim[3]-lim[2],0))<<endl;
    return 0;
}
