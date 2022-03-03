/*
 * Unsecured Optimization
 */
#pragma GCC optimize "O3" /* 最適化 */
#pragma GCC target "avx" /* SIMD(ベクトル化) */
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native") /* 浮動小数点数のSIMD */
// #pragma GCC optimize "fast-math"
// #pragma GCC optimize "unroll-loops" /* ループの展開 */
#ifdef _DEBUG
// #define _GLIBCXX_DEBUG 1
#endif

/* 
 * Include Headers
 */
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
using tl3=tuple<int,int,int>;
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
constexpr int INF=1<<30;

/*
 * Utilities
 */
template<class T>constexpr bool chmax(T&a,T b){return a<b?a=b,1:0;}
template<class T>constexpr bool chmin(T&a,T b){return a>b?a=b,1:0;}
template<class S>S sum(vector<S>&a){return accumulate(all(a),S());}
template<class S>S max(vector<S>&a){return *max_element(all(a));}
template<class S>S min(vector<S>&a){return *min_element(all(a));}


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
	Timer(uint64_t _limit = 2970): start(getClocks()),limit(start+_limit*ClocksPerMsec) {}
	uint64_t get() const{return (getClocks()-start)/ClocksPerMsec;}
	operator bool()const{return getClocks()<limit;}
};
void wait(const int&msec){Timer tm(msec); while(tm);}


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


struct StaticDataStore {
private:
	StaticDataStore() = default;

public:
	static inline int n, sy, sx;
	static inline vector<vector<int>> stage;
	static inline Timer timer;

	static void Input() {
		cin>>n>>sy>>sx;
		sy++; sx++;
		stage.resize(n+2, vi(n+2,0));

		char c;
		rep(i,n)rep(j,n){
			cin>>c;
			if(c=='#')continue;
			stage[i+1][j+1] = (c - '0');
		}
	}
};

struct _Construct {
	_Construct(){
		StaticDataStore::Input();
	}
} _construct;


struct SolverInterface {
	virtual int Solve() = 0;
	virtual void Print() = 0;

protected:

};

#define endl '\n'


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
	Graph(int n=1,T inf=INF):size(n),INF_VAL(inf){edge.resize(size);}
	constexpr void add(ll from, ll to, T cost, bool directed=false){
		edge[from].emplace_back(to,cost);
		if(!directed) edge[to].emplace_back(from,cost);
	}
	constexpr friend ostream &operator<<(ostream &os, const Graph<T> &g) {
		rep(i,g.size)for(auto[from,val]:g.edge[i])puta(make_tuple(i,"=>",from,", cost :",val),os);
		return os;
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
	pair<T,vi> dist(ll s,ll t){
		vi dist=this->dist(s);
		vi path(1,t);
		while(path.back()!=s)for(auto[to,cost]:g.edge[path.back()])if(dist[to]==dist[path.back()]-cost){path.emplace_back(to);break;}
		reverse(all(path));
		return {dist[t], path};
	}
};

struct UnionFind{
	vl par,dist;
	UnionFind(int x){par.assign(x,-1); dist.assign(x,0);}
	ll find(ll x){return par[x]<0?x:find(par[x]);}
	ll depth(ll x){return par[x]<0?0:depth(par[x])+dist[x];}
	bool same(ll x,ll y){return find(x)==find(y);}
	ll size(ll x){return -par[find(x)];}
	ll diff(ll x,ll y){return same(x,y)?depth(x)-depth(y):INF;}
	bool unite(ll x,ll y,ll k=0){
		k+=depth(y); k-=depth(x); k=-k;
		x=find(x); y=find(y);
		if(x==y)return false;
		if(size(x)<size(y)){swap(x,y);k=-k;}
		par[x]+=par[y]; par[y]=x; dist[y]=k;
		return true;
	}
};

template<class T>struct Kruskal{
	Graph<T> g;
	Kruskal(Graph<T> g):g(g){}
	pair<T, vector<pair<int,int>>> calc(){
		T ans=0;
		UnionFind uf(g.size);
		vector<tuple<T,ll,ll>> edge;
		vector<pair<int,int>> used;
		rep(from,g.size)for(auto&[to,cost]:g.edge[from])edge.emplace_back(cost,from,to);
		sort(all(edge));
		for(auto&[cost,from,to]:edge)if(uf.unite(from,to)){
			used.emplace_back(from,to);
			ans+=cost;
		}
		return {ans, used};
	}
};

