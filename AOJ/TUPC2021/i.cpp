/*
 * Unsecured Optimization
 */
#pragma GCC optimize "O3" /* 最適化 */
#pragma GCC target "avx" /* SIMD(ベクトル化) */
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native") /* 浮動小数点数のSIMD */
// #pragma GCC optimize "fast-math"
// #pragma GCC optimize "unroll-loops" /* ループの展開 */
// #ifdef _DEBUG
// #define _GLIBCXX_DEBUG 1
// #endif

/* 
 * Include Headers
 */
#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;

struct Setup_io {
	Setup_io() {
		ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
		cout<<fixed<<setprecision(11);
	}
} setup_io;

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
template<class K> using HashSet=__gnu_pbds::gp_hash_table<K,__gnu_pbds::null_type>;
template<class K,class V> using IndexedMap=__gnu_pbds::tree<K,V,less<K>,__gnu_pbds::rb_tree_tag,__gnu_pbds::tree_order_statistics_node_update>;
template<class K,class V> using HashMap=__gnu_pbds::gp_hash_table<K,V>;

/*
 * Macros
 */
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

/*
 * Constants
 */
constexpr ll LINF=1ll<<60;
constexpr int INF=1<<30;
constexpr double EPS=(1e-14);
constexpr ll MOD=998244353ll;
constexpr long double PI=3.14159265358979323846;

/*
 * Output Assist
 */
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

/*
 * Input Assist
 */
template<class S,class T>auto&operator>>(istream&is,pair<S,T>&p){is>>p.first>>p.second;return is;}
template<class S>auto&operator>>(istream&is,vector<S>&t){for(S&a:t)is>>a;return is;}
template<typename...S>void geta_(S&...s){((cin>>s),...);}
#define geta(t,...) t __VA_ARGS__;geta_(__VA_ARGS__)
template<class T,class...Args>auto vec(T x,int arg,Args...args){if constexpr(sizeof...(args)==0)return vector(arg,x);else return vector(arg,vec(x,args...));}
#define getv(a,...) auto a=vec(__VA_ARGS__);cin>>a

/*
 * Utilities
 */
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
template<class T> vector<pair<T,int>> addIndex(vector<T> a){
	vector<pair<T,int>> r;
	rep(i,a.size())r.emplace_back(a[i],i);
	return r;
}


#ifdef _MSC_VER
#include <intrin.h>
#endif

namespace atcoder {

namespace internal {

// @param n `0 <= n`
// @return minimum non-negative `x` s.t. `n <= 2**x`
int ceil_pow2(int n) {
    int x = 0;
    while ((1U << x) < (unsigned int)(n)) x++;
    return x;
}

// @param n `1 <= n`
// @return minimum non-negative `x` s.t. `(n & (1 << x)) != 0`
int bsf(unsigned int n) {
#ifdef _MSC_VER
    unsigned long index;
    _BitScanForward(&index, n);
    return index;
#else
    return __builtin_ctz(n);
#endif
}

}  // namespace internal

}  // namespace atcoder

