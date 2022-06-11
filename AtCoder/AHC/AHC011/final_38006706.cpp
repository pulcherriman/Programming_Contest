#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("inline")

#pragma GCC diagnostic ignored "-Wunused-value"
#ifdef _DEBUG
// #define _GLIBCXX_DEBUG 1
#endif
int _TEMPORARY_DEBUG = 1;


/* 
 * Include Headers
 */
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
template<class K> using IndexedSet=__gnu_pbds::tree<K,__gnu_pbds::null_type,less<K>,__gnu_pbds::rb_tree_tag,__gnu_pbds::tree_order_statistics_node_update>;
template<class K> using HashSet=__gnu_pbds::gp_hash_table<K,__gnu_pbds::null_type>;
template<class K,class V> using IndexedMap=__gnu_pbds::tree<K,V,less<K>,__gnu_pbds::rb_tree_tag,__gnu_pbds::tree_order_statistics_node_update>;
template<class K,class V> using HashMap=__gnu_pbds::gp_hash_table<K,V>;
template<class V> using minpq = priority_queue<V, vector<V>, greater<V>>;
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
#define __RRANGE(i,a,n) for(int i=((int)((n)-1));i>=((int)a);--i)
#define sz(a) ((int)(a).size())

/*
 * Constants
 */
constexpr int INF=1<<30;

/*
 * Utilities
 */
template<class T>constexpr bool chmax(T&a,T b){return a<b?a=b,1:0;}
template<class T>constexpr bool chmin(T&a,T b){return a>b?a=b,1:0;}
template<class S>S sum(vector<S>&a){return accumulate(all(a),S());}
template<class S>S max(vector<S>&a){return *max_element(all(a));}
template<class S>S min(vector<S>&a){return *min_element(all(a));}

namespace IO {
	// container detection
	template<typename T, typename _=void> struct is_container : false_type {};
	template<> struct is_container<string> : false_type {};
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
		if(auto b=begin(t), e=end(t) ; !t.empty()) for(os<<(*b++);b!=e;os<<Separator<<(*b++)) ;
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
	template<class...Ts> constexpr ostream& debug(Ts...args) { 
		if(_TEMPORARY_DEBUG) return pargs(cerr, args...)<<'\n';
		else return cerr;
	}
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
	using result_type = unsigned int;
	constexpr result_type operator()(){return operator()((ll)min(),(ll)max());}
	static constexpr result_type max(){return numeric_limits<result_type>::max();}
	static constexpr result_type min(){return 0;}
	constexpr Random(const bool&isDeterministic):y(isDeterministic?2463534242ll:chrono::system_clock::now().time_since_epoch().count()){}
	constexpr int operator()(int a,int b){return next()%(b-a)+a;}
	constexpr ll operator()(ll a,ll b){return (((ull)next())<<32|next())%(b-a)+a;}
	constexpr double operator()(double a,double b){return (b-a)*next()/4294967296.0+a;}
	result_type getSeed(){return y;}
	void setSeed(result_type seed){y=seed;}
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
	uint64_t get() const{return (getClocks()-start)/ClocksPerMsec;}
	operator bool()const{return getClocks()<limit;}
};
void wait(const int&msec){Timer tm(msec); while(tm);}

struct Mgr {
	static const int TLE = 3000;
	static inline Timer timer = Timer(TLE-100);
	Mgr() {
		ios_base::sync_with_stdio(0); cin.tie(0);
		cout<<fixed<<setprecision(11);
		cerr<<fixed<<setprecision(3);
	}
	~Mgr(){
		// debug_f(timer.get(), "ms")<<flush;
	}
} _manager;

enum DIR {
	LEFT = 1,
	UP = 2,
	RIGHT = 4,
	DOWN = 8,
};

const int DirToInverseIndex[]={0,2,3,0,0,0,0,0,1};
const int DirToInverse[]={0,4,8,0,1,0,0,0,2};
const int dy[]={0,-1,0,1};
const int dx[]={-1,0,1,0};

