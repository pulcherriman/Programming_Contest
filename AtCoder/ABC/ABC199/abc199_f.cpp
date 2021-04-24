#pragma region Perfect Template
#pragma region Unsecured Optimization
// #pragma GCC target("avx")
// #pragma GCC optimize("O3,inline,omit-frame-pointer,no-asynchronous-unwind-tables,fast-math")
// #pragma GCC optimize("unroll-loops")
#pragma endregion

#pragma region Include Headers
#if defined(ONLINE_JUDGE) || defined(_DEBUG)
#include <atcoder/all>
using namespace atcoder;
#endif
#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;

void Main();
int main(){cin.tie(nullptr);ios::sync_with_stdio(false);Main();return 0;}
#pragma endregion

#pragma region Additional Type Definition
using ll=long long;
using ld=long double;
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
template<class K> using IndexedSet=__gnu_pbds::tree<K,__gnu_pbds::null_type,less<K>,__gnu_pbds::rb_tree_tag,__gnu_pbds::tree_order_statistics_node_update>;
template<class K> using HashSet=__gnu_pbds::gp_hash_table<K,__gnu_pbds::null_type>;
template<class K,class V> using IndexedMap=__gnu_pbds::tree<K,V,less<K>,__gnu_pbds::rb_tree_tag,__gnu_pbds::tree_order_statistics_node_update>;
template<class K,class V> using HashMap=__gnu_pbds::gp_hash_table<K,V>;
#pragma endregion

#pragma region Macros
#define all(a) a.begin(),a.end()
#define rall(a) a.rbegin(),a.rend()
#define loop(q) __loop(q, __LINE__)
#define __loop(q,l) __loop2(q,l)
#define __loop2(q,l) rep(_lp ## l,q)
#define rep(i,n) range(i,0,n)
#define rrep(i,n) rrange(i,0,n)
#define range(i,a,n) for(ll i=((ll)a);i<((ll)n);++i)
#define rrange(i,a,n) for(ll i=((ll)n-1);i>=((ll)a);--i)
#define repsq(i,n) for(ll i=0;i*i<=n;++i)
#define each(v,a) for(auto v:a)
#define eachref(v,a) for(auto&v:a)
#define fcout(a) cout<<setprecision(a)<<fixed
#pragma endregion

#pragma region Constants
constexpr ll LINF=1ll<<60;
constexpr int INF=1<<30;
constexpr double EPS=(1e-9);
constexpr ll MOD=1000000007ll;
constexpr long double PI=3.14159265358979323846;
#pragma endregion

#pragma region Output Assist
template<class T>struct hasItr{
    template<class U>static constexpr true_type check(class U::iterator*);
    template<class U>static constexpr false_type check(...);
    static constexpr bool v=decltype(check<T>(nullptr))::value;
};
template<>struct hasItr<string>{static constexpr bool v=false;};

template<class T>void puta(T&t,false_type,ostream&os,[[maybe_unused]]char el){os<<t;}
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
template<class S,class T>constexpr ostream&operator<<(ostream&os,pair<S,T>p){
    os<<'['<<p.first<<", ";
    if constexpr(hasItr<T>::v)puta(p.second,bool_constant<true>(),os,']');
    else os<<p.second<<']';
    return os;
};
template<class...T>constexpr ostream&operator<<(ostream&os,tuple<T...>t){puta(t,os); return os;}
void YN(bool b){puta(b?"YES":"NO");}
void Yn(bool b){puta(b?"Yes":"No");}

#ifdef _DEBUG
template<class T>void dump_f(const T&t){puta(t,cerr);}
template<class H,class...T>void dump_f(const H&h,const T&...t){cerr<<h<<' ';dump_f(t...);}
template<class...T>void dump_f(tuple<T...>const&t){puta(t,cerr);}
#define dump(...)cerr<<"  "<<string(#__VA_ARGS__)<<": ["<<to_string(__LINE__)<<":"<<__FUNCTION__<<"]\n    ",dump_f(__VA_ARGS__)
#else
#define dump(...)                                                              
#endif
#pragma endregion

