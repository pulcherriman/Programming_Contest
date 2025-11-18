/**
 * AHC050 - 階層的意思決定版
 * main.cppをベースに、マクロ・ミクロ階層で最適化
 */

#ifdef _DEBUG
// #define _GLIBCXX_DEBUG 1
#else
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("inline")
#endif

/* 
 * Include Headers
 */
#if defined(EVAL) || defined(ATCODER) || defined(_DEBUG)
#include <atcoder/all>
using namespace atcoder;
#endif
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

#ifndef _GLIBCXX_DEBUG
template<class K> using IndexedSet=__gnu_pbds::tree<K,__gnu_pbds::null_type,less<K>,__gnu_pbds::rb_tree_tag,__gnu_pbds::tree_order_statistics_node_update>;
template<class K,class V> using IndexedMap=__gnu_pbds::tree<K,V,less<K>,__gnu_pbds::rb_tree_tag,__gnu_pbds::tree_order_statistics_node_update>;
template<class K,class V> struct HashMap : __gnu_pbds::gp_hash_table<K,V,hash<K>> {
	bool contains(const K&k) const { return this->find(k) != this->end(); }
};
template<class K> struct HashSet : __gnu_pbds::gp_hash_table<K,__gnu_pbds::null_type,hash<K>> {
	bool contains(const K&k) const { return this->find(k) != this->end(); }
};
#else
template<class K> using IndexedSet=set<K>;
template<class K> using HashSet=unordered_set<K>;
template<class K,class V> using IndexedMap=map<K,V>;
template<class K,class V> using HashMap=unordered_map<K,V>;
#endif
template<class V> using maxpq = priority_queue<V>;
template<class V> using minpq = priority_queue<V, vector<V>, greater<V>>;

#define all(a) begin(a),end(a)
#define rall(a) rbegin(a),rend(a)
#define __LOOPSWITCH(_1, _2, _3, __LOOPSWITCH, ...) __LOOPSWITCH
#define rep(...) __LOOPSWITCH(__VA_ARGS__, __RANGE, __REP, __LOOP) (__VA_ARGS__)
#define rrep(...) __LOOPSWITCH(__VA_ARGS__, __RRANGE, __RREP, __LOOP) (__VA_ARGS__)
#define __LOOP(q) for([[maybe_unused]] int _lp ## __LINE__ : views::iota(0, q))
#define __LOOP2(q,l) __LOOP3(q,l)
#define __LOOP3(q,l) __REP(_lp ## l,q)
#define __REP(i,n) __RANGE(i,0,n)
#define __RANGE(i,a,n) for(ll i=((ll)a);i<((ll)n);++i)
#define __RREP(i,n) __RRANGE(i,0,n)
#define __RRANGE(i,a,n) for(ll i=((ll)(n)-1);i>=((ll)a);--i)
#define sz(a) ((ll)(a).size())
#define pb push_back
#define eb emplace_back

/*
 * Constants
 */
constexpr ll LINF=1ll<<60;
constexpr int INF=1<<30;
constexpr double EPS=(1e-14);
constexpr ll MOD=998244353ll;
constexpr long double PI=3.14159265358979323846;

/*
 * Utilities
 */
template<class T,class...Args>auto vec(T x,int arg,Args...args){
	if constexpr(sizeof...(args)==0) return vector(arg,x);
	else return vector(arg,vec(x,args...));
}
template<class T>constexpr bool chmax(T&a, type_identity_t<T> b){return a<b?a=b,1:0;}
template<class T>constexpr bool chmin(T&a, type_identity_t<T> b){return a>b?a=b,1:0;}
template<class S>S sum(vector<S>&a){return accumulate(all(a),S());}
template<class S>S max(vector<S>&a){return *max_element(all(a));}
template<class S>S min(vector<S>&a){return *min_element(all(a));}
ll sumAtoB(ll a,ll b){return (a+b)*(b-a+1)/2;}

namespace IO {
	// concepts定義
	template<typename T> concept Iterable = ranges::range<T> && !is_convertible_v<T, string_view>;
	template<typename T> concept RecursiveIterable = Iterable<T> && ranges::range<ranges::range_value_t<T>>;
	template<typename T> concept TupleLike = !Iterable<T> && requires(T a) {
		tuple_size<T>::value;
		get<0>(a);
		!is_convertible_v<T, string_view>;
	};

