/*
 * Unsecured Optimization
 */
#pragma GCC target "avx"
#pragma GCC target "sse4.2"
#pragma GCC optimize "Ofast"
// #pragma GCC optimize "fast-math"
// #pragma GCC optimize "unroll-loops"
#ifndef _DEBUG
#define NDEBUG
#endif

#include<iostream>
#include<vector>
#include<array>
#include<queue>
#include<iomanip>
#include<chrono>
#include<limits>
#include<cassert>
using namespace std;

void Main();
int main(){cin.tie(nullptr);ios::sync_with_stdio(false);Main();return 0;}

/*
 * Additional Type Definition
 */
using ll=long long;
using ull=unsigned long long;
using vb=vector<bool>;
using vvb=vector<vb>;
using vi=vector<int>;
using vvi=vector<vi>;
using vl=vector<ll>;
using vvl=vector<vl>;
using pll=pair<ll,ll>;
using vp=vector<pll>;
using tl2=tuple<ll,ll>;
using tl3=tuple<ll,ll,ll>;

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
constexpr int INF=100000000;

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
	int adjacent = 0;
	int valueSum = 0;
};

const int DY[]={1,-1,0,0};
const int DX[]={0,0,1,-1};
const int n=16, m=5000, t=1000;
const int TLE = 1930;
const int NONE = -1;
const pair<int,int> NONE_COOR = {NONE,NONE};
Vegetable veg[m];
vector<int> VegetableIndexOfStartDate[t];
vector<int> VegetableIndexOfEndDate[t];

void Initialize() {
	int _;
	cin>>_>>_>>_;
	rep(i,m){
		cin>>veg[i].y>>veg[i].x>>veg[i].start>>veg[i].end>>veg[i].value;
		VegetableIndexOfStartDate[veg[i].start].push_back(i);
		VegetableIndexOfEndDate[veg[i].end].push_back(i);
	}
}

struct Simulator {
	using ActionInfo = array<int, 4>;
	enum PHASE {
		NOTHING,		// 野菜出現前
		APPEARED,		// 野菜出現後
		ACTIONED,		// 操作後
		HARVESTED,		// 収穫後
		DISAPPEARED,	// 野菜消滅後
	};
	int vegField[n][n];
	int hrvField[n][n];
	ActionInfo action[t];
	Harvester hrv[n*n];
	int date = -1;
	int money = 1;
	int HarvesterCount = 0;
	PHASE phase = DISAPPEARED;

	Simulator() {
		Reset();
	}

	void Reset(bool hardReset = false) {
		rep(i,n)rep(j,n){
			vegField[i][j] = NONE;
			hrvField[i][j] = NONE;
		}
		if(hardReset) rep(i,t)rep(j,4) action[i][j] = -1;
		date = -1;
		money = 1;
		HarvesterCount = 0;
		phase = DISAPPEARED;
	}

	constexpr int& VegFieldRef(int index) {
		return vegField[veg[index].y][veg[index].x];
	}
	
	bool GoodMorning() {
		if(phase == DISAPPEARED) Sleep();
		if(date == t) return false;
		if(phase == NOTHING) Appear();
		return true;
	}

	void GoodNight() {
		if(phase == ACTIONED) Harvest();
		if(phase == HARVESTED) Disappear();
	}

	void Appear() {
		assert(phase == NOTHING);
		for (auto&index : VegetableIndexOfStartDate[date]) {
			VegFieldRef(index) = index;
		}
		phase = APPEARED;
	}

	bool IsBuyableHarvester() {
		return money >= (HarvesterCount+1) * (HarvesterCount+1) * (HarvesterCount+1);
	}

	inline ActionInfo DoNothing() {
		return {-1, -1, -1, -1};
	}

	ActionInfo AddHarvester(int y, int x) {
		assert(IsBuyableHarvester());
		assert(hrvField[y][x]==NONE);
		hrv[HarvesterCount].y = y;
		hrv[HarvesterCount].x = x;
		hrvField[y][x]=HarvesterCount;
		HarvesterCount++;
		money -= HarvesterCount * HarvesterCount * HarvesterCount;
		return {y, x, -1, -1};
	}

	ActionInfo MoveHarvester(int index, int y, int x) {
		assert(index < HarvesterCount);
		if(hrvField[y][x]!=NONE){
			assert(hrvField[y][x] == index);
			cerr<<"move position is same."<<endl;
		}
		assert(hrvField[hrv[index].y][hrv[index].x]!=NONE);
		ActionInfo ret={hrv[index].y, hrv[index].x, y, x};
		hrvField[hrv[index].y][hrv[index].x]=NONE;
		hrvField[y][x]=index;
		hrv[index].y = y;
		hrv[index].x = x;
		return ret;
	}

	ActionInfo ApplyAction(ActionInfo act) {
		if(act[0] == NONE) {
			return DoNothing();
		} else if(act[2] == NONE) {
			return AddHarvester(act[0], act[1]);
		} else {
			return MoveHarvester(hrvField[act[0]][act[1]], act[2], act[3]);
		}
	}

	using array2d = array<array<int,n>, n>;
	pair<array2d ,array2d> HarvesterConnection(){
		queue<int> q;
		array2d visited;
		array2d adjacent;
		rep(i,n)rep(j,n)visited[i][j]=adjacent[i][j]=0;

		rep(i,HarvesterCount) {
			q.push(i);
			vi used;
			while (!q.empty()) {
				int p = q.front(); q.pop();
				int y=hrv[p].y, x=hrv[p].x;			
				if(visited[y][x])continue;
				visited[y][x]=1;
				used.push_back(p);
				rep(v,4){
					int ny=y+DY[v], nx=x+DX[v];
					if(ny<0 or nx<0 or ny>=n or nx>=n) continue;
					if(hrvField[ny][nx]==NONE) {
						adjacent[ny][nx]++;
						continue;
					}
					if(visited[ny][nx]) continue;
					q.push(hrvField[ny][nx]);
				}
				if(vegField[y][x]!=NONE) adjacent[y][x]=0;
			}
			for(auto&p:used)visited[hrv[p].y][hrv[p].x]=used.size();
		}
		return {visited, adjacent};
	}

