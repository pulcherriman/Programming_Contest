/**
 * AHC050 - Beam Search Implementation (based on main.cpp)
 * ビーム幅とビーム深度を制限した制限ビームサーチ実装
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

// 状態を表現する構造体
struct State {
	vs field;                    // 現在のフィールド状態
	vector<pii> moves;           // これまでの手順
	vvd prob;                    // 現在の確率分布
	double totalScore;           // 累積スコア
	double robotLife;            // ロボット生存確率
	int turn;                    // 現在のターン
	
	State() = default;
	State(const vs& f, int N, int M) : field(f), totalScore(0.0), robotLife(1.0), turn(0) {
		prob = vvd(N, vd(N, 0.0));
		int emptyCount = N * N - M;
		rep(i, N) rep(j, N) {
			if(field[i][j] == '.') {
				prob[i][j] = 1.0 / emptyCount;
			}
		}
	}
	
	// main.cppと同じ確率更新
	void updateProbability(int N) {
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
		prob = nextProb;
	}
	
	// 手を実行して新しい状態を生成
	State makeMove(const pii& pos, int N) const {
		State newState = *this;
		
		// 確率更新
		newState.updateProbability(N);
		
		// スコア更新
		double robotProb = newState.prob[pos.first][pos.second];
		newState.robotLife -= robotProb;
		newState.totalScore += newState.robotLife;
		
		// 岩を設置
		newState.prob[pos.first][pos.second] = 0.0;
		newState.field[pos.first][pos.second] = '#';
		newState.moves.push_back(pos);
		newState.turn++;
		
		return newState;
	}
	
	// 候補手を取得（確率の低い順にソート）
	vector<pii> getCandidates(int N, int maxCandidates = -1) const {
		vector<pair<double, pii>> candidates;
		
		rep(i, N) rep(j, N) {
			if(field[i][j] == '.') {
				candidates.push_back({prob[i][j], {i, j}});
			}
		}
		
		sort(all(candidates));
		
		vector<pii> result;
		int limit = (maxCandidates == -1) ? candidates.size() : min((int)candidates.size(), maxCandidates);
		rep(i, limit) {
			result.push_back(candidates[i].second);
		}
		
		return result;
	}
	
	// 現在の状態の評価値（total scoreベース）
	double evaluate() const {
		return totalScore;
	}
	
	// 終了判定
	bool isFinished(int N) const {
		rep(i, N) rep(j, N) {
			if(field[i][j] == '.') return false;
		}
		return true;
	}
};

// ビームサーチクラス
class BeamSearch {
public:
	int N, M;
	int beamWidth;
	int maxDepth;
	Timer timer;
	
	BeamSearch(int n, int m) : N(n), M(m), timer(1970) {
		// 動的なパラメータ調整
		if(N <= 10) {
			beamWidth = 8;
			maxDepth = min(15, N*N - M);
		} else if(N <= 20) {
			beamWidth = 6;
			maxDepth = min(12, N*N - M);
		} else {
			beamWidth = 4;
			maxDepth = min(10, N*N - M);
		}
		
		debug("BeamSearch params: width=", beamWidth, "depth=", maxDepth);
	}
	
	// ビームサーチ実行
	vector<pii> search(const vs& field) {
		// 初期状態
		vector<State> beam = {State(field, N, M)};
		State* bestComplete = nullptr;
		double bestScore = -1;
		
		rep(depth, maxDepth) {
			if(!timer || beam.empty()) break;
			
			vector<State> nextBeam;
			
			for(const auto& state : beam) {
				if(!timer) break;
				
				if(state.isFinished(N)) {
					if(!bestComplete || state.evaluate() > bestScore) {
						bestComplete = const_cast<State*>(&state);
						bestScore = state.evaluate();
					}
					continue;
				}
				
				// 候補手を取得（制限付き）
				int maxCandidates = (depth < 5) ? 8 : (depth < 10) ? 6 : 4;
				auto candidates = state.getCandidates(N, maxCandidates);
				
				for(const auto& move : candidates) {
					if(!timer) break;
					
					State newState = state.makeMove(move, N);
					nextBeam.push_back(newState);
				}
			}
			
			// ビーム幅で制限
			if(nextBeam.size() > beamWidth) {
				sort(all(nextBeam), [](const State& a, const State& b) {
					return a.evaluate() > b.evaluate();
				});
				nextBeam.resize(beamWidth);
			}
			
			beam = nextBeam;
			
			debug("Depth:", depth, "BeamSize:", beam.size(), 
				  "BestInBeam:", beam.empty() ? 0.0 : beam[0].evaluate(),
				  "Time:", timer.get());
		}
		
		// 最適解を選択
		State* best = bestComplete;
		if(!best && !beam.empty()) {
			best = &beam[0];
			for(auto& state : beam) {
				if(state.evaluate() > best->evaluate()) {
					best = &state;
				}
			}
		}
		
		if(!best) {
			debug("No solution found, falling back to greedy");
			return fallbackGreedy(field);
		}
		
		// 残りの手をgreedyで補完
		vector<pii> result = best->moves;
		if(!best->isFinished(N)) {
			debug("Completing with greedy from turn", best->turn);
			auto remaining = completeWithGreedy(*best);
			result.insert(result.end(), all(remaining));
		}
		
		debug("Final solution length:", result.size());
		return result;
	}
	
private:
	// 時間切れ時のGreedy fallback
	vector<pii> fallbackGreedy(const vs& field) {
		State state(field, N, M);
		vector<pii> result;
		
		while(!state.isFinished(N)) {
			state.updateProbability(N);
			
			auto candidates = state.getCandidates(N, 1);
			if(candidates.empty()) break;
			
			pii move = candidates[0];
			state = state.makeMove(move, N);
			result.push_back(move);
		}
		
		return result;
	}
	
	// Greedyで解を補完
	vector<pii> completeWithGreedy(State state) {
		vector<pii> result;
		
		while(!state.isFinished(N)) {
			state.updateProbability(N);
			
			auto candidates = state.getCandidates(N, 1);
			if(candidates.empty()) break;
			
			pii move = candidates[0];
			state = state.makeMove(move, N);
			result.push_back(move);
		}		
		return result;
	}
};

int main() {
	def(int,N,M);
	vs field(N);
	in(field);
	
	BeamSearch bs(N, M);
	vector<pii> ans = bs.search(field);
	
	for(auto [i, j] : ans) {
		out(i, j);
	}
	
	return 0;
}
