/**
 * C++23 Template @ AtCoder
 * - official support library
 *   - AC Library@1.5.1
 *   - Boost@1.82.0
 *   - GMP@6.2.1
 *   - Eigen@3.4.0-2ubuntu2
 * - compile option
 *   ```
 *     g++-12 -std=gnu++2b -O2 -DONLINE_JUDGE -DATCODER \
 *      -Wall -Wextra \
 *      -mtune=native -march=native \
 *      -fconstexpr-depth=2147483647 -fconstexpr-loop-limit=2147483647 -fconstexpr-ops-limit=2147483647 \
 *      -I/opt/ac-library -I/opt/boost/gcc/include -L/opt/boost/gcc/lib \
 *      -o a.out Main.cpp \
 *      -lgmpxx -lgmp \
 *      -I/usr/include/eigen3
 *   ```
 * - compiler information: https://docs.google.com/spreadsheets/d/1HXyOXt5bKwhKWXruzUvfMFHQtBxfZQ0047W7VVObnXI/edit#gid=408033513&range=F43
 */

#ifdef _DEBUG
// #define _GLIBCXX_DEBUG 1
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("inline")
#else
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("inline")
#endif

/* 
 * Include Headers
 */
#if defined(EVAL) || defined(ATCODER) || defined(_DEBUG)
// #include <atcoder/all>
// using namespace atcoder;
#endif
#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
// #include <boost/unordered_map.hpp>
using namespace std;

/*
 * Additional Type Definition
 */
using ll=long long;
using ull=unsigned long long;
using vb=vector<bool>;
using vvb=vector<vb>;
using vi=vector<int>;
using vvi=vector<vi>;
using pii=pair<int,int>;
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
constexpr int INF=1<<30;

/*
 * Utilities
 */
template<class T>constexpr bool chmax(T&a, type_identity_t<T> b){return a<b?a=b,1:0;}
template<class T>constexpr bool chmin(T&a, type_identity_t<T> b){return a>b?a=b,1:0;}
template<class S>S sum(vector<S>&a){return accumulate(all(a),S());}
template<class S>S max(vector<S>&a){return *max_element(all(a));}
template<class S>S min(vector<S>&a){return *min_element(all(a));}


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
	#define def(t,...) t __VA_ARGS__; in(__VA_ARGS__);
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
} Random(1);

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
	static const int TLE = 20000;
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

// カスタム構造体 Point の定義
struct Point {
    int x;
    int y;

    // コンストラクタ
    Point(int x_ = 0, int y_ = 0) : x(x_), y(y_) {}

    // 加算演算子のオーバーロード
    Point operator+(const Point& other) const {
        return Point(x + other.x, y + other.y);
    }

    // 減算演算子のオーバーロード
    Point operator-(const Point& other) const {
        return Point(x - other.x, y - other.y);
    }

    // 等価性の比較（unordered_set 用）
    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
};

// std::hash<Point> の特化（最適化版）
namespace std {
    template <>
    struct hash<Point> {
        size_t operator()(const Point& p) const noexcept {
            // ビットシフト演算を使用してハッシュを計算
            return (static_cast<size_t>(p.x) << 5) | static_cast<size_t>(p.y);
        }
    };
}

// シミュレーションの各状態を表す構造体
struct State {
	Point root_diff;              // ルート頂点の相対座標
	vector<int> rotations;        // 各頂点（頂点1からV-1）の回転操作
	vector<bool> grab_diffs;      // 各葉のアームの状態を切り替えるかどうか

	// デフォルトコンストラクタ
	State() {}
};

constexpr int COORD_MIN = 0;
constexpr int COORD_MAX = 30;
constexpr int TARGET_MAX = 450;

// Robot クラスの定義
struct Robot {
	// 頂点の構造体
	struct Vertex {
		int parent;            // 親頂点のインデックス
		int length;
		int rotation;
		vector<int> children;  // 子頂点のインデックス
	};

	int V;                        // 頂点数
	vector<Vertex> vertices;      // 頂点のリスト
	vector<int> leaves;           // 葉（子を持たない頂点）のリスト
	vector<bool> is_leaf;         // 各頂点が葉かどうかを示す
	vector<bool> is_grab;         // 各葉が物をつかんでいるかどうか
	Point root_pos;
	static constexpr int ANGLES[] = {3, 1, 0};

	Robot() {}