	// output
	constexpr ostream&operator<<(ostream&os, Iterable auto a){
		if(auto b=begin(a), e=end(a) ; a.size()) for(os<<(*b++);b!=e;os<<' '<<(*b++)) ;
		return os;
	}
	constexpr ostream&operator<<(ostream&os, RecursiveIterable auto a){
		if(auto b=begin(a), e=end(a) ; a.size()) for(os<<(*b++);b!=e;os<<'\n'<<(*b++)) ;
		return os;
	}
	constexpr ostream&operator<<(ostream&os, TupleLike auto a){
		apply([&](auto&&...args){((os<<args<<' '),...);}, a);
		return os;
	}

	template<class T, class...Ts> constexpr ostream& pargs(ostream&os, T&&t, Ts&&...args) {
		return ((os<<t)<<...<<(os<<' ', args));
	}
	template<class...Ts> constexpr ostream& out(Ts...args) { return pargs(cout, args...)<<'\n'; }
	template<class...Ts> constexpr ostream& out_f(Ts...args) { return pargs(cout, args...)<<'\n'<<flush; }
	template<class...Ts> constexpr ostream& debug_f(Ts...args) { return pargs(cerr, args...)<<'\n'<<flush; }
	#ifdef _DEBUG
	template<class...Ts> constexpr ostream& debug(Ts...args) { return pargs(cerr, args...)<<'\n'; }
	#else
	#define debug(...) if(false)debug_f(__VA_ARGS__)
	#endif
	void Yn(bool f) { out(f?"Yes":"No"); }

	// input
	constexpr auto&operator>>(istream&is, Iterable auto&t){ for(auto&a:t)is>>a; return is; }
	constexpr auto&operator>>(istream&is, TupleLike auto&t){
		apply([&](auto&&...args){((is>>args),...);}, t);
		return is;
	};

	template<class T, class...Ts> constexpr istream& gargs(istream&is, T&&t, Ts&&...args) {
		return ((is>>t)>>...>>args);
	}
	template<typename...S>auto&in(S&...s){return gargs(cin, s...);}
	#define def(t,...) t __VA_ARGS__; in(__VA_ARGS__)
}
using namespace IO;

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
	uint64_t get() const { return (getClocks()-start)/ClocksPerMsec; }
	operator bool() const { return getClocks()<limit; }
	float persentile() const { return (float)get()/limit; }
};
void wait(const int&msec){Timer tm(msec); while(tm);}

struct Mgr {
	static const int TLE = 2000;
	static inline Timer timer = Timer(TLE-70);
	Mgr() {
		ios_base::sync_with_stdio(0); cin.tie(0);
		cout<<fixed<<setprecision(11);
		cerr<<fixed<<setprecision(3);
	}
	~Mgr(){
		cout<<flush;
		debug_f(timer.get(), "ms")<<flush;
	}
} _manager;

namespace std {
	template<class T>
	struct hash_base {
		const static inline size_t hash_value = 0x9e3779b9;
		static inline size_t hash_rnd = Random(0, numeric_limits<size_t>::max());
		template<class V, class P=remove_const_t<remove_reference_t<V>>> static size_t& do_hash(size_t&seed, V&v) {
			return seed ^= hash<P>{}(v) + hash_value + (seed<<6) + (seed>>2);
		}
		virtual size_t operator()(T p) const = 0;
	};

	template<class S, class T>
	struct hash<pair<S,T>> : public hash_base<pair<S,T>> {
		size_t operator()(pair<S,T> p) const {
			size_t seed = 0;
			this->do_hash(seed, p.first);
			this->do_hash(seed, p.second);
			return this->do_hash(seed, this->hash_value);
		}
	};

	template<class...Ts>
	struct hash<tuple<Ts...>> : public hash_base<tuple<Ts...>> {
		size_t operator()(tuple<Ts...> t) const {
			return apply([&](auto&&...args)->size_t{
				size_t seed = 0;
				for(auto&&v : {args...}) this->do_hash(seed, v);
				return this->do_hash(seed, this->hash_value);
			}, t);
		}
	};
}

