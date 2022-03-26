#pragma GCC optimize "O3" /* 最適化 */
#pragma GCC target "avx" /* SIMD(ベクトル化) */
// #pragma GCC optimize "fast-math"
// #pragma GCC optimize "unroll-loops" /* ループの展開 */
#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;

using vb=vector<bool>;
using vvb=vector<vb>;
using vi=vector<int>;
using vvi=vector<vi>;
using pii=pair<int,int>;
using vp=vector<pii>;
using tl2=tuple<int,int>;
using tl3=tuple<int,int,int>;
using vs=vector<string>;
template<class K> using IndexedSet=__gnu_pbds::tree<K,__gnu_pbds::null_type,less<K>,__gnu_pbds::rb_tree_tag,__gnu_pbds::tree_order_statistics_node_update>;
template<class K> using HashSet=__gnu_pbds::gp_hash_table<K,__gnu_pbds::null_type>;
template<class K,class V> using IndexedMap=__gnu_pbds::tree<K,V,less<K>,__gnu_pbds::rb_tree_tag,__gnu_pbds::tree_order_statistics_node_update>;
template<class K,class V> using HashMap=__gnu_pbds::gp_hash_table<K,V>;

#define all(a) a.begin(),a.end()
#define rall(a) a.rbegin(),a.rend()
#define __LOOPSWITCH(_1, _2, _3, __LOOPSWITCH, ...) __LOOPSWITCH
#define rep(...) __LOOPSWITCH(__VA_ARGS__, __RANGE, __REP, __LOOP) (__VA_ARGS__)
#define rrep(...) __LOOPSWITCH(__VA_ARGS__, __RRANGE, __RREP, __LOOP) (__VA_ARGS__)
#define __LOOP(q) __LOOP2(q, __LINE__)
#define __LOOP2(q,l) __LOOP3(q,l)
#define __LOOP3(q,l) __REP(_lp ## l,q)
#define __REP(i,n) __RANGE(i,0,n)
#define __RANGE(i,a,n) for(int i=((int)a);i<((int)n);++i)
#define __RREP(i,n) __RRANGE(i,0,n)
#define __RRANGE(i,a,n) for(int i=((int)n-1);i>=((int)a);--i)
#define repsq(i,n) for(int i=0;i*i<=n;++i)
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
	constexpr result_type operator()(){return operator()((int)min(),(int)max());}
	static constexpr result_type max(){return numeric_limits<result_type>::max();}
	static constexpr result_type min(){return 0;}
	constexpr Random(const bool&isDeterministic):y(isDeterministic?2463534242:chrono::system_clock::now().time_since_epoch().count()){}
	constexpr int operator()(int a,int b){return next()%(b-a)+a;}
	constexpr double operator()(double a,double b){return (b-a)*next()/4294967296.0+a;}
private:
	result_type y;
	constexpr result_type next(){return y^=(y^=(y^=y<<13)>>17)<<5;}
} Random(0);


#define endl '\n'

template<class T>struct Graph;
template<class T>struct DFSResult{
	vb connected;
	vector<T> distance;
	vi preorder, postorder, eulertour, subtreeNodeCount;
	vi subtreePathLengthSum;
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
template<class T=int>struct Graph{
	int size;
	T INF_VAL;
	vector<vector<tuple<int,T>>>edge;
	vector<vector<tuple<int,T>>>inverseEdge;
	Graph(int n=1,T inf=INF):size(n),INF_VAL(inf){
		edge.resize(size);
		inverseEdge.resize(size);
	}

	constexpr void add(int from, int to, T cost, bool directed=false){
		edge[from].emplace_back(to,cost);
		inverseEdge[to].emplace_back(from,cost);
		if (!directed) {
			edge[to].emplace_back(from,cost);
			edge[from].emplace_back(to,cost);
		}
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
			for(auto [nxt,cost]:g.edge[p]){
				if(ret[nxt]<=ret[p]+cost)continue;
				q.emplace(-ret[p]-cost,nxt);
			}
		}
		return ret;
	}
	pair<T,vi> dist(int s,int t){
		vi dist=this->dist(s);
		vi path(1,t);
		while(path.back()!=s){
			for(auto[from,cost]:g.inverseEdge[path.back()]){
				if(dist[from]==dist[path.back()]-cost){
					path.emplace_back(from);
					break;
				}
			}
		}
		reverse(all(path));
		return {dist[t], path};
	}
};

