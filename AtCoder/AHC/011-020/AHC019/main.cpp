#pragma GCC optimize("Ofast", "unroll-loops", "omit-frame-pointer", "inline")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma,bmi2")
#pragma GCC option("arch=native","tune=native","no-zeroupper")
#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"

/* 
 * Include Headers
 */
#include<bits/stdc++.h>
#if defined(EVAL) || defined(ONLINE_JUDGE) || defined(_DEBUG)
#include <atcoder/all>
using namespace atcoder;
#endif
#include <ext/pb_ds/assoc_container.hpp>
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
template<class K> using IndexedSet=__gnu_pbds::tree<K,__gnu_pbds::null_type,less<K>,__gnu_pbds::rb_tree_tag,__gnu_pbds::tree_order_statistics_node_update>;
template<class K> using HashSet=__gnu_pbds::gp_hash_table<K,__gnu_pbds::null_type,hash<K>>;
template<class K,class V> using IndexedMap=__gnu_pbds::tree<K,V,less<K>,__gnu_pbds::rb_tree_tag,__gnu_pbds::tree_order_statistics_node_update>;
template<class K,class V> using HashMap=__gnu_pbds::gp_hash_table<K,V,hash<K>>;
template<class V> using minpq = priority_queue<V, vector<V>, greater<V>>;

#define all(a) begin(a),end(a)
#define rall(a) rbegin(a),rend(a)
#define __LOOPSWITCH(_1, _2, _3, __LOOPSWITCH, ...) __LOOPSWITCH
#define rep(...) __LOOPSWITCH(__VA_ARGS__, __RANGE, __REP, __LOOP) (__VA_ARGS__)
#define rrep(...) __LOOPSWITCH(__VA_ARGS__, __RRANGE, __RREP, __LOOP) (__VA_ARGS__)
#define __LOOP(q) __LOOP2(q, __LINE__)
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
template<class T,class...Args>auto vec(T x,int arg,Args...args){
	if constexpr(sizeof...(args)==0) return vector(arg,x);
	else return vector(arg,vec(x,args...));
}
template<class T>constexpr bool chmax(T&a,T b){return a<b?a=b,1:0;}
template<class T>constexpr bool chmin(T&a,T b){return a>b?a=b,1:0;}
template<class S>S sum(vector<S>&a){return accumulate(all(a),S());}
template<class S>S max(vector<S>&a){return *max_element(all(a));}
template<class S>S min(vector<S>&a){return *min_element(all(a));}
ll sumAtoB(ll a,ll b){return (a+b)*(b-a+1)/2;}

namespace IO {
	// container detection
	template<typename T, typename _=void> struct is_container : false_type {};
	template<> struct is_container<string> : false_type {};
	template<class T> struct is_container<valarray<T>> : true_type {};
	template<typename...Ts> struct is_container_helper {};
	template<typename T> struct is_container<T, conditional_t<
		true, void, is_container_helper<
			typename T::value_type, typename T::size_type, typename T::iterator,
			decltype(declval<T>().size()),
			decltype(declval<T>().begin()),
			decltype(declval<T>().end()) >>> : public true_type {};
	template<typename T,
		typename enable_if<is_container<T>{}, nullptr_t>::type = nullptr,
		char Separator = is_container<typename T::value_type>{} ? '\n' : ' ' >
	constexpr ostream&operator<<(ostream&os, T t){
		if(auto b=begin(t), e=end(t) ; t.size()) for(os<<(*b++);b!=e;os<<Separator<<(*b++)) ;
		return os;
	}

	// output
	template<class T, class...Ts> constexpr ostream& pargs(ostream&os, T&&t, Ts&&...args); // support clang
	template<class S,class T>constexpr ostream&operator<<(ostream&os,pair<S,T>p){ return os<<'['<<p.first<<", "<<p.second<<']'; };
	template<class...Ts>constexpr ostream&operator<<(ostream&os,tuple<Ts...>t){
		return apply([&os](auto&&t,auto&&...args)->ostream&{return pargs(os, t, args...);}, t);
	};
	template<class T, class...Ts> constexpr ostream& pargs(ostream&os, T&&t, Ts&&...args) {
		return ((os<<t)<<...<<(os<<' ', args));
	}

	template<class...Ts> constexpr ostream& out(Ts...args) { return pargs(cout, args...)<<'\n'; }
	template<class...Ts> constexpr ostream& debug_f(Ts...args) { return pargs(cerr, args...)<<'\n'; }
	#ifdef _DEBUG
	template<class...Ts> constexpr ostream& debug(Ts...args) { return pargs(cerr, args...)<<'\n'; }
	#else
	#define debug(...) if(false)debug_f(__VA_ARGS__)
	#endif
	void Yn(bool f) { out(f?"Yes":"No"); }

