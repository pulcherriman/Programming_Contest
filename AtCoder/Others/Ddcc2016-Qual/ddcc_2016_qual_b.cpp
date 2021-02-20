 
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
#define dcl(...) double __VA_ARGS__;get(__VA_ARGS__);


int main(){
    dcl(r,n,m);
    double ans=0;
    vector<double> l(n+2*m,0);
    rep(i,n+1){
        double h=(n-i*2)/n;
        l[i+m]=2*r*sqrt(1-h*h);
    }
    //for(auto i:l)cout<<i<<endl;
    rep(i,n+m+1){
        //cout<<i<<","<<i+m<<endl;
        ans+=max(l[i+m],l[i]);
    }
    cout<<fixed<<setprecision(16)<<ans<<endl;
    
}
