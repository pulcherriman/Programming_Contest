#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("inline")
#pragma GCC optimize("omit-frame-pointer,no-asynchronous-unwind-tables,fast-math")

#ifdef _DEBUG
// #define _GLIBCXX_DEBUG 1
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx2") /* 浮動小数点数のSIMD */
#else
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx2,avx512f,avx512vl,avx512dq") /* 浮動小数点数のSIMD */
#endif

/* 
 * Include Headers
 */
#if defined(EVAL) || defined(ONLINE_JUDGE) || defined(_DEBUG)
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
using ld=double;
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
using vp=vector<pii>;
using tl2=tuple<ll,ll>;
using tl3=tuple<ll,ll,ll>;
using vs=vector<string>;
using vd=vector<ld>;
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
constexpr ld EPS=(1e-14);
constexpr ld PI=3.14159265358979323846;

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
	constexpr ld operator()(ld a,ld b){return (b-a)*next()/4294967296.0+a;}
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
	uint64_t get() const{return (getClocks()-start)/ClocksPerMsec;}
	operator bool()const{return getClocks()<limit;}
};
void wait(const int&msec){Timer tm(msec); while(tm);}

struct Mgr {
	static const int TLE = 5000;
	static inline Timer timer = Timer(TLE-100);
	Mgr() {
		ios_base::sync_with_stdio(0); cin.tie(0);
		cout<<fixed<<setprecision(11);
		cerr<<fixed<<setprecision(3);

	}
	~Mgr(){
		cout<<flush;
		// debug_f(timer.get(), "ms")<<flush;
	}
} _manager;



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