	// コンストラクタ：頂点数と頂点データを受け取り、ツリーを構築
	Robot(int num_vertices, Point init_root_pos, const vector<tuple<int, int>> &vertex_data) {
		V = num_vertices;
		root_pos = init_root_pos;
		vertices.resize(V, Vertex{-1, 0, 0, {}});
		is_leaf.assign(V, true);  // 初期状態では全てが葉と仮定
		is_grab.assign(V, false);

		// 頂点1からV-1までの親と相対座標を設定
		for (int i = 1; i < V; ++i) {
			int parent = get<0>(vertex_data[i - 1]);
			int x = get<1>(vertex_data[i - 1]);
			vertices[i].parent = parent;
			vertices[i].length = x;
			vertices[i].rotation = 0;
			vertices[parent].children.push_back(i);
			is_leaf[parent] = false;  // 親は葉ではない
		}

		// 葉のリストを取得
		for (int i = 1; i < V; ++i) {
			if (is_leaf[i]) {
				leaves.push_back(i);
			}
		}
	}

	// 非葉ノードの全回転を列挙して最適な状態を探す関数
	State find_best_state(const Point &root_diff, const HashSet<Point> &takoyakis, const HashSet<Point> &spots) {
		State best_state;
		best_state.root_diff = root_diff;
		best_state.rotations.assign(V, 0);
		best_state.grab_diffs.assign(V, false);
		int max_match_count = -1;

		// 非葉ノードのリストを作成
		vector<int> non_leaf_nodes;
		for (int i = 1; i < V; ++i) {
			if (!is_leaf[i]) non_leaf_nodes.push_back(i);
		}

		// 非葉ノードの全回転パターンを列挙
		int non_leaf_count = non_leaf_nodes.size();
		int total_patterns = pow(3, non_leaf_count);

		for (int pattern = 0; pattern < total_patterns; ++pattern) {
			State current_state;
			current_state.root_diff = root_diff;
			current_state.rotations.assign(V, 0);
			current_state.grab_diffs.assign(V, false);

			// パターンに応じて非葉ノードの回転を設定
			int temp = pattern;
			for (int idx = 0; idx < non_leaf_count; ++idx) {
				int op = temp % 3;
				temp /= 3;
				int node = non_leaf_nodes[idx];
				current_state.rotations[node] = ANGLES[op];
			}

			// 葉ノードの可能な位置を計算
			vector<vector<Point>> leaf_possible_positions(V);
			vector<vector<int>> leaf_possible_rotations(V);
			calculate_leaf_positions(current_state, leaf_possible_positions, leaf_possible_rotations);

			// マッチングの構築
			int match_count = perform_matching(current_state, leaf_possible_positions, leaf_possible_rotations, takoyakis, spots, max_match_count);

			// 最適な状態を更新
			if (match_count > max_match_count) {
				max_match_count = match_count;
				best_state = current_state;
			}
		}

		return best_state;
	}

	// 葉ノードの可能な位置を計算する関数
	void calculate_leaf_positions(const State &state, vector<vector<Point>> &leaf_positions, vector<vector<int>> &leaf_rotations) {
		vector<Point> abs_pos(V);
		vector<int> cumulative_rotations(V, 0);
		abs_pos[0] = root_pos + state.root_diff;

		rep(i,1,V){
			// 頂点の絶対座標と累積回転を得る
			int parent = vertices[i].parent;
			int rot = state.rotations[i];

			// 葉でない場合、stateにすでに回転が入っている
			if(!is_leaf[i]) {
				cumulative_rotations[i] = (cumulative_rotations[parent] + rot) % 4;
				abs_pos[i] = abs_pos[parent] + rotate_point(vertices[i].length, vertices[i].rotation + cumulative_rotations[i]);
				continue;
			}

			// 葉の場合、全ての回転を試す
			for(const auto angle: ANGLES) {
				cumulative_rotations[i] = (cumulative_rotations[parent] + angle) % 4;
				abs_pos[i] = abs_pos[parent] + rotate_point(vertices[i].length, vertices[i].rotation + cumulative_rotations[i]);
				if(abs_pos[i].x < COORD_MIN || abs_pos[i].x >= COORD_MAX || abs_pos[i].y < COORD_MIN || abs_pos[i].y >= COORD_MAX) continue;
				leaf_positions[i].push_back(abs_pos[i]);
				leaf_rotations[i].push_back(angle);
			}
		}
	}

