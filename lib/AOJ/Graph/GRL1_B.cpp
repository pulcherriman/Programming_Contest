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

void YN(bool b){puta(b?"YES":"NO");}
void Yn(bool b){puta(b?"Yes":"No");}
//input
template<class S>auto&operator>>(istream&is,vector<S>&t){for(S&a:t)cin>>a;return is;}
// #define geta(t,n,...) t n;cin>>n;geta(t,__VA_ARGS__)
// #define vec(t,a,h,...) vector<t>a(h);rep(i,n)a[i]=t(__VA_ARGS__);rep(i,n)cin>>a[i]
template<typename...S>void geta_(S&...s){((cin>>s),...);}

#define geta(t,...) t __VA_ARGS__;geta_(__VA_ARGS__)

/*他のライブラリを入れる場所*/
template<class T=ll>struct Graph{
    int size;
    T INF_VAL;
    vector<vector<tuple<ll,T>>>edge;
    Graph(int n=1,T inf=LINF):size(n),INF_VAL(inf){edge.resize(size);}
    void add(ll from, ll to, T cost, bool directed=false){
        edge[from].emplace_back(to,cost);
        if(!directed) edge[to].emplace_back(from,cost);
    }
    void dump(){
        rep(i,size)for(auto&[from,val]:edge[i])
            puta(i,"=>",from,", cost :",val);
    }
};

template<class T=ll>struct BellmanFord{
    Graph<T> g;
    BellmanFord(Graph<T> g):g(g){}
    pair<bool,vector<T>> dist(ll s){
        bool isNegativeCycle=false;
        vector<T> ret(g.size,g.INF_VAL);
        ret[s]=0;
        rep(i,2*g.size){
            rep(f,g.size)for(auto&[t,c]:g.edge[f]){
                if(ret[f]!=g.INF_VAL && chmin(ret[t],ret[f]+c) && i+1>=g.size){
                    isNegativeCycle = true;
                    ret[t]=-g.INF_VAL;
                }
            }
        }
        return {isNegativeCycle, ret};
    }
    pair<bool,T> dist(ll s,ll t){auto[nega,ret]=dist(s); return {nega,ret[t]};}
};

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);

    geta(ll,n,m,r);

    Graph g(n);
    rep(i,m){
        geta(ll,a,b,d);
        g.add(a,b,d,true);
    }

    auto[nega,ans]=BellmanFord(g).dist(r);
    if(nega){
        puta("NEGATIVE CYCLE");
        return 0;
    }

    for(auto v:ans){
        if(v==LINF)puta("INF");
        else puta(v);
    }

    return 0;
}