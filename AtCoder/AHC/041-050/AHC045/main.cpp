/**
* C++23 Template @ AtCoder
* - official support library
*   - AC Library@1.5.1
*   - Boost@1.82.0
*   - GMP@6.2.1
*   - Eigen@3.4.0-2ubuntu2
* - compile option
*   g++-12 -std=gnu++2b -O2 -DONLINE_JUDGE -DATCODER \
*      -Wall -Wextra \
*      -mtune=native -march=native \
*      -fconstexpr-depth=2147483647 -fconstexpr-loop-limit=2147483647 -fconstexpr-ops-limit=2147483647 \
*      -I/opt/ac-library -I/opt/boost/gcc/include -L/opt/boost/gcc/lib \
*      -o a.out Main.cpp \
*      -lgmpxx -lgmp \
*      -I/usr/include/eigen3
*/

#ifdef _DEBUG
// #define _GLIBCXX_DEBUG 1
#undef _DEBUG
#else
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("inline")
#endif

/* 
 * Include Headers
 */
#if defined(EVAL) || defined(ATCODER) || defined(_DEBUG)
#include <atcoder/all>
using namespace atcoder;
#endif
#include <bits/stdc++.h>
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

#ifndef _GLIBCXX_DEBUG
template<class K> using IndexedSet=__gnu_pbds::tree<K,__gnu_pbds::null_type,less<K>,__gnu_pbds::rb_tree_tag,__gnu_pbds::tree_order_statistics_node_update>;
template<class K,class V> using IndexedMap=__gnu_pbds::tree<K,V,less<K>,__gnu_pbds::rb_tree_tag,__gnu_pbds::tree_order_statistics_node_update>;
template<class K,class V> struct HashMap : __gnu_pbds::gp_hash_table<K,V,hash<K>> {
	bool contains(const K&k) const { return this->find(k) != this->end(); }
};
template<class K> struct HashSet : __gnu_pbds::gp_hash_table<K,__gnu_pbds::null_type,hash<K>> {
	bool contains(const K&k) const { return this->find(k) != this->end(); }
};
#else
template<class K> using IndexedSet=set<K>;
template<class K> using HashSet=unordered_set<K>;
template<class K,class V> using IndexedMap=map<K,V>;
template<class K,class V> using HashMap=unordered_map<K,V>;
#endif
template<class V> using maxpq = priority_queue<V>;
template<class V> using minpq = priority_queue<V, vector<V>, greater<V>>;

#define all(a) begin(a),end(a)
#define rall(a) rbegin(a),rend(a)
#define __LOOPSWITCH(_1, _2, _3, __LOOPSWITCH, ...) __LOOPSWITCH
#define rep(...) __LOOPSWITCH(__VA_ARGS__, __RANGE, __REP, __LOOP) (__VA_ARGS__)
#define rrep(...) __LOOPSWITCH(__VA_ARGS__, __RRANGE, __RREP, __LOOP) (__VA_ARGS__)
#define __LOOP(q) for([[maybe_unused]] int _lp ## __LINE__ : views::iota(0, q))
#define __LOOP2(q,l) __LOOP3(q,l)
#define __LOOP3(q,l) __REP(_lp ## l,q)
#define __REP(i,n) __RANGE(i,0,n)
#define __RANGE(i,a,n) for(int i=((int)a);i<((int)n);++i)
#define __RREP(i,n) __RRANGE(i,0,n)
#define __RRANGE(i,a,n) for(int i=((int)(n)-1);i>=((int)a);--i)
#define sz(a) ((int)(a).size())
#define pb push_back
#define eb emplace_back

/*
 * Constants
 */
constexpr ll LINF=1ll<<60;
constexpr int INF=1000000;
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
template<class T>constexpr bool chmax(T&a, typename std::type_identity<T>::type b){return a<b?(a=b,true):false;}
template<class T>constexpr bool chmin(T&a, typename std::type_identity<T>::type b){return a>b?(a=b,true):false;}
template<class S>S sum(vector<S>&a){return accumulate(all(a),S());}
template<class S>S max(vector<S>&a){return *max_element(all(a));}
template<class S>S min(vector<S>&a){return *min_element(all(a));}
ll sumAtoB(ll a,ll b){return (a+b)*(b-a+1)/2;}

