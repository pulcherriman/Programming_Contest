 
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

int main(){
    string s,cs;
    cin>>s;
    
    int ans=1000;
    for(auto c:"qwertyuiopasdfghjklzxcvbnm"s){
        cs=s;
        int m=0;
        while(cs.size() && count(all(cs),c)!=cs.length()){
            m++;
            rep(i,cs.size()-1){
                if(cs[i]==c || cs[i+1]==c){
                    cs[i]=c;
                }
            }
            cs=cs.substr(0,cs.size()-1);
            // cout<<cs<<endl;
            // cout<<count(all(cs),c)<<","<<cs.length()<<endl;
        }
        ans=min(ans,m);
    }
    cout<<ans<<endl;
}
