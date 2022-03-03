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
constexpr ll LINF=1ll<<60;
constexpr int INF=1<<30;
constexpr double EPS=(1e-14);
constexpr long double PI=3.14159265358979323846;

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

struct GreedySolver : public SolverInterface {
	int score = 0;
	vector<vector<pair<int,int>>> graph;
	vector<pair<int, int>> point;
	vector<vector<int>> pointMap;
	int startPoint;
	vector<int> path;
	vector<int> pathInfo;

	GreedySolver() {
		const auto& stage = StaticDataStore::stage;
		const int n = StaticDataStore::n;

		graph.resize(n+2);
		pointMap.resize(n+2, vi(n+2,-1));
		rep(i,1,n+1)rep(j,1,n+1)if(stage[i][j]!=0){
			bool v=false, h=false;
			if(stage[i-1][j])v=true;
			if(stage[i+1][j])v=true;
			if(stage[i][j-1])h=true;
			if(stage[i][j+1])h=true;
			if(v and h){
				pointMap[i][j]=point.size();
				point.emplace_back(i,j);
				cerr<<pointMap[i][j]<<" : ("<<i<<","<<j<<")"<<endl;
			}
		}

		const int sy = StaticDataStore::sy;
		const int sx = StaticDataStore::sx;
		if(pointMap[sy][sx] == -1){
			pointMap[sy][sx]=point.size();
			point.emplace_back(sy,sx);
		}
		startPoint = pointMap[sy][sx];

		graph.resize(point.size());
		rep(i,point.size()){
			{//→
				int dist=0;
				auto[y,x]=point[i];
				rep(dx, x+1, n+1){
					if(stage[y][dx]==0)break;
					dist+=stage[y][dx];
					if(pointMap[y][dx]==-1) continue;
					int other = pointMap[y][dx];
					// distを平滑化
					// graph[i].emplace_back(other, dist);
					// graph[other].emplace_back(i, dist - stage[y][dx] + stage[y][x]);
					dist=(dist * 2 - stage[y][dx] + stage[y][x])/2;
					graph[i].emplace_back(other, dist);
					graph[other].emplace_back(i, dist);
					break;
				}
			}
			{//↓
				int dist=0;
				auto[y,x]=point[i];
				rep(dy, y+1, n+1){
					if(stage[dy][x]==0)break;
					dist+=stage[dy][x];
					if(pointMap[dy][x]==-1) continue;
					int other = pointMap[dy][x];
					// graph[i].emplace_back(other, dist);
					// graph[other].emplace_back(i, dist - stage[dy][x] + stage[y][x]);
					dist=(dist * 2 - stage[dy][x] + stage[y][x])/2;
					graph[i].emplace_back(other, dist);
					graph[other].emplace_back(i, dist);
					break;
				}
			}
		}

		// rep(i,point.size()){
		// 	cout<<"point : "<<i<<" ("<<point[i].first<<","<<point[i].second<<")"<<endl;
		// 	rep(j,graph[i].size()){
		// 		cout<<"  "<<graph[i][j].first<<" "<<graph[i][j].second<<endl;
		// 	}
		// }
	}