	// マッチングを行う関数
	int perform_matching(State &state, const vector<vector<Point>> &leaf_positions, const vector<vector<int>> &leaf_rotations, const HashSet<Point> &takoyakis, const HashSet<Point> &spots, int max_match_count) {
		// たこ焼とスポット、個別に処理する
		// is_grabがtrueの場合はたこ焼を持っているのでスポットとマッチング

		int match_count = 0;

		{
			vector<int> shrinked_leaves;
			vector<Point> shrinked_leaf_positions;
			vector<int> shrinked_leaf_rotations;
			int enable_count = match_count;
			rep(i,leaves.size()) {
				if(!is_grab[leaves[i]]) {
					int leaf = leaves[i];
					bool found = false;
					rep(j,leaf_positions[leaf].size()) {
						if(takoyakis.contains(leaf_positions[leaf][j])) {
							shrinked_leaves.push_back(leaf);
							shrinked_leaf_positions.push_back(leaf_positions[leaf][j]);
							shrinked_leaf_rotations.push_back(leaf_rotations[leaf][j]);
							enable_count++;
							found = true;
							break;
						}
					}
				} else {
					// spotの方が全部enableであると仮定
					enable_count++;
				}
			}

			if(enable_count <= max_match_count) return match_count;

			// 葉ノードとたこ焼きの位置のマッチング
			auto result = solve_biparate_matching_single(shrinked_leaf_positions);
			match_count += result.size();

			// idx番目のshrinked_leafを、座標pに持って行くことに成功した
			for(const auto &[p, idx]: result) {
				state.rotations[shrinked_leaves[idx]] = shrinked_leaf_rotations[idx];
				state.grab_diffs[shrinked_leaves[idx]] = true;
			}
		}


		{
			// debug_f(" spots matching");
			vector<int> shrinked_leaves;
			vector<Point> shrinked_leaf_positions;
			vector<int> shrinked_leaf_rotations;
			int enable_count = match_count;
			rep(i,leaves.size()) {
				if(is_grab[leaves[i]]) {
					int leaf = leaves[i];
					bool found = false;
					rep(j,leaf_positions[leaf].size()) {
						if(spots.contains(leaf_positions[leaf][j])) {
							shrinked_leaves.push_back(leaf);
							shrinked_leaf_positions.push_back(leaf_positions[leaf][j]);
							shrinked_leaf_rotations.push_back(leaf_rotations[leaf][j]);
							enable_count++;
							found = true;
							break;
						}
					}
				}
			}
			if(enable_count <= max_match_count) return match_count;

			// 葉ノードとスポットの位置のマッチング
			auto result = solve_biparate_matching_single(shrinked_leaf_positions);
			match_count += result.size();

			// idx番目のshrinked_leafを、座標pに持って行くことに成功した
			for(const auto &[p, idx]: result) {
				state.rotations[shrinked_leaves[idx]] = shrinked_leaf_rotations[idx];
				state.grab_diffs[shrinked_leaves[idx]] = true;
			}
		}


		return match_count;
	}

	// 各葉ノードが一つの候補位置を持つ場合のマッチング関数
	vector<pair<Point, int>> solve_biparate_matching_single(const vector<Point>& leaf_positions) {
		int n = leaf_positions.size();

		// ターゲットノード（右側のノード）のインデックスを構築
		unordered_map<Point, int> point_to_index; // Pointをキーに使用
		int m = 0;
		for (const auto& p : leaf_positions) {
			if (point_to_index.find(p) == point_to_index.end()) {
				point_to_index[p] = m++;
			}
		}

		// グラフの構築
		vector<vector<int>> graph(n);
		for (int u = 0; u < n; ++u) {
			int v = point_to_index[leaf_positions[u]];
			graph[u].push_back(v);
		}

		vector<int> match_to(m, -1);
		vector<bool> used(n, false);

		// マッチングを貪欲に構築
		for (int u = 0; u < n; ++u) {
			int v = graph[u][0];
			if (match_to[v] == -1) {
				match_to[v] = u;
			}
		}

		// マッチング結果を収集
		vector<pair<Point, int>> match;
		match.reserve(n);
		for (int v = 0; v < m; ++v) {
			int u = match_to[v];
			if (u != -1) {
				match.emplace_back(leaf_positions[u], u);
			}
		}

		return match;
	}

	// rotate_point関数の最適化
	inline Point rotate_point(const int length, int rot) const {
		rot = (rot % 4 + 4) % 4;
		switch (rot) {
			case 0:
				return Point(length, 0);
			case 1:
				return Point(0, length);
			case 2:
				return Point(-length, 0);
			case 3:
				return Point(0, -length);
			default:
				return Point(0, 0);  // 予期しない回転値
		}
	}

