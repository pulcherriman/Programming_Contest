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

template<class T>struct Graph;
template<class T>struct DFSResult{
	vb connected;
	vector<T> distance;
	vi preorder, postorder, eulertour, subtreeNodeCount, parents;
	vl subtreePathLengthSum, eulerWeight;
	vp eulerEdge;
	DFSResult(Graph<T>&g):
		connected(g.size,false),
		distance(g.size,g.INF_VAL),
		preorder(g.size,-1),
		postorder(g.size,-1),
		parents(g.size,0),
		subtreeNodeCount(g.size,1),
		subtreePathLengthSum(g.size,0){
			eulertour.reserve(g.size*2);
			eulerWeight.reserve(g.size*2);
			eulerEdge.reserve(g.size*2);
	}
};
template<class T=ll>struct Graph{
	int size;
	T INF_VAL;
	vector<vector<tuple<ll,T>>>edge;
	Graph(int n=1,T inf=LINF):size(n),INF_VAL(inf){edge.resize(size);}
	constexpr void add(ll from, ll to, T cost, bool directed=false){
		edge[from].emplace_back(to,cost);
		if(!directed) edge[to].emplace_back(from,cost);
	}
	constexpr friend ostream &operator<<(ostream &os, const Graph<T> &g) {
		rep(i,g.size)for(auto[from,val]:g.edge[i])pargs(os, i,"=>",from,", cost :",val)<<'\n';
		return os;
	}
	constexpr static pair<int,Graph<T>> input(bool weighted=false, bool directed=false){
		def(int,n,m);
		Graph<T> g(n);
		g.inputEdge(m,weighted,directed);
		return {n,g};
	}

	// s始点で深さ優先探索して情報を返す。木以外で使うのか？
	// この関数は変更しない
	constexpr DFSResult<T> dfs(int s){
		int pre=0,post=0;
		DFSResult<T> ret(*this);
		ret.distance[s]=0;
		vi parent(size, 0);

		vector<HashMap<int,ll>> edges(size);
		rep(i,size)for(auto[to,cost]:edge[i])edges[i][to]=cost;


		const function<void(int)> dfsrec=[this, &edges, &ret ,&pre, &post, &dfsrec, &parent](int p){
			ret.connected[p]=true;
			ret.preorder[p]=pre++;
			ret.eulertour.emplace_back(p);
			ret.eulerWeight.emplace_back(edges[parent[p]][p]);
			ret.eulerEdge.emplace_back(parent[p],p);
			for(auto[to,cost]:edge[p])if(!ret.connected[to]){
				ret.distance[to]=ret.distance[p]+cost;
				parent[to]=p;
				dfsrec(to);
				ret.subtreePathLengthSum[p]+=ret.subtreePathLengthSum[to] + ret.subtreeNodeCount[to] * cost;
				ret.subtreeNodeCount[p]+=ret.subtreeNodeCount[to];
			}
			ret.postorder[p]=post++;
			ret.eulertour.emplace_back(p);
			ret.eulerWeight.emplace_back(-edges[parent[p]][p]);
			ret.eulerEdge.emplace_back(parent[p],p);
		};
		dfsrec(s);
		ret.parents=parent;
		return ret;
	};
	// BFSする。この関数は変更しない
	constexpr vector<T> bfs(int s){
		vector<T> ret(size,INF_VAL);
		deque<int> q;
		ret[q.emplace_back(s)]=0;
		while(!q.empty()){
			int p=q.front(); q.pop_front();
			for(auto[to,cost]:edge[p])if(chmin(ret[to],ret[p]+cost)){
				if(cost==0)q.emplace_front(to); else q.emplace_back(to);
			}
		}
		return ret;
	}
	// BFSしてパスを復元する。
	// 余分にO(N)掛けてるので、距離だけほしい場合はbfs(s)[t]を見るとよい
	constexpr pair<T,vi> bfs(int s, int t){
		auto dist=bfs(s);
		vi path(1,t);
		while(path.back()!=s)for(auto[to,_]:edge[path.back()])if(dist[to]==dist[path.back()]-1){path.emplace_back(to);break;}
		reverse(all(path));
		return {dist[t], path};
	}
	
	constexpr void inputEdge(int edgeCount, bool weighted, bool directed){
		int a,b; T c=1;
		rep(i,edgeCount){
			cin>>a>>b; if(weighted)cin>>c;
			add(a-1,b-1,c,directed);
		}
	}

	// ノードを追加
	int addNode(){
		edge.emplace_back();
		return size++;
	}

	// 入次数を返す
	vi inDegree(){
		vi in(size,0);
		for(auto&e:edge)for(auto&[to,_]:e)in[to]++;
		return in;
	}

	// トポロジカルソート
	pair<bool,vi> topologicalSort(){
		queue<int> st;
		vi ans, in=inDegree();
		rep(i,size)if(in[i]==0)st.push(i);
		while(!st.empty()){
			int p=st.front(); st.pop();
			ans.push_back(p);
			for(auto&[to,cost]:edge[p]){
				if(--in[to]==0)st.push(to);
			}
		}
		return {(int)ans.size()==size, ans};
	}
};

class GridGraphBase{
protected:
	static const char ROAD_CHAR='.', WALL_CHAR='#', DIRECTION_CHAR[];
	static const int DY[],DX[];
};
const int GridGraphBase::DY[]={0,1,0,-1,1,1,-1,-1};
const int GridGraphBase::DX[]={1,0,-1,0,1,-1,-1,1};
const char GridGraphBase::DIRECTION_CHAR[]="RDLU";