	// input
	template<class T, class...Ts> constexpr istream& gargs(istream&is, T&&t, Ts&&...args) {
		return ((is>>t)>>...>>args);
	}
	template<class S,class T>auto&operator>>(istream&is,pair<S,T>&p){return is>>p.first>>p.second;}
	template<class...Ts>constexpr istream&operator>>(istream&is,tuple<Ts...>&t){
		return apply([&is](auto&&t,auto&&...args)->istream&{return gargs(is, t, args...);}, t);
	};

	template<typename...S>auto&in(S&...s){return gargs(cin, s...);}
	#define def(t,...) t __VA_ARGS__; in(__VA_ARGS__)
	template<typename T, typename enable_if<is_container<T>{}, nullptr_t>::type = nullptr>
	auto&operator>>(istream&is,T&t){for(auto&a:t)is>>a; return is;}
}
using namespace IO;

class Random {
public:
	typedef uint_fast32_t result_type;
	constexpr result_type operator()(){return operator()((int)min(),(int)max());}
	static constexpr result_type max(){return numeric_limits<result_type>::max();}
	static constexpr result_type min(){return 0;}
	constexpr Random(const bool&isDeterministic):y(isDeterministic?2463534242:chrono::system_clock::now().time_since_epoch().count()){}
	constexpr int operator()(int a,int b){return next()%(b-a)+a;}
	result_type y;
private:
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
	uint64_t get() const{return (getClocks()-start)/ClocksPerMsec;}
	operator bool()const{return getClocks()<limit;}
};
void wait(const int&msec){Timer tm(msec); while(tm);}

struct Mgr {
	static const int TLE = 6000;
	static inline Timer timer = Timer(TLE-300);
	Mgr() {
		ios_base::sync_with_stdio(0); cin.tie(0);
		cerr<<fixed<<setprecision(3);
	}
	~Mgr(){
		cout<<flush;
		debug_f(timer.get(), "ms")<<flush;
	}
} _manager;

template<class S, class T, class U>
constexpr bool isInRange(S x, T l, U r) { return (S)l <= x && x < (S)r; }

namespace Parameter {
	int limit = 14*14*14;
}

// 展開図
template<int n>
struct Projection: public bitset<n*n>{
	Projection() {}
	Projection(const bitset<n*n>&b): bitset<n*n>(b) {}

	void input() {
		string s,t;
		rep(i,n){ in(t); s+=t; }
		reverse(all(s));
		*this = bitset<n*n>(s);
	}

	void show() {
		rep(i,n){
			rep(j,n) cout << (this->test(i*n+j) ? "██" : "  ");
			out("");
		}
	}
};

// Block,Shapeの基底クラス
// 共通で操作を定義
// 連結性の定義ではBlock ⊂ Shapeの関係だが、持ちたい操作が違うので継承させない
template<int n>
struct BlockBase: public bitset<n*n*n> {
	BlockBase() {}
	BlockBase(const bitset<n*n*n>&b): bitset<n*n*n>(b) {}

	constexpr auto size() const noexcept {
		return this->count();
	}

	// 上から見て時計回りに回転
	void rotateClockwise() {
		BlockBase<n> tmp;
		rep(i,n) rep(j,n) rep(k,n) if(this->test((n-1-j)*n*n+i*n+k)){
			tmp.set(i*n*n+j*n+k);
		}
		*this = tmp;
	}

	// 正面から見て奥に回す（右から見て時計回り）
	void rotateBack() {
		BlockBase<n> tmp;
		rep(i,n) rep(j,n) rep(k,n) if(this->test(i*n*n+k*n+(n-1-j))){
			tmp.set(i*n*n+j*n+k);
		}
		*this = tmp;
	}

	// ブロックの平行移動
	void transform(int dx, int dy, int dz) {
		BlockBase<n> tmp;
		rep(i,max(0, -dx), min(n, n-dx)) {
			rep(j,max(0, -dy), min(n, n-dy)) {
				rep(k,max(0, -dz), min(n, n-dz)) {
					if (this->test(i*n*n+j*n+k)) {
						tmp.set((i+dx)*n*n+(j+dy)*n+(k+dz));
					}
				}
			}
		}
		*this = tmp;
	}

