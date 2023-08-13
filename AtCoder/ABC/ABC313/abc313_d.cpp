// @prefix _template
// @description 新テンプレート

#ifdef _DEBUG
// #define _GLIBCXX_DEBUG 1
#else
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("inline")
#endif

/* 
 * Include Headers
 */
#if defined(EVAL) || defined(ONLINE_JUDGE) || defined(_DEBUG)
// #include <atcoder/all>
// using namespace atcoder;
#endif
#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;

/*
 * Additional Type Definition
 */
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
using pii=pair<int,int>;
using pll=pair<ll,ll>;
using vp=vector<pll>;
using tl2=tuple<ll,ll>;
using tl3=tuple<ll,ll,ll>;
using vs=vector<string>;
template<class K> using IndexedSet=__gnu_pbds::tree<K,__gnu_pbds::null_type,less<K>,__gnu_pbds::rb_tree_tag,__gnu_pbds::tree_order_statistics_node_update>;
template<class K> using HashSet=__gnu_pbds::gp_hash_table<K,__gnu_pbds::null_type,hash<K>>;
template<class K,class V> using IndexedMap=__gnu_pbds::tree<K,V,less<K>,__gnu_pbds::rb_tree_tag,__gnu_pbds::tree_order_statistics_node_update>;
template<class K,class V> using HashMap=__gnu_pbds::gp_hash_table<K,V,hash<K>>;
template<class V> using minpq = priority_queue<V, vector<V>, greater<V>>;

#define all(a) begin(a),end(a)
#define rall(a) rbegin(a),rend(a)
#define __LOOPSWITCH(_1, _2, _3, __LOOPSWITCH, ...) __LOOPSWITCH
#define rep(...) __LOOPSWITCH(__VA_ARGS__, __RANGE, __REP, __LOOP) (__VA_ARGS__)
#define rrep(...) __LOOPSWITCH(__VA_ARGS__, __RRANGE, __RREP, __LOOP) (__VA_ARGS__)
#define __LOOP(q) __LOOP2(q, __LINE__)
#define __LOOP2(q,l) __LOOP3(q,l)
#define __LOOP3(q,l) __REP(_lp ## l,q)
#define __REP(i,n) __RANGE(i,0,n)
#define __RANGE(i,a,n) for(ll i=((ll)a);i<((ll)n);++i)
#define __RREP(i,n) __RRANGE(i,0,n)
#define __RRANGE(i,a,n) for(ll i=((ll)(n)-1);i>=((ll)a);--i)
#define sz(a) ((ll)(a).size())
#define pb push_back
#define eb emplace_back

/*
 * Constants
 */
constexpr ll LINF=1ll<<60;
constexpr int INF=1<<30;
constexpr double EPS=(1e-14);
constexpr ll MOD=998244353ll;
constexpr long double PI=3.14159265358979323846;

/*
 * Utilities
 */
template<class T,class...Args>auto vec(T x,int arg,Args...args){
	if constexpr(sizeof...(args)==0) return vector(arg,x);
	else return vector(arg,vec(x,args...));
}
template<class T>constexpr bool chmax(T&a,T b){return a<b?a=b,1:0;}
template<class T>constexpr bool chmin(T&a,T b){return a>b?a=b,1:0;}
template<class S>S sum(vector<S>&a){return accumulate(all(a),S());}
template<class S>S max(vector<S>&a){return *max_element(all(a));}
template<class S>S min(vector<S>&a){return *min_element(all(a));}
ll sumAtoB(ll a,ll b){return (a+b)*(b-a+1)/2;}

namespace IO {
	// container detection
	template<typename T, typename _=void> struct is_container : false_type {};
	template<> struct is_container<string> : false_type {};
	template<class T> struct is_container<valarray<T>> : true_type {};
	template<typename...Ts> struct is_container_helper {};
	template<typename T> struct is_container<T, conditional_t<
		true, void, is_container_helper<
			typename T::value_type, typename T::size_type, typename T::iterator,
			decltype(declval<T>().size()),
			decltype(declval<T>().begin()),
			decltype(declval<T>().end()) >>> : public true_type {};
	template<typename T,
		typename enable_if<is_container<T>{}, nullptr_t>::type = nullptr,
		char Separator = is_container<typename T::value_type>{} ? '\n' : ' ' >
	constexpr ostream&operator<<(ostream&os, T t){
		if(auto b=begin(t), e=end(t) ; t.size()) for(os<<(*b++);b!=e;os<<Separator<<(*b++)) ;
		return os;
	}

	// output
	template<class T, class...Ts> constexpr ostream& pargs(ostream&os, T&&t, Ts&&...args); // support clang
	template<class S,class T>constexpr ostream&operator<<(ostream&os,pair<S,T>p){ return os<<'['<<p.first<<", "<<p.second<<']'; };
	template<class...Ts>constexpr ostream&operator<<(ostream&os,tuple<Ts...>t){
		return apply([&os](auto&&t,auto&&...args)->ostream&{return pargs(os, t, args...);}, t);
	};
	template<class T, class...Ts> constexpr ostream& pargs(ostream&os, T&&t, Ts&&...args) {
		return ((os<<t)<<...<<(os<<' ', args));
	}