#pragma region Input Assist
template<class S>auto&operator>>(istream&is,vector<S>&t){for(S&a:t)cin>>a;return is;}
template<typename...S>void geta_(S&...s){((cin>>s),...);}
#define geta(t,...) t __VA_ARGS__;geta_(__VA_ARGS__)
template<class T,class...Args>auto vec(T x,int arg,Args...args){if constexpr(sizeof...(args)==0)return vector(arg,x);else return vector(arg,vec(x,args...));}
#define getv(a,...) auto a=vec(__VA_ARGS__);cin>>a
#pragma endregion

#pragma region Utilities
template<class T>constexpr bool chmax(T&a,T b){return a<b?a=b,1:0;}
template<class T>constexpr bool chmin(T&a,T b){return a>b?a=b,1:0;}
template<class S>S sum(vector<S>&a){return accumulate(all(a),S());}
template<class S>S max(vector<S>&a){return *max_element(all(a));}
template<class S>S min(vector<S>&a){return *min_element(all(a));}
template<class T> pair<int,T> getMaxAndIndex(vector<T> a){
    int p=-1; T v=numeric_limits<T>::min();
    rep(i,a.size())if(chmax(v,a[i]))p=i;
    return {p,v};
}
#pragma endregion
#pragma endregion

// ここにライブラリを貼る
// regionのfoldは[Ctrl+K] => [Ctrl+8] expandは9
#pragma region Additional Libraries
int mpow(int v, ll a) {
    ll x = v, n = a, res = 1;
    while ( n ) {
        if ( n & 1 )res = res*x%MOD;
        x = x*x%MOD;
        n >>= 1;
    }
    return res;
}

class mymint {
private:
    ll v;
public:
    static ll mod(ll a) { return ( a % MOD + MOD ) % MOD; }
    mymint(ll a = 0) { this->v = mod(a); };
    mymint(const mymint &a) { v = a.v; }
    mymint operator+(const mymint &a) { return mymint(v + a.v); }
    mymint operator+(const ll a) { return mymint(v + a % MOD); }
    mymint operator+(const signed a) { return mymint(v + a % MOD); }
    friend mymint operator+(const ll a, const mymint &b) { return mymint(a % MOD + b.v); }
    void operator+=(const mymint &a) { v = ( v + a.v ) % MOD; }
    void operator+=(const ll a) { v = mod(v + a % MOD); }
    void operator+=(const signed a) { v = mod(v + a % MOD); }
    friend void operator+=(ll &a, const mymint &b) { a = mod(a % MOD + b.v); }
    mymint operator-(const mymint &a) { return mymint(v - a.v); }
    mymint operator-(const ll a) { return mymint(v - a % MOD); }
    mymint operator-(const signed a) { return mymint(v - a % MOD); }
    friend mymint operator-(const ll a, const mymint &b) { return mymint(a % MOD - b.v); }
    void operator-=(const mymint &a) { v = mod(v - a.v); }
    void operator-=(const ll a) { v = mod(v - a % MOD); }
    void operator-=(const signed a) { v = mod(v - a % MOD); }
    friend void operator-=(ll &a, const mymint &b) { a = mod(a % MOD - b.v); }
    mymint operator*(const mymint &a) { return mymint(v * a.v); }
    mymint operator*(const ll a) { return mymint(v * ( a % MOD )); }
    mymint operator*(const signed a) { return mymint(v * ( a % MOD )); }
    friend mymint operator*(const ll a, const mymint &b) { return mymint(a % MOD * b.v); }
    void operator*=(const mymint &a) { v = ( v * a.v ) % MOD; }
    void operator*=(const ll a) { v = mod(v * ( a % MOD )); }
    void operator*=(const signed a) { v = mod(v * ( a % MOD )); }
    friend void operator*=(ll &a, const mymint &b) { a = mod(a % MOD * b.v); }
    mymint operator/(const mymint &a);
    mymint operator/(const ll a);
    mymint operator/(const signed a);
    friend mymint operator/(const ll a, const mymint &b);
    void operator/=(const mymint &a);
    void operator/=(const ll a);
    void operator/=(const signed a);
    friend void operator/=(ll &a, const mymint &b);
    mymint operator^(const mymint &a) { return mpow(v, a.v); };
    mymint operator^(const ll a) { return mpow(v, a); };
    mymint operator^(const signed a) { return mpow(v, a); };
    friend mymint operator^(const ll a, const mymint &b) { return mpow(a, b.v); };
    void operator^=(const mymint &a) { v = mpow(v, a.v); }
    void operator^=(const ll a) { v = mpow(v, a); }
    void operator^=(const signed a) { v = mpow(v, a); }
    mymint operator+() { return *this; }
    mymint operator++() { v++; return *this; }
    mymint operator++(signed d) { mymint res = *this; v++; return res;}
    mymint operator-() { return operator*(-1); }
    mymint operator--() { v--; return *this; }
    mymint operator--(signed d) { mymint res = *this; v--; return res;}
    bool operator==(mymint &a) { return v == a.v; }
    bool operator==(signed a) { return v == a; }
    friend bool operator==(signed a, mymint &b) { return a == b.v; }
    bool operator!=(mymint &a) { return v != a.v; }
    bool operator!=(signed a) { return v != a; }
    friend bool operator!=(signed a, mymint &b) { return a != b.v; }
    operator int() { return v; }
};
const int setModMax = 510000;
mymint fac[setModMax], finv[setModMax], inv[setModMax];
void setMod() {
    fac[0] = fac[1] = finv[0] = finv[1] = inv[1] = 1;
    for ( int i = 2; i < setModMax; i++ ) {
        fac[i] = fac[i - 1] * i % MOD;
        inv[i] = MOD - inv[MOD % i] * ( MOD / i ) % MOD;
        finv[i] = finv[i - 1] * inv[i] % MOD;
    }
}
mymint minv(ll a) {
    if ( fac[0] == 0 )setMod();
    if ( a < setModMax ) return inv[a];
    a %= MOD;
    ll b = MOD, x = 1, y = 0;
    while ( b ) {
        ll t = a / b;
        a -= t*b; swap(a, b);
        x -= t*y; swap(x, y);
    }
    return ( x % MOD + MOD ) % MOD;
}

