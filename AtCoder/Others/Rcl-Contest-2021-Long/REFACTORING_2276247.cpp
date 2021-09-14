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
	array2d HarvesterConnection(){
		queue<int> q;
		bool visited[n][n] = {};
		array2d adjacent;
		rep(i,n)rep(j,n)adjacent[i][j]=0;

		rep(i,HarvesterCount) {
			q.push(i);
			while (!q.empty()) {
				int p = q.front(); q.pop();
				int y=hrv[p].y, x=hrv[p].x;			
				if(visited[y][x])continue;
				visited[y][x]=true;
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
		}
		return adjacent;
	}

	ActionInfo CreateInitialActionOneday(int MAX_HARVESTERS) {
		// どの座標に動かすか決定
		// 今の盤面を見て、1手で獲得できる最善とスコアを計算する
		ActionInfo bestAction = {};

		auto adjacent = HarvesterConnection();
		int maxIncome=-1;
		int centerPoint=100;

		Simulator tmp = *this;

		rep(toY,n)rep(toX,n){
			if(adjacent[toY][toX] == 0 and vegField[toY][toX]==NONE) continue;
			if(hrvField[toY][toX]!=NONE) continue;
			if(date>200 and adjacent[toY][toX]==0)continue;

			if(IsBuyableHarvester() and HarvesterCount<MAX_HARVESTERS) {
				tmp = *this;
				auto act = tmp.AddHarvester(toY, toX);
				tmp.phase = ACTIONED;
				int income =  tmp.Harvest();
				if(chmax(maxIncome, income)){
					bestAction = act;
				}
			}

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
		return bestAction;
	}

	void CreateInitialActions(int MAX_HARVESTERS = 40) {
		Reset();
		rep(d,t){
			GoodMorning();

			auto bestAction = CreateInitialActionOneday(MAX_HARVESTERS);
			action[d] = ApplyAction(bestAction);

			phase = ACTIONED;
			GoodNight();
		}
	}

	void Action() {
		assert(phase == APPEARED);

		if(action[date][0] == -1){

		} else if(action[date][2] == -1){
			AddHarvester(action[date][0], action[date][1]);
		} else {
			MoveHarvester(hrvField[action[date][0]][action[date][1]], action[date][2], action[date][3]);
		}

		phase = ACTIONED;
	}

	bool CheckedAction() {
		assert(phase == APPEARED);

		if(action[date][0] == -1){

		} else if(action[date][2] == -1){
			if(!IsBuyableHarvester()) return false;
			if(hrvField[action[date][0]][action[date][1]]!=NONE) return false;
			AddHarvester(action[date][0], action[date][1]);
		} else {
			if(hrvField[action[date][2]][action[date][3]]!=NONE) return false;
			if(hrvField[action[date][0]][action[date][1]]==NONE) return false;
			if(hrv[hrvField[action[date][0]][action[date][1]]].y != action[date][0]) return false;
			if(hrv[hrvField[action[date][0]][action[date][1]]].x != action[date][1]) return false;
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

	bool ChangeAction() {
		if(action[date][2]==NONE) return false;

		int currentTgt = hrvField[action[date][0]][action[date][1]];
		int newtgt=currentTgt;
		{
			int maxValue=-INF;
			rep(i,HarvesterCount){
				int d=abs(action[date][2]-hrv[i].y)+abs(action[date][3]-hrv[i].x);
				if(chmax(maxValue, d)) newtgt=i;
			}
			if(newtgt == currentTgt) {
				return false;
			}
		}

		// 同じ操作ならやらない
		// TODO
		Harvester placePos={action[date][2],action[date][3]};

		// 今回新しく動かしたやつの辻褄合わせ
		bool check_tmp=true;
		rep(i,date+1,t){
			if(check_tmp && action[i].size()==4 and action[i][2]==action[date][0] and action[i][3]==action[date][1]) {
				action[i]={-1,-1,-1,-1};
				check_tmp = false;
				continue;
			}
			if(check_tmp && action[i].size()==2 and action[i][0]==action[date][0] and action[i][1]==action[date][1]) {
				action[i]={-1,-1,-1,-1};
				check_tmp = false;
				continue;
			}
			if(action[i].size()==4 and action[i][0]==hrv[newtgt].y and action[i][1]==hrv[newtgt].x){
				action[i][0]=placePos.y;
				action[i][1]=placePos.x;
				break;
			}
		}

		// もともと動かしていたやつの辻褄合わせ
		rep(i,date+1,t){
			if(action[i].size()==4 and action[i][0]==action[date][2] and action[i][1]==action[date][3]){
				action[i][0]=action[date][0];
				action[i][1]=action[date][1];
				break;
			}
		}

		// newtgtをplacePosに移動
		// cout<<action[date][0]<<" "<<action[date][1]<<" "<<action[date][2]<<" "<<action[date][3]<<endl;
		action[date]=MoveHarvester(newtgt, placePos.y, placePos.x);
		// cout<<action[date][0]<<" "<<action[date][1]<<" "<<action[date][2]<<" "<<action[date][3]<<endl;
		return true;
	}

	inline int GetFieldValue(int y, int x) {
		int val=0;
		rep(i,n)rep(j,n)if(vegField[i][j]!=NONE){
			val+=veg[vegField[i][j]].value / (abs(i-y)+abs(j-x)+1);
		}
		return val + (vegField[y][x] == NONE ? 0 : veg[vegField[y][x]].value);
	}

	pair<int, int> AnalyseHarvest(int exceptHarvester = NONE) {
		int nearMax = 0;
		pair<int, int> nearMaxPos=NONE_COOR;
		queue<int> q;
		bool visited[n][n] = {};

		rep(i,HarvesterCount) {
			if(exceptHarvester==i)continue;
			vector<int> used;
			q.push(i);
			int cnt=0, sum=0, adjMaxvalue = -INF;
			pair<int, int> pos=NONE_COOR;
			while (!q.empty()) {
				int p = q.front(); q.pop();
				int y=hrv[p].y, x=hrv[p].x;			
				if(visited[y][x])continue;
				visited[y][x]=true;
				used.push_back(p);
				cnt++;
				sum+=GetFieldValue(y, x);
				rep(v,4){
					int ny=y+DY[v], nx=x+DX[v];
					if(ny<0 or nx<0 or ny>=n or nx>=n)continue;
					if(visited[ny][nx])continue;
					if(hrvField[ny][nx]!=NONE) q.push(hrvField[ny][nx]);
					else if(chmax(adjMaxvalue, GetFieldValue(ny, nx))) pos={ny, nx};
				}
			}
			for(auto p:used) {
				hrv[p].adjacent = cnt;
				hrv[p].valueSum = sum;
			}
			if(adjMaxvalue == -INF) continue;
			if(chmax(nearMax, (sum+adjMaxvalue) * (cnt+1))) {
				nearMaxPos = pos;
			}
		}
		return nearMaxPos;
	}

	bool ChangeAction2() {
		if(action[date][2]==NONE) return false;

		int currentTgt = hrvField[action[date][0]][action[date][1]];
		int newtgt=currentTgt;
		Harvester placePos={action[date][2],action[date][3]};

		// placePosを、いま一番獲得できる報酬が大きいものに変えてみる
		{
			auto[y,x] = AnalyseHarvest(currentTgt);
			if(y==NONE) return false;
			placePos.y = y;
			placePos.x = x;
		}
		if(placePos.y == action[date][0] and placePos.x == action[date][1] ) return false;
		if(placePos.y == action[date][2] and placePos.x == action[date][3] ) return false;

		// 今回新しく動かしたやつの辻褄合わせ
		rep(i,date+1,t){
			if(action[i][0]==action[date][2] and action[i][1]==action[date][3]){
				action[i][0]=placePos.y;
				action[i][1]=placePos.x;
				break;
			}
		}

		// newtgtをplacePosに移動
		// cout<<action[date][0]<<" "<<action[date][1]<<" "<<action[date][2]<<" "<<action[date][3]<<endl;
		action[date]=MoveHarvester(newtgt, placePos.y, placePos.x);
		// cout<<action[date][0]<<" "<<action[date][1]<<" "<<action[date][2]<<" "<<action[date][3]<<endl;
		// cout<<"===="<<endl;
		return true;
	}

	pair<bool,int> Optimize(Timer timer, int day, int mode) {
		Reset();
		while(GoodMorning()){
			if(!timer) return {false, day};
			if(date<day){
				Action();
			} else if(date==day) {
				bool ok=true;
				if(mode==0)ok = ChangeAction();
				if(mode==1)ok = ChangeAction2();
				if(!ok){
					// 行動が変わらなかったら、せっかくなので次の日をやる
					day++;
					Action();
				} else {
					phase = ACTIONED;
				}
			} else {
				if(!CheckedAction()) return {false, day};
			}
			Harvest();
			Disappear();
		}
		return {true, day};
	}
};

const int TLE = 1930;

void Main(){
	Timer timer(TLE);
	Initialize();

	Simulator sim;
	sim.CreateInitialActions(40);
	cerr<<sim.money<<endl;

	int day=1, cnt=0, mode = 0;
	while(timer){
		cnt++;
		auto tmp = sim;
		auto[success, after] = tmp.Optimize(timer, day, mode);

		if(success){
			if(tmp.money > sim.money-min(100, (int)(TLE-timer.get())/10)){
				// if(tmp.money > sim.money)
				// 	cout<<"(mode="<<mode<<") Day:"<<after<<" [count="<<cnt<<", "<<timer.get()<<"ms] "<<tmp.money<<" (+"<<tmp.money-sim.money<<") "<<endl;
				sim = tmp;
			}
		}

		day=after+1;
		if(day==t){
			day=1;
			mode=1-mode;
		}
	}
	sim.OutputAction();
	cerr<<cnt<<" / "<<timer.get()<<"ms"<<endl;
}
//   Case #: 60
//  Average: 1862959
// Expected: 93147900
//      Max: 2439469
//      Min: 1444110