namespace IO {
	// concepts定義
	template<typename T> concept Iterable = ranges::range<T> && !is_convertible_v<T, string_view>;
	template<typename T> concept RecursiveIterable = Iterable<T> && ranges::range<ranges::range_value_t<T>>;
	template<typename T> concept TupleLike = !Iterable<T> && requires(T a) {
		tuple_size<T>::value;
		get<0>(a);
		!is_convertible_v<T, string_view>;
	};

	// output
	constexpr ostream&operator<<(ostream&os, TupleLike auto a){
		apply([&](auto&&...args){((os<<args<<' '),...);}, a);
		return os;
	}
	constexpr ostream&operator<<(ostream&os, Iterable auto a){
		if(!a.empty()){
			auto b=begin(a), e=end(a);
			os<<(*b++);
			while(b!=e){ os<<' '<<(*b++); }
		}
		return os;
	}
	constexpr ostream&operator<<(ostream&os, RecursiveIterable auto a){
		if(!a.empty()){
			auto b=begin(a), e=end(a);
			os<<(*b++);
			while(b!=e){ os<<'\n'<<(*b++); }
		}
		return os;
	}

	template<class T, class...Ts> constexpr ostream& pargs(ostream&os, T&&t, Ts&&...args) {
		return ((os<<t)<<...<<(os<<' ', args));
	}
	template<class...Ts> constexpr ostream& out(Ts...args) { return pargs(cout, args...)<<'\n'; }
	template<class...Ts> constexpr ostream& out_f(Ts...args) { return pargs(cout, args...)<<'\n'<<flush; }
	template<class...Ts> constexpr ostream& debug_f(Ts...args) { return pargs(cerr, args...)<<'\n'<<flush; }
	#ifdef _DEBUG
	template<class...Ts> constexpr ostream& debug(Ts...args) { return pargs(cerr, args...)<<'\n'; }
	#else
	#define debug(...) if(false)debug_f(__VA_ARGS__)
	#endif
	void Yn(bool f) { out(f?"Yes":"No"); }

	// input
	constexpr auto&operator>>(istream&is, Iterable auto&t){ for(auto&a:t)is>>a; return is; }
	constexpr auto&operator>>(istream&is, TupleLike auto&t){
		apply([&](auto&&...args){((is>>args),...);}, t);
		return is;
	};

	template<class T, class...Ts> constexpr istream& gargs(istream&is, T&&t, Ts&&...args) {
		return ((is>>t)>>...>>args);
	}
	template<typename...S>auto&in(S&...s){return gargs(cin, s...);}
	#define def(t,...) t __VA_ARGS__; in(__VA_ARGS__)
}
using namespace IO;

class Random {
public:
	typedef uint_fast32_t result_type;
	constexpr result_type operator()(){return operator()((ll)min(),(ll)max());}
	static constexpr result_type max(){return numeric_limits<result_type>::max();}
	static constexpr result_type min(){return 0;}
	constexpr Random(const bool&isDeterministic):y(isDeterministic?2463534242:chrono::system_clock::now().time_since_epoch().count()){ }
	constexpr int operator()(int a,int b){return next()%(b-a)+a;}
	constexpr ll operator()(ll a,ll b){return (((ull)next())<<32|next())%(b-a)+a;}
	constexpr double operator()(double a,double b){
		// [a, b) の一様乱数
		double scale = (double)next() / (double)std::numeric_limits<uint_fast32_t>::max();
		return scale*(b - a) + a;
	}
private:
	result_type y;
	constexpr result_type next(){
		y ^= (y << 13);
		y ^= (y >> 17);
		y ^= (y << 5);
		return y;
	}
};