namespace atcoder {

template <class S, S (*op)(S, S), S (*e)()> struct segtree {
  public:
    segtree() : segtree(0) {}
    explicit segtree(int n) : segtree(std::vector<S>(n, e())) {}
    explicit segtree(const std::vector<S>& v) : _n(int(v.size())) {
        log = internal::ceil_pow2(_n);
        size = 1 << log;
        d = std::vector<S>(2 * size, e());
        for (int i = 0; i < _n; i++) d[size + i] = v[i];
        for (int i = size - 1; i >= 1; i--) {
            update(i);
        }
    }

    void set(int p, S x) {
        assert(0 <= p && p < _n);
        p += size;
        d[p] = x;
        for (int i = 1; i <= log; i++) update(p >> i);
    }

    S get(int p) {
        assert(0 <= p && p < _n);
        return d[p + size];
    }

    S prod(int l, int r) {
        assert(0 <= l && l <= r && r <= _n);
        S sml = e(), smr = e();
        l += size;
        r += size;

        while (l < r) {
            if (l & 1) sml = op(sml, d[l++]);
            if (r & 1) smr = op(d[--r], smr);
            l >>= 1;
            r >>= 1;
        }
        return op(sml, smr);
    }

    S all_prod() { return d[1]; }

    template <bool (*f)(S)> int max_right(int l) {
        return max_right(l, [](S x) { return f(x); });
    }
    template <class F> int max_right(int l, F f) {
        assert(0 <= l && l <= _n);
        assert(f(e()));
        if (l == _n) return _n;
        l += size;
        S sm = e();
        do {
            while (l % 2 == 0) l >>= 1;
            if (!f(op(sm, d[l]))) {
                while (l < size) {
                    l = (2 * l);
                    if (f(op(sm, d[l]))) {
                        sm = op(sm, d[l]);
                        l++;
                    }
                }
                return l - size;
            }
            sm = op(sm, d[l]);
            l++;
        } while ((l & -l) != l);
        return _n;
    }

    template <bool (*f)(S)> int min_left(int r) {
        return min_left(r, [](S x) { return f(x); });
    }
    template <class F> int min_left(int r, F f) {
        assert(0 <= r && r <= _n);
        assert(f(e()));
        if (r == 0) return 0;
        r += size;
        S sm = e();
        do {
            r--;
            while (r > 1 && (r % 2)) r >>= 1;
            if (!f(op(d[r], sm))) {
                while (r < size) {
                    r = (2 * r + 1);
                    if (f(op(d[r], sm))) {
                        sm = op(d[r], sm);
                        r--;
                    }
                }
                return r + 1 - size;
            }
            sm = op(d[r], sm);
        } while ((r & -r) != r);
        return 0;
    }

  private:
    int _n, size, log;
    std::vector<S> d;

    void update(int k) { d[k] = op(d[2 * k], d[2 * k + 1]); }
};

}  // namespace atcoder



// ここにライブラリを貼る
// NOTICE: Require "Random"
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

struct _Prime {
private:
	constexpr ull fast_gcd(ull a, ull b) {
		if(a==0||b==0)return a+b;
		int n=__builtin_ctzll(a),m=__builtin_ctzll(b);
		a>>=n; b>>=m;
		while(a!=b){ int x=__builtin_ctzll(a-b); a=(max(a,b)-(b=min(a,b)))>>x; }
		return a<<min(n,m);
	}
	constexpr ull mul (ull a,ull b,ull&mod) {
		ll ret=a*b-mod*(ull)(1.L/mod*a*b);
		return ret+(ret<0)*mod-(ret>=(ll)mod)*mod;
	}
	constexpr ull mod128 (ull a,ull e,ull&mod) {
		ull ret=1;
		while(e){ if(e&1)ret=mul(ret,a,mod); a=mul(a,a,mod),e>>=1; }
		return ret;
	}
	constexpr inline ull pollard_f(ull x, ull&n, ull&c){ return mul(x,x,n)+c; }
	ull pollard(ull n){
		ull t=0,prod=2,q,x=0,y=0,c=0,i=2;
		while((t++&127) or fast_gcd(prod,n)==1){
			if(x==y)y=pollard_f(x=i,n,c=Random(1ll,n));
			if((q=mul(prod,max(x,y)-min(x,y),n)))prod=q;
			x=pollard_f(x,n,c),y=pollard_f(pollard_f(y,n,c),n,c);
		}
		return fast_gcd(prod,n);
	}
public:
	constexpr bool isPrime (ull n) {
		if(n<=1)return false;
		if(n<4)return true;
		if(n%6%4!=1)return false;
		ull s=__builtin_ctzll(n-1),d=n>>s;

		constexpr ull pollard_seed[7]={2, 325, 9375, 28178, 450775, 9780504, 1795265022};
		for(ull x:pollard_seed){
			ull p=mod128(x,d,n),i=s;
			while(p!=1 and p!=n-1 and x%n and i--)p=mul(p,p,n);
			if(p!=n-1 and i!=s) return false;
		}
		return true;
	}

