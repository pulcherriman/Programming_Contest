#pragma GCC optimize "O3" /* 最適化 */
#pragma GCC target "avx" /* SIMD(ベクトル化) */
// #pragma GCC optimize "fast-math"
// #pragma GCC optimize "unroll-loops" /* ループの展開 */
#include<bits/stdc++.h>

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

#define all(a) begin(a),end(a)
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


namespace IO {
	constexpr static char CHAR_BR='\n';
	template<class T, class...Args> static constexpr ostream& print(T t, Args...args) {
		return ((cout<<t)<<...<<(cout<<' ', args))<<CHAR_BR;
	}
	template<class T, class...Args> static constexpr ostream& debug_f(T t, Args...args) {
		return ((cerr<<t)<<...<<(cerr<<' ', args))<<CHAR_BR;
	}
	#ifdef _DEBUG
	template<class T, class...Args> static constexpr ostream& debug(T t, Args...args) {
		return ((cerr<<t)<<...<<(cerr<<' ', args))<<CHAR_BR;
	}
	#else
	static inline ostream& debug(...) { return cerr; }
	#endif
}
using namespace IO;


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
	Timer(uint64_t _limit=1970): start(getClocks()),limit(start+_limit*ClocksPerMsec) {}
	uint64_t get() const{return (getClocks()-start)/ClocksPerMsec;}
	operator bool()const{return getClocks()<limit;}
};
void wait(const int&msec){Timer tm(msec); while(tm);}



struct Marathon {
	static const int TLE = 1970;
	static inline Timer baseTimer = Timer(TLE);
	Marathon() {

	}
	~Marathon(){
		debug_f(baseTimer.get(), "ms")<<flush;
	}

} marathon;



// input
int H, S, C, a, b;
vi K;
vvi N, A, B;
int TOTAL = 0;


void read_input() {
    cin >> S >> C >> H >> a >> b;
    N.resize(S);
	rep(s,S) {
        N[s].resize(C);
        rep(c,C) {
			cin >> N[s][c];
			TOTAL += N[s][c];
		}
    }
    K.resize(S);
    rep(s,S) cin >> K[s];
    A.resize(S);
    rep(s,S) {
        A[s].resize(S);
        rep(t,S) cin >> A[s][t];
    }
    B.resize(C);
    rep(c,C) {
        B[c].resize(C);
        rep(d,C) cin >> B[c][d];
    }
}

void write_output(const vector<pair<int, int> > &ans) {
	print(ans.size());
	for(auto[s,c]:ans){
        if (s >= 0) {
			print(s+1, c+1);
        } else {
			print(s);
        }
    }
}

struct ParameterPack {
	vi shapes, colors;
	vp answer;
	int penalty = INF;

	ParameterPack() {}
	ParameterPack(vi shapes, vi colors) : shapes(shapes), colors(colors) {}

	bool operator>(const ParameterPack &rhs) const {
		return penalty > rhs.penalty;
	}
	
	inline vi& get_small(){
		return shapes.size() < colors.size() ? shapes : colors;
	}
	inline vi& get_large(){
		return shapes.size() >= colors.size() ? shapes : colors;
	}

	static const int SIZE_THRESHOLD = 0;
	bool next_vector(vi&feat){
		if(feat.size() <= SIZE_THRESHOLD){
			return next_permutation(all(feat));
		} else {
			shuffle(all(feat), Random);
			return true;
		}
	}

	void reset_small(){
		auto&target = get_small();
		if(target.size() <= SIZE_THRESHOLD)iota(all(target), 0);
		else shuffle(all(target), Random);
	}

	void reset_large(){
		auto&target = get_large();
		if(target.size() <= SIZE_THRESHOLD)iota(all(target), 0);
		else shuffle(all(target), Random);
	}

	bool move_small(){
		return next_vector(get_small());
	}
	bool move_large(){
		return next_vector(get_large());
	}

	int nearby_key = 0;
	void nearby(vi&target, bool isRevert){
		if(!isRevert) {
			const int a=Random(0, target.size());
			const int b=Random(0, target.size()-1);
			nearby_key = a*target.size()+b;
			if(a<=b)nearby_key++;
		}
		const int a=nearby_key/target.size();
		const int b=nearby_key%target.size();
		swap(target[a], target[b]);
	}
	void nearby_small(bool isRevert = false){
		nearby(get_small(), isRevert);
	}
	void nearby_large(bool isRevert = false){
		nearby(get_large(), isRevert);
	}

	double startTemp   =  2000;
	static constexpr double endTemp     =    10;
	bool is_updatable(ParameterPack&target) {
		if(*this > target) return true;
		const double temp = startTemp + (endTemp - startTemp) * Marathon::baseTimer.get() / (Marathon::TLE - 200);
		const double probability = exp((penalty - target.penalty) / temp);
		const bool FORCE_NEXT = probability > Random(0.0, 1.0);
		if(FORCE_NEXT) {
			return true;
		}

		return false;
	}
};

struct Solver {
	int X = 0, Y = 0;
	int pos = 0, prev_s = -1, prev_c = -1;
	int remain_kinds = S*C, errorCount = 0;
	vi hanger_on_hook;
	vi hangers_available;
	vi need_shape;
	vvi remainCount;
	deque<pii> que;
	vp ans;

	Solver(ParameterPack&params) {
		pos = 0, prev_s = -1, prev_c = -1;
		remain_kinds = S*C, errorCount = 0;
		hanger_on_hook.resize(H, -1);
		hangers_available = K;
		need_shape.resize(S,0);
		remainCount = N;

		for(auto c:params.colors) for(auto s:params.shapes) if(remainCount[s][c] > 0){
			que.emplace_back(s, c);
			need_shape[s]+=remainCount[s][c];
		}
	}