int n,t;
struct Field{
public:
	vl a;
	vl compressedMove;
	int nextLineIndex = 0;
	int mvLength=0,by,bx;
	friend bool operator<(const Field&l, const Field&r){
		return l.mvLength>r.mvLength;
	};
	Field() = default;
	Field(vl&_a):a(_a){
		rep(i,n)rep(j,n)if(get(i,j)==0){by=i; bx=j; return;}
	}
	void addMove(ll dirIndex){
		if((mvLength&31)==0)compressedMove.emplace_back(dirIndex);
		else{
			const int shift = (mvLength&31)*2;
			compressedMove.back() &= ~(3ll<<shift);
			compressedMove.back() |= dirIndex<<shift;
		}
		mvLength++;
	}
	void removeMove(){
		mvLength--;
		if((mvLength&31)==0)compressedMove.pop_back();
	}
	int lastMove(){
		return (compressedMove.back()>>(((mvLength-1)&31)*2))&3;
	}
	bool move(DIR d){
		if(mvLength and lastMove()==DirToInverseIndex[d]){
			back();
			return false;
		}
		switch(d){
			case RIGHT: 
				if(bx+1==n)return false;
				addMove(2);
				swap(by, bx, by, bx+1); ++bx; break;
			case UP:
				if(by==0)return false;
				addMove(1);
				swap(by, bx, by-1, bx); --by; break;
			case LEFT:
				if(bx==0)return false;
				addMove(0);
				swap(by, bx, by, bx-1); --bx; break;
			case DOWN:
				if(by+1==n)return false;
				addMove(3);
				swap(by, bx, by+1, bx); ++by; break;
		}
		return true;
	}
	bool back(){
		switch(lastMove()){
			case 0: swap(by, bx, by, bx+1); ++bx; break;
			case 1: swap(by, bx, by+1, bx); ++by; break;
			case 2: swap(by, bx, by, bx-1); --bx; break;
			case 3: swap(by, bx, by-1, bx); --by; break;
		}
		removeMove();
		return true;
	}
	inline ll get(int i, int j){
		return (a[i]>>(j*4))&15;
	}
	inline ll get(int h){
		return (a[h/n]>>(h%n*4))&15;
	}
	inline void set(int i, int j, ll type){
		a[i] &= ~(15ll<<(j*4));
		a[i] |= type<<(j*4);
	}
	void swap(int i1, int j1, int i2, int j2){
		ll d=get(i1,j1);
		set(i1,j1,get(i2,j2));
		set(i2,j2,d);
	}
	string getString() {
		string ret;
		const static string charMap="LURD";
		rep(i,mvLength){
			ret+=charMap[(compressedMove[i/32]>>((i&31)*2))&3];
		}
		return ret;
	}
};

struct UnionFind{
	vi par;
	UnionFind(int x){par.assign(x,-1);}
	int find(int x){return par[x]<0?x:find(par[x]);}
	bool same(int x,int y){return find(x)==find(y);}
	int size(int x){return -par[find(x)];}
	bool unite(int x,int y){
		x=find(x); y=find(y);
		if(x==y)return false;
		if(size(x)<size(y)) swap(x,y);
		par[x]+=par[y]; par[y]=x;
		return true;
	}
};
int calculate(Field&f) {
	int ret=1;
	UnionFind uf(n*n);
	rep(i,n)rep(j,n){
		if(j!=n-1 and (f.get(i,j)&DIR::RIGHT) and (f.get(i,j+1)&DIR::LEFT)){
			if(!uf.unite(i*n+j,i*n+j+1)) {
				return 0;
			}
		}
		if(i!=n-1 and (f.get(i,j)&DIR::DOWN) and (f.get(i+1,j)&DIR::UP)){
			if(!uf.unite(i*n+j,(i+1)*n+j)) {
				return 0;
			}
		}
		chmax(ret, (int)uf.size(i*n+j));
	}
	return round(500000.f * ret / (n*n-1));
}


using TileZaiko = array<int, 16>;

/*
 * 上端、下端に伸びる線の有無を決め打って、可能なタイルの配置を返す
 */
vl calcKouho(TileZaiko&	remainTileCount, int top, int bottom){
	vl ret;
	rep(connect,1<<(n-1)){
		ll tilesHash=0;
		bool isStraight = false;
		TileZaiko zaiko = remainTileCount;
		rep(i,n){
			int current = 0;
			if((top>>i&1)) current |= DIR::UP;
			if((bottom>>i)&1) current|=DIR::DOWN;
			if(i+1<n and (connect>>(n-i-2)&1)) current|=DIR::RIGHT;
			if(i>0 and (connect>>(n-i-1)&1)) current|=DIR::LEFT;
			if(--zaiko[current]<0){
				if(i+1<n) connect |= ((1<<(n-i-2))-1);
				tilesHash = 0; break;
			}

			if(isStraight){
				if(current==1) {
					if(i+1<n) connect |= ((1<<(n-i-2))-1);
					tilesHash = 0; break;
				}
				if(current!=5) isStraight = false;
			}else if(current==4) isStraight = true;
			tilesHash |= ((ll)current)<<(i*4);
		}
		if(tilesHash){
			ret.emplace_back(tilesHash);
		}
	}
	shuffle(all(ret), Random);
	if(ret.size() > 10) {
		ret.erase(ret.begin()+10, ret.end());
	}
	return ret;
}

/*
 * placedLine列まで置いたときにfが全域木になり得るか判定
 */ 
