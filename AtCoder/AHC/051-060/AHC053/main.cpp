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


// 問題の定数
const int N = 500;
const int M = 50;
const ll L = 1000000000000000LL - 2000000000000LL;  // 10^15 - 2*10^12
const ll U = 1000000000000000LL + 2000000000000LL;  // 10^15 + 2*10^12

// B値を生成（デバッグ環境用）
vector<ll> generate_B_values() {
    vector<ll> B(M);
    rep(i, M) {
        B[i] = rnd(L, U + 1);  // [L, U]の範囲で乱数生成
    }
    sort(all(B));  // 昇順にソート
    return B;
}

ll calc_error(ll S_value, ll B_value) {
	return S_value > B_value ? (S_value - B_value) : (B_value - S_value);
}

// 評価関数: 総誤差を計算
ll evaluate_assignment(const vector<ll>& A, const vector<ll>& B, const vector<int>& X) {
    vector<ll> S(M, 0);  // 各山の合計
    rep(i, N) {
        if(X[i] > 0) {  // 0は廃棄
            S[X[i] - 1] += A[i];
        }
    }

    ll total_error = 0;
    rep(j, M) {
        total_error += calc_error(S[j], B[j]);
    }
    return total_error;
}

// 貪欲法による初期割り当て
vector<int> greedy_assignment(const vector<ll>& A, const vector<ll>& B) {
    vector<int> X(N, 0);  // 0で初期化（すべて廃棄状態）
    vector<ll> S(M, 0);   // 各山の現在の合計

	rep(i,M) {
		X[i] = i+1;
	}
    return X;
}

// 近傍操作: 単一移動は全探索、交換はランダム
vector<int> generate_neighbor(const vector<int>& X, const vector<ll>& A, const vector<ll>& B) {
    auto new_X = X;

    // 現在の各山の合計を計算
    vector<ll> S(M, 0);
    rep(i, N) {
        if(X[i] > 0) {
            S[X[i] - 1] += A[i];
        }
    }

    // 操作選択：40%で単一移動、30%で交換、30%でDP山再構築
    int operation = rnd(0, 10);
    if(operation < 4) {
        // 操作1: 単一カードの最適移動（全探索）
		int card = rnd(50, N);
        int current_pile = X[card];

        // 最も改善される移動先を全探索
        int best_pile = current_pile;  // デフォルトは現在の位置
        ll max_improvement = 0;

        rep(new_pile, M + 1) {  // 0=廃棄, 1~M=山番号
            if(new_pile == current_pile) continue;

            ll improvement = 0;

            // 元の山からの改善
            if(current_pile > 0) {
                ll old_error = calc_error(S[current_pile - 1], B[current_pile - 1]);
                ll new_error = calc_error(S[current_pile - 1] - A[card], B[current_pile - 1]);
                improvement += old_error - new_error;
				// debug(S[current_pile - 1], B[current_pile - 1], A[card], old_error, new_error);
            }

            // 移動先の山への影響
            if(new_pile > 0) {
                ll old_error = calc_error(S[new_pile - 1], B[new_pile - 1]);
                ll new_error = calc_error(S[new_pile - 1] + A[card], B[new_pile - 1]);
                improvement += old_error - new_error;
            }

			// debug("Card", card, "from", current_pile, "to", new_pile, "improvement", improvement, "current pile sum", S[current_pile - 1], "new pile sum", (new_pile > 0 ? S[new_pile - 1] : -1));

            if(improvement > max_improvement) {
                max_improvement = improvement;
                best_pile = new_pile;
            }
        }

        new_X[card] = best_pile;
    } else if(operation < 7) {
        // 操作2: 2つのカードの交換
        int card1 = rnd(50, N);
        int card2 = rnd(50, N);
        if(card1 != card2) {
            swap(new_X[card1], new_X[card2]);
        }
    } else {
        // 操作3: 2山破壊＋貪欲振り分け
        int pile1 = rnd(1, M + 1);
        int pile2 = rnd(1, M + 1);
        while(pile1 == pile2) pile2 = rnd(1, M + 1);

        // 2つの山のカードと廃棄カードを収集
        vector<int> collected_cards;
        rep(i, N) {
            if(X[i] == pile1 || X[i] == pile2 || X[i] == 0) {  // 廃棄カードも含める
                collected_cards.push_back(i);
                new_X[i] = 0;  // 一旦廃棄
            }
        }

        // カードを値の大きい順にソート
        sort(collected_cards.begin(), collected_cards.end(), [&](int a, int b) {
            return A[a] > A[b];
        });

        // 現在の各山の状態を再計算
        vector<ll> current_sums(M, 0);
        rep(i, N) {
            if(new_X[i] > 0) {
                current_sums[new_X[i] - 1] += A[i];
            }
        }

        // 大きいカードから順に最適な山に配置
        for(int card : collected_cards) {
            int best_pile = 0;  // デフォルトは廃棄
            ll best_error = LINF;

            // 各山に配置した場合のエラーを計算
            rep(pile, M) {
                ll new_sum = current_sums[pile] + A[card];
                if(new_sum <= B[pile]) {  // 超過しない場合のみ考慮
                    ll error = calc_error(new_sum, B[pile]);
                    if(error < best_error) {
                        best_error = error;
                        best_pile = pile + 1;
                    }
                }
            }

            // 最適な山に配置
            new_X[card] = best_pile;
            if(best_pile > 0) {
                current_sums[best_pile - 1] += A[card];
            }
        }
    }

    return new_X;
}