	// ブロックの全ての回転を取得
	vector<BlockBase<n>> getAllRotation() {
		vector<BlockBase<n>> ret;
		BlockBase<n> tmp = *this;
		
		// 6面分の回転を取得
		ret.push_back(tmp);
		tmp.rotateBack();
		ret.push_back(tmp);
		tmp.rotateBack();
		ret.push_back(tmp);
		tmp.rotateBack();
		ret.push_back(tmp);
		tmp.rotateClockwise();
		tmp.rotateBack();
		ret.push_back(tmp);
		tmp.rotateBack();
		tmp.rotateBack();
		ret.push_back(tmp);

		// 各面を上にしたブロックについて、上面を固定したまま1周回す
		rep(i,6){
			tmp = ret[i];
			rep(j,3){
				tmp.rotateClockwise();
				ret.push_back(tmp);
			}
		}
		return ret;
	}

	static const array<bitset<n*n*n>, n> MASK_X, MASK_Y, MASK_Z;

	// ブロックを包含する直方体の範囲を取得
	tuple<int,int,int,int,int,int> getRect() noexcept {
		int x1, x2, y1, y2, z1, z2;

		rep(i,n)if ((MASK_X[i] & *this).any()) { x1 = i; break; }
		rrep(i,n)if ((MASK_X[i] & *this).any()) { x2 = i; break; }
		rep(i,n)if ((MASK_Y[i] & *this).any()) { y1 = i; break; }
		rrep(i,n)if ((MASK_Y[i] & *this).any()) { y2 = i; break; }
		rep(i,n)if ((MASK_Z[i] & *this).any()) { z1 = i; break; }
		rrep(i,n)if ((MASK_Z[i] & *this).any()) { z2 = i; break; }

		return make_tuple(x1, x2, y1, y2, z1, z2);
	}
};

template<int n>
const array<bitset<n*n*n>,n> BlockBase<n>::MASK_X = [](){
	array<bitset<n*n*n>,n> ret;
	bitset<n*n*n> mask;
	rep(i,n*n) mask.set(i);
	rep(i,n) {
		ret[i] = mask << (n*n*i);
	}
	return ret;
}();

template<int n>
const array<bitset<n*n*n>,n> BlockBase<n>::MASK_Y = [](){
	array<bitset<n*n*n>,n> ret;
	bitset<n*n*n> mask;
	rep(i,n)rep(j,n) mask.set(i*n*n+j);
	rep(i,n) {
		ret[i] = mask << (n*i);
	}
	return ret;
}();

template<int n>
const array<bitset<n*n*n>,n> BlockBase<n>::MASK_Z = [](){
	array<bitset<n*n*n>,n> ret;
	bitset<n*n*n> mask;
	rep(i,n*n) mask.set(i*n);
	rep(i,n) {
		ret[i] = mask << i;
	}
	return ret;
}();

// ブロック（常に連結である）
template<int n>
struct Block: public BlockBase<n> {
	Block(const bitset<n*n*n>&b): BlockBase<n>(b) {}

	Block(bool isSet = false) {
		if (isSet) this->set();
	}

	// n*n*nすべてをfillしたBlockを取得
	constexpr static Block Unit(bool isSet = true) {
		return Block(isSet);
	}

	bool operator<(const Block&b) const {
		return this->size() < b.size();
	}
};

// ブロックの集合 削除や大きさ順のソートをサポート
template<int n>
struct Blocks: public vector<Block<n>> {

};

// 形状（連結とは限らない）
template<int n>
struct Shape: public BlockBase<n> {
	Shape() {}
	Shape(const bitset<n*n*n>&b): BlockBase<n>(b) {}

	void fillFrontProjection(const Projection<n>&front) {
		rep(i,n) rep(j,n) if (!front[i*n+j]) {
			rep(k,n) this->set(j*n*n+k*n+i, 1);
		}
	}

	void fillRightProjection(const Projection<n>&right) {
		rep(i,n) rep(j,n) if (!right[i*n+j]) {
			rep(k,n) this->set(k*n*n+j*n+i, 1);
		}
	}

	Projection<n> getFrontProjection() const {
		Projection<n> ret;
		bitset<n*n*n> merged;
		rep(i,n){
			merged |= ((*this) & this->MASK_Y[i]) >> (i*n);
		}
		rep(i,n)rep(j,n) if(merged.test(j*n*n+i)) ret.set(i*n+j);
		return ret;
	}

	Projection<n> getRightProjection() const {
		Projection<n> ret;
		bitset<n*n*n> merged;
		rep(i,n){
			merged |= ((*this) & this->MASK_X[i]) >> (i*n*n);
		}
		rep(i,n)rep(j,n) if(merged.test(j*n+i)) ret.set(i*n+j);
		return ret;
	}

