/**
* C++23 Template @ AtCoder
* - official support library
*   - AC Library@1.5.1
*   - Boost@1.82.0
*   - GMP@6.2.1
*   - Eigen@3.4.0-2ubuntu2
* - compile option
*   g++-12 -std=gnu++2b -O2 -DONLINE_JUDGE -DATCODER \
*	  -Wall -Wextra \
*	  -mtune=native -march=native \
*	  -fconstexpr-depth=2147483647 -fconstexpr-loop-limit=2147483647 -fconstexpr-ops-limit=2147483647 \
*	  -I/opt/ac-library -I/opt/boost/gcc/include -L/opt/boost/gcc/lib \
*	  -o a.out Main.cpp \
*	  -lgmpxx -lgmp \
*	  -I/usr/include/eigen3
*/

#ifdef _DEBUG
// #define _GLIBCXX_DEBUG 1
// #undef _DEBUG
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
#include <bits/stdc++.h>
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
using vp=vector<pii>;
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
#define __RANGE(i,a,n) for(int i=((int)a);i<((int)n);++i)
#define __RREP(i,n) __RRANGE(i,0,n)
#define __RRANGE(i,a,n) for(int i=((int)(n)-1);i>=((int)a);--i)
#define sz(a) ((int)(a).size())
#define pb push_back
#define eb emplace_back

/*
 * Constants
 */
constexpr ll LINF=1ll<<60;
constexpr int INF=1000000;
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
template<class T>constexpr bool chmax(T&a, typename std::type_identity<T>::type b){return a<b?(a=b,true):false;}
template<class T>constexpr bool chmin(T&a, typename std::type_identity<T>::type b){return a>b?(a=b,true):false;}
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
	constexpr ostream&operator<<(ostream&os, TupleLike auto a){
		apply([&](auto&&...args){((os<<args<<' '),...);}, a);
		return os;
	}
	constexpr ostream&operator<<(ostream&os, Iterable auto a){
		if(!a.empty()){
			auto b=begin(a), e=end(a);
			os<<(*b++);
			while(b!=e){ os<<' '<<(*b++); }
		}
		return os;
	}
	constexpr ostream&operator<<(ostream&os, RecursiveIterable auto a){
		if(!a.empty()){
			auto b=begin(a), e=end(a);
			os<<(*b++);
			while(b!=e){ os<<'\n'<<(*b++); }
		}
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
	constexpr Random(const bool&isDeterministic):y(isDeterministic?2463534242:chrono::system_clock::now().time_since_epoch().count()){ }
	constexpr int operator()(int a,int b){return next()%(b-a)+a;}
	constexpr ll operator()(ll a,ll b){return (((ull)next())<<32|next())%(b-a)+a;}
	constexpr double operator()(double a,double b){
		// [a, b) の一様乱数
		double scale = (double)next() / (double)std::numeric_limits<uint_fast32_t>::max();
		return scale*(b - a) + a;
	}
private:
	result_type y;
	constexpr result_type next(){
		y ^= (y << 13);
		y ^= (y >> 17);
		y ^= (y << 5);
		return y;
	}
};

inline float t_sqrtF( const float& x )
{
	float xHalf = 0.5f * x;
	int   tmp   = 0x5f3700a0 - ( *(int*)&x >> 1 );
	float xRes  = *(float*)&tmp;
	xRes *= ( 1.5f - ( xHalf * xRes * xRes ) );
	return xRes * x;
}


#ifdef _DEBUG
Random rnd(1); // デバッグ時は固定シード
#else
Random rnd(0); // 本番用は可変シード
#endif

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
	float persentile() const { return (float)get()/((float)limit/ClocksPerMsec); }
};
void wait(const int&msec){Timer tm(msec); while(tm);}

struct Mgr {
	#ifdef _DEBUG
	static const int TLE = 2000; // ms
	#else
	static const int TLE = 2000; // ms
	#endif
	static inline Timer timer = Timer(TLE-150);
	Mgr() {
		ios_base::sync_with_stdio(0); cin.tie(0);
		cout<<fixed<<setprecision(0);
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
		static inline size_t hash_rnd = rnd(0,INF); // 適当に初期化
		static const inline size_t hash_value = 0x9e3779b9;
		template<class V, class P=remove_const_t<remove_reference_t<V>>>
		static size_t& do_hash(size_t&seed, V&v) {
			return seed ^= hash<P>{}(v) + hash_value + (seed<<6) + (seed>>2);
		}
	};

	template<class S, class T>
	struct hash<pair<S,T>> : public hash_base<pair<S,T>> {
		size_t operator()(pair<S,T> p) const {
			size_t seed= this->hash_rnd;
			this->do_hash(seed, p.first);
			this->do_hash(seed, p.second);
			return seed;
		}
	};

