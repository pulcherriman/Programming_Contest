/*
 * Unsecured Optimization
 */
#pragma GCC optimize "O3" /* 最適化 */
#pragma GCC target "avx" /* SIMD(ベクトル化) */
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native") /* 浮動小数点数のSIMD */
// #pragma GCC optimize "fast-math"
// #pragma GCC optimize "unroll-loops" /* ループの展開 */

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
using ull=unsigned long long;
using ld=long double;
using vb=vector<bool>;
using vvb=vector<vb>;
using vd=vector<ld>;
using vvd=vector<vd>;
using vi=vector<int>;
using vvi=vector<vi>;
using pii=pair<int,int>;
using pll=pair<ll,ll>;
using vp=vector<pll>;
using tl2=tuple<ll,ll>;
using tl3=tuple<ll,ll,ll>;
using vs=vector<string>;
template<class K> using IndexedSet=__gnu_pbds::tree<K,__gnu_pbds::null_type,less<K>,__gnu_pbds::rb_tree_tag,__gnu_pbds::tree_order_statistics_node_update>;
template<class K> using HashSet=__gnu_pbds::gp_hash_table<K,__gnu_pbds::null_type>;
template<class K,class V> using IndexedMap=__gnu_pbds::tree<K,V,less<K>,__gnu_pbds::rb_tree_tag,__gnu_pbds::tree_order_statistics_node_update>;
template<class K,class V> using HashMap=__gnu_pbds::gp_hash_table<K,V>;

constexpr int INF=1<<30;


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

/*
 * Utilities
 */
template<class T>constexpr bool chmax(T&a,T b){return a<b?a=b,1:0;}
template<class T>constexpr bool chmin(T&a,T b){return a>b?a=b,1:0;}
template<class S>S sum(vector<S>&a){return accumulate(all(a),S());}
template<class S>S max(vector<S>&a){return *max_element(all(a));}
template<class S>S min(vector<S>&a){return *min_element(all(a));}

// 乱数
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
} Random(1);


// タイマー
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

const int TLE=3000;
Timer timer(TLE);


// ステージ情報

enum DIRECTION {
	UP,
	DOWN,
	LEFT,
	RIGHT,
	NOTHING,
};
DIRECTION Directions[] = {
	UP,
	DOWN,
	LEFT,
	RIGHT,
};

constexpr inline DIRECTION Inverse(const DIRECTION&d){
	switch (d) {
		case UP: return DOWN;
		case DOWN: return UP;
		case LEFT: return RIGHT;
		case RIGHT: return LEFT;
		default: return NOTHING;
	}
}


const int SIZE = 30;

struct Point {
	int y, x;
	Point(): y(0), x(0) {}
	Point(int X, int Y) : y(Y), x(X) {}
	void MoveUp() { y--; }
	void MoveDown() { y++; }
	void MoveLeft() { x--; }
	void MoveRight() { x++; }

	int Hash() {
		return y * (SIZE+2) + x;
	}

	int Distance(Point o) {
		return abs(x - o.x) + abs(y - o.y);
	}

	Point GetDir(DIRECTION dir) {
		switch (dir) {
		case UP:
			return Up();
		case DOWN:
			return Down();
		case LEFT:
			return Left();
		case RIGHT:
			return Right();
		default:
			return *this;
		}
	}

	Point Up() { return Point(x, y - 1); }
	Point Down() { return Point(x, y + 1); }
	Point Left() { return Point(x - 1, y); }
	Point Right() { return Point(x + 1, y); }

	bool Is(Point p) {
		return x == p.x && y == p.y;
	}

	auto operator<(const Point&p)const{
		return y < p.y || (y == p.y && x < p.x);
	}

	auto operator==(const Point&p)const{
		return y == p.y && x == p.x;
	}
};

template <>
struct std::tr1::hash<Point> {
	size_t operator()(Point x) const throw() {
		return x.Hash();
	}
};

struct Stage {
	array<int, SIZE+2> stage;
	
	Stage() {
		stage.fill(0);
		stage[0]=~0;
		rep(i,SIZE)stage[i+1]=(1<<31)+1;
		stage[SIZE+1]=~0;
	}

