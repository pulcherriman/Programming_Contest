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
template<class S,class T>ostream&operator<<(ostream&os,map<S,T>d){bool a=1;for(auto v:d){os<<(a?"":" ")<<v;a=0;}return os;};
template<class S>ostream&operator<<(ostream&os,set<S>d){bool a=1;for(auto v:d){os<<(a?"":" ")<<v;a=0;}return os;};
template<class S>auto&operator<<(ostream&os,vector<S>d){bool a=1;for(auto v:d){os<<(a?"":" ")<<v;a=0;}return os;}
template<class S>auto&operator>>(istream&is,vector<S>&t){for(S&a:t)cin>>a;return is;}

/*他のライブラリを入れる場所*/
ll cnt(ll v, vl&a){//v以下の数の個数
    ll r=0,n=a.size(),need=0,p=0;
    if(v<=0){
        rep(i,n){
            if(a[i]<0){
                need=(-v-a[i]-1)/(-a[i]);
                p=lower_bound(all(a), need)-a.begin();
                r+=n-p;
            }else if(a[i]==0){
                if(v==0){
                    r+=n-i-1;
                }
            }   
        }
    }else{
        rep(i,n){
            if(a[i]<0){
                need=-(v/(-a[i]));
                p=lower_bound(all(a), need)-a.begin();
                if(p>i){
                    r+=n-p;
                }else{
                    r+=n-i-1;
                }
            }else if(a[i]==0){
                r+=n-i-1;
            }else{
                need=(v)/(a[i]);
                p=lower_bound(all(a), need+1)-a.begin();
                r+=max(p-i-1, 0ll);
            }
            // puta(i,r);
        }
    }
    return r;
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    ll n,k;
    cin>>n>>k;
    vl a(n);
    cin>>a;
    sort(all(a));
    ll l=-1000000000000000000ll,r=1000000000000000001ll;
    while(abs(r-l)>1){
        ll m=(r+l)/2;
        ll v=cnt(m,a);
        // ll v2=cnt(m-1,a);
        // puta(l,r,m,v);
        if(v<k){
            l=m;
        }else{
            r=m;
        }
        // puta(l,r,m,v);
    } 
    puta(l+1);
    return 0;
}