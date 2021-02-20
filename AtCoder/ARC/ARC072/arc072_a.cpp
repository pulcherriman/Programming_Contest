 
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

bool sign(ll a){
    return a>=0;
}

int main(){
    ll ans=0,ans2=0;
    dcl(n);
    vector<ll> in(n+1,0ll);
    range(i,1,n+1){
        cin>>in[i];
    }
    auto a=in,b=in;
    if(a[1]==0){
        ans++;
        a[1]=1;
    }
    partial_sum(all(a),a.begin());
    ll d=0;
    range(i,2,n+1){
        a[i]+=d;
        if(a[i]==0){
            ans++;
            a[i]=sign(a[i-1])?-1:1;
            d+=sign(a[i-1])?-1:1;
        }else if(sign(a[i])==sign(a[i-1])){
            ans+=abs(a[i])+1;
            d+=a[i]*-1+(sign(a[i])?-1:1);
            if(sign(a[i])){
                a[i]=-1;
            }else{
                a[i]=1;
            }
        }
        //cout<<a[i]<<"("<<d<<"), ";
    }

    if(b[1]==0){
        ans2++;
        b[1]=-1;
    }else{
        ans2=abs(b[1])+1;
        b[1]=(sign(b[1])?-1:1);
    }
    partial_sum(all(b),a.begin());
    d=0;
    range(i,2,n+1){
        a[i]+=d;
        if(a[i]==0){
            ans2++;
            a[i]=sign(a[i-1])?-1:1;
            d+=sign(a[i-1])?-1:1;
        }else if(sign(a[i])==sign(a[i-1])){
            ans2+=abs(a[i])+1;
            d+=a[i]*-1+(sign(a[i])?-1:1);
            if(sign(a[i])){
                a[i]=-1;
            }else{
                a[i]=1;
            }
        }
        //cout<<a[i]<<"("<<d<<"), ";
    }
    cout<<min(ans,ans2)<<endl;
}
