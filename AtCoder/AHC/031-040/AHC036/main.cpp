/**
 * C++23 Template @ AtCoder
 * - official support library
 *   - AC Library@1.5.1
 *   - Boost@1.82.0
 *   - GMP@6.2.1
 *   - Eigen@3.4.0-2ubuntu2
 * - compile option
 *   ```
 *     g++-12 -std=gnu++2b -O2 -DONLINE_JUDGE -DATCODER \
 *      -Wall -Wextra \
 *      -mtune=native -march=native \
 *      -fconstexpr-depth=2147483647 -fconstexpr-loop-limit=2147483647 -fconstexpr-ops-limit=2147483647 \
 *      -I/opt/ac-library -I/opt/boost/gcc/include -L/opt/boost/gcc/lib \
 *      -o a.out Main.cpp \
 *      -lgmpxx -lgmp \
 *      -I/usr/include/eigen3
 *   ```
 * - compiler information: https://docs.google.com/spreadsheets/d/1HXyOXt5bKwhKWXruzUvfMFHQtBxfZQ0047W7VVObnXI/edit#gid=408033513&range=F43
 */

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
#if defined(EVAL) || defined(ATCODER) || defined(_DEBUG)
#include <atcoder/all>
using namespace atcoder;
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
template<class T>constexpr bool chmax(T&a, type_identity_t<T> b){return a<b?a=b,1:0;}
template<class T>constexpr bool chmin(T&a, type_identity_t<T> b){return a>b?a=b,1:0;}
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
	constexpr ostream&operator<<(ostream&os, Iterable auto a){
		if(auto b=begin(a), e=end(a) ; a.size()) for(os<<(*b++);b!=e;os<<' '<<(*b++)) ;
		return os;
	}
	constexpr ostream&operator<<(ostream&os, RecursiveIterable auto a){
		if(auto b=begin(a), e=end(a) ; a.size()) for(os<<(*b++);b!=e;os<<'\n'<<(*b++)) ;
		return os;
	}
	constexpr ostream&operator<<(ostream&os, TupleLike auto a){
		apply([&](auto&&...args){((os<<args<<' '),...);}, a);
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
	constexpr Random(const bool&isDeterministic):y(isDeterministic?2463534242:chrono::system_clock::now().time_since_epoch().count()){}
	constexpr int operator()(int a,int b){return next()%(b-a)+a;}
	constexpr ll operator()(ll a,ll b){return (((ull)next())<<32|next())%(b-a)+a;}
	constexpr double operator()(double a,double b){return (b-a)*next()/4294967296.0+a;}
private:
	result_type y;
	constexpr result_type next(){return y^=(y^=(y^=y<<13)>>17)<<5;}
} Random(1);

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
	float persentile() const { return (float)get()/limit; }
};
void wait(const int&msec){Timer tm(msec); while(tm);}

