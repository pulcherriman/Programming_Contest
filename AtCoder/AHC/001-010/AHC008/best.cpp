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
constexpr double EPS=(1e-14);
constexpr ll MOD=998244353ll;
constexpr long double PI=3.14159265358979323846;

/*
 * Output Assist
 */
template<class T>struct hasItr{
	template<class U>static constexpr true_type check(class U::iterator*);
	template<class U>static constexpr false_type check(...);
	static constexpr bool v=decltype(check<T>(nullptr))::value;
};
template<>struct hasItr<string>{static constexpr bool v=false;};

template<class T>void puta(T&t,false_type,ostream&os,[[maybe_unused]]char el){os<<t;}
template<class T>void puta(T&t,true_type,ostream&os,char el){
	constexpr bool h=hasItr<typename T::value_type>::v;
	bool F=true,I;
	for(auto&i:t){
		if(!F)os<<' ';
		puta(i,bool_constant<h>(),os,el);
		F=I=h;
	}
	if(!I)os<<el;
}
template<class T>void puta(const T&t, ostream&os=cout, char el='\n'){
	puta(t,bool_constant<hasItr<T>::v>(),os,el);
	if(!hasItr<T>::v)os<<el;
}
template<class H,class...T>void puta(const H&h,const T&...t){cout<<h<<' ';puta(t...);}
template<size_t i,class...T>void puta(tuple<T...>const&t, ostream&os){
	if constexpr(i==sizeof...(T)-1)puta(get<i>(t),os);
	else{os<<get<i>(t)<<' ';puta<i+1>(t,os);}
}
template<class...T>void puta(tuple<T...>const&t, ostream&os=cout){puta<0>(t,os);}
template<class S,class T>constexpr ostream&operator<<(ostream&os,pair<S,T>p){
	os<<'['<<p.first<<", ";
	if constexpr(hasItr<T>::v)puta(p.second,bool_constant<true>(),os,']');
	else os<<p.second<<']';
	return os;
};
template<class...T>constexpr ostream&operator<<(ostream&os,tuple<T...>t){puta(t,os); return os;}
void YN(bool b){puta(b?"YES":"NO");}
void Yn(bool b){puta(b?"Yes":"No");}

#ifdef _DEBUG
template<class T>void dump_f(const T&t){puta(t,cerr);}
template<class H,class...T>void dump_f(const H&h,const T&...t){cerr<<h<<' ';dump_f(t...);}
template<class...T>void dump_f(tuple<T...>const&t){puta(t,cerr);}
#define dump(...)cerr<<"  "<<string(#__VA_ARGS__)<<": ["<<to_string(__LINE__)<<":"<<__FUNCTION__<<"]\n    ",dump_f(__VA_ARGS__)
#else
#define dump(...)                                                              
#endif

/*
 * Input Assist
 */
template<class S,class T>auto&operator>>(istream&is,pair<S,T>&p){is>>p.first>>p.second;return is;}
template<class S>auto&operator>>(istream&is,vector<S>&t){for(S&a:t)is>>a;return is;}
template<typename...S>void geta_(S&...s){((cin>>s),...);}
#define geta(t,...) t __VA_ARGS__;geta_(__VA_ARGS__)
template<class T,class...Args>auto vec(T x,int arg,Args...args){if constexpr(sizeof...(args)==0)return vector(arg,x);else return vector(arg,vec(x,args...));}
#define getv(a,...) auto a=vec(__VA_ARGS__);cin>>a

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
template<class T> vector<pair<T,int>> addIndex(vector<T> a){
	vector<pair<T,int>> r;
	rep(i,a.size())r.emplace_back(a[i],i);
	return r;
}

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

const int SIZE = 30;

struct Point {
	int y, x;
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

	Point Move(DIRECTION dir) {
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
};

struct Stage {
	array<int, SIZE+2> stage;
	
	Stage() {
		stage.fill(0);
		stage[0]=~0;
		rep(i,SIZE)stage[i+1]=(1<<31)+1;
		stage[SIZE+1]=~0;
	}

