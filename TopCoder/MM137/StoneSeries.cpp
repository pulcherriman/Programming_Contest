#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("inline")
#pragma GCC diagnostic ignored "-Wunused-value"
#ifdef _DEBUG
// #define _GLIBCXX_DEBUG 1
// #define _GLIBCXX_DEBUG_PEDANTIC 1
#endif

/* 
 * Include Headers
 */
#include<bits/stdc++.h>
// #include <ext/pb_ds/assoc_container.hpp>
using namespace std;

/*
 * Additional Type Definition
 */
using vb=vector<bool>;
using vvb=vector<vb>;
using vi=vector<int>;
using vvi=vector<vi>;
using pii=pair<int,int>;
using vp=vector<pii>;
using t3=tuple<int,int,int>;
using t4=tuple<int,int,int,int>;
using vs=vector<string>;
// template<class K> using IndexedSet=__gnu_pbds::tree<K,__gnu_pbds::null_type,less<K>,__gnu_pbds::rb_tree_tag,__gnu_pbds::tree_order_statistics_node_update>;
// template<class K> using HashSet=__gnu_pbds::gp_hash_table<K,__gnu_pbds::null_type>;
// template<class K,class V> using IndexedMap=__gnu_pbds::tree<K,V,less<K>,__gnu_pbds::rb_tree_tag,__gnu_pbds::tree_order_statistics_node_update>;
// template<class K,class V> using HashMap=__gnu_pbds::gp_hash_table<K,V>;
// template<class V> using minpq = priority_queue<V, vector<V>, greater<V>>;

#define all(a) begin(a),end(a)
#define rall(a) rbegin(a),rend(a)
#define __LOOPSWITCH(_1, _2, _3, __LOOPSWITCH, ...) __LOOPSWITCH
#define rep(...) __LOOPSWITCH(__VA_ARGS__, __RANGE, __REP, __LOOP) (__VA_ARGS__)
#define rrep(...) __LOOPSWITCH(__VA_ARGS__, __RRANGE, __RREP, __LOOP) (__VA_ARGS__)
#define __LOOP(q) __LOOP2(q, __LINE__)
#define __LOOP2(q,l) __LOOP3(q,l)
#define __LOOP3(q,l) __REP(_lp ## l,q)
#define __REP(i,n) __RANGE(i,0,n)
#define __RANGE(i,a,n) for(int i=((int)a);i<((int)n);++i)
#define __RREP(i,n) __RRANGE(i,0,n)
#define __RRANGE(i,a,n) for(int i=((int)(n)-1);i>=((int)a);--i)
#define sz(a) ((int)(a).size())

/*
 * Constants
 */
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

namespace IO {
	// container detection
	template<typename T, typename _=void> struct is_container : false_type {};
	template<> struct is_container<string> : false_type {};
	template<typename...Ts> struct is_container_helper {};
	template<typename T> struct is_container<T, conditional_t<
		true, void, is_container_helper<
			typename T::value_type, typename T::size_type, typename T::iterator,
			decltype(declval<T>().size()),
			decltype(declval<T>().begin()),
			decltype(declval<T>().end()) >>> : public true_type {};
	template<typename T,
		typename enable_if<is_container<T>{}, nullptr_t>::type = nullptr,
		char Separator = is_container<typename T::value_type>{} ? '\n' : ' ' >
	constexpr ostream&operator<<(ostream&os, T t){
		if(auto b=begin(t), e=end(t) ; !t.empty()) for(os<<(*b++);b!=e;os<<Separator<<(*b++)) ;
		return os;
	}

	// output
	template<class T, class...Ts> constexpr ostream& pargs(ostream&os, T&&t, Ts&&...args); // support clang
	template<class S,class T>constexpr ostream&operator<<(ostream&os,pair<S,T>p){ return os<<'['<<p.first<<", "<<p.second<<']'; };
	template<class...Ts>constexpr ostream&operator<<(ostream&os,tuple<Ts...>t){
		return apply([&os](auto&&t,auto&&...args)->ostream&{return pargs(os, t, args...);}, t);
	};
	template<class T, class...Ts> constexpr ostream& pargs(ostream&os, T&&t, Ts&&...args) {
		return ((os<<t)<<...<<(os<<' ', args));
	}