struct UnionFind{
	vi par,dist;
	UnionFind(int x){par.assign(x,-1); dist.assign(x,0);}
	int find(int x){return par[x]<0?x:find(par[x]);}
	int depth(int x){return par[x]<0?0:depth(par[x])+dist[x];}
	bool same(int x,int y){return find(x)==find(y);}
	int size(int x){return -par[find(x)];}
	int diff(int x,int y){return same(x,y)?depth(x)-depth(y):INF;}
	bool unite(int x,int y,int k=0){
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
		vector<tuple<T,int,int>> edge;
		vector<pair<int,int>> used;
		rep(from,g.size)for(auto [to,cost]:g.edge[from])edge.emplace_back(cost,from,to);
		sort(all(edge));
		for(auto [cost,from,to]:edge)if(uf.unite(from,to)){
			used.emplace_back(from,to);
			ans+=cost;
		}
		return {ans, used};
	}
};

struct StaticDataStore {
private:
	StaticDataStore() = default;

public:
	static inline int n, sy, sx;
	static inline vector<vector<int>> stage;
	static inline Timer timer;
	static inline Graph<int> cellGraph;

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

		cellGraph = Graph<int>((n+2)*(n+2));
		rep(i,1,n+1)rep(j,1,n+1)if(stage[i][j]){
			if(stage[i-1][j])cellGraph.add(i*(n+2)+j,(i-1)*(n+2)+j,stage[i-1][j], 1);
			if(stage[i+1][j])cellGraph.add(i*(n+2)+j,(i+1)*(n+2)+j,stage[i+1][j], 1);
			if(stage[i][j-1])cellGraph.add(i*(n+2)+j,i*(n+2)+j-1,stage[i][j-1], 1);
			if(stage[i][j+1])cellGraph.add(i*(n+2)+j,i*(n+2)+j+1,stage[i][j+1], 1);
		}
	}
};

struct _Construct {
	_Construct(){
		StaticDataStore::Input();
	}
	~_Construct(){
		cerr<<StaticDataStore::timer.get()<<" ms"<<endl;
	}
} _construct;


struct SolverInterface {
	virtual int Solve() = 0;
	virtual void Print() = 0;
	virtual string GetAnswer() = 0;

protected:

};


struct GreedySolver : public SolverInterface {
	using Point = pair<int, int>;

	const int pivotY, pivotX;		// 交差点選択のためのピボット
	vector<Point> allPoint;			// 全ての交差点の集合
	vector<Point> point;			// 訪れる交差点の集合
	vvi pointMap;					// pointの逆対応
	vvi distance;					// 交差点間の最短距離
	vi path;						// 交差点の訪問順

	static inline const auto& STAGE = StaticDataStore::stage;
	static inline const int n = StaticDataStore::n;
	static inline const int sy = StaticDataStore::sy;
	static inline const int sx = StaticDataStore::sx;
	static inline const Timer& baseTimer = StaticDataStore::timer;
	static inline const Graph<int> cellGraph = StaticDataStore::cellGraph;

	GreedySolver(int _pivotY, int _pivotX) : pivotY(_pivotY), pivotX(_pivotX) {
		pointMap.resize(n+2, vi(n+2, -1));

		vvi isLightenH(n+2, vi(n+2, 0));
		vvi isLightenV(n+2, vi(n+2, 0));
		const auto addPoint = [&](int y, int x){
			pointMap[y][x]=point.size();
			point.emplace_back(y,x);
			for(int dy=y ; STAGE[dy][x] ; dy--){
				if(STAGE[dy][x]==0)break;
				isLightenV[dy][x]=1;
			}
			for(int dy=y ; STAGE[dy][x] ; dy++){
				if(STAGE[dy][x]==0)break;
				isLightenV[dy][x]=1;
			}
			for(int dx=x ; STAGE[y][dx] ; dx--){
				if(STAGE[y][dx]==0)break;
				isLightenH[y][dx]=1;
			}
			for(int dx=x ; STAGE[y][dx] ; dx++){
				if(STAGE[y][dx]==0)break;
				isLightenH[y][dx]=1;
			}
		};
		addPoint(sy, sx);

		rep(i,1,n+1)rep(j,1,n+1)if(STAGE[i][j]!=0){
			bool v = STAGE[i-1][j] or STAGE[i+1][j];
			bool h = STAGE[i][j-1] or STAGE[i][j+1];
			if(v and h) allPoint.emplace_back(i,j);
		}

		const auto compare = [this](const auto& a, const auto& b){
			int d=abs(a.first-pivotY)+abs(a.second-pivotX);
			int d2=abs(b.first-pivotY)+abs(b.second-pivotX);
			return d>d2;
		};
		sort(all(allPoint), compare);

		for(auto [i,j]:allPoint){
			if(isLightenH[i][j] or isLightenV[i][j])continue;
			addPoint(i, j);
		}
		sort(rall(allPoint), compare);
		for(auto [i,j]:allPoint){
			if(isLightenH[i][j] and isLightenV[i][j])continue;
			addPoint(i, j);
		}

		distance = vvi(point.size(), vi(point.size(), INF));
		Dijkstra<int> dijkstra(cellGraph);
		rep(i, point.size()){
			int from = GetCellGraphIndexFromPoint(point[i]);
			auto res = dijkstra.dist(from);
			rep(j, point.size()){
				int to = GetCellGraphIndexFromPoint(point[j]);
				distance[i][j] = res[to];
			}
		}
	}