	vector<ull> factor(ull n){
		if (n==1) return{};
		if (isPrime(n)) return{n};
		ull x=pollard(n);
		auto l=factor(x),r=factor(n/x);
		l.insert(l.end(),all(r));
		return l;
	}

	vector<ull> divisor(ull n){
		HashSet<ull> st;
		vector<ull> tmp;
		st.insert(1);
		for(auto&f:factor(n)){
			tmp.clear();
			for(auto&d:st)tmp.emplace_back(d*f);
			for(auto&d:tmp)st.insert(d);
		}
		return vector<ull>(all(st));
	}

	int divisorCount(ull n){
		int ret=1; ull v=0,c=0;
		auto fac=factor(n);
		sort(all(fac)); fac.emplace_back(-1);
		for(auto&f:fac){if(f!=v)ret*=c+1, v=f, c=0; c++;}
		return ret;
	}
}; _Prime Prime;


template <int mod> struct ModInt {
	// 原始根 O(sqrt(N))
	static int get_primitive_root() {
		static int primitive_root = 0;
		if (!primitive_root) {
			primitive_root = -1;
			set<int> fac;
			int v=mod-1;
			for(int64_t i=2;i*i<=v;i++)while(v%i)fac.insert(i),v/=i;
			if(v>1)fac.insert(v);
			rep(g,1,mod){
				bool ok=true;
				for(auto&i:fac) if(ModInt(g).pow((mod-1)/i)==1){ ok=false; break; }
				if(ok){ primitive_root=g; break; }
			}
		}
		return primitive_root;
	}
	int x;
	ModInt() : x(0) {}
	ModInt(int64_t y) : x(y >= 0 ? y % mod : (mod - (-y) % mod) % mod) {}
	explicit operator bool() const { return x != 0; }
	explicit operator int64_t() const { return x; }
	ModInt operator+(const ModInt &p) const { return ModInt(*this) += p; }
	ModInt operator-(const ModInt &p) const { return ModInt(*this) -= p; }
	ModInt operator*(const ModInt &p) const { return ModInt(*this) *= p; }
	ModInt operator/(const ModInt &p) const { return ModInt(*this) /= p; }
	ModInt operator-() const { return ModInt(-x); }
	ModInt &operator+=(const ModInt &p) { if((x += p.x) >= mod) x -= mod; return *this; }
	ModInt &operator-=(const ModInt &p) { if((x += mod - p.x) >= mod) x -= mod; return *this; }
	ModInt &operator*=(const ModInt &p) { x = (int) (1LL * x * p.x % mod); return *this; }
	ModInt &operator/=(const ModInt &p) { return *this *= p.inv(); }
	friend ModInt operator+(int64_t a, const ModInt &p) { return p+a; }
	friend ModInt operator-(int64_t a, const ModInt &p) { return -p+a; }
	friend ModInt operator*(int64_t a, const ModInt &p) { return p*a; }
	friend ModInt operator/(int64_t a, const ModInt &p) { return p.inv()*a; }
	bool operator==(const ModInt &p) const { return x == p.x; }
	bool operator!=(const ModInt &p) const { return x != p.x; }
	bool operator<(const ModInt &p) const { return x < p.x; }
	friend istream &operator>>(istream &is, ModInt &p) { int64_t t; is >> t; p = ModInt(t); return is; }
	friend ostream &operator<<(ostream &os, const ModInt &p) { return os << p.x; }
	ModInt pow(int64_t n) const {
		ModInt ret(1), mul(x);
		while(n > 0) {
			if(n & 1) ret *= mul;
			mul *= mul;
			n >>= 1;
		}
		return ret;
	}

	ModInt inv() const {
		int a = x, b = mod, u = 1, v = 0, t;
		while(b > 0) {
			t = a / b;
			swap(a -= t * b, b);
			swap(u -= t * v, v);
		}
		return u;
	}

	ModInt sqrt() const {
		if (x==0) return 0;
		if (mod==2) return x;
		if (pow((mod-1)/2)!=1) return 0;
		ModInt b = 1;
		while (b.pow((mod-1)/2)==1)b+=1;
		int e=0, m=mod-1;
		while(m%2==0)m>>=1, e++;
		ModInt p=pow((m-1)/2), y=(*this)*p*p, z=b.pow(m);
		p*=(*this);
		while(y!=1){
			int j=0;
			ModInt t=y;
			while(t!=1)j++, t*=t;
			z=z.pow(1LL<<(e-j-1));
			p*=z,z*=z,y*=z,e=j;
		}
		return ModInt(min(p.x, mod-p.x));
	}
};
using mymint = ModInt<MOD>;
using vm = vector<mymint>;
using vvm = vector<vm>;
mymint operator"" _m(unsigned long long a){ return mymint(a); }


