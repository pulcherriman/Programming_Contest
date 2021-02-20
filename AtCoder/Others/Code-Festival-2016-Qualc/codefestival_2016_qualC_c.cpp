 
#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using vi=vector<int>;
using vvi=vector<vi>;
using vs=vector<string>;
using msi=map<string,int>;
using mii=map<int,int>;
using psi=pair<string,int>;
using pii=pair<int,int>;
using vlai=valarray<int>;
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
#define MOD ((ll)1e9+7)
void get(){}template<class H,class...T>void get(H&h,T&...t){cin>>h;get(t...);}
template<class T>void geti(T&a){for(auto&_:a)cin>>_;}
template<class T>void getii(T&a){for(auto&_:a)geti(_);}
void put(string d){}template<class H,class...T>void put(string d,H&h,T&...t){cout<<h;if(sizeof...(t))cout<<d;put(d,t...);}
template<class T>void puti(T&a,string d=" "){bool f=1;for(auto&_:a)cout<<(exchange(f,0)?"":d)<<_;cout<<endl;}
template<class T>void putii(T&a,string d=" "){for(auto&_:a)puti(_,d);}
#define dcl(...) ll __VA_ARGS__;get(__VA_ARGS__)
#define dclt(t,...) t __VA_ARGS__;get(__VA_ARGS__)
template<class F,class S>void add(map<F,S>&mp,F f,S s){if(mp.find(f)==mp.end())mp[f]=F();mp[f]+=s;}
 
constexpr int gcd(int a,int b){return b?gcd(b,a%b):a;}
constexpr int lcm(int a,int b){return a*b/gcd(a,b);}


int main(){
    dcl(n);
    vector<vector<ll>> h(2,vector<ll>(n,0ll));
    getii(h);
    auto p=h;
    for(int i=n-1;i>0;i--){
        if(h[0][i]==h[0][i-1]){
            h[0][i]=0;
        }
    }
    for(int i=1;i<n;i++){
        if(h[1][i-1]==h[1][i]){
            h[1][i-1]=0;
        }
    }
    if(p[0].back()!=p[1].front()){
        cout<<0<<endl;
        return 0;
    }
    ll ans=1;
    rep(i,n){
        if(h[0][i]!=h[1][i] && h[0][i] && h[1][i]){
            cout<<0<<endl;
            return 0;
        }else if(h[0][i]==0 && h[1][i] && p[0][i]<p[1][i]){
            cout<<0<<endl;
            return 0;
        }else if(h[1][i]==0 && h[0][i] && p[1][i]<p[0][i]){
            cout<<0<<endl;
            return 0;
        }
        ll odd=1;
        if(h[0][i]==0 && h[1][i]==0){
            odd=min(p[0][i],p[1][i]);
        }
        ans=ans*odd%MOD;
    }
    cout<<ans<<endl;
    
}