	void createInitPath(){
		path.clear();
		path.resize(point.size());
		Graph<int> mst(point.size());
		{
			Graph<int> pointGraph(point.size());
			rep(i,point.size())rep(j,point.size())if(i!=j){
				pointGraph.add(i,j,distance[i][j],1);
			}
			const auto[_, usedEdge] = Kruskal<int>(pointGraph).calc();
			for(auto [from, to] : usedEdge){
				mst.add(from, to, (distance[from][to]+distance[to][from])/2);
			}
		}

		auto preorder = mst.dfs(0).preorder;
		rep(i,preorder.size()){
			path[preorder[i]] = i;
		}
		path.emplace_back(0);
		// rep(i,path.size()){
		// 	cout<<path[i]<<" ";
		// }
		// cout<<endl;
	}

	int calculate(vi currentPath){
		int r=0;
		rep(i,currentPath.size()-1){
			r += distance[currentPath[i]][currentPath[i+1]];
		}
		return (int)round(10000 + 10000000.0 * n / r);
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
		return 100-pow(100, baseTimer.get()/3000.0);
	}

	int Solve() {
		createInitPath();

		int bestScore = calculate(path);
		cerr<<"INIT: "<<bestScore<<endl;

		auto currentPath = path;
		int challenge = 0;
		int type=0, typeCount = 3;
		bool isModified = false;

		int a=1, b=1;
		while(baseTimer){
			/* change */
			challenge++;

			if(++b == path.size() - 1){
				if(++a == path.size() - 2){
					if(++type==typeCount){
						if(!isModified) break;
						isModified = false;
						type = 0;
					}
					a=1;
				}
				b=a+1;
			}

			if(currentPath[a] == 0)continue;
			if(currentPath[b] == 0)continue;
			switch(type){
				case 0: {
					/* 隣接要素の訪問順をswap */
					
					swap(currentPath[a], currentPath[b]);
					break;
				}
				case 1: {
					/**
					 *  a, a+1, ... , b  を
					 *  a+1, ... , b, a  に変更
					 */
					auto c2=currentPath;
					currentPath.clear();
					rep(i,c2.size()){
						if(i==a)continue;
						currentPath.emplace_back(c2[i]);
						if(i==b)currentPath.emplace_back(c2[a]);
					}
					break;
				}
				case 2: {
					/**
					 *  a, a+1, ... , b  を
					 *  b, a, a+1, ...   に変更
					 */
					auto c2=currentPath;
					currentPath.clear();
					rep(i,c2.size()){
						if(i==a)currentPath.emplace_back(c2[b]);
						if(i!=b)currentPath.emplace_back(c2[i]);
					}
					break;
				}
				case 3: {
					/**
					 *  aを削除
					 */
					if(b!=1)continue;
					auto c2=currentPath;
					currentPath.clear();
					rep(i,c2.size()){
						if(i!=a)currentPath.emplace_back(c2[i]);
					}
					break;
				}
			}

			int currentScore = calculate(currentPath);
			if(chmax(bestScore, currentScore)){
				path = currentPath;
				isModified = true;
			}else{
				currentPath = path;
			}
		}
		// rep(i,path.size()){
		// 	cout<<path[i]<<" ";
		// }
		// cout<<endl<<endl;
		return bestScore;
	}

	static int GetCellGraphIndexFromPoint(Point& p){
		return p.first*(n+2)+p.second;
	}

	string Move(int fromPoint, int toPoint) {
		Dijkstra<int> dijkstra(cellGraph);

		int fromIndex = GetCellGraphIndexFromPoint(point[fromPoint]);
		int toIndex = GetCellGraphIndexFromPoint(point[toPoint]);
		auto[_, route] = dijkstra.dist(fromIndex, toIndex);

		string ret = "";
		rep(i,route.size()-1){
			if(route[i]+1 == route[i+1]) ret += "R";
			if(route[i]-1 == route[i+1]) ret += "L";
			if(route[i]+n+2 == route[i+1]) ret += "D";
			if(route[i]-n-2 == route[i+1]) ret += "U";
		}
		return ret;
	}

	void Print() {
		cout<<GetAnswer()<<endl<<flush;
	}

	string GetAnswer(){
		string ans = "";
		rep(i,path.size()-1){
			ans += Move(path[i],path[i+1]);
		}
		return ans;
	}
};