	template<class...Ts> constexpr ostream& out(Ts...args) { return pargs(cout, args...)<<'\n'; }
	template<class...Ts> constexpr ostream& debug_f(Ts...args) { return pargs(cerr, args...)<<'\n'; }
	#ifdef _DEBUG
	template<class...Ts> constexpr ostream& debug(Ts...args) { return pargs(cerr, args...)<<'\n'; }
	#else
	#define debug(...) if(false)debug_f(__VA_ARGS__)
	#endif
	void Yn(bool f) { out(f?"Yes":"No"); }

	// input
	template<class T, class...Ts> constexpr istream& gargs(istream&is, T&&t, Ts&&...args) {
		return ((is>>t)>>...>>args);
	}
	template<class S,class T>auto&operator>>(istream&is,pair<S,T>&p){return is>>p.first>>p.second;}
	template<class...Ts>constexpr istream&operator>>(istream&is,tuple<Ts...>&t){
		return apply([&is](auto&&t,auto&&...args)->istream&{return gargs(is, t, args...);}, t);
	};

	template<typename...S>auto&in(S&...s){return gargs(cin, s...);}
	#define def(t,...) t __VA_ARGS__; in(__VA_ARGS__)
	template<typename T, typename enable_if<is_container<T>{}, nullptr_t>::type = nullptr>
	auto&operator>>(istream&is,T&t){for(auto&a:t)is>>a; return is;}
}
using namespace IO;

class Random {
public:
	typedef uint_fast32_t result_type;
	constexpr result_type operator()(){return operator()((ll)min(),(ll)max());}
	static constexpr result_type max(){return numeric_limits<result_type>::max();}
	static constexpr result_type min(){return 0;}
	constexpr Random(const bool&isDeterministic):y(isDeterministic?2463534242:chrono::system_clock::now().time_since_epoch().count()){}
	constexpr int operator()(int a,int b){return next()%(b-a)+a;}
	constexpr ll operator()(ll a,ll b){return (((ull)next())<<32|next())%(b-a)+a;}
	constexpr double operator()(double a,double b){return (b-a)*next()/4294967296.0+a;}
private:
	result_type y;
	constexpr result_type next(){return y^=(y^=(y^=y<<13)>>17)<<5;}
} Random(0);

class Timer {
	#ifdef _DEBUG
	static constexpr uint64_t ClocksPerMsec = 3587000;
	#else
	static constexpr uint64_t ClocksPerMsec = 2987000;
	#endif
	const uint64_t start,limit;
	uint64_t getClocks() const{
		unsigned int lo,hi;
		__asm__ volatile ("rdtsc" : "=a" (lo), "=d" (hi));
		return((uint64_t)hi<<32)|lo;
	}
public:
	Timer(uint64_t _limit=1970): start(getClocks()),limit(start+_limit*ClocksPerMsec) {}
	uint64_t get() const{return (getClocks()-start)/ClocksPerMsec;}
	operator bool()const{return getClocks()<limit;}
};
void wait(const int&msec){Timer tm(msec); while(tm);}

struct Mgr {
	static const int TLE = 2000;
	static inline Timer timer = Timer(TLE-20);
	Mgr() {
		ios_base::sync_with_stdio(0); cin.tie(0);
		cout<<fixed<<setprecision(11);
		cerr<<fixed<<setprecision(3);
	}
	~Mgr(){
		cout<<flush;
		debug_f(timer.get(), "ms")<<flush;
	}
} _manager;

namespace std {
	template<class T>
	struct hash_base {
		const static inline size_t hash_value = 0x9e3779b9;
		static inline size_t hash_rnd = Random(0, numeric_limits<size_t>::max());
		template<class V, class P=remove_const_t<remove_reference_t<V>>> static size_t& do_hash(size_t&seed, V&v) {
			return seed ^= hash<P>{}(v) + hash_value + (seed<<6) + (seed>>2);
		}
		virtual size_t operator()(T p) const = 0;
	};

	template<class S, class T>
	struct hash<pair<S,T>> : public hash_base<pair<S,T>> {
		size_t operator()(pair<S,T> p) const {
			size_t seed = 0;
			this->do_hash(seed, p.first);
			this->do_hash(seed, p.second);
			return this->do_hash(seed, this->hash_value);
		}
	};

	template<class...Ts>
	struct hash<tuple<Ts...>> : public hash_base<tuple<Ts...>> {
		size_t operator()(tuple<Ts...> t) const {
			return apply([&](auto&&...args)->size_t{
				size_t seed = 0;
				for(auto&&v : {args...}) this->do_hash(seed, v);
				return this->do_hash(seed, this->hash_value);
			}, t);
		}
	};
}








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
	Matrix(int H, int W) : H(H), W(W), elem(H * W, 0) {}
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
 
int main() {
	/*$1*/
	def(ll,n,k);
	vl a;
	vl ans(n);
	rep(i,k+1){
		vl q;
		rep(j,k) q.push_back((i+j)%(k+1)+1);
		out("?",q)<<flush;
		def(ll,v);
		a.push_back(v);
	}
	ll b = sum(a)%2;
	rep(i,k+1){
		ans[(i+k)%(k+1)] = (b-a[i]+2)%2;
		debug((i+k)%(k+1),(b-a[i]+2)%2);
	}
	b=0;
	rep(i,k-1) b+=ans[i];
	rep(i,k+1,n){
		vl q;
		rep(j,k-1)q.push_back(j+1);
		q.push_back(i+1);
		out("?",q)<<flush;
		def(ll,v);
		ans[i] = (b-v+2)%2;
	}
	out("!",ans)<<flush;


}