#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("inline")

#pragma GCC diagnostic ignored "-Wunused-value"
#ifdef _DEBUG
// #define _GLIBCXX_DEBUG 1
#endif

/* 
 * Include Headers
 */
#include <algorithm>
#include <iostream>
#include <cstdio>
#include <map>
#include <numeric>
#include <cmath>
#include <set>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <complex>
#include <string.h>
#include <unordered_set>
#include <unordered_map>
#include <bitset>
#include <iomanip>
#include <sys/time.h>
#include <tuple>
#include <random>
#include <chrono>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;

/*
 * Additional Type Definition
 */
using ll = int;
using vl = vector<ll>;
using vvl = vector<vl>;
using vb=vector<bool>;
using vvb=vector<vb>;
using vi=vector<int>;
using vvi=vector<vi>;
using pii=pair<int,int>;
using vp=vector<pii>;
using ti2=tuple<int,int>;
using ti3=tuple<int,int,int>;
using ti4=tuple<int,int,int,int>;
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
#define __RANGE(i,a,n) for(int i=((int)a);i<((int)n);++i)
#define __RREP(i,n) __RRANGE(i,0,n)
#define __RRANGE(i,a,n) for(int i=((int)((n)-1));i>=((int)a);--i)
#define siz(a) ((int)(a).size())

/*
 * Constants
 */
constexpr int INF=1<<29;
constexpr int LINF=1<<29;

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
		if(auto b=begin(t), e=end(t) ; !t.empty()) for(os<<(*b++);b!=e;os<<Separator<<(*b++)) ;
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
	template<class...Ts> constexpr ostream& debug(Ts...args) { 
		return pargs(cerr, args...)<<'\n';
	}
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
	using result_type = unsigned int;
	constexpr result_type operator()(){return operator()(min(),max());}
	static constexpr result_type max(){return numeric_limits<result_type>::max();}
	static constexpr result_type min(){return 0;}
	constexpr Random(const bool&isDeterministic):y(isDeterministic?2463534242ll:chrono::system_clock::now().time_since_epoch().count()){}
	constexpr result_type operator()(result_type a, result_type b){return next()%(b-a)+a;}
	constexpr double operator()(double a,double b){return (b-a)*next()/4294967296.0+a;}
	result_type getSeed(){return y;}
	void setSeed(result_type seed){y=seed;}
private:
	result_type y;
	constexpr result_type next(){return y^=(y^=(y^=y<<13)>>17)<<5;}
}
#ifdef _DEBUG
Random(1);
#else
Random(1);
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
	uint64_t get() const{return (getClocks()-start)/ClocksPerMsec;}
	operator bool()const{return getClocks()<limit;}
};
void wait(const int&msec){Timer tm(msec); while(tm);}

struct Mgr {
	static const int TLE = 2000;
	static inline Timer timer = Timer(TLE-20);
	Mgr() {
		ios_base::sync_with_stdio(0); cin.tie(0);
		cerr<<fixed<<setprecision(3);
	}
	~Mgr(){
		debug_f(timer.get(), "ms")<<flush;
	}
} _manager;

namespace std::tr1 {
	template<class S, class T>
	struct hash<pair<S,T>> {
		size_t operator()(pair<S,T> p) const {
			return (p.first << 7) ^ p.second;
		}
	};
}


struct Point {
	int y, x;
	int getDist(int p, int q) {
		return (int)ceil(sqrt((y-p)*(y-p) + (x-q)*(x-q)));
	}
};

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
template<class T=int>struct Dijkstra{
	Graph<T> g;
	Dijkstra(Graph<T> g):g(g){}
	vector<T>dist(int s){
		vector<T> ret(g.size, g.INF_VAL);
		priority_queue<tuple<T,int>> q;
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
	T dist(int s,int t){return dist(s)[t];}
	pair<T, vi> distAndPath(int s, int t){
		auto d=dist(s);
		return {d[t],getPath(t,d)};
	}
};

template<class T=ll>
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
	pair<T, Tree<T>> calc(){
		Tree<T> ret(g.size);
		T ans=0;
		UnionFind uf(g.size);
		vector<tuple<T,ll,ll>> edge;
		rep(from,g.size)for(auto&[to,cost]:g.edge[from])edge.emplace_back(cost,from,to);
		sort(all(edge));
		for(auto&[cost,from,to]:edge)if(uf.unite(from,to)){
			ans+=cost;
			ret.add(from,to,cost);
		}
		return {ans,ret};
	}
};