template<class T=ll>struct Dijkstra{
    Graph<T> g;
    Dijkstra(Graph<T> g):g(g){}
    vector<T>dist(ll s){
		// rep(i,g.size)shuffle(all(g.edge[i]), Random);

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
    pair<T,vp> calc(){
        T ans=0;
        UnionFind uf(g.size);
        vector<tuple<T,ll,ll>> edge;
		vp uses;
        rep(from,g.size)for(auto&[to,cost]:g.edge[from])edge.emplace_back(cost,from,to);
        sort(all(edge));
        for(auto&[cost,from,to]:edge)if(uf.unite(from,to)){
			ans+=cost;
			uses.emplace_back(from,to);
		}
        return {ans, uses};
    }
};


int N,W,K,C;

struct Simulator {
	int health = 0;

	vvi answer, remain, predict, predict_init, digging;
	void init() {
		remain.resize(N);
		predict.resize(N);
		predict_init.resize(N);
		digging.resize(N);
		rep(i,N){
			remain[i].resize(N, 5000);
			predict[i].resize(N, 5000);
			predict_init[i].resize(N, 5000);
			digging[i].resize(N, 0);
		}

		#ifdef _DEBUG
		answer.resize(N);
		rep(i,N){
			answer[i].resize(N, 5000);
			cin>>answer[i];
		}
		#endif
	}

	int post(int y, int x, int p){
		out(y,x,p)<<flush;
		#ifdef _DEBUG
		if (answer[y][x] <= 0) return -1;
		answer[y][x] -= p;
		return answer[y][x] <= 0 ? 1 : 0;
		#else
		def(int, t);
		return t;
		#endif
	}

	bool dig(int y, int x, int p){
		chmin(p, remain[y][x]);
		if(p <= 0){
			return true;
		}

		int digged = 5000 - remain[y][x];

		health += p + C;
		remain[y][x] -= p;
		digging[y][x] += p;
		
		int result = post(y,x,p);
		predict_init[y][x] = clamp(digged + p, 10, 5000);
		if(result == -1 or result == 2){
			exit(0);
		}
		if(result == 1) {
			if(predict[y][x] == 5000){
				predict[y][x] = digged + p/2;
				predict_init[y][x] = clamp(digged + p/2, 10, 5000);
			}
			remain[y][x] = 0;
		}
		return result;
	}

	bool dig_strict(int y, int x){
		return dig(y, x, remain[y][x]);
	}

};

vp waters, houses;
Simulator simulator;

map<int, tuple<int,int,int,ld>> PARAMETERS = {
	{1, {15, 15, 700, 1.2}},
	{2, {15, 15, 900, 1.1}},
	{4, {20, 16, 900, 1.2}},
	{8, {30, 16, 900, 1.3}},
	{16, {35, 16, 900, 1.4}},
	{32, {50, 16, 900, 1.6}},
	{64, {75, 16, 900, 1.7}},
	{128, {90, 19, 900, 2.0}}
};
const int PREDICT_CLAMP_MAX = 1000;

int INIT_POWER, CELL_COUNT, THRESHOLD; ld POWER_MULTIPLIER;

int SAMPLE_SIZE; vi SAMPLE_INDICES;
void initialize() {
	cin>>N>>W>>K>>C;
	simulator.init();
	waters.resize(W);
	cin>>waters;
	houses.resize(K);
	cin>>houses;
	tie(INIT_POWER, CELL_COUNT, THRESHOLD, POWER_MULTIPLIER) = PARAMETERS[C];

	SAMPLE_SIZE = ceil((ld)N / CELL_COUNT);

	rep(i,SAMPLE_SIZE){
		int index = round(N / (ld)(SAMPLE_SIZE-1) * i);
		SAMPLE_INDICES.push_back(clamp(index, 0, N-1));
	}
}


int forceDigging = 0;
int dig(int y, int x, int p, bool must=false){
	// int ave_power = 2500;
	// chmin(p,ave_power);
	if(simulator.dig(y,x,p)) return 1;
	if(!must)return 0;
	forceDigging++;
	return dig(y,x,INIT_POWER,true);
}

typedef int Value;
typedef complex<Value> Point;
#define X real()
#define Y imag()
Value dot(Point a, Point b)   { return real(conj(a)*b); }
Value cross(Point a, Point b) { return imag(conj(a)*b); }
Value dist2(Point a, Point b) { return dot(a-b, a-b); }

int ccw(Point a, Point b, Point c) {
  b -= a; c -= a;
  if (cross(b,c) > 0)      return +1; // counter clockwise
  if (cross(b,c) < 0)      return -1; // clockwise
  if (dot(b,c) < 0)        return +2; // c--a--b on line
  if (dot(b,b) < dot(c,c)) return -2; // a--b--c on lne
  return 0;
}
namespace std { 
  bool operator < (Point a, Point b) { // bottom-left
    return a.Y != b.Y ? a.Y < b.Y : a.X < b.X; 
  }
}
vector<Point> convexHull(vector<Point> p) {
  int n = p.size(), k = 0;
  vector<Point> h(2*n);
  sort(all(p));
  for (int i = 0; i < n; h[k++] = p[i++]) 
    while (k >= 2 && ccw(h[k-2], h[k-1], p[i]) <= 0) --k;
  for (int i = n-2, t = k+1; i >= 0; h[k++] = p[i--]) 
    while (k >= t && ccw(h[k-2], h[k-1], p[i]) <= 0) --k;
  return vector<Point>(h.begin(), h.begin() + k - (k > 1));
}

bool isInConvexHull(int y, int x) {
	vector<Point> positions;
	for(auto p : waters){
		positions.push_back(Point(p.first, p.second));
	}
	for(auto p : houses){
		positions.push_back(Point(p.first, p.second));
	}

	int siz = sz(positions);
	rep(i,siz){
		rep(j,i){
			Point center((positions[i].X+positions[j].X)/2, (positions[i].Y+positions[j].Y)/2);
			positions.push_back(center);
		}
	}

	auto polygon = convexHull(positions);
	rep(i,sz(polygon)){
		auto&a = polygon[i];
		auto&b = polygon[(i+1)%sz(polygon)];
		auto c = ccw(a,b,Point(y,x));
		if(c==-1){
			return false;
		}
	}
	return true;
}


pair<int, HashSet<int>> getMSF(vvi predict) {
	rep(i,N)rep(j,N){
		if(simulator.remain[i][j] == 0){
			predict[i][j] = 0; // もう掘れてる
		}
	}

	Graph<int> g(N*N, INF);
	rep(i,N)rep(j,N){
		if(j>0){
			auto cost = (predict[i][j]+predict[i][j-1])/2;
			g.add(i*N+j, i*N+j-1, cost==0 ? 1 : (cost + C));
		}
		if(i>0){
			auto cost = (predict[i][j]+predict[i-1][j])/2;
			g.add(i*N+j, i*N+j-N, cost==0 ? 1 : (cost + C));
		}
	}

	HashMap<int, HashMap<int,int>>dists;

	Dijkstra<int> dijkstra(g);
	rep(i,W){
		auto [y,x] = waters[i];
		auto dist = dijkstra.dist(y*N+x);
		rep(j,N*N){
			dists[y*N+x][j] = dists[j][y*N+x] = dist[j];
		}
	}
	rep(i,K){
		auto [y,x] = houses[i];
		auto dist = dijkstra.dist(y*N+x);
		rep(j,N*N){
			dists[y*N+x][j] = dists[j][y*N+x] = dist[j];
		}
	}

	/*
		mst_with_water_houses[W][2^K] = 各水源に家の部分集合を割り当てた際のMST
		4*(2^10)
	*/
	vector<vector<HashSet<int>>> mst_with_water_houses(W, vector<HashSet<int>>(1<<K));
	rep(water,W){
		rep(house_targets, 1<<K){
			vp positions(1, waters[water]);
			rep(i,K){
				if(house_targets & (1<<i)){
					positions.emplace_back(houses[i]);
				}
			}

			Graph<int> mstGraph(sz(positions), INF);
			rep(i,sz(positions))rep(j,i){
				if(i==j)continue;
				auto [y1,x1] = positions[i];
				auto [y2,x2] = positions[j];
				mstGraph.add(i, j, dists[y1*N+x1][y2*N+x2]);
			}

			Kruskal<int> kruskal(mstGraph);
			auto [_, edges] = kruskal.calc();

			for(auto [u,v] : edges){
				auto [y1,x1] = positions[u];
				auto [y2,x2] = positions[v];
				int cur = y2*N+x2;
				while(cur!=y1*N+x1){
					for(auto&[to, cost] : g.edge[cur]){
						if(dists[y1*N+x1][to] + cost == dists[y1*N+x1][cur]){
							mst_with_water_houses[water][house_targets].insert(cur);
							mst_with_water_houses[water][house_targets].insert(to);
							cur = to;
							break;
						}
					}
				}
			}
		}
	}


	vvi mst_cost_with_water_houses(W, vi(1<<K, INF));
	rep(water,W){
		rep(house_targets, 1<<K){
			mst_cost_with_water_houses[water][house_targets] = 0;
			for(auto&e:mst_with_water_houses[water][house_targets]){
				mst_cost_with_water_houses[water][house_targets] += predict[e/N][e%N];
			}
		}
	}

	int mstBestCost=INF;
	HashSet<int> mst;
	rep(house_targets,pow(W,K)){
		int mstCost = 0;
		rep(water, W){
			int tmp = house_targets;
			int house_set = 0;
			rep(k,K){
				if(tmp%W == water){
					house_set |= 1<<k;
				}
				tmp/=W;
			}
			mstCost += mst_cost_with_water_houses[water][house_set];
		}

		if(chmin(mstBestCost, mstCost)){
			mst.clear();
			rep(water, W){
				int tmp = house_targets;
				int house_set = 0;
				rep(k,K){
					if(tmp%W == water){
						house_set |= 1<<k;
					}
					tmp/=W;
				}
				for(auto&e : mst_with_water_houses[water][house_set]){
					mst.insert(e);
				}
			}
		}
	}
	return {mstBestCost, mst};
}



vvi getConvexMap(){
	vvi isConvex(N, vi(N, 5000));

	if(W+K==2){// 凸包の面積がX以下なら...?
		auto [y1,x1] = waters[0];
		auto [y2,x2] = houses[0];
		int y = (y1+y2)/2;
		int x = (x1+x2)/2;
		// int dist = hypot(y1-y2, x1-x2)/2-log2(C)-3;
		int dist = hypot(y1-y2, x1-x2)/2-CELL_COUNT*1.5;
		rep(i,N)rep(j,N){
			if(hypot(i-y, j-x) <= dist){
				isConvex[i][j] = 0;
			}else{
				isConvex[i][j] = hypot(i-y, j-x) - dist;
			}
		}
		return isConvex;
	}

	vvi templatePredictor(N,  vi(N, 5000));
	auto [_, mst] = getMSF(templatePredictor);
	
	queue<pii> q;
	// rep(i,N)rep(j,N){
		// if(isInConvexHull(i,j)){
		// 	isConvex[i][j] = 0;
		// 	q.push(pii(i,j));
		// }
	// }
	for(auto&e:mst){
		isConvex[e/N][e%N] = 0;
		q.push(pii(e/N, e%N));
	}
	auto d4 = vector<pii>{{1,0},{-1,0},{0,1},{0,-1}};
	while(!q.empty()){
		auto [y,x] = q.front(); q.pop();
		for(auto [dy,dx]:d4){
			int ny = y+dy;
			int nx = x+dx;
			if(ny<0||nx<0||ny>=N||nx>=N)continue;
			if(isConvex[ny][nx] == 5000){
				isConvex[ny][nx] = isConvex[y][x] + 1;
				q.push(pii(ny,nx));
			}
		}
	}
	return isConvex;
}

void printCurrentPredict(vvi predict) {
	out(N,W,K,C);
	rep(i,N)rep(j,N)predict[i][j] = clamp(predict[i][j], 10, 5000);
	out(predict);
	for(auto[y,x]:waters)out(y,x);
	for(auto[y,x]:houses)out(y,x);
}

ld weightByDistance(ld d) {
	ld a = -1.2;
	if(d<1.0)return 1-(a+3)*d*d+(a+2)*d*d*d;
	if(d<=2.0)return a*d*d*d-5*a*d*d+8*a*d-4*a;
	return 0;
}

ld encode(ld parlin){
	ld s = 1.0 / (1.0 + exp(-3.0 * (parlin - 0.25)));
	return pow(s, 4);
}

vd decoded_values;
ld decode(int p){
	if(decoded_values.empty()){
		ld l = 0.00001213112, u = 0.74035929506; // 3.0
		// 0.00002580126, u = 0.75534674900; // 2.8
		l = 0.00000027874, u = 0.66976643244; // 4.0
		// l = 0.00052795953, u = 0.81839259066; // 2.0
		decoded_values.resize(5001);
		rep(i,10,5001){
			const ld x = (i-10) * (u - l) / (5000-10) + l;
			const ld s = pow(x, 1/ 4.0);
			decoded_values[i] = log(1.0/s - 1.0) / -3.0 + 0.25;
		}
	}
	return decoded_values[p];
}


vp compressRange; vd relativePositions; vp decompress_range;
void bicubicBase(){
	if(compressRange.empty()){
		decompress_range.resize(SAMPLE_SIZE, {N,-1});
		int il=-1, ir=3;
		rep(i,N){
			if(i==SAMPLE_INDICES[ir-2] and ir<SAMPLE_SIZE)ir++;
			if(i==SAMPLE_INDICES[il+2])il++;
			compressRange.emplace_back(max(il, 0), min(ir, SAMPLE_SIZE));
			rep(j,max(il, 0),min(ir, SAMPLE_SIZE)){
				chmin(decompress_range[j].first, (int)i);
				chmax(decompress_range[j].second, (int)i);
			}
		}
		rep(i,SAMPLE_SIZE){
			relativePositions.push_back(SAMPLE_INDICES[i] / (ld)N * (SAMPLE_SIZE-1));
		}
	}
}

vvi BicubicInterpolation(vvd&compressed, int predict_clamp_max) {
	bicubicBase();

	ld minValue = INF, maxValue = -INF;
	vector<vd> predict_raw(N, vd(N, 0));
	vvd decodedValues(SAMPLE_SIZE, vd(SAMPLE_SIZE));

	auto convex = getConvexMap();
	rep(i,SAMPLE_SIZE){
		rep(j,SAMPLE_SIZE){
			// if(convex[SAMPLE_INDICES[i]][SAMPLE_INDICES[j]] > 18) {
				// decodedValues[i][j] = decode(predict_clamp_max);
			// }else{
				decodedValues[i][j] = decode(compressed[i][j]);
			// }
		}
	}

	rep(i,N){
		rep(j,N){
			const auto [il, ir] = compressRange[i];
			const ld y = i / (ld)N * (SAMPLE_SIZE-1);
			const auto [jl, jr] = compressRange[j];
			const ld x = j / (ld)N * (SAMPLE_SIZE-1);

			ld norm = 0;

			rep(ci, il, ir)rep(cj, jl, jr){
				const auto weight = weightByDistance(abs(y-relativePositions[ci])) * weightByDistance(abs(x-relativePositions[cj]));
				predict_raw[i][j] += decodedValues[ci][cj] * weight;
				norm += weight;
			}
			predict_raw[i][j] = encode(predict_raw[i][j] / norm);
			chmin(minValue, predict_raw[i][j]);
			chmax(maxValue, predict_raw[i][j]);
		}
	}
	
	vvi predict(N, vi(N, 0));
	rep(i,N)rep(j,N){
		predict[i][j] = round((predict_raw[i][j] - minValue)  * (predict_clamp_max-10) / (maxValue - minValue) + 10);
	}
	return predict;
}


template<class S,class T>struct std::hash<pair<S,T>>{size_t operator()(pair<S,T> p)const{return p.first<<8|p.second;}};


bool BicubicInterpolation_Difference(vvd&compressed, int predict_clamp_max, vvi&predict) {
	bicubicBase();

	bool isModified = false;
	ld minValue = INF, maxValue = -INF;
	rep(i,N)rep(j,N){
		const auto v = encode(decode(predict[i][j]));
		chmin(minValue, v); chmax(maxValue, v);
	}

	HashSet<pair<int,int>> targets;
	rep(i,N)rep(j,N)if(simulator.remain[i][j] == 0)targets.insert({i,j});

	auto convex = getConvexMap();

	rep(i,SAMPLE_SIZE)rep(j,SAMPLE_SIZE){
			if(convex[SAMPLE_INDICES[i]][SAMPLE_INDICES[j]] > 18) {
				continue;
			}
		int beforeCompressedValue = compressed[i][j];
		int targetValue = clamp(beforeCompressedValue * (Random(0,2)+0.5) , 10.0, (ld)predict_clamp_max);
		if(beforeCompressedValue == targetValue) continue;
		compressed[i][j] = targetValue;

		// i,jを変更する → i,jの変更が影響する範囲について、値を再計算する
		auto [effected_il, effected_ir] = decompress_range[i];
		auto [effected_jl, effected_jr] = decompress_range[j];

		ld beforeError = 0, afterError = 0;
		rep(ii,effected_il, effected_ir+1){
			rep(jj,effected_jl, effected_jr+1){
				if(targets.find({ii, jj}) == targets.end()) continue;

				const auto [il, ir] = compressRange[ii];
				const ld y = ii / (ld)N * (SAMPLE_SIZE-1);
				const auto [jl, jr] = compressRange[jj];
				const ld x = jj / (ld)N * (SAMPLE_SIZE-1);

				ld norm = 0, predictValue = 0;
				rep(ci, il, ir)rep(cj, jl, jr){
					const auto weight = weightByDistance(abs(y-relativePositions[ci])) * weightByDistance(abs(x-relativePositions[cj]));
					predictValue += decode(compressed[ci][cj]) * weight;
					norm += weight;
				}
				predictValue = encode(predictValue / norm);
				// chmin(minValue, predictValue);
				// chmax(maxValue, predictValue);
				predictValue = clamp(predictValue, minValue, maxValue);
				predictValue = round((predictValue - minValue)  * (predict_clamp_max-10) / (maxValue - minValue) + 10);

				auto bdiff = ((decode(simulator.predict_init[ii][jj]) - decode(predict[ii][jj])));
				beforeError += bdiff * bdiff;
				auto diff = ((decode(simulator.predict_init[ii][jj]) - decode(predictValue)));
				afterError += diff * diff;
			}
		}
		
		if(afterError < beforeError){
			rep(ii,effected_il, effected_ir+1){
				rep(jj,effected_jl, effected_jr+1){
					const auto [il, ir] = compressRange[ii];
					const ld y = ii / (ld)N * (SAMPLE_SIZE-1);
					const auto [jl, jr] = compressRange[jj];
					const ld x = jj / (ld)N * (SAMPLE_SIZE-1);

					ld norm = 0, predictValue = 0;
					rep(ci, il, ir)rep(cj, jl, jr){
						const auto weight = weightByDistance(abs(y-relativePositions[ci])) * weightByDistance(abs(x-relativePositions[cj]));
						predictValue += decode(compressed[ci][cj]) * weight;
						norm += weight;
					}
					predictValue = clamp(encode(predictValue / norm), minValue, maxValue);
					predict[ii][jj] = round((predictValue - minValue)  * (predict_clamp_max-10) / (maxValue - minValue) + 10);
				}
			}
			isModified = true;
		}else{
			compressed[i][j] = beforeCompressedValue;
		}
	}
	return isModified;
}


vvi getPredict2(int predict_clamp_max = 2000) {
	auto convex = getConvexMap();

	vvd compressed(SAMPLE_SIZE, vd(SAMPLE_SIZE, 0));
	rep(i,SAMPLE_SIZE)rep(j,SAMPLE_SIZE){
		const int y = SAMPLE_INDICES[i], x = SAMPLE_INDICES[j];
		if(convex[y][x] > CELL_COUNT*1.5) {
			compressed[i][j] = predict_clamp_max;
			continue;
		}

		int power = INIT_POWER;
		while(compressed[i][j] < THRESHOLD){
			if(dig(y,x,min(power, THRESHOLD - (int)compressed[i][j]))) {
				compressed[i][j] += power;
				break;
			}
			compressed[i][j] += power;
			power *= POWER_MULTIPLIER;
		}
		if(compressed[i][j] >= THRESHOLD){
			compressed[i][j] = predict_clamp_max;
		}

		// int power = INIT_POWER;
		// while(compressed[i][j] < THRESHOLD){
		// 	if(dig(y,x,min(power, THRESHOLD - (int)compressed[i][j]))) {
		// 		break;
		// 	}
		// 	power *= POWER_MULTIPLIER;
		// }
		// if(simulator.remain[y][x] == 0){
		// 	compressed[i][j] = simulator.predict_init[y][x];
		// }else{
		// 	compressed[i][j] = predict_clamp_max;
		// }
	}

	return BicubicInterpolation(compressed, predict_clamp_max);
}

// predictと、既に掘りきった座標の推定値の二乗誤差が小さくなるように、compressを調整する
vvi optimizePredict(ld predict_clamp_max = 2000) {
	auto convex = getConvexMap();
	vvd compressed(SAMPLE_SIZE, vd(SAMPLE_SIZE, 0));
	rep(i,SAMPLE_SIZE)rep(j,SAMPLE_SIZE){
		const int y = SAMPLE_INDICES[i], x = SAMPLE_INDICES[j];
		if(simulator.remain[y][x] == 0){
			compressed[i][j] = simulator.predict_init[y][x];
		}else{
			compressed[i][j] = predict_clamp_max;
		}
		compressed[i][j] = clamp(compressed[i][j], 10.0, predict_clamp_max);
	}

	auto minPredict = BicubicInterpolation(compressed, predict_clamp_max);
	rep(15){
		minPredict = BicubicInterpolation(compressed, predict_clamp_max);
		if(!BicubicInterpolation_Difference(compressed, predict_clamp_max, minPredict)) break;
	}
	return minPredict;
}

int main() {
	initialize();

	// // 全ての家を壊し、最大の頑丈さを取得
	int maxHP = 0;
	{
		for(auto&[y,x] : houses){
			dig(y, x, INIT_POWER, true);
			chmax(maxHP, simulator.digging[y][x]);
		}
	}

	// // 全体をmaxHPまで壊す
	// maxHP = 200;
	// rep(y,N)rep(x,N)if(y%10 == 5 && x%10 == 5){
	// // for(auto&x:SAMPLE_INDICES)for(auto&y:SAMPLE_INDICES){
	// 	int power = INIT_POWER;
	// 	int currentHP = maxHP;
	// 	while(true){
	// 		if(dig(y,x,min(power, currentHP))) break;
	// 		if((currentHP-=power)<=0)break;
	// 		power *= POWER_MULTIPLIER;
	// 	}
	// }

	auto predict = getPredict2();
	// predict = optimizePredict();

	
	auto [mstBestCost, mst] = getMSF(predict);
	mstBestCost += simulator.health;

	// for(auto&e:mst){
	// 	int y = e/N;
	// 	int x = e%N;
	// 	dig(y,x,simulator.answer[y][x],true);
	// }
	// printCurrentPredict(predict);

	// exit(0);

	while(!mst.empty()){
		vp scores;
		for(auto&e:mst){
			int y = e/N;
			int x = e%N;
			if(simulator.remain[y][x] == 0)continue;
			scores.emplace_back(predict[y][x], e);
		}
		if(scores.empty()) break;
		sort(all(scores));
		auto [ _, i] = scores.front();
		

		mst.erase(i);
		int y = i/N;
		int x = i%N;

		int pre_forceDigCount = forceDigging;
		dig(y, x, predict[y][x], true);
		if(pre_forceDigCount==forceDigging){
			continue;
		}
		int over = simulator.predict[y][x] - predict[y][x];

		int R = 13;
		rep(dy,-R,R+1)rep(dx,-R,R+1){
			float r = hypot(dy,dx);
			if(r > R) continue;
			int ny = y+dy;
			int nx = x+dx;
			if(ny<0 || ny>=N || nx<0 || nx>=N)continue;

			if(simulator.remain[ny][nx] == 0){
				continue;
			}

			int diff = over;
			if(predict[ny][nx]==5000){
				predict[ny][nx] = simulator.predict[y][x] * (1-r/(R+1)) * 2;
				predict[ny][nx] = simulator.predict[y][x];
				predict[ny][nx] = clamp(predict[ny][nx], 10, 5000);
				continue;
			}
			predict[ny][nx] += diff * (1-r/(R+1));
		}
	}

	out("#",simulator.health);
	out("#",forceDigging);
	out("#", mstBestCost);

	// predict = optimizePredict(5000);
	// printCurrentPredict(predict);


}
