/**
 * AHC050 - 高度戦略版
 * 確率分布の動的特性活用 + メタ戦略 + フロー解析
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

// 簡化されたIO
namespace IO {
	void Yn(bool f) { cout << (f?"Yes":"No") << '\n'; }
	
	template<typename T>
	istream& operator>>(istream& is, vector<T>& v) {
		for(auto& x : v) is >> x;
		return is;
	}
	
	template<class T, class...Ts> constexpr istream& gargs(istream&is, T&&t, Ts&&...args) {
		return ((is>>t)>>...>>args);
	}
	template<typename...S>auto&in(S&...s){return gargs(cin, s...);}
	#define def(t,...) t __VA_ARGS__; in(__VA_ARGS__)
	
	#ifdef _DEBUG
	template<class...Ts> void debug(Ts...args) {
		((cerr << args << ' '), ...);
		cerr << '\n';
	}
	#else
	#define debug(...) if(false)debug(__VA_ARGS__)
	#endif
	
	template<class...Ts> void out(Ts...args) {
		((cout << args << ' '), ...);
		cout << '\n';
	}
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
	}
	~Mgr(){
		cout<<flush;
		debug("Execution time:", timer.get(), "ms");
	}
} _manager;

// 確率分布の更新（1ステップ）
vvd updateProbability(const vvd& prob, const vs& field, int N) {
	vvd nextProb(N, vd(N, 0.0));
	vector<pii> dirs = {{-1,0}, {1,0}, {0,-1}, {0,1}};
	
	rep(i, N) rep(j, N) {
		double p = prob[i][j];
		if(p <= 1e-9) continue;
		
		for(auto [di, dj] : dirs) {
			int ni = i + di, nj = j + dj;
			if(ni < 0 || ni >= N || nj < 0 || nj >= N || field[ni][nj] != '.') {
				nextProb[i][j] += p * 0.25;
				continue;
			}
			
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

// 確率フロー解析: 各位置への確率流入量を計算
vvd calculateProbabilityFlow(const vvd& prob, const vs& field, int N) {
	vvd flow(N, vd(N, 0.0));
	vector<pii> dirs = {{-1,0}, {1,0}, {0,-1}, {0,1}};
	
	rep(i, N) rep(j, N) {
		double p = prob[i][j];
		if(p <= 1e-9) continue;
		
		for(auto [di, dj] : dirs) {
			int ni = i + di, nj = j + dj;
			if(ni < 0 || ni >= N || nj < 0 || nj >= N || field[ni][nj] != '.') {
				continue;
			}
			
			// 移動先を計算
			while(ni + di >= 0 && ni + di < N && nj + dj >= 0 && nj + dj < N && 
				  field[ni + di][nj + dj] == '.') {
				ni += di;
				nj += dj;
			}
			
			// この位置への流入量を記録
			flow[ni][nj] += p * 0.25;
		}
	}
	return flow;
}

// 長期確率分布予測（数ステップ先を計算）
vvd predictLongTermProbability(const vvd& prob, const vs& field, int N, int steps) {
	vvd current = prob;
	for(int step = 0; step < steps; step++) {
		current = updateProbability(current, field, N);
	}
	return current;
}

// アトラクター分析: 確率が集中しやすい領域を特定
vector<pii> findProbabilityAttractors(const vs& field, int N, int steps = 5) {
	// 初期確率分布
	vvd prob(N, vd(N, 0.0));
	int emptyCount = 0;
	rep(i, N) rep(j, N) {
		if(field[i][j] == '.') emptyCount++;
	}
	rep(i, N) rep(j, N) {
		if(field[i][j] == '.') {
			prob[i][j] = 1.0 / emptyCount;
		}
	}
	
	// 数ステップ進めて安定化
	for(int step = 0; step < steps; step++) {
		prob = updateProbability(prob, field, N);
	}
	
	// 高確率領域を特定
	vector<pair<double, pii>> candidates;
	rep(i, N) rep(j, N) {
		if(field[i][j] == '.' && prob[i][j] > 0) {
			candidates.push_back({prob[i][j], {i, j}});
		}
	}
	
	sort(all(candidates), greater<pair<double, pii>>());
	
	vector<pii> attractors;
	for(auto [p, pos] : candidates) {
		if(attractors.size() >= 10) break; // 上位10個
		attractors.push_back(pos);
	}
	
	return attractors;
}

// 戦略的評価関数（複数要素を統合）
double evaluateAdvancedMove(const pii& pos, const vvd& prob, const vvd& flow, 
							const vs& field, double robotLife, int turn, int N) {
	auto [r, c] = pos;
	double hitProb = prob[r][c];
	
	// 基本スコア
	double baseScore = robotLife - hitProb;
	
	// フロー効果: この位置への確率流入を阻止する効果
	double flowBlockingScore = flow[r][c] * 0.5;
	
	// 戦略的位置価値
	double strategicValue = 0.0;
	
	// 端に近い位置は戦略的価値が高い
	int edgeDistance = min({r, N-1-r, c, N-1-c});
	if(edgeDistance <= 2) {
		strategicValue += 0.01 * (3 - edgeDistance);
	}
	
	// 中央付近の制御価値
	int centerDistance = abs(r - N/2) + abs(c - N/2);
	if(centerDistance <= N/4) {
		strategicValue += 0.005 * (N/4 - centerDistance);
	}
	
	// 周辺への影響度
	double neighborInfluence = 0.0;
	vector<pii> dirs = {{-1,0}, {1,0}, {0,-1}, {0,1}};
	for(auto [di, dj] : dirs) {
		int ni = r + di, nj = c + dj;
		if(ni >= 0 && ni < N && nj >= 0 && nj < N && field[ni][nj] == '.') {
			neighborInfluence += prob[ni][nj];
		}
	}
	strategicValue += neighborInfluence * 0.02;
	
	// ゲーム段階による重み調整
	double phaseMultiplier = 1.0;
	if(turn < 20) {
		// 序盤: 戦略的価値を重視
		phaseMultiplier = 1.5;
		strategicValue *= 2.0;
	} else if(turn > 60) {
		// 終盤: 即効性を重視
		baseScore *= 1.2;
		strategicValue *= 0.7;
	}
	
	return (baseScore + flowBlockingScore + strategicValue) * phaseMultiplier;
}

// 高度戦略版メイン関数
vector<pii> strategy_advanced(const vs& field, int N, int M) {
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
	
	// アトラクター分析
	auto attractors = findProbabilityAttractors(currentField, N);
	debug("Found", attractors.size(), "probability attractors");
	
	double totalScore = 0.0;
	double robotLife = 1.0;
	int turn = 0;
	
	Timer localTimer(2600);
	
	while(true) {
		if(!localTimer) {
			debug("Time limit reached");
			break;
		}
		
		// 確率分布を更新
		prob = updateProbability(prob, currentField, N);
		
		// フロー解析
		vvd flow = calculateProbabilityFlow(prob, currentField, N);
		
		// 長期予測（3ステップ先）
		vvd longTermProb = predictLongTermProbability(prob, currentField, N, 3);
		
		// 候補位置の評価
		vector<pair<double, pii>> candidates;
		rep(i, N) rep(j, N) {
			if(currentField[i][j] == '.') {
				double score = evaluateAdvancedMove({i, j}, prob, flow, currentField, robotLife, turn, N);
				
				// 長期予測も考慮
				double longTermBonus = (prob[i][j] - longTermProb[i][j]) * 0.1;
				score += longTermBonus;
				
				// アトラクター近傍ボーナス
				for(auto [ar, ac] : attractors) {
					int dist = abs(i - ar) + abs(j - ac);
					if(dist <= 2) {
						score += 0.005 * (3 - dist);
					}
				}
				
				candidates.push_back({score, {i, j}});
			}
		}
		
		if(candidates.empty()) break;
		
		// 最高評価の位置を選択
		sort(all(candidates), greater<pair<double, pii>>());
		auto [bestScore, bestPos] = candidates[0];
		
		// ロボットの生存確率を更新
		robotLife -= prob[bestPos.first][bestPos.second];
		totalScore += robotLife;
		
		debug("Turn:", turn, "Pos:", bestPos.first, bestPos.second, 
			  "Score:", bestScore, "RobotProb:", prob[bestPos.first][bestPos.second],
			  "Life:", robotLife);
		
		// 岩を設置
		prob[bestPos.first][bestPos.second] = 0.0;
		currentField[bestPos.first][bestPos.second] = '#';
		
		result.push_back(bestPos);
		turn++;
		
		// アトラクター再計算（定期的に）
		if(turn % 20 == 0) {
			attractors = findProbabilityAttractors(currentField, N);
		}
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
	
	vector<pii> ans = strategy_advanced(field, N, M);

	for(auto [i, j] : ans) {
		out(i, j);
	}

	return 0;
}