bool checkConnectivity(Field&f, int placedLine){
	vvb visited(n, vb(n, false));
	queue<pii> q;
	const auto push=[&](int i, int j){
		if(!visited[i][j]) q.emplace(i,j);
	};

	bool closeCount=0; bool openCount=0;
	rep(i,placedLine+1)rep(j,n)if(!visited[i][j] and f.get(i,j)){
		push(i,j);
		//bfs
		bool isOpen=false;
		while(!q.empty()){
			auto [y,x]=q.front(); q.pop();
			if(visited[y][x]) {
				return false;
			}
			visited[y][x]=true;
			const int selfValue=f.get(y,x);
			if(y>0 and selfValue&DIR::UP) {
				if(f.get(y-1,x)&DIR::DOWN) push(y-1,x);
				else return false;	// 上向きの道の先が空マス
			}
			if(y+1<n and selfValue&DIR::DOWN) {
				if(f.get(y+1,x)&DIR::UP) push(y+1,x);
				else if(y<=placedLine) isOpen=true;	// まだ下の行に置いていない
				else return false;	// 下向きの道の先が空マス
			}
			if(x>0 and selfValue&DIR::LEFT) {
				if(f.get(y,x-1)&DIR::RIGHT) push(y,x-1);
				else return false;	// 左向きの道の先が空マス
			}
			if(x+1<n and selfValue&DIR::RIGHT) {
				if(f.get(y,x+1)&DIR::LEFT) push(y,x+1);
				else return false;	// 右向きの道の先が空マス
			}
		}
		if(isOpen) openCount=true;
		else if(closeCount) return false;
		else closeCount=true;
		if(closeCount and openCount) return false;
	}
	if(placedLine+1==n){
		if(closeCount and !openCount) return true;
		return false;
	}
	return true;
}

/*
 * 与えられた盤面のパネルから構成できる全域木を返す
 * プログラム開始からmax(1つ見つかるまで,2秒)探索する。N=10の時1.8秒くらいかかるのでアレ
 * TODO: 3秒見つからなかったときにTLEになる気がする
 */
bool solveAtoB(Field&from, Field&to);
struct AnswerObserver {
	int challenge = 0;

	bool isSuccess = false;
	int maxScore=0;
	string answerString;

	AnswerObserver() = default;

	void createMove(Field init, Field mst){
		bool flipped = false;
		// 左下に空白があったら盤面を反転
		{
			if(mst.get(n-1,0) == 0) {
				flipped = true;
				// 1と4のビットを反転
				const int flip[] ={0,4,2,6,1,5,3,7,8,12,10,14,9,13,11,15};
				Field mst2=mst, init2=init;
				rep(i,n)rep(j,n){
					mst.set(i,n-1-j,flip[mst2.get(i,j)]);
					init.set(i,n-1-j,flip[init2.get(i,j)]);
				}
				init.bx=n-1-init.bx;
				mst.bx=n-1-mst.bx;
			}
			if(mst.get(n-1,n-1) != 0) {
				return;
			}
		}
		// if(!flipped)return;

		challenge++;
		const auto setfixString=[&](){
			answerString=init.getString();
			if(flipped) {
				for(auto&c:answerString){
					if(c=='R')c='L';
					else if(c=='L')c='R';
				}
			}
		};
		try {
			bool succeeded = solveAtoB(init, mst);

			if(succeeded){
	//			debug(challenge, "SUCCESS!!!");
				int score =  1000000 - round(500000.f * init.mvLength / t);
				if(chmax(maxScore, score)){
					isSuccess = true;
					setfixString();
				}
			}else{
	//			debug(challenge, "FAILED....");
				if(!isSuccess){
					if(chmax(maxScore, calculate(init))){
						setfixString();
					}
				}
			}
		} catch(runtime_error&e){
			debug_f(e.what());
		}
	}
};
AnswerObserver answerObserver;

