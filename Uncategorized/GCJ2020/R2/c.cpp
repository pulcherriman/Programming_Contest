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

constexpr ll gcd(ll a,ll b){return b?gcd(b,a%b):a;}
constexpr ll lcm(ll a,ll b){return a/gcd(a,b)*b;}
ll n;
ll nexthole(vector<pll>&p, pll&vec, pll&pos, bool isF){
    ll ret=-1;
    ll dist=LINF;
    rep(i,n){
        if(isF and p[i]==pos)return i;
        if(!isF and p[i]==pos)continue;
        ll x=p[i].fs-pos.fs;
        ll y=p[i].sc-pos.sc;
        ll g=gcd(abs(x),abs(y));
        if(g){x/=g;y/=g;}

        if(vec==pll{x,y}){
            if(chmin(dist,x*x+y*y)){
                ret=i;
            }
        }
    }
    return ret;
}

ll play(vector<pll>&p, int start, pll vec, vl&hole){
    pll pos=p[start];
    set<ll> ans;
    set<ll> in,out;
    bool isF=true;

    puta(start,vec,hole);


    while(1){
        ll nxt = nexthole(p,vec,pos,isF);
        puta("next: ",start,nxt);
        if(nxt!=-1){
            ans.insert(nxt);
            if(in.find(nxt)!=in.end())break;
            in.insert(nxt);
        }

        isF=false;
        if(nxt==-1)break;
        bool dep=false;
        rep(i,n)if(nxt!=i)if(hole[nxt]==hole[i]){
            dep=true;
            start = i;
            break;
        }
        if(!dep)break;
        pos=p[start];
        ans.insert(start);
        if(out.find(start)!=out.end())break;
        out.insert(start);
    }
    puta(ans.size());
    return ans.size();
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    
    ll testcase;
    cin>>testcase;
    rep(tc,testcase){
        cout<<"Case #"<<tc+1<<": ";
        cin>>n;
        vector<pll> p(n);
        rep(i,n)cin>>p[i].fs>>p[i].sc;
        vl hole;
        rep(i,n)hole.push_back(i/2);
        set<pll> vec;
        rep(i,n)rep(j,n)if(i!=j){
            ll x=p[i].fs-p[j].fs;
            ll y=p[i].sc-p[j].sc;
            ll g=gcd(abs(x),abs(y));
            x/=g;y/=g;
            vec.emplace(x,y);
        }
        ll ans=1;
        do{hole={0,1,0,1,2};
            for(auto&v:vec)rep(start,n){
                chmax(ans,play(p, start, v, hole));
            }
            break;
        }while(next_permutation(all(hole)));
        puta(ans);
    }
    return 0;
}