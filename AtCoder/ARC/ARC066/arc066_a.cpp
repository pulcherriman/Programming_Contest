 
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

 
constexpr int gcd(int a,int b){return b?gcd(b,a%b):a;}
constexpr int lcm(int a,int b){return a*b/gcd(a,b);}


int main(){
    dcl(n);
    vi a(n);
    geti(a);
    sort(all(a));

    bool ok;
    if(n%2){
        ok=a[0]==0;
        for(int i=1;i<n;i+=2){
            ok&=(a[i]==a[i+1]&&a[i]==i+1);
        }
    }else{
        ok=a[0]==1;
        for(int i=0;i<n;i+=2){
//            cout<<a[i]<<","<<a[i+1]<<","<<i+1<<endl;
            ok&=(a[i]==a[i+1]&&a[i]==i+1);
        }
    }
    if(ok){
        ll ans=1;
        rep(i,(a.back()+1)/2){
            ans=ans*2%MOD;
        }
        cout<<ans<<endl;
    }else{
        cout<<0<<endl;
    }
}