template<class Cell=int>struct GridGraph : public Graph<int> , private GridGraphBase{
	int h,w;
	vector<Cell> field;
	constexpr typename vector<Cell>::iterator operator[](int i) { return field.begin() + i * w; }
	constexpr Cell &at(int i, int j) { return field[i*w+j]; }
	constexpr Cell get(int i, int j) const { return field[i*w+j]; }

	GridGraph(int&_h, int&_w):Graph((_h+=2)*(_w+=2),INF),h(_h),w(_w){
		edge.resize(h*w);
		field.resize(h*w,ROAD);
		rep(i,h)at(i,0)=at(i,w-1)=WALL;
		rep(j,w)at(0,j)=at(h-1,j)=WALL;
	}
	constexpr void input(){
		char c;
		rep(i,1,h-1)rep(j,1,w-1){cin>>c; at(i,j)=(c==WALL_CHAR?WALL:ROAD);}
		rep(i,1,h-1)rep(j,1,w-1)if(get(i,j)==ROAD){
			if(get(i+1,j)==ROAD)add(i*w+j, i*w+j+w, 1);
			if(get(i,j+1)==ROAD)add(i*w+j, i*w+j+1, 1);
		}
	}
	constexpr friend ostream &operator<<(ostream &os, const GridGraph<Cell> &g) {
		rep(i,g.h){rep(j,g.w)os<<(g.get(i,j)==WALL?WALL_CHAR:ROAD_CHAR);os<<endl;}
		return os;
	}
	template<int tgt=4> constexpr vector<tuple<int,int,int>> neighborIndex(int y, int x, Cell v=ROAD){
		vector<tuple<int,int,int>> p;
		rep(i,tgt)if(get(y+DY[i],x+DX[i])==v)p.emplace_back(y+DY[i],x+DX[i],i);
		return p;
	}
	template<int tgt=4> constexpr vector<reference_wrapper<Cell>> neighborCell(int y, int x, Cell v=ROAD){
		vector<reference_wrapper<Cell>> p;
		rep(i,tgt)if(get(y+DY[i],x+DX[i])==v)p.push_back(at(y+DY[i],x+DX[i]));
		return p;
	}
private:
	static constexpr Cell ROAD=0, WALL=-1;
};

template<class T=int>struct Tree : public Graph<T>{
	Tree(int n, T inf=INF):Graph<T>(n,inf){}

	static pair<int,Tree<T>> input(bool weighted=false, bool directed=false){
		def(int,n);
		Tree<T> g(n);
		g.inputEdge(n-1,weighted,directed);
		return {n,g};
	}

	pair<T,vi> diameter(){
		auto [s,_]=getMaxAndIndex(this->bfs(0));
		auto [t,w]=getMaxAndIndex(this->bfs(s));
		return this->bfs(s,t);
	}
};







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
	SegmentTree(vector<Val> data_)
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
}

// SegmentTree<SegTreeUtil::Add_Sum<ll>> st(n);

template<class T=ll>struct LCA{
	Graph<T> g;
	vvi parent;
	vi dist;
	LCA(Graph<T> g, int root=0):g(g){
		int K=1;
		while((1<<K)<g.size)K++;
		parent.assign(K, vi(g.size,-1));
		dist.assign(g.size, -1);
		dfs(root,-1,0);
		rep(k,K-1)rep(v,g.size){
			parent[k + 1][v]=parent[k][v]<0 ? -1 : parent[k][parent[k][v]];
		}
	}
	void dfs(int v, int p, int d) {
		parent[0][v]=p, dist[v]=d;
		for(auto&[to,_]:g.edge[v])if(to!=p)dfs(to,v,d+1);
	}
	ll get(ll u, ll v){
		if(dist[u]<dist[v])swap(u,v);
		int K = parent.size();
		rep(k,K)if((dist[u]-dist[v])>>k&1)u=parent[k][u];
		if(u==v)return u;
		rrep(k,K)if(parent[k][u]!=parent[k][v])u=parent[k][u],v=parent[k][v];
		return parent[0][u];
	}
};

int main() {
	/**/
	def(ll,n);
	Tree<ll> g(n);
	vp edge;
	rep(i,n-1){
		def(ll,a,b,c);
		a--,b--;
		g.add(a,b,c);
		edge.emplace_back(a,b);
	}

	auto res=g.dfs(0);
	auto eulerTour=res.eulertour;
	auto eulerWeight=res.eulerWeight;
	auto eulerEdge = res.eulerEdge;
	
	SegmentTree<SegTreeUtil::Update_Sum<ll>> st(n*2);
	rep(i,n*2)st.update(i,eulerWeight[i]);

	LCA lca(g);

	vector<HashMap<int,vi>>edgetoIndex(n);
	rep(i,n*2){
		auto [u,v]=eulerEdge[i];
		edgetoIndex[u][v].push_back(i);
		edgetoIndex[v][u].push_back(i);
	}

	vi indexToindex(n);
	rep(i,n*2){
		indexToindex[eulerTour[i]]=i;
	}



	def(ll,q);
	rep(q){
		def(ll,t,a,b);
		if(t==1){
			a--;
			auto [u,v]=edge[a];
			for(auto&i:edgetoIndex[u][v]){
				if(eulerWeight[i] >= 0){
					st.update(i,b);
					eulerWeight[i]=b;
				}else{
					st.update(i,-b);
					eulerWeight[i]=-b;
				}
			}
		}else{
			a--; b--;
			ll lcaValue = lca.get(a, b);
			ll toA = st.query(0,indexToindex[a]).val;
			ll toB = st.query(0,indexToindex[b]).val;
			ll toLCA = st.query(0,indexToindex[lcaValue]).val;
			out(toA+toB-toLCA*2);

		}
	}



}