struct GreedySolver : public SolverInterface {
	int score = 0;
	vector<vector<pair<int,int>>> graph;
	vector<pair<int, int>> point;
	vector<vector<int>> pointMap;
	vector<vector<int>> distance;
	int startPoint;
	vector<int> path;
	Graph<int> g;

	GreedySolver() {
		const auto& stage = StaticDataStore::stage;
		const int n = StaticDataStore::n;

		vvi isLightenH(n+2, vi(n+2,0));
		vvi isLightenV(n+2, vi(n+2,0));

		graph.resize(n+2);
		pointMap.resize(n+2, vi(n+2,-1));

		const int sy = StaticDataStore::sy;
		const int sx = StaticDataStore::sx;
		startPoint = pointMap[sy][sx]=0;
		point.emplace_back(sy,sx);
		{
			int i=sy, j=sx;
			for(int dy=i ; stage[dy][j] ; dy--){
				if(stage[dy][j]==0)break;
				isLightenV[dy][j]=1;
			}
			for(int dy=i ; stage[dy][j] ; dy++){
				if(stage[dy][j]==0)break;
				isLightenV[dy][j]=1;
			}
			for(int dx=j ; stage[i][dx] ; dx--){
				if(stage[i][dx]==0)break;
				isLightenH[i][dx]=1;
			}
			for(int dx=j ; stage[i][dx] ; dx++){
				if(stage[i][dx]==0)break;
				isLightenH[i][dx]=1;
			}
		}

		vector<pair<int,int>> koho;
		rep(i,1,n+1)rep(j,1,n+1)if(stage[i][j]!=0){
			bool v=false, h=false;
			if(stage[i-1][j])v=true;
			if(stage[i+1][j])v=true;
			if(stage[i][j-1])h=true;
			if(stage[i][j+1])h=true;
			if(v and h){
				koho.emplace_back(i,j);
			}
		}
		sort(all(koho), [&](const auto& a, const auto& b){
			int d=abs(a.first-StaticDataStore::sy)+abs(a.second-StaticDataStore::sx);
			int d2=abs(b.first-StaticDataStore::sy)+abs(b.second-StaticDataStore::sx);
			return d>d2;
		});
		for(auto&[i,j]:koho){
			if(isLightenH[i][j] and isLightenV[i][j])continue;
			pointMap[i][j]=point.size();
			point.emplace_back(i,j);
			for(int dy=i ; stage[dy][j] ; dy--){
				if(stage[dy][j]==0)break;
				isLightenV[dy][j]=1;
			}
			for(int dy=i ; stage[dy][j] ; dy++){
				if(stage[dy][j]==0)break;
				isLightenV[dy][j]=1;
			}
			for(int dx=j ; stage[i][dx] ; dx--){
				if(stage[i][dx]==0)break;
				isLightenH[i][dx]=1;
			}
			for(int dx=j ; stage[i][dx] ; dx++){
				if(stage[i][dx]==0)break;
				isLightenH[i][dx]=1;
			}
			cerr<<pointMap[i][j]<<" : ("<<i<<","<<j<<")"<<endl;
		}

		g = Graph<int>((n+2)*(n+2));
		rep(i,1,n+1)rep(j,1,n+1)if(stage[i][j]){
			// if(stage[i-1][j])g.add(i*(n+2)+j,(i-1)*(n+2)+j,stage[i-1][j]);
			if(stage[i+1][j])g.add(i*(n+2)+j,(i+1)*(n+2)+j,stage[i+1][j]);
			// if(stage[i][j-1])g.add(i*(n+2)+j,i*(n+2)+j-1,stage[i][j-1]);
			if(stage[i][j+1])g.add(i*(n+2)+j,i*(n+2)+j+1,stage[i][j+1]);
		}
		distance = vvi(point.size(), vi(point.size(),INF));

		Dijkstra<int> dijkstra(g);
		rep(i, point.size()){
			int from = point[i].first*(n+2)+point[i].second;
			auto res = dijkstra.dist(from);
			rep(j, point.size()){
				int to = point[j].first*(n+2)+point[j].second;
				distance[i][j] = res[to];
			}
		}
	}

