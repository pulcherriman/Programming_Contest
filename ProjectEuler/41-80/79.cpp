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

// 73162890

ll len=LINF; string ans;
/*他のライブラリを入れる場所*/
string solve(string pass, vs slist){
    if(slist.size()==0){
        if(chmin(len, (ll)pass.size())){
            puta(pass.size(), pass);
            ans=pass;
        }
        return "";
    }
    if(pass.size()>len)return "-1";

    string ret(10000,'0');
    ll cnt=-1;vb ex(10,false);
    for(auto&s:slist){chmax(cnt, (ll)s.size());ex[s[0]-'0']=1;}
    if(cnt==1){
        ret="";
        rep(i,10)if(ex[i])ret+=to_string(i);
        return solve(pass+ret, vs());
    }
    bool isMod=false;
    for(auto c : "7012345689"){
        vs nxtlist;
        bool ok=false;
        for(auto&s:slist){
            if(s[0]==c){
                if(s.size()>1) nxtlist.push_back(s.substr(1));
                ok=true;
            }else if(s[0]!=c){
                nxtlist.push_back(s);
            }
        }
        if(!ok) continue;
        string v=solve(pass+c, nxtlist);
        if(v=="-1")continue;
        if(ret.size()>v.size()){
            isMod=true;
            ret=v;
        }
    }
    return ret;
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    ll n=50;
    vs s(n);cin>>s;
    puta(solve("",s));
    return 0;
}