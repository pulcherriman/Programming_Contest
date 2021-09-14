/*
 * Unsecured Optimization
 */
// #pragma GCC target "avx"
// #pragma GCC target "sse4.2"
// #pragma GCC optimize "O3"
// #pragma GCC optimize "fast-math"
// #pragma GCC optimize "unroll-loops"

#include<bits/stdc++.h>
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

const int dPos[]={1,-1};
const int n=16, m=5000, t=1000;
const int TLE = 1930;
const int NONE = -1;
const pair<int,int> NONE_COOR = {NONE,NONE};
int field[n][n];
int hrvField[n][n];
int HarvesterCount = 0;
int money=1;
Vegetable veg[m];
Harvester hrv[n*n];
vector<int> VegetableIndexOfStartDate[t];
vector<int> VegetableIndexOfEndDate[t];

inline bool IsBuyableHarvester() {
	return money >= (HarvesterCount+1) * (HarvesterCount+1) * (HarvesterCount+1);
}

vector<int> AddHarvester(int y, int x) {
	assert(IsBuyableHarvester());
	assert(hrvField[y][x]==NONE);
	hrv[HarvesterCount].y = y;
	hrv[HarvesterCount].x = x;
	hrvField[y][x]=HarvesterCount;
	HarvesterCount++;
	money -= HarvesterCount * HarvesterCount * HarvesterCount;
	return {y, x};
}

vector<int> MoveHarvester(int index, int y, int x) {
	assert(index < HarvesterCount);
	assert(hrvField[y][x]==NONE);
	assert(hrvField[hrv[index].y][hrv[index].x]!=NONE);
	vector<int> ret={hrv[index].y, hrv[index].x, y, x};
	hrvField[hrv[index].y][hrv[index].x]=NONE;
	hrvField[y][x]=index;
	hrv[index].y = y;
	hrv[index].x = x;
	return ret;
}

