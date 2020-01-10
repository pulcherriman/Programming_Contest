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
// 376

vl lank(vl h){
    vl ret;
    vl pair(5,-1); bool p2=false;
    rep(i,13){
        ll v=0; rep(j,5)if(h[j]%13==i)v++;
        if(v==2 and pair[v]!=-1) p2=true;
        chmax(pair[v],i);
    }
    if(pair[4]!=-1){ret.push_back(7); ret.push_back(pair[4]);}
    else if(pair[3]!=-1 and pair[2]!=-1){ret.push_back(6); ret.push_back(pair[3]);}
    else if(pair[3]!=-1){ret.push_back(3); ret.push_back(pair[3]);}
    else if(p2){ret.push_back(2); ret.push_back(pair[2]);}
    else if(pair[2]!=-1){ret.push_back(1); ret.push_back(pair[2]);}
    else {
        bool same=true;
        rep(i,4)same&=(h[0]/13==h[i+1]/13);
        ll straight=-1;
        rep(i,5)h[i]%=13; sort(all(h));
        if(h[4]-h[0]==4)straight=h[0];
        if(same){
            if(straight==8){ret.push_back(9); ret.push_back(h[4]);}
            else if(straight!=-1){ret.push_back(8); ret.push_back(h[4]);}
            else {ret.push_back(5); ret.push_back(h[4]);}
        }else if (straight!=-1) {ret.push_back(4); ret.push_back(h[4]);}
        else {ret.push_back(0); ret.push_back(h[4]);}
    }
    rep(i,5)ret.push_back(h[4-i]);

    return ret;
}

vl get(){
    map<char,ll> suit;
    suit['A']=12; suit['2']=0; suit['3']=1;
    suit['4']=2; suit['5']=3; suit['6']=4;
    suit['7']=5; suit['8']=6; suit['9']=7;
    suit['T']=8; suit['J']=9; suit['Q']=10; suit['K']=11;
    suit['C']=0; suit['H']=13; suit['S']=26; suit['D']=39;
    
    vs s(5); cin>>s;
    vl ret(5,0);
    rep(i,5){
        ret[i]+=suit[s[i][0]];
        ret[i]+=suit[s[i][1]];
    }

    puta(s);
    puta(lank(ret));
    return lank(ret);
}


int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    ll n=1000, ans=0;
    rep(_,n){
        auto h1 = get();
        auto h2 = get();
        if(h1>h2) ans++;
        Yn(h1>h2);
        puta("====");
        // if(_==4)break;
    }
    puta(ans);
    return 0;
}