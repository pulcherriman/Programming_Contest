#include <bits/stdc++.h>
using namespace std;
#define rep(i,n) for(int i=0;i<n;i++)
int main(void){
    int h,w,ans=0;
    cin>>h>>w;
    vector<vector<int>> cost(10,vector<int>(10,0));
    vector<int> wall(10,0);

    rep(i,10)rep(j,10)cin>>cost[i][j];
    rep(i,h*w){
        int n; cin>>n;
        if(n!=-1) wall[n]++;
    }

    rep(i,10)rep(j,10)rep(k,10)
        if(cost[j][k]>cost[j][i]+cost[i][k])
            cost[j][k]=cost[j][i]+cost[i][k];
    
    rep(i,10)ans+=cost[i][1]*wall[i];
    cout<<ans;
    
}
