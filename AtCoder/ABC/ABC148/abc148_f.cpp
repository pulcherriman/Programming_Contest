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
    ll n,t,a;
    cin>>n>>t>>a;
    t--;a--;
    vvl edge(n);
    rep(i,n-1){
        ll p,q;cin>>p>>q;
        edge[p-1].push_back(q-1);
        edge[q-1].push_back(p-1);
    }
    vl vt(n,-1), va(n,-1);
    queue<int> q;
    q.push(t);vt[t]=0;
    while(!q.empty()){
        ll p=q.front();q.pop();
        for(auto&nxt:edge[p]){
            if(vt[nxt]==-1){
                q.push(nxt);
                vt[nxt]=vt[p]+1;
            }
        }
    }
    q.push(a);va[a]=0;
    while(!q.empty()){
        ll p=q.front();q.pop();
        for(auto&nxt:edge[p]){
            if(va[nxt]==-1){
                q.push(nxt);
                va[nxt]=va[p]+1;
            }
        }
    }
    // ll turn=0,ans=0;;
    // while(true){
    //     if(turn==0){
    //         ll mv=-1, mp=0;
    //         for(auto&adj:edge[t]){
    //             if(chmax(mv,va[adj]))mp=adj;
    //         }
    //         t=mp;
    //         if(t==a){
    //             puta(ans);
    //             return 0;
    //         }
    //     }else{
    //         ll mv=LINF, mp=0;
    //         for(auto&adj:edge[a]){
    //             if(chmin(mv,vt[adj]))mp=adj;
    //         }
    //         a=mp;
    //         ans++;
    //         if(t==a){
    //             puta(ans);
    //             return 0;
    //         }
    //     }
    //     puta(turn, t,a);
    //     turn=1-turn;
    // }
    ll oe = (va[0]-vt[0]+20000000)%2;
    // puta(vt);
    // puta(va);
    ll ans=0,a2=oe?0:LINF;
    rep(i,n){
        if(va[i]>vt[i] and edge[i].size()>=2)chmax(ans, va[i]);
        if(va[i]==vt[i] and edge[i].size()>=2)chmin(a2, va[i]);
    }
    puta(max(ans,a2));
    return 0;
}