inline float t_sqrtF( const float& x )
{
	float xHalf = 0.5f * x;
	int   tmp   = 0x5f3700a0 - ( *(int*)&x >> 1 );
	float xRes  = *(float*)&tmp;
	xRes *= ( 1.5f - ( xHalf * xRes * xRes ) );
	return xRes * x;
}


#ifdef _DEBUG
Random rnd(1); // デバッグ時は固定シード
#else
Random rnd(1); // 本番用は可変シード
#endif

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
	uint64_t get() const { return (getClocks()-start)/ClocksPerMsec; }
	operator bool() const { return getClocks()<limit; }
	float persentile() const { return (float)get()/((float)limit/ClocksPerMsec); }
};
void wait(const int&msec){Timer tm(msec); while(tm);}

struct Mgr {
	#ifdef _DEBUG
	static const int TLE = 2000; // ms
	#else
	static const int TLE = 2000; // ms
	#endif
	static inline Timer timer = Timer(TLE-70);
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
		static inline size_t hash_rnd = rnd(0,INF); // 適当に初期化
		static const inline size_t hash_value = 0x9e3779b9;
		template<class V, class P=remove_const_t<remove_reference_t<V>>>
		static size_t& do_hash(size_t&seed, V&v) {
			return seed ^= hash<P>{}(v) + hash_value + (seed<<6) + (seed>>2);
		}
	};

	template<class S, class T>
	struct hash<pair<S,T>> : public hash_base<pair<S,T>> {
		size_t operator()(pair<S,T> p) const {
			size_t seed= this->hash_rnd;
			this->do_hash(seed, p.first);
			this->do_hash(seed, p.second);
			return seed;
		}
	};

	template<class...Ts>
	struct hash<tuple<Ts...>> : public hash_base<tuple<Ts...>> {
		size_t operator()(tuple<Ts...> t) const {
			size_t seed= this->hash_rnd;
			apply([&](auto&&...args){
				((this->do_hash(seed, args)),...);
			}, t);
			return seed;
		}
	};
}