mymint mymint::operator/(const mymint &a) { return mymint(v * minv(a.v)); }
mymint mymint::operator/(const ll a) { return mymint(v * minv(a)); }
mymint mymint::operator/(const signed a) { return mymint(v * minv(a)); }
mymint operator/(const ll a, const mymint &b) { return mymint(a % MOD * minv(b.v)); }
void mymint::operator/=(const mymint &a) { v = ( v * minv(a.v) ) % MOD; }
void mymint::operator/=(const ll a) { v = mod(v * minv(a)); }
void mymint::operator/=(const signed a) { v = mod(v * minv(a)); }
void operator/=(ll &a, const mymint &b) { a = mymint::mod(a % MOD * minv(b.v)); }
auto&operator>>(istream&is,mymint&t){ll a; cin>>a; t=a; return is;};
auto&operator<<(ostream&os,mymint&t){cout<<((int)t); return os;};
mymint operator"" _m(unsigned long long a){return mymint(a);}
using vm=vector<mymint>;
using vvm=vector<vm>;
mymint nCr(ll n,ll r){
    if ( fac[0] == 0 )setMod();
    return fac[n]*finv[r]*finv[n-r];
}


template<class T=ll>struct Graph{
    int size;
    T INF_VAL;
    vector<vector<tuple<ll,T>>>edge;
    Graph(int n=1,T inf=LINF):size(n),INF_VAL(inf){edge.resize(size);}
    void add(ll from, ll to, T cost, bool directed=false){
        edge[from].emplace_back(to,cost);
        if(!directed) edge[to].emplace_back(from,cost);
    }
    virtual void show(){
        rep(i,size)for(auto&[from,val]:edge[i])
            puta(i,"=>",from,", cost :",val);
    }
};

template<class T=ll>struct GraphSearchBase{
    Graph<T> g;
    GraphSearchBase(Graph<T> g):g(g){}
    vector<T>calc(int s){
        vector<T> ret(g.size,g.INF_VAL);
        ret[push(s)]=0;
        while(!q.empty()){
            int p=pop();
            for(auto&[to,cost]:g.edge[p])if(ret[to]==g.INF_VAL)ret[push(to)]=ret[p]+cost;
        }
        return ret;
    }
    pair<T, vi> calc(int s, int t){
        auto result=calc(s);
        if(result[t]==g.INF_VAL)return {g.INF_VAL,vi()};
        vi path(1,t);
        while(t!=s)for(auto&[to,_]:g.edge[t])if(result[t]>result[to]){path.push_back(t=to); break;}
        reverse(all(path));
        return {result[path.back()],path};
    }
protected:
    deque<int> q;
    virtual int push(int s) = 0;
    virtual int pop() = 0;
};

