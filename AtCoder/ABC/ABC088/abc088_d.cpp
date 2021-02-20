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
    dcl(h,w);
    vvi s(h+2,vi(w+2,-1));
    rep(i,h)rep(j,w){
        dclt(char,c);
        s[i+1][j+1]=(c=='#'?-1:0);
    }
    s[1][1]=1;
    
    queue<pii> q;
    q.emplace(1,1);
    while(!q.empty()){
        pii cur=q.front();
        q.pop();
        int v[]={-1,0,1,0,-1};
        rep(i,4){
            if(s[cur.fs+v[i]][cur.sc+v[i+1]]==0){
                s[cur.fs+v[i]][cur.sc+v[i+1]]=s[cur.fs][cur.sc]+1;
                q.emplace(cur.fs+v[i],cur.sc+v[i+1]);
            }
        }
    }
    if(s[h][w]==0){
        cout<<-1<<endl;
        return 0;
    }
    q.emplace(h,w);
    while(!q.empty()){
        pii cur=q.front();
        q.pop();
        int v[]={-1,0,1,0,-1};
        rep(i,4){
            if(s[cur.fs+v[i]][cur.sc+v[i+1]]==s[cur.fs][cur.sc]-1){
                s[cur.fs][cur.sc]=-1;
                q.emplace(cur.fs+v[i],cur.sc+v[i+1]);
                break;
            }
        }
    }
    s[1][1]=-1;
    int ans=0;
    rep(i,h+2)rep(j,w+2)if(s[i][j]>=0)ans++;
    cout<<ans<<endl;

}

