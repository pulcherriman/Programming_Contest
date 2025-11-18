/**
 * AHC050 - 先読み探索版
 * 2-3手先を読む改良版実装
 */

#ifdef _DEBUG
// #define _GLIBCXX_DEBUG 1
#else
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("inline")
#endif

#if defined(EVAL) || defined(ATCODER) || defined(_DEBUG)
#include <atcoder/all>
using namespace atcoder;
#endif
#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;

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

constexpr ll LINF=1ll<<60;
constexpr int INF=1<<30;
constexpr double EPS=(1e-14);
constexpr ll MOD=998244353ll;
constexpr long double PI=3.14159265358979323846;

template<class T,class...Args>auto vec(T x,int arg,Args...args){
	if constexpr(sizeof...(args)==0) return vector(arg,x);
	else return vector(arg,vec(x,args...));
}
template<class T>constexpr bool chmax(T&a, T b){return a<b?a=b,1:0;}
template<class T>constexpr bool chmin(T&a, T b){return a>b?a=b,1:0;}

namespace IO {
	template<typename T> concept Iterable = ranges::range<T> && !is_convertible_v<T, string_view>;
	template<typename T> concept RecursiveIterable = Iterable<T> && ranges::range<ranges::range_value_t<T>>;
	template<typename T> concept TupleLike = !Iterable<T> && requires(T a) {
		tuple_size<T>::value;
		get<0>(a);
		!is_convertible_v<T, string_view>;
	};

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

struct Mgr {
	static const int TLE = 2000;
	static inline Timer timer = Timer(TLE-70);
	Mgr() {
		ios_base::sync_with_stdio(0); cin.tie(0);
		cout<<fixed<<setprecision(11);
		cerr<<fixed<<setprecision(3);
	}	~Mgr(){
		cout<<flush;
		// debug_f(timer.get(), "ms")<<flush;  // 標準出力への時刻表示を無効化
	}
} _manager;

// ハイパーパラメータ設定（trial15の最良パラメータ）
static const double VERY_LOW_PROB_THRESHOLD = 7.402e-08;
static const double NEIGHBOR_WEIGHT = 0.005895;
static const double CORNER_BONUS_BASE = 0.042125;
static const double CORNER_BONUS_EXTRA = 0.020673;
static const double ADJACENT_EMPTY_PENALTY = 0.007263;
static const int ADJACENT_EMPTY_THRESHOLD = 3;
static const int MAX_CANDIDATES_DEPTH0 = 10;
static const int MAX_CANDIDATES_OTHERS = 6;
static const int MAIN_MAX_CANDIDATES = 10;
static const int DEPTH_THRESHOLD_HIGH = 120;
static const int DEPTH_THRESHOLD_MID = 80;
static const int DEPTH_THRESHOLD_LOW = 27;
static const int MAX_DEPTH_SMALL = 2;

// 確率分布の更新（1ステップ）- 最適化版
vvd updateProbability(const vvd& prob, const vs& field, int N) {
	vvd nextProb(N, vd(N, 0.0));
	vector<pii> dirs = {{-1,0}, {1,0}, {0,-1}, {0,1}};
	
	rep(i, N) rep(j, N) {
		double p = prob[i][j];
		if(p <= 1e-9) continue;
		
		for(auto [di, dj] : dirs) {
			int ni = i + di, nj = j + dj;
			// 範囲チェックを先に
			if(ni < 0 || ni >= N || nj < 0 || nj >= N || field[ni][nj] != '.') {
				// 境界または岩にぶつかった場合、元の位置に残る
				nextProb[i][j] += p * 0.25;
				continue;
			}
			
			// 移動できる場合、ぶつかるまで移動
			while(ni + di >= 0 && ni + di < N && nj + dj >= 0 && nj + dj < N && 
				  field[ni + di][nj + dj] == '.') {
				ni += di;
				nj += dj;
			}
			nextProb[ni][nj] += p * 0.25;
		}
	}
	return nextProb;
}

// 空きマスのリストを取得（確率付き）
vector<pair<pii, double>> getEmptyCellsWithProb(const vs& field, const vvd& prob, int N) {
	vector<pair<pii, double>> empty;
	rep(i, N) rep(j, N) {
		if(field[i][j] == '.') {
			empty.pb({{i, j}, (double)prob[i][j]});
		}
	}
	return empty;
}

// 軽量化された角形状評価（局所的チェックのみ）
double calculateLocalCornerBonus(const vs& field, int r, int c, int N) {
	// この位置周辺の角パターンのみをチェック（O(1)計算）
	double bonus = 0.0;
	
	// 隣接する2方向が岩の場合のボーナス（角を作らない位置）
	vector<pii> dirs = {{-1,0}, {1,0}, {0,-1}, {0,1}};
	int adjacentRocks = 0;
	
	for(auto [di, dj] : dirs) {
		int ni = r + di, nj = c + dj;
		if(ni >= 0 && ni < N && nj >= 0 && nj < N && field[ni][nj] == '#') {
			adjacentRocks++;
		}
	}
		// 隣接岩が多いほど角を作りにくい（良い）	if(adjacentRocks >= 2) bonus += CORNER_BONUS_BASE;
	if(adjacentRocks >= 3) bonus += CORNER_BONUS_EXTRA;
	
	return bonus;
}



// 改良された評価関数（確率ベース + 極低確率時のみ角対応）
double evaluateMove(const pii& pos, double hitProb, double robotLife, const vvd& prob, const vs& field, int N) {
	auto [r, c] = pos;
	
	// 基本スコア: 確率の小さいマスを優先（main.cpp戦略）
	double baseScore = -(hitProb); // 小さいほど良い
	
	// 周辺の確率密度をチェック
	double neighborSum = 0.0;
	vector<pii> dirs = {{-1,0}, {1,0}, {0,-1}, {0,1}};	for(auto [di, dj] : dirs) {
		int ni = r + di, nj = c + dj;
		if(ni >= 0 && ni < N && nj >= 0 && nj < N) {
			neighborSum += prob[ni][nj];
		}
	}
	
	// 統合評価関数（まずは基本戦略）
	double score = baseScore + neighborSum * NEIGHBOR_WEIGHT;
	
	// 確率がほぼ0の時のみ角パターンを考慮
	if(hitProb <= VERY_LOW_PROB_THRESHOLD) {
		// 極低確率の場合のみ、角を埋めることを考慮
		double cornerBonus = calculateLocalCornerBonus(field, r, c, N);
		score += cornerBonus;
	} else {
		// 通常確率の場合は、角を作りやすい場所を避ける
		int adjacentEmpty = 0;
		for(auto [di, dj] : dirs) {
			int ni = r + di, nj = c + dj;
			if(ni >= 0 && ni < N && nj >= 0 && nj < N && field[ni][nj] == '.') {
				adjacentEmpty++;
			}
		}
		// 隣接空きマスが多すぎる場合（新しい角を作りやすい）は軽くペナルティ
		if(adjacentEmpty >= ADJACENT_EMPTY_THRESHOLD) score -= ADJACENT_EMPTY_PENALTY;
	}
	
	return score;
}

// 先読き探索のための再帰関数
double lookaheadScore(vs field, vvd prob, double robotLife, int depth, int maxDepth, int N, Timer& timer) {
	// 時間制限チェック
	if(!timer) return 0.0;
	
	// 基底条件：深度制限に達した場合
	if(depth >= maxDepth) return 0.0;
	
	// 確率分布を更新
	vvd newProb = updateProbability(prob, field, N);
	
	// 空きマスを取得（改良版）
	auto emptyCells = getEmptyCellsWithProb(field, newProb, N);
	if(emptyCells.empty()) return 0.0;
		// 評価関数でソート
	sort(all(emptyCells), [&](const auto& a, const auto& b) {
		double scoreA = evaluateMove(a.first, a.second, robotLife, newProb, field, N);
		double scoreB = evaluateMove(b.first, b.second, robotLife, newProb, field, N);
		return scoreA > scoreB;
	});
	
	double bestScore = -1e9;
		// 候補数を制限（時間節約のため）- より少なく
	int maxCandidates = min((int)emptyCells.size(), depth == 0 ? MAX_CANDIDATES_DEPTH0 : MAX_CANDIDATES_OTHERS);
	
	rep(i, maxCandidates) {
		if(!timer) break;
		
		auto [pos, hitProb] = emptyCells[i];
		auto [r, c] = pos;
				// この手のスコア（改良版）
		double currentScore = evaluateMove(pos, hitProb, robotLife, newProb, field, N);
		
		// 次の状態を作成（効率化）
		char original = field[r][c];
		double originalProb = newProb[r][c];
		field[r][c] = '#';
		newProb[r][c] = 0.0;
		double newRobotLife = robotLife - hitProb;
		
		// 再帰的に先読み
		double futureScore = 0.0;
		if(newRobotLife > 1e-9 && depth + 1 < maxDepth) {
			futureScore = lookaheadScore(field, newProb, newRobotLife, depth + 1, maxDepth, N, timer);
		}
		
		// 状態を復元
		field[r][c] = original;
		newProb[r][c] = originalProb;
		
		double totalScore = currentScore + futureScore;
		chmax(bestScore, totalScore);
	}
	
	return bestScore;
}

// 先読きベースの戦略
vector<pii> strategy_lookahead(const vs& field, int N, int M) {
	vector<pii> result;
	vs currentField = field;
	
	// 初期確率分布
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
	
	Timer localTimer(2600); // 安全マージンを持たせる
	
	while(true) {

				// 確率分布を更新
		prob = updateProbability(prob, currentField, N);
		
		// 空きマスを取得（改良版）
		auto emptyCells = getEmptyCellsWithProb(currentField, prob, N);
		if(emptyCells.empty()) break;
		// 動的に先読み深度を調整（より保守的）
		int lookaheadDepth = 2;		if(emptyCells.size() > DEPTH_THRESHOLD_HIGH) lookaheadDepth = 1;
		else if(emptyCells.size() > DEPTH_THRESHOLD_MID) lookaheadDepth = 2;
		else if(emptyCells.size() < DEPTH_THRESHOLD_LOW) lookaheadDepth = MAX_DEPTH_SMALL;
		
		if(!localTimer) {
			lookaheadDepth = 0;
		}

		double bestScore = -1e9;
		pii bestPos = {-1, -1};
				// 評価関数で候補をソート（改良版）
		sort(all(emptyCells), [&](const auto& a, const auto& b) {
			double scoreA = evaluateMove(a.first, a.second, robotLife, prob, currentField, N);
			double scoreB = evaluateMove(b.first, b.second, robotLife, prob, currentField, N);
			return scoreA > scoreB;
		});
		// 上位候補のみを評価（時間節約）- より少なく
		int maxCandidates = min((int)emptyCells.size(), MAIN_MAX_CANDIDATES);
		
		rep(i, maxCandidates) {
			if(!localTimer) break;
			
			auto [pos, hitProb] = emptyCells[i];
			auto [r, c] = pos;
					// この手の評価スコア（改良版）
			double immediateScore = evaluateMove(pos, hitProb, robotLife, prob, currentField, N);
			
			// 先読きスコア（コピーを削減）
			vs newField = currentField;
			newField[r][c] = '#';
			vvd newProb = prob;
			newProb[r][c] = 0.0;
			double newRobotLife = robotLife - hitProb;
			
			double futureScore = 0.0;
			if(newRobotLife > 1e-9 && lookaheadDepth > 0) {
				futureScore = lookaheadScore(newField, newProb, newRobotLife, 1, lookaheadDepth, N, localTimer);
			}
			
			double totalScore = immediateScore + futureScore;
			
			if(totalScore > bestScore) {
				bestScore = totalScore;
				bestPos = pos;
			}
		}		if(bestPos.first == -1) {
			// フォールバック：最小確率の位置を選択（確率ベース + 極低確率時のみ角考慮）
			double bestFallbackScore = -1e9;
			rep(i, N) rep(j, N) {
				if(currentField[i][j] == '.') {
					// 基本は最小確率戦略
					double minProbScore = -prob[i][j];
					double fallbackScore = minProbScore;
							// 確率がほぼ0の時のみ角パターンを考慮
					if(prob[i][j] <= VERY_LOW_PROB_THRESHOLD) {
						double cornerBonus = calculateLocalCornerBonus(currentField, i, j, N);
						fallbackScore += cornerBonus;
					} else {
						// 通常確率の場合は角を作りやすい場所を避ける
						int adjacentEmpty = 0;
						vector<pii> dirs = {{-1,0}, {1,0}, {0,-1}, {0,1}};
						for(auto [di, dj] : dirs) {
							int ni = i + di, nj = j + dj;
							if(ni >= 0 && ni < N && nj >= 0 && nj < N && currentField[ni][nj] == '.') {
								adjacentEmpty++;
							}
						}
						if(adjacentEmpty >= ADJACENT_EMPTY_THRESHOLD) fallbackScore -= ADJACENT_EMPTY_PENALTY;
					}
					
					if(fallbackScore > bestFallbackScore) {
						bestFallbackScore = fallbackScore;
						bestPos = {i, j};
					}
				}
			}
		}
		
		if(bestPos.first == -1) break;
		
		// ロボットの生存確率を更新
		robotLife -= prob[bestPos.first][bestPos.second];
		totalScore += robotLife;
		debug("Turn:", turn, "Pos:", bestPos.first, bestPos.second, 
			  "Depth:", lookaheadDepth, "Candidates:", maxCandidates,
			  "RobotProb:", prob[bestPos.first][bestPos.second],
			  "Life:", robotLife, "Score:", bestScore);
		
		// 岩を設置
		prob[bestPos.first][bestPos.second] = 0.0;
		currentField[bestPos.first][bestPos.second] = '#';
		
		result.push_back(bestPos);
		turn++;
	}
	
	// 最終スコア計算
	double ub = (N * N - M - 1);
	double normalizedScore = (totalScore / ub) * 1e6;
	debug("Final Score:", (ll)round(normalizedScore));
	
	return result;
}

int main() {
	def(int, N, M);
	vs field(N);
	in(field);
	
	vector<pii> ans = strategy_lookahead(field, N, M);

	for(auto [i, j] : ans) {
		out(i, j);
	}

	return 0;
}
