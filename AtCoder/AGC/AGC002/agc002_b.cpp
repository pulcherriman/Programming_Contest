#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using vi=vector<int>;
using vvi=vector<vi>;
using pii=pair<int,int>;
#define rep(i,n) for(int i=0;i<n;i++)
#define all(a) a.begin(),a.end()
#define INF (int)(1e9)

int main(){
    int n,m; cin>>n>>m;
    vi ball(n,1),exist(n,0); exist[0]=1; 
    rep(i,m){
        int p,q; cin>>p>>q; p--; q--;
        ball[p]--; ball[q]++;
        if(exist[p]==1){
            if(ball[p]==0) exist[p]=0;
            exist[q]=1;
        }
    }
    cout<<accumulate(all(exist),0)<<endl;
}