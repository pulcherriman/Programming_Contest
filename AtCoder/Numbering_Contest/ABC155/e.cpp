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


int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    string s;
    cin>>s;
    ll n=s.size();
    s="0"+s;
    ll b=-1;

    vvl dp(n+1,vl(n+1,LINF));//i枚目まで見て、最後にj+1桁目で桁上がりしたときの答え
    dp[n][n]=s[n]-'0';
    // vl ans(n+1,LINF);
    rrep(i,n){
        dp[i]=dp[i+1];
        rep(j,n+1)dp[i][j]+=s[i]-'0';
        range(j,i+1,n+1){//i桁目で桁上がりする時
            ll v=dp[i+1][j];//最後にj+1で桁上がり
            puta("start", i, j, v);
            range(k,i+1,j+1){
                v-=s[k]-'0';
                if(k)v+=9-(s[k]-'0');
            }
            puta(v);
            v+=s[i]-'0'+2;
            // if(j!=n)v-=s[j+1]-'0'+2;
            puta(i,j,v);
            chmin(dp[i][i], v);
        }
        puta(dp[i]);
    }
    puta(min(dp[0]));

    // ll ds=0;
    // rep(i,n+1)ds+=s[i]-'0';
    // rrep(i,n){
    //     // if(s[i+1]=='0')continue;
    //     ll p1=s[i+1]-'0'; ll p2=0, b2=10-p1,diff=0;
    //     string s2=s;
    //     while(true){
    //         p1+=s[i]-'0';
    //         s2[i+1]='0';
    //         if(s[i]!='9'){
    //             p2 += s[i]-'0'+1;
    //             s2[i]++;
    //             break;
    //         }else{
    //             i--;
    //             diff++;
    //         }
    //     }
    //     i+=diff;
    //     puta(s[i],s[i+1]);
    //     puta(s2);
    //     puta(p1,0,p2,b2);
    //     if(p1>p2+b2){//上げたほうがいい
    //         ds -= (p1-p2-b2);
    //         s=s2;
    //         i-=diff;
    //     }
    //     puta(s,ds);
    //     // if(s[i]+s[i+1]<=)
    // }
    return 0;
}