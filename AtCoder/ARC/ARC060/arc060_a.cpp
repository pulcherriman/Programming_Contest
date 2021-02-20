
#include <bits/stdc++.h>
using namespace std;
using vi=vector<int>;
using vvi=vector<vi>;
using vs=vector<string>;
using msi=map<string,int>;
using mii=map<int,int>;
//using pii=pair<int,int>;
using vlai=valarray<int>;
using ll=long long;
using pii=pair<ll,ll>;
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
#define MOD (1e9+7)
void get(){}template<class H,class...T>void get(H&h,T&...t){cin>>h;get(t...);}
#define dcl(...) ll __VA_ARGS__;get(__VA_ARGS__);
 
int main(){
    dcl(n,a);

    vector<vector<vector<ll>>> dp(n+1,vector<vector<ll>>(51,vector<ll>(2501,0)));
    dp[0][0][0]=1;
    
    ll ans=-1;
    
    rep(i,n){
        dcl(x);
        rep(j,51){
            rep(k,2501){
                if(dp[i][j][k]){
                    dp[i+1][j][k]+=dp[i][j][k];
                    dp[i+1][j+1][k+x]+=dp[i][j][k];
                }
            }
        }
    }
    rep(j,51)rep(k,2501){
        if(j*a==k){
            ans+=dp[n][j][k];
        }
    }
    cout<<ans<<endl;
    
}