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
    ll n;
    vvl near{
        {0},
        {0,1},
        {1,2},
        {2},
        {0,3},
        {0,1,3,4},
        {1,2,4,5},
        {2,5},
        {6,3},
        {7,6,4,3},
        {8,7,5,4},
        {8,5},
        {6},
        {7,6},
        {8,7},
        {8}
    };
    while(cin>>n,n){
        vvl edge(n*9+9);
        vl f(n*9);
        rep(i,n){
            rep(j,16){
                ll t;cin>>t;
                // cout<<t;
                // if(j%4==3)cout<<endl;
                if(t)for(auto&q:near[j])f[i*9+q]=1;
            }
            // rep(j,9){cout<<f[i*9+j];if(j%3==2)cout<<endl;}
            // puta("===");
            rep(y,3)rep(x,3)rep(ny,3)rep(nx,3)if(y==ny or x==nx){
                edge[i*9+y*3+x].push_back(i*9+9+ny*3+nx);
            }
        }

        queue<pll> q;
        q.emplace(4,1+1*7+1*7*7+1*7*7*7);
        vvb v(n*9+9,vb(2500,false));
        bool ok=false;
        while(!q.empty()){
            ll p,r; tie(p,r)=q.front();
            q.pop();
            if(f[p] or v[p][r])continue;
            if(p/9==n-1){
                // puta(r%7, r/7%7, r/7/7%7, r/7/7/7%7);
                ok=true;
                break;
            }
            v[p][r]=true;
            for(auto&nxt:edge[p]){
                if(f[nxt])continue;
                ll w1=r%7+1;
                ll w2=r/7%7+1;
                ll w3=r/7/7%7+1;
                ll w4=r/7/7/7%7+1;
                if(nxt%9==0)w1=0;
                if(nxt%9==2)w2=0;
                if(nxt%9==6)w3=0;
                if(nxt%9==8)w4=0;
                if(w1==7 or w2==7 or w3==7 or w4==7)continue;
                q.emplace(nxt,(((w4*7+w3)*7+w2)*7+w1));
            }
        }
        if(ok)puta(1);else puta(0);
    }
    return 0;
}