	void Set(Point p, bool value, bool fillAdjacent = false) {
		const int d = SIZE + 1 - p.x;
		if (value) {
			stage[p.y] |= 1 << d;
			if (fillAdjacent) {
				stage[p.y]   |= 1 << (d-1);
				stage[p.y]   |= 1 << (d+1);
				stage[p.y-1] |= 1 << (d);
				stage[p.y+1] |= 1 << (d);
			}
		} else {
			stage[p.y] &= ~(1 << d);
			if (fillAdjacent) {
				if(p.x < 30) stage[p.y]   &= ~(1 << (d-1));
				if(p.x >  1) stage[p.y]   &= ~(1 << (d+1));
				if(p.y >  1) stage[p.y-1] &= ~(1 << (d));
				if(p.y < 30) stage[p.y+1] &= ~(1 << (d));
			}
		}
	}

	void Print(){
		rep(i, SIZE+2){
			cout<<"# "<<bitset<32>(stage[i]).to_string()<<endl;
		}
	}

	bool Get(Point p){
		return stage[p.y] & (1 << (SIZE + 1 - p.x));
	}

	bool Get(Point&p, DIRECTION dir) {
		return Get(p.GetDir(dir));
	}

	void Any(Stage&o){
		rep(i,SIZE+2) stage[i] |= o.stage[i];
	}

	int CountAdjacent(Point p){
		int wallCount=0;
		wallCount += Get(p, UP) ? 1 : 0;
		wallCount += Get(p, DOWN) ? 1 : 0;
		wallCount += Get(p, LEFT) ? 1 : 0;
		wallCount += Get(p, RIGHT) ? 1 : 0;
		return wallCount;
	}
};



struct Pet : public Point {
	int id, type;
	bool isIsolated = false;
	Pet(int ID, int X, int Y, int TYPE) :Point(X, Y), id(ID), type(TYPE) {}

	void Action(char act) {
		switch (act) {
		case '.':
			return;
		case 'U':
			y--;
			return;
		case 'D':
			y++;
			return;
		case 'L':
			x--;
			return;
		case 'R':
			x++;
			return;
		default:
			assert(false);
		}
	}
};

struct Human : public Point {
	int id; 
	Stage walk;
	int nothingCount= 0;
	int role = -1;
	queue<Point> targets;
	Human(int ID, int X, int Y) : Point(X, Y), id(ID) {
		walk.Set(*this, 1);
	}

	char DoNothing() {
		nothingCount++;
		return '.';
	}

	char Move(DIRECTION dir) {
		nothingCount=0;
		if (dir == UP) --y;
		if (dir == DOWN) ++y;
		if (dir == LEFT) --x;
		if (dir == RIGHT) ++x;
		walk.Set(*this, 1);
		return "UDLR."[(int)dir];
	}

	char PlaceWall(DIRECTION dir) {
		nothingCount=0;
		return "udlr."[(int)dir];
	}

	// 自分から見て指定された座標がある方向
	DIRECTION MoveToDirection(Point p) {
		if (p.x == x && p.y == y) return NOTHING;
		if (p.x > x) return RIGHT;
		if (p.x < x) return LEFT;
		if (p.y > y) return DOWN;
		return UP;
	}
};

struct Logic {
	Logic() {
		RecalculatePlaceableWallMap();
	}

	/** @brief 10~20 */
	int petCount;

	/** @brief 5~10 */
	int humanCount;

	vector<Pet> pets;
	vector<Human> humans;

	Stage wall;
	Stage notPlaceable;

	void RecalculatePlaceableWallMap() {
		notPlaceable = wall;

		for(auto&human:humans){
			notPlaceable.Set(human, 1);
		}
		for(auto&pet:pets){
			notPlaceable.Set(pet, 1, true);
		}
	}

	bool IsPlaceable(Point p, DIRECTION dir = NOTHING) {
		return !notPlaceable.Get(p, dir);
	}

	bool IsExistWall(Point p, DIRECTION dir = NOTHING){
		return wall.Get(p, dir);
	}

	bool IsMovable(Point p, DIRECTION dir = NOTHING) {
		// cout<<"# ismovable : "<<p.y <<" "<<p.x<<" "<<dir<<"=" << !IsExistWall(p,dir)<<endl;
		return !IsExistWall(p,dir);
	}

	// humanに壁を置かせる
	char PlaceWall(Human&human, DIRECTION dir) {
		wall.Set(human.GetDir(dir), 1);
		notPlaceable.Set(human.GetDir(dir), 1);
		return human.PlaceWall(dir);
	}