// 山登り法による最適化
vector<int> hill_climbing(vector<ll>& A, const vector<ll>& B, vector<int> initial_X, int time_limit_ms) {
    auto current_X = initial_X;
    auto best_X = current_X;
    ll current_score = evaluate_assignment(A, B, current_X);
    ll best_score = current_score;

    int iteration = 0;
    Timer opt_timer(time_limit_ms);

    while(opt_timer) {
        // 近傍解を生成
        auto new_X = generate_neighbor(current_X, A, B);
        ll new_score = evaluate_assignment(A, B, new_X);

        // 改善解のみ受容（山登り法）
        if(new_score < current_score) {
            current_X = new_X;
            current_score = new_score;

            if(current_score < best_score) {
                best_X = current_X;
                best_score = current_score;
                debug("New best score:", best_score, "at iteration", iteration);
            }
        }

        iteration++;

        if(iteration % 10000 == 0) {
            debug("Iteration:", iteration, "Current:", current_score, "Best:", best_score);
        }
    }

    debug("Hill climbing completed. Iterations:", iteration, "Best score:", best_score);
    return best_X;
}

// メイン関数
int main() {
    def(int, n, m);
    def(ll, l, u);

#ifdef _DEBUG
    // デバッグ環境では問題設定の値を使用
    n = N; m = M; l = L; u = U;
    debug("Debug mode: using predefined values");
    debug("N =", n, "M =", m, "L =", l, "U =", u);
#endif

    // A値を決定（妥当な乱数生成）
    vector<ll> A(n);
    ll avg_B = 0;

#ifdef _DEBUG
    // デバッグ時は仮のB値で平均計算
    vector<ll> temp_B = generate_B_values();
    for(ll b : temp_B) avg_B += b;
    avg_B /= m;
#else
    // 本番では大体の予想値を使用
    avg_B = (l + u) / 2;
#endif

    // A値のマージンベース分布戦略
    ll LARGE_MARGIN = 100000000000LL;  // 5*10^11
    const int MEDIUM_COUNT = 3;

    int large_count = 75;                     // M枚 (50枚)
    int medium_count = 125; // M*MEDIUM_COUNT枚 (150枚)
    int small_count = n - large_count - medium_count; // 残り (250枚)

    int idx = 0;

    // 大分布: [L-LARGE_MARGIN, U-LARGE_MARGIN]をM等分
    rep(i, large_count) {
        ll range = (u - LARGE_MARGIN) - (l - LARGE_MARGIN);
        ll base_value = (l - LARGE_MARGIN) + (ll)i * range / (large_count - 1);
        A[idx++] = max(L, base_value);
    }

    // 中分布: [LARGE_MARGIN/MEDIUM_COUNT - LARGE_MARGIN/(MEDIUM_COUNT*2),
    //          LARGE_MARGIN/MEDIUM_COUNT + LARGE_MARGIN/(MEDIUM_COUNT*2)]
    ll medium_center = LARGE_MARGIN / MEDIUM_COUNT;  // 約1.63×10^13
    ll medium_half_width = LARGE_MARGIN / (MEDIUM_COUNT * 2);  // 約8.14×10^12
    rep(i, medium_count) {
        ll medium_value = medium_center + rnd(-medium_half_width, medium_half_width + 1);
        A[idx++] = max(1LL, medium_value);
    }

    // 小分布: 合計不足量/300近辺の乱数として設定
    // 分析結果: 平均不足量約2,123億、中央値約1,563億
    // 期待される合計不足量を推定
    ll expected_total_deficit = 212264193215LL * 50; // 約10.6兆
    ll small_unit_base = expected_total_deficit / 200; // 約354億

    // 5つのグループに分けて生成（各60個）
    rep(group, 5) {
        ll group_base = small_unit_base;
        for(int div = 0; div < group; div++) {
            group_base /= 10;  // 10, 100, 1000, 10000で順次割る
        }

        rep(i, 60) {
            // group_baseの50%～150%の範囲でランダム
            ll min_val = group_base / 2;
            ll max_val = group_base * 3 / 2;
            A[idx++] = max(1LL, rnd(min_val, max_val + 1));
        }
    }

    debug("Average B:", avg_B);
    debug("Margin-based A distribution:");
    debug("  LARGE_MARGIN:", LARGE_MARGIN, "(5*10^11)");
    debug("  Large units (", large_count, " cards): [", l - LARGE_MARGIN, ", ", u - LARGE_MARGIN, "]");
    debug("  Medium units (", medium_count, " cards):", medium_center, "±", medium_half_width);
    debug("  Small units (", small_count, " cards): 5 groups of 60 each:");
    debug("    Group 1: ~", small_unit_base, "±50%");
    debug("    Group 2: ~", small_unit_base/10, "±50%");
    debug("    Group 3: ~", small_unit_base/100, "±50%");
    debug("    Group 4: ~", small_unit_base/1000, "±50%");
    debug("    Group 5: ~", small_unit_base/10000, "±50%");
    debug("A values range:", *min_element(all(A)), "to", *max_element(all(A)));

    // A値を出力
    rep(i, n) {
        cout << A[i];
        if(i < n - 1) cout << " ";
    }
    out_f("");  // 改行 + flush

    // B値を入力または生成
    vector<ll> B(m);
#ifdef _DEBUG
    B = generate_B_values();
    debug("Generated B values:", B);
#else
    rep(i, m) {
        cin >> B[i];
    }
#endif

    // 最適化プロセス
    debug("Starting optimization...");

    // 1. 貪欲法で初期解を生成
    debug("Generating initial solution with greedy algorithm...");
    vector<int> X = greedy_assignment(A, B);
    ll initial_score = evaluate_assignment(A, B, X);
    debug("Initial greedy score:", initial_score);

    // 2. 山登り法で改善
    debug("Optimizing with hill climbing...");
    X = hill_climbing(A, B, X, 1800);  // 1.5秒で最適化
    ll final_score = evaluate_assignment(A, B, X);
    debug("Final optimized score:", final_score);
    debug("Improvement:", initial_score - final_score);

    // X値を出力
    rep(i, n) {
        cout << X[i];
        if(i < n - 1) cout << " ";
    }
    out_f("");  // 改行 + flush

#ifdef _DEBUG
    // デバッグ情報を出力
    vector<ll> S(m, 0);  // 各山の合計
    int used_cards = 0, discarded_cards = 0;

    rep(i, n) {
        if(X[i] > 0) {  // 0は廃棄
            S[X[i] - 1] += A[i];
            used_cards++;
        } else {
            discarded_cards++;
        }
    }

    debug_f("Cards used:", used_cards, ", discarded:", discarded_cards);
    debug_f("Discard rate:", (double)discarded_cards / n * 100, "%");

    ll total_error = 0;
    rep(j, m) {
        total_error += abs(S[j] - B[j]);
        if(j < 10) {  // 最初の10山だけ詳細表示
            debug_f("Pile", j + 1, ": sum =", S[j], ", target =", B[j], ", error =", abs(S[j] - B[j]));
        }
    }
    debug_f("Total error:", total_error);

    double score = round((20.0 - log10(1.0 + total_error)) * 5e7);
    debug_f("Final Score:", score);

    // 統計情報
    ll max_error = 0, min_error = LINF;
    rep(j, m) {
        ll error = abs(S[j] - B[j]);
        chmax(max_error, error);
        chmin(min_error, error);
    }
    debug_f("Error range: [", min_error, ",", max_error, "]");
#endif

    return 0;
}