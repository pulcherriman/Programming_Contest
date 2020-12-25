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
int M=20000;
vector<long double> d1(M,log(1));
vector<long double> d2(M,log(1));
vector<long double> d3(M,log(1));
bool calc=true;

int solve(ll p, ll w){
    if(p*w>100)return -2;
    // if(w<=1 || p==0)return -1;

    if(calc){
        calc=false;
        long double P=p/100.;
        range(i,1,M){
            d1[i]=d1[i-1]+log(1-P)-log(i);
            d2[i]=d2[i-1]+log(P)-log(i);
            d3[i]=d3[i-1]+log(i);
        }
    }

    long double val=1, v=0;
    ll ans=-1;
    range(_i,1,M){
        int i=w*_i-1;
        if(i>=M)break;
        int x=((w-1)*i+w-1)/w;
        val=0;
        rep(j,x){
            v=exp(d1[j] + d2[i-j] + d3[i]);
            if(v==0)break;
            val+=v;
        }
        if(val>0.5) ans=i;
    }
    return ans;
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    ll p,w;
    cin>>p>>w;
    puta(solve(p,w));
    // rep(p,5){
    //     calc =true;
    //     rep(w,101){
    //         cout<<solve(p,w)<<",";
    //     }
    //     cout<<endl;
    // }

    return 0;
}