void findMST(Field&f, int useableThreshold) {
	int calcCount=0;
	vector<TileZaiko> masterTileCount(n);
	masterTileCount[0].fill(0);
	rep(i,n){
		if(i)masterTileCount[i]=masterTileCount[i-1];
		rep(j,n) masterTileCount[i][f.get(i,j)]++;
	}

	try {
		deque<Field> q;
		{
			vl tmp(n,0);
			q.emplace_back(tmp);
		}
		vi bottoms;
		rep(bottom, 1, 1<<n) bottoms.emplace_back(bottom);
		sort(rall(bottoms), [] (int a, int b) {
			return __builtin_popcount(a) < __builtin_popcount(b);
		});

		while(!q.empty()){
			auto cur = q.front(); q.pop_front();
			TileZaiko zaiko = masterTileCount[min(cur.nextLineIndex+useableThreshold, n)-1];
			rep(i,cur.nextLineIndex)rep(j,n)zaiko[cur.get(i,j)]--;

			zaiko[0]=cur.nextLineIndex+1==n; // (H):0の位置を最下段に固定

			int top=0;
			if(cur.nextLineIndex){
				rep(j,n)top |= (cur.get(cur.nextLineIndex-1,j) >> 3) << j;
			}

			int minimumBottomCount=0, maximumBottomCount=0;
			if (n-cur.nextLineIndex-1 > 0){
				rep(i,8,16)minimumBottomCount += zaiko[i];
				maximumBottomCount = min(n, minimumBottomCount);
				minimumBottomCount-=(n-cur.nextLineIndex-2)*n;
			}

			// 下方向に伸ばす線の組合せを全探索
			// 線が多い順にやる
			// この列で下方向に置く必要がある数(minimumBottomCount)を下回ったら終了
			int emplaceCount=0;
			for(auto&bottom:(cur.nextLineIndex+1==n)?vi(1,0):bottoms){
				if(__builtin_popcount(bottom) < minimumBottomCount) continue;
				if(__builtin_popcount(bottom) > maximumBottomCount) continue;
				if(cur.nextLineIndex+2==n and bottom&(1<<(n-1)) and bottom&(1)) continue;
				
				auto result = calcKouho(zaiko, top, bottom);
				if(result.empty())continue;
				int innerEmplaceCount = 0;
				for(auto&placedTiles: result){
					if(cur.nextLineIndex==n-1){
						if((placedTiles>>((n-1)*4)) !=0 and (placedTiles&15) != 0) continue;
					}
					if (!Mgr::timer){
						throw logic_error("timeout");
					}
					calcCount++;
					Field nxt = cur;
					nxt.nextLineIndex++;
					rep(j,n) nxt.set(cur.nextLineIndex, j, (placedTiles>>(j*4))&15);
					if(!checkConnectivity(nxt, cur.nextLineIndex)){
						continue;
					}
					if(cur.nextLineIndex+1==n){
						// 発見！
						answerObserver.createMove(f, nxt);
						continue;
					}
					if(innerEmplaceCount == 0){
						innerEmplaceCount++;
						emplaceCount++;
						q.push_front(nxt);
					}else if(emplaceCount <= 10){
						emplaceCount++;
						q.push_back(nxt);
					} else break;
				}
			}
		}
	} catch(logic_error& e) {

	}
}

/*
 * 　 方針1: 同じ数に対しては事前に割り当てを決めて、順列として解く
 * 　　　　　　情報は多いが、N=10で長さ99の順列になって辛そう
 * 　 方針2: 各盤面ごと、良さそうなものを逐次採用していく？
 * 　　　　　　よくわからん
 * ☆ 方針3: 列、行を横>縦>横>縦と確定させて、探索範囲を絞って最後に3x3を解く
 * 　　　　　　途中で奇置換が確定する割り当てをすると解けなくなる
 * 　　　　　　でも後でどうにかなると思いたい
 */ 

struct SearchNode{
	Field&f; Field&target;
	SearchNode(Field&f, Field&target):f(f), target(target){
		fixed.reset();
	}

	int cRow=0, cColumn=0;
	HashSet<int> kouho;
	bitset<100> fixed; // 固定された座標のフラグ