	Blocks<n> getConnectivity() {
		vi degrees(n*n*n, 0);
		for(int p = this->_Find_first() ; p != n*n*n ; p = this->_Find_next(p)){
			int ni = p/(n*n), nj = p/n%n, nk = p%n;
			rep(l,3){
				if(l==0) ni++;
				else if(l==1) nj++;
				else nk++;

				if(ni<n and nj<n and nk<n and this->test(ni*n*n+nj*n+nk)) {
					degrees[p]++;
					degrees[ni*n*n+nj*n+nk]++;
				}

				if(l==0) ni--;
				else if(l==1) nj--;
				else nk--;
			}
		}

		minpq<pair<int,int>> pq;
		for(int p = this->_Find_first() ; p != n*n*n ; p = this->_Find_next(p)){
			pq.push({degrees[p], p});
		}

		static vector<tuple<int,int,int>> ds {
			{1,0,0}, {0,1,0}, {0,0,1}, {-1,0,0}, {0,-1,0}, {0,0,-1}
		};


		Shape<n> visited;
		Blocks<n> ret;
		while(!pq.empty()){
			auto [d,p] = pq.top(); pq.pop();
			if(visited.test(p)) continue;

			Block<n> block;
			block.set(p);

			queue<tuple<int,int,int,int>> q;
			q.push({p,p/(n*n),p/n%n,p%n});
			int limit = Parameter::limit;
			// limit -= Random(0, limit/2+1);
			while (!q.empty()) {
				auto [c,i,j,k] = q.front(); q.pop();
				if(visited.test(c)) continue;
				visited.set(c);
				block.set(c);
				limit--;

				shuffle(all(ds),Random);
				for(auto[di,dj,dk]:ds) {
					int ni = i+di, nj = j+dj, nk = k+dk;
					if(!isInRange(ni,0,n) or !isInRange(nj,0,n) or !isInRange(nk,0,n)) continue;
					int next = ni*n*n+nj*n+nk;
					if(this->test(next) and !visited.test(next)){
						q.push({next,ni,nj,nk});
						degrees[next]--;
						pq.push({degrees[next], next});
					}
				}
				if(limit <= 0) break;
			}

			ret.push_back(block);
		}
		return ret;
	}

	Shape<n> getIntersect(Shape<n> other) {
		Shape<n> ret((*this) & other);
		return ret;
	}
};

// キューブ
// blocksはセルを共有しない shapeはblocksの和集合
template<int n>
struct Cube {
	Shape<n> shape;
	Blocks<n> blocks;
	Cube() {
		addBlock(Block<n>::Unit(1));
	}

	// 連結なブロックを追加する
	void addBlock(Block<n> block) {
		blocks.push_back(block);
		shape |= block;
	}

	// 既存のブロックを削除する
	void removeBlock(int index) {
		swap(blocks[index], blocks.back());
		shape ^= blocks.back();
		blocks.pop_back();
	}
	void removeBlock(Block<n> block) {
		shape ^= block;
		blocks.erase(remove(all(blocks), block), blocks.end());
	}

	// 現在のブロック集合からなる形状から、特定の形を消す
	// 残ったブロックの連結性は崩壊するので組み直す
	void subtractShape(Shape<n> sub) {
		shape &= ~sub;
		blocks = shape.getConnectivity();
	}

	void show() {
		out("  Shape:");
		rep(j,n){
			cout<<"    ";
			rep(i,n){
				rep(k,n) cout << (shape[i*n*n+k*n+j] ? "██" : "  ");
				cout << " | ";
			}
			out("");
		}
		out("  Blocks:");
		out("    size:", blocks.size());
	}
};

// オブジェクト（キューブ + 展開図2面）
// 既に確定して取り除かれたブロックはこの層で管理
template<int n>
struct Object {
	Projection<n> front, right;
	Cube<n> cube;
	Blocks<n> subtractedBlocks;
	Object() {}

	void dig() {
		Shape<n> digShape;
		digShape.fillFrontProjection(front);
		digShape.fillRightProjection(right);
		cube.subtractShape(digShape);
	}

