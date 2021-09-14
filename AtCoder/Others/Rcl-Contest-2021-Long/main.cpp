/*
 * Unsecured Optimization
 */
// #pragma GCC target "avx"
#pragma GCC target "sse4.2"
#pragma GCC optimize "O3"
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
	int adjacent = 0;
	int valueSum = 0;
};

const int DY[]={1,-1,0,0};
const int DX[]={0,0,1,-1};
const int n=16, m=5000, t=1000;
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
	if(hrvField[y][x]!=NONE){
		assert(hrvField[y][x] == index);
		cerr<<"move position is same."<<endl;
	}
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

inline int GetFieldValue(int y, int x) {
	return field[y][x] == NONE ? 0 : veg[field[y][x]].value;
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

pair<int, int> AnalyseHarvest(int exceptHarvester = NONE, int turn=0) {
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

vi turnScore(t);
void Reset() {
	rep(i,n)rep(j,n){
		field[i][j]=NONE;
		hrvField[i][j]=NONE;
	}
	rep(i,t)turnScore[i]=NONE;
	HarvesterCount = 0;
	money=1;
	rep(i,n*n)hrv[i]=Harvester();
}


/*
 * 収穫機1つで最善を目指す
 */
vector<pair<int,int>> harvesterMoveTo(t, NONE_COOR);

vector<vector<int>> Single_Optimal(int MAX_HARVESTERS=1) {
	vector<vector<int>> action(t);
	priority_queue<tuple<int, int, int, int>> pq;

	Reset();
	vvi lastAppearDate(n, vi(n,0));
	rep(d,t){
		for(auto&i:VegetableIndexOfEndDate[d]){
			lastAppearDate[veg[i].y][veg[i].x]=d;
		}
	}

	rep(d,t){
		UpdateField_Morning(d);
			// どの座標に動かすか決定
			// 今の盤面を見て、1,2,3...手で獲得できる最善とスコアを計算する
			

			for(auto&i:VegetableIndexOfStartDate[d]){
				pq.emplace(veg[i].value, veg[i].end, veg[i].y, veg[i].x);
			}
			// j日後に出るでかい数字の上下左右を足してみる
			rep(j,1,1){
				if(d+j<t) {
					for(auto&i:VegetableIndexOfStartDate[d+j]){
						if(veg[i].value<1000)continue;
						//veg[i].y/xからマンハッタン距離でj離れている点
						rep(y,n)rep(x,n){
							if(abs(y-veg[i].y)+abs(x-veg[i].x)==j){
								int center=abs(8-y)+abs(8-x);
								pq.emplace(veg[i].value-center, (veg[i].end-j), y, x);
							}
						}
					}
				}
			}

			while(!pq.empty()){
				auto [value,end,y,x]=pq.top(); pq.pop();
				if(end<d) continue;
				if(hrvField[y][x]!=NONE) continue;
				harvesterMoveTo[d] = {y, x};
				// cout<<value<<","<<y<<","<<x<<endl;
				break;
			}

			// 処理の決定
			if(IsBuyableHarvester() && HarvesterCount<MAX_HARVESTERS) {
				if(harvesterMoveTo[d] == NONE_COOR) {
					rep(y,n)rep(x,n)if(hrvField[y][x]==NONE){
						action[d] = AddHarvester(y,x);
						y=x=n;
					}
				} else {
					if(hrvField[harvesterMoveTo[d].first][harvesterMoveTo[d].second]==NONE) {
						action[d] = AddHarvester(harvesterMoveTo[d].first, harvesterMoveTo[d].second);
					} else {
						rep(y,n)rep(x,n)if(hrvField[y][x]==NONE){
							action[d] = AddHarvester(y,x);
							y=x=n;
						}
					}
				}
			} else {
				if(harvesterMoveTo[d] == NONE_COOR) {
					action[d] = DoNothing();
				} else {
					if(hrvField[harvesterMoveTo[d].first][harvesterMoveTo[d].second]==NONE) {
						int tgt = 0;
						// 動かしてもよさそうな収穫機を選ぶ
						queue<int> q;
						int visited[n][n] = {};
						int adjacent[n][n] = {};
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
									if(hrvField[ny][nx]==NONE) continue;
									adjacent[y][x]++;
									if(visited[ny][nx]) continue;
									q.push(hrvField[ny][nx]);
								}
								if(field[y][x]!=NONE) adjacent[y][x]=0;
							}
							for(auto&p:used)visited[hrv[p].y][hrv[p].x]=used.size();
						}

						int minValue=INF;
						rep(j,HarvesterCount){
							if(minValue > visited[hrv[j].y][hrv[j].x]) {
								tgt=j;
								minValue = visited[hrv[j].y][hrv[j].x];
							} else if(minValue == visited[hrv[j].y][hrv[j].x]) {
								if(adjacent[hrv[j].y][hrv[j].x]==4 && lastAppearDate[hrv[j].y][hrv[j].x]<d){
									tgt=j;
								}
							}
						}
						// rep(j,HarvesterCount){
						// 	if(chmin(minValue, visited[hrv[j].y][hrv[j].x]))tgt=j;
						// }

						action[d] = MoveHarvester(tgt, harvesterMoveTo[d].first, harvesterMoveTo[d].second);
					} else {
						action[d] = DoNothing();
					}
				}
			}
		Harvest();
		UpdateField_Night(d);
	}
	return action;
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
		turnScore[i]=Harvest();
		UpdateField_Night(i);
	}
	return true;
}

