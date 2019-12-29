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
#define _cTime (chrono::system_clock::now())
#define progress (chrono::duration_cast<chrono::milliseconds>(_cTime-_sTime).count())
#define reset _sTime=_cTime
auto reset;

mt19937 _mt(chrono::steady_clock::now().time_since_epoch().count());
ll getRand(ll l,ll r){return uniform_int_distribution<ll>(l,r-1)(_mt);}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    ll n,m;
    cin>>n>>m;
    vs df(n);
    rep(i,n)cin>>df[i];
    vl py,px;
    rep(i,n)rep(j,n)if(df[i][j]=='X'){py.push_back(i); px.push_back(j);}

    ll ans=LINF;
    vs af=df;
    ll rep=0;

    while(progress<900){
        ll val=0;
        vs f=df;
        vvl cc;

        while(progress<960){
            vvl cnt(n,vl(n,0));
            rep(_,m){
                ll i=py[_];
                ll j=px[_];
                vl ny,nx,nv;
                rep(v,8){
                    bool need=true;
                    ll y=i,x=j;
                    while(true){
                        y+=dy[v];x+=dx[v];
                        if(y<0 or x<0 or y>=n or x>=n)need=false;
                        if(need and f[y][x]=='#')need=false;
                        if(need and f[y][x]=='X')need=false;
                        if(!need or f[y][x]=='Q')break;
                    }
                    if(need){
                        ny.push_back(y);
                        nx.push_back(x);
                        nv.push_back(v);
                    }
                }
                rep(d,ny.size()){
                    ll y=ny[d], x=nx[d], v=nv[d];
                    while(true){
                        y-=dy[v];x-=dx[v];
                        if(f[y][x]=='.')cnt[y][x]+=(cc.size()==0?1:getRand(0,cc[y][x]*cc[y][x]+1));
                        else break;
                    }
                }
            }
            if(cc.size()==0){
                cc=cnt;
            }
            ll cm=0,cy,cx;
            rep(i,n)rep(j,n){
                if(chmax(cm,cnt[i][j]) and getRand(0,10))cy=i,cx=j;
            }
            if(cm<=3)break;
            f[cy][cx]='#';
            val++;
        }


        rep(_,m){
            ll i=py[_];
            ll j=px[_];
            rep(v,8){
                bool need=true;
                ll y=i,x=j;
                while(true){
                    y+=dy[v];x+=dx[v];
                    if(y<0 or x<0 or y>=n or x>=n)need=false;
                    if(need and f[y][x]=='#')need=false;
                    if(need and f[y][x]=='X')need=false;
                    if(!need or f[y][x]=='Q')break;
                }
                if(need){
                    f[i+dy[v]][j+dx[v]]='#';
                    val++;
                }
            }
        }

        rep(i,n)rep(j,n)if(f[i][j]=='#'){
            string s="";
            rep(v,8){
                ll y=i,x=j;
                bool need=true;
                while(true){
                    y+=dy[v];x+=dx[v];
                    if(y<0 or x<0 or y>=n or x>=n)need=false;
                    if(need and f[y][x]=='#')need=false;
                    if(need and f[y][x]=='X')need=false;
                    if(!need or f[y][x]=='Q')break;
                }
                if(y<0 or x<0 or y>=n or x>=n)s+=".";
                else s+=f[y][x];
            }
            bool need=false;
            if(s[0]=='Q' and s[2]=='X') need=true;
            if(s[1]=='Q' and s[3]=='X') need=true;
            if(s[2]=='Q' and s[0]=='X') need=true;
            if(s[3]=='Q' and s[1]=='X') need=true;
            if(s[4]=='Q' and s[6]=='X') need=true;
            if(s[5]=='Q' and s[7]=='X') need=true;
            if(s[6]=='Q' and s[4]=='X') need=true;
            if(s[7]=='Q' and s[5]=='X') need=true;
            if(!need){
                f[i][j]=='.';
                val--;
            }
        }
        if(chmin(ans,val))af=f;
        rep++;
    }

    rep(i,n)puta(af[i]);
    // puta(ans,rep);
    return 0;
}