	void add_position(){
		if (pos == H - 1) pos = 0; else pos++;
	}
	bool is_placeable(int s, int _pos){
		return hanger_on_hook[_pos] == s or hangers_available[s] > 0;
	}

	void place_product(int s, int c){
		assert(remainCount[s][c] > 0);
		assert(is_placeable(s, pos));

		ans.emplace_back(s, c);
		need_shape[s]--;
		remainCount[s][c]--;
		if (hanger_on_hook[pos] != s) {
			if (hanger_on_hook[pos] >= 0) {
				// 既存のハンガーを外す
				X++;
				hangers_available[hanger_on_hook[pos]]++;
			}
			// 新しいハンガーを設置
			X++;
			hangers_available[s]--;
			hanger_on_hook[pos] = s;
		}
		if(remainCount[s][c]==0) {
			remain_kinds--;
		}
		errorCount = 0;
		prev_s = s;
		prev_c = c;
	}

	void remove_hanger(){
		assert(hanger_on_hook[pos] != -1);
		X++;;
		ans.emplace_back(-1, 0);
		Y++;
		hangers_available[hanger_on_hook[pos]]++;
		hanger_on_hook[pos] = -1;
	};

	void do_nothing(){
		ans.emplace_back(-2, 0);
		Y++;
	};

	void remove_or_stay(){
		const int hanger_id = hanger_on_hook[pos];
		const bool cannot_place = hanger_id != -1;
		const bool want_to_use_other = need_shape[hanger_id] > hangers_available[hanger_id];
		if(cannot_place and want_to_use_other) {
			remove_hanger();
		}else{
			do_nothing();
		}
	};

	void rotate(){
		auto p=que.front();
		que.pop_front();
		que.emplace_back(p);
	}

	void walk(){
		auto[s,c] = que.front();
		que.pop_front();
		const int setup = (prev_s == -1 ? 0 : max(A[prev_s][s], B[prev_c][c]));
		{
			int dpos = (pos + setup) % H;
			if (!is_placeable(s, dpos)) {
				errorCount++;
				if(errorCount < remain_kinds){
					que.emplace_back(s, c);
					return;
				}
				remove_or_stay();
				add_position();
				que.emplace_back(s, c);
				return;
			}
		}

		rep(setup) {
			remove_or_stay();
			add_position();
		}

		for ( ;remainCount[s][c]; ) {
			if (is_placeable(s, pos)){
				place_product(s,c);
			} else {
				errorCount++;
				if(errorCount < remain_kinds){
					que.emplace_back(s, c);
					break;
				}
				remove_or_stay();
			}
			add_position();
		}
	}

	int solve(int ashikiri = INF) {
		while (!que.empty()) {
			walk();
			if(a*X + b*Y > ashikiri) return INF;
		}

		return a*X + b*Y;
	}
};

int solveCount = 0;
void solve(ParameterPack&params, bool isBeamSearch = false, int threshold = 10) {
	solveCount++;
	Solver solver(params);
	if(isBeamSearch)while(!solver.que.empty()){
		if( solver.que.size() >= threshold ){
			solver.walk();
			continue;
		}
		int q_size = solver.que.size();
		int bestScore = INF;
		Solver searchSolver = solver;
		pii bestPair;
		rep(i, q_size){
			pii currentPair = searchSolver.que.front();
			if(chmin(bestScore, searchSolver.solve(bestScore))){
				bestPair = currentPair;
			}
			solver.rotate();
			searchSolver = solver;
		}
		while(solver.que.front() != bestPair){
			solver.rotate();
		}
		solver.walk();
	}
	params.penalty = solver.solve();
	params.answer = solver.ans;
}


int main() {
    read_input();

	vi shapes(S), colors(C);
	iota(all(shapes), 0);
	iota(all(colors), 0);

	ParameterPack bestParams, currentParams;
	ParameterPack params(shapes, colors);
	
	int epoch = 10, fail_count = 0, fail_threshold = 5000;
	Timer SATimer(Marathon::TLE-200);
	do{
		{
			debug("start small");
			Timer timer(epoch);
			do {
				bool isAfter = Marathon::baseTimer.get() > 1000;
				params.nearby_small();
				solve(params, isAfter);
				if(currentParams.is_updatable(params)){
					currentParams = params;
					if(!isAfter) solve(params, true);
					chmin(currentParams, params);
					if(chmin(bestParams, currentParams)){
						debug("small:", bestParams.penalty);
					}
				} else {
					params.nearby_small(true);
					// if(++fail_count >= fail_threshold){
					// 	params.move_small();
					// 	currentParams.penalty = INF;
					// 	debug("RESET");
					// 	fail_count = 0;
					// }
				}
			}while(timer and SATimer);
		}
		params = currentParams;
		{
			debug("start large");
			Timer timer(epoch);
			do {
				bool isAfter = Marathon::baseTimer.get() > 1000;
				params.nearby_large();
				solve(params, isAfter);
				if(currentParams.is_updatable(params)){
					currentParams = params;
					if(!isAfter) solve(params, true);
					chmin(currentParams, params);
					if(chmin(bestParams, currentParams)){
						debug("large:", bestParams.penalty);
					}
				} else {
					params.nearby_large(true);
					// if(++fail_count >= fail_threshold){
					// 	params.move_large();
					// 	currentParams.penalty = INF;
					// 	debug("RESET");
					// 	fail_count = 0;
					// }
				}
			}while(timer and SATimer);
		}
		params = currentParams;
	}while(SATimer);

	debug_f(solveCount, bestParams.penalty);
	{
		auto params = bestParams;
		solve(params, true, INF);
		chmin(bestParams, params);
	}
	debug_f(solveCount, bestParams.penalty);
	write_output(bestParams.answer);
}
