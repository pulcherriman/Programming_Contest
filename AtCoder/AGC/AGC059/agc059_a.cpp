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
template<class K> using HashSet=__gnu_pbds::gp_hash_table<K,__gnu_pbds::null_type>;
template<class K,class V> using IndexedMap=__gnu_pbds::tree<K,V,less<K>,__gnu_pbds::rb_tree_tag,__gnu_pbds::tree_order_statistics_node_update>;
template<class K,class V> using HashMap=__gnu_pbds::gp_hash_table<K,V>;
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
template<class T>constexpr bool chmax(T&a,T b){return a<b?a=b,1:0;}
template<class T>constexpr bool chmin(T&a,T b){return a>b?a=b,1:0;}
template<class S>S sum(vector<S>&a){return accumulate(all(a),S());}
template<class S>S max(vector<S>&a){return *max_element(all(a));}
template<class S>S min(vector<S>&a){return *min_element(all(a));}

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
		debug_f(timer.get(), "ms")<<flush;
	}
} _manager;

namespace std::tr1 {
	template<class T>
	struct hash_base {
		const static inline size_t hash_value = 0x9e3779b9;
		static inline size_t hash_rnd = Random(0, numeric_limits<size_t>::max());
		template<class V> static size_t& do_hash(size_t&seed, V&v) {
			return seed ^= hash<V>{}(v) + hash_value + (seed<<6) + (seed>2);
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
}






template <typename Monoids>
class SegmentTree {
	using Val = typename Monoids::Val;
	using Op = typename Monoids::Op;

private:
	const int h, n;
	vector<Val> data;
	vector<Op> lazy;

	void push(int node) {
		if (lazy[node] == Monoids::id_op()) return;
		if (node < n) {
			lazy[node * 2] = Monoids::concat_op(lazy[node * 2], lazy[node]);
			lazy[node * 2 + 1] = Monoids::concat_op(lazy[node * 2 + 1], lazy[node]);
		}
		data[node] = Monoids::operate(data[node], lazy[node]);
		lazy[node] = Monoids::id_op();
	}
	void eval(int node) {
		data[node] = Monoids::concat_val(Monoids::operate(data[node * 2], lazy[node * 2])
						, Monoids::operate(data[node * 2 + 1], lazy[node * 2 + 1]));
	}

	int find_rightest_sub(int a, int b, Val x, int k, int l, int r) {
		if (data[k] > x || r <= a || b <= l) {
			return a - 1;
		} else if (k >= n - 1) {
			return (k - (n - 1));
		} else {
			int vr = find_rightest_sub(a, b, x, 2 * k + 2, (l + r) / 2, r);
			if (vr != a - 1) {
				return vr;
			} else {
				return find_rightest_sub(a, b, x, 2 * k + 1, l, (l + r) / 2);
			}
		}
	}
	int find_leftest_sub(int a, int b, Val x, int k, int l, int r) {
		if (data[k] > x || r <= a || b <= l) {
			return b;
		} else if (k >= n - 1) {
			return (k - (n - 1));
		} else {
			int vl = find_leftest_sub(a, b, x, 2 * k + 1, l, (l + r) / 2);
			if (vl != b) {
				return vl;
			} else {
				return find_leftest_sub(a, b, x, 2 * k + 2, (l + r) / 2, r);
			}
		}
	}

public:
	SegmentTree(int n_): SegmentTree(n_, Monoids::init_val()) {}
	SegmentTree(int n_, Val v1) : SegmentTree(vector<Val>(n_, v1)) {}
	SegmentTree(const vector<Val>& data_)
		: h(ceil(log2(data_.size()))), n(1 << h), data(n * 2, Monoids::id_val()), lazy(n * 2, Monoids::id_op()) {
		for (int i = 0; i < (int)data_.size(); i++) data[i + n] = data_[i];
		for (int i = n - 1; i >= 1; i--) data[i] = Monoids::concat_val(data[i * 2], data[i * 2 + 1]);
	}