const vector<int> NOTHING(1, NONE);
inline vector<int> DoNothing() {
	return NOTHING;
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

/*
 * 現在のフィールドを収穫して、収入を得る
 */ 
int Harvest() {
	int totalEarned = 0;
	queue<int> q;
	bool visited[n][n] = {};
	rep(i,HarvesterCount) {
		auto el=hrv[i];
		if(field[el.y][el.x]==NONE)continue;
		q.push(i);
		int cnt=0, sum=0;
		while (!q.empty()) {
			int p = q.front(); q.pop();
			int y=hrv[p].y, x=hrv[p].x;			
			if(visited[y][x])continue;
			visited[y][x]=true;
			cnt++;
			if(field[y][x]!=NONE){
				sum+=veg[field[y][x]].value;
				field[y][x]=NONE;
			}
			if(y>0 and hrvField[y-1][x]!=NONE and !visited[y-1][x]) q.push(hrvField[y-1][x]);
			if(x>0 and hrvField[y][x-1]!=NONE and !visited[y][x-1]) q.push(hrvField[y][x-1]);
			if(y<n-1 and hrvField[y+1][x]!=NONE and !visited[y+1][x]) q.push(hrvField[y+1][x]);
			if(x<n-1 and hrvField[y][x+1]!=NONE and !visited[y][x+1]) q.push(hrvField[y][x+1]);
		}
		totalEarned += sum * cnt;
	}
	money += totalEarned;
	return totalEarned;
}

/*
 * 収穫機1つで最善を目指す
 */
vector<pair<int,int>> harvesterMoveTo(t, NONE_COOR);

vector<vector<int>> Single_Optimal(int max_harvester=1) {
	vector<vector<int>> answer;
	priority_queue<pair<int,int>> pq;
	rep(date,t){
		for(auto&i:VegetableIndexOfStartDate[date]){
			pq.emplace(veg[i].value, i);
		}
		while(!pq.empty()){
			auto [value,i]=pq.top(); pq.pop();
			if(veg[i].end<date) continue;
			harvesterMoveTo[date] = {veg[i].y, veg[i].x};
			break;
		}
	}

	rep(i,t){
		UpdateField_Morning(i);
		if(IsBuyableHarvester() && HarvesterCount<max_harvester) {
			if(harvesterMoveTo[i] == NONE_COOR) {
				rep(y,n)rep(x,n)if(hrvField[y][x]==NONE){
					answer.push_back(AddHarvester(y,x));
					y=x=n;
				}
			} else {
				if(hrvField[harvesterMoveTo[i].first][harvesterMoveTo[i].second]==NONE) {
					answer.push_back(AddHarvester(harvesterMoveTo[i].first, harvesterMoveTo[i].second));
				} else {
					rep(y,n)rep(x,n)if(hrvField[y][x]==NONE){
						answer.push_back(AddHarvester(y,x));
						y=x=n;
					}
				}
			}
		} else {
			if(harvesterMoveTo[i] == NONE_COOR) {
				answer.push_back(DoNothing());
			} else {
				if(hrvField[harvesterMoveTo[i].first][harvesterMoveTo[i].second]==NONE) {
					int minValue=INF, tgt=0;
					rep(j,HarvesterCount){
						int vegIndex=field[hrv[j].y][hrv[j].x];
						int vegVal=vegIndex==NONE ? -1 : veg[vegIndex].value;
						if(chmin(minValue, vegVal))tgt=j;
					}
					answer.push_back(MoveHarvester(tgt, harvesterMoveTo[i].first, harvesterMoveTo[i].second));
				} else {
					answer.push_back(DoNothing());
				}
			}
		}
		Harvest();
		UpdateField_Night(i);
	}
	return answer;
}
/*
 * ここまで
 */

void Initialize() {
	int _;
	cin>>_>>_>>_;
	rep(i,m){
		cin>>veg[i].y>>veg[i].x>>veg[i].start>>veg[i].end>>veg[i].value;
		VegetableIndexOfStartDate[veg[i].start].push_back(i);
		VegetableIndexOfEndDate[veg[i].end].push_back(i);
	}
}

void Reset() {
	rep(i,n)rep(j,n){
		field[i][j]=NONE;
		hrvField[i][j]=NONE;
	}
	HarvesterCount = 0;
	money=1;
	rep(i,n*n)hrv[i]=Harvester();
}

/*
 * 操作列を受け取って、[start, end)の間の日付をシミュレートする
 * start!=0の時は、filedなどの情報がそのまま残っていることを期待する
 */
bool Calculate(vector<vector<int>>&ans, int start=0, int end=t) {
	if(start==0) Reset();
	rep(i,start,end){
		UpdateField_Morning(i);
		switch(ans[i].size()) {
			case 1:
				break;
			case 2:
				if(!IsBuyableHarvester()) return false;
				if(hrvField[ans[i][0]][ans[i][1]]!=NONE) return false;
				AddHarvester(ans[i][0], ans[i][1]);
				break;
			case 4:
				if(hrvField[ans[i][2]][ans[i][3]]!=NONE) return false;
				if(hrvField[ans[i][0]][ans[i][1]]==NONE) return false;
				if(hrv[hrvField[ans[i][0]][ans[i][1]]].y != ans[i][0]) return false;
				if(hrv[hrvField[ans[i][0]][ans[i][1]]].x != ans[i][1]) return false;
				MoveHarvester(hrvField[ans[i][0]][ans[i][1]], ans[i][2], ans[i][3]);
				break;
		}
		Harvest();
		UpdateField_Night(i);
	}
	return true;
}

void Main(){
	Timer timer(TLE);
	Initialize();

	int maxMoney=0;
	vector<vector<int>> ans;
	rep(hrvCnt,1,100){
		Reset();
		auto ctrl=Single_Optimal(hrvCnt);
		if(chmax(maxMoney, money) or hrvCnt<=21) {
			maxMoney=money;
			ans=ctrl;
		}
		if(HarvesterCount < hrvCnt) break;
	}

	int succeeded=0, failed=0;
	while(timer){
		vector<vector<int>> ans2=ans;
		int tgt=Random(0,t);;
		while(ans2[tgt].size()!=4)tgt=Random(0,t);

		Calculate(ans2, 0, tgt);
		UpdateField_Morning(tgt);
		// 移動操作を焼いてみる
		// 一番効果の薄い収穫機を、一番効果の高い収穫機の隣においてみる
		int newtgt=0;
		vector<int> maxUsed, maxSizeUsed;
		{
			int minValue=INF, maxValue=0;
			int adjacentCnt[HarvesterCount]={};
			queue<int> q;
			bool visited[n][n] = {};
			rep(i,HarvesterCount) {
				auto el=hrv[i];
				vector<int> used;
				if(field[el.y][el.x]==NONE)continue;
				q.push(i);
				int cnt=0, sum=0;
				while (!q.empty()) {
					int p = q.front(); q.pop();
					int y=hrv[p].y, x=hrv[p].x;			
					if(visited[y][x])continue;
					visited[y][x]=true;
					used.push_back(p);
					cnt++;
					if(field[y][x]!=NONE){
						sum+=veg[field[y][x]].value;
						field[y][x]=NONE;
					}
					if(y>0 and hrvField[y-1][x]!=NONE and !visited[y-1][x]) q.push(hrvField[y-1][x]);
					if(x>0 and hrvField[y][x-1]!=NONE and !visited[y][x-1]) q.push(hrvField[y][x-1]);
					if(y<n-1 and hrvField[y+1][x]!=NONE and !visited[y+1][x]) q.push(hrvField[y+1][x]);
					if(x<n-1 and hrvField[y][x+1]!=NONE and !visited[y][x+1]) q.push(hrvField[y][x+1]);
				}

				sum*=cnt;
				for(auto&p:used)adjacentCnt[p]=sum;
				
				if(used.size()>0){
					if(chmin(minValue, sum))newtgt=used[Random(0,used.size())];
					if(chmax(maxValue, sum))maxUsed=used;
					if(maxSizeUsed.size()<used.size())maxSizeUsed=used;
				}
			}
		}
		
		Harvester placePos={ans2[tgt][2],ans2[tgt][3]};
		if(maxUsed.size()==0){
			int maxValue=-INF;
			if(maxSizeUsed.size()!=0){
				for(auto&p:maxSizeUsed){
					for(int dy:dPos)for(int dx:dPos){
						int y=hrv[p].y+dy, x=hrv[p].x+dx;
						if(y<0 or x<0 or y==n or x==n)continue;
						int vegValue=field[y][x]==NONE ? -1 : veg[field[y][x]].value;
						if(hrvField[y][x]==NONE and chmax(maxValue, vegValue)){
							placePos.y=y; placePos.x=x;
						}
					}
				}
			} else {
				// このパターン（多い）の時は処理を変える
				// tgt列の移動先を変更するのではなく、移動元を適切なものに変更する
				int maxValue=-INF;
				rep(i,HarvesterCount){
					int d=abs(ans2[tgt][2]-hrv[i].y)+abs(ans2[tgt][3]-hrv[i].x);
					if(chmax(maxValue, d))newtgt=i;
				}
				if(newtgt == hrvField[ans2[tgt][0]][ans2[tgt][1]]) {
					continue;
				}
			}
		} else {
			int maxValue=-INF;
			for(auto&p:maxUsed){
				for(int dy:dPos)for(int dx:dPos){
					int y=hrv[p].y+dy, x=hrv[p].x+dx;
					if(y<0 or x<0 or y==n or x==n)continue;
					int vegValue=field[y][x]==NONE ? -1 : veg[field[y][x]].value;
					if(hrvField[y][x]==NONE and chmax(maxValue, vegValue)){
						placePos.y=y; placePos.x=x;
					}
				}
			}
		}

		// 同じ操作ならやらない
		// TODO

		// 今回新しく動かしたやつの辻褄合わせ
		bool check_tmp=true;
		rep(i,tgt+1,t){
			if(check_tmp && ans[i].size()==4 and ans[i][2]==ans[tgt][0] and ans[i][3]==ans[tgt][1]) {
				ans2[i]=NOTHING;
				check_tmp = false;
				continue;
			}
			if(check_tmp && ans[i].size()==2 and ans[i][0]==ans[tgt][0] and ans[i][1]==ans[tgt][1]) {
				ans2[i]=NOTHING;
				check_tmp = false;
				continue;
			}
			if(ans[i].size()==4 and ans[i][0]==hrv[newtgt].y and ans[i][1]==hrv[newtgt].x){
				ans2[i][0]=placePos.y;
				ans2[i][1]=placePos.x;
				break;
			}
		}

		// もともと動かしていたやつの辻褄合わせ
		rep(i,tgt+1,t){
			if(ans[i].size()==4 and ans[i][0]==ans[tgt][2] and ans[i][1]==ans[tgt][3]){
				ans2[i][0]=ans2[tgt][0];
				ans2[i][1]=ans2[tgt][1];
				break;
			}
		}

		// newtgtをplacePosに移動
		ans2[tgt]=MoveHarvester(newtgt, placePos.y, placePos.x);

		Harvest();
		UpdateField_Night(tgt);
		bool finished = Calculate(ans2, tgt+1);
		if(finished && maxMoney-(1500-(int)timer.get()) < money){
			// cout<<"Changed"<<endl;
			// cout<<maxMoney<<" -> "<<money<<endl;
			ans=ans2;
			maxMoney=money;
			succeeded++;
		} else failed++;
	}

	
	// FIXME: なぜか1桁が-1にならない
	rep(i,t){
		if(ans[i].size()==1)ans[i][0]=NONE;
	}

	// OUTPUT
	rep(i,t){
		cout<<ans[i][0];
		rep(j,1,ans[i].size())cout<<" "<<ans[i][j];
		cout<<endl;
	}
	cerr<<succeeded+failed<<" ("<<succeeded<<" / "<<failed<<")"<<endl;
}
// 21
//   Case #: 30
//  Average: 247008
// Expected: 12350423
//      Max: 346947
//      Min: 178254

//18
//   Case #: 30
//  Average: 248614
// Expected: 12430708
//      Max: 336891
//      Min: 177963

// auto
//   Case #: 30
//  Average: 225529
// Expected: 11276475
//      Max: 325776
//      Min: 182570