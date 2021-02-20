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
struct car{
    ll x,d; double v;
    car(){}
    car(ll X, double V, ll D):x(X),v(V),d(D){}
};
using Edge=pair<ll,double>;

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    ll n,l;
    cin>>n>>l;
    vector<car> c;
    rep(i,n+1){
        ll x=0,v,d;
        if(i)cin>>x; cin>>v>>d;
        c.emplace_back(x,v,d);
    }
    c.emplace_back(l,0,0);
    sort(all(c),[](car a, car b){return a.x<b.x;});

    vector<vector<Edge>> edge(n+2);
    rep(i,n+2)range(j,i+1,n+2){
        if(c[i].x + c[i].d >= c[j].x)edge[i].emplace_back(j,(c[j].x-c[i].x)/c[i].v);
    }
    auto cmp=[](Edge a,Edge b){return a.sc>b.sc ;};
    priority_queue<Edge, vector<Edge>, decltype(cmp)> q{cmp};
    q.emplace(0,0);
    vd ans(n+2,-1);
    while(!q.empty()){
        ll p; double d;
        tie(p,d) = q.top() ; q.pop();
        if(ans[p]!=-1)continue;
        ans[p]=d;
        for(auto&e:edge[p]){
            ll np; double nc;
            tie(np,nc) = e;
            q.emplace(np,d+nc);
        }
    }
    if(ans[n+1]==-1)puta("impossible");
    else fcout(16)<<ans[n+1]<<endl;
    return 0;
}