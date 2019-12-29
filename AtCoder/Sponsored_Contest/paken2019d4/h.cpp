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
#define _cTime (chrono::system_clock::now())
#define progress (chrono::duration_cast<chrono::milliseconds>(_cTime-_sTime).count())
#define reset _sTime=_cTime
auto reset;
mt19937 _mt(chrono::steady_clock::now().time_since_epoch().count());
ll getRand(ll l,ll r){return uniform_int_distribution<ll>(l,r-1)(_mt);}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    ll n;
    cin>>n;
    vs s(n);cin>>s;
    vector<pll> d(n);
    rep(i,n){
        s[i]+="0";
        ll len=0;
        rep(j,s[i].size()){
            if(s[i][j]=='1'){
                len++;
            }else{
                if(d[i].sc<len)d[i]=make_pair(j-len,len);
                if(len)break;
                len=0;
            }
        }
    }

    vl ansd(n,-1);ll ans=0;
    vl v(n); iota(all(v),0);
    ll cnt=0;

    while(progress<1980){
        shuffle(all(v), _mt);
        //puta(v);
        string cur=string(20000,'0');ll need=70;
        vl vd(n,0);
        for(auto&i:v){
            while(need+1<cur.size())if(cur[need]=='1')need++;else break;
            // if(getRand(0,2))need--;
            vd[i]=need-d[i].fs;
            range(j,d[i].fs, s[i].size()){
                chmax(cur[need+j-d[i].fs],s[i][j]);
            }
        }
        while(need+1<cur.size())if(cur[need]=='1')need++;else break;
        ll diff=min(vd);
        if(chmax(ans,need-70)){
            ansd=vd;
        }
        cnt++;
    }
    // puta(cnt);
    ll diff=min(ansd);
    rep(i,n)puta(ansd[i]-diff);

    return 0;
}