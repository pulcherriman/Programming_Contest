#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using ull=unsigned long long;
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
struct _Prime{
    bool IsPrime(ll n){
        if(n<2)return false;
        if(~n&1)return n==2;
        if(n<=INT_MAX)return IsPrime<int,ll>(n);
        return IsPrime<ll,__int128_t>(n);
    }
    map<ll,int> Factorize(ll n){
        map<ll,int> r;
        if(n!=1){
            ll x=pollard_single(n);
            if(x==n)r[x]=1;
            else{
                r=Factorize(x);
                for(auto&v:Factorize(n/x))r[v.first]+=v.second;
            }
        }
        return r;
    }
    vl Divisor(ll n){
        vl r(1,1);
        for(auto[v,c]:Factorize(n)){
            ll l=r.size();
            rep(i,l)rep(j,c)r.push_back(r[i]*pmod(v,j+1,LLONG_MAX));
        }
        return r;
    }

    private:
    template<class T>static constexpr int arr[]={2,7,61};

    template<class T,class U>
    static T pmod(T x,U n,T p) {
        T r=1%p;
        while(x%=p,n){if(n&1)r=r*x%p;x*=x;n>>=1;}
        return r;
    }
    template<class T,class U>static bool IsPrime(T n){
        for(int a:arr<T>){
            bool c=true;
            ll m=n-1;
            while(~m&1)c&=pmod<U>(a,m>>=1,n)!=n-1;
            c&=pmod<U>(a,m?:1,n)!=1;
            if(c)return n<=a;
        }
        return true;
    }

    ll fast_gcd(ll _a, ll _b) {
        ll a=abs(_a),b=abs(_b);
        if(a==0||b==0)return a+b;
        int n=__builtin_ctzll(a),m=__builtin_ctzll(b);
        a>>=n;b>>=m;
        while(a!=b){
            int x=__builtin_ctzll(a-b);
            ll c=a>b?a:b;
            a=(c-=b=a>b?b:a)>>x;
        }
        return a<<min(n,m);
    }
    ll pollard_single(ll n){
        const static auto f=[&](ll x){return(__int128_t(x)*x+1)%n;};
        if(~n&1)return 2;
        if(IsPrime(n))return n;
        ll st=0;
        while(true){
            ll x=++st,y=f(x);
            while(true){
                ll p=fast_gcd(y-x+n,n);
                if(p==0||p==n)break;
                if(p!=1)return p;
                x=f(x);
                y=f(f(y));
            }
        }
    }
};
template<>constexpr int _Prime::arr<ll>[]={2,325,9375,28178,450775,9780504,1795265022};
_Prime Prime;


int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);

    ll n; cin>>n;
    rep(i,n){
        ll t; cin>>t;
        auto f = Prime.Factorize(t);
        
        ll c=0;
        for(auto p:f)c+=p.second;

        vl ans(1,c);
        for(auto p:f){
            rep(j,p.second) ans.push_back(p.first);
        }
        puta(ans);
    }
    return 0;

}