	void createInit(){
		Graph<int> pointGraph(point.size());
		rep(i,point.size())rep(j,point.size())if(i!=j){
			pointGraph.add(i,j,distance[i][j],1);
		}
		Kruskal<int> kruskal(pointGraph);
		auto[_,usedEdge] = kruskal.calc();
		
		Graph<int> mst(point.size());
		for(auto&[from, to] : usedEdge){
			mst.add(from, to, (distance[from][to]+distance[to][from])/2);
		}
		auto preorder = mst.dfs(startPoint).preorder;
		path = preorder;

		rep(i,preorder.size()){
			path[preorder[i]] = i;
		}
		path.emplace_back(startPoint);

		return;
	}

	int calculate(vi path){
		int r=0;
		rep(i,path.size()-1){
			r+=distance[path[i]][path[i+1]];
		}
		return (int)round(10000 + 10000000.0 * StaticDataStore::n / r);
	}

	bool IsMovable(int from, int to) {
		auto[fy,fx]=point[from];
		auto[ty,tx]=point[to];
		return fy == ty or fx == tx;
	}

	float Exchange_Probability(float exchange_cost){
		return exp(-exchange_cost/Temperature());
	}
 
	float Temperature(){
	return 100-pow(100,StaticDataStore::timer.get()/3000.0);
	}
	
	int Solve() {
		createInit();

		int bestScore = calculate(path);
		cerr<<"INIT: "<<bestScore<<endl;

		auto currentPath = path;
		// cerr<<bestScore<<endl<<flush;
		int challenge = 0;
		int type=0;
		while(StaticDataStore::timer){
			/* change */
			challenge++;
			int a = challenge % path.size();
			int b = challenge / path.size() % path.size();
			if(a==0 and b==0){
				if(type==1)break;
				type=1;
			}
			if(currentPath[a]==0 or currentPath[b]==0)continue;
			if(a==b)continue;
			if(type==0){
				swap(currentPath[a], currentPath[b]);
			}else{
				if(a>=b)continue;
				auto c2=currentPath;
				currentPath.clear();
				rep(i,c2.size()){
					if(i==a)continue;
					currentPath.emplace_back(c2[i]);
					if(i==b)currentPath.emplace_back(c2[a]);
				}
			}

			int currentScore = calculate(currentPath);
			if(chmax(bestScore, currentScore)){
				path = currentPath;
			}else{
				currentPath = path;
				// cerr<<StaticDataStore::timer.get()<<","<<challenge<<","<<bestScore<<endl;
			}
		}

		return bestScore;
	}

	string Move(int from, int to) {
		const int n=StaticDataStore::n;
		auto[fy,fx]=point[from];
		auto[ty,tx]=point[to];
		// cout<<"MOVE "<<from<<" "<<to<<endl<<flush;
		from = fy*(n+2)+fx;
		to = ty*(n+2)+tx;
		
		Dijkstra<int> dijkstra(g);
		auto[_, route] = dijkstra.dist(from, to);


		string ret = "";
		rep(i,route.size()-1){
			if(route[i]+1 == route[i+1]){
				ret += "R";
			}
			if(route[i]-1 == route[i+1]){
				ret += "L";
			}
			if(route[i]+n+2 == route[i+1]){
				ret += "D";
			}
			if(route[i]-n-2 == route[i+1]){
				ret += "U";
			}
		}

		return ret;
	}

	void Print() {
		/* 結果を出力 */
		rep(i,path.size()-1){
			cerr<<path[i]<<"->"<<path[i+1]<<endl;
			cout<<Move(path[i],path[i+1]);
		}
		cout<<endl<<std::flush;
	}
};

int main(){
	Timer timer;

	SolverInterface* solver = new GreedySolver();

	cerr<<solver->Solve()<<endl;

	solver->Print();

	cerr<<timer.get()<<" ms"<<endl;
}