	/* 区間 [l,r) の各要素に対してopを作用させる */
	void update(int l, int r, Op op) {
		l += n, r += n - 1;
		for (int i = h; i > 0; i--) push(l >> i), push(r >> i);
		int tl = l, tr = r;
		r++;
		while (l < r) {
			if (l & 1) lazy[l] = Monoids::concat_op(lazy[l], op), l++;
			if (r & 1) r--, lazy[r] = Monoids::concat_op(lazy[r], op);
			l >>= 1; r >>= 1;
		}
		while (tl >>= 1, tr >>= 1, tl) {
			if (lazy[tl] == Monoids::id_op()) eval(tl);
			if (lazy[tr] == Monoids::id_op()) eval(tr);
		}
	}

	/* i番目の要素に対してopを作用させる */
	void update(int i, Op op) { update(i, i+1, op); }

	/* 区間 [l,r) の値に対してconcat_valを作用させた結果を得る */
	Val query(int l, int r) {
		l += n, r += n - 1;
		for (int i = h; i > 0; i--) push(l >> i), push(r >> i);
		r++;
		Val res1 = Monoids::id_val(), res2 = Monoids::id_val();
		while (l < r) {
			if (l & 1) res1 = Monoids::concat_val(res1, Monoids::operate(data[l], lazy[l])), l++;
			if (r & 1) r--, res2 = Monoids::concat_val(Monoids::operate(data[r], lazy[r]), res2);
			l >>= 1; r >>= 1;
		}
		return Monoids::concat_val(res1, res2);
	}

	/* i番目の要素を得る */
	Val operator[](int i) {
		int l=i+n;
		rep(h) push(l>>=1);
		return Monoids::operate(data[i+n], lazy[i+n]);
	}

	/* 区間 [l,r) の中で、x以下の要素を持つ最も右の要素の位置を返す 無ければr
	 * Valに演算子 > が必要
	 * TODO: 非再帰にする
	 */
	int find_rightest(int l, int r, Val x) { return find_rightest_sub(l, r, x, 0, 0, n); }

	/* 区間 [l,r) の中で、x以下の要素を持つ最も左の要素の位置を返す 無ければl-1
	 * Valに演算子 > が必要
	 * TODO: 非再帰にする
	 */
	int find_leftest(int l, int r, Val x) { return find_leftest_sub(l, r, x, 0, 0, n); }

	friend ostream &operator<<(ostream &os, SegmentTree &st) {
		Val v;
		rep(i,st.input_n-1) os<<(v=st[i])<<' ';
		return os<<(v=st[st.input_n-1]);
	}
};

namespace SegTreeUtil {
	template<typename T>
	struct Val_HasSize {
		using V_t = Val_HasSize<T>;
		T val;
		int len;
		Val_HasSize() : Val_HasSize(0, 0) {}
		Val_HasSize(T v, int l=1) : val(v), len(l) {}
		friend ostream& operator<<(ostream& os, V_t&v) { return os << v.val; }
		friend V_t operator+(const V_t&a, const V_t&b) {
			return V_t(a.val + b.val, a.len + b.len);
		}
	};

	template<typename T>
	struct Update_Min {
		using Val = T;
		using Op = T;
		static Val init_val() { return id_val(); }
		static Val id_val() { return numeric_limits<Val>::max(); }
		static Op id_op() { return numeric_limits<Op>::min(); }
		static Val concat_val(const Val& l, const Val& r) { return min(l, r); }
		static Val operate(const Val& l, const Op& r) { return r != id_op() ? r : l; }
		static Op concat_op(const Op& l, const Op& r) { return r != id_op() ? r : l; }
	};