	int Solve() {

		// ワーシャルフロイド
		{
			vvi dist(point.size(), vi(point.size(),INF));
			rep(i,point.size())for(auto&[to,d] : graph[i])dist[i][to]=dist[to][i]=d;
			rep(i, point.size())
			rep(k, point.size())if(dist[i][k]!=INF)
			rep(j, point.size())if(i!=j)if(dist[k][j]!=INF)if(IsMovable(i,j)){
				dist[i][j]=min(dist[i][j], dist[i][k]+dist[k][j]);
			}

			graph = vector<vector<pii>>(point.size());
			
			rep(i,point.size())rep(j,point.size())if(dist[i][j]!=INF){
				graph[i].emplace_back(j,dist[i][j]);
				// cout<<"dist["<<i<<"]["<<j<<"]="<<dist[i][j]<<endl;
			}
		}

		vector<vector<pair<int,int>>> mst =graph;
		

		vb verticalViewed(point.size(), false);
		vb horizontalViewed(point.size(), false);
		const auto& stage = StaticDataStore::stage;
		HashSet<int> enqueued;
		
		path.clear();
		{
			vector<bool> visited(point.size(), false);
			stack<pair<int,int>> st;
			st.emplace(-1, startPoint);
			enqueued.insert(startPoint);
			while(!st.empty()){
				auto[prev,now]= st.top();
				st.pop();
				if(prev == -2){
					path.emplace_back(now);
					pathInfo.emplace_back(-1);
					continue;
				}
				if(visited[now])continue;
				if(horizontalViewed[now] and verticalViewed[now]){
					bool ok = false;
					for(auto&[to,dist] : mst[now]){
						if(visited[to])continue;
						if(horizontalViewed[to] and verticalViewed[to])continue;
						ok=true;
					}
					st.pop();
					if(!ok)continue;
				}
				path.emplace_back(now);
				if(horizontalViewed[now] and verticalViewed[now]){
					pathInfo.emplace_back(1);
				}else{
					pathInfo.emplace_back(0);
				}
				visited[now]=true;
				
				// 頂点nowに到達
				auto[y,x]=point[now];
				// cout<<"now : "<<now<<" => "<<y<<","<<x<<endl;
				if(!horizontalViewed[now]){
					for(int dx=x ; stage[y][dx] ; dx++){
						if(stage[y][dx]==0)break;
						if(pointMap[y][dx]==-1) continue;
						int tgt = pointMap[y][dx];
						horizontalViewed[tgt]=true;
						// cout<<"horizontalViewed :"<<point[tgt].first<<","<<point[tgt].second<<endl;
					}
					for(int dx=x ; stage[y][dx] ; dx--){
						if(stage[y][dx]==0)break;
						if(pointMap[y][dx]==-1) continue;
						int tgt = pointMap[y][dx];
						horizontalViewed[tgt]=true;
						// cout<<"horizontalViewed :"<<point[tgt].first<<","<<point[tgt].second<<endl;
					}
				}
				if(!verticalViewed[now]){
					for(int dy=y ; stage[dy][x] ; dy++){
						if(stage[dy][x]==0)break;
						if(pointMap[dy][x]==-1) continue;
						int tgt = pointMap[dy][x];
						verticalViewed[tgt]=true;
						// cout<<"verticalViewed :"<<point[tgt].first<<","<<point[tgt].second<<endl;
					}
					for(int dy=y ; stage[dy][x] ; dy--){
						if(stage[dy][x]==0)break;
						if(pointMap[dy][x]==-1) continue;
						int tgt = pointMap[dy][x];
						verticalViewed[tgt]=true;
						// cout<<"verticalViewed :"<<point[tgt].first<<","<<point[tgt].second<<endl;
					}
				}

				vector<tl3> tmp;
				for(auto&[to,dist] : mst[now]){
					if(visited[to])continue;
					if(horizontalViewed[to] and verticalViewed[to])continue;
					tmp.emplace_back(dist, now, to);
				}
				sort(rall(tmp));
				for(auto&[dist,now,to] : tmp){
					st.emplace(-2, now);
					st.emplace(now, to);
				}
			}
		}
		
		return score;
	}

	bool IsMovable(int from, int to) {
		auto[fy,fx]=point[from];
		auto[ty,tx]=point[to];
		return fy == ty or fx == tx;
	}

	string Move(int from, int to) {
		auto[fy,fx]=point[from];
		auto[ty,tx]=point[to];
		
		char dir='.';
		if(fy == ty){
			dir = fx < tx ? 'R' : 'L';
		}else{
			dir = fy < ty ? 'D' : 'U';
		}

		int dist = abs(fx-tx) + abs(fy-ty);

		return string(dist, dir);
	}

	void Print() {
		/* 結果を出力 */
		rep(i,path.size()-1){
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