template<class T=ll>struct BFS : public GraphSearchBase<T>{
    BFS(Graph<T> g):GraphSearchBase<T>(g){}
protected:
    int push(int s){ return this->q.emplace_back(s);}
    int pop(){
        int v=this->q.front();
        this->q.pop_front();
        return v;
    }
};

template<class T=ll>struct DFS : public GraphSearchBase<T>{
    DFS(Graph<T> g):GraphSearchBase<T>(g){}
protected:
    int push(int s){ return this->q.emplace_front(s); }
    int pop(){
        int v=this->q.back();
        this->q.pop_back();
        return v;
    }
};

struct GridGraph : public Graph<int>{
    int h,w;
    vs field;
    GridGraph(int h, int w):Graph(1,0),h(h),w(w){field.resize(h);}
    void input(bool needOutline=true){
        rep(i,h)cin>>field[i];
        if(needOutline){
            field.resize(h+2);
            rrep(i,h)field[i+1]='#'+field[i]+'#';
            field[0]=field[h+1]=string(w+2,'#');
            h+=2; w+=2;
        }
        create();
    }
    void create(){
        edge.clear();
        edge.resize(size=h*w);
        range(i,1,h-1)range(j,1,w-1)if(field[i][j]=='.'){
            if(field[i+1][j]=='.')add(pos2index(i,j,w), pos2index(i+1,j,w), 1);
            if(field[i][j+1]=='.')add(pos2index(i,j,w), pos2index(i,j+1,w), 1);
        }
    }
    void show() override{ each(s,field)puta(s); }
private:
    static constexpr int pos2index(int y, int x, int w){ return y*w+x; }
};

template<class T=ll>struct Tree : public Graph<T>{
    Tree(int n, T inf=LINF):Graph<T>(n,inf){}

    pair<T,vi> diameter(){
        if(_diameter.first==this->INF_VAL){
            BFS bfs(*this);
            auto [s,_]=getMaxAndIndex(bfs.calc(0));
            auto [t,w]=getMaxAndIndex(bfs.calc(s));
            _diameter=bfs.calc(s,t);
        }
        return _diameter;
    }
private:
    pair<T,vi> _diameter = {this->INF_VAL, vi()};
};

#pragma endregion
// int mpow(int v, ll a) {
//     ll x = v, n = a, res = 1;
//     while ( n ) {
//         if ( n & 1 )res = res*x%MOD;
//         x = x*x%MOD;
//         n >>= 1;
//     }
//     return res;
// }


vvm gpow(vvm v, ll a) {
    ll c=v.size();
    vvm x=v, res=vvm(c,vm(c,0)); ll n = a;
    rep(i,c)res[i][i]=1;
    while ( n ) {
        if ( n & 1 ){
            vvm r=vvm(c,vm(c,0));
            rep(i,c)rep(j,c)rep(k,c){
                r[i][k]+=res[i][j]*x[j][k];
            }
            res=r;
        }
        {
            vvm r=vvm(c,vm(c,0));
            rep(i,c)rep(j,c)rep(k,c){
                r[i][k]+=x[i][j]*x[j][k];
            }
            x=r;
        }
        n >>= 1;
    }
    return res;
}



void Main(){
    geta(ll, n,m,k);
    getv(a,0ll,n);
    Graph g(n);
    rep(i,m){
        geta(ll,x,y);
        x--;y--;
        g.add(x,y,1);
    }
    vvm v(n, vm(n,0));
    rep(i,n){
        v[i][i]=(m-g.edge[i].size())*2;
        for(auto&[to,_]:g.edge[i]){
            v[to][i]+=1;
            v[i][i]+=1;
        }
    }
    rep(i,n)rep(j,n)v[i][j]/=2*m;
    // rep(i,n)rep(j,n)puta((ll)v[i][j]);puta("===");
    v=gpow(v,k);
    // rep(i,n)rep(j,n)puta((ll)v[i][j]);puta("===");
    rep(i,n){
        mymint ans=0;
        rep(j,n)ans+=a[j]*v[i][j];
        puta((ll)ans);
    }
}