	template<typename T>
	struct Update_Max {
		using Val = T;
		using Op = T;
		static Val init_val() { return id_val(); }
		static Val id_val() { return numeric_limits<Val>::min(); }
		static Op id_op() { return numeric_limits<Op>::max(); }
		static Val concat_val(const Val& l, const Val& r) { return max(l, r); }
		static Val operate(const Val& l, const Op& r) { return r != id_op() ? r : l; }
		static Op concat_op(const Op& l, const Op& r) { return r != id_op() ? r : l; }
	};

	template<typename T>
	struct Update_Sum {
		using Val = Val_HasSize<T>;
		using Op = T;
		static Val init_val() { return Val(0); }
		static Val id_val() { return Val(); }
		static Op id_op() { return numeric_limits<Op>::max(); }
		static Val concat_val(const Val& l, const Val& r) { return l + r; }
		static Val operate(const Val& l, const Op& r) { return r != id_op() ? Val(r*l.len, l.len) : l; }
		static Op concat_op(const Op& l, const Op& r) { return r != id_op() ? r : l; }
	};

	template<typename T>
	struct Add_Min {
		using Val = T;
		using Op = T;
		static Val init_val() { return id_val(); }
		static Val id_val() { return numeric_limits<Val>::max(); }
		static Op id_op() { return Op(); }
		static Val concat_val(const Val& l, const Val& r) { return min(l, r); }
		static Val operate(const Val& l, const Op& r) { return l + r; }
		static Op concat_op(const Op& l, const Op& r) { return l + r; }
	};

	template<typename T>
	struct Add_Max {
		using Val = T;
		using Op = T;
		static Val init_val() { return id_val(); }
		static Val id_val() { return numeric_limits<Val>::min(); }
		static Op id_op() { return Op(); }
		static Val concat_val(const Val& l, const Val& r) { return max(l, r); }
		static Val operate(const Val& l, const Op& r) { return l + r; }
		static Op concat_op(const Op& l, const Op& r) { return l + r; }
	};

	template<typename T>
	struct Add_Sum {
		using Val = Val_HasSize<T>;
		using Op = T;
		static Val init_val() { return Val(0); }
		static Val id_val() { return Val(); }
		static Op id_op() { return Op(); }
		static Val concat_val(const Val& l, const Val& r) { return l + r; }
		static Val operate(const Val& l, const Op& r) { return Val(l.val + r*l.len, l.len); }
		static Op concat_op(const Op& l, const Op& r) { return l + r; }
	};

	template<typename T>
	struct Temp {
		using Val = T;
		using Op = T;
		static Val init_val() { return 0; }
		static Val id_val() { return 0; }
		static Op id_op() { return 0; }
		static Val concat_val(const Val& l, const Val& r) { return l|r; }
		static Val operate(const Val& l, const Op& r) { return l | r; }
		static Op concat_op(const Op& l, const Op& r) { return l | r; }
	};
}

// SegmentTree<SegTreeUtil::Add_Sum<ll>> st(n);
ll n,q;
string s;

vi manachar(string S){
	vi R(S.size());
	int i = 0, j = 0;
	while (i < S.size()) {
	while (i-j >= 0 && i+j < S.size() && S[i-j] == S[i+j]) ++j;
	R[i] = j;
	int k = 1;
	while (i-k >= 0 && k+R[i-k] < j) R[i+k] = R[i-k], ++k;
	i += k; j -= k;
	}
	return R;
}

int main() {
	/**/
	in(n,q,s);
	char prev='-';
	string s2;
	vi indexMap(n,0);
	rep(i,n){
		if(prev!=s[i]){
			s2+=s[i];
		}
		prev=s[i];
		indexMap[i]=s2.size()-1;
	}
	s=s2;
	n=s.size();

	rep(q){
		def(ll,l,r);
		l--; r--;
		l=indexMap[l];
		r=indexMap[r];
		ll len = r-l+1;
		if(len%2==0){
			out(len/2);
		}else{
			if(s[l]!=s[r]) out((len+1)/2);
			else out(len/2);
		}
	}

	
}