	template<class...Ts>
	struct hash<tuple<Ts...>> : public hash_base<tuple<Ts...>> {
		size_t operator()(tuple<Ts...> t) const {
			size_t seed= this->hash_rnd;
			apply([&](auto&&...args){
				((this->do_hash(seed, args)),...);
			}, t);
			return seed;
		}
	};
}


// 方向定数：上下左右（問題文の優先度順）
const int di[] = {-1, 1, 0, 0};
const int dj[] = {0, 0, -1, 1};

// ゲーム状態を管理する構造体
struct GameState {
    int N, ti, tj;
    vector<string> board;
    int pi, pj; // 冒険者の位置
    set<pair<int, int>> revealed;
    set<pair<int, int>> placed_trents;
    int turn;

    GameState() : turn(0) {}

    // 安全な戦略でトレント配置を決定
    vector<pair<int, int>> decideTreentPlacement() {
        vector<pair<int, int>> moves;

        // 花への距離が十分離れている場合のみトレント配置
        int dist_to_flower = abs(pi - ti) + abs(pj - tj);
        if (dist_to_flower > 5) {
            for (int dir = 0; dir < 4; dir++) {
                int ni = pi + di[dir];
                int nj = pj + dj[dir];

                if (ni >= 0 && ni < N && nj >= 0 && nj < N &&
                    revealed.find({ni, nj}) == revealed.end() &&
                    placed_trents.find({ni, nj}) == placed_trents.end() &&
                    board[ni][nj] == '.' &&
                    make_pair(ni, nj) != make_pair(ti, tj)) {

                    // 花への直線経路を塞がないようにチェック
                    bool blocks_direct_path = false;
                    if ((pi < ti && ni == pi + 1 && nj == pj) || // 下への移動を塞ぐ
                        (pi > ti && ni == pi - 1 && nj == pj) || // 上への移動を塞ぐ
                        (pj < tj && ni == pi && nj == pj + 1) || // 右への移動を塞ぐ
                        (pj > tj && ni == pi && nj == pj - 1)) { // 左への移動を塞ぐ
                        blocks_direct_path = true;
                    }

                    if (!blocks_direct_path) {
                        moves.push_back({ni, nj});
                        placed_trents.insert({ni, nj});
                        board[ni][nj] = 'T';
                        break; // 1個だけ
                    }
                }
            }
        }

        return moves;
    }
};

// 入出力インターフェース
class GameInterface {
public:
    virtual ~GameInterface() = default;
    virtual void initialize(GameState& state) = 0;
    virtual bool getAdventurerState(GameState& state, vector<pair<int, int>>& newly_revealed) = 0;
    virtual void outputTrentPlacements(const vector<pair<int, int>>& moves) = 0;
    virtual bool isGameFinished(const GameState& state) = 0;
};

// デバッグモード用の実装クラス
class DebugGameInterface : public GameInterface {
private:
    vector<pair<int, int>> q; // ランダム順序
    vector<vector<bool>> revealed_grid;

public:
    void initialize(GameState& state) override {
        // 初期入力
        cin >> state.N >> state.ti >> state.tj;

        state.board.resize(state.N);
        for (int i = 0; i < state.N; i++) {
            cin >> state.board[i];
        }

        // ランダム順序（q配列）を読み込み
        for (int i = 0; i < state.N * state.N - 1; i++) {
            int qi, qj;
            cin >> qi >> qj;
            q.push_back({qi, qj});
        }

        // 冒険者の初期状態
        state.pi = 0;
        state.pj = state.N / 2;
        revealed_grid = vector<vector<bool>>(state.N, vector<bool>(state.N, false));
        revealed_grid[0][state.N / 2] = true;
        state.revealed.insert({0, state.N / 2});

        // デバッグ用：初期状態を表示
        cerr << "=== Initial State ===" << endl;
        cerr << "Adventurer at (" << state.pi << ", " << state.pj << "), Target at (" << state.ti << ", " << state.tj << ")" << endl;
        printMap(state);
    }

    bool getAdventurerState(GameState& state, vector<pair<int, int>>& newly_revealed) override {
        if (state.pi == state.ti && state.pj == state.tj) {
            cerr << "Game finished in " << state.turn << " turns" << endl;
            return false; // ゲーム終了
        }

        cerr << "\n=== Turn " << state.turn << " ===" << endl;
        cerr << "Adventurer at (" << state.pi << ", " << state.pj << ")" << endl;

        // 冒険者の視界更新をシミュレート
        newly_revealed.clear();
        for (int dir = 0; dir < 4; dir++) {
            int ni = state.pi, nj = state.pj;
            while (true) {
                ni += di[dir];
                nj += dj[dir];

                if (ni < 0 || ni >= state.N || nj < 0 || nj >= state.N) break;

                if (!revealed_grid[ni][nj]) {
                    revealed_grid[ni][nj] = true;
                    state.revealed.insert({ni, nj});
                    newly_revealed.push_back({ni, nj});
                }

                if (state.board[ni][nj] == 'T') break;
            }
        }

        cerr << "Newly revealed: " << newly_revealed.size() << " cells" << endl;
        return true; // ゲーム継続
    }

