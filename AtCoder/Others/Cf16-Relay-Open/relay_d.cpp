 
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
    int v[3][3];
    cin>>v[0][0]>>v[0][1]>>v[1][1];
    range(i,0,101){
        int t=v[0][0]+v[0][1]+i;
        v[0][2]=i;
        v[2][2]=t-v[0][0]-v[1][1];
        v[1][2]=t-v[0][2]-v[2][2];
        v[2][1]=t-v[0][1]-v[1][1];
        v[1][0]=t-v[1][1]-v[1][2];
        v[2][0]=t-v[2][1]-v[2][2];
        bool ans=(t==v[2][0]+v[1][1]+v[0][2] && t==v[0][0]+v[1][0]+v[2][0]);
        if(ans){
            rep(j,3)rep(k,3){cout<<v[j][k];if(k==2)cout<<endl;else cout<<" ";}
            return 0;
        }
    }
    return 0;
}
