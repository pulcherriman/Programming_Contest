#include <bits/stdc++.h>
#ifdef ONLINE_JUDGE
#include <atcoder/all>
#endif

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
#define PI (3.1415926535897932384)

int dx[]={1,0,-1,0,1,-1,-1,1},dy[]={0,1,0,-1,1,1,-1,-1};
template<class T>bool chmax(T&a,T b){if(a<b){a=b; return true;}return false;}
template<class T>bool chmin(T&a,T b){if(a>b){a=b; return true;}return false;}
template<class S>S sum(vector<S>&a){return accumulate(all(a),S());}
template<class S>S max(vector<S>&a){return *max_element(all(a));}
template<class S>S min(vector<S>&a){return *min_element(all(a));}

//output
template<class T>struct hasItr{
    template<class U>static constexpr true_type check(class U::iterator*);
    template<class U>static constexpr false_type check(...);
    static constexpr bool v=decltype(check<T>(nullptr))::value;
};
template<>struct hasItr<string>{static constexpr bool v=false;};

template<class T>void puta(T&t,false_type,ostream&os,char el){os<<t;}
template<class T>void puta(T&t,true_type,ostream&os,char el){
    constexpr bool h=hasItr<typename T::value_type>::v;
    bool F=true,I;
    for(auto&i:t){
        if(!F)os<<' ';
        puta(i,bool_constant<h>(),os,el);
        F=I=h;
    }
    if(!I)os<<el;
}
template<class T>void puta(const T&t, ostream&os=cout, char el='\n'){
    puta(t,bool_constant<hasItr<T>::v>(),os,el);
    if(!hasItr<T>::v)os<<el;
}
template<class H,class...T>void puta(const H&h,const T&...t){cout<<h<<' ';puta(t...);}
template<size_t i,class...T>void puta(tuple<T...>const&t, ostream&os){
    if constexpr(i==sizeof...(T)-1)puta(get<i>(t),os);
    else{os<<get<i>(t)<<' ';puta<i+1>(t,os);}
}
template<class...T>void puta(tuple<T...>const&t, ostream&os=cout){puta<0>(t,os);}
template<class T>void dump(const T&t){puta(t,cerr);}
template<class H,class...T>void dump(const H&h,const T&...t){cerr<<h<<' ';dump(t...);}
template<class...T>void dump(tuple<T...>const&t){puta(t,cerr);}
template<class S,class T>constexpr ostream&operator<<(ostream&os,pair<S,T>p){
    os<<'['<<p.first<<", ";
    if constexpr(hasItr<T>::v)puta(p.second,bool_constant<true>(),os,']');
    else os<<p.second<<']';
    return os;
};
template<class...T>constexpr ostream&operator<<(ostream&os,tuple<T...>t){
    puta(t,os); return os;
}

void YN(bool b){puta(b?"YES":"NO");}
void Yn(bool b){puta(b?"Yes":"No");}
//input
template<class S>auto&operator>>(istream&is,vector<S>&t){for(S&a:t)cin>>a;return is;}
// #define geta(t,n,...) t n;cin>>n;geta(t,__VA_ARGS__)
// #define vec(t,a,h,...) vector<t>a(h);rep(i,n)a[i]=t(__VA_ARGS__);rep(i,n)cin>>a[i]
template<typename...S>void geta_(S&...s){((cin>>s),...);}

#define geta(t,...) t __VA_ARGS__;geta_(__VA_ARGS__)

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
    geta(ll, n, m);
    vl a(n);cin>>a;
    // 6,7,8,9
    // 1:0(特殊) 2:2(6,8) 3:2(6,9)
    vb exist(100001,0);
    rep(i,n)exist[a[i]]=1;
    vl cnt(100001,0);
    range(i,1,m+1){
        for(int v=i;v<=100000;v+=i){
            if(exist[v])cnt[i]++;
        }
        // for(auto p:Prime.Divisor(a[i])){
        //     if(p<=m)cnt[p]++;
        // }
    }

    cnt[1]=0;

    range(i,1,m+1){
        ll val=0;
        vl factor;
        for(auto[p,c]:Prime.Factorize(i)){
            factor.push_back(p);
        }
        // dump(factor);
        ll c=factor.size();
        range(s,1,1<<c){
            ll t=1;
            rep(j,c){
                if((s>>j)&1)t*=factor[j];
            }
            //tはm以下
            val += cnt[t] * (__builtin_popcount(s)%2==1 ? 1 : -1);
            // dump(i,"divisor",t,":",(__builtin_popcount(s)%2==1 ? "+" : "-"),cnt[t]);
        }
        puta(n-val);
    }
    return 0;
}