	// humanを指定の方向に移動させる
	char Move(Human&human, DIRECTION dir) {
		notPlaceable.Set(human.GetDir(dir), 1);
		return human.Move(dir);
	}

	// humanを指定の位置に移動させる
	char MoveTo(Human&human, Point p) 
	{
		return Move(human, NearestMoveToDirection(human, p));
	}

	// humanが指定の位置に壁を置けるか
	bool IsPlaceable(Human&human, Point p) {
		return human.Distance(p) == 1 and IsPlaceable(p);
	}

	// humanに、指定の位置に壁を置かせる
	char PlaceTo(Human&human, Point p) {
		if(human.Distance(p) == 1){
			// 置こうとする
			if(IsPlaceable(p)){
				return PlaceWall(human, human.MoveToDirection(p));
			}
			return human.DoNothing();
		} else {
			// 移動
			return MoveTo(human, p);
		}
	}

	// humanにとって、指定した位置の集合で一番近い位置
	Point PointMultipleTo(Human&human, HashSet<Point> points){
		auto dist = BFS(human);

		int minDist = INF;
		Point minPoint(0,0);
		for(auto&p:points){
			if (chmin(minDist, dist[p.y][p.x])){
				minPoint = p;
			}
		}

		return minPoint;
	}

	// 始点から終点までの最短経路を通るためにどちらの方向に進むべきか
	DIRECTION NearestMoveToDirection(Point s, Point t) {
		if(IsExistWall(s) or IsExistWall(t)){
			return NOTHING;
		}
		static array<bool, 1000> visited;
		visited.fill(false);
		visited[t.Hash()] = true;

		queue<pair<Point, DIRECTION>> q;
		q.emplace(t, NOTHING);

		while(!q.empty()){
			auto [p, d]=q.front();
			if(p.Is(s)) {
				return Inverse(d);
			}
			q.pop();
			for(auto&dir:Directions){
				if(visited[p.GetDir(dir).Hash()]) continue;
				visited[p.GetDir(dir).Hash()] = true;

				if(IsMovable(p, dir)) {
					q.emplace(p.GetDir(dir), dir);
				}
			}
		}
		return NOTHING;
	}

	Point NearestMoveToDirection(Point s, Stage&targets) {
		vvi dist(SIZE+2, vi(SIZE+2, -1));
		dist[s.y][s.x] = 0;

		queue<pair<Point, int>> q;
		q.emplace(s, 0);

		while(!q.empty()){
			auto [p, d]=q.front();
			if(targets.Get(p)) {
				return p;
			}
			q.pop();
			for(auto&dir:Directions){
				auto np = p.GetDir(dir);
				if(dist[np.y][np.x] != -1) continue;
				if(IsMovable(p, dir)) {
					dist[np.y][np.x] = dist[p.y][p.x] + 1;
					q.emplace(p.GetDir(dir), dir);
				}
			}
		}
		return Point(0, 0);
	}

	vvi BFS(Point s) {
		vvi dist(SIZE+2, vi(SIZE+2, INF));
		dist[s.y][s.x] = 0;

		queue<pair<Point, int>> q;
		q.emplace(s, 0);

		while(!q.empty()){
			auto [p, d]=q.front();
			q.pop();
			for(auto&dir:Directions){
				auto np = p.GetDir(dir);
				if(dist[np.y][np.x] != INF) continue;
				if(IsMovable(p, dir)) {
					dist[np.y][np.x] = dist[p.y][p.x] + 1;
					q.emplace(p.GetDir(dir), dir);
				}
			}
		}
		return dist;
	}

	void PetsAction() {
		string s;
		rep(i, petCount){
			cin>>s;
			for(auto&c:s) pets[i].Action(c);
		}
		RecalculatePlaceableWallMap();
	}
};


struct Solver : public Logic {
	int turn = 0;

	void Input() {
		int x,y,t;

		cin>>petCount;
		rep(i,petCount){
			cin>>y>>x>>t;
			pets.emplace_back(i,x,y,t);
		}

		cin>>humanCount;
		rep(i,humanCount){
			cin>>y>>x;
			humans.emplace_back(i,x,y);
		}
	}

	int GetAreaId(Point p) {
		if(GetLineId(p) != -1) return -1;

		int level = (p.y + p.x) / 3 - 2;
		if(level < 0 or level >= 17) return -1;
		if(p.x - p.y >= 3) {
			return level + 18;
		} else if(p.x - p.y <= -2){
			return level;
		}
		return -1;
	}

