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
int sgn(const double&r){return (r>EPS)-(r<-EPS);} // a>0  : sgn(a)>0
int sgn(const double&a,const double&b){return sgn(a-b);} // b<=c : sgn(b,c)<=0

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


int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    ll h,w;
    cin>>h>>w;
    vvl f(h+1,vl(w+1,0));
    vs s(h);
    rep(i,h){cin>>s[i];rep(j,w)f[i+1][j+1]=(s[i][j]=='#'?1:0);}
    rep(i,h+1)rep(j,w)f[i][j+1]+=f[i][j];
    rep(i,h)rep(j,w+1)f[i+1][j]+=f[i][j];
    vvl a(h+2,vl(w+2,0));


    ll q; cin>>q;
    vl qy(q),qx(q),ql(q);
    rep(i,q)cin>>qy[i]>>qx[i]>>ql[i];




    if(max(ql)==1){
        vvl ans(h+2,vl(w+2,-1));
        range(i,1,h+1)range(j,1,w+1)if(s[i-1][j-1]=='.' and ans[i][j]==-1){
            queue<pll> q;
            q.emplace(i,j);
            vector<pll> p;
            vvb v(h+2,vb(w+2,false));
            ll val=0;
            while(!q.empty()){
                ll cy,cx; tie(cy,cx)=q.front();q.pop();
                // puta(cy,cx);
                if(v[cy][cx])continue;
                v[cy][cx]=true;
                val++;
                p.emplace_back(cy,cx);
                rep(d,4){
                    ll ny=cy+dy[d], nx=cx+dx[d];
                    if(ny>0 and nx>0 and ny<=h and nx<=w){
                        if(s[ny-1][nx-1]=='.' and !v[ny][nx] and ans[ny][nx]==-1)q.emplace(ny,nx);
                    }
                }
            }
            for(auto&pt:p)if(v[pt.fs][pt.sc])ans[pt.fs][pt.sc]=val;
        }
        rep(i,q){
            ll y=qy[i], x=qx[i], l=ql[i];
            puta(ans[y][x]);
        }
    }else{
        vector<map<pll,ll>> memo(1501);
        rep(i,h)rep(j,w){
            ll ok=0,ng=min(h,w)+1;
            while(ng-ok>1){
                ll mid=(ok+ng)/2;
                ll rig = j+mid, btm = i+mid;
                bool safe = (rig<=w and btm<=h);
                if(safe)safe=(f[btm][rig]-f[btm][j]-f[i][rig]+f[i][j])==0;
                if(safe)ok=mid; else ng=mid;
            }
            a[i+1][j+1]=ok;
        }

        rep(i,q){
            ll y=qy[i], x=qx[i], l=ql[i];
            queue<pll> q;
            q.emplace(y,x);
            vvb v(h+2,vb(w+2,false));
            ll ans=0;
            while(!q.empty()){
                ll cy,cx; tie(cy,cx)=q.front();q.pop();
                if(v[cy][cx])continue;
                v[cy][cx]=true;
                ans++;
                auto pr = make_pair(cy,cx);
                if(memo[l].find(pr)!=memo[l].end()){
                    ans=memo[l][pr];
                    break;
                }
                rep(d,4){
                    ll ny=cy+dy[d], nx=cx+dx[d];
                    if(ny>0 and nx>0 and ny<=h and nx<=w){
                        if(a[ny][nx]>=l)q.emplace(ny,nx);
                    }
                }
            }
            range(j,1,h+1)range(k,1,w+1)if(v[j][k])memo[l][make_pair(j,k)]=ans;
            puta(ans);
        }
    }

    return 0;
}