	// Stateが示す差分を、robotに適用する
	// robot.vertices[i].rel_pos を更新する
	void apply_state(const State &state, HashSet<Point> &takoyakis, HashSet<Point> &spots) {
		// 各頂点の絶対座標を保持する配列
		vector<Point> abs_pos(V, Point(0, 0));
		abs_pos[0] = root_pos + state.root_diff;

		// 各頂点の累積回転を保持する配列
		vector<int> cumulative_rotations(V, 0);
		cumulative_rotations[0] = 0;  // vertex0 has no rotation

		// BFSを使用してツリーをレベル順に走査
		queue<int> q;
		q.push(0);  // ルート頂点から開始

		while (!q.empty()) {
			int current = q.front();
			q.pop();

			for (auto &child : vertices[current].children) {
				int op = state.rotations[child];
				int delta = op;
				cumulative_rotations[child] = (cumulative_rotations[current] + delta) % 4;
				Point rotated_rel = rotate_point(vertices[child].length, vertices[child].rotation + cumulative_rotations[child]);
				abs_pos[child] = abs_pos[current] + rotated_rel;
				q.push(child);
			}
		}

		// 各頂点の絶対座標を更新
		for (int i = 0; i < V; ++i) {
			vertices[i].rotation = (vertices[i].rotation + cumulative_rotations[i] + 4) % 4;
		}

		root_pos = abs_pos[0];

		// 各葉の状態を更新
		for (int i = 0; i < V; i++)
			if (is_leaf[i]) {
				is_grab[i] = is_grab[i] ^ state.grab_diffs[i];
				if (state.grab_diffs[i]) {
					if (is_grab[i]) {  // 持った
						takoyakis.erase(abs_pos[i]);
					} else {
						spots.erase(abs_pos[i]);
					}
				}
			}
	}

	// dfsしても1つも進展しない場合に確実に進展させる手を打つ
	State fail_safe(int N, const HashSet<Point> &takoyakis, const HashSet<Point> &spots) {
		auto abs_pos = get_current_abs_pos();
		bool is_grabbing_mode = false;

		Point diff;
		// いずれかの頂点がたこ焼をつかんでいる場合、その頂点を一番近いスポットに持っていく
		rep(i, V) if (is_grab[i]) {
			is_grabbing_mode = true;
			Point current_point = abs_pos[i];
			int min_manhattan_distance = INF;
			for (const auto &p : spots) {
				int manhattan_distance =
					abs(current_point.x - p.x) + abs(current_point.y - p.y);
				if (manhattan_distance < min_manhattan_distance) {
					min_manhattan_distance = manhattan_distance;
					diff = p - current_point;
				}
			}
		}

		if (!is_grabbing_mode) {
			// すべての頂点がたこ焼を持っていない場合、最後の葉で最も近いたこ焼を持ちに行く
			int min_manhattan_distance = INF;
			Point current_point = abs_pos.back();
			for (const auto &p : takoyakis) {
				int manhattan_distance =
					abs(current_point.x - p.x) + abs(current_point.y - p.y);
				if (manhattan_distance < min_manhattan_distance) {
					min_manhattan_distance = manhattan_distance;
					diff = p - current_point;
				}
			}
		}

		// もしdiffだけ移動させようとしたときにrootが盤面をはみ出る場合、代わりにランダムな回転を行う...。
		auto after_root_pos = root_pos + diff;
		if (after_root_pos.x < 0 || after_root_pos.x >= N || after_root_pos.y < 0 ||
			after_root_pos.y >= N) {
			State fail_safe_state;
			fail_safe_state.root_diff = Point(0, 0);
			fail_safe_state.rotations.assign(V, 0);
			rep(i, 1, V) { fail_safe_state.rotations[i] = ANGLES[Random(0, 3)]; }
			fail_safe_state.grab_diffs.assign(V, false);
			return fail_safe_state;
		}

		// diff 方向に1マス近づく移動方向を得る
		Point root_diff;
		if (abs(diff.x) > abs(diff.y)) {
			root_diff = Point(diff.x / abs(diff.x), 0);
		} else {
			root_diff = Point(0, diff.y / abs(diff.y));
		}

		State fail_safe_state;
		fail_safe_state.root_diff = root_diff;
		fail_safe_state.rotations.assign(V, 0);
		fail_safe_state.grab_diffs.assign(V, false);

		return fail_safe_state;
	}

	vector<Point> get_current_abs_pos() const {
		// 各頂点の絶対座標を保持する配列
		vector<Point> abs_pos(V, Point(0, 0));
		abs_pos[0] = root_pos;

		rep(i, 1, V) {
			abs_pos[i] = abs_pos[vertices[i].parent] +
						 rotate_point(vertices[i].length, vertices[i].rotation);
		}

		return abs_pos;
	}
};

struct Result {
	int turn;
	Robot robot;
	vector<State> states;

	Result() { turn = 0; }
};

