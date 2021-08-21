#pragma region Perfect Template
#pragma region Unsecured Optimization
// #pragma GCC target("avx")
// #pragma GCC optimize("O3,inline,omit-frame-pointer,no-asynchronous-unwind-tables,fast-math")
// #pragma GCC optimize("unroll-loops")
#ifdef _DEBUG
#define _GLIBCXX_DEBUG 1
#endif
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
using vd=vector<ld>;
using vvd=vector<vd>;
using vi=vector<int>;
using vvi=vector<vi>;
using vl=vector<ll>;
using vvl=vector<vl>;
using pll=pair<ll,ll>;
using vp=vector<pll>;
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
#define __LOOPSWITCH(_1, _2, _3, __LOOPSWITCH, ...) __LOOPSWITCH
#define rep(...) __LOOPSWITCH(__VA_ARGS__, __RANGE, __REP, __LOOP) (__VA_ARGS__)
#define rrep(...) __LOOPSWITCH(__VA_ARGS__, __RRANGE, __RREP, __LOOP) (__VA_ARGS__)
#define __LOOP(q) __LOOP2(q, __LINE__)
#define __LOOP2(q,l) __LOOP3(q,l)
#define __LOOP3(q,l) __REP(_lp ## l,q)
#define __REP(i,n) __RANGE(i,0,n)
#define __RANGE(i,a,n) for(ll i=((ll)a);i<((ll)n);++i)
#define __RREP(i,n) __RRANGE(i,0,n)
#define __RRANGE(i,a,n) for(ll i=((ll)n-1);i>=((ll)a);--i)
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
template<class S,class T>auto&operator>>(istream&is,pair<S,T>&p){is>>p.first>>p.second;return is;}
template<class S>auto&operator>>(istream&is,vector<S>&t){for(S&a:t)is>>a;return is;}
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
template<class T>T gcd(vector<T> v){return accumulate(all(v),T(),gcd<T,T>);}
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





