#include <bits/stdc++.h>
#include <cxxabi.h>
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
#define MOD (1e9+7)
void get(){}template<class H,class...T>void get(H&h,T&...t){cin>>h;get(t...);}
template<class T>void geti(T&a){for(auto&_:a)cin>>_;}
template<class T>void getii(T&a){for(auto&_:a)geti(_);}
void put(string d){cout<<endl;}template<class H,class...T>void put(string d,H&&h,T&&...t){cout<<h;if(sizeof...(t))cout<<d;put(d,t...);}
template<class T>void puti(T&a,string d=" "){bool f=1;for(auto&_:a)cout<<(exchange(f,0)?"":d)<<_;cout<<endl;}
template<class T>void putii(T&a,string d=" "){for(auto&_:a)puti(_,d);}
#define dcl(...) ll __VA_ARGS__;get(__VA_ARGS__)
#define dclt(t,...) t __VA_ARGS__;get(__VA_ARGS__)

template<class T>string bitstr(T x){return typeid(T)==typeid(int)?bitset<32>(x).to_string('_','#'):bitset<64>(x).to_string();}
template<class T>int bitcnt(T x){return typeid(T)==typeid(int)?__builtin_popcount(x):__builtin_popcountll(x);}
template<class T>int bitdig(T x){return x?typeid(T)==typeid(int)?32-__builtin_clz(x):64-__builtin_clzll(x):0;}
template<class T>int bitpow(T x){return x?typeid(T)==typeid(int)?__builtin_ctz(x):__builtin_ctzll(x):0;}


int main(){
    vvi c(3,vi(3));
    getii(c);
    rep(i,3){
        int mn=*min_element(all(c[i]));
        rep(j,3){
            c[i][j]-=mn;
        }
    }
    if(c[0]==c[1] && c[1]==c[2]) cout<<"Yes"<<endl; else cout<<"No"<<endl;
}