auto create_vertex_data(int N, int V) {
	static vector<tuple<int, int>> vertex_data;

	if (vertex_data.empty()) {
		vertex_data.resize(V - 1);
		rep(i, 1, V) {
			int par = vi{0, 1, 2, 2, 4, 4, 3, 3, 4, 3, 4, 3, 4, 3}[i - 1];
			int len = vi{N / 2, N / 3, N / 4, N / 5, 2, 3, 2, 3, 4, 4, 5, 5, 6, 6}[i - 1];
			vertex_data[i - 1] = make_tuple(par, len);
		}
	} else {
		// 2回目以降は適当に乱数で動かしてみる
		rep(i, 1, V) {
			int par = get<0>(vertex_data[i - 1]);
			int len = Random(1, N / 2);
			vertex_data[i - 1] = make_tuple(par, len);
		}
	}
	return vertex_data;
}

auto solve(int N, int M, int V, HashSet<Point> takoyakis, HashSet<Point> spots, int best_turn) {
	Result result;

	auto vertex_data = create_vertex_data(N, V);

	result.robot = Robot(V, Point(N / 2, N / 2), vertex_data);

	while (!spots.empty()) {
		// 最適状態の取得
		const vector<Point> diffs = {Point(0, 0), Point(1, 0), Point(0, 1), Point(-1, 0), Point(0, -1)};
		State best_state;
		int best_score = 0;
		for (const auto &diff : diffs) {
			auto after_root = result.robot.root_pos + diff;
			if (after_root.x < 0 || after_root.x >= N || after_root.y < 0 || after_root.y >= N) continue;
			State state = result.robot.find_best_state(diff, takoyakis, spots);
			int score = 0;
			for (bool grab : state.grab_diffs) {
				if (grab) score++;
			}
			if (score > best_score) {
				best_score = score;
				best_state = state;
			}
		}

		if (best_score == 0) {
			best_state = result.robot.fail_safe(N, takoyakis, spots);
		}

		result.robot.apply_state(best_state, takoyakis, spots);
		result.turn++;
		result.states.push_back(best_state);

		if (result.turn >= best_turn) {
			result.turn = INF;
			break;
		}
	}

	return result;
}

// メイン関数
int main() {
	// 定数定義

	int N, M, V;
	cin >> N >> M >> V;
	// V = min(V, 13);
	HashSet<Point> takoyakis, spots;
	rep(i, N) {
		def(string, s);
		rep(j, N) if (s[j] == '1') { takoyakis.insert(Point(j, i)); }
	}
	HashSet<Point> alreadyPlacedTakoyakis;
	rep(i, N) {
		def(string, s);
		rep(j, N) if (s[j] == '1') {
			if (takoyakis.contains(Point(j, i))) {
				alreadyPlacedTakoyakis.insert(Point(j, i));
			} else
				spots.insert(Point(j, i));
		}
	}
	for (const auto &p : alreadyPlacedTakoyakis) {
		takoyakis.erase(p);
	}

	Result bestResult;
	bestResult.turn = INF;
	int try_count = 0;

	do {
		auto result = solve(N, M, V, takoyakis, spots, bestResult.turn);
		if (result.turn < bestResult.turn) {
			bestResult = result;
		}
		try_count++;

		// 一回当たりの時間を計算
		int elapsed = Mgr::timer.get() / try_count;
		int remain = 2900 - Mgr::timer.get();

		// 2回ぶんの時間がない場合は打ち切る
		if (remain < elapsed * 2) {
			break;
		}
	} while (true);

	debug_f("Try Count:", try_count);

	// 出力
	out(bestResult.robot.V);
	rep(i, 1, bestResult.robot.V) {
		int par = bestResult.robot.vertices[i].parent;
		int len = bestResult.robot.vertices[i].length;
		out(par, len);
	}
	out(N / 2, N / 2);
	for (auto &state : bestResult.states) {
		string action =
			state.root_diff == Point(0, 0)
				? "."
				: state.root_diff == Point(1, 0)   ? "R"
				  : state.root_diff == Point(0, 1) ? "D"
				  : state.root_diff == Point(-1, 0) ? "L"
													: "U";
		for (size_t i = 1; i < state.rotations.size(); ++i) {
			action += state.rotations[i] == 1 ? "R" : state.rotations[i] == 3 ? "L" : ".";
		}
		for (int i = 0; i < bestResult.robot.V; ++i) {
			if (bestResult.robot.is_leaf[i]) {
				action += state.grab_diffs[i] ? "P" : ".";
			} else {
				action += ".";
			}
		}
		out(action);
	}

	debug_f("Score:", bestResult.turn);

	return 0;
}