const vector<vector<int>> EMPTY_ANS;

// 移動元を変えてみる
bool Neighbor1(int tgt, vector<vector<int>>&ans, int threshold) {
	if(ans[tgt].size()!=4) return false;
	vector<vector<int>> ans2=ans;
	Calculate(ans2, 0, tgt);
	UpdateField_Morning(tgt);
	int currentTgt = hrvField[ans2[tgt][0]][ans2[tgt][1]];
	int newtgt=currentTgt;
	{
		int maxValue=-INF;
		rep(i,HarvesterCount){
			int d=abs(ans2[tgt][2]-hrv[i].y)+abs(ans2[tgt][3]-hrv[i].x);
			if(chmax(maxValue, d)) newtgt=i;
		}
		if(newtgt == currentTgt) {
			return false;
		}
	}

	// 同じ操作ならやらない
	// TODO
	Harvester placePos={ans2[tgt][2],ans2[tgt][3]};

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
	if(Calculate(ans2, tgt+1) && threshold < money) {
		ans=ans2;
		return true;
	}
	return false;
}

// 移動先を変えてみる
bool Neighbor2(int tgt, vector<vector<int>>&ans, int threshold) {
	if(ans[tgt].size()!=4) return false;
	vector<vector<int>> ans2=ans;
	Calculate(ans2, 0, tgt);
	UpdateField_Morning(tgt);

	int currentTgt = hrvField[ans2[tgt][0]][ans2[tgt][1]];
	int newtgt=currentTgt;
	Harvester placePos={ans2[tgt][2],ans2[tgt][3]};

	// placePosを、いま一番獲得できる報酬が大きいものに変えてみる
	{
		auto[y,x] = AnalyseHarvest(currentTgt, tgt);
		if(y==NONE) return false;
		placePos.y = y;
		placePos.x = x;
	}

	// 今回新しく動かしたやつの辻褄合わせ
	rep(i,tgt+1,t){
		if(ans[i].size()==4 and ans[i][0]==ans2[tgt][2] and ans[i][1]==ans2[tgt][3]){
			ans2[i][0]=placePos.y;
			ans2[i][1]=placePos.x;
			break;
		}
	}

	// newtgtをplacePosに移動
	ans2[tgt]=MoveHarvester(newtgt, placePos.y, placePos.x);

	Harvest();
	UpdateField_Night(tgt);
	bool ok=Calculate(ans2, tgt+1);
	if(ok && threshold < money) {
		ans=ans2;
		return true;
	}
	return false;
}

