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
    ll testcase;
    cin>>testcase;
    rep(tc,testcase){
        cout<<"Case #"<<tc+1<<": ";

        ll h,w;
        cin>>h>>w;
        if(h*w>100)return 0;
        vvl a(h,vl(w)), l(h,vl(w,LINF));
        cin>>a;
        rep(i,h){
            ll d=0;
            rep(j,w){
                if(j==0 or a[i][j-1]<a[i][j]){
                    d=0;
                }else{
                    if(a[i][j-1]==a[i][j]){
                        if(d) d++;
                    }else{
                        d=1;
                    }
                    if(d) chmin(l[i][j], d);
                }
            }
            d=0;
            rrep(j,w){
                if(j==w-1 or a[i][j+1]<a[i][j]){
                    d=0;
                }else{
                    if(a[i][j+1]==a[i][j]){
                        if(d) d++;
                    }else{
                        d=1;
                    }
                    if(d) chmin(l[i][j], d);
                }
            }
        }
        rep(j,w){
            ll d=0;
            rep(i,h){
                if(i==0 or a[i-1][j]<a[i][j]){
                    d=0;
                }else{
                    if(a[i-1][j]==a[i][j]){
                        if(d) d++;
                    }else{
                        d=1;
                    }
                    if(d)chmin(l[i][j], d);
                }
            }
            d=0;
            rrep(i,h){
                if(i==h-1 or a[i+1][j]<a[i][j]){
                    d=0;
                }else{
                    if(a[i+1][j]==a[i][j]){
                        if(d) d++;
                    }else{
                        d=1;
                    }
                    if(d) chmin(l[i][j], d);
                }
            }
        }

        rep(j,w){
            ll mv=0;
            rep(i,h)chmax(mv, a[i][j]);
            rep(i,h)if(a[i][j]==mv){
                for(ll x=i+1; x<h;x++){if(a[x][j]==mv)break; chmin(l[x][j], x-i);}
                for(ll x=i-1; x>=0;x--){if(a[x][j]==mv)break; chmin(l[x][j], i-x);}
            }
        }
        rep(i,h)puta(l[i]);
        ll t=0;
        rep(i,h)rep(j,w)if(l[i][j]!=LINF)chmax(t, l[i][j]);
        t++;
        
        ll ans=0;
        rep(i,h)rep(j,w)if(l[i][j]==LINF)ans+=a[i][j]*t;else ans+=a[i][j]*l[i][j];
        puta(ans);
    }
    return 0;
}