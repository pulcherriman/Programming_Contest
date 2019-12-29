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

vvl f;

ll cnt(ll a,ll b,ll c,ll d){
    b--;a--;
    return f[c][d]-f[c][b]-f[a][d]+f[a][b];
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    ll h,w;
    cin>>h>>w;
    vs s(h);
    cin>>s;
    f=vvl(h+1,vl(w+1,0));
    ll v=0;
    rep(i,h)rep(j,w)if(s[i][j]=='.')f[i+1][j+1]=1,v++;
    rep(i,h+1)rep(j,w)f[i][j+1]+=f[i][j];
    rep(i,h)rep(j,w+1)f[i+1][j]+=f[i][j];
    //o
    // rep(i,h+1)puta(f[i]);
    if(cnt(1,1,h,w)==0){puta(0);return 0;}
    //1
    rep(i,h/2)rep(j,w/2){
        if(cnt(i+1,j+1,i+h/2,j+w/2)==v){puta(1);return 0;}
    }

    int h0=0,h1=0,w0=0,w1=0;
    rep(j,w){
        if(cnt(1,j+1, h/2,j+1)==0)h0++;
        else break;
    }
    rrep(j,w){
        if(cnt(1,j+1, h/2,j+1)==0)h0++;
        else break;
    }
    rep(j,w){
        if(cnt(h/2+1,j+1, h,j+1)==0)h1++;
        else break;
    }
    rrep(j,w){
        if(cnt(h/2+1,j+1, h,j+1)==0)h1++;
        else break;
    }
    rep(i,h){
        if(cnt(i+1,1, i+1,w/2)==0)w0++;
        else break;
    }
    rrep(i,h){
        if(cnt(i+1,1, i+1,w/2)==0)w0++;
        else break;
    }
    rep(i,h){
        if(cnt(i+1,w/2+1, i+1,w)==0)w1++;
        else break;
    }
    rrep(i,h){
        if(cnt(i+1,w/2+1, i+1,w)==0)w1++;
        else break;
    }
    // puta(h0,h1,w0,w1);
    if(h0<w/2 and h1<w/2 and w0<h/2 and w1<h/2){puta(4);return 0;}
    if((h0>=w/2 and h1>=w/2) or (w0>=h/2 and w1>=h/2)){puta(2);return 0;}
    puta(3);
    return 0;
}