template<class T>struct Graph;
template<class T>struct DFSResult{
	vb connected;
	vector<T> distance;
	vi preorder, postorder, eulertour, subtreeNodeCount;
	vl subtreePathLengthSum;
	DFSResult(Graph<T>&g):
		connected(g.size,false),
		distance(g.size,g.INF_VAL),
		preorder(g.size,-1),
		postorder(g.size,-1),
		subtreeNodeCount(g.size,1),
		subtreePathLengthSum(g.size,0){
			eulertour.reserve(g.size*2);
	}
};
template<class T=ll>struct Graph{
	int size;
	T INF_VAL;
	vector<HashMap<ll,T>>edge;
	Graph(int n=1,T inf=INF):size(n),INF_VAL(inf){edge.resize(size);}
	constexpr void add(ll from, ll to, T cost, bool directed=false){
		edge[from][to]=cost;
		if(!directed) edge[to][from]=cost;
	}
	constexpr void remove(ll from, ll to, bool directed=false){
		if(edge[from].contains(to)){
			edge[from].erase(to);
			if(!directed) edge[to].erase(from);
		}
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
		const function<void(int)> dfsrec=[this, &ret ,&pre, &post, &dfsrec](int p){
			ret.connected[p]=true;
			ret.preorder[p]=pre++;
			ret.eulertour.emplace_back(p);
			for(auto[to,cost]:edge[p])if(!ret.connected[to]){
				ret.distance[to]=ret.distance[p]+cost;
				dfsrec(to);
				ret.subtreePathLengthSum[p]+=ret.subtreePathLengthSum[to] + ret.subtreeNodeCount[to] * cost;
				ret.subtreeNodeCount[p]+=ret.subtreeNodeCount[to];
			}
			ret.postorder[p]=post++;
			ret.eulertour.emplace_back(p);
		};
		dfsrec(s);
		return ret;
	};
	// BFSする。この関数は変更しない
	constexpr vector<T> bfs(int s){
		vector<T> ret(size,INF_VAL);
		deque<int> q;
		ret[q.emplace_back(s)]=0;
		while(!q.empty()){
			int p=q.front(); q.pop_front();
			vi toList;
			for(auto[to,cost]:edge[p])if(chmin(ret[to],ret[p]+cost)){
				q.push_back(to);
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


template<class T=int>
struct UnionFind{
	vi par; vector<T> dist;
	UnionFind(int x){par.assign(x,-1); dist.assign(x,T());}
	int find(int x){return par[x]<0?x:find(par[x]);}
	T depth(int x){return par[x]<0?T():depth(par[x])+dist[x];}
	bool same(int x,int y){return find(x)==find(y);}
	int size(int x){return -par[find(x)];}
	T diff(int x,int y){return same(x,y)?depth(x)-depth(y):LINF;}
	bool unite(int x, int y, T k=T()){
		k+=depth(y); k-=depth(x); k=-k;
		x=find(x); y=find(y);
		if(x==y)return false;
		if(size(x)<size(y)){swap(x,y);k=-k;}
		par[x]+=par[y]; par[y]=x; dist[y]=k;
		return true;
	}
	HashMap<int,vi> groups(){
		HashMap<int,vi> ret;
		rep(i,par.size()) ret[find(i)].push_back(i);
		return ret;
	}
};

template<class T>struct Kruskal{
	Graph<T> g;
	Kruskal(Graph<T> g):g(g){}
	T calc(){
		T ans=0;
		UnionFind uf(g.size);
		vector<tuple<T,ll,ll>> edge;
		rep(from,g.size)for(auto&[to,cost]:g.edge[from])edge.emplace_back(cost,from,to);
		sort(all(edge));
		for(auto&[cost,from,to]:edge)if(uf.unite(from,to))ans+=cost;
		return ans;
	}
	vector<pii> calcEdge(){
		vector<pii> ret;

		T ans=0;
		UnionFind uf(g.size);
		vector<tuple<T,ll,ll>> edge;
		rep(from,g.size)for(auto&[to,cost]:g.edge[from])edge.emplace_back(cost,from,to);
		sort(all(edge));

		// vi shKey(g.size); iota(all(shKey),0); shuffle(all(shKey), rnd);
		// sort(all(edge), [&](auto&l, auto&r){
		// 	auto [a,b,c]=l;
		// 	auto [d,e,f]=r;
		// 	return a==d ? (shKey[b] == shKey[e] ? shKey[c] < shKey[f] : shKey[b] < shKey[e]) : a < d;
		// });

		for(auto&[cost,from,to]:edge)if(uf.unite(from,to)){
			ans+=cost;
			ret.emplace_back(from, to);
		}
		return ret;
	}
};

template<class T=ll>struct Dijkstra{
	Graph<T> g;
	Dijkstra(Graph<T> g):g(g){}
	vector<T>dist(ll s){
		vector<T> ret(g.size, g.INF_VAL);
		priority_queue<tuple<T,ll>> q;
		q.emplace(T(),s);
		while(!q.empty()){
			auto[c,p]=q.top(); q.pop();
			if(ret[p]!=g.INF_VAL)continue;
			ret[p]=abs(c);
			for(auto&[nxt,cost]:g.edge[p]){
				if(ret[nxt]<=ret[p]+cost)continue;
				q.emplace(-ret[p]-cost,nxt);
			}
		}
		return ret;
	}
	T dist(ll s,ll t){return dist(s)[t];}
};

/* ------ ここから下が必要な実装 ------ */
const int N=800, Q=400;
int M,L,W;
vector<int> G;

struct Rect {
	int lx, rx, ly, ry;
	int _w, _cx, _cy;

	Rect(){}
	Rect(int _lx, int _rx, int _ly, int _ry): lx(_lx), rx(_rx), ly(_ly), ry(_ry) {
		int wx=rx-lx, wy=ry-ly;
		_w = max(wx, wy);
		_cx = max(min(lx==0 ? (rx - _w/2) : (lx + _w/2), rx), lx);
		_cy = max(min(ly==0 ? (ry - _w/2) : (ly + _w/2), ry), ly);
	}	
};
vector<Rect> rects(N);

#ifdef _DEBUG
vector<pii> _TRUE_ANS(N);
#endif

#ifdef _DEBUG
// #define _OPTIMIZED 1
#endif



void input() {
	int _, __;
	in(_,M,__,L,W);
	G.resize(M);
	in(G);
	rep(i,N){
		def(int,lx,rx,ly,ry);
		rects[i] = Rect(lx, rx, ly, ry);
	}

	#ifdef _DEBUG
	rep(i,N){
		in(_TRUE_ANS[i].first, _TRUE_ANS[i].second);
	}
	#endif
}

HashSet<pii> query(vector<int> C) {
	out_f("?", C.size(), C);
	// debug("?",C);

	#ifdef _DEBUG
	static array<array<int, N>, N> distMap;
	if(distMap[0][0]==0){
		rep(i,N)rep(j,N){
			int dx = abs(_TRUE_ANS[i].first - _TRUE_ANS[j].first);
			int dy = abs(_TRUE_ANS[i].second - _TRUE_ANS[j].second);
			distMap[i][j] = t_sqrtF(dx*dx + dy*dy);
		}
	}
	vector<pii> nodes;
	rep(i,sz(C))rep(j,i,sz(C)){
		nodes.emplace_back(min(C[i],C[j]), max(C[i],C[j]));
	}
	sort(all(nodes), [&](pii a, pii b){
		return distMap[a.first][a.second] < distMap[b.first][b.second];
	});
	UnionFind uf(N);
	HashSet<pii> ans;
	for(auto [a, b] : nodes){
		if(uf.unite(a, b)){
			ans.insert({a,b});
		}
	}

	return ans;
	#else
	HashSet<pii> ans;
	rep(i,sz(C)-1) {
		def(int,a,b);
		ans.insert({a,b});
		// debug(a,b);
	}
	return ans;
	#endif
}

Graph<int> createMSTGraph() {
	Graph<int> mstG(N);
	HashSet<pii> used;
	{
		Graph<int> g(N);
		rep(i,N)rep(j,i+1,N){
			if(used.contains({i, j})) continue;
			int dx = abs(rects[i]._cx - rects[j]._cx);
			int dy = abs(rects[i]._cy - rects[j]._cy);
			#ifdef _OPTIMIZED
			dx = abs(_TRUE_ANS[i].first - _TRUE_ANS[j].first);
			dy = abs(_TRUE_ANS[i].second - _TRUE_ANS[j].second);
			#endif

			int dw = rects[i]._w + rects[j]._w;
			g.add(i, j, t_sqrtF(dx*dx + dy*dy));
		}

		Kruskal<int> kruskal(g);
		auto mst = kruskal.calcEdge();

		for(auto [a, b] : mst){
			mstG.add(a, b, 1);
			used.insert({a, b});
		}
	}
	return mstG;
}

void queryOptimize(Graph<int>&gQuery){
	vi selectedCount(N,0);
	vi indexedCount(N,0);

	HashSet<pii> MSTEdges, notMSTEdges;
	rep(Q){
		int idx = -1;
		rep(i,N) {
			if(selectedCount[i]) continue;
			// if(gQuery.edge[idx].size() < gQuery.edge[i].size()) idx = i;
			int wxidx=rects[idx].rx-rects[idx].lx;
			int wyidx=rects[idx].ry-rects[idx].ly;
			int wx=rects[i].rx-rects[i].lx;
			int wy=rects[i].ry-rects[i].ly;
			// int maxwidx = wxidx * wyidx;
			// int maxw = wx * wy;
			int maxwidx = max(wxidx, wyidx);
			int maxw = max(wx, wy);
			if(maxwidx < maxw) idx=i;
			if(idx == -1) idx = i;
		}
		if(idx==-1) rep(i,N) {
			if(indexedCount[i]) continue;
			// if(gQuery.edge[idx].size() < gQuery.edge[i].size()) idx = i;
			int wxidx=rects[idx].rx-rects[idx].lx;
			int wyidx=rects[idx].ry-rects[idx].ly;
			int wx=rects[i].rx-rects[i].lx;
			int wy=rects[i].ry-rects[i].ly;
			// int maxwidx = wxidx * wyidx;
			// int maxw = wx * wy;
			int maxwidx = max(wxidx, wyidx);
			int maxw = max(wx, wy);
			if(maxwidx < maxw) idx=i;
			if(idx == -1) idx = i;
		}
		indexedCount[idx]++;

		vi C;
		{
			vi orders(N); iota(all(orders), 0);
			auto dijk = gQuery.bfs(idx);
			sort(all(orders), [&](int a, int b){
				return dijk[a] == dijk[b] ? selectedCount[a] < selectedCount[b] : dijk[a] < dijk[b];
			});
			rep(i,L) {
				C.push_back(orders[i]);
				selectedCount[orders[i]]++;
			}
		}


		auto mstContained = query(C);
		for(auto [a, b] : mstContained){
			if(!gQuery.edge[a].contains(b)){
			// if(!gQuery.edge[a].contains(b) && !notMSTEdges.contains({min(a, b), max(a, b)})){
				gQuery.add(a, b, 1);
				MSTEdges.insert({min(a, b), max(a, b)});
			}
		}
		rep(j,L)rep(i,j)if(gQuery.edge[C[i]].contains(C[j]) && !mstContained.contains({min(C[i], C[j]), max(C[i], C[j])})){
			gQuery.remove(C[i], C[j]);

			auto d=gQuery.bfs(0);
			auto dmax=max(d);
			if(dmax == INF) {
				gQuery.add(C[i], C[j], 1);
				continue;
			}
			
			notMSTEdges.insert({min(C[i], C[j]), max(C[i], C[j])});
		}
	}
}

auto decideCluster_failsafe(Graph<int> gQueryMST){
	vi orders(N); iota(all(orders), 0);
	auto dfsres = gQueryMST.dfs(0);
	sort(all(orders), [&](int a, int b){
		return dfsres.preorder[a] < dfsres.preorder[b];
	});

	vector<vector<int>> clusters;
	int idx = 0;
	for(auto& gs : G){
		vi nodes;
		rep(i,gs){
			nodes.push_back(orders[idx++]);
		}
		clusters.push_back(nodes);
	}
	return clusters;
}


auto decideCluster(Graph<int> gQueryMST){

	vvi clusters(M);
	vp undecidedCluster;
	rep(i,M) {
		undecidedCluster.emplace_back(G[i], i);
	}
	sort(rall(undecidedCluster));

	HashSet<int> unusedNodes;
	rep(i,N) unusedNodes.insert(i);


	int failedCount=0;
	while(!unusedNodes.empty()){
		failedCount++;
		if(failedCount>100) {
			return vvi();
		}

		int idx=0;
		{
			vi _nodes(all(unusedNodes));
			idx = _nodes[rnd(0, sz(_nodes))];
		}
		auto dfsres = gQueryMST.dfs(idx);

		vp subTreeNodeCount;
		rep(i,N) subTreeNodeCount.emplace_back(dfsres.subtreeNodeCount[i], i);
		sort(rall(subTreeNodeCount));

		bool isClustered = false;
		for(auto& [nCount, nIndex] : subTreeNodeCount){
			if(!unusedNodes.contains(nIndex)) continue;
			for(auto&[cCount,cIndex]: undecidedCluster){
				if(nCount!=cCount) continue;
				vi subtree;
				{
					queue<int> q;
					q.push(nIndex);
					while(!q.empty()){
						int p=q.front(); q.pop();
						subtree.push_back(p);
						for(auto&[to,_]:gQueryMST.edge[p]){
							if(dfsres.distance[to]==dfsres.distance[p]+1)q.push(to);
						}
					}
				}

				// debug("Cluster", cIndex, ":", subtree);
				isClustered = true;
				failedCount=0;

				for(auto p : subtree) unusedNodes.erase(p);
				clusters[cIndex] = subtree;
				cCount=0; cIndex=-1;

				for(auto p : subtree){
					vi toList;
					for(auto[to,_]:gQueryMST.edge[p]){
						toList.push_back(to);
					}
					for(auto to : toList){
						gQueryMST.remove(p, to);
					}
				}

				break;
			}
			if(isClustered) break;
		}
		
		undecidedCluster.erase(remove_if(all(undecidedCluster), [&](auto& p){
			return p.first==0;
		}), undecidedCluster.end());
	}

	return clusters;
}

auto decideCluster2(Graph<int> gQueryMST){

	vvi clusters(M);
	vp undecidedCluster;
	rep(i,M) {
		undecidedCluster.emplace_back(G[i], i);
	}
	sort(rall(undecidedCluster));

	HashSet<int> unusedNodes;
	rep(i,N) unusedNodes.insert(i);

	for(auto&[clusterSize, clusterIdx]: undecidedCluster){
		bool isClustered = false;
		for(auto&idx:unusedNodes){
			auto dfsres = gQueryMST.dfs(idx);
			if(find(all(dfsres.subtreeNodeCount), clusterSize) == dfsres.subtreeNodeCount.end()){
				continue;
			}
			isClustered = true;

			vi subtree;
			{
				int subtreeRoot = find(all(dfsres.subtreeNodeCount), clusterSize) - dfsres.subtreeNodeCount.begin();
				queue<int> q;
				q.push(subtreeRoot);
				while(!q.empty()){
					int p=q.front(); q.pop();
					subtree.push_back(p);
					for(auto&[to,_]:gQueryMST.edge[p]){
						if(dfsres.distance[to]==dfsres.distance[p]+1)q.push(to);
					}
				}
			}

			for(auto p : subtree) unusedNodes.erase(p);
			clusters[clusterIdx] = subtree;

			for(auto p : subtree){
				vi toList;
				for(auto[to,_]:gQueryMST.edge[p]){
					toList.push_back(to);
				}
				for(auto to : toList){
					gQueryMST.remove(p, to);
				}
			}

			break;
		}
		if(!isClustered){
			return vvi();
		}
	}

	return clusters;
}


template<class T> pair<int,T> getMaxAndIndex(vector<T> a){
	int p=-1; T v=numeric_limits<T>::min();
	rep(i,a.size())if(chmax(v,a[i]))p=i;
	return {p,v};
}

auto decideCluster3(Graph<int> gQueryMST){
	auto dfs=gQueryMST.dfs(0);
	if(max(dfs.distance) == INF) {
		return vvi();
	}

	vvi clusters(M);
	vp undecidedCluster;
	rep(i,M) {
		undecidedCluster.emplace_back(G[i], i);
	}
	sort(all(undecidedCluster));

	vb connected(N,false);
	int cIdx=0;
	const function<void(int)> dfsrec=[&](int p){
		connected[p]=true;
		for(auto[to,cost]:gQueryMST.edge[p])if(!connected[to]){
			dfsrec(to);
		}

		auto& targetCluster = undecidedCluster[cIdx];
		clusters[targetCluster.second].push_back(p);
		if(--targetCluster.first==0){
			cIdx++;
		}

	};

	auto [s,_]=getMaxAndIndex(gQueryMST.bfs(0));
	auto [t,w]=getMaxAndIndex(gQueryMST.bfs(s));
	auto [__,d] = gQueryMST.bfs(s,t);
	dfsrec(d[d.size()/2]);

	return clusters;
}




vector<vector<int>> clusterMST(vector<int> G) {
	vvi queryEdges(N, vi(N, 0));
	Graph<int> gQuery(N);

	// 長方形の中心に仮置きしてMSTを構築
	gQuery = createMSTGraph();

	// クエリで近い頂点を投げつつ、MSTの情報を反映
	queryOptimize(gQuery);

	
	// クラスタを決定。クエリしたグラフ上でMSTをつくり、preorder順に訪問する
	vvi clusters;
	{
		auto qmst = Kruskal<int>(gQuery).calcEdge();
		Graph<int> gQueryMST(N);
		for(auto [a, b] : qmst){
			gQueryMST.add(a, b, gQuery.edge[a][b]);
		}

		clusters = decideCluster(gQueryMST);
		while(Mgr::timer.get() <= 1700){
			clusters = decideCluster(gQueryMST);
			if(!clusters.empty()) break;
		}
	}
		
	if(clusters.empty()){
		debug_f("failed to decideCluster1");

		auto qmst = Kruskal<int>(gQuery).calcEdge();
		Graph<int> gQueryMST(N);
		for(auto [a, b] : qmst){
			gQueryMST.add(a, b, gQuery.edge[a][b]);
		}
		clusters = decideCluster2(gQueryMST);
	}

	if(clusters.empty()){
		debug_f("failed to All decideCluster2");

		auto qmst = Kruskal<int>(gQuery).calcEdge();
		Graph<int> gQueryMST(N);
		for(auto [a, b] : qmst){
			gQueryMST.add(a, b, gQuery.edge[a][b]);
		}
		clusters = decideCluster3(gQueryMST);
	}

	if(clusters.empty()){
		debug_f("failed to All decideClusters");

		auto qmst = Kruskal<int>(gQuery).calcEdge();
		Graph<int> gQueryMST(N);
		for(auto [a, b] : qmst){
			gQueryMST.add(a, b, gQuery.edge[a][b]);
		}
		clusters = decideCluster_failsafe(gQueryMST);
	}


	// 完成したクラスタごとに、部分的なMSTを構築する
	// 元のグラフに残っている辺なら採用、そうでない辺は距離を計算して採用
	// TODO: クエリ過程で一度でも出てきた辺は優秀かも？
	int predict_length = 0;
	out("!");
	for(auto& c : clusters){
		out(c);
		Graph<int> part(sz(c));
		rep(i,sz(c))rep(j,i,sz(c)){
			if(gQuery.edge[c[i]].contains(c[j])){
				part.add(i, j, 0);
			}else{
				int dx = abs(rects[c[i]]._cx - rects[c[j]]._cx);
				int dy = abs(rects[c[i]]._cy - rects[c[j]]._cy);
				part.add(i, j, t_sqrtF(dx*dx + dy*dy));
			}
		}
		auto mst = Kruskal<int>(part).calcEdge();
		for(auto& [a, b] : mst){
			out(c[a], c[b]);
			int dx= abs(rects[c[a]]._cx - rects[c[b]]._cx);
			int dy= abs(rects[c[a]]._cy - rects[c[b]]._cy);
			predict_length += t_sqrtF(dx*dx + dy*dy);
		}
	}
	debug("predict_length", predict_length);

	#ifdef _DEBUG
	// 実際のスコアを計算
	{
		int score = 0;
		for(auto& c : clusters){
			Graph<int> part(sz(c));
			rep(i,sz(c))rep(j,i,sz(c)){
				if(gQuery.edge[c[i]].contains(c[j])){
					part.add(i, j, 0);
				}else{
					int dx = abs(rects[c[i]]._cx - rects[c[j]]._cx);
					int dy = abs(rects[c[i]]._cy - rects[c[j]]._cy);
					part.add(i, j, t_sqrtF(dx*dx + dy*dy));
				}
			}
			auto mst = Kruskal<int>(part).calcEdge();
			for(auto& [a, b] : mst){
				int dx= abs(_TRUE_ANS[c[a]].first - _TRUE_ANS[c[b]].first);
				int dy= abs(_TRUE_ANS[c[a]].second - _TRUE_ANS[c[b]].second);
				score += t_sqrtF(dx*dx + dy*dy);
			}
		}
		debug("score", score);
	}
	#endif


	return clusters;
}

int main() {
	input();
	
	const auto clusters = clusterMST( G);

}
