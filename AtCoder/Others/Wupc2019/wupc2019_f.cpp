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
using tlll=tuple<ll,ll,ll>;
using vs=vector<string>;
#define all(a) a.begin(),a.end()
#define rall(a) a.rbegin(),a.rend()
#define rep(i,n) range(i,0,n)
#define rrep(i,n) for(ll i=(n)-1;i>=0;i--)
#define range(i,a,n) for(ll i=(a);i<(n);i++)
#define LINF ((ll)1ll<<55)
#define INF ((int)1<<30)
#define EPS (1e-9)
#define MOD (1000000007ll)
#define fcout(a) cout<<setprecision(a)<<fixed
#define fs first
#define sc second
#define PI (3.1415926535897932384)

int dx[]={1,0,-1,0,1,-1,-1,1},dy[]={0,1,0,-1,1,1,-1,-1};
template<class T>bool chmax(T&a,T b){if(a<b){a=b; return true;}return false;}
template<class T>bool chmin(T&a,T b){if(a>b){a=b; return true;}return false;}
template<class S>S sum(vector<S>&a){return accumulate(all(a),S());}
template<class S>S max(vector<S>&a){return *max_element(all(a));}
template<class S>S min(vector<S>&a){return *min_element(all(a));}
ll max(int a,ll b){return max((ll)a,b);} ll max(ll a,int b){return max(a,(ll)b);}

template<class T>void puta(T&&t){cout<<t<<"\n";}
template<class H,class...T>void puta(H&&h,T&&...t){cout<<h<<' ';puta(t...);}
template<class S,class T>void tf(bool b,S t,T f){if(b)puta(t);else puta(f);}
void YN(bool b){tf(b,"YES","NO");}
void Yn(bool b){tf(b,"Yes","No");}
void yn(bool b){tf(b,"yes","no");}
template<class S,class T>ostream&operator<<(ostream&os,pair<S,T>p){os<<"["<<p.first<<", "<<p.second<<"]";return os;};
template<class S>auto&operator<<(ostream&os,vector<S>t){bool a=1;for(auto s:t){os<<(a?"":" ")<<s;a=0;}return os;}
template<class S>auto&operator>>(istream&is,vector<S>&t){for(S&a:t)cin>>a;return is;}

/*他のライブラリを入れる場所*/
/*
 * 最大流問題を解く（フォードファルカーソン）
 * MaxFlow mf(100); //100頂点のグラフを考える、以降0-indexed
 * mf.add(0,5,10);  //頂点0から頂点5に、流量10の辺。最大流問題では、有向かつ流量が正整数の辺しか張れない。
 * mf.calcMF(0,5);  //頂点0から頂点5の流量を求める。O(辺の数*最大流量)
 */

struct max_flow {
    struct edge { ll to, cap, rev; };
    ll V;
    vector<vector<edge>> G;
    vector<ll> itr, level;

    max_flow(ll V) : V(V) { G.assign(V,vector<edge>()); }

    void add_edge(ll from, ll to, ll cap) {
        G[from].push_back((edge) {to, cap, (ll) G[to].size()});
        G[to].push_back((edge) {from, 0, (ll) G[from].size()-1});
    }

    void bfs(ll s) {
        level.assign(V,-1);
        queue<ll> q;
        level[s] = 0; q.push(s);
        while (!q.empty()) {
            ll v = q.front(); q.pop();
            for(auto &e: G[v]){
                if (e.cap > 0 and level[e.to] < 0) {
                    level[e.to] = level[v] + 1;
                    q.push(e.to);
                }
            }
        }
    }

    ll dfs(ll v, ll t, ll f) {
        if (v == t) return f;
        for (ll& i = itr[v]; i < (ll) G[v].size(); ++i) {
            edge& e = G[v][i];
            if (e.cap > 0 and level[v] < level[e.to]) {
                ll d = dfs(e.to, t, min(f, e.cap));
                if (d > 0) {
                    e.cap -= d;
                    G[e.to][e.rev].cap += d;
                    return d;
                }
            }
        }
        return 0;
    }

    ll run(ll s, ll t) {
        ll ret = 0, f;
        while (bfs(s), level[t] >= 0) {
            itr.assign(V,0);
            while ((f = dfs(s, t, LINF)) > 0) ret += f;
        }
        return ret;
    }
};
int main(){
	cin.tie(0);
	ios::sync_with_stdio(false);
	ll n,m;
	cin>>n>>m;
	max_flow mf(n*2+2);
	ll s=n*2, g=n*2+1;

	rep(i,n-2){
		ll p=(i+1)*2;
		ll t;
		cin>>t;
		if(t==-1){
			mf.add_edge(s,p+1,LINF);
			mf.add_edge(p,g,LINF);
		}else{
			mf.add_edge(p,p+1,t);
		}
	}
	rep(i,m){
		ll a,b;
		cin>>a>>b;
		a=(a-1)*2;
		b=(b-1)*2;
		mf.add_edge(a+1,b,LINF);
	}
	ll ans=mf.run(s,g);
	if(ans>=LINF)puta(-1);
	else puta(ans);
	return 0;
}