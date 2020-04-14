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
int popcnt(int x){return __builtin_popcount(x);}
int popcnt(ll x){return __builtin_popcountll(x);}
int bitdig(int x){return 32 - __builtin_clz(x);}
int bitdig(ll x){return 64 - __builtin_clzll(x);}
int bitffs(int x){return __builtin_ffs(x);}
int bitffs(ll x){return __builtin_ffsll(x);}


int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    ll testcase;
    cin>>testcase;
    
    testcase = 1000000000;
    rrep(tc,testcase){
        // cout<<"Case #"<<tc+1<<":"<<endl;

        ll n;
        n=tc+1; // cin>>n;
        vector<pll> ans;
        bool ok=false;
        rep(i,30){//難行素通りするか
            ll v=n-i;
            if(v<0)break;
            // puta(bitdig(v)-popcnt(v));
            if(bitdig(v)-popcnt(v) <= i){
                ll d=1,l=1,s=i;
                while(v){
                    if(v%2==0){
                        if(l)ans.emplace_back(d,1);
                        else ans.emplace_back(d,d);
                        s--;
                    }else{
                        if(l){
                            rep(j,d)ans.emplace_back(d,j+1);
                        }else{
                            rep(j,d)ans.emplace_back(d,d-j);
                        }
                        l=1-l;
                    }
                    v/=2;
                    d++;
                }
                rep(j,s){
                    if(l)ans.emplace_back(d,1);
                    else ans.emplace_back(d,d);
                    d++;
                }
                if(ans.size()<=500){
                    // for(auto&a:ans){
                    //     puta(a.fs, a.sc);
                    // }
                    ok=true;
                    break;
                }
            }
        }
        if(!ok){puta(n);return 0;}
        if(n%100000000==0)puta("prog", n);
    }
    return 0;
}