	void CreateInitialActions(int MAX_HARVESTERS = 40) {
		Reset();
		rep(d,t){
			GoodMorning();

			// どの座標に動かすか決定
			// 今の盤面を見て、1手で獲得できる最善とスコアを計算する
			ActionInfo bestAction = {};
			{
				auto[_, adjacent] = HarvesterConnection();
				int maxIncome=-1;
				int centerPoint=100;

				// vvi ddd(n,vi(n,0));
				// rep(i,n)rep(j,n)ddd[i][j]=adjacent[i][j];
				// puta(ddd);
				Simulator tmp = *this;

				rep(toY,n)rep(toX,n){
					if(adjacent[toY][toX] == 0 and vegField[toY][toX]==NONE) continue;
					if(hrvField[toY][toX]!=NONE) continue;
					if(d>200 and adjacent[toY][toX]==0)continue;

					if(IsBuyableHarvester() and HarvesterCount<MAX_HARVESTERS) {
						tmp = *this;
						auto act = tmp.AddHarvester(toY, toX);
						tmp.phase = ACTIONED;
						int income =  tmp.Harvest();
						if(chmax(maxIncome, income)){
							bestAction = act;
						}
					}
					if(d == 0) continue;

					rep(i,HarvesterCount){
						tmp = *this;
						auto act = tmp.MoveHarvester(i, toY, toX);
						tmp.phase = ACTIONED;
						int income =  tmp.Harvest();
						if(chmax(maxIncome, income)){
							bestAction = act;
						}else if(maxIncome == income){
							if(chmin(centerPoint, (int)(abs(8-toY)+abs(8-toX)))){
								bestAction = act;
							}
						}
					}
				}
			}

			// 処理の決定
			action[d] = ApplyAction(bestAction);

			phase = ACTIONED;
			GoodNight();
		}
	}

	bool Action() {
		assert(phase == APPEARED);

		if(action[date][0] == -1){

		} else if(action[date][2] == -1){
			AddHarvester(action[date][0], action[date][1]);
		} else {
			MoveHarvester(hrvField[action[date][0]][action[date][1]], action[date][2], action[date][3]);
		}

		phase = ACTIONED;
		return true;
	}

	int Harvest() {
		assert(phase == ACTIONED);

		int totalEarned = 0;
		queue<int> q;
		bool visited[n][n] = {};
		rep(i,HarvesterCount) {
			if(vegField[hrv[i].y][hrv[i].x]==NONE)continue;
			q.push(i);
			int cnt=0, sum=0;
			while (!q.empty()) {
				int p = q.front(); q.pop();
				int y=hrv[p].y, x=hrv[p].x;			
				if(visited[y][x])continue;
				visited[y][x]=true;
				cnt++;
				if(vegField[y][x]!=NONE){
					sum+=veg[vegField[y][x]].value;
					vegField[y][x]=NONE;
				}
				rep(v,4){
					int ny=y+DY[v], nx=x+DX[v];
					if(ny<0 or nx<0 or ny>=n or nx>=n) continue;
					if(visited[ny][nx]) continue;
					if(hrvField[ny][nx]==NONE) continue;
					q.push(hrvField[ny][nx]);
				}
			}
			totalEarned += sum * cnt;
		}
		money += totalEarned;

		phase = HARVESTED;
		return totalEarned;
	}

	void Disappear() {
		assert(phase == HARVESTED);
		for (auto&index : VegetableIndexOfEndDate[date]) {
			VegFieldRef(index) = NONE;
		}
		phase = DISAPPEARED;
	}

	void Sleep() {
		assert(phase == DISAPPEARED);
		date++;
		phase = NOTHING;
	}

// #ifdef _DEBUG
// 	void OutputVegField() {
// 		vvi val(n, vi(n));
// 		rep(i,n)rep(j,n)val[i][j]=vegField[i][j];
// 		puta(val);
// 	}
// #endif

	void OutputAction() {
		const char br='\n', sp=' ';
		for(auto&act : action) {
			if(act[0]==-1) {
				cout<<-1<<br;
			} else if(act[2]==-1) {
				cout<<act[0]<<sp<<act[1]<<br;
			} else {
				cout<<act[0]<<sp<<act[1]<<sp<<act[2]<<sp<<act[3]<<br;
			}
		}
		cerr<<money<<endl;
	}

	void SimulateDay() {
		if(!GoodMorning()) return;
		Action();
		GoodNight();
	}

	void Simulate() {
		while(date < t){
			SimulateDay();
		}
	}
};


void Main(){
	Timer timer(TLE);
	Initialize();

	Simulator simulator;
	{
		int maxValue = 0;

		rep(i,44,46){
			Simulator tmp;
			tmp.CreateInitialActions(i);
			tmp.Simulate();
			if (chmax(maxValue, tmp.money)) simulator = tmp;
			// cerr<<i<<":"<<tmp.money<<endl;
			if(tmp.HarvesterCount < i) break;
		}
	}
	simulator.OutputAction();
	cerr<<timer.get()<<endl;

}
//   Case #: 80
//  Average: 1926468
// Expected: 96323400
//      Max: 2932564
//      Min: 1