int main(){
	SolverInterface* solver = new GreedySolver(StaticDataStore::sy, StaticDataStore::sx);

	int bestScore = solver->Solve();
	int bestY=StaticDataStore::sy, bestX=StaticDataStore::sx;

	string bestPath = solver->GetAnswer();
	int cnt=0;

	vector<pair<int,int>> pivots;
	vvi pivotsMap(StaticDataStore::n+2, vi(StaticDataStore::n+2,0));
	vector<pair<int, pair<int,int>>> pivotsScore;

	rep(i,StaticDataStore::n+2){
		rep(j,StaticDataStore::n+2){
			if(i%10 == 5 and j%10 == 5) 
				pivots.emplace_back(i,j);
		}
	}

	int challenge = 0, mode = 0;
	while(StaticDataStore::timer and !pivots.empty()){
		auto[y,x] = pivots.back();
		pivots.pop_back();

		challenge++;

		solver = new GreedySolver(y,x);
		int score = solver->Solve();
		if(chmax(bestScore, score)){
			bestPath = solver->GetAnswer();
			bestY = y;
			bestX = x;
		}
		pivotsScore.emplace_back(score, make_pair(y,x));
		pivotsMap[y][x]=score;
		cerr<<y<<","<<x<<" : "<<score<<"("<<++cnt<<")"<<endl;
		if(pivots.empty()){
			if(mode==0){
				sort(all(pivotsScore));
				for(auto&[sc, p]:pivotsScore){
					cerr<<sc<<" : "<<p.first<<","<<p.second<<endl;
					for(int i=-4; i<=4 ; i+=2){
						for(int j=-4; j<=4 ; j+=2){
							if(i==0 and j==0)continue;
							if(p.first+i>=StaticDataStore::n+2)continue;
							if(p.second+j>=StaticDataStore::n+2)continue;
							pivots.push_back({p.first+i,p.second+j});
						}
					}
				}
				mode = 1;
			}
		}
	}

	cout<<bestPath<<endl<<flush;
	// rep(i,StaticDataStore::n+2){
	// 	rep(j,StaticDataStore::n+2){
	// 		cout<<pivotsMap[i][j]<<"\t";
	// 	}
	// 	cout<<endl;
	// }
	cerr<<"N: "<<StaticDataStore::n<<endl;
	cerr<<"CHALLENGE: "<<challenge<<endl;
	cerr<<"SCORE: "<<bestScore<<endl;
	
	// cout<<StaticDataStore::n<<"\t"<<bestScore<<"\t";
	// cout<<StaticDataStore::sy<<"\t"<<StaticDataStore::sx<<"\t";
	// cout<<bestY<<"\t"<<bestX<<endl<<flush;
}

/*
var src = document.createElement("script");
src.src = "https://code.jquery.com/jquery-3.6.0.slim.min.js";
document.body.appendChild(src);

var d=0;
var interval = setInterval(function() {
	if(d<1000000) d += 10000;
	$("#t_bar").val( d );
	visualize();
	if(d==1000000)clearInterval(interval);
}, 20);
*/

/*
DDLLDDDDLLLLDDDDDDDDLLDDLLLLLLLLLLLLRRUUUUUUUURRRRDDLLRRUUUUUUUUUUUURRUUUULLLLUUUULLUULLUUUUUUUUUUUUUUUUUUUUDDDDDDDDRRDDDDRRRRRRUUDDRRDDDDRRRRRRDDRRRRRRRRUURRRRUUUURRRRUUUUUUUUUUDDDDLLLLLLLLLLUUUULLUUDDLLLLRRRRRRDDDDRRRRRRRRRRDDRRRRRRDDRRRRRRLLLLLLDDDDRRDDDDRRLLLLLLLLDDLLDDDDDDDDRRDDDDDDDDDDDDRRUURRUURRRRRRRRLLDDDDDDDDDDDDRRLLLLLLLLLLLLLLLLLLLLLLLLUUUUUUUUUURRUUUUUUUURRUUDDLLLLLLDD
208300

DDRRRRDDDDLLDDLLDDDDLLLLLLDDDDLLLLLLLLLLLLLLRRUUUUUUUURRRRRRRRRRUUUUUUUULLLLUUUUUUUUUULLLLUUUULLLLRRUUUUUUUUUURRRRUUUUUUUUDDDDDDDDRRRRRRDDDDDDUUUUUURRRRUUUUUURRRRRRUUDDRRRRDDRRRRRRUURRRRRRDDDDDDDDRRRRRRLLLLDDDDDDDDRRDDDDDDDDDDDDLLRRRRRRDDDDDDLLDDDDDDDDDDDDRRLLLLLLLLLLLLLLLLUUUUUUUUUURRRRRRLLUUUUUUUULLLLLLLLUUUUUUUUUUUURRLLLLLLLLDDDDDDDDDDDDDD
228263
*/