	inline int encode(int i, int j) { return i*n+j; }
	inline pii decode(int h) { return pii(h/n, h%n); }
	inline void fix(int i, int j){
//		if(!isFixed(i,j))debug("!!! fix", i,j);
		fixed[encode(i,j)] = true;
	}
	inline void unfix(int i, int j){
//		if(isFixed(i,j))debug("!!! unfix", i,j);
		fixed[encode(i,j)] = false;
	}
	inline bool isFixed(int i, int j){
//		// debug("!!! query", i,j);
		return fixed[encode(i,j)];
	}
	void considerCurrentRow() {
		bool isAdded = false;
		rep(j,n){
			if(cRow>=n-2 and j>=n-2)continue;
			if(f.get(cRow, j) == target.get(cRow, j)){ 
				if(cRow+2==n and j and !isFixed(cRow+1, j-1)) continue;
				fix(cRow,j);
				continue; 
			}
			kouho.insert(encode(cRow, j));
			isAdded = true;
			break;
		}
		if(!isAdded){
			if(cRow+1 != n-1) {
//				debug("ADD row :", cRow ,"->", cRow+1);
				cRow++;
				considerCurrentRow();
			}
			return;
		}
		rrep(j,n){
			if(cRow>=n-2 and j>=n-2)break;
			if(!isFixed(cRow, cColumn)) break;
			if(f.get(cRow, j) == target.get(cRow, j)){ fix(cRow,j); continue; }
			kouho.insert(encode(cRow, j));
			break;
		}
	}
	void considerCurrentColumn() {
		bool isAdded = false;
		rep(i,n){
			if(cColumn>=n-2 and i>=n-2)continue;
			if(cColumn+2==n and i and !isFixed(i-1, cColumn+1)) continue;
			if(f.get(i, cColumn) == target.get(i, cColumn)){ fix(i, cColumn); continue; }
			kouho.insert(encode(i, cColumn));
			isAdded = true;
			break;
		}
		if(!isAdded){
			if(cColumn+1 != n-1) {
//				debug("ADD column :", cColumn ,"->", cColumn+1);
				cColumn++;
				considerCurrentColumn();
			}
			return;
		}
		rrep(i,n){
			if(cColumn>=n-2 and i>=n-2)break;
			if(!isFixed(cRow, cColumn)) break;
			if(f.get(i, cColumn) == target.get(i, cColumn)){ fix(i, cColumn); continue; }
			kouho.insert(encode(i, cColumn));
			break;
		}
	}
	bool considerAlreadyFitted() {
		bool ret = false;
		vi eraseIndex;
//		debug("ALREADY", kouho);
		for(auto&k:kouho){
//			debug("  ", f.get(k), target.get(k), isFixed(k/n, k%n));
			if(f.get(k) == target.get(k)){
				if(k%n and k/n==n-2 and !isFixed(n-1, k%n-1)) continue;
				if(k/n and k%n==n-2 and !isFixed(k/n-1, n-1)) continue;
				fix(k/n, k%n);
				ret = true;
//				debug("!", decode(k), "is already fitted");
				eraseIndex.emplace_back(k);
			}
		}
		for(auto&i:eraseIndex) kouho.erase(i);

		// kouho上にblankがあると判定が難しくなるので避ける
		for(auto&k:kouho){
			if(f.get(k) == 0){
//				debug("! brank is in Kouho", kouho, "->", decode(k));
				auto [goalY, goalX] = decode(k);
				vvi distMap(n, vi(n, 32));
				queue<pii> q;
				q.emplace(goalY, goalX);
				distMap[goalY][goalX] = 0;
				//bfs
				while(!q.empty()){
					auto [i, j] = q.front(); q.pop();
					// move euler adjacent
					rep(k,4){
						int ny = i+dy[k], nx = j+dx[k];
						if(ny<0 || ny>=n || nx<0 || nx>=n) continue;
						if(!isFixed(ny,nx) and chmin(distMap[ny][nx], distMap[i][j]+1)){
							if(kouho.find(encode(ny, nx)) == kouho.end()) {
								moveBlankTo(ny, nx);
								return ret;
							}
							q.emplace(ny, nx);
						}
					}
				}
			}
		}
		return ret;
	}

	inline int manhattanDist(int h1, int h2) {
		return abs(h1/n-h2/n)+abs(h1%n-h2%n);
	}

	// 次の行動は、座標firstのものをsecondに持っていくこと
	pii decideMoveTile() {
//		debug("  decide start");
		// TODO?: 候補のマスが空白ならどうにかする
		int currentBlank = encode(f.by, f.bx);
		int minDist = 32, minTilePos = 0, minTargetPos = 0;
		vvi positionsByTile(16);
		rep(i,cRow,n)rep(j,cColumn,n)if(!isFixed(i,j)){
			positionsByTile[f.get(i,j)].emplace_back(encode(i,j));
		}

		for(auto&k:kouho){
			for(auto&pos:positionsByTile[target.get(k)]){
				int dist = manhattanDist(currentBlank, pos) + manhattanDist(pos, k);
				if(chmin(minDist, dist)) {
					minTilePos = pos;
					minTargetPos = k;
				}
			}
		}
//		debug("  decide finish :", "move to", decode(minTargetPos), "from", decode(minTilePos), "=", minDist);
		kouho.erase(minTargetPos);
		return {minTilePos, minTargetPos};
	}

	// f.by, f.bxをfixed制約の上でposに移動
	void moveBlankTo(int y, int x){
//		debug("      move Blank", pii(f.by,f. bx), "to", decode(encode(y,x)));
		vvi distMap(n, vi(n, 32));
		queue<pii> q;
		q.emplace(y, x);
		distMap[y][x] = 0;
		//bfs
		while(!q.empty()){
			auto [i, j] = q.front(); q.pop();
			// move euler adjacent
			rep(k,4){
				int ny = i+dy[k], nx = j+dx[k];
				if(ny<0 || ny>=n || nx<0 || nx>=n) continue;
				if(!isFixed(ny,nx) and chmin(distMap[ny][nx], distMap[i][j]+1)){
					q.emplace(ny, nx);
				}
			}
			if(distMap[f.by][f.bx] != 32) break;
		}
		if(distMap[f.by][f.bx] == 32) {
//			debug(distMap);
			throw new runtime_error("moveBlankTo failed");
		}

		int prop=0;
		while(f.by != y || f.bx != x){
			prop++;
			rep(k,4){
				int ny = f.by+dy[k], nx = f.bx+dx[k];
				if(ny<0 || ny>=n || nx<0 || nx>=n) continue;
				if(distMap[ny][nx]+1 == distMap[f.by][f.bx]){
//					debug("        move blank step: move to ", "_LU_R___D"[1<<k]);
					f.move((DIR)(1<<k));
					break;
				}
			}
			if(prop==32){
//				debug(distMap);
				throw new runtime_error("moveBlankTo failed");
			}
		}
	}
	
