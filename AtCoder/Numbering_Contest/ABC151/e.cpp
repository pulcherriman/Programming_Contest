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
template<int _MOD>struct modint{
    ll val;
    constexpr static int setModMax = 510000;
    static modint<_MOD> fac[setModMax], finv[setModMax], inv[setModMax];

    static constexpr ll mod(ll a){return(a%_MOD+_MOD)%_MOD;}
    constexpr modint(ll v = 0)noexcept:val(v%_MOD){
        if(val<0)v+=_MOD;
    }
    constexpr int getmod(){return _MOD;}
    constexpr modint operator-()const noexcept{return val?_MOD-val:0;}
    constexpr modint operator+(const modint&r)const noexcept{return modint(*this)+=r;}
    constexpr modint operator-(const modint&r)const noexcept{return modint(*this)-=r;}
    constexpr modint operator*(const modint&r)const noexcept{return modint(*this)*=r;}
    constexpr modint operator/(const modint&r)const noexcept{return modint(*this)/=r;}
    constexpr modint operator^(const modint&r)const noexcept{return modint(*this)^=r;}
    constexpr modint&operator+=(const modint&r)noexcept{val=mod(val+r.val);return*this;}
    constexpr modint&operator-=(const modint&r)noexcept{val=mod(val-r.val);return*this;}
    constexpr modint&operator*=(const modint&r)noexcept{val=mod(val*r.val);return*this;}
    constexpr modint&operator/=(const modint&r)noexcept{
        ll a=r.val,b=_MOD,u=1,v=0;while(b){ll t=a/b;a-=t*b;swap(a,b);u-=t*v;swap(u,v);}
        val=val*u%_MOD;if(val<0)val+=_MOD;return*this;}
    constexpr modint&operator^=(const modint&r)noexcept{val=modpow(val,r.val).val;return*this;}
    constexpr bool operator<(const modint&r)const noexcept{return this->val<r.val;}
    constexpr bool operator>(const modint&r)const noexcept{return r<*this;}
    constexpr bool operator!=(const modint&r)const noexcept{return *this<r||*this>r;}
    constexpr bool operator==(const modint&r)const noexcept{return !(*this!=r);}
    constexpr bool operator<=(const modint&r)const noexcept{return !(*this>r);}
    constexpr bool operator>=(const modint&r)const noexcept{return !(*this<r);}
    friend constexpr ostream&operator<<(ostream&os,const modint<_MOD>&x)noexcept{return os<<x.val;}
    friend constexpr istream&operator>>(istream&is,modint<_MOD>&x)noexcept{return is>>x.val;}
    constexpr modint<_MOD>modpow(const modint<_MOD>&a,ll n)noexcept{
        if(n==0)return 1;auto t=modpow(a,n/2);t*=t;if(n&1)t*=a;return t;}
    friend modint<_MOD>operator+(const ll a,const modint&b){return modint(a)+=b;}
    friend void operator+=(ll&a,const modint&b){a=modint(a)+b;}
    friend modint<_MOD>operator-(const ll a,const modint&b){return modint(a)-=b;}
    friend void operator-=(ll&a,const modint&b){a=modint(a)-b;}
    friend modint<_MOD>operator*(const ll a,const modint&b){return modint(a)*=b;}
    friend void operator*=(ll&a,const modint&b){a=modint(a)*b;}
    friend modint<_MOD>operator/(const ll a,const modint&b){return modint(a)/=b;}
    friend void operator/=(ll&a,const modint&b){a=modint(a)/b;}
    friend modint<_MOD>operator^(const ll a,const modint&b){return modint(a)^=b;}
    friend void operator^=(ll&a,const modint&b){a=modint(a)^b;}
};
using mint = modint<MOD>;
using vm = vector<mint>;
using vvm = vector<vm>;
mint operator""_m(unsigned long long a){return mint(a);}
mint nCr(ll n,ll r){
    const static int setModMax = 510000;
    static mint fac[setModMax],finv[setModMax],inv[setModMax];
    if(fac[0]==0){
        fac[0]=fac[1]=finv[0]=finv[1]=inv[1]=1;
        for(int i=2;i<setModMax;i++) {
            fac[i]=fac[i-1]*i;
            inv[i]=-inv[MOD%i]*(MOD/i);
            finv[i]=finv[i-1]*inv[i];
        }
    }
    return fac[n]*finv[r]*finv[n-r];
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    ll n,k;
    cin>>n>>k;
    mint ans=0;
    vm a(n);
    cin>>a;
    sort(all(a));
    rep(i,n){
        ll v=i, r=k-1;
        if(v>=r)ans+=a[i]*nCr(v,r);
    }
    rep(i,n){
        ll v=n-i-1, r=k-1;
        if(v>=r)ans-=a[i]*nCr(v,r);
    }
    puta(ans);
    return 0;
}