	int GetAreaLevel(Point p){
		int areaId = GetAreaId(p);
		if(areaId == -1) return -1;
		if(areaId<=7){
			return (areaId + 2) * 3 + p.x - p.y;
		}
		if(areaId<=17){
			return (18 - areaId) * 3 + p.x - p.y - 1;
		}
		if(areaId<=25){
			return (areaId - 16) * 3 + p.y - p.x;
		}
		return (36 - areaId) * 3 + p.y - p.x - 1;
	}

	int GetLineId(Point p){
		if(p.x-p.y == 0) return -1;
		if(p.x-p.y == 1) return -1;

		int s = (p.y + p.x);
		if(s%3!=0)return -1;
		if(s==3)return -1;
		if(s==60)return -1;
		int level = s / 3 - 2;
		if(p.x > p.y) level += 18;
		return level;
	}

	int status=0;
	vi lineLevel;

	// 指定された座標は封鎖可能か？
	bool IsIsolatable(Point p) {
		int areaLevel = GetAreaLevel(p);
		if(areaLevel == -1) return false;
		int areaId = GetAreaId(p);

		int reqLv1 = INF, reqLv2 = INF;
		if(areaId <= 7) {
			reqLv1 = (areaLevel + 1) / 2;
			reqLv2 = areaLevel / 2 + 2;
		} else if (areaId <= 17) {
			reqLv1 = areaLevel / 2 + 2;
			reqLv2 = (areaLevel + 1) / 2;
		} else if(areaId <= 25) {
			reqLv1 = (areaLevel + 1) / 2;
			reqLv2 = areaLevel / 2 + 2;
		} else {
			reqLv1 = areaLevel / 2 + 2;
			reqLv2 = (areaLevel + 1) / 2;
		}
		return lineLevel[areaId] >= reqLv1 and lineLevel[areaId+1] >= reqLv2;
	}

