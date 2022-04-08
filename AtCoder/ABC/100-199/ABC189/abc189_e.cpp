#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using ull=unsigned long long;
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
#define rrep(i,n) for(ll i=((ll)n)-1;i>=0;i--)
#define range(i,a,n) for(ll i=((ll)a);i<((ll)n);i++)
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
template<class S,class T>auto&operator<<(ostream&os,map<S,T>mp){bool a=1;for(auto p:mp){os<<(a?"":", ")<<p;a=0;}return os;}
template<class S>auto&operator>>(istream&is,vector<S>&t){for(S&a:t)cin>>a;return is;}

/*他のライブラリを入れる場所*/
vl mul(vl a,vl b){
    vl r(9,0);
    rep(i,3)rep(j,3)rep(k,3){
        r[i*3+j]+=a[i*3+k]*b[j+k*3];
    }
    return r;
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    ll n,m,q;
    cin>>n;
    vl x(n),y(n);
    rep(i,n)cin>>x[i]>>y[i];

    cin>>m;
    vvl g(m+1,vl{1,0,0,0,1,0,0,0,1});
    rep(i,m){
        ll t;cin>>t;
        if(t==1){
            g[i+1]=vl{0,1,0,-1,0,0,0,0,1};
        }else if(t==2){
            g[i+1]=vl{0,-1,0,1,0,0,0,0,1};
        }else if(t==3){
            ll v; cin>>v;
            g[i+1]=vl{1,0,-v,0,1,0,0,0,1};
            g[i+1]=mul(vl{-1,0,0,0,1,0,0,0,1},g[i+1]);
            g[i+1]=mul(vl{1,0,v,0,1,0,0,0,1}, g[i+1]);
        }else{
            ll v; cin>>v;
            g[i+1]=vl{1,0,0,0,1,-v,0,0,1};
            g[i+1]=mul(vl{1,0,0,0,-1,0,0,0,1}, g[i+1]);
            g[i+1]=mul(vl{1,0,0,0,1,v,0,0,1}, g[i+1]);
        }
    }

    rep(i,m)g[i+1]=mul(g[i+1],g[i]);
    cin>>q;
    rep(i,q){
        ll ind,t;
        cin>>t>>ind;
        ind--;
        auto r=mul( g[t], vl{1,0,x[ind],0,1,y[ind],0,0,1});
        puta(r[2], r[5]);
    }
    return 0;
}