template<class T=ll>struct WarshallFloyd{
	Graph<T> g;
	WarshallFloyd(Graph<T> g):g(g){}
	pair<bool, vector<vector<T>>>dist(){
		bool isNegativeCycle=false;
		vector<vector<T>> ret(g.size,vector<T>(g.size,g.INF_VAL));
		rep(f,g.size){
			ret[f][f]=0;
			for(auto&[t,c]:g.edge[f])ret[f][t]=c;
		}
		rep(k,g.size)rep(i,g.size)if(ret[i][k]!=g.INF_VAL)
			rep(j,g.size)if(ret[k][j]!=g.INF_VAL)
				chmin(ret[i][j],ret[i][k]+ret[k][j]);
		rep(i,g.size)isNegativeCycle|=ret[i][i]<0;
		return {isNegativeCycle,ret};
	}
};

const int N = 100; int M, K;
vector<Point> hoso(N), hito;
vvi edge(N, vi(N, INF));
vector<pii> rawEdges;
HashMap<pii, int> edgeIndex;
void input() {
	cin>>M;cin>>M>>K;
	rep(i,N) cin>>hoso[i].y>>hoso[i].x;
	rep(i,M) {
		int a, b, c; cin>>a>>b>>c; a--; b--;
		edge[a][b] = edge[b][a] = c;
		edgeIndex[{a, b}] = edgeIndex[{b, a}] = i;
		rawEdges.push_back({a, b});
	}
	rep(i,K) {
		int a, b; cin>>a>>b;
		hito.push_back({a, b});
	}
}