	int moveTileAdjacent(int tilePos, DIR d) {
//		debug("    step: move to ", "_LU_R___D"[d]);
		int targetPos = 0;
		switch(d){
			case DIR::UP: targetPos = tilePos-n; break;
			case DIR::DOWN: targetPos = tilePos+n; break;
			case DIR::LEFT: targetPos = tilePos-1; break;
			case DIR::RIGHT: targetPos = tilePos+1; break;
		}
		fix(tilePos/n, tilePos%n);
		moveBlankTo(targetPos/n, targetPos%n);
		unfix(tilePos/n, tilePos%n);
		f.move((DIR)DirToInverse[d]);
		return targetPos;
	}

	vector<pair<int, DIR>> bfs(int from, int to){
		auto [goalY, goalX] = decode(to);
		auto [startY, startX] = decode(from);
		vvi distMap(n, vi(n, 32));
		queue<tl3> q;
		q.emplace(goalY, goalX, 0);
		distMap[goalY][goalX] = 0;
		//bfs
		while(!q.empty()){
			auto [i, j, cnd] = q.front(); q.pop();
			// move euler adjacent
			rep(_k,4){
				int k=cnd ? _k : 3-_k;
				int ny = i+dy[k], nx = j+dx[k];
				if(ny<0 || ny>=n || nx<0 || nx>=n) continue;
				if(!isFixed(ny,nx) and chmin(distMap[ny][nx], distMap[i][j]+1)){
					q.emplace(ny, nx, 1-cnd);
				}
			}
			if(distMap[startY][startX] != 32) break;
		}
		// debug_f(distMap);
		if(distMap[startY][startX] == 32) {
			throw new runtime_error("bfs failed");
		}
//		debug(distMap);

		int prop=0;
		vector<pair<int, DIR>> path;
		while(startY != goalY || startX != goalX){
			prop++;
			rep(k,4){
				int ny = startY+dy[k], nx = startX+dx[k];
				if(ny<0 || ny>=n || nx<0 || nx>=n) continue;
				if(distMap[ny][nx]+1 == distMap[startY][startX]){
					startY=ny; startX=nx;
					path.emplace_back(encode(ny,nx), (DIR)(1<<k));
					break;
				}
			}
			if(prop==32){
//				debug(distMap);
				throw new runtime_error("bfs failed");
			}
		}
		return path;
	}

	bool moveTile(int tilePos, int targetPos) {
//		debug("  move start :", "to", decode(targetPos), "from", decode(tilePos));
		// tile -> targetPosへの、fixedを考慮した最短経路を求める
		// 経路の1歩先にblankを行かせればOK
		auto path = bfs(tilePos, targetPos);

		for(auto&[_, nextDir]:path){
			tilePos = moveTileAdjacent(tilePos, nextDir);
		}
		if(tilePos == targetPos) {
			fix(targetPos/n, targetPos%n);
			return false;
		}
		return true;
	}

	// 次の行動は、座標firstのものをsecondに持っていくこと
	int decideMoveTileByType(int targetPos, int type) {
//		debug("  decide start");
		// TODO?: 候補のマスが空白ならどうにかする
		int currentBlank = encode(f.by, f.bx);
		int minDist = 32, minTilePos = -1;
		vi positionsByTile;
		rep(i,cRow,n)rep(j,cColumn,n)if(!isFixed(i,j) and f.get(i,j) == type){
			positionsByTile.emplace_back(encode(i,j));
		}
//		debug(cRow,cColumn,type, isFixed(9,7), ":",positionsByTile);


		for(auto&pos:positionsByTile){
			int dist = manhattanDist(currentBlank, pos) + manhattanDist(pos, targetPos);
			if(chmin(minDist, dist)) {
				minTilePos = pos;
			}
		}
//		debug("  decide finish :", "move to", decode(targetPos), "from", decode(minTilePos), "=", minDist);
		return minTilePos;
	}

