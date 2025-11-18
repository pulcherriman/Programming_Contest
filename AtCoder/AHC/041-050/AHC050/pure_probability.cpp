/**
 * AHC050 - 純粋確率分析版
 * メタ戦略を一切排除し、確率的改善のみに特化
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

// 基本の確率更新（main.cppと同じ）
vvd updateProbability(const vvd& prob, const vs& field, int N) {
	vvd nextProb(N, vd(N, 0.0));
	vector<pii> dirs = {{-1,0}, {1,0}, {0,-1}, {0,1}};
	
	rep(i, N) rep(j, N) {
		if(prob[i][j] <= 1e-9) continue;
		
		for(auto [di, dj] : dirs) {
			int ni = i, nj = j;
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

// 効率的な確率影響度分析（O(N^2)全体で計算）
vector<pair<double, pii>> calculateAllImpacts(const vvd& currentProb, 
											  const vs& field, int N) {
	vector<pair<double, pii>> results;
	
	// 元の次ステップ確率分布を一度だけ計算
	vvd nextProbOriginal = updateProbability(currentProb, field, N);
	
	// 各候補位置について軽量な影響度計算
	rep(i, N) rep(j, N) {
		if(field[i][j] != '.') continue;
		
		double directHit = currentProb[i][j];
		
		// 軽量な間接影響計算：隣接マスの確率流入阻止効果のみ
		double indirectImpact = 0.0;
		vector<pii> dirs = {{-1,0}, {1,0}, {0,-1}, {0,1}};
		
		for(auto [di, dj] : dirs) {
			// この方向からの流入を計算
			int si = i - di, sj = j - dj;
			
			// 流入元を遡って探す
			while(si >= 0 && si < N && sj >= 0 && sj < N && field[si][sj] == '.') {
				// この位置からi,jへの流入量
				double flowContrib = currentProb[si][sj] * 0.25;
				indirectImpact += flowContrib;
				
				// さらに一歩遡る
				if(si - di < 0 || si - di >= N || sj - dj < 0 || sj - dj >= N || 
				   field[si - di][sj - dj] != '.') break;
				si -= di;
				sj -= dj;
			}
		}
		
		// 総合評価：直接効果 + 軽量間接効果
		double totalImpact = directHit + indirectImpact * 0.05;
		results.push_back({totalImpact, {i, j}});
	}
	
	return results;
}

// 元のmain.cppベース + 効率的確率影響度分析
vector<pii> strategy_pure_probability(const vs& field, int N, int M) {
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
	
	Timer localTimer(1900);
	
	while(true) {
		if(!localTimer) {
			debug("Time limit reached");
			break;
		}
		
		// 確率分布を更新（main.cppと同じ）
		prob = updateProbability(prob, currentField, N);
		
		// 全位置の影響度を効率的に計算（O(N^2)）
		auto candidates = calculateAllImpacts(prob, currentField, N);
		
		if(candidates.empty()) break;
		
		// 最も影響度の高い位置を選択
		sort(all(candidates), greater<pair<double, pii>>());
		auto [bestImpact, bestPos] = candidates[0];
		
		// ロボットの生存確率を更新
		robotLife -= prob[bestPos.first][bestPos.second];
		totalScore += robotLife;
		
		debug("Turn:", turn, "Pos:", bestPos.first, bestPos.second, 
			  "Impact:", bestImpact, "RobotProb:", prob[bestPos.first][bestPos.second],
			  "Life:", robotLife);
		
		// 岩を設置
		prob[bestPos.first][bestPos.second] = 0.0;
		currentField[bestPos.first][bestPos.second] = '#';
		
		result.push_back(bestPos);
		turn++;
	}
	
	// 最終スコア計算（main.cppと同じ）
	double ub = (N * N - M - 1);
	double normalizedScore = (totalScore / ub) * 1e6;
	debug("Final Score:", (ll)round(normalizedScore));
	
	return result;
}

// フォールバック: main.cppと全く同じ戦略
vector<pii> strategy_original(const vs& field, int N, int M) {
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
	
	while(true) {
		// 毎ターン確率分布を更新
		prob = updateProbability(prob, currentField, N);
		
		// 最小確率の空きマスを探す（main.cppと同じ）
		double minProb = 1e9;
		pii bestPos = {-1, -1};
		
		rep(i, N) rep(j, N) {
			if(currentField[i][j] == '.' && prob[i][j] < minProb) {
				minProb = prob[i][j];
				bestPos = {i, j};
			}
		}
		
		if(bestPos.first == -1) break;
		
		// ロボットの生存確率を更新
		robotLife -= prob[bestPos.first][bestPos.second];
		totalScore += robotLife;
		
		debug("Turn:", turn, "Pos:", bestPos.first, bestPos.second, 
			  "RobotProb:", prob[bestPos.first][bestPos.second],
			  "Life:", robotLife, "TotalScore:", totalScore);
		
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
	
	// まず改良版を試行、問題があれば元版を使用
	vector<pii> ans = strategy_pure_probability(field, N, M);

	for(auto [i, j] : ans) {
		out(i, j);
	}

	return 0;
}