	void decomposeIntoDominos(){
		const static int di[] = {1, -1, 0, 0, 0, 0};
		const static int dj[] = {0, 0, 1, -1, 0, 0};
		const static int dk[] = {0, 0, 0, 0, 1, -1};

		mf_graph<int> g(n*n*n + 2);
		const int start = n*n*n, goal = start + 1;
		for(int p = cube.shape._Find_first() ; p != n*n*n ; p = cube.shape._Find_next(p)){
			int i = p/(n*n), j = p/n%n, k = p%n;
			if((i+j+k)%2==0){
				g.add_edge(start, p, 1);
				rep(d,6){
					int ni = i+di[d], nj = j+dj[d], nk = k+dk[d];
					if(!isInRange(ni,0,n) or !isInRange(nj,0,n) or !isInRange(nk,0,n)) continue;
					int odd = ni*n*n+nj*n+nk;
					if(cube.shape[odd]){
						g.add_edge(p, odd, 1);
					}
				}
			} else g.add_edge(p, goal, 1);
		}

		g.flow(start, goal);

		cube.blocks.clear();
		{
			auto shape = cube.shape;
			for(auto&e : g.edges()){
				if(e.from<n*n*n and e.to<n*n*n and e.flow==1){
					Block<n> block;
					block.set(e.from);
					block.set(e.to);
					cube.blocks.push_back(block);
					shape ^= block;
				}
			}
			for(int p = shape._Find_first() ; p != n*n*n ; p = shape._Find_next(p)){
				Block<n> block;
				block.set(p);
				cube.blocks.push_back(block);
			}
		}
	}

	bool isRemovableBlock(Block<n> block) {
		auto shape = cube.shape;
		for(auto& b : subtractedBlocks) {
			shape ^= b;
		}
		shape ^= block;
		
		bool ok = front == shape.getFrontProjection();
		ok &= right == shape.getRightProjection();
		return ok;
	}

	// 展開図を損なわないように、セルをrequireCount個削る
	bool removeCells(int requireCount = 1) {
		vi degrees(n*n*n, 0);

		for(int p = cube.shape._Find_first() ; p != n*n*n ; p = cube.shape._Find_next(p)){
			int ni = p/(n*n), nj = p/n%n, nk = p%n;
			rep(l,3){
				if(l==0) ni++;
				else if(l==1) nj++;
				else nk++;

				if(ni<n and nj<n and nk<n and cube.shape.test(ni*n*n+nj*n+nk)) {
					degrees[p]++;
					degrees[ni*n*n+nj*n+nk]++;
				}

				if(l==0) ni--;
				else if(l==1) nj--;
				else nk--;
			}
		}
		
		minpq<pii> pq;
		for(int p = cube.shape._Find_first() ; p != n*n*n ; p = cube.shape._Find_next(p)){
			pq.push({degrees[p], p});
		}

		while(!pq.empty()){
			auto [_, idx] = pq.top(); pq.pop();
			if(!cube.shape.test(idx)) continue;
			cube.shape.reset(idx);

			if(front != cube.shape.getFrontProjection() or right != cube.shape.getRightProjection()) {
				cube.shape.set(idx);
				continue;
			}

			const auto newBlocks = cube.shape.getConnectivity();
			if(cube.blocks.size() < newBlocks.size()) {
				cube.shape.set(idx);
				continue;
			}
			cube.blocks = newBlocks;
			requireCount--;
			if(requireCount == 0) break;
		}

		return requireCount == 0;
	} 

	// 1x1ブロックを消せるだけ消す
	void removeRedundantCells() {
		auto targetBlocks = cube.blocks;
		for(auto& block : targetBlocks) {
			if(block.size() > 1) continue;
			if(isRemovableBlock(block)) {
				cube.removeBlock(block);
			}
		}
	}

	// 1x2ブロックを小さい順に削除 1x2がいくつ残るか（残ったか）返す
	pair<int,int> removeRedundantDominos(int deleteLimit = 0) {
		int remainCount = 0, removeCount = 0;
		auto targetBlocks = cube.blocks;
		for(auto& block : targetBlocks) {
			if(block.size() != 2) continue;
			if(isRemovableBlock(block)) {
				removeCount++;
				if(deleteLimit > 0) {
					deleteLimit--;
					cube.removeBlock(block);
				}
			} else {
				remainCount++;
			}
		}
		return {remainCount, removeCount};
	}

	void reset() {
		cube = Cube<n>();
		subtractedBlocks.clear();
	}

	void input() {
		front.input();
		right.input();
	}

	void show() {
		out("-- Right --");
		right.show();
		out("");
		out("-- Front --");
		front.show();
		out("");
		out("-- Cube --");
		cube.show();
		out("");
	}
};


// ソルバー
struct SolverInterface {
	virtual void input() = 0;
	virtual int solve() = 0;
	virtual float getScore() = 0;
	virtual pair<vi, vi> output() = 0;
	virtual void show() = 0;
};