	bool Last2x2(){
		debug("LAST 2x2!");
		const auto judge = [&](Field&fc){
			return fc.get(n-2, n-2) == target.get(n-2, n-2)
			   and fc.get(n-2, n-1) == target.get(n-2, n-1)
			   and fc.get(n-1, n-2) == target.get(n-1, n-2)
			   and fc.get(n-1, n-1) == target.get(n-1, n-1);
		};

		int turn = 32;
		Field mn = f;
		{
			Field fc = f;
			rep(i,13){
				if(judge(fc)){
					if(chmin(turn, i)) mn = fc;
					break;
				}
				if(fc.by == n-2 and fc.bx == n-2)fc.move(DIR::RIGHT);
				else if(fc.by == n-2 and fc.bx == n-1)fc.move(DIR::DOWN);
				else if(fc.by == n-1 and fc.bx == n-1)fc.move(DIR::LEFT);
				else if(fc.by == n-1 and fc.bx == n-2)fc.move(DIR::UP);
			}
		}
		{
			Field fc = f;
			rep(i,13){
				if(judge(fc)){
					if(chmin(turn, i)) mn = fc;
					break;
				}
				if(fc.by == n-2 and fc.bx == n-2)fc.move(DIR::DOWN);
				else if(fc.by == n-1 and fc.bx == n-2)fc.move(DIR::RIGHT);
				else if(fc.by == n-1 and fc.bx == n-1)fc.move(DIR::UP);
				else if(fc.by == n-2 and fc.bx == n-1)fc.move(DIR::LEFT);
			}
		}
		if(turn != 32) {
			f=mn;
			return true;
		}
		return false;
	}

	int finishStatus = 0;
	bool checkRecentTwo(){
//		debug(kouho);
		if(kouho.empty()){
			// 2x2のはず...
			finishStatus = Last2x2() ? 2 : 1;
			return false;
		}

		// 1要素の救出
		{ // 列
			int cnt=0; vi p;
			rep(i,n)if(!isFixed(i, cColumn)){
				if(++cnt == 3) break;
				p.push_back(encode(i,cColumn));
			}
			if(cnt==1){
//				debug("Special Operation: only one");
				if(auto [y,x]=decode(p[0]); y == n-1){
					unfix(y-1,x);
					kouho.insert(encode(y-1,x));
				}else{
					unfix(y+1,x);
					kouho.insert(encode(y+1,x));
				}
				return checkRecentTwo();
			}
		}
		{ // 行
			int cnt=0; vi p;
			rep(i,n)if(!isFixed(cRow, i)){
				if(++cnt == 3) break;
				p.push_back(encode(cRow,i));
			}
			if(cnt==1){
//				debug("Special Operation: only one");
				if(auto [y,x]=decode(p[0]); x == n-1){
					unfix(y,x-1);
					kouho.insert(encode(y,x-1));
				}else{
					unfix(y,x+1);
					kouho.insert(encode(y,x+1));
				}
				return checkRecentTwo();
			}
		}

		// 2要素ハマりの救出
		{ // 列
			int cnt=0; vi p;
			rep(i,n)if(!isFixed(i, cColumn)){
				if(++cnt == 3) break;
				p.push_back(encode(i,cColumn));
			}
			if(cnt==2 and p[0] != encode(n-2, n-2)){
//				debug("  Step 1");
				// p[1](右)の位置にp[0]に置きたいものを持ってくる
				int tile1 = decideMoveTileByType(p[0], target.get(p[0]));
				while(moveTile(tile1, p[1]));
				if(f.by==p[0]/n and f.bx==p[0]%n){
					f.move(RIGHT);
				}
				fix(p[0]/n, p[0]%n);
				// p[1](右)の下にp[1]に置きたいものを持ってくる
				int tempTargetPos = p[1]+1;
				int tile2 = decideMoveTileByType(tempTargetPos, target.get(p[1]));
				// p[1]に置きたいもの=target.get(p[1])が現時点でp[0]にしかないと詰むので対策
				if(tile2==-1){
//					debug("  tsumi.");
					bool side1 = encode(f.by, f.bx) == tempTargetPos;
					if(!side1 and encode(f.by, f.bx) != tempTargetPos-n){
						moveBlankTo(tempTargetPos/n-1, tempTargetPos%n);
					}
					const vector<DIR> dirs=side1 ? vector<DIR>{
						LEFT, UP, RIGHT, DOWN, RIGHT, UP, LEFT,
						LEFT, DOWN, RIGHT, UP, RIGHT, DOWN, LEFT, LEFT, UP, RIGHT,
					} : vector<DIR>{
						LEFT, DOWN, RIGHT, UP, RIGHT, DOWN, LEFT,
						LEFT, UP, RIGHT, DOWN, RIGHT, UP, LEFT, LEFT, DOWN, RIGHT,
					};
					for(auto&dir:dirs) f.move(dir);
					return true;
				}

//				debug("  Step 2", tempTargetPos, target.get(p[1]));
				while(moveTile(tile2, tempTargetPos));

				// p[0](左)の位置に移動する
//				debug("  Step 3");
				int targetBlankPos = p[0]+1;
				moveBlankTo(targetBlankPos/n, targetBlankPos%n);
				f.move(LEFT);
				f.move(DOWN);
				f.move(RIGHT);
				unfix(tempTargetPos/n, tempTargetPos%n);
				return true;
			}
		}
		{ // 行
			int cnt=0; vi p;
			rep(i,n)if(!isFixed(cRow, i)){
				if(++cnt == 3) break;
				p.push_back(encode(cRow,i));
			}
			if(cnt==2 and p[0] != encode(n-2, n-2)){
				// p[1](右)の位置にp[0]に置きたいものを持ってくる
//				debug("  Step 1");
				int tile1 = decideMoveTileByType(p[0], target.get(p[0]));
				while(moveTile(tile1, p[1]));
				if(f.by==p[0]/n and f.bx==p[0]%n){
					f.move(DOWN);
				}
				fix(p[0]/n, p[0]%n);

				// p[1](右)の下にp[1]に置きたいものを持ってくる
				int tempTargetPos = p[1]+n;
				int tile2 = decideMoveTileByType(tempTargetPos, target.get(p[1]));
				// p[1]に置きたいもの=target.get(p[1])が現時点でp[0]にしかないと詰むので対策
				if(tile2==-1){
					bool side1 = encode(f.by, f.bx) == tempTargetPos;
					if(!side1 and encode(f.by, f.bx) != tempTargetPos-1){
						moveBlankTo(tempTargetPos/n, tempTargetPos%n-1);
					}
					const vector<DIR> dirs=side1 ? vector<DIR>{
						UP, LEFT, DOWN, RIGHT, DOWN, LEFT, UP,
						UP, RIGHT, DOWN, LEFT, DOWN, RIGHT, UP, UP, LEFT, DOWN
					} : vector<DIR>{
						UP, RIGHT, DOWN, LEFT, DOWN, RIGHT, UP,
						UP, LEFT, DOWN, RIGHT, DOWN, LEFT, UP, UP, RIGHT, DOWN
					};
					for(auto&dir:dirs) f.move(dir);
					return true;
				}

//				debug("  Step 2", tempTargetPos, target.get(p[1]));
				while(moveTile(tile2, tempTargetPos));

				// p[0](左)の位置に移動する
//				debug("  Step 3");
				int targetBlankPos = p[0]+n;
				moveBlankTo(targetBlankPos/n, targetBlankPos%n);
				f.move(UP);
				f.move(RIGHT);
				f.move(DOWN);
				unfix(tempTargetPos/n, tempTargetPos%n);
				return true;
			}
		}

		return false;
	}

