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



template<class T=ll>struct Matrix{
    ll h,w;
    vector<vector<T>> A;
    Matrix(ll n):Matrix(n,n){};
    Matrix(ll h,ll w):h(h),w(w),A(h,vector<T>(w,0)){};
    void get(){rep(i,h)rep(j,w)cin>>A[i][j];}

    using iterator=typename decltype(A)::iterator;
    using const_iterator=typename decltype(A)::const_iterator;
    iterator begin(){ return A.begin(); }
    const_iterator begin() const { return A.begin(); }
    iterator end(){ return A.end(); }
    const_iterator end() const { return A.end(); }

    vector<T> operator[](const int i) const {return A[i];}
    vector<T>& operator[](const int i){return A[i];}
    // Matrix op Matrix
    Matrix& operator=(const Matrix& B){assert(w==B.w&&h==B.h);rep(i,h)rep(j,w)A[i][j]=B[i][j];return *this;}
    Matrix& operator+=(const Matrix& B){assert(w==B.w&&h==B.h);rep(i,h)rep(j,w)A[i][j]+=B[i][j];return *this;}
    Matrix& operator-=(const Matrix& B){assert(w==B.w&&h==B.h);rep(i,h)rep(j,w)A[i][j]-=B[i][j];return *this;}
    Matrix& operator*=(const Matrix& B){assert(w==B.h);Matrix<T> tmp(h,B.w);rep(i,h)rep(j,B.w)rep(k,w){tmp[i][j]+=A[i][k]*B[k][j];}w=B.w;A=tmp.A;return *this;}
    Matrix operator+(const Matrix& B)const{return Matrix(*this)+=B;}
    Matrix operator-(const Matrix& B)const{return Matrix(*this)-=B;}
    Matrix operator*(const Matrix& B)const{return Matrix(*this)*=B;}
    bool operator==(const Matrix& B){assert(w==B.w&&h==B.h);bool ret=true;rep(i,h)rep(j,w)if(B[i][j]!=A[i][j])ret=false;return ret;}
    // Matrix op Scalr
    Matrix& operator+=(const T& K){rep(i,h)rep(j,w)A[i][j]+=K;return *this;}
    Matrix& operator-=(const T& K){rep(i,h)rep(j,w)A[i][j]-=K;return *this;}
    Matrix& operator*=(const T& K){rep(i,h)rep(j,w)A[i][j]*=K;return *this;}
    Matrix& operator/=(const T& K){rep(i,h)rep(j,w)A[i][j]/=K;return *this;}
    Matrix& operator%=(const T& K){rep(i,h)rep(j,w)A[i][j]%=K;return *this;}
    Matrix operator+(const T& K)const{return Matrix(*this)+=K;}
    Matrix operator-(const T& K)const{return Matrix(*this)-=K;}
    Matrix operator*(const T& K)const{return Matrix(*this)*=K;}
    Matrix operator/(const T& K)const{return Matrix(*this)/=K;}
    Matrix operator%(const T& K)const{return Matrix(*this)%=K;}

    static Matrix I(ll n){Matrix ret(n,n);rep(i,n)ret[i][i]=1; return ret;}
    Matrix<T> pow(ll K){
        assert(h==w);
        Matrix<T> C(h,w),ret(h,w);
        rep(i,h){rep(j,w)C[i][j]=A[i][j];ret[i][i]=1;}
        while(K>0){if(K&1)ret*=C; C*=C;K>>=1;}
        return ret;
    }
    T det() {
        assert(w==h);
        Matrix B(*this);
        T ret = 1;
        rep(i,w){
            int idx=-1; T vv;
            range(j,i,w)if(B[j][i])idx=j;
            if(idx==-1)return 0;
            if(i!=idx){ret*=-1;swap(B[i],B[idx]);}
            ret*=vv=B[i][i];
            rep(j,w)B[i][j]/=vv;
            range(j,i+1,w){
                T a=B[j][i];
                rep(k,w)B[j][k]-=B[i][k]*a;
            }
        }
        return ret;
    }
};
template<class T>void puta(Matrix<T>t){puta(t.A);}

void Main(){
    geta(ll, n);

    Matrix m(n);
    m.get();
    puta(m.det());

}