enum SegType{SEG_MIN,SEG_MAX,SEG_SUM};
 
struct SegmentTree{
    using Func=function<mymint(mymint,mymint)>;
    using Attr=tuple<mymint,Func,Func>;
    int n;
    vm val;
    mymint e;
    Func f,g;
    const vector<Attr> tmpAttr{
        Attr(LINF,[](mymint a,mymint b){return min(a,b);},[](mymint a,mymint b){return b;}),
        Attr(-LINF,[](mymint a,mymint b){return max(a,b);},[](mymint a,mymint b){return b;}),
        Attr(1,[](mymint a,mymint b){return a*b;},[](mymint a,mymint b){return b;}),
    };
	SegmentTree(){}
	SegmentTree(const SegmentTree&) = default;
    SegmentTree(int N){
        n=1; while(n<=N)n*=2;
    }
    SegmentTree(int N,int t):SegmentTree(N){tie(e,f,g)=tmpAttr[t];val.assign(n*2,e);}
    SegmentTree(int N,mymint E,Func F,Func G):SegmentTree(N){tie(e,f,g)=Attr(E,F,G);val.assign(n*2,e);}
    void update(int k,mymint a){
        k+=n;
        val[k]=g(val[k],a);
        while(k){
            k/=2;
            val[k]=f(val[k*2],val[k*2+1]);
        }
    }
    mymint query(int a, int b){return query(a,b,1,0,n);}
    mymint query(int a, int b, int k, int l, int r){
        if(r<=a or l>=b) return e;
        if(a<=l and r<=b) return val[k];
        int m=(l+r)/2;
        return f(query(a,b,k*2,l,m),query(a,b,k*2+1,m,r));
    }   
	void init(int N,int t){
		n=1; while(n<=N)n*=2;
		tie(e,f,g)=tmpAttr[t];val.assign(n*2,e);
	}
};


int main(){
	geta(ll, n);
	map<int,int> primeMap;
	vi invmap;
	int cnt=0;
	rep(i,1,1000001)if(Prime.isPrime(i)){
		primeMap[i]=cnt++;
		invmap.push_back(i);
	}


	SegmentTree st(n, SEG_SUM);
	vector<bitset<100000>> lcms(cnt);

	rep(i,n){
		geta(ll, a);
		st.update(i, a);
		for(int p:Prime.factor(a)){
			lcms[primeMap[p]][i]=1;
		}
	}

	geta(int,q);
	rep(q){
		geta(int, l,r);
		l--;
		auto ans = st.query(l,r);
		rep(i,cnt){
			int p=invmap[i];
			auto bs = lcms[i];
			bs<<=(100000-r);
			bs>>=(100000-r);
			bs>>=l;
			bs<<=l;
			if(bs.any()){
				ans *= (p-1);
				ans /= p;
			}
		}
		puta(ans);
	}

}


/* 問題概要
 * 長さ1e5、値1~1e6からなる正整数列について、1e5クエリ答えよ
 *　「L,Rに対して、「L番目からR番目までの全要素の積」のトーシェント（mod 9982）
 *
 */