	void Placement(Point p, bool fillAdjacent = false) {
		stage[p.y] |= 1 << (SIZE + 1 - p.x);
		if (fillAdjacent) {
			stage[p.y]   |= 1 << (SIZE + 0 - p.x);
			stage[p.y]   |= 1 << (SIZE + 2 - p.x);
			stage[p.y-1] |= 1 << (SIZE + 1 - p.x);
			stage[p.y+1] |= 1 << (SIZE + 1 - p.x);
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
		switch (dir) {
		case UP:
			return Get(Point(p.x, p.y - 1));
		case DOWN:
			return Get(Point(p.x, p.y + 1));
		case LEFT:
			return Get(Point(p.x - 1, p.y));
		case RIGHT:
			return Get(Point(p.x + 1, p.y));
		default:
			assert(false);
		}
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
	Human(int ID, int X, int Y) : Point(X, Y), id(ID) {
		walk.Placement(*this);
	}

	/**
	 * @brief 
	 * 
	 * @param wall 壁の情報
	 * @param cannotMovable 移動できない場所
	 * @param cannotWallPlaceable 壁を置けない場所
	 * @return char 
	 */
	char TestOptimizeAction(int turn, Stage&wall, Stage&cannotMovable, Stage&cannotWallPlaceable) {
		int wallCount=cannotMovable.CountAdjacent(*this);

		vector<DIRECTION> dirs(4);
		{
			vector<pair<int, DIRECTION>> d;
			d.emplace_back(Up().Distance(Point(15,15)), UP);
			d.emplace_back(Down().Distance(Point(15,15)), DOWN);
			d.emplace_back(Left().Distance(Point(15,15)), LEFT);
			d.emplace_back(Right().Distance(Point(15,15)), RIGHT);
			sort(all(d));
			if(turn >= 250) sort(rall(d));
			rep(i,4){
				dirs[i]=d[i].second;
			}
		}
		// shuffle(all(dirs), Random);

		if (wallCount < 3) {
			each(dir, dirs){
				if (!cannotWallPlaceable.Get(*this, (DIRECTION)dir)) {
					PlaceWall((DIRECTION)dir, cannotMovable, cannotWallPlaceable);
					return PlaceWall((DIRECTION)dir, wall, cannotWallPlaceable);
				}
			}
		}
		if (wallCount == 3 or nothingCount >= 4) {
			each(dir, dirs){
				if (!cannotMovable.Get(*this, (DIRECTION)dir)) {
					return Move((DIRECTION)dir, cannotWallPlaceable);
				}
			}
		}

		return DoNothing();
	}

	char DoNothing() {
		nothingCount++;
		return '.';
	}

	char Move(DIRECTION dir, Stage&cannotWallPlaceable) {
		if(nothingCount) nothingCount--;
		switch (dir) {
		case UP:
			cannotWallPlaceable.Placement(Point(x, --y));
			walk.Placement(*this);
			return 'U';
		case DOWN:
			cannotWallPlaceable.Placement(Point(x, ++y));
			walk.Placement(*this);
			return 'D';
		case LEFT:
			cannotWallPlaceable.Placement(Point(--x, y));
			walk.Placement(*this);
			return 'L';
		case RIGHT:
			cannotWallPlaceable.Placement(Point(++x, y));
			walk.Placement(*this);
			return 'R';
		default:
			assert(false);
		}
	}

	char PlaceWall(DIRECTION dir, Stage&wall, Stage&cannotWallPlaceable) {
		if(nothingCount) nothingCount--;
		switch (dir) {
		case UP:
			wall.Placement(Point(x, y - 1));
			cannotWallPlaceable.Placement(Point(x, y - 1));
			return 'u';
		case DOWN:
			wall.Placement(Point(x, y + 1));
			cannotWallPlaceable.Placement(Point(x, y + 1));
			return 'd';
		case LEFT:
			wall.Placement(Point(x - 1, y));
			cannotWallPlaceable.Placement(Point(x - 1, y));
			return 'l';
		case RIGHT:
			wall.Placement(Point(x + 1, y));
			cannotWallPlaceable.Placement(Point(x + 1, y));
			return 'r';
		default:
			wall.Placement(*this);
			// cannotWallPlaceable.Placement(*this);
			return ' ';
		}
	}
};


struct Solver {
	int turn = 0;
	/** @brief 10~20 */
	int petCount;

	/** @brief 5~10 */
	int humanCount;

	vector<Pet> pets;
	vector<Human> humans;

	Stage wall;

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

	string HumansAction() {
		auto cannotMovable = wall;
		for(auto&human:humans){
			cannotMovable.Any(human.walk);
		}
		// cout<<"# walk:"<<endl;
		// cannotMovable.Print();

		auto cannotWallPlaceable = cannotMovable;
		for(auto&pet:pets){
			cannotWallPlaceable.Placement(pet, true);
		}
		rep(x,2,SIZE)rep(y,2,SIZE){
			if(wall.CountAdjacent(Point(x,y)) >= 2){
				cannotWallPlaceable.Placement(Point(x,y));
			}
		}

		// cout<<"# cannot place:"<<endl;
		// cannotWallPlaceable.Print();

		// 人の行動を決定する
		string humanAction = "";
		for(auto&human:humans){
			humanAction += human.TestOptimizeAction(turn, wall, cannotMovable, cannotWallPlaceable);
		}
		return humanAction;
	}

	void PetsAction() {
		string s;
		rep(i, petCount){
			cin>>s;
			for(auto&c:s) pets[i].Action(c);
		}
	}

	void Turn() {
		turn++;
		auto action = HumansAction();
		cout<<action<<endl;
		PetsAction();
	}

	void Simulate() {
		rep(300){
			Turn();
			#ifdef _DEBUG
			CalculateScore();
			#endif
		}
	}

	int CalculateScore() {
		vd scores(humanCount, 0);
		// wall.Print();

		rep(i,humanCount)if(scores[i]==0){
			auto[area, containHumans, containPets] = AreaPetCount(humans[i]);
			for(auto&humanId : containHumans) {
				scores[humanId] = area / 900.0 / (1 << containPets.size());
				cout<<"# "<<humanId<<" "<<area<<" "<<containPets.size()<<" = "<<(int)round(1e8 * scores[humanId] / humanCount)<<endl;
			}
		}

		#ifdef _DEBUG
		cout<<"# Turn: "<<turn<<endl;
		// rep(i,humanCount){
		// 	cout<<"# "<<i<<" "<<scores[i]<<endl;
		// }
		cout<<"# "<<"total: "<<(int)round(1e8 * sum(scores) / humanCount)<<endl;
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
				q.push(p.Move(dir));
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

	solver.Simulate();
}