    void outputTrentPlacements(const vector<pair<int, int>>& moves) override {
        // トレント配置のデバッグ出力
        if (moves.empty()) {
            cerr << "No trents placed" << endl;
        } else {
            cerr << "Placed trents at:";
            for (auto [x, y] : moves) {
                cerr << " (" << x << ", " << y << ")";
            }
            cerr << endl;
        }

        // 標準出力
        cout << moves.size();
        for (auto [x, y] : moves) {
            cout << " " << x << " " << y;
        }
        cout << endl;
    }

    bool isGameFinished(const GameState& state) override {
        return state.pi == state.ti && state.pj == state.tj;
    }

    // 冒険者の移動をシミュレート
    void simulateAdventurerMove(GameState& state) {
        // 花に向かって直進（簡単な実装）
        if (state.pi < state.ti) state.pi++;
        else if (state.pi > state.ti) state.pi--;
        else if (state.pj < state.tj) state.pj++;
        else if (state.pj > state.tj) state.pj--;

        cerr << "Adventurer moves to (" << state.pi << ", " << state.pj << ")" << endl;
        printMap(state);
    }

private:
    void printMap(const GameState& state) {
        cerr << "Current map:" << endl;
        for (int i = 0; i < state.N; i++) {
            for (int j = 0; j < state.N; j++) {
                if (i == state.pi && j == state.pj) cerr << 'A'; // 冒険者
                else if (i == state.ti && j == state.tj) cerr << 'F'; // 花
                else if (revealed_grid[i][j]) cerr << (state.board[i][j] == '.' ? '.' : 'T');
                else cerr << '?'; // 未確認
            }
            cerr << endl;
        }
    }
};

// 本番モード用の実装クラス
class ProductionGameInterface : public GameInterface {
public:
    void initialize(GameState& state) override {
        // 初期入力
        cin >> state.N >> state.ti >> state.tj;

        state.board.resize(state.N);
        for (int i = 0; i < state.N; i++) {
            cin >> state.board[i];
        }
    }

    bool getAdventurerState(GameState& state, vector<pair<int, int>>& newly_revealed) override {
        // 冒険者の位置
        cin >> state.pi >> state.pj;

        if (state.pi == state.ti && state.pj == state.tj) {
            return false; // ゲーム終了
        }

        // 新規確認マス
        int n;
        cin >> n;
        newly_revealed.clear();
        for (int i = 0; i < n; i++) {
            int x, y;
            cin >> x >> y;
            state.revealed.insert({x, y});
            newly_revealed.push_back({x, y});
        }

        return true; // ゲーム継続
    }

    void outputTrentPlacements(const vector<pair<int, int>>& moves) override {
        cout << moves.size();
        for (auto [x, y] : moves) {
            cout << " " << x << " " << y;
        }
        cout << endl;
        cout.flush();
    }

    bool isGameFinished(const GameState& state) override {
        return state.pi == state.ti && state.pj == state.tj;
    }
};

// 統一されたゲームループ
void runGame(GameInterface& interface) {
    GameState state;
    interface.initialize(state);

    vector<pair<int, int>> newly_revealed;

    while (true) {
        // 冒険者の状態を取得
        if (!interface.getAdventurerState(state, newly_revealed)) {
            break; // ゲーム終了
        }

        // アルゴリズム：トレント配置を決定
        auto moves = state.decideTreentPlacement();

        // 出力
        interface.outputTrentPlacements(moves);

        // デバッグモードの場合は冒険者の移動をシミュレート
        #ifdef _DEBUG
        auto* debugInterface = dynamic_cast<DebugGameInterface*>(&interface);
        if (debugInterface) {
            debugInterface->simulateAdventurerMove(state);
        }
        #endif

        state.turn++;

        // 安全のためのターン制限
        if (state.turn > 1000) {
            cerr << "Turn limit exceeded" << endl;
            break;
        }
    }
}

#ifdef _DEBUG
int main() {
    DebugGameInterface interface;
    runGame(interface);
    return 0;
}

#else
int main() {
    ProductionGameInterface interface;
    runGame(interface);
    return 0;
}
#endif