void getInitial2() {
	Graph<int> g(N);
	rep(i,N) rep(j,i) if(edge[i][j] != INF) {
		g.add(i, j, edge[i][j]);
	}
	auto [_, mst] = Kruskal<int>(g).calc();
	auto dist = mst.bfs(0);
	auto warshall = WarshallFloyd<int>(g).dist().second;
	vvi distHosoTohito(N, vi(K, INF));
	rep(i,N) rep(j,K) {
		distHosoTohito[i][j] = hoso[i].getDist(hito[j].y, hito[j].x);
	}

	vi powers(N, 0);
	rep(i,K){
		int bestCost=INF, bestHoso=0, bestDist = 0;
		rep(j,N) {
			int d = distHosoTohito[j][i];
			if(d > 5000)continue;
			int cost = dist[j] + d*d;
			if(chmin(bestCost, cost)) {
				bestHoso = j;
				bestDist = d;
			}
		}
		chmax(powers[bestHoso], bestDist);
	}

	using Reach = bitset<5000>;
	vector<Reach> reach(N);
	rep(i,N) {
		Reach reachable(0);
		rep(j,K){
			int d = distHosoTohito[i][j];
			if(d > powers[i])continue;
			reachable.set(j);
		}
		reach[i] = reachable;
	}

	// mst上の辺のみを採用し、使用しない頂点に紐づく辺を削除する
	vi edgeEnable(M, 0);
	{
		rep(i,N)for(auto&[to,cost]:mst.edge[i]) {
			int j = edgeIndex[{i, to}];
			edgeEnable[j] = 1;
		}
		queue<int> q;
		rep(i,1,N) if(mst.edge[i].size() == 1) q.push(i);
		while(!q.empty()) {
			int i = q.front(); q.pop();
			int j=0,cnt=0;
			for(auto&[to,cost]:mst.edge[i]){
				if(!edgeEnable[edgeIndex[{i, to}]])continue;
				cnt++;
				j = to;
			}
			if(cnt!=1)continue;

			int current = dist[i] < dist[j] ? j : i;
			int next = dist[i] < dist[j] ? i : j;
			if(powers[current] == 0) {
				edgeEnable[edgeIndex[{i, j}]] = 0;
				if(next!=0)q.push(next);
			}
		}
	}
	vi currentDegree(N, 0);
	rep(i,N) {
		int degree = 0;
		for(auto&[to,cost]:mst.edge[i]) {
			if(edgeEnable[edgeIndex[{i, to}]])degree++;
		}
		currentDegree[i] = degree;
	}

	priority_queue<pair<int, int>> pq;
	rep(i,N) pq.push({powers[i], i});
	int challenge = 0;
	while(Mgr::timer){
		if(pq.empty()){
			rep(i,N) pq.push({powers[i], i});
			continue;
		}
		auto [_, tgt] = pq.top(); pq.pop();
		if(powers[tgt] == 0) continue;

		auto newReach = reach[tgt];
		rep(j,K)if(reach[tgt][j]) {
			int d = distHosoTohito[tgt][j];
			if(d > powers[tgt]-1){
				newReach.reset(j);
			}
		}
		auto mask = newReach;
		rep(i,N)if(i!=tgt and powers[i] != 0){
			mask |= reach[i];
		}
		if((int)mask.count() == K) {
			// その円を縮小できる
			reach[tgt] = newReach;
			powers[tgt]--;
			if(powers[tgt] != 0)pq.push({powers[tgt], tgt});
			else if(tgt!=0){
				if(currentDegree[tgt] >= 2)continue; //その円はコスト0になったが、木の葉ではないので辺を削除できない
				while(true){
					if(tgt == 0 or currentDegree[tgt] >= 2 or powers[tgt] > 0)break;
					int cnt = 0, j=0;
					for(auto&[to,cost]:mst.edge[tgt]) {
						if(!edgeEnable[edgeIndex[{tgt, to}]])continue;
						cnt++;
						j = to;
					}
					if(cnt!=1)break;
					edgeEnable[edgeIndex[{tgt, j}]] = 0;
					currentDegree[tgt]--;
					currentDegree[j]--;
					tgt = j;
				}
			}
		}else{
			challenge++;
			auto backupPower = powers;
			auto backupEdgeEnable = edgeEnable;
			auto backupCurrentDegree = currentDegree;
			auto backupReach = reach;

			// その円を縮小するには、はみ出たやつをフォローする必要がある
			ll otoku = (powers[tgt]*powers[tgt] - (powers[tgt]-1)*(powers[tgt]-1));
			if(powers[tgt] == 1){
				// TODO:その頂点を使わなくなったことにより削除できる辺のコスト
				int current = tgt;
				while(currentDegree[current] == 1 and current != 0){
					for(auto&[to,cost]:mst.edge[current]) {
						if(currentDegree[to] == 0)continue;
						otoku += cost;
						edgeEnable[edgeIndex[{current, to}]] = 0;
						currentDegree[current]--;
						currentDegree[to]--;
						current = to;
					}
				}
			}
			reach[tgt] = newReach;
			powers[tgt]--;

			
			ll requireTotal = 0;
			vi newHoso;
			rep(i,K)if(!mask.test(i)){
				// はみでた頂点iをカバーするのに最適な頂点を探す
				int bestCost=INF, bestHoso=0, bestDist = 0;
				rep(j,N)if(j!=tgt) {
					int d = distHosoTohito[j][i];
					if(d> 5000)continue;
					int require = 0;
					if(currentDegree[j] == 0) {
						require = INF;
						rep(k,N)if(powers[k] != 0) {
							chmin(require, warshall[j][k]);
						}
						require += d*d;
					}else{
						require = d*d - powers[j]*powers[j];
					}
					if(chmin(bestCost, require)) {
						bestHoso = j;
						bestDist = d;
					}
				}
				requireTotal += bestCost;
				//はみ出た頂点iのカバーには、bestHosoをbestDistまで拡大すればいい
				powers[bestHoso] = bestDist;
				reach[tgt] = newReach;
				newReach.reset();
				rep(j,K){
					int d = distHosoTohito[bestHoso][j];
					if(d <= powers[bestHoso]) newReach.set(j);
				}
				reach[bestHoso] = newReach;
				mask.reset();
				rep(j,N)if(powers[j] != 0){
					mask |= reach[j];
				}

				if(currentDegree[bestHoso] == 0) { // 新たにbestHosoを使うことになった
					int near = 0, nearDist = INF;
					rep(j,N)if(j!=tgt and currentDegree[j] != 0){
						if(chmin(nearDist, warshall[bestHoso][j])) {
							near = j;
						}
					}
					while(bestHoso != near and bestHoso != 0) {
						for(auto&[to,cost]:mst.edge[bestHoso]) {
							if(dist[to] + cost == dist[bestHoso]) {
								edgeEnable[edgeIndex[{bestHoso, to}]] = 1;
								currentDegree[bestHoso]++;
								currentDegree[to]++;
								newHoso.push_back(bestHoso);
								bestHoso = to;
								break;
							}
						}
					}
				}
			}
			double init = 2000000, fin = 1;
			double temp = init - (init-fin) * Mgr::timer.get() / Mgr::TLE;
			double prob = exp(min(0.0, fin * (otoku - requireTotal) / temp));

			if(Random(0.0, 1.0) > prob){
				powers = backupPower;
				edgeEnable = backupEdgeEnable;
				currentDegree = backupCurrentDegree;
				reach = backupReach;
			}else{
				pq.push({powers[tgt], tgt});
				for(auto&i:newHoso) {
					pq.push({powers[i], i});
				}
			}
		}
	}

	



	out(powers);
	out(edgeEnable);
	debug_f(challenge);
}

int main() {
	input();

	getInitial2();
}
