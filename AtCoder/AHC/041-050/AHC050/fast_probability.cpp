/**
 * AHC050 - 軽量確率分析版
 * 高速で効果的な確率分析のみに特化
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

// 高速確率分布更新
vvd updateProbabilityFast(const vvd& prob, const vs& field, int N) {
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

// 軽量確率影響度分析
double calculateImpactScore(const pii& pos, const vvd& prob, const vs& field, int N, double robotLife) {
	auto [r, c] = pos;
	double hitProb = prob[r][c];
	
	// 基本スコア
	double baseScore = robotLife - hitProb;
	
	// 周辺影響度（軽量版）
	double neighborImpact = 0.0;
	vector<pii> dirs = {{-1,0}, {1,0}, {0,-1}, {0,1}, {-1,-1}, {-1,1}, {1,-1}, {1,1}};
	
	for(auto [di, dj] : dirs) {
		int ni = r + di, nj = c + dj;
		if(ni >= 0 && ni < N && nj >= 0 && nj < N && field[ni][nj] == '.') {
			neighborImpact += prob[ni][nj];
		}
	}
	
	// 確率密度効果（隣接マスのみ）
	double densityEffect = neighborImpact * 0.01;
	
	// フィールド中央付近の微調整（軽量）
	int distFromCenter = abs(r - N/2) + abs(c - N/2);
	double centerBonus = max(0.0, (N/2 - distFromCenter) * 0.001);
	
	return baseScore + densityEffect + centerBonus;
}

// メイン戦略（軽量確率分析版）
vector<pii> strategy_fast_probability(const vs& field, int N, int M) {
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
		prob = updateProbabilityFast(prob, currentField, N);
		
		// 最適位置を高速探索
		double bestScore = -1e9;
		pii bestPos = {-1, -1};
		
		rep(i, N) rep(j, N) {
			if(currentField[i][j] == '.') {
				double score = calculateImpactScore({i, j}, prob, currentField, N, robotLife);
				if(score > bestScore) {
					bestScore = score;
					bestPos = {i, j};
				}
			}
		}
		
		if(bestPos.first == -1) break;
		
		// ロボットの生存確率を更新
		double hitProb = prob[bestPos.first][bestPos.second];
		robotLife -= hitProb;
		totalScore += robotLife;
		
		debug("Turn:", turn, "Pos:", bestPos.first, bestPos.second, 
			  "Score:", bestScore, "RobotProb:", hitProb, "Life:", robotLife);
		
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
	
	vector<pii> ans = strategy_fast_probability(field, N, M);

	for(auto [i, j] : ans) {
		out(i, j);
	}

	return 0;
}
