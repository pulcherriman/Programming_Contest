/*
 * Unsecured Optimization
 */
// #pragma GCC target "avx"
// #pragma GCC target "sse4.2"
// #pragma GCC optimize "O3"
// #pragma GCC optimize "fast-math"
// #pragma GCC optimize "unroll-loops"
#ifdef _DEBUG
#define _GLIBCXX_DEBUG 1
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

void Main();
int main(){cin.tie(nullptr);ios::sync_with_stdio(false);Main();return 0;}

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
constexpr double EPS=(1e-9);
constexpr ll MOD=1000000007ll;
constexpr long double PI=3.14159265358979323846;

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

// ここにライブラリを貼る
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
	Timer(uint64_t _limit): start(getClocks()),limit(start+_limit*ClocksPerMsec) {}
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

struct Vegetable {
	int y, x, start, end, value;
};
struct Harvester {
	int y, x;
};
int HarvesterCount = 0;

const int n=16, m=5000, t=1000;
const int TLE = 2000;
const int NONE = -1;
int field[n][n];
int money=1;
Timer timer(TLE);
Vegetable veg[m];
Harvester hrv[100];
vector<int> VegetableIndexOfStartDate[t];
vector<int> VegetableIndexOfEndDate[t];

inline bool IsBuyableHarvester() {
	return money >= (HarvesterCount+1) * (HarvesterCount+1) * (HarvesterCount+1);
}

void AddHarvester(int y, int x) {
	assert(IsBuyableHarvester());
	hrv[HarvesterCount].y = y;
	hrv[HarvesterCount].x = x;
	HarvesterCount++;
	money -= HarvesterCount * HarvesterCount * HarvesterCount;
	cout << y << " " << x << endl;
}

void MoveHarvester(int index, int y, int x) {
	assert(index < HarvesterCount);
	cout << hrv[index].y << " " << hrv[index].x << " " << y << " " << x << endl;
	hrv[index].y = y;
	hrv[index].x = x;
}

inline void DoNothing() {
	cout << -1 <<endl;
}

void UpdateField_Morning(int date) {
	for (auto&index : VegetableIndexOfStartDate[date]) {
		field[veg[index].y][veg[index].x] = index;
	}
}

void UpdateField_Night(int date) {
	for (auto&index : VegetableIndexOfEndDate[date]) {
		field[veg[index].y][veg[index].x] = NONE;
	}
}

struct AdjacentElement {
	int date, index;
	int start=t+1, end=0;
	int score=0;
	vector<int> useVeg;
	AdjacentElement(int _date, vector<int> _useVeg) {
		date = _date;
		useVeg = _useVeg;
		for(int i:useVeg) {
			chmin(start, veg[i].start);
			chmax(end, veg[i].end);
			if(chmax(score, veg[i].value)) index = i;
		}
		score*=useVeg.size();
	}
	bool operator<( const AdjacentElement& right ) const {
        return score == right.score ? date < right.date : score < right.score;
    }
	bool operator==( const AdjacentElement& right ) const {
        return score == right.score && start == right.start && end == right.end && index == right.index;
    }
};

pair<int,int> MaxPerformance[m];
vector<AdjacentElement> adjElems;
void CheckAdjacentElements(int date) {
	bool visited[n][n] = {};
	queue<int> q;
	rep(i,n)rep(j,n)if(field[i][j]!=NONE and !visited[i][j]){
		int maxValue = 0, cnt = 0;
		vector<int> used;
		q.push(field[i][j]);
		while (!q.empty()) {
			int p = q.front(); q.pop();
			int y=veg[p].y, x=veg[p].x;			
			if(visited[y][x])continue;
			visited[y][x]=true;
			used.push_back(p);
			cnt++;
			chmax(maxValue, veg[p].value);
			if(y>0 and field[y-1][x]!=NONE and !visited[y-1][x]) q.push(field[y-1][x]);
			if(x>0 and field[y][x-1]!=NONE and !visited[y][x-1]) q.push(field[y][x-1]);
			if(y<n-1 and field[y+1][x]!=NONE and !visited[y+1][x]) q.push(field[y+1][x]);
			if(x<n-1 and field[y][x+1]!=NONE and !visited[y][x+1]) q.push(field[y][x+1]);
		}
		// cout<<maxIndex<<": "<<maxValue<<"x"<<cnt<<"="<<maxValue*cnt<<endl;
		adjElems.emplace_back(date, used);
	}
}

void CreateIslandStatus() {
	rep(date,t){
		UpdateField_Morning(date);
		CheckAdjacentElements(date);
		UpdateField_Night(date);
	}
	sort(rall(adjElems));
	adjElems.erase(unique(all(adjElems)), adjElems.end());
}


/*
 * Greedy
 */
const pair<int,int> NONE_COOR = {NONE,NONE};
vector<pair<int,int>> harvesterMoveTo(t, NONE_COOR);
int fieldLogging[t][n][n];
bool IsValidElement(int index) {
	auto adj=adjElems[index];
	for(auto&i:adj.useVeg){
		rep(d, veg[i].start, veg[i].end+1) {
			if(fieldLogging[d][veg[i].y][veg[i].x]!=NONE)return false;
		}
	}
	return true;
}

void Decide(int index) {
	auto adj=adjElems[index];
	if(harvesterMoveTo[adj.date] != NONE_COOR) {
		// cout << "duplicated." <<endl;
		return;
	}

	for(auto&i:adj.useVeg){
		rep(d, veg[i].start, veg[i].end+1) {
			fieldLogging[d][veg[i].y][veg[i].x] = index;
		}
	}
	// cout<<adj.date<<" : "<<veg[adj.index].y<<", "<<veg[adj.index].x<<endl;
	// cout<<adj.date<<" : "<<adj.score<<" ("<<adj.start<<" - "<<adj.end<<", "<<adj.index<<")"<<endl;
	harvesterMoveTo[adj.date] = {veg[adj.index].y, veg[adj.index].x};
}

void Greedy() {
	rep(i,t)rep(j,n)rep(k,n)fieldLogging[i][j][k]=NONE;

	rep(i,adjElems.size()) {
		if(IsValidElement(i)) {
			Decide(i);
			// asns
		}
	}
	
	rep(i,t){
		// cout<<harvesterMoveTo[i].first<<", "<<harvesterMoveTo[i].second<<endl;
		if(IsBuyableHarvester()) {
			if(harvesterMoveTo[i] == NONE_COOR) {
				rep(y,n)rep(x,n)if(fieldLogging[i][y][x]==NONE){
					AddHarvester(y,x);
					y=x=n;
				}
			} else {
				AddHarvester(harvesterMoveTo[i].first, harvesterMoveTo[i].second);
			}
			continue;
		}

		if(harvesterMoveTo[i] == NONE_COOR) {
			DoNothing();
		} else {
			MoveHarvester(Random(0, HarvesterCount), harvesterMoveTo[i].first, harvesterMoveTo[i].second);
		}
	}
}
/*
 * Greedy Finish
 */

void Main(){
	{
		// input section
		int _;
		cin>>_>>_>>_;
		rep(i,n)rep(j,n)field[i][j]=NONE;
		rep(i,m){
			cin>>veg[i].y>>veg[i].x>>veg[i].start>>veg[i].end>>veg[i].value;
			VegetableIndexOfStartDate[veg[i].start].push_back(i);
			VegetableIndexOfEndDate[veg[i].end].push_back(i);
		}
	}

	CreateIslandStatus();

	Greedy();

}