template<int n>
struct Solver: public SolverInterface {
	Object<n> obj1, obj2;
	Solver() {}

	void input() {
		obj1.input();
		obj2.input();
	}

	// 回転・平行移動によって出来る一番大きな共通部分を発見し、確定させてCubeから取り除く
	bool subtractMaxIntersect() {
		static int cnt = 0;

		// 残りブロックの最大サイズが2以下なら、二部マッチングで対応するので終了する
		{
			if(obj1.cube.blocks.empty() or obj2.cube.blocks.empty()) return false;
			auto maxSize1 = (*max_element(all(obj1.cube.blocks))).size();
			if(maxSize1 <= n/2) return false;
			auto maxSize2 = (*max_element(all(obj2.cube.blocks))).size();
			if(maxSize2 <= n/2) return false;
		}

		Block<n> maxIntersect1;
		Block<n> maxIntersect2;

		// オブジェクトの交差判定をするが、高速化のためサイズ2以下になったオブジェクトは除外して計算
		auto cpObj2 = obj2;
		rep(i,cpObj2.cube.blocks.size()) {
			if(cpObj2.cube.blocks[i].size() <= 2) cpObj2.cube.removeBlock(i--);
		}

		auto cpBlocks1 = obj1.cube.blocks;
		sort(rall(cpBlocks1));

		for(auto&cpBlock1:cpBlocks1){
			if(2 >= cpBlock1.size()) break;
			if(maxIntersect1.size() >= cpBlock1.size()) break;

			// cpObj1とcpObj2を包含する直方体の始点と終点を、それぞれ求める
			const auto [minI1, maxI1, minJ1, maxJ1, minK1, maxK1] = cpBlock1.getRect();

			for(auto&rotShape2: cpObj2.cube.shape.getAllRotation()){
				// if(Random(0, 5)) continue;

				const auto [minI2, maxI2, minJ2, maxJ2, minK2, maxK2] = rotShape2.getRect();

				// cpObj2をdi,dj,dkだけ平行移動させたものと、cpObj1を包含する直方体が共通部分を持つ範囲だけ回すcontinue
				const auto judge = [&](int di, int dj, int dk){
					Shape<n> transformed = rotShape2;
					transformed.transform(di,dj,dk);
					if(transformed.size() <= maxIntersect1.size()) return;

					Shape<n> intersect = transformed.getIntersect(cpBlock1);
					if(intersect.size() > maxIntersect1.size()) {
						auto blocks = intersect.getConnectivity();
						// auto minBlock = *min_element(all(blocks));
						// if(minBlock.size() <= 2) return;

						auto maxBlock = *max_element(all(blocks));
						if(maxBlock.size() > maxIntersect1.size()) {

							transformed ^= intersect;
							if(transformed.getConnectivity().size() > cpObj2.cube.blocks.size()) return;

							maxIntersect1 = maxBlock;
							maxBlock.transform(-di,-dj,-dk);
							maxIntersect2 = maxBlock;
						}
					}
				};

				const int Li = max(-n+1, minI1-maxI2), Ri = min(n, maxI1-minI2+1);
				const int Lj = max(-n+1, minJ1-maxJ2), Rj = min(n, maxJ1-minJ2+1);
				const int Lk = max(-n+1, minK1-maxK2), Rk = min(n, maxK1-minK2+1);

				rep(di,-1,2)rep(dj,-1,2)rep(dk,-1,2){
					int Ci = (Li+Ri)/2 + di, Cj = (Lj+Rj)/2 + dj, Ck = (Lk+Rk)/2 + dk;
					Ci = clamp(Ci, Li, Ri-1);
					Cj = clamp(Cj, Lj, Rj-1);
					Ck = clamp(Ck, Lk, Rk-1);
					judge(Ci,Cj,Ck);
				}

				// const int ilMax = min(maxI1, maxI2+(Li+Ri)/2) - max(minI1, minI2+(Li+Ri)/2) + 1;
				const int jlMax = min(maxJ1, maxJ2+(Lj+Rj)/2) - max(minJ1, minJ2+(Lj+Rj)/2) + 1;
				const int klMax = min(maxK1, maxK2+(Lk+Rk)/2) - max(minK1, minK2+(Lk+Rk)/2) + 1;

				rep(di, Li, Ri) {
					const int il = min(maxI1, maxI2+di) - max(minI1, minI2+di) + 1;
					if(il*jlMax*klMax <= (int)maxIntersect1.size()) {
						if(di > (Li+Ri)/2) break;
						continue;
					}
					rep(dj, Lj, Rj) {
						const int jl = min(maxJ1, maxJ2+dj) - max(minJ1, minJ2+dj) + 1;
						if(il*jl*klMax <= (int)maxIntersect1.size()) {
							if(dj > (Lj+Rj)/2) break;
							continue;
						}
						rep(dk, Lk, Rk) {
							if(abs(di - (Li+Ri)/2) <= 1 and abs(dj - (Lj+Rj)/2) <= 1 and abs(dk - (Lk+Rk)/2) <= 1) continue;
							// 交差する領域の体積がmaxIntersect1.size()より小さければ、更新の可能性がないのでcontinue
							const int kl = min(maxK1, maxK2+dk) - max(minK1, minK2+dk) + 1;
							if(il*jl*kl <= (int)maxIntersect1.size()) {
								if(dk > (Lk+Rk)/2) break;
								continue;
							}
							cnt++;
							if(Random(0, 10)) continue;

							judge(di,dj,dk);
						}
					}
				}
			}
		}

		if(maxIntersect1.size() <= 2) {
			return false;
		}

		auto intersectRotations = maxIntersect2.getAllRotation();
		for(auto&rot:intersectRotations) {
			if(cpObj2.cube.shape.getIntersect(rot) == rot) {
				maxIntersect2 = rot;
				break;
			}
		}

		obj1.subtractedBlocks.push_back(maxIntersect1);
		obj2.subtractedBlocks.push_back(maxIntersect2);
		obj1.cube.subtractShape(maxIntersect1);
		obj2.cube.subtractShape(maxIntersect2);
		return true;
	}

