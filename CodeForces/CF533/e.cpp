#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using vb=vector<bool>;
using vvb=vector<vb>;
using vd=vector<double>;
using vvd=vector<vd>;
using vi=vector<int>;
using vvi=vector<vi>;
using vl=vector<ll>;
using vvl=vector<vl>;
using pll=pair<ll,ll>;
using tll=tuple<ll,ll>;
using vs=vector<string>;
#define all(a) a.begin(),a.end()
#define rall(a) a.rbegin(),a.rend()
#define rep(i,n) range(i,0,n)
#define range(i,a,n) for(ll i=(a);i<(n);i++)
#define LINF ((ll)1ll<<60)
#define INF ((int)1<<30)
#define EPS (1e-9)
#define MOD (1000000007ll)
#define fcout(a) cout<<setprecision(a)<<fixed
#define fs first
#define sc second
#define PI 3.1415926535897932384

int dx[]={1,0,-1,0,1,-1,-1,1},dy[]={0,1,0,-1,1,1,-1,-1};
template<class S,class T>ostream&operator<<(ostream&os,pair<S,T>p){os<<"["<<p.first<<", "<<p.second<<"]";return os;};
template<class S>auto&operator<<(ostream&os,vector<S>t){bool a=1; for(auto s:t){os<<(a?"":" ")<<s;a=0;} return os;}
template<class S>void tf(bool b,S t,S f){cout<<(b?t:f)<<endl;}
void OUT(bool b){tf(b,"YES","NO");}
void Out(bool b){tf(b,"Yes","No");}
void out(bool b){tf(b,"yes","no");}
template<class T>void puta(T&&t){cout<<t<<endl;}
template<class H,class...T>void puta(H&&h,T&&...t){cout<<h<<' ';puta(t...);}

int popcnt(int x){return __builtin_popcount(x);}
int popcnt(ll x){return __builtin_popcountll(x);}
int bsr(int x){return 31 - __builtin_clz(x);}
int bsr(ll x){return 63 - __builtin_clzll(x);}
int bsf(int x){return __builtin_ctz(x);}
int bsf(ll x){return __builtin_ctzll(x);}
template<class T>bool chmax(T&a,T b){if(a<b){a=b; return true;}return false;}
template<class T>bool chmin(T&a,T b){if(a>b){a=b; return true;}return false;}

/*他のライブラリを入れる場所*/
/*
 * 最大流問題を解く（フォードファルカーソン）
 * MaxFlow mf(100); //100頂点のグラフを考える、以降0-indexed
 * mf.add(0,5,10);  //頂点0から頂点5に、流量10の辺。最大流問題では、有向かつ流量が正整数の辺しか張れない。
 * mf.calcMF(0,5);  //頂点0から頂点5の流量を求める。O(辺の数*最大流量)
 */
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
        g[from].emplace_back(to,cap,g[to].size());
        g[to].emplace_back(from,0,g[from].size()-1);
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
	cin.tie(0);
	ios::sync_with_stdio(false);
	int n,m;
	cin>>n>>m;
	map<string,int> db;
	vi ts(m+2,0),old(m+2,0);
	old[m]=1;
	MaxFlow mf(m+2);
	rep(i,n){
		int t;
		cin>>t;
		if(t==1){
			ts=vi(m,0);
		}else{
			string s;cin>>s;
			if(db.find(s)==db.end()){
				db[s]=db.size();
			}
			ts[db[s]]=1;
		}
	}
	return 0;
}