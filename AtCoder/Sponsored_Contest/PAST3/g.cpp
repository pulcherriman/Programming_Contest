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

int dx[]={1,0,-1,1,-1,0},dy[]={-1,-1,-1,0,0,1};
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
    ll n,x,y;
    cin>>n>>x>>y;
    x+=400,y=400-y;
    vvl a(801,vl(801,-1));
    rep(i,n){
        ll p,q;cin>>p>>q;
        a[400-q][p+400]=-2;
    }
    // range(i, 190, 211){
    //     range(j,190,211){
    //         if(a[i][j]==-2)cout<<"#";
    //         else if(i==y && j==x)cout<<"G";
    //         else if(i==200 && j==200)cout<<"S";
    //         else cout<<".";
    //     }
    //     cout<<endl;
    // }
    queue<tlll> que;
    que.emplace(400,400,0);
    while(!que.empty()){
        ll p,q,c;
        tie(p,q,c)=que.front(); que.pop();
        if(a[p][q]!=-1)continue;
        a[p][q]=c;
        if(p==y && q==x){
            break;
        }
        rep(v,6){
            if(p+dy[v]>800 or p+dy[v]<0)continue;
            if(q+dx[v]>800 or q+dx[v]<0)continue;
            if(a[p+dy[v]][q+dx[v]]==-1){
                que.emplace(p+dy[v], q+dx[v], c+1);
            }
        }
    }
    // range(i, 190, 211){
    //     range(j,190,211){
    //         if(a[i][j]==-2)cout<<"#";
    //         else if(i==y && j==x)cout<<"G";
    //         else if(i==200 && j==200)cout<<"S";
    //         else if(a[i][j]>=1)cout<<a[i][j];
    //         else cout<<".";
    //     }
    //     cout<<endl;
    // }
    puta(a[y][x]);
    
    return 0;
}