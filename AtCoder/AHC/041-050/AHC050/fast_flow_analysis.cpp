/**
 * AHC050 - 高速化版確率フロー解析
 * main.cppをベースに、差分計算と軽量評価で高速化
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

// 高速化されたフロー評価クラス
class FastFlowAnalyzer {
private:
	int N;
	vs field;
	vvd prob;
	
	// キャッシュされた隣接リスト（停止位置を事前計算）
	vvi stopPositions; // [i*N+j][dir] = 停止位置のインデックス
	
	void precomputeStopPositions() {
		stopPositions = vvi(N*N, vi(4, -1));
		vector<pii> dirs = {{-1,0}, {1,0}, {0,-1}, {0,1}};
		
		rep(i, N) rep(j, N) {
			if(field[i][j] != '.') continue;
			
			rep(d, 4) {
				auto [di, dj] = dirs[d];
				int ni = i, nj = j;
				
				// 岩にぶつかるまで移動
				while(ni + di >= 0 && ni + di < N && nj + dj >= 0 && nj + dj < N && 
					  field[ni + di][nj + dj] == '.') {
					ni += di;
					nj += dj;
				}
				
				stopPositions[i*N + j][d] = ni * N + nj;
			}
		}
	}
	
public:
	FastFlowAnalyzer(const vs& f) : N(f.size()), field(f), prob(N, vd(N, 0.0)) {
		precomputeStopPositions();
		
		// 初期確率分布
		int emptyCount = 0;
		rep(i, N) rep(j, N) {
			if(field[i][j] == '.') emptyCount++;
		}
		rep(i, N) rep(j, N) {
			if(field[i][j] == '.') {
				prob[i][j] = 1.0 / emptyCount;
			}
		}
	}
	
	// 確率分布の高速更新（事前計算済みの停止位置を使用）
	void updateProbability() {
		vvd nextProb(N, vd(N, 0.0));
		
		rep(i, N) rep(j, N) {
			if(prob[i][j] <= 1e-9) continue;
			
			rep(d, 4) {
				int stopIdx = stopPositions[i*N + j][d];
				if(stopIdx != -1) {
					int ni = stopIdx / N, nj = stopIdx % N;
					nextProb[ni][nj] += prob[i][j] * 0.25;
				}
			}
		}
		
		prob = nextProb;
	}
	
	// 岩を設置（フィールドと確率を更新、停止位置も再計算）
	void placeRock(int r, int c) {
		field[r][c] = '#';
		prob[r][c] = 0.0;
		
		// 影響される位置の停止位置のみを再計算（差分更新）
		vector<pii> dirs = {{-1,0}, {1,0}, {0,-1}, {0,1}};
		
		// この位置に向かって移動してくる可能性のある範囲を更新
		rep(d, 4) {
			auto [di, dj] = dirs[d];
			
			// 逆方向に進んで影響範囲を特定
			int i = r - di, j = c - dj;
			while(i >= 0 && i < N && j >= 0 && j < N && field[i][j] == '.') {
				// この位置からの移動先を再計算
				rep(dd, 4) {
					auto [ddi, ddj] = dirs[dd];
					int ni = i, nj = j;
					
					while(ni + ddi >= 0 && ni + ddi < N && nj + ddj >= 0 && nj + ddj < N && 
						  field[ni + ddi][nj + ddj] == '.') {
						ni += ddi;
						nj += ddj;
					}
					
					stopPositions[i*N + j][dd] = ni * N + nj;
				}
				
				i -= di;
				j -= dj;
			}
		}
	}
		// 軽量フロー評価（main.cppの戦略に準拠：確率の低いマスを優先）
	double evaluateFlowEfficiency(int r, int c) {
		// 基本確率（小さいほど良い→負にして大きいほど良いスコアに変換）
		double hitProb = prob[r][c];
		double baseScore = -hitProb; // 確率が小さいほど良いスコア
		
		// 局所的な隣接影響度（O(1)計算）
		double neighborInfluence = 0.0;
		vector<pii> dirs = {{-1,0}, {1,0}, {0,-1}, {0,1}};
		for(auto [di, dj] : dirs) {
			int ni = r + di, nj = c + dj;
			if(ni >= 0 && ni < N && nj >= 0 && nj < N && field[ni][nj] == '.') {
				neighborInfluence += prob[ni][nj];
			}
		}
		
		// 流入遮断効果（この位置に流入してくる確率の総和）
		double inflow = 0.0;
		rep(i, N) rep(j, N) {
			if(prob[i][j] <= 1e-9) continue;
			
			rep(d, 4) {
				int stopIdx = stopPositions[i*N + j][d];
				if(stopIdx == r*N + c) {
					inflow += prob[i][j] * 0.25;
				}
			}
		}
		
		// 統合評価（確率の小さいマスを優先）
		return baseScore + neighborInfluence * 0.01 + inflow * 0.05;
	}
		// 現在の確率を取得（フィールドが空きマスの場合のみ）
	double getProbability(int r, int c) const {
		if(field[r][c] != '.') return 0.0;
		return prob[r][c];
	}
	
	// フィールドの状態を確認
	bool isEmpty(int r, int c) const {
		return field[r][c] == '.';
	}
	
	// 簡単なアトラクター分析（上位確率の位置）
	vector<pii> getTopProbabilityPositions(int count = 5) {
		vector<pair<double, pii>> candidates;
		rep(i, N) rep(j, N) {
			if(field[i][j] == '.' && prob[i][j] > 1e-9) {
				candidates.push_back({prob[i][j], {i, j}});
			}
		}
		
		sort(rall(candidates));
		
		vector<pii> result;
		rep(i, min(count, (int)candidates.size())) {
			result.push_back(candidates[i].second);
		}
		
		return result;
	}
};

// 高速化版確率フロー解析戦略
vector<pii> strategy_fast_flow_analysis(const vs& field, int N, int M) {
	vector<pii> result;
	
	FastFlowAnalyzer analyzer(field);
	
	double totalScore = 0.0;
	double robotLife = 1.0;
	int turn = 0;
	
	while(true) {
		// 確率分布を更新（高速化済み）
		analyzer.updateProbability();
				// フロー効率性で最適な手を決定（確率の小さいマスを優先）
		double bestScore = -1e9;
		pii bestPos = {-1, -1};
				rep(i, N) rep(j, N) {
			// 空きマスかつ確率が0でない場合
			if(analyzer.isEmpty(i, j) && analyzer.getProbability(i, j) > 1e-12) {
				double score = analyzer.evaluateFlowEfficiency(i, j);
				if(score > bestScore) {
					bestScore = score;
					bestPos = {i, j};
				}
			}
		}
		
		// フォールバック：純粋に最小確率の空きマスを選択（main.cpp戦略）
		if(bestPos.first == -1) {
			double minProb = 1e9;
			rep(i, N) rep(j, N) {
				if(analyzer.isEmpty(i, j)) {
					double p = analyzer.getProbability(i, j);
					if(p < minProb) {
						minProb = p;
						bestPos = {i, j};
					}
				}
			}
		}
		
		if(bestPos.first == -1) break; // 空きマスがない
		
		// ロボットの生存確率を更新
		double robotProb = analyzer.getProbability(bestPos.first, bestPos.second);
		robotLife -= robotProb;
		totalScore += robotLife;
		
		// 軽量アトラクター分析（30ターンごとに削減）
		if(turn % 30 == 0) {
			auto attractors = analyzer.getTopProbabilityPositions(5);
			debug("Turn:", turn, "TopPositions:", attractors.size(), 
				  "FlowScore:", bestScore);
		}
		
		debug("Turn:", turn, "Pos:", bestPos.first, bestPos.second, 
			  "RobotProb:", robotProb,
			  "Life:", robotLife, "FlowScore:", bestScore);
		
		// 岩を設置（差分更新）
		analyzer.placeRock(bestPos.first, bestPos.second);
		
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
	// 高速化版確率フロー解析戦略を使用
	ans = strategy_fast_flow_analysis(field, N, M);

	for(auto [i, j] : ans) {
		out(i, j);
	}

	return 0;
}
