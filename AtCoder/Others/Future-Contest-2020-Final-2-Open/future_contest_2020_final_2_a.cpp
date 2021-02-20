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
struct point{
    ll x,y,c;
    point(){}
    point(ll x,ll y,ll c):x(x),y(y),c(c){}
    void get(){cin>>x>>y>>c;}
    double dist(point p){
        double d = hypot(abs(x-p.x), abs(y-p.y));
        if(d>=c+p.c) return -1;
        return d;
    }
};

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    ll n,s;
    cin>>n>>s;
    vector<point> p(n);
    rep(i,n)p[i].get();
    vector<pll> edge;

    vector<pll> ps;
    rep(i,n)ps.emplace_back(-p[i].c, i);
    sort(all(ps));

    rep(i,n)range(j,i+1,n){
        ll a=ps[i].sc, b=ps[j].sc;
        if(p[a].dist(p[b])!=-1)edge.emplace_back(a+1,b+1);
    }
    ll u=min(100000ll, (ll)edge.size());

    set<ll> use;
    puta(u);
    rep(i,u){
        puta(edge[i].fs, edge[i].sc);
        use.insert(edge[i].fs);
        use.insert(edge[i].sc);
    }
    vector<pll> use2;
    for(auto&j:use){
        use2.emplace_back(-p[j-1].c, j);
    }
    sort(all(use2));

    ll k;
    rep(i,s){
        cin>>k;
        vl a(k-1);cin>>a;
        
        rep(j,k){
            cout<<use2[j].sc;if(j+1!=k)cout<<" ";else {cout<<endl;break;}
        }
    }
    return 0;
}