	HashSet<Point> targets;
	string HumansAction() {
		cout<<"# status : "<<status<<endl;
		// 人の行動を決定する
		string humanAction = "";

		{
			if(lineLevel.empty()){
				lineLevel.resize(36,0);
			}

			if(status == 0){
				status = 1;

				rep(i,1,SIZE+1)rep(j,1,SIZE+1){
					if(GetAreaId(Point(j,i))%2 != 0)continue;
					if(GetAreaLevel(Point(j,i)) != 0)continue;
					targets.insert(Point(j,i));
				}
				for(auto&human:humans){
					Point target(1,1);
					int minDist = INF;
					for(auto&p:targets){
						if(chmin(minDist, human.Distance(p))){
							target = p;
						}
					}

					targets.erase(target);
					human.role = 0;
					human.targets.push(target);
				}
			}

			// エリアごとに、レベルいくつの地点までペットが存在するか？
			vi petLvByArea(35, INF);
			HashMap<int, Point> petByArea;
			{
				for(auto&pet:pets){
					if(pet.isIsolated) continue;
					if(!IsIsolatable(pet)) continue;
					if(chmin(petLvByArea[GetAreaId(pet)], GetAreaLevel(pet))){
						petByArea[GetAreaId(pet)] = pet;
					}
				}
			}

			// 各人がターゲットに突撃
			for(auto&human:humans){
				if(turn ==183 and human.id==4){
					cout<<"# yaba"<<endl;
					cout<<"# STAT"<<human.role<<endl;;
				}

				// もしペットを隔離できる状態ならやる
				{
					// HOTFIX: 76手目、2人目が空を塞いでる
					// TODO: ゆるい
					int areaId = GetAreaId(human);
					int areaLevel = GetAreaLevel(human);
					if(areaId == -1) goto Label_SkipIsolate;
					if(turn == 76 and human.id == 1){
						cout<<"# DEBUG: "<< areaId<<endl;
						cout<<"# DEBUG: "<< areaLevel<<endl;
						cout<<"# DEBUG: "<< areaLevel<<endl;
						
					}
					if(petLvByArea[areaId] != INF and petLvByArea[areaId] + 3 <= areaLevel) {
						for(auto&other:humans){
							if(areaId != GetAreaId(other)) continue;
							if(areaLevel <= GetAreaLevel(other)) continue;
							goto Label_SkipIsolate;
						}
						Point wallPoint = human;
						Point isolatePoint = human;
						if(areaId <= 17){
							if(IsExistWall(wallPoint.Left())){
								wallPoint.MoveDown();
							}else wallPoint.MoveLeft();
							isolatePoint.MoveDown();
							isolatePoint.MoveLeft();
						} else {
							if(IsExistWall(wallPoint.Right())){
								wallPoint.MoveUp();
							}else wallPoint.MoveRight();
							isolatePoint.MoveUp();
							isolatePoint.MoveRight();
						}

						if(IsPlaceable(human, wallPoint) and IsIsolatable(isolatePoint)){
							humanAction += PlaceTo(human, wallPoint);
							for(auto&pet:pets){
								if(GetAreaId(pet) == areaId and GetAreaLevel(pet) + 3<= areaLevel){
									pet.isIsolated = true;
								}
							}
							continue;
						}
					}
				}
				Label_SkipIsolate:;

				// ターゲットがいない場合設定する
				if(human.role == -1){
					if(targets.empty()){
						human.role = 10;
					} else {
						auto target = PointMultipleTo(human, targets);
						targets.erase(target);
						human.role = 0;
						human.targets.push(target);
					}
				}

				// 置き始めの場所に向かう
				if(human.role == 0) {
					auto target = human.targets.front();
					if(!human.Is(target)){
						// 何らかの理由で行けなくなっている
						if(NearestMoveToDirection(human, target) == NOTHING){
							human.targets.pop();
							human.role = -1;
							goto Label_SkipIsolate;
						}

						humanAction += MoveTo(human, target);
						continue;
					}
					human.targets.pop();

					human.role = 1;
					if(GetAreaId(target) <= 7){
						human.targets.push(target.Down());
						human.targets.push(target.Up().Up());
					} else if(GetAreaId(target) == 8){
						human.targets.push(target.Up());
						human.targets.push(target.Right().Right());
					} else if(GetAreaId(target) <= 17){
						human.targets.push(target.Left());
						human.targets.push(target.Right().Right());
					} else if(GetAreaId(target) <= 25){
						human.targets.push(target.Right());
						human.targets.push(target.Left().Left());
					} else if(GetAreaId(target) == 26){
						human.targets.push(target.Left());
						human.targets.push(target.Down().Down());
					} else {
						human.targets.push(target.Up());
						human.targets.push(target.Down().Down());
					}
				}

				if(human.role == 1){
					auto target = human.targets.front();
					// 置けるかな
					if (IsPlaceable(human, target)) {
						// 置ける
						human.targets.pop();
						humanAction += PlaceTo(human, target);

						lineLevel[GetLineId(target)]++;

						if(target.x - target.y >= 4) {
							human.targets.emplace(target.x-1, target.y+1);
						} else if(target.x - target.y <= -3) {
							human.targets.emplace(target.x+1, target.y-1);
						}
						cout<<"# Placed : "<<human.id<<" * "<<human.targets.size()<<endl;

						if(human.targets.empty()){
							human.role = -1;
						}
					} else {
						// 置けない
						humanAction += PlaceTo(human, target);
					}
					continue;
				}

				if(human.role == 3){
					auto action = NearestMoveToDirection(human, human.targets.front());
					if(action == NOTHING){
						human.targets.pop();
						human.role = 10;
					} else {
						humanAction += MoveTo(human, human.targets.front());
						continue;
					}
				}


				// 何もできることがない
				if(human.role == 10) {
					// TODO: エリア内の未捕獲ペットが最も多いエリアの中で一番近いものに向かう
					HashSet<Point> notIsolated;
					rep(i, 35)if(petLvByArea[i]!=INF){
						bool ok = true;
						for(auto&human:humans) {
							if(GetAreaId(human.targets.front()) == i) {
								ok = false;
								break;
							}
						}

						if(ok) notIsolated.insert(petByArea[i]);
					}

					if(notIsolated.empty()){
						human.role = 100;
						goto Label_FinalOptimize;
					}

					auto bfs = BFS(human);
					int minDist = INF;
					Point minPoint(0,0);
					for(auto&p:notIsolated){
						if(chmin(minDist, bfs[p.y][p.x])){
							minPoint = p;
						}
					}

					if(minDist == INF){
						human.role = 100;
						goto Label_FinalOptimize;
					}

					human.role = 3;
					human.targets.push(minPoint);
					cout<<"# reboot " << human.id <<" : "<<minPoint.y<<" "<<minPoint.x<<endl;
					goto Label_SkipIsolate;
				}

				Label_FinalOptimize:;
				int currentScore = CalculateScore();

				if(human.role == 100){
					int p101=0;
					rep(i, human.id){
						if(humans[i].role == 100){
							p101++;
						}
					}

					auto bfs = BFS(human);
					vector<pair<int, Point>> wallScore;
					rep(i,2,SIZE)rep(j,2,SIZE)if(bfs[i][j]!=INF){
						if(abs(i-j)>4)continue;
						auto point = Point(j,i);
						// if(human.Distance(point) >= 299-turn) continue;

						wall.Set(point, 1);
						if(auto[_,d,__]=AreaPetCount(human); d.size()!=humanCount){
							wall.Set(point, 0);
							continue;
						}

						int placedScore = CalculateScore();
						wall.Set(point, 0);
						if(currentScore >= placedScore) continue;
						wallScore.emplace_back(CalculateScore(), Point(j,i));

					}

					if(wallScore.size() <= 0){
						humanAction += human.DoNothing();
						continue;
					}

					sort(rall(wallScore));

					while(!human.targets.empty())human.targets.pop();
					human.targets.push(wallScore[0].second);
				}

				auto target = human.targets.front();
				if(human.Distance(target) == 1 and IsPlaceable(target)){
					human.targets.pop();
				}
				humanAction += PlaceTo(human, target);
				continue;
			}
			cout<<"# Lines: ";
			rep(i,36)cout<<lineLevel[i]<<" ";
			cout<<endl;
			return humanAction;
		}
	}