// main.cppと同じ確率更新関数
vvd updateProbability(const vvd& prob, const vs& field, int N) {
	vvd nextProb(N, vd(N, 0.0));
	rep(i, N) rep(j, N) {
		if(prob[i][j] <= 1e-9) continue;
		
		// 4方向への移動
		vector<pii> dirs = {{-1,0}, {1,0}, {0,-1}, {0,1}};
		for(auto [di, dj] : dirs) {
			int ni = i, nj = j;
			// 岩にぶつかるまで移動
			while(ni + di >= 0 && ni + di < N && nj + dj >= 0 && nj + dj < N && 
				  field[ni + di][nj + dj] == '.') {
				ni += di;
				nj += dj;
			}
			nextProb[ni][nj] += prob[i][j] * 0.25;
		}
	}
	return nextProb;
}

// 領域を表現する構造体
struct Region {
	int minR, maxR, minC, maxC;
	double totalProb;
	double avgProb;
	int emptyCells;
	double importance;
	
	Region(int r1, int r2, int c1, int c2) : minR(r1), maxR(r2), minC(c1), maxC(c2) {}
	
	// 領域内の統計を計算
	void calculateStats(const vs& field, const vvd& prob, int N) {
		totalProb = 0.0;
		emptyCells = 0;
		
		for(int i = minR; i <= maxR && i < N; i++) {
			for(int j = minC; j <= maxC && j < N; j++) {
				if(field[i][j] == '.') {
					totalProb += prob[i][j];
					emptyCells++;
				}
			}
		}
		
		avgProb = (emptyCells > 0) ? totalProb / emptyCells : 0.0;
		
		// 重要度計算：総確率と空きマス数のバランス
		importance = totalProb * (1.0 + sqrt(emptyCells) * 0.1);
	}
	
	// 座標が領域内にあるかチェック
	bool contains(int r, int c) const {
		return r >= minR && r <= maxR && c >= minC && c <= maxC;
	}
};

// 階層的意思決定クラス
class HierarchicalDecision {
private:
	int N;
	vector<Region> regions;
	
	// フィールドを領域に分割
	void createRegions() {
		regions.clear();
		
		// 分割数を動的に決定
		int divs = (N <= 20) ? 2 : (N <= 30) ? 3 : 4;
		int regionSize = N / divs;
		
		rep(i, divs) rep(j, divs) {
			int r1 = i * regionSize;
			int r2 = (i == divs - 1) ? N - 1 : (i + 1) * regionSize - 1;
			int c1 = j * regionSize;
			int c2 = (j == divs - 1) ? N - 1 : (j + 1) * regionSize - 1;
			
			regions.emplace_back(r1, r2, c1, c2);
		}
		
		debug("Created", regions.size(), "regions with size ~", regionSize);
	}
	
	// 領域内での精密探索（ミクロレベル）
	pii searchInRegion(const Region& region, const vs& field, const vvd& prob, 
					   double robotLife, int depth, Timer& timer) {
		
		if(!timer) return {-1, -1};
		
		// 領域内の候補を取得
		vector<pair<double, pii>> candidates;
		for(int i = region.minR; i <= region.maxR && i < N; i++) {
			for(int j = region.minC; j <= region.maxC && j < N; j++) {
				if(field[i][j] == '.' && prob[i][j] > 1e-12) {
					candidates.push_back({prob[i][j], {i, j}});
				}
			}
		}
		
		if(candidates.empty()) return {-1, -1};
		
		// 確率の小さい順にソート（main.cpp戦略）
		sort(all(candidates));
		
		// 先読み探索
		double bestScore = -1e9;
		pii bestPos = {-1, -1};
		
		// 候補数を制限
		int maxCandidates = min((int)candidates.size(), depth == 1 ? 8 : 5);
		
		rep(i, maxCandidates) {
			if(!timer) break;
			
			auto [hitProb, pos] = candidates[i];
			auto [r, c] = pos;
			
			// この手の即座評価
			double immediateScore = robotLife - hitProb;
			
			// 先読きが可能な場合
			double futureScore = 0.0;
			if(depth > 1 && robotLife - hitProb > 1e-9) {
				// 次の状態を作成
				vs nextField = field;
				nextField[r][c] = '#';
				vvd nextProb = updateProbability(prob, nextField, N);
				nextProb[r][c] = 0.0;
				
				// 領域内で再帰探索
				pii nextMove = searchInRegion(region, nextField, nextProb, 
											  robotLife - hitProb, depth - 1, timer);
				
				if(nextMove.first != -1) {
					futureScore = (robotLife - hitProb) - nextProb[nextMove.first][nextMove.second];
				}
			}
			
			double totalScore = immediateScore + futureScore * 0.5;
			
			if(totalScore > bestScore) {
				bestScore = totalScore;
				bestPos = pos;
			}
		}
		
		return bestPos;
	}
	
public:
	HierarchicalDecision(int n) : N(n) {
		createRegions();
	}
	
