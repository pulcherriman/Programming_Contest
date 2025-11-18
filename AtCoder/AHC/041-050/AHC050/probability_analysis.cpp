/**
 * AHC050 - 確率分析版
 * 純粋な確率的分析による改善（メタ戦略なし）
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

// 確率変化量分析: 各位置に岩を置いた場合の確率分布変化を計算
double calculateProbabilityImpact(const pii& pos, const vvd& prob, const vs& field, int N) {
	auto [r, c] = pos;
	
	// この位置に岩を置いた状態を作成
	vs testField = field;
	testField[r][c] = '#';
	
	// 元の確率分布での次ステップ
	vvd originalNext = updateProbability(prob, field, N);
	
	// 岩を置いた場合の次ステップ
	vvd modifiedNext = updateProbability(prob, testField, N);
	
	// 確率分布の変化量を計算（総確率の減少量）
	double totalReduction = 0.0;
	rep(i, N) rep(j, N) {
		if(field[i][j] == '.') {
			double reduction = originalNext[i][j] - modifiedNext[i][j];
			if(reduction > 0) {
				totalReduction += reduction;
			}
		}
	}
	
	return totalReduction;
}

// 確率集中度分析: 確率分布の偏りを測定
double calculateProbabilityConcentration(const vvd& prob, const vs& field, int N) {
	double entropy = 0.0;
	double totalProb = 0.0;
	
	rep(i, N) rep(j, N) {
		if(field[i][j] == '.' && prob[i][j] > 1e-9) {
			totalProb += prob[i][j];
			entropy -= prob[i][j] * log(prob[i][j]);
		}
	}
	
	// エントロピーが低いほど集中している
	return -entropy;
}

// 隣接効果分析: 周辺への確率流入阻止効果
double calculateNeighborBlocking(const pii& pos, const vvd& prob, const vs& field, int N) {
	auto [r, c] = pos;
	double blockingEffect = 0.0;
	vector<pii> dirs = {{-1,0}, {1,0}, {0,-1}, {0,1}};
	
	// 隣接マスからこの位置への確率流入を計算
	for(auto [di, dj] : dirs) {
		for(int dist = 1; dist <= 3; dist++) {
			int si = r - di * dist, sj = c - dj * dist;
			if(si < 0 || si >= N || sj < 0 || sj >= N || field[si][sj] != '.') break;
			
			// この位置からの移動をシミュレート
			int ni = si + di, nj = sj + dj;
			while(ni >= 0 && ni < N && nj >= 0 && nj < N && field[ni][nj] == '.') {
				if(ni == r && nj == c) {
					// この位置で止まる確率を加算
					blockingEffect += prob[si][sj] * 0.25;
					break;
				}
				ni += di;
				nj += dj;
			}
		}
	}
	
	return blockingEffect;
}

// 改良された評価関数（純粋な確率分析のみ）
double evaluateProbabilisticMove(const pii& pos, const vvd& prob, const vs& field, 
								 double robotLife, int N) {
	auto [r, c] = pos;
	double hitProb = prob[r][c];
	
	// 基本スコア
	double baseScore = robotLife - hitProb;
	
	// 確率変化量による効果
	double impactScore = calculateProbabilityImpact(pos, prob, field, N);
	
	// 隣接効果による確率阻止
	double blockingScore = calculateNeighborBlocking(pos, prob, field, N);
	
	// 局所的確率密度（周辺の確率和）
	double localDensity = 0.0;
	vector<pii> dirs = {{-1,0}, {1,0}, {0,-1}, {0,1}, {-1,-1}, {-1,1}, {1,-1}, {1,1}};
	for(auto [di, dj] : dirs) {
		int ni = r + di, nj = c + dj;
		if(ni >= 0 && ni < N && nj >= 0 && nj < N && field[ni][nj] == '.') {
			localDensity += prob[ni][nj];
		}
	}
	
	// 重み付け（実験的に調整）
	return baseScore + impactScore * 0.3 + blockingScore * 0.4 + localDensity * 0.02;
}

// 確率分析戦略
vector<pii> strategy_probability_analysis(const vs& field, int N, int M) {
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
	
	Timer localTimer(1900);
	
	while(true) {
		if(!localTimer) {
			debug("Time limit reached");
			break;
		}
		
		// 確率分布を更新
		prob = updateProbability(prob, currentField, N);
		
		// 候補位置の評価
		vector<pair<double, pii>> candidates;
		rep(i, N) rep(j, N) {
			if(currentField[i][j] == '.') {
				double score = evaluateProbabilisticMove({i, j}, prob, currentField, robotLife, N);
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
	
	vector<pii> ans = strategy_probability_analysis(field, N, M);

	for(auto [i, j] : ans) {
		out(i, j);
	}

	return 0;
}