// NEXT: -1へのアプローチ
bool Neighbor3(int tgt, vector<vector<int>>&ans, int threshold) {
	if(ans[tgt].size()!=1)return false;
	vector<vector<int>> ans2=ans;
	int currentHrvCnt = HarvesterCount;
	Calculate(ans2, 0, tgt);
	UpdateField_Morning(tgt);

	{
		auto[y,x] = AnalyseHarvest(-1, tgt);
		if(y==NONE){
			return false;
		}

		// 収穫機追加
		if(IsBuyableHarvester() && tgt<=950){
			ans2[tgt] = AddHarvester(y, x);
			rep(i,tgt+1,t){
				if(ans[i].size()==4 and ans[i][2]==y and ans[i][3]==x) {
					ans2[i]=NOTHING;
					break;
				}
				if(ans[i].size()==2 and ans[i][0]==y and ans[i][1]==x) {
					ans2[i]=NOTHING;
					break;
				}
			}
			Harvest();
			UpdateField_Night(tgt);
			bool ok=Calculate(ans2, tgt+1);
			if(ok) ans=ans2;
			return ok;
		}
	}


	int maxScore=NONE, maxNewtgt=NONE;
	Harvester maxPlacePos = {NONE, NONE};
	rep(newtgt,currentHrvCnt){
		ans2=ans;
		Calculate(ans2, 0, tgt);
		UpdateField_Morning(tgt);
		if(newtgt>=HarvesterCount)break;
		
		auto[y,x] = AnalyseHarvest(newtgt, tgt);
		if(y==NONE)continue;
		Harvester placePos={y, x};

		// 今回新しく動かしたやつの辻褄合わせ
		bool check_tmp=true;
		rep(i,tgt+1,t){
			if(check_tmp && ans[i].size()==4 and ans[i][2]==y and ans[i][3]==x) {
				ans2[i]=NOTHING;
				check_tmp = false;
				continue;
			}
			if(check_tmp && ans[i].size()==2 and ans[i][0]==y and ans[i][1]==x) {
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

		// newtgtをplacePosに移動
		ans2[tgt]=MoveHarvester(newtgt, placePos.y, placePos.x);
		Harvest();
		UpdateField_Night(tgt);
		bool ok=Calculate(ans2, tgt+1);
		if(ok && chmax(maxScore, money)){
			maxNewtgt = newtgt;
			maxPlacePos = placePos;
		}
	}
	if(maxScore==NONE) return false;

	ans2=ans;
	Calculate(ans2, 0, tgt);
	UpdateField_Morning(tgt);
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
		if(ans[i].size()==4 and ans[i][0]==hrv[maxNewtgt].y and ans[i][1]==hrv[maxNewtgt].x){
			ans2[i][0]=maxPlacePos.y;
			ans2[i][1]=maxPlacePos.x;
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
	ans2[tgt]=MoveHarvester(maxNewtgt, maxPlacePos.y, maxPlacePos.x);
	Harvest();
	UpdateField_Night(tgt);
	bool ok=Calculate(ans2, tgt+1);
	if(ok && threshold < money) {
		ans=ans2;
		return true;
	}
	return false;
}


// 購入の前倒しなど？
void Optimize(vector<vector<int>>&ans, int threshold) {
	auto ans2=ans;
	int cnt=0;
	rep(i,500,t)if(ans2[i].size()==1){
		cnt++;
		if(cnt>=20)rep(j,3) swap(ans2[i-1-j], ans2[i-j]);
	}
	bool ok = Calculate(ans2);
	if(ok && threshold - 2000 <= money){
		// cout<<"SUCCESS"<<endl;
		ans=ans2;
	}
}

const int TLE = 1970;

void Main(){
	Timer timer(TLE);
	Initialize();

	int maxMoney=0;
	vector<vector<int>> ans;
	rep(hrvCnt,1,100){
		Reset();
		auto ctrl=Single_Optimal(hrvCnt);
		if(chmax(maxMoney, money)) {
			ans=ctrl;
		}
		if(HarvesterCount < hrvCnt) break;
	}

	int succeeded=0, failed=0, target = 0, targetBase=200;
	bool(* Neighbors[])(int, vvi&, int) = {Neighbor1, Neighbor2, Neighbor3};
	int mode = 0;
	while(timer){
		target++;
		if(target%t==0){
			mode++;
			if(mode==3){
				mode=0;
				targetBase+=200;
				chmin(targetBase, 801);
				Optimize(ans, maxMoney);
			}
			target=targetBase+1;
		}
		bool finished = Neighbors[mode](target, ans, maxMoney);
		if(finished){
			// cout<<timer.get()<<" : "<<target<<","<<mode<<" => "<<money-maxMoney<<endl;
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

	// CHECK: 後ろが-1になってたり
	// rep(i,t){
	// 	cout<<turnScore[i];
	// 	cout<<endl;
	// }
	cerr<<maxMoney<<" : "<<succeeded+failed<<" ("<<succeeded<<" / "<<failed<<")"<<endl;
}

// 519930 : 8688 (404 / 8284)
//   Case #: 50
//  Average: 1023480
// Expected: 51174000
//      Max: 1633032
//      Min: 446291
//   Case #: 450
//  Average: 1062003
// Expected: 53100100
//      Max: 1823247
//      Min: 446291