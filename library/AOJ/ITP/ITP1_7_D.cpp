// 行列
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
template<class T=ll>struct Matrix{
    ll h,w;
	vector<vector<T>> A;
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
	Matrix& operator*=(const Matrix& B){assert(w==B.h);Matrix<T> tmp(h,B.w);rep(i,h)rep(j,B.w)rep(k,w){tmp[i][j]=(tmp[i][j]+A[i][k]*B[k][j]%MOD)%MOD;w=B.w;A=tmp.A;return *this;}
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
		while(K>0){if(K&1){ret=ret*C%MOD;}C=C*C%MOD;K=K>>1;}
		return ret;
	}
    T determinant() {
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

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    
    geta(ll,n,m,l);
    Matrix a(n,m), b(m,l);
    a.get();
    b.get();
    
    puta(a*b);

    return 0;
}