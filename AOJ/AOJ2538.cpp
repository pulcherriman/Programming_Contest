#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using vb=vector<bool>;
using vvb=vector<vb>;
using vvvb=vector<vvb>;
using vvvvb=vector<vvvb>;
using vd=vector<double>;
using vvd=vector<vd>;
using vi=vector<int>;
using vvi=vector<vi>;
using vvvi=vector<vvi>;
using vvvvi=vector<vvvi>;
using vl=vector<ll>;
using vvl=vector<vl>;
using pii=pair<int, int>;
using pll=pair<ll,ll>;
using tll=tuple<ll,ll>;
using tlll=tuple<ll,ll,ll>;
using vs=vector<string>;
#define all(a) a.begin(),a.end()
#define rall(a) a.rbegin(),a.rend()
#define rep(i,n) range(i,0,n)
#define rrep(i,n) for(ll i=(n)-1;i>=0;i--)
#define range(i,a,n) for(ll i=(a);i<(n);i++)
#define LINF ((ll)1ll<<60)
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
using Pos=map<char, vector<pii>>;
using Visit=vvvvb;
constexpr bool cmp(int&a,int l, int r){
    return l<=a and a<r;
}
vvvvi memo;
vvvvi vis;
int rec(int sy, int sx, int gy, int gx, vs&f, Pos&mp){
    if(!cmp(sy,0,f.size()) or !cmp(gy,0,f.size()) or !cmp(sx,0,f[0].size()) or !cmp(gx,0,f[0].size())){
        return -1;
    }
    if(f[sy][sx]=='#' or f[gy][gx]=='#'){
        return -1;
    }
    if(sx>gx or sy>gy or (sx==gx and sy==gy)){
        return 0;
    }
    if(memo[sy][sx][gy][gx]!=INF){
        return memo[sy][sx][gy][gx];
    }
    if(vis[sy][sx][gy][gx]!=1) return -1;
    int ret=max(rec(sy+1,sx,gy,gx,f,mp), rec(sy,sx+1,gy,gx,f,mp));
    if(islower(f[sy][sx])){
        for(auto&to : mp[toupper(f[sy][sx])]){
            int ty,tx,val=0;
            tie(ty,tx) = to;
            if(vis[sy][sx][ty][tx]!=1 or vis[ty][tx][gy][gx]!=1)continue;
            val += max({rec(sy+1,sx,ty,tx-1,f,mp), rec(sy,sx+1,ty-1,tx,f,mp),
                        rec(sy+1,sx,ty-1,tx,f,mp), rec(sy,sx+1,ty,tx-1,f,mp)});
            val += 1+rec(ty,tx,gy,gx,f,mp);
            chmax(ret, val);
        }
    }
    return memo[sy][sx][gy][gx] = ret;
}
bool bfs(int sy, int sx, int gy, int gx, vs&f){
    if(!cmp(sy,0,f.size()) or !cmp(gy,0,f.size()) or !cmp(sx,0,f[0].size()) or !cmp(gx,0,f[0].size())){
        return 0;
    }
    if(vis[sy][sx][gy][gx]!=-1) return vis[sy][sx][gy][gx];
    int ret = 0;
    if(sx>gx or sy>gy or f[sy][sx]=='#' or f[gy][gx]=='#'){
        ;
    } else if (sx==gx and sy==gy){
        ret = f[sy][sx]=='#'?0:1;
    }else if (sx==gx and sy+1==gy and f[sy][sx]!='#' and f[gy][gx]!='#'
                or sy==gy and sx+1==gx and f[sy][sx]!='#' and f[gy][gx]!='#'){
        ret = 1;
    }else{
        ret|=bfs(sy+1,sx,gy-1,gx,f);
        ret|=bfs(sy+1,sx,gy,gx-1,f);
        ret|=bfs(sy,sx+1,gy-1,gx,f);
        ret|=bfs(sy,sx+1,gy,gx-1,f);
    }
    
    return vis[sy][sx][gy][gx]=ret;
}
/*他のライブラリを入れる場所*/
int solve(int h, int w){
    vs f(h);
    cin>>f;
    memo=vvvvi(h, vvvi(w, vvi(h, vi(w,INF))));
    vis=vvvvi(h, vvvi(w, vvi(h, vi(w,-1))));
    Pos mp;
    rep(i,h)rep(j,w){
        if(isalpha(f[i][j])){
            if(mp.find(f[i][j])==mp.end()){
                mp[f[i][j]] = vector<pii>();
            }
            mp[f[i][j]].emplace_back(i,j);
        }
    }
    rep(i,h)rep(j,w)rep(k,h)rep(l,w)bfs(i,j,k,l,f);
    return rec(0,0,h-1,w-1,f,mp);
}
int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    ll h,w;
    while(cin>>h>>w,h+w){
        puta(solve(h,w));
    }
    return 0;
}