struct Mgr {
	static const int TLE = 20000;
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
	vi preorder, postorder, eulertour, subtreeNodeCount;
	vl subtreePathLengthSum;
	vector<pair<ll, int>> subtreeDistance;
	DFSResult(Graph<T>&g):
		connected(g.size,false),
		distance(g.size,g.INF_VAL),
		preorder(g.size,-1),
		postorder(g.size,-1),
		subtreeNodeCount(g.size,1),
		subtreePathLengthSum(g.size,0),
		subtreeDistance(g.size,{0, -1}){
			eulertour.reserve(g.size*2);
	}
};
template<class T=int>struct Graph{
	int size;
	T INF_VAL;
	vector<vector<tuple<ll,T>>>edge, inverse;
	Graph(int n=1,T inf=INF):size(n),INF_VAL(inf){
		edge.resize(size);
		inverse.resize(size);
	}
	constexpr void add(ll from, ll to, T cost, bool directed=false){
		edge[from].emplace_back(to,cost);
		inverse[to].emplace_back(from,cost);
		if(!directed) {
			edge[to].emplace_back(from,cost);
			inverse[from].emplace_back(to,cost);
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
			ret.subtreeDistance[p]={0,p};
			for(auto[to,cost]:edge[p])if(!ret.connected[to]){
				ret.distance[to]=ret.distance[p]+cost;
				dfsrec(to);
				ret.subtreePathLengthSum[p]+=ret.subtreePathLengthSum[to] + ret.subtreeNodeCount[to] * cost;
				ret.subtreeNodeCount[p]+=ret.subtreeNodeCount[to];
				pair<T, int> subDist = {ret.subtreeDistance[to].first + cost, to};
				chmax(ret.subtreeDistance[p], subDist);
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


template<class T=ll>struct LongPathDecomposition{
	Graph<T> g;
	LongPathDecomposition(Graph<T> g):g(g){}

	struct LPDNode{
		vi path;
		int parentIdx;
	};
	struct BelongsTo{
		int path;
		int depth;
	};

	auto getLPD(int s){
		vector<LPDNode> lpds;
		vector<BelongsTo> belongsTo(g.size);

		auto dfs = g.dfs(s);
		queue<pair<int, int>> roots;
		roots.emplace(s, s);
		vb visited(g.size, false);
		while(!roots.empty()) {
			auto [root, parentIdx] = roots.front(); roots.pop();
			// out_f(root, ":", maxDistNode);

			if(visited[root]) continue;

			visited[root] = true;

			vi path;
			{
				int curNode = root;
				while(true) {
					int child = dfs.subtreeDistance[curNode].second;
					belongsTo[curNode] = {(int)lpds.size(), (int)path.size()};
					path.push_back(curNode);
					
					for(auto&[to, _]:g.edge[curNode]) {
						if(visited[to]) continue;
						if(to == child) continue;
						roots.emplace(to, curNode);
					}

					if(child == curNode) break;
					curNode = child;
				}
			}
			lpds.push_back({path, parentIdx});
		}
		return make_pair(lpds, belongsTo);
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
	T diff(int x,int y){return same(x,y)?depth(x)-depth(y):INF;}
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
	void clear() {
		fill(all(par), -1);
		fill(all(dist), T());
	}
};

template<class T>struct Kruskal{
	Graph<T> g;
	Kruskal(Graph<T> g):g(g){}
	Graph<T> calc(){
		Graph<T> ret(g.size);
		UnionFind uf(g.size);
		vector<tuple<T,ll,ll>> edge;
		rep(from,g.size)for(auto&[to,cost]:g.edge[from])edge.emplace_back(cost,from,to);
		sort(all(edge));
		for(auto&[cost,from,to]:edge)if(uf.unite(from,to)){
			ret.add(from,to,cost);
		}
		return ret;
	}
	Graph<T> calcMax(){
		Graph<T> ret(g.size);
		UnionFind uf(g.size);
		vector<tuple<T,ll,ll>> edge;
		rep(from,g.size)for(auto&[to,cost]:g.edge[from])edge.emplace_back(cost,from,to);
		sort(rall(edge));
		for(auto&[cost,from,to]:edge)if(uf.unite(from,to)){
			ret.add(from,to,cost);
		}
		return ret;
	}
};

/*
 N: 都市の数 = 600
 M: 道路の数 = N-1 ~ 3N-6
 T: 訪問地点の数 = 600
 La: 信号DBの要素数 = N ~ 2N
 Lb: 同時につけられる信号の数 = 4 ~ 24
*/
int N,M,T,La,Lb;
array<array<int, 600>, 600> edge;
vvi adjacentList(600);
array<int, 600> tList;

void input() {
	in(N,M,T,La,Lb);
	rep(i, N) fill(all(edge[i]), 0);
	rep(i,M) {
		def(int,u,v);
		edge[u][v] = edge[v][u] = 1;
		adjacentList[u].push_back(v);
		adjacentList[v].push_back(u);
	}
	in(tList);
}

class GraphSolver {
public:
    vi solve(Graph<int> &g) {
        int n = g.size;

        // 各頂点からBFSで最短経路を求める
        vector<vector<int>> shortest_paths(n);
        for (int i = 0; i < n; ++i) {
            shortest_paths[i] = g.bfs(i);
        }

		vvi usedShortestPath(n, vi(n, 0));
		int currentPos = 0;
		for(auto&t:tList) {
			// currentPos -> t  に移動しながら、最短経路を復元
			vi path(1, currentPos);
			int cur = currentPos;
			while(cur != t) {
				for(auto&[to,_]:g.edge[cur]) {
					if(shortest_paths[to][t] + 1 == shortest_paths[cur][t]) {
						path.push_back(to);
						cur = to;
						break;
					}
				}
			}
			rep(i, sz(path)-1) {
				usedShortestPath[path[i]][path[i+1]]++;
				usedShortestPath[path[i+1]][path[i]]++;
			}
			currentPos = t;
		}

		Graph<int> weightedGraph(N, INF);
		float weightPower = Random(0.2, 1.0);
		rep(i,N) for(auto[j,_]:g.edge[i]) {
			weightedGraph.add(i, j, (int)pow(usedShortestPath[i][j],weightPower)+1, true);
		}

        // 最短距離のパスでの利用回数が最大になる全域木を構築
		auto mst = Kruskal<int>(weightedGraph).calcMax();
		// rep(i,N) for(auto&[j,c]:mst.edge[i]) c=1;

        // 奇数度の頂点を見つける
        unordered_set<int> odd_degree_nodes;
        for (int i = 0; i < n; ++i) {
            if (mst.edge[i].size() % 2 == 1) {
                odd_degree_nodes.insert(i);
            }
        }

        // 奇数度の頂点ペアを結ぶ（最も遠いペアを選ぶ）
        while (odd_degree_nodes.size() > 1) {
            int min_distance = INF;
            int u = -1, v = -1;

            for (int i : odd_degree_nodes) {
                for (int j : odd_degree_nodes) {
                    if (i != j && chmin(min_distance, shortest_paths[i][j])) {
                        u = i;
                        v = j;
                    }
                }
            }

			if (min_distance <= Lb * 2+1) {
				// 最短経路で結ぶ
				int current = u;
				while (current != v) {
					for (int next : adjacentList[current]) {
						if (shortest_paths[next][v] + 1 == shortest_paths[current][v]) {
							mst.add(current, next, 1);
							current = next;
							break;
						}
					}
				}

				// 奇数度の頂点リストを更新
				odd_degree_nodes.erase(u);
				odd_degree_nodes.erase(v);
			} else {
				// 長さLbのパスだけ作る
				int current = u, pLength = 0;;
				while (current != v) {
					for (int next : adjacentList[current]) {
						if (shortest_paths[next][v] + 1 == shortest_paths[current][v]) {
							mst.add(current, next, 1);
							if(pLength == Lb) break;
							current = next;
							break;
						}
					}
				}

				// 奇数度の頂点リストを更新
				odd_degree_nodes.erase(u);
			}
        }

        // DFSで巡回路を構築
        vector<int> path;
        unordered_set<int> visited;
        dfs(mst, 0, visited, path);

        // 仮想辺i,jを元の最短経路に戻す
        vector<int> expanded_path;
        for (size_t i = 0; i < path.size() - 1; ++i) {
            int u = path[i];
            int v = path[i + 1];
            // if (shortest_paths[u][v] != 1) {  // 隣接していない場合
            //     vector<int> segment = reconstruct_path(shortest_paths, u, v);
            //     expanded_path.insert(expanded_path.end(), segment.begin(), segment.end() - 1);
            // } else {
                expanded_path.push_back(u);
            // }
        }
        expanded_path.push_back(path.back());

        return expanded_path;
    }

private:
    // DFSを使って巡回路を構築する
    void dfs(const Graph<int> &graph, int u, unordered_set<int> &visited, vector<int> &path) {
        visited.insert(u);
        path.push_back(u);
        for (const auto &[e, _] : graph.edge[u]) {
            if (visited.find(e) == visited.end()) {
                dfs(graph, e, visited, path);
            }
        }
    }

    // 元の最短経路を復元する
    vector<int> reconstruct_path(const vector<vector<int>> &shortest_paths, int u, int v) {
        vector<int> path;
        path.push_back(u);
        while (u != v) {
            for (int next : adjacentList[u]) {
                if (shortest_paths[next][v] + 1 == shortest_paths[u][v]) {
                    u = next;
                    path.push_back(u);
                    break;
                }
            }
        }
        return path;
    }
};

auto cyclicDb() {
	Graph<int> g(N, INF);
	rep(i, N) rep(j, i) if (edge[i][j]) {
		g.add(i, j, 1);
	}
	vi temp = GraphSolver().solve(g);
	// longPathDb();
	return temp;
}

auto decideDb() {
	Graph<int> g(N, INF);
	rep(i, N) rep(j, i) if (edge[i][j]) {
		g.add(i, j, 1);
	}

	// 操作DB
	vi db;
	vi bestMinimumRoute; int bestMinimumRouteLength = INF;
	rep(10) {
		vi temp = GraphSolver().solve(g);
		if(chmin(bestMinimumRouteLength, sz(temp))) bestMinimumRoute = temp;
		if(bestMinimumRouteLength <= La) break;
	}
	auto temp = bestMinimumRoute;
	debug_f("minimum cycle size = ", sz(temp));

	bool isContainCycle = false;

	if(sz(temp) <= La) {
		isContainCycle = true;
		db.insert(db.end(), all(temp));
		vi temp2 = GraphSolver().solve(g);
		vi temp3 = GraphSolver().solve(g);
		db.insert(db.end(), all(temp2));
		db.insert(db.end(), all(temp3));
		while(sz(db) > La) db.pop_back();
	} else {
		int ln = sz(temp);
		vb used(N, false);
		rep(i, sz(temp)) {
			if(ln==La){
				db.push_back(temp[i]);
				continue;
			}
			if(used[temp[i]]) {
				ln--;
				continue;
			}
			used[temp[i]] = true;
			db.push_back(temp[i]);
		}
	}
	return make_pair(isContainCycle, db);
}

auto calcAnswer_OptimizeCyclic(vi db) {
	Graph<int> g(N, INF);
	rep(i, N) rep(j, N) if (edge[i][j]) {
		g.add(i, j, 1);
	}

	// distFromGoalToDb[i][j] = db[i]を始点とするLb個の頂点がjを含むか
	const int L = La - Lb + 1;
	vector<HashSet<int>> nodeSet(L);
	vector<array<int, 600>> distFromGoalToDb(L);
	rep(i, L) {
		rep(j, Lb) {
			distFromGoalToDb[i][db[i + j]] = 1;
			nodeSet[i].insert(db[i + j]);
		}
	}

	// parentNodeInSet[i][j] = 集合i内の頂点のみ見た、頂点jから集合iの代表元までの経路上の親頂点
	vector<HashMap<int,int>> parentNodeInSet(L);
	rep(i,L) {
		HashSet<int> nodeSetTemp = nodeSet[i];
		int major = db[i], connectedNodeCount = 0;
		// nodeSet[i] の頂点のみを用いて、majorから幅優先
		queue<int> q;
		q.push(major);
		parentNodeInSet[i][major] = major;
		while(!q.empty()) {
			int p = q.front(); q.pop();
			nodeSetTemp.erase(p);
			connectedNodeCount++;
			for(auto&[to,_]: g.edge[p]) {
				if(nodeSet[i].contains(to) && !parentNodeInSet[i].contains(to)) {
					parentNodeInSet[i][to] = p;
					q.push(to);
				}
			}
		}

		// 集合が連結でない場合、連結でない頂点はないものとして扱う
		out_f("# omit", i, ":", nodeSetTemp);
		for(auto&v: nodeSetTemp) {
			distFromGoalToDb[i][v] = 0;
			nodeSet[i].erase(v);
		}
	}
	

	// dbConnected[i] = 頂点iから移動できる集合j=db[j:j+Lb)の集合
	vector<HashSet<int>> dbConnected(N);
	// dbConnectedNode[i][j] = 頂点iから集合jに移動した時、頂点iと、jのどの頂点が接続しているか
	vector<HashMap<int, int>> dbConnectedNode(N);
	rep(i,N) {
		for(auto&[to,_]:g.edge[i]) {
			rep(j, L) {
				if(distFromGoalToDb[j][to]) {
					dbConnected[i].insert(j);
					dbConnectedNode[i][j] = to;
				}
			}
		}
	}

	// dbConnectedGraph[i][j] = 集合iから集合jに移動できる場合有向辺
	Graph<int> dbConnectedGraph(L, INF), backTrackGraph(L, INF);
	// dbToDbConnectedNode[i][j] = 集合iから集合jに移動できる場合、iのどの頂点とjのどの頂点が接続しているか
	vector<vector<pair<int,int>>> dbToDbConnectedNode(L, vector<pair<int,int>>(L, {-1, -1}));
	rep(i,L) {
		// toMap[to] = 集合iから集合toに移動できるとき、頂点何から移動できるか
		HashMap<int, int> toMap;
		rep(j,Lb) {
			for(auto&to: dbConnected[db[i+j]]) {
				toMap[to] = db[i+j];
			}
		}
		for(auto&[to, fromNode] : toMap) if(to != i) {
			dbConnectedGraph.add(i, to, 1, true);
			backTrackGraph.add(to, i, 1, true);
			dbToDbConnectedNode[i][to] = {fromNode, dbConnectedNode[fromNode][to]};
		}
	}

	/* 集合内の移動経路モード */

	// 集合st内の頂点だけを利用して、fromからstの代表元までの経路を求める
	// fromは含まない方が都合がいいので入れない
	// Note: 各集合は高々24頂点なので、1177 * 24 * 23 通り全部メモれるかも
	auto getNodePathToMajor = [&](int st, int from) {
		int to = db[st];
		vi path;
		// parentNodeInSet[st]を利用して、fromからto(代表元)までの経路を復元
		while(from != to) {
			from = parentNodeInSet[st][from];
			path.push_back(from);
		}
		return path;
	};
	// 集合st内の頂点だけを利用して、aからbまでの経路を求める
	// aからtoに行って、toからbに行けばいい
	auto getNodePathAtoB = [&](int st, int a, int b) {
		auto atoMajor = getNodePathToMajor(st, a);
		if(atoMajor.empty()) {
			// a==db[st] の場合
			auto btoMajor = getNodePathToMajor(st, b);
			// a==db[st]==b の場合
			if(btoMajor.empty()) return vi{};
			btoMajor.pop_back(); reverse(all(btoMajor)); btoMajor.push_back(b);
			return btoMajor;
		}
		auto btoMajor = getNodePathToMajor(st, b);
		// db[st]==b の場合
		if(btoMajor.empty()) return atoMajor;

		reverse(all(btoMajor)); btoMajor.push_back(b);
		atoMajor.pop_back();
		atoMajor.insert(atoMajor.end(), all(btoMajor));
		return atoMajor;
	};

	vvi outputActions;
	int currentPos = 0, currentSet = -1;
	rep(i,T){
		auto t = tList[i];

		HashSet<int> containGoalSet;
		rep(j, L) {
			if(distFromGoalToDb[j][t]) {
				containGoalSet.insert(j);
			}
		}
		// backTrackGraph上で、containGoalSet内の要素を始点とした多始点BFS
		// このグラフを逆に辿れば、dbConnectedGraph上でcontainGoalSetまでの移動が可能
		vi parent(L, -1), dist(L, INF);
		queue<int> q;
		for(auto&j: containGoalSet) {
			q.push(j);
			parent[j] = j;
			dist[j] = 0;
		}
		while(!q.empty()) {
			int p = q.front(); q.pop();
			for(auto&[to,_]: backTrackGraph.edge[p]) {
				if(parent[to] == -1) {
					parent[to] = p;
					dist[to] = dist[p] + 1;
					q.push(to);
				}
			}
		}

		// backTrackGraph上で、dist=0の頂点からcurまで行くパスを復元
		//  == dbConnectedGraph上で、curからdist=0の頂点まで行くパスを作成
		auto getSetPath = [&](int cur) {
			vi path;
			while(cur != parent[cur]) {
				path.push_back(cur);
				cur = parent[cur];
			}
			path.push_back(cur);
			return path;
		};

		if(i==0){
			// 初手、信号集合が空の場合、始点は頂点0に隣接する頂点を含むすべての集合から選べる
			int selectBestInitialSet = -1, bestDist = INF;
			HashSet<int>&adjacentSet = dbConnected[0];
			for(auto&j: adjacentSet) {
				if(chmin(bestDist, dist[j])) {
					selectBestInitialSet = j;
				}
			}

			// 最初の集合を設定
			currentSet = selectBestInitialSet;
			outputActions.push_back({Lb, selectBestInitialSet, 0});
			// 頂点0から最初の頂点に移動
			currentPos = dbConnectedNode[0][selectBestInitialSet];
			outputActions.push_back({currentPos});
		}

		// 初手、いまcurrentSet集合のcurrentPosにいる場合
		auto path = getSetPath(currentSet);
		if(i==1) {
			out_f("#moveToNode", t);
			out_f("#moveSetPath", path);
		}
		// いまいる集合から次の集合に渡り歩く
		rep(j,sz(path)-1) {
			if(i==1) {
				out_f("#moveSet", path[j], path[j+1]);
			}

			auto [connectFrom, connectTo] = dbToDbConnectedNode[path[j]][path[j+1]];
			if(i==1) {
				out_f("#connect", connectFrom, connectTo);
			}

			// いまいる集合で、次の集合に隣接する頂点まで移動
			if(i==1) {
				out_f("#atob", nodeSet[path[j]], "/", currentPos, connectFrom);
			}
			auto nodePath = getNodePathAtoB(path[j], currentPos, connectFrom);
			for(auto&node: nodePath) {
				outputActions.push_back({node});
			}
			if(i==1) {
				out_f("#nodePath", currentPos, connectFrom , "=", nodePath);
			}

			// 集合を切り替え
			outputActions.push_back({Lb, path[j+1], 0});
			// 次の集合に移動
			outputActions.push_back({connectTo});
			currentPos = connectTo;
		}
		// 最後の集合に来たら、目的地まで移動
		if(i==1){
			out_f("#moveToNode", currentPos, db[path.back()], t);
		}
		
		auto nodePathToTarget = getNodePathAtoB(path.back(), currentPos, t);
		for(auto&node: nodePathToTarget) {
			outputActions.push_back({node});
		}
		if(i==1) {
			out_f("#LastMoveNode", currentPos, t , "=", nodePathToTarget);
		}

		currentPos = t;
		currentSet = path.back();
		out_f(i);
	}

	return outputActions;
}

auto calcAnswer_Universal(vi db) {
	Graph<int> g(N, INF);
	vector<HashSet<int>> edgeSet(N);

	rep(i, N) rep(j, N) if (edge[i][j]) {
		g.add(i, j, 1);
		edgeSet[i].insert(j);
		edgeSet[j].insert(i);
	}

	vvi distMap(N, vi(N, INF));
	rep(i, N) distMap[i] = g.bfs(i);


	// 操作DB
	vi blue(Lb, -1);

	vvi outputActions;
	int currentPos = 0;
	for(auto&t:tList){
		auto&distFromGoal = distMap[t];

		while(true) {
			int currentDist = distFromGoal[currentPos];
			int bestNextDist = currentDist;
			vvi bestAction;
			vi bestNextBlue = blue;

			rrep(len, max(Lb-6, 1), Lb+1) rep(to, Lb - len + 1) rep(from, La - len + 1) {
				auto newBlue = blue;
				rep(i, len) newBlue[to+i] = db[from+i];

				{
					bool ok=false;
					for(auto&b: newBlue) if(b != -1) {
						if(distFromGoal[b] == currentDist-1) {
							ok = true;
							break;
						}
					}
					if(!ok) continue;

					vi existentDistList(currentDist, 0);
					rep(i, Lb) if(newBlue[i] != -1) {
						if(distFromGoal[newBlue[i]] <= currentDist-1) {
							existentDistList[distFromGoal[newBlue[i]]] = 1;
						}
					}
					rrep(i, bestNextDist-1, currentDist) if(!existentDistList[i]) {
						ok = false;
						break;
					}

					if(!ok) continue;
				}

				// currentPosから、できるだけdistが小さい頂点に、newBlueに記述の頂点だけを通って移動
				queue<int> q; q.push(-1);
				vector<int> distOnlyBlue(Lb, -100);
				// debug_f(len, from, to);
				// debug_f(newBlue);
				while(!q.empty()){
					int partialPos = q.front(); q.pop();
					// debug_f(partialPos);
					rep(i, Lb) if(newBlue[i] != -1 and distOnlyBlue[i] == -100){
						if(partialPos == -1) {
							if(edge[currentPos][newBlue[i]]) {
								distOnlyBlue[i] = -1;
								q.push(i);
							}
						} else if(edge[newBlue[partialPos]][newBlue[i]]) {
							distOnlyBlue[i] = partialPos;
							q.push(i);
						}
					}
				}

				rep(i, Lb) if(newBlue[i] != -1 and distOnlyBlue[i] != -100) {
					int nextDist = distFromGoal[newBlue[i]];
					if(chmin(bestNextDist, nextDist)) {
						vi path(1, i);
						do {
							int next = distOnlyBlue[path.back()];
							if(next >= 0) path.push_back(next);
							else break;
						} while(true);

						bestNextBlue = newBlue;
						bestAction = {{len, from, to}};
						rrep(j, sz(path)) bestAction.push_back({newBlue[path[j]]});
					}
				}
			}

			outputActions.insert(outputActions.end(), all(bestAction));
			blue = bestNextBlue;
			currentPos = bestAction.back()[0];

			if(currentPos == t) break;
		}
	}

	return outputActions;
}

auto compressDb(vi db, vvi actions) {
	vi compressedDb;
	vvi compressedActions;
	vi usedRange(La, 1);
	for(auto&act: actions) {
		if(sz(act) == 3) {
			rep(i,act[1],act[1]+act[0]) {
				usedRange[i] = 0;
			}
		}
	}
	rep(i,La) if(!usedRange[i]) compressedDb.push_back(db[i]);
	partial_sum(all(usedRange), usedRange.begin());

	int score = 0;
	for(auto&act: actions) {
		if(sz(act) == 3) {
			vi newAct = {act[0], act[1] - usedRange[act[1]], act[2]};
			compressedActions.push_back(newAct);
			score++;
		} else {
			compressedActions.push_back(act);
		}
	}

	return make_tuple(compressedDb, compressedActions, score);
}

auto testCyclic() {
	auto db = cyclicDb();
	int defaultLa = La;
	La = sz(db);
	vvi outputActions = calcAnswer_OptimizeCyclic(db);
	auto [compressedDb, compressedOutputActions, score] = compressDb(db, outputActions);
	La = defaultLa;

	debug_f("test", sz(compressedDb), score);

	if(sz(compressedDb) > La) {
		return make_tuple(vi(), vvi(), INF);
	}

	rep(i, sz(compressedDb), La) {
		compressedDb.push_back(0);
	}

	return make_tuple(compressedDb, compressedOutputActions, score);
}

int main() {
	input();
	bool isCyclicAchieved = false;
	vi bestDb; vvi bestOutputActions;
	int bestScore = INF;

	{
		auto [db, outputActions, score] = testCyclic();
		if(sz(db) <= La && chmin(bestScore, score)) {
			bestDb = db;
			bestOutputActions = outputActions;
			isCyclicAchieved = true;
		}
	}

	if(!isCyclicAchieved){
		auto [isContainCycle, db] = decideDb();
		vvi outputActions;
		debug_f("universal");
		outputActions = calcAnswer_Universal(db);
		int score = 0;
		for(auto&act: outputActions) {
			score += sz(act) == 3;
		}
		if(chmin(bestScore, score)) {
			debug_f("Score", score);
			bestDb = db;
			bestOutputActions = outputActions;
		}
	}


	if(isCyclicAchieved){
		rep(i, 1, 1000){
			// あと2回やる余裕がないならやめる
			if(i) {
				int timeByLoop = Mgr::timer.get() / i;
				int expectedTime = Mgr::timer.get() + timeByLoop * 2;
				if(expectedTime > 2900) break;
			}

			auto [db, outputActions, score] = testCyclic();
			if(sz(db) <= La && chmin(bestScore, score)) {
				debug_f("Score", score);
				bestDb = db;
				bestOutputActions = outputActions;
			}
		}
	}

	out(bestDb);
	vi usedRange(La, false);
	for(auto&act: bestOutputActions) {
		if(sz(act) == 3) {
			out("s", act);
			rep(i,act[1],act[1]+act[0]) {
				usedRange[i] = true;
			}
		} else {
			out("m", act);
		}
	}
}