	// マクロレベル意思決定：最重要領域を特定
	pii makeDecision(const vs& field, const vvd& prob, double robotLife, Timer& timer) {
		// 各領域の統計を更新
		for(auto& region : regions) {
			region.calculateStats(field, prob, N);
		}
		
		// 重要度でソート
		sort(all(regions), [](const Region& a, const Region& b) {
			return a.importance > b.importance;
		});
		
		// 時間に応じて探索深度を調整
		int searchDepth = timer.get() < 1000 ? 2 : 1;
		
		// 重要領域から順に探索
		for(const auto& region : regions) {
			if(!timer) break;
			
			if(region.emptyCells == 0) continue;
			
			pii result = searchInRegion(region, field, prob, robotLife, searchDepth, timer);
			
			if(result.first != -1) {
				debug("Selected region importance:", region.importance, 
					  "emptyCells:", region.emptyCells, "depth:", searchDepth);
				return result;
			}
		}
		
		// フォールバック：グローバル最小確率探索
		double minProb = 1e9;
		pii fallback = {-1, -1};
		
		rep(i, N) rep(j, N) {
			if(field[i][j] == '.' && prob[i][j] < minProb) {
				minProb = prob[i][j];
				fallback = {i, j};
			}
		}
		
		debug("Fallback to global minimum");
		return fallback;
	}
};

// 階層的意思決定戦略
vector<pii> strategy_hierarchical(const vs& field, int N, int M) {
	vector<pii> result;
	vs currentField = field;
	
	// 初期確率分布（main.cppと同じ）
	vvd prob(N, vd(N, 0.0));
	int emptyCount = N * N - M;
	rep(i, N) rep(j, N) {
		if(currentField[i][j] == '.') {
			prob[i][j] = 1.0 / emptyCount;
		}
	}
	
	double totalScore = 0.0;
	double robotLife = 1.0;
	int turn = 0;
	
	HierarchicalDecision hd(N);
	Timer localTimer(1900);
	
	while(true) {
		if(!localTimer) {
			debug("Time limit reached at turn", turn);
			break;
		}
		
		// 確率分布を更新（main.cppと同じ）
		prob = updateProbability(prob, currentField, N);
		
		// 階層的意思決定
		pii bestPos = hd.makeDecision(currentField, prob, robotLife, localTimer);
		
		if(bestPos.first == -1) break; // 空きマスがない
		
		// ロボットの生存確率を更新
		robotLife -= prob[bestPos.first][bestPos.second];
		totalScore += robotLife;
		
		debug("Turn:", turn, "Pos:", bestPos.first, bestPos.second, 
			  "RobotProb:", prob[bestPos.first][bestPos.second],
			  "Life:", robotLife, "Time:", localTimer.get());
		
		// 岩を設置
		prob[bestPos.first][bestPos.second] = 0.0;
		currentField[bestPos.first][bestPos.second] = '#';
		
		result.push_back(bestPos);
		turn++;
	}
	
	// 最終スコア計算（lib.rsと同じ正規化）
	double ub = (N * N - M - 1);
	double normalizedScore = (totalScore / ub) * 1e6;
	debug("Final Score:", (ll)round(normalizedScore));
	
	return result;
}

int main() {
	def(int,N,M);
	vs field(N);
	in(field);
	
	vector<pii> ans;
	// 階層的意思決定戦略を使用
	ans = strategy_hierarchical(field, N, M);

	for(auto [i, j] : ans) {
		out(i, j);
	}

	return 0;
}