	bool calc(){
		int turn = 0;
		while(f.mvLength <= t){
//			debug("========================================");
			turn++;

//			debug("Start consider");
			do{
				considerCurrentRow();
				considerCurrentColumn();
			}while(considerAlreadyFitted());
//			debug("Finish consider");

			// 今見ている列の残りが2つ以下ならその列を揃える
			if(checkRecentTwo()){
				continue;
			}

			// 終わっている可能性がある
			if(finishStatus){
				return finishStatus==2;
			}


			// 候補の中から揃えるものを選ぶ
			auto [tile, to] = decideMoveTile();
			moveTile(tile, to);
		}
		return false;
	}
};

/*
 * fromの盤面をtoに変換するような移動経路を求める
 */
bool solveAtoB(Field&from, Field&to){
	SearchNode node(from, to);
	return node.calc();
}

void solve(Field&f){
	rep(i,1,n*n) findMST(f, i);
	out(answerObserver.answerString);
	debug_f("found:", answerObserver.challenge, "\tn:",n, "\tscore:",answerObserver.maxScore);
}

int main() {
	_TEMPORARY_DEBUG = false;
	/* N=6,7,8,9,10 のケースで、木を作る
	 * T=2*N^3 回以内の操作で達成せよ
	 * T 回以内の操作により、(N−1,N−1) に空きマスを配置した状態の、大きさ N ^2−1 の木を作成出来ることは保証されている
	 * スコアは、全域木を作れなかった場合500000*木の大きさの割合
	 * 全域木の場合、500000*(2-操作回数/T)
	 */
	cin>>n>>t;

	vl init(n);
	{
		string s;
		rep(i,n){
			cin>>s;
			reverse(all(s));
			init[i]=stoll(s,nullptr,16);
		}
	}
	
	Field f(init);
	solve(f);
}