template <typename T> struct Matrix {
	int H, W;
	vector<T> elem;
	typename vector<T>::iterator operator[](int i) { return elem.begin() + i * W; }
	inline T &at(int i, int j) { return elem[i * W + j]; }
	inline T get(int i, int j) const { return elem[i * W + j]; }
	operator vector<vector<T>>() const {
		vector<vector<T>> ret(H);
		rep(i,H) copy(elem.begin()+i*W, elem.begin()+(i+1)*W, back_inserter(ret[i]));
		return ret;
	}
 
	Matrix() = default;
	Matrix(int N) : Matrix(N, N) {}
	Matrix(int H, int W) : H(H), W(W), elem(H * W) {}
	Matrix(const vector<vector<T>> &d) : H(d.size()), W(d.size() ? d[0].size() : 0) {
		for (auto &raw : d) copy(raw.begin(), raw.end(), back_inserter(elem));
	}
 
	static Matrix Identity(int N){ Matrix ret(N, N); rep(i,N)ret.at(i,i)=1; return ret; }
 
	Matrix operator-() const{ Matrix ret(H, W); rep(i,H*W)ret.elem[i]=-elem[i]; return ret; }
	Matrix operator*(const T &v) const { Matrix ret=*this; for(auto&x:ret.elem)x*=v; return ret; }
	Matrix operator/(const T &v) const { Matrix ret=*this; for(auto&x:ret.elem)x/=v; return ret; }
	Matrix operator+(const Matrix &r) const { Matrix ret=*this; rep(i,H*W)ret.elem[i]+=r.elem[i]; return ret;}
	Matrix operator-(const Matrix &r) const { Matrix ret=*this; rep(i,H*W)ret.elem[i]-=r.elem[i]; return ret; }
	Matrix operator*(const Matrix &r) const { Matrix ret(H, r.W); rep(i,H)rep(k,W)rep(j,r.W)ret.at(i, j)+=this->get(i, k)*r.get(k, j); return ret; }
	Matrix &operator*=(const T &v) { return *this=*this*v; }
	Matrix &operator/=(const T &v) { return *this=*this/v; }
	Matrix &operator+=(const Matrix &r) { return *this=*this+r; }
	Matrix &operator-=(const Matrix &r) { return *this=*this-r; }
	Matrix &operator*=(const Matrix &r) { return *this=*this*r; }
	bool operator==(const Matrix &r) const { return H == r.H && W == r.W && elem == r.elem; }
	bool operator!=(const Matrix &r) const { return !(*this==r); }
	bool operator<(const Matrix &r) const { return elem < r.elem; }
	Matrix pow(int64_t n) const {
		Matrix ret=Identity(H);
		if(n)rrep(i,64-__builtin_clzll(n)){ if(ret*=ret;(n>>i)&1)ret*=*this; }
		return ret;
	}
	// 転置
	Matrix transpose() const {
		Matrix ret(W, H);
		rep(i,H)rep(j,W)ret.at(j, i)=this->get(i, j);
		return ret;
	}
	// ガウスの掃き出し法 (整数でもdoubleにすること)
	// O(H^2 W)
	Matrix gauss_jordan() const {
		int c = 0;
		Matrix mtr(*this);
		vector<int> ws;
		ws.reserve(W);
		rep(h,H) {
			if (c == W) break;
			int piv = -1;
			rep(j,h,H)if(mtr.get(j, c)){piv=j; break;}
			if(piv==-1){c++; h--; continue;}
			if (h != piv)rep(w,W){
				swap(mtr[piv][w], mtr[h][w]);
				mtr.at(piv, w) *= -1;
			}
			ws.clear();
			rep(w,c,W)if(mtr.at(h, w)) ws.emplace_back(w);
			rep(hh,H)if(hh!=h){
				const T coeff=mtr.at(hh, c)/mtr.at(h, c);
				for(auto&w:ws)mtr.at(hh, w)-=mtr.at(h, w)*coeff;
			}
			c++;
		}
		return mtr;
	}
	// 掃き出し済みを仮定したランク
	// ランク=変数の個数なら唯一解、ランク<変数の個数なら不定解
	// 係数行列のランク!=拡大係数行列のランクの場合、この値にかかわらず解なし
	int rank_of_gauss_jordan() const { rrep(i,H*W)if(elem[i])return i/W+1; return 0; }
	// 上三角行列（=掃き出し済み）を仮定した行列式
	T determinant_of_upper_triangle() const { T ret=1; rep(i,H)ret*=get(i, i); return ret; }
	// 逆行列
	int inverse() {
		assert(H == W);
		vector<vector<T>> ret = Identity(H), tmp = *this;
		int rank = 0;
		rep(i,H) {
			int ti = i;
			while (ti < H and tmp[ti][i] == 0) ti++;
			if (ti == H) continue;
			rank++;
			ret[i].swap(ret[ti]), tmp[i].swap(tmp[ti]);
			T inv = tmp[i][i].inv();
			rep(j,W) ret[i][j] *= inv;
			rep(j,i+1,W) tmp[i][j] *= inv;
			rep(h,H)if(i!=h){
				const T c = -tmp[h][i];
				rep(j,W) ret[h][j] += ret[i][j] * c;
				rep(j,i+1,W) tmp[h][j] += tmp[i][j] * c;
			}
		}
		*this = ret;
		return rank;
	}
	friend vector<T> operator*(const Matrix &m, const vector<T> &v) {
		assert(m.W == int(v.size()));
		vector<T> ret(m.H);
		rep(i,m.H)rep(j,m.W) ret[i] += m.get(i, j) * v[j];
		return ret;
	}
	friend vector<T> operator*(const vector<T> &v, const Matrix &m) {
		assert(int(v.size()) == m.H);
		vector<T> ret(m.W);
		rep(i,m.H)rep(j,m.W) ret[j] += v[i] * m.get(i, j);
		return ret;
	}
	friend ostream &operator<<(ostream &os, const Matrix &x) {
		puta((vector<vector<T>>)x, os); return os;
	}
	friend istream &operator>>(istream &is, Matrix &x) {
		return is>>x.elem;
	}
};

struct P {
	int x; 
	P(): P(0){}
	P(int _x): x(_x%100){}
	friend ostream &operator<<(ostream &os, const P &p) {
		return os<<p.x;
	}
	P operator+=(P p){ x=(x+p.x)%100; return *this;}
	P operator*=(int p){ x=x*p%100; return *this;}
	P operator*(const P&p){ return P(x*p.x);}
};

#pragma endregion

void Main(){
	geta(int, n,x,y);
	vector<vector<P>> init = {{1, 1}, {1, 0}};
	Matrix<P> a(init);
	auto d=a.pow(n-2);
	puta((y*d[0][0].x + x*d[0][1].x)%100);
}