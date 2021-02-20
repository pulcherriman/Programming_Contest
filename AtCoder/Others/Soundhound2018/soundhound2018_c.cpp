 
#include <bits/stdc++.h>
using namespace std;
using vi=vector<int>;
using vvi=vector<vi>;
using vs=vector<string>;
using msi=map<string,int>;
using mii=map<int,int>;
using pii=pair<int,int>;
using vlai=valarray<int>;
using ll=long long;
#define rep(i,n) for(int i=0;i<n;i++)
#define rrep(i,n) for(int i=n-1;i>=0;i--)
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
#define MOD 1000000007
void bulk(){}template<class H,class...T>void bulk(H&h,T&...t){cin>>h;bulk(t...);}
#define get(...) int __VA_ARGS__; bulk(__VA_ARGS__);

struct MaxFlow{
    struct edge{
        int to,cap,rev;
        edge(int t, int c, int r):to(t),cap(c),rev(r){}
    };
    vector<vector<edge>> g;
    vector<bool> used;
    MaxFlow(int n){
        g=vector<vector<edge>>(n);
        used=vector<bool>(n);
    }
    void add(int from, int to, int cap){
        g[from].eb(to,cap,g[to].size());
        g[to].eb(from,0,g[from].size()-1);
    }
    int dfs(int v, int t, int f){
        if(v==t) return f;
        used[v]=true;
        rep(i,g[v].size()){
            auto &e=g[v][i];
            if(!used[e.to] && e.cap>0){
                int d=dfs(e.to, t, min(f,e.cap));
                if(d>0){
                    e.cap-=d;
                    g[e.to][e.rev].cap+=d;
                    return d;
                }
            }
        }
        return 0;
    }
    int calcMF(int s, int t){
        int flow=0;
        while(1){
            fill(all(used),false);
            int f=dfs(s,t,INF);
            if(f==0) return flow;
            flow+=f;
        }
    }
};

int main(){
    get(h,w);
    vs m(h);
    int t=0;
    rep(i,h)cin>>m[i];
    MaxFlow mf(h*w+2);
    rep(i,h)rep(j,w){
        if(m[i][j]!='.') continue;
        t++;
        if((i+j)%2==1){
            mf.add(i*w+j,h*w+1,1);
        }else{
            mf.add(h*w,i*w+j,1);
            if(i>0&&m[i-1][j]=='.')mf.add(i*w+j,(i-1)*w+j,1);
            if(i<h-1&&m[i+1][j]=='.')mf.add(i*w+j,(i+1)*w+j,1);
            if(j>0&&m[i][j-1]=='.')mf.add(i*w+j,i*w+(j-1),1);
            if(j<w-1&&m[i][j+1]=='.')mf.add(i*w+j,i*w+(j+1),1);
        }
    }
    cout<<t-mf.calcMF(h*w,h*w+1)<<endl;
	return 0;
}
