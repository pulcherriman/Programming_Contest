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

const int N=36, M=12, L=1000000;
array<string, N> S;
array<int, N> P;


using IntMat = vector<vector<int>>;
using FloatMat = vector<vector<float>>;

// --- 必要ヘッダと型エイリアス ---
using Mat = vector<vector<double>>;

// 1) KMP の fail 配列構築
static vector<int> buildFail(const string &word) {
    int n = word.size();
    vector<int> fail(n);
    fail[0] = 0;
    for (int i = 1; i < n; ++i) {
        int j = fail[i-1];
        while (j > 0 && word[i] != word[j]) j = fail[j-1];
        if (word[i] == word[j]) ++j;
        fail[i] = j;
    }
    return fail;
}

// 2) nxt テーブル構築
static vector<vector<int>> buildNext(const string &word, const string &C, const vector<int> &fail) {
    int Lw = word.size();
    vector<vector<int>> nxt(Lw+1, vector<int>(M));
    rep(len, Lw+1) rep(v, M) {
        if (len < Lw && C[v] == word[len]) {
            nxt[len][v] = len + 1;
        } else {
            int j = (len>0 ? fail[len-1] : 0);
            while (j > 0 && C[v] != word[j]) j = fail[j-1];
            nxt[len][v] = (C[v] == word[j] ? j+1 : 0);
        }
        if (nxt[len][v] == Lw) nxt[len][v] = -1;  // 完全一致は吸収
    }
    return nxt;
}

// 3) 状態IDを固定配列で構築
//    最大状態数: max_len(12) * M(12) = 144
static int buildStateID(const string &word, const string &C, int state_id[13][M]) {
    int sid = 0;
    int Lw = word.size();
    // -1 で初期化
    rep(len, Lw+1) rep(j, M) state_id[len][j] = -1;
    // 常に (0, j)
    rep(j, M) state_id[0][j] = sid++;
    // 文字一致時に (i+1, j)
    rep(j, M) rep(i, Lw-1) if (word[i] == C[j]) {
        state_id[i+1][j] = sid++;
    }
    return sid; // Nstate
}

// 4) 行列乗算
constexpr int MAX_STATE = 144;

// フラット行列乗算: i→k→j のループ順序で L1 キャッシュを有効活用
static inline void mulMatrixFlat(const double* __restrict A,
                                 const double* __restrict B,
                                 double* __restrict C,
                                 int n) {
    int nn = n * n;
    std::memset(C, 0, nn * sizeof(double));
    for (int i = 0; i < n; ++i) {
        const double* Ai = A + i * n;
        double* Ci = C + i * n;
        for (int k = 0; k < n; ++k) {
            double aik = Ai[k];
            if (aik != 0.0) {
                const double* Bk = B + k * n;
                for (int j = 0; j < n; ++j) {
                    Ci[j] += aik * Bk[j];
                }
            }
        }
    }
}

// 2^20 乗の累乗 (行列サイズ n×n), スレッドローカル buffer で確保コストを排除
static inline void powMatrixFlat(const double* __restrict X0,
                                 double* __restrict Y,
                                 double* __restrict tmp,
                                 double* __restrict base,
                                 int n) {
    int nn = n * n;
    // base = X0
    std::memcpy(base, X0, nn * sizeof(double));
    // Y = I_n
    std::memset(Y, 0, nn * sizeof(double));
    for (int i = 0; i < n; ++i) Y[i * n + i] = 1.0;
    int power = 1 << 20;
    while (power > 0) {
        if (power & 1) {
            mulMatrixFlat(Y, base, tmp, n);
            std::memcpy(Y, tmp, nn * sizeof(double));
        }
        mulMatrixFlat(base, base, tmp, n);
        std::memcpy(base, tmp, nn * sizeof(double));
        power >>= 1;
    }
}

// computeProbability の行列演算部分を置き換え
static double computeProbability(int wi,
                                 const string& C,
                                 const IntMat& A,
                                 const vector<int>& fail) {
    const string& word = S[wi];
    int Lw = (int)word.size();
    static vector<vvi> nxtCache(N);
    if (nxtCache[wi].empty()) nxtCache[wi] = buildNext(word, C, fail);
    auto& nxt = nxtCache[wi];
    int state_id[13][M];
    int Nstate = buildStateID(word, C, state_id);

    // フラットバッファ (スタックでは大きすぎるため thread_local)
    static thread_local double Xbuf[MAX_STATE * MAX_STATE];
    static thread_local double Ybuf[MAX_STATE * MAX_STATE];
    static thread_local double Tbuf[MAX_STATE * MAX_STATE];
    static thread_local double Bbuf[MAX_STATE * MAX_STATE];

    int nn = Nstate * Nstate;
    // Xbuf = 0
    std::memset(Xbuf, 0, nn * sizeof(double));
    // 遷移確率をフラットに埋め込み
    for (int len = 0; len <= Lw; ++len) {
        for (int u = 0; u < M; ++u) {
            int from = state_id[len][u];
            if (from < 0) continue;
            for (int v = 0; v < M; ++v) {
                int nl = nxt[len][v];
                if (nl < 0) continue;
                int to = state_id[nl][v];
                Xbuf[to * Nstate + from] += A[u][v] * 0.01;
            }
        }
    }
    // POW 演算
    powMatrixFlat(Xbuf, Ybuf, Tbuf, Bbuf, Nstate);
    // 初期状態 index
    int init = (C[0] == word[0] ? state_id[1][0] : state_id[0][0]);
    double prob = 1.0;
    for (int i = 0; i < Nstate; ++i) prob -= Ybuf[i * Nstate + init];
    return (prob < 0.0 ? 0.0 : (prob > 1.0 ? 1.0 : prob));
}

// --- calcScore ---
int calcScore(const string& C, const IntMat& A) {
    static vector<vector<int>> all_fail;
    static bool init = false;
    if (!init) {
        all_fail.resize(N);
        rep(i, N) all_fail[i] = buildFail(S[i]);
        init = true;
    }
    double total = 0.0;
    rep(i, N) {
		total += computeProbability(i, C, A, all_fail[i]) * P[i];
	}
    return (int)round(total);
}

IntMat cleateInitMat() {
	// 基本方針 a~fを2個ずつ用意、適当に並べる
	vector<vector<float>> matrix(M, vector<float>(M, 0));
	rep(i,N){
		int target = i<2 ? i : rnd(0,2);
		vector<vector<int>> cnt(6, vector<int>(6, 0));
		rep(j,sz(S[i])-1){
			int a=S[i][j]-'a';
			int b=S[i][j+1]-'a';
			cnt[a][b]++;
		}
		rep(j,6){
			int total = sum(cnt[j]);
			rep(k,6) {
				if (cnt[j][k] > 0) {
					matrix[j*2+target][k*2+target] += pow(P[i], 3) * (float)cnt[j][k] / total;
				}
			}
		}
	}
	rep(i,M){
		int minimum = rnd(0,2);
		float total = sum(matrix[i]);
		// 行の合計が100になるように正規化
		if (total > 0) {
			rep(j,M){
				matrix[i][j] = int(matrix[i][j] / total * (100 - 12 * minimum));
			}
			int floors = sum(matrix[i]);
			while(floors < (100 - 12 * minimum)) {
				int maxj = -1;
				float maxv = -1;
				rep(j,M) {
					if (matrix[i][j] > maxv) {
						maxj = j;
						maxv = matrix[i][j];
					}
				}
				matrix[i][maxj]++;
				floors++;
			}
		}
		rep(j,M) {
			matrix[i][j] += minimum;
		}
	}

	IntMat ret(M, vector<int>(M, 0));
	rep(i,M){
		rep(j,M){
			ret[i][j] = matrix[i][j];
		}
	}
	return ret;
}

int main() {
	def(int,_,__,___);
	rep(i,N) {
		in(S[i], P[i]);
	}
	{
		vi perm(N); iota(all(perm), 0);
		sort(all(perm), [&](int a, int b) {
			return P[a] > P[b];
		});
		auto ns=S;
		rep(i,N) {
			S[i]=ns[perm[i]];
		}
		auto np=P;
		rep(i,N) {
			P[i]=np[perm[i]];
		}
	}

	int maxScore = 0;
	IntMat matrix;

	rep(40) {
		auto newMat = cleateInitMat();
		int newScore = calcScore("aabbccddeeff", newMat);
		if (newScore > maxScore) {
			maxScore = newScore;
			matrix = newMat;
		}
	}

	// #ifdef _DEBUG
	// rep(i,M){
	// 	char c = 'a' + (i/2);
	// 	out(c,  matrix[i]);
	// }
	// out("======");
	// #endif

	int _itr=0;
	while(Mgr::timer){
		_itr++;
		auto newMat = matrix;

		// 1行選んで、その中の0以上の値を1つ選び、-1。同じ行の他のランダムな値1つに+1。
		int thr = rnd(1,10);
		int row = rnd(0, M);
		int col = rnd(0, M);
		while(newMat[row][col] < thr) {
			col = rnd(0, M);
		}
		newMat[row][col]-=thr;
		int col2 = rnd(0, M);
		while(col == col2) {
			col2 = rnd(0, M);
		}
		newMat[row][col2]+=thr;

		int newScore = calcScore("aabbccddeeff", newMat);
		if (newScore > maxScore) {
			// debug(newScore);
			maxScore = newScore;
			matrix = newMat;
		}
	}
	debug_f(_itr, "itr");
	debug_f(maxScore, "maxScore");

	rep(i,M){
		char c = 'a' + (i/2);
		out(c,  matrix[i]);
	}

	return 0;
}