	template<class...Ts> constexpr ostream& out(Ts...args) { return pargs(cout, args...)<<'\n'; }
	template<class...Ts> constexpr ostream& debug_f(Ts...args) { return pargs(cerr, args...)<<'\n'; }
	#ifdef _DEBUG
	template<class...Ts> constexpr ostream& debug(Ts...args) { return pargs(cerr, args...)<<'\n'; }
	#else
	#define debug(...) if(false)debug_f(__VA_ARGS__)
	#endif
	void Yn(bool f) { out(f?"Yes":"No"); }

	// input
	template<class T, class...Ts> constexpr istream& gargs(istream&is, T&&t, Ts&&...args) {
		return ((is>>t)>>...>>args);
	}
	template<class S,class T>auto&operator>>(istream&is,pair<S,T>&p){return is>>p.first>>p.second;}
	template<class...Ts>constexpr istream&operator>>(istream&is,tuple<Ts...>&t){
		return apply([&is](auto&&t,auto&&...args)->istream&{return gargs(is, t, args...);}, t);
	};

	template<typename...S>auto&in(S&...s){return gargs(cin, s...);}
	#define def(t,...) t __VA_ARGS__; in(__VA_ARGS__)
	template<typename T, typename enable_if<is_container<T>{}, nullptr_t>::type = nullptr>
	auto&operator>>(istream&is,T&t){for(auto&a:t)is>>a; return is;}
}
using namespace IO;

class Random {
public:
	typedef uint_fast32_t result_type;
	static constexpr result_type max(){return numeric_limits<result_type>::max();}
	static constexpr result_type min(){return 0;}
	constexpr Random(const bool&isDeterministic):y(isDeterministic?2463534242:chrono::system_clock::now().time_since_epoch().count()){}
	constexpr int operator()(int a,int b){return next()%(b-a)+a;}
private:
	result_type y;
	constexpr result_type next(){return y^=(y^=(y^=y<<13)>>17)<<5;}
} Random(1);

class Timer {
	#ifdef _DEBUG
	static constexpr uint64_t ClocksPerMsec = 3587000;
	#else
	static constexpr uint64_t ClocksPerMsec = 2787000;
	#endif
	const uint64_t start,limit;
	uint64_t getClocks() const{
		unsigned int lo,hi;
		__asm__ volatile ("rdtsc" : "=a" (lo), "=d" (hi));
		return((uint64_t)hi<<32)|lo;
	}
public:
	Timer(uint64_t _limit=1970): start(getClocks()),limit(start+_limit*ClocksPerMsec) {}
	uint64_t get() const{return (getClocks()-start)/ClocksPerMsec;}
	operator bool()const{return getClocks()<limit;}
};
void wait(const int&msec){Timer tm(msec); while(tm);}

struct Mgr {
	static const int TLE = 9850;
	static inline Timer timer = Timer(TLE-20);
	Mgr() {
		ios_base::sync_with_stdio(0); cin.tie(0);
	}
	~Mgr(){
		debug_f(timer.get(), "ms")<<flush;
	}
} _manager;


const int WALL=-1;

int n;
vvi field;

inline bool isWall(int y, int x){
	return field[y][x]==WALL;
}

inline bool isBlank(int y, int x){
	return field[y][x]==0;
}

/**
 * @brief マス(y,x)の隣接マスの情報を返す
 * 
 * @param y Y座標
 * @param x X座標
 * @return tuple {隣接する空マスの数, 隣接数値の個数, 隣接数値の合計値}
 */
t3 neighborSum(int y, int x){
	int blank=0, cnt=0, total=0;
	rep(i,y-1,y+2)rep(j,x-1,x+2){
		if(i==y and j==x)continue;
		if(isWall(i,j))continue;
		if(isBlank(i,j))++blank;
		else total+=field[i][j], ++cnt;
	}
	return {blank, cnt, total};
}