	int solve() {
		if(!Mgr::timer) return 0;
		obj1.reset(); obj2.reset();

		obj1.dig();
		obj2.dig();

		// sort(all(obj1.cube.blocks));
		rep(i,obj1.cube.blocks.size()) {
			auto&block1 = obj1.cube.blocks[i];
			if(!obj1.isRemovableBlock(block1)) continue;
			// erase-remove idiom
			obj1.cube.removeBlock(block1);
			i--;
		}
		// sort(all(obj2.cube.blocks));
		rep(i,obj2.cube.blocks.size()) {
			auto&block2 = obj2.cube.blocks[i];
			if(!obj2.isRemovableBlock(block2)) continue;
			// erase-remove idiom
			obj2.cube.removeBlock(block2);
			i--;
		}

		// セル数が同じになるように、隣接要素が少なく連結性を損なわないセルを削る
		int cell1 = obj1.cube.shape.size();
		int cell2 = obj2.cube.shape.size();
		if(cell1 > cell2) {
			obj1.removeCells(cell1-cell2);
		} else if(cell2 > cell1) {
			obj2.removeCells(cell2-cell1);
		}
		
		// 大きさ3以上の重複を全て取り除く
		while(subtractMaxIntersect()) {
			// break;
			if(!Mgr::timer) break;
		}

		// 残ったブロックを全て1X2か1x1に分割
		obj1.decomposeIntoDominos();
		obj2.decomposeIntoDominos();

		// 未確定ブロックをサイズ昇順に、それを取り除いても投影図が壊れなければ削除
		// 1x1は、消せるだけ消したい
		obj1.removeRedundantCells();
		obj2.removeRedundantCells();



		// 1x2は、偏りをなくすのが最適 (3-5個を 3-2にするより3-3のほうがいい)
		int remain1 = count_if(all(obj1.cube.blocks), [](auto&block){ return block.size() == 2; });
		int remain2 = count_if(all(obj2.cube.blocks), [](auto&block){ return block.size() == 2; });
		if(remain1 > remain2) {
			auto [_, removeCount] = obj1.removeRedundantDominos(remain1 - remain2);
			remain1 -= removeCount;
		} else if(remain1 < remain2) {
			auto [_, removeCount] = obj2.removeRedundantDominos(remain2 - remain1);
			remain2 -= removeCount;
		}
		auto [_, removable1] = obj1.removeRedundantDominos(0);
		auto [__, removable2] = obj2.removeRedundantDominos(0);
		int removable = min(removable1, removable2);
		obj1.removeRedundantDominos(removable);
		obj2.removeRedundantDominos(removable);


		// 残った未確定ブロックで、同じ大きさのものをsubtractedBlocksに移動
		sort(all(obj1.cube.blocks));
		sort(all(obj2.cube.blocks));

		int i1 = 0, i2 = 0;
		while(i1 < (int)obj1.cube.blocks.size() && i2 < (int)obj2.cube.blocks.size()) {
			if(obj1.cube.blocks[i1].size() == obj2.cube.blocks[i2].size()) {
				obj1.subtractedBlocks.push_back(obj1.cube.blocks[i1]);
				obj2.subtractedBlocks.push_back(obj2.cube.blocks[i2]);
				obj1.cube.removeBlock(i1);
				obj2.cube.removeBlock(i2);
				sort(all(obj1.cube.blocks));
				sort(all(obj2.cube.blocks)); // TODO: 遅いけどボトルネックにはならない
			} else if(obj1.cube.blocks[i1].size() < obj2.cube.blocks[i2].size()) {
				++i1;
			} else {
				++i2;
			}
		}

		// if(obj1.cube.blocks.size() != 0 ) return 0;
		// if(obj2.cube.blocks.size() != 0 ) return 0;

		// 確定済ブロックで、両方から消してもいいもの小さい順に削除
		rrep(i,obj1.subtractedBlocks.size()) {
			auto&block1 = obj1.subtractedBlocks[i];
			if(!obj1.isRemovableBlock(block1)) continue;
			auto&block2 = obj2.subtractedBlocks[i];
			if(!obj2.isRemovableBlock(block2)) continue;

			// erase-remove idiom
			obj1.subtractedBlocks.erase(obj1.subtractedBlocks.begin() + i);
			obj2.subtractedBlocks.erase(obj2.subtractedBlocks.begin() + i);
		}

		return (*max_element(all(obj1.subtractedBlocks), [](auto&b1, auto&b2){ return b1.size() < b2.size(); })).size();
	}

	
	float getScore() {
		float commonScore = 0;
		float distinctScore = 0;
		for(auto&b: obj1.subtractedBlocks) {
			commonScore += 1.0 / b.size();
		}
		for(auto&b: obj1.cube.blocks) {
			distinctScore += b.size();
		}
		for(auto&b: obj2.cube.blocks) {
			distinctScore += b.size();
		}
		float score = round(1e9 * (commonScore + distinctScore));
		return score;
	}

