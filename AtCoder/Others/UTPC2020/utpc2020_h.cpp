// #pragma GCC target("avx")
// #pragma GCC optimize("O3,inline,omit-frame-pointer,no-asynchronous-unwind-tables,fast-math")
// #pragma GCC optimize("unroll-loops")

#define _USE_MATH_DEFINES
#ifndef _DEBUG
#define NDEBUG
#endif
#if defined(ONLINE_JUDGE) || defined(_DEBUG)
#include <atcoder/all>
using namespace atcoder;
#endif
#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/priority_queue.hpp>
#include <ext/pb_ds/tag_and_trait.hpp>

using namespace std;
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

#define all(a) a.begin(),a.end()
#define rall(a) a.rbegin(),a.rend()
#define rep(i,n) range(i,0,n)
#define rrep(i,n) rrange(i,0,n)
#define range(i,a,n) for(ll i=((ll)a);i<((ll)n);++i)
#define rrange(i,a,n) for(ll i=((ll)n-1);i>=((ll)a);--i)
#define repsq(i,n) for(ll i=0;i*i<=n;++i)
#define fcout(a) cout<<setprecision(a)<<fixed
constexpr ll LINF=1ll<<60;
constexpr int INF=1<<30;
constexpr double EPS=(1e-9);
constexpr ll MOD=1000000007ll;
constexpr double PI=3.1415926535897932384;

void Main();
int main(){cin.tie(nullptr);ios::sync_with_stdio(false);Main();return 0;}
template<class T>constexpr bool chmax(T&a,T b){return a<b?a=b,1:0;}
template<class T>constexpr bool chmin(T&a,T b){return a>b?a=b,1:0;}
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

//input
template<class S>auto&operator>>(istream&is,vector<S>&t){for(S&a:t)cin>>a;return is;}
template<typename...S>void geta_(S&...s){((cin>>s),...);}
#define geta(t,...) t __VA_ARGS__;geta_(__VA_ARGS__)

// ライブラリ貼るスペース


void Main(){
    geta(ll, h, w);
    vs s(h);cin>>s;

    vl a(h,0),b(w,0);
    rep(i,h)rep(j,w)if(s[i][j]=='#'){
        a[i]+=1;
        b[j]+=1;
    }
    dump(a);
    dump(b);

    int horizonWhite=0;
    int horizonBlack=0;
    int verticalWhite=0;
    int verticalBlack=0;
    bool ok=false;
    do{
        ok=false;
        if(horizonBlack+horizonWhite==h)goto next;
        if(verticalBlack+verticalWhite==w)goto next;
        if(h-horizonBlack-horizonWhite < w-verticalBlack-verticalWhite){
            rep(i,w){
                if(b[i]==-1)continue;
                if(b[i]-horizonBlack==0){
                    b[i]=-1;
                    verticalWhite++;
                    ok=true;
                    goto next;
                }
                if(b[i]+horizonWhite==h){
                    b[i]=-1;
                    verticalBlack++;
                    ok=true;
                    goto next;
                }
            }
            rep(i,h){
                if(a[i]==-1)continue;
                if(a[i]-verticalBlack==0){
                    a[i]=-1;
                    horizonWhite++;
                    ok=true;
                    goto next;
                }
                if(a[i]+verticalWhite==w){
                    a[i]=-1;
                    horizonBlack++;
                    ok=true;
                    goto next;
                }
            }
        }else{
            rep(i,h){
                if(a[i]==-1)continue;
                if(a[i]-verticalBlack==0){
                    a[i]=-1;
                    horizonWhite++;
                    ok=true;
                    goto next;
                }
                if(a[i]+verticalWhite==w){
                    a[i]=-1;
                    horizonBlack++;
                    ok=true;
                    goto next;
                }
            }
            rep(i,w){
                if(b[i]==-1)continue;
                if(b[i]-horizonBlack==0){
                    b[i]=-1;
                    verticalWhite++;
                    ok=true;
                    goto next;
                }
                if(b[i]+horizonWhite==h){
                    b[i]=-1;
                    verticalBlack++;
                    ok=true;
                    goto next;
                }
            }            
        }
        next:;
        dump(a);
        dump(b);
        dump(horizonBlack,horizonWhite,verticalBlack,verticalWhite);
    }while(ok);
    dump(horizonBlack,horizonWhite,verticalBlack,verticalWhite);
    puta(horizonBlack+horizonWhite+verticalBlack+verticalWhite);
}