pair<int, vp> solve() {
	static vp place,target;
	place.clear();
	if(target.empty()){
		rep(i,1,n+1)rep(j,1,n+1){
			if(isBlank(i,j)){
				target.emplace_back(i,j);
			}
		}
		sort(all(target), [&](pii a, pii b){
			const int center = n/2;
			int adist=abs(a.first-center)+abs(a.second-center);
			int bdist=abs(b.first-center)+abs(b.second-center);
			return adist<bdist;
		});
	}

	int score=0;
	{
		// place 1s
		for(auto&[i,j]:target){
			auto [blank, cnt, total] = neighborSum(i,j);
			if(cnt>=1)continue;
			if(blank+cnt<8)continue;
			place.emplace_back(i, j);
			score += 1;
			field[i][j] = 1;
		}
		while(true){
			bool updated=false;
			for(auto&[i,j]:target){
				if(!isBlank(i,j))continue;
				auto [blank, cnt, total] = neighborSum(i,j);
				if(cnt>=1)continue;
				if(Random(0,20)>0)continue;
				updated = true;
				place.emplace_back(i, j);
				score += 1;
				field[i][j] = 1;
			}
			if(!updated)break;
		}
	}

	int currentPlacedMax = 1;
	// place others
	while(true){
		t4 maxPlace = {-1,0,0,0};
		rep(i,1,n+1)rep(j,1,n+1){
			if(!isBlank(i,j))continue;
			auto [blank, cnt, total] = neighborSum(i,j);
			if(cnt==1)continue;
			if(total > currentPlacedMax+1)continue;
			chmax(maxPlace, {total, -blank, i, j});
		}
		auto [total, _, y, x] = maxPlace;


		if(total == -1)break;
		chmax(total, 1);
		place.emplace_back(y, x);
		score += total;
		field[y][x] = total;
		chmax(currentPlacedMax, total);
	}

	return {score, place};
}

vi snapshotScore;
vector<vvi> snapshot;
void createSimulate(vvi&init, vp&place){
	snapshotScore.resize(sz(place)+1, 0);
	snapshot.resize(sz(place)+1);

	snapshotScore[0]=0;
	snapshot[0]=init;

	field = init;
	int score = 0, currentPlacedMax = 0;
	rep(i,sz(place)){
		auto[y,x]=place[i];
		auto [blank, cnt, total] = neighborSum(y, x);
		chmax(total, 1);
		chmax(currentPlacedMax, total);
		score += total;
		snapshotScore[i+1] = score;

		field[y][x] = total;
		snapshot[i+1] = field;
	}
}


int simulate(vp&place, int ignore){
	int score = 0, currentPlacedMax = 0;
	score = snapshotScore[ignore];
	field = snapshot[ignore];

	rep(i,ignore+1,sz(place)){
		auto[y,x]=place[i];
		auto [blank, cnt, total] = neighborSum(y, x);
		if(cnt==1) return -1;
		chmax(total, 1);
		if(total > currentPlacedMax+1) return -1;
		score += total;
		field[y][x] = total;
		chmax(currentPlacedMax, total);
	}
	return score;
}

pair<int, vp> yamanobori(vvi&init, int maxScore, vp answer) {
	createSimulate(init, answer);
	
	int from = -1;
	while(true){
		from++;
		if(from>=sz(answer)){
			break;
		}
		int score = simulate(answer, from);
		if(score==-1) continue;
		auto[addScore, addPlace] = solve();
		score+=addScore;

		if(chmax(maxScore, score)){
			answer.erase(answer.begin()+from);
			copy(all(addPlace), back_inserter(answer));
			from=-1;
			createSimulate(init, answer);
		}
	}
	return {maxScore, answer};
}

int main() {
	cin>>n;
	vvi init(n+2, vi(n+2, WALL));
	rep(i,1,n+1)rep(j,1,n+1){
		char c; cin>>c;
		if(c=='.') init[i][j]=0;
	}

	int cnt=0;
	int maxScore = 0, maxDefaultScore=0;
	vp answer;

	while(Mgr::timer){
		cnt++;
		field = init;
		auto [score, place] = solve();
		if(chmax(maxDefaultScore, score)){
			tie(score, place) = yamanobori(init, maxDefaultScore, place);
		}
		if(chmax(maxScore, score)){
			answer = place;
		}
	}

	cout<<answer.size()<<endl;
	for(auto&[y,x]:answer)cout<<y-1<<" "<<x-1<<endl;
		
	#ifdef _DEBUG
	
	rep(i,1,n+1){
		rep(j,1,n+1)cerr<<(init[i][j]==0 ? '.' : '#');
		cerr<<endl;
	}
	debug("Score:",maxScore);
	debug("Count:",cnt);

	#endif
	return 0;
}


/*
Seed = 1, Score = 247.0
Seed = 2, Score = 187339.0
Seed = 3, Score = 103178.0
Seed = 4, Score = 118575.0
Seed = 5, Score = 100486.0
Seed = 6, Score = 7468.0
Seed = 7, Score = 1031.0
Seed = 8, Score = 4230.0

Seed = 1, Score = 238.0
Seed = 2, Score = 177086.0
Seed = 3, Score = 100795.0
Seed = 4, Score = 104704.0
Seed = 5, Score = 100232.0
Seed = 6, Score = 7468.0
Seed = 7, Score = 1000.0
Seed = 8, Score = 4230.0

*/