	pair<vi, vi> output() {
		vi ans(n*n*n,0), ans2(n*n*n,0);
		rep(i,obj1.subtractedBlocks.size()) {
			auto&block1 = obj1.subtractedBlocks[i];
			rep(j,n*n*n) if(block1[j]) ans[j] = i+1;

			auto&block2 = obj2.subtractedBlocks[i];
			rep(j,n*n*n) if(block2[j]) ans2[j] = i+1;
		}

		int id = obj1.subtractedBlocks.size();
		rep(i,obj1.cube.blocks.size()){
			auto&block1 = obj1.cube.blocks[i];
			++id;
			rep(j,n*n*n) if(block1[j]) ans[j] = id;
		}
		rep(i,obj2.cube.blocks.size()){
			auto&block2 = obj2.cube.blocks[i];
			++id;
			rep(j,n*n*n) if(block2[j]) ans2[j] = id;
		}

		return {ans, ans2};
	}

	void show() {
		obj1.show();
		obj2.show();
	}
};


int main() {
	HashMap<int, SolverInterface*> solvers;
	solvers[5] = new Solver<5>();
	solvers[6] = new Solver<6>();
	solvers[7] = new Solver<7>();
	solvers[8] = new Solver<8>();
	solvers[9] = new Solver<9>();
	solvers[10] = new Solver<10>();
	solvers[11] = new Solver<11>();
	solvers[12] = new Solver<12>();
	solvers[13] = new Solver<13>();
	solvers[14] = new Solver<14>();


	def(int,n);
	auto solver = solvers[n];
	solver->input();

	float bestScore = numeric_limits<float>::max();
	vi ans1, ans2;
	
	int itrCount = 0;
	while(Mgr::timer) {
		rrep(i,n, n*n*n+1){
			if (!Mgr::timer) break;
			itrCount++;
			Parameter::limit = i;
			int maxBlock = solver->solve();
			i = maxBlock;
			// out(Mgr::timer.get(), solver->getScore(), "(",Parameter::limit,"->",maxBlock,")");
			if(chmin(bestScore, solver->getScore())) {
				debug(Mgr::timer.get(), solver->getScore(), "(",i,")");
				tie(ans1, ans2) = solver->output();
				// out(max(max(ans1), max(ans2)));
				// out(ans1);
				// out(ans2);
			}
		}
	}
	debug_f("itr:",itrCount);

	
	out(max(max(ans1), max(ans2)));
	out(ans1);
	out(ans2);
	// solver->show();
}