	void Turn() {
		turn++;
		cout<<"# ### Turn " << turn << "START"<<endl;
		auto action = HumansAction();
		cout<<action<<endl;
		PetsAction();
	}

	void Simulate() {
		rep(300){
			Turn();
			#ifdef _DEBUG
			CalculateScore(false);
			#endif
		}
	}

	int CalculateScore(bool silent = true) {
		vd scores(humanCount, 0);
		if(!silent)wall.Print();

		rep(i,humanCount)if(scores[i]==0){
			auto[area, containHumans, containPets] = AreaPetCount(humans[i]);
			for(auto&humanId : containHumans) {
				scores[humanId] = area / 900.0 / (1 << containPets.size());
				#ifdef _DEBUG
				if(!silent)cout<<"# "<<humanId<<" "<<area<<" "<<containPets.size()<<" = "<<(int)round(1e8 * scores[humanId] / humanCount)<<endl;
				if(!silent)cout<<"#   "<<humans[humanId].role<<" : "<<humans[humanId].targets.front().y<<","<<humans[humanId].targets.front().x<<endl;
				#endif
			}
		}

		#ifdef _DEBUG
		// rep(i,humanCount){
		// 	cout<<"# "<<i<<" "<<scores[i]<<endl;
		// }
		if(!silent)cout<<"# "<<"total: "<<(int)round(1e8 * sum(scores) / humanCount)<<endl;
		if(!silent)cout<<"# "<<timer.get()<<"ms"<<endl;
		#endif

		return round(1e8 * sum(scores) / humanCount);
	}

	// 特定の座標に連結する領域の面積と、ヒトとペットの情報
	tuple<int, vi, vi> AreaPetCount(Point p_init){
		int area = 0;
		vi containHumans, containPets;

		queue<Point> q;
		q.push(p_init);
		HashSet<int> hs;
		while(!q.empty()){
			auto p=q.front();
			q.pop();
			if(hs.find(p.Hash())!=hs.end()) continue;
			hs.insert(p.Hash());
			if (wall.Get(p)) continue;
			area++;
			for(auto&dir:Directions){
				q.push(p.GetDir(dir));
			}
		}

		rep(i, humanCount){
			if(hs.find(humans[i].Hash())!=hs.end()) containHumans.push_back(i);
		}
		rep(i, petCount){
			if(hs.find(pets[i].Hash())!=hs.end()) containPets.push_back(i);
		}
		return {area, containHumans, containPets};
	}

	// ここに置くとペットを隔離できる！という座標
	Stage IsoratePetPoints(){
		Stage result;

		return result;
	}
};

// ./tester.exe ../../../a.exe < ./tools/in/0001.txt > ./tools/out/0001.txt
int main(){
	Solver solver;
	solver.Input();

	// auto d = solver.NearestMoveToDirection(Point(15,15), Point(1,1));
	// cout<<d<<endl;
	solver.Simulate();
}
