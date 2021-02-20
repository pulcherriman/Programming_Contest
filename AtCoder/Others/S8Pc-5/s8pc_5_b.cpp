#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using vi=vector<int>;
using vvi=vector<vi>;
using pii=pair<int,int>;
#define range(i,a,n) for(int i=a;i<n;i++)
#define rep(i,n) for(int i=0;i<n;i++)
#define all(a) a.begin(),a.end()
#define INF (int)(1e9)

int main(){
    int n,m;
    cin>>n>>m;
    using data=tuple<int,int,int>;
    vector<data> p(n+m);
    rep(i,n){int a,b,c;cin>>a>>b>>c; p[i]=make_tuple(a,b,c);}
    rep(i,m){int a,b;cin>>a>>b; p[i+n]=make_tuple(a,b,-1);}
    double ans=1e9;
    rep(i,n+m)range(j,i+1,n+m){
        int a1,a2,a3,b1,b2,b3;
        tie(a1,a2,a3)=p[i];
        tie(b1,b2,b3)=p[j];
        switch((a3>0)*2+(b3>0)){
            case 0: ans=min(ans, hypot(a1-b1,a2-b2)/2); break;
            case 1: ans=min(ans, fmin(b3,hypot(a1-b1,a2-b2)-b3)); break;
            case 2: ans=min(ans, fmin(a3,hypot(a1-b1,a2-b2)-a3)); break;
            case 3: ans=min(ans, fmin(a3,b3)); break;
        }
    }
    cout.precision(10);
    cout<<fixed<<ans<<endl;
}