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
} 

#ifdef _DEBUG
Random(1);
#else
Random(0);
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
	float persentile() const { return (float)get()/limit; }
};
void wait(const int&msec){Timer tm(msec); while(tm);}

struct Mgr {
	#ifdef _DEBUG
	static const int TLE = 2000;
	#else
	static const int TLE = 2000;
	#endif
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

/**
 * 方針案
 * 鬼にindexを振り、落とす順番を焼きなます
 * 
 */

static const int N = 20;

// 方向ごとの文字と移動量
char DIR_CHAR[4] = {'U','D','L','R'};
int  DR[4]       = {-1, +1, 0,  0};
int  DC[4]       = { 0,  0, -1, +1};

/*
  データ構造
  焼きなまし等で決定された "demon[i].bestDir" により鬼iを落とす方向が指定済みとする
*/
struct Demon {
    int r, c;       // 鬼の初期座標
    int bestDir;    // 落とす方向(0=U,1=D,2=L,3=R)
    bool alive;     // まだ盤上にいるか
};

// (r,c)の鬼が、このboard上で「少なくとも1方向」は福が無い(=落ちられる)かを
// 簡易チェックする関数
bool canEscape(const vector<string> &board, int r, int c) {
    // 既に盤外 or '.' or 'o' なら false
    if(r<0 || r>=N || c<0 || c>=N) return false;
    if(board[r][c] != 'x') return false;

    // 4方向のどれかに福('o')が無ければ落とせると判断(問題の簡易版)
    // 本来は端まで走査して福が無ければOK
    // ここでは簡単に「行or列に'o'が無い」ならOKとするなど、実装はお好み
    // (より厳密にするなら全マス走査)
    // 例: 上方向チェック
    {
        bool existF = false;
        for(int rr=r-1; rr>=0; rr--){
            if(board[rr][c]=='o') { existF = true; break; }
        }
        if(!existF) return true;  // 上は通る
    }
    // 下
    {
        bool existF = false;
        for(int rr=r+1; rr<N; rr++){
            if(board[rr][c]=='o') { existF = true; break; }
        }
        if(!existF) return true;
    }
    // 左
    {
        bool existF = false;
        for(int cc=c-1; cc>=0; cc--){
            if(board[r][cc]=='o') { existF = true; break; }
        }
        if(!existF) return true;
    }
    // 右
    {
        bool existF = false;
        for(int cc=c+1; cc<N; cc++){
            if(board[r][cc]=='o') { existF = true; break; }
        }
        if(!existF) return true;
    }
    return false;
}

// まだ盤上にいる全鬼が「どこかの方向で落ちられる可能性があるか」をまとめてチェック
bool allDemonsCanEscape(const vector<string> &board,
                        const vector<Demon> &demons)
{
    for(const auto &dm : demons){
        if(dm.alive){
            if(!canEscape(board, dm.r, dm.c)) {
                return false;
            }
        }
    }
    return true;
}

/*
  行 or 列を 1マス動かす関数
  dir: 0=U,1=D → 列 index を上or下へ 1マス
       2=L,3=R → 行 index を左or右へ 1マス
  index: 行 or 列番号
  - boardを書き換え、盤外に出た鬼(x)は削除('.')
  - 福(o)が出たら……本来NGだが、とりあえず '.'にしてしまう or 例外処理
*/
void shiftOneStep(vector<string> &board, int dir, int index) {
    if(dir==0) {
        // U: 列= index を上へ
        // 最上段が消える
        for(int r=0; r<N-1; r++){
            // r番目 ← r+1番目
            board[r][index] = board[r+1][index];
        }
        // 最下段を空白
        board[N-1][index] = '.';
    }
    else if(dir==1) {
        // D: 列= index を下へ
        // 最下段が消える
        for(int r=N-1; r>0; r--){
            board[r][index] = board[r-1][index];
        }
        board[0][index] = '.';
    }
    else if(dir==2) {
        // L: 行= index を左へ
        for(int c=0; c<N-1; c++){
            board[index][c] = board[index][c+1];
        }
        board[index][N-1] = '.';
    }
    else {
        // R: 行= index を右へ
        for(int c=N-1; c>0; c--){
            board[index][c] = board[index][c-1];
        }
        board[index][0] = '.';
    }
}

/*
  必要回数 "一気に" シフトして対象鬼を落とす
  - demon( r,c, dir ) について、(r+1)回 'U' とか (N-1 - r +1)回 'D' とか
  - 途中で福を落とさないか要確認 → 落ちたら破綻だが、この例では無視または '.' 置換
*/
int neededShifts(int r, int c, int dir){
    // 方向ごとに「対象鬼を確実に落とすために必要なシフト回数」
    // 例：dir=0(U) → 上端までに r 回 +1  = r+1
    if(dir==0) {
        // U
        return r+1;
    } else if(dir==1){
        // D
        return (N-1 - r) +1;
    } else if(dir==2){
        // L
        return c+1;
    } else {
        // R
        return (N-1 - c) +1;
    }
}

// シフト後に、盤上の鬼の座標(r,c)も更新しておく
// xが移動した場合には Demon[].r,c を変える必要がある。
// 簡易に「全鬼をスキャン」して移動先へ更新する(計算量多いがイメージ重視)
void updateDemonsCoord(vector<Demon> &demons, vector<string> &board) {
    // すべて '.' に初期化→ board を見て 'x' の場所に対応する demon を割り当て
    // ただし複数の鬼が同じマスに重なる可能性は原問題では無い(落としきるまではxが重なることはない想定)
    // → ここでは鬼が最大 40 個程度なので雑実装OK
    // 1) 全鬼.alive のものは alive=false にしておく
    // 2) boardを上から下まで走査し、xのマスがあれば空いてるDemonを1つ割り当てて alive=true, r=..., c=...
    for(auto &dm : demons){
        if(dm.alive){
            dm.alive = false; // 再割り当て
        }
    }
    // 次に board を見て 'x' があれば demon に割り振る
    // 鬼の数 <= 40 かつ 'x' マス数と demon の alive 数は一致するはず
    // 順序は適当
    int idx=0;
    for(int r=0; r<N; r++){
        for(int c=0; c<N; c++){
            if(board[r][c] == 'x'){
                // 生きてるDemonを一つ使う
                // ここでは idx を次々進めるだけ→実際には管理がやや面倒
                // (本来はIDで紐付ける等が望ましい)
                while(idx<(int)demons.size() && demons[idx].alive) idx++;
                if(idx<(int)demons.size()){
                    demons[idx].alive = true;
                    demons[idx].r = r;
                    demons[idx].c = c;
                }
            }
        }
    }
}

/*
 「一匹の鬼(demon i)を指定方向へ一気に落とす→
  さらに同じ方向で余分に動かして別の鬼も落ちるかも→
  戻さずに済むならそのまま。詰まるなら全戻し」
*/
vector<pair<char,int>> dropOneDemonWithNoReturnIfPossible(
    vector<string> &board,
    vector<Demon> &demons,
    int i       // 落とす鬼のインデックス
){
    vector<pair<char,int>> localOps;
    if(!demons[i].alive) {
        // 既に落ちている場合は何もしない
        return localOps;
    }

    int r = demons[i].r, c = demons[i].c;
    int dir = demons[i].bestDir;
    int shifts = neededShifts(r, c, dir);  // 必要な回数

    // boardバックアップ
    auto backupBoard = board;
    auto backupDems  = demons;

    // 一気に 'shifts' 回シフト
    for(int t=0; t<shifts; t++){
        // 行 or 列をシフト
        // dir=0,1 → 列=c
        // dir=2,3 → 行=r
        int index = (dir<=1 ? c : r);
        localOps.push_back({DIR_CHAR[dir], index});
        shiftOneStep(board, dir, index);
    }
    // シフトが終わったら座標更新
    updateDemonsCoord(demons, board);

    // 同じ方向に追加で動かして落とせる鬼があるかも
    // ここではループしながら「追加で1回シフトすると落ちる鬼がいそうか？」を判断し
    // もし落ちそうならやってみる → どれだけ続けるかは適当
    for(int addCount=0; addCount<5; addCount++){ // 適当に5回だけ試す例
        // 仮に1回シフト → 何匹か新たに落ちる鬼がいればメリット大
        // ただし「福が落ちたらアウト」等、厳密判定省略
        auto boardTmp = board;
        auto demTmp   = demons;
        int index = (dir<=1 ? demTmp[i].c : demTmp[i].r); 
        // どの行/列を動かすか実は鬼iだけの行/列で良いか？
        // しかし鬼iは既に落ちているかもしれない→ここでは i に限らず "dir<=1? c : r" を使う
        shiftOneStep(boardTmp, dir, index);
        updateDemonsCoord(demTmp, boardTmp);

        // もし落ちる鬼がいないorメリットが無いならやめる、等々ロジック次第
        // ここでは雑に「少しでも鬼が減るなら追加シフト採用」
        int beforeAlive=0, afterAlive=0;
        for(auto &dm: demons) if(dm.alive) beforeAlive++;
        for(auto &dm: demTmp) if(dm.alive) afterAlive++;
        if(afterAlive < beforeAlive){
            // 鬼が減ったなら採用
            localOps.push_back({DIR_CHAR[dir], index});
            board = boardTmp;
            demons= demTmp;
        } else {
            // 落ちないのでやめる
            break;
        }
    }

    // この時点で盤面が決まった。ここで「他の鬼が詰まってないか」チェック
    if(!allDemonsCanEscape(board, demons)){
        // 詰まってしまった→全戻し
        board  = backupBoard;
        demons = backupDems;
        // 操作列は空に
        localOps.clear();
    } else {
        // 詰まってないなら「戻さずに終了」
        // → localOpsそのまま採用
    }

    return localOps;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; cin >> n; // N=20
    vector<string> board(n);
    for(int i=0; i<n; i++){
        cin >> board[i];
    }

    // 仮に鬼を抽出し、焼きなましで "bestDir" を決めてあるとする
    // (ここでは適当に bestDir=0(U) で固定する例)
    vector<Demon> demons;
    for(int r=0;r<N;r++){
        for(int c=0;c<N;c++){
            if(board[r][c]=='x'){
                Demon d;
                d.r=r; d.c=c;
                d.bestDir=0; // 仮に全鬼が上方向
                d.alive=true;
                demons.push_back(d);
            }
        }
    }

    // 順序 (焼きなまし後の順列) → ここでは単に 0..demons.size()-1
    vector<int> order(demons.size());
    iota(order.begin(), order.end(), 0);

    // buildOps (改良版): 
    //   1) 指定順序で鬼を落とす
    //   2) 必要なら追加シフト, 戻しの可否を判断
    //   3) 既に落ちている鬼はskip
    vector<pair<char,int>> allOps;
    for(int idx: order){
        if(!demons[idx].alive) continue; // 既に落ちた鬼はスキップ
        // 1匹の鬼に対して 「一気に落とす→追加シフト→戻さず終了 or 全戻し」処理
        auto localOps = dropOneDemonWithNoReturnIfPossible(board, demons, idx);
        // localOps が空の場合は「戻した」か「何もしなかった」
        // そうでなければ実際に操作が適用済み
        // 追加
        for(auto &op: localOps){
            allOps.push_back(op);
        }
    }

    // 操作数が4*N*N=1600超えるとWAなのでカット
    if((int)allOps.size()>4*N*N){
        allOps.clear();
    }

    // 出力
    for(auto &op: allOps){
        cout << op.first << " " << op.second << "\n";
    }
    return 0;
}
