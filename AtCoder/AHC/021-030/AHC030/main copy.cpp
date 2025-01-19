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

// #define _DEBUG 1
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize("unroll-loops")
// #pragma GCC optimize("inline")


#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("inline")

#ifdef _DEBUG
// #define _GLIBCXX_DEBUG 1
#define GREEDY_SPEC 100000
#else
#define GREEDY_SPEC 600000
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
	static const int TLE = 3000;
	static inline Timer timer = Timer(TLE-70);
	Mgr() {
		cout<<fixed<<setprecision(5);
	}
	~Mgr(){
		cout<<flush;
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

static inline float 
fasterlog2 (float x)
{
  union { float f; uint32_t i; } vx = { x };
  float y = vx.i;
  y *= 1.1920928955078125e-7f;
  return y - 126.94269504f;
}

template<class T=int>
struct UnionFind{
	vi par; vector<T> dist;
	UnionFind(int x){par.assign(x,-1); dist.assign(x,T());}
	int find(int x){return par[x]<0?x:find(par[x]);}
	T depth(int x){return par[x]<0?T():depth(par[x])+dist[x];}
	bool same(int x,int y){return find(x)==find(y);}
	int size(int x){return -par[find(x)];}
	T diff(int x,int y){return same(x,y)?depth(x)-depth(y):LINF;}
	bool unite(int x, int y, T k=T()){
		k+=depth(y); k-=depth(x); k=-k;
		x=find(x); y=find(y);
		if(x==y)return false;
		if(size(x)<size(y)){swap(x,y);k=-k;}
		par[x]+=par[y]; par[y]=x; dist[y]=k;
		return true;
	}
	HashMap<int,vi> groups(){
		HashMap<int,vi> ret;
		rep(i,par.size()) ret[find(i)].push_back(i);
		return ret;
	}
};

string getColorCode(float val, float maxVal) {
	float f = val / maxVal;
	//get hex code , white to red.
	int r = 255 * (1 - f);
	int g = 255 * (1 - f);
	int b = 255;
	stringstream ss;
	ss << "#" << hex << setfill('0') << setw(2) << r << setw(2) << g << setw(2) << b;
	return ss.str();
}

using Cell = short;
using Field = valarray<Cell>;
bool isFieldContained(Field parent, Field&child) {
	return (parent.apply([](Cell x){return max(x, (Cell)0);}) - child).min() >= 0;
}
bool isFieldEqual(Field&a, Field&b) {
	return (a == b).min() == 1;
}


int _n, m; float eps;

struct PlobremInterface {
	virtual void input() = 0;
	virtual void solve() = 0;
};

template<int n>
struct Plobrem: PlobremInterface {
	struct Query {
		int queryCount=0;
		#ifdef _DEBUG
		vector<pair<int,int>> pos;
		Field answer;
		array<float, 2*n*n> queryRand;
		#endif

		void input() {
			#ifdef _DEBUG
			pos.resize(m);
			rep(i,m) cin>>pos[i].first>>pos[i].second;
			answer.resize(n*n);
			rep(i,n*n) cin>>answer[i];
			in(queryRand);
			#endif
		}

		int singleDig(int p) {
			out_f("q", 1, p/n, p%n);
			queryCount++;
			#ifdef _DEBUG
			return answer[p];
			#else
			int v; cin>>v; return v;
			#endif
		}

		float multiDig(vi ps) {
			vi output(1, sz(ps));
			for(auto p: ps) {
				output.push_back(p/n);
				output.push_back(p%n);
			}
			out_f("q", output);
			queryCount++;
			#ifdef _DEBUG
			int correct = 0;
			for(auto p: ps) {
				correct += answer[p];
			}
			auto stdNormal = queryRand[queryCount-1];
			float ave=(sz(ps) - correct) * eps + correct * (1-eps);
			float std=sqrt(sz(ps) * eps * (1-eps));
			auto predicted = stdNormal * std + ave;
			int v = max(0, (int)round(predicted));
			return max(0.f, (v - sz(ps) * eps) / (1 - eps*2));
			#else
			int v; cin>>v; 
			return max(0.f, (v - sz(ps) * eps) / (1 - eps*2));
			#endif
		}

		int sendAnswer(vector<int> ans) {
			queryCount++;
			vector<int> output(1, sz(ans));
			for(auto a: ans) {
				output.push_back(a/n);
				output.push_back(a%n);
			}
			out_f("a", output);
			#ifdef _DEBUG
			rep(i,n*n) {
				bool choiced = find(all(ans), i) != ans.end();
				bool correct = answer[i] > 0;
				if(choiced != correct) {
					return 0;
				}
			}
			return 1;
			#else
			int v; cin>>v; return v;
			#endif
		}
	};

	struct Polyomino {
		int h=0, w=0, d=0;
		Field mino;

		Polyomino() {
			mino.resize(n*n, 0);
		}

		static Polyomino fromInput() {
			Polyomino p;
			cin>>p.d;
			rep(p.d) {
				int y, x; cin>>y>>x;
				p.mino[y*n+x] = 1;
				chmax(p.h, y+1);
				chmax(p.w, x+1);
			}
			return p;
		}
	};

	Field diggedCount, allocatedCount;
	
	struct Overlap {
		bool isDecided = false;
		Polyomino* p;
		vector<Field> states;
		Field sum;
		Field* _allocatedCount;
		Overlap(Polyomino* _p, Field* __allocatedCount): p(_p), _allocatedCount(__allocatedCount) {
			sum.resize(n*n, 0);
			rep(dy, n-p->h+1) rep(dx, n-p->w+1) {
				Field f = p->mino.shift(-(dy*n+dx));
				states.push_back(f);
				sum += f;
			}
		}
		void output() {
			out(p->h, p->w, "/", sz(states));
			rep(i,n){
				rep(j,n) {
					if(sum[i*n+j] == sz(states)){
						cout<<"#######\t";
					} else if(sum[i*n+j] == 0){
						cout<<"       \t";
					} else {
						cout<<(float)sum[i*n+j]/sz(states)<<"\t";
					}
				}
				cout<<endl;
			}
		}
		void removeAt(int idx) {
			sum -= states[idx];
			swap(states[idx], states.back());
			states.pop_back();
			if(!isDecided and sz(states) == 1) {
				isDecided = true;
				*_allocatedCount += states[0];
			}
		}
		void decideNoExist(int idx) {
			if(sum[idx] == 0) return;
			rep(i, sz(states)) if(states[i][idx]) {
				removeAt(i);
				if(sum[idx] == 0) return;
				i--;
			}
		}
		void decideExist(int idx) {
			if(sum[idx] == sz(states)) return;
			rep(i, sz(states)) if(states[i][idx]==0) {
				removeAt(i);
				if(sum[idx] == sz(states)) return;
				i--;
			}
		}

		void decideShape(Field f) {
			if(!isDecided) {
				states.clear();
				states.push_back(f);
				sum = f;
				isDecided = true;
				*_allocatedCount += f;
			}
		}

		bool isNoExist(int idx) {
			return sum[idx] == 0;
		}
		bool isExist(int idx) {
			return sum[idx] == sz(states);
		}
		float prob(int idx) {
			return (float)sum[idx]/sz(states);
		}

	};

	vector<Polyomino> polyominos;
	vector<Overlap> overlaps;
	Query query;

	Plobrem() {
		diggedCount.resize(n*n, -1);
		allocatedCount.resize(n*n, 0);
	}

	auto calculateRange() {
		Field l(n*n, 0), r(n*n, m);
	}

	void input() {
		polyominos.resize(m);
		rep(i,m){
			polyominos[i] = Polyomino::fromInput();
			overlaps.emplace_back(&polyominos[i], &allocatedCount);
		}
		query.input();
	}

		/*
			確率変数Xiを、マスiの持つ値とする。Xiは、0からmまでの整数値を取る。
			事前分布：P(Xi = j) = マスiの値がjである確率。 P(Xi)は正規分布。
			観測したデータ：Xi = マスiの値
			予測したい事後分布：P(j|i) = マスiの値がjである確率

			たとえば、マスi



		*/

	bool turn(){
		/* 最も掘ることで情報が大きそうなマスを掘る */
		pair<float, int> maxEntropy = {0, -1};
		vector<float> probList(m+1, 0);

		{
			vector<vector<valarray<float>>> dp2(m+1, vector<valarray<float>>(m+1));
			dp2[0][0].resize(n*n, 1);
			valarray<float> prob(n*n);
			rep(i,m){
				rep(j,m+1) dp2[i+1][j].resize(n*n, 0);
				rep(j,n*n) prob[j] = overlaps[i].prob(j);
				rep(j,i+1) {
					dp2[i+1][j] += dp2[i][j] * (1-prob);
					if(j<m) dp2[i+1][j+1] += dp2[i][j] * prob;
				}
			}
			if(query.queryCount == 3) {
				vector<float> value16_8(m+1);
				rep(i,m+1) value16_8[i] = dp2[m][i][16*n+8];
				out("#!", diggedCount[16*n+8]);
				out_f(value16_8);
				exit(0);
			}

			rep(i,n*n)if(diggedCount[i]==-1){
				float entropy = 0;
				// マスiに対するエントロピー
				// TODO: 「現在1が出ている」をうまいこと取り込みたい

				#ifndef _DEBUG
				if(dp[0]) entropy = -dp[0]*fasterlog2(dp[0]);
				// if(1-dp[m][0]) entropy -= (1-dp[m][0])*fasterlog2((1-dp[m][0]));
				#endif
				// NOTE: 0のみにすると伸びる（伸びてしまう）
				rep(k,m+1){
					#ifdef _DEBUG
					entropy -= dp2[m][k][i] ? dp2[m][k][i]*fasterlog2(dp2[m][k][i]) : 0;
					#endif
					if(abs(dp2[m][k][i]-1.0) <= 1e-6) {
						diggedCount[i] = k;
					}
				}
				if(chmax(maxEntropy, {entropy, i})){
					rep(k,m+1) probList[k] = dp2[m][k][i];
				}
			}
		}

		if(maxEntropy.second == -1) return false;

		auto cnt = query.singleDig(maxEntropy.second);
		diggedCount[maxEntropy.second] = cnt;

		{
			int minVal = INF, maxVal = -INF;
			rep(i,m+1) if(probList[i] > 0) {
				chmin(minVal, i);
				chmax(maxVal, i);
			}
			// もし掘ったマスの油田数が最小ケース通りなら、現時点で不確定な油田はこのマスにない
			if(cnt==minVal) {
				rep(i,m){
					if(!overlaps[i].isExist(maxEntropy.second)) {
						overlaps[i].decideNoExist(maxEntropy.second);
					}
				}
			}
			// もし掘ったマスの油田数が最大ケース通りなら、現時点で不確定な油田はすべてこのマスにある
			if(cnt==maxVal) {
				rep(i,m){
					if(!overlaps[i].isNoExist(maxEntropy.second)) {
						overlaps[i].decideExist(maxEntropy.second);
					}
				}
			}
		}
		return true;
	}


	pair<bool, vector<Field>> getStrictIslands(Field countData) {
		if(countData.min() < 0) {
			return {false, {}};
		}
		return {true, getIslands(countData)};
	}

	// 境界が確定している島
	vector<Field> getIslands(Field countData) {
		vector<Field> islands;

		Field isVisited; isVisited.resize(n*n, 0);
		rep(i,n*n){
			// bfs
			if(isVisited[i] or countData[i]<=0) continue;
			Field island; island.resize(n*n, 0);
			queue<int> q; q.push(i);
			const vi dy={-1,0,1,0}, dx={0,1,0,-1};
			bool isIsland = true;
			while(!q.empty()){
				auto p = q.front(); q.pop();
				int y=p/n, x=p%n;
				if(isVisited[y*n+x]) continue;
				isVisited[y*n+x] = 1;
				island[y*n+x] = countData[y*n+x];
				rep(k,4){
					int ny=y+dy[k], nx=x+dx[k];
					if(ny<0 or nx<0 or ny>=n or nx>=n) continue;
					if(isVisited[ny*n+nx]) continue;
					if(countData[ny*n+nx] == 0) continue;
					if(countData[ny*n+nx] <= -1) {
						isIsland = false;
						continue;
					}
					q.push(ny*n+nx);
				}
			}
			if(!isIsland) continue;
			islands.push_back(island);
		}

		return islands;
	}

	vector<Field> dp_pool;
	bool turn_greedy(){
		if(dp_pool.empty()) {
			vector<Field> dp(1, allocatedCount), ndp;
			dp.reserve(GREEDY_SPEC);
			ndp.reserve(GREEDY_SPEC);
			rep(i,m)if(!overlaps[i].isDecided) {
				ndp.clear();
				for(auto&f: dp) {
					rep(k,sz(overlaps[i].states)) {
						auto newField = f + overlaps[i].states[k];
						// newFieldがdiggedCountを超えていたら無視
						bool ok=true;
						rep(l,n*n)if(diggedCount[l] != -1){
							if((i==m-1 and newField[l] != diggedCount[l] ) or (i!=m-1 and diggedCount[l]-newField[l] < 0)) {
								ok=false;
								break;
							}
						}
						if(ok) ndp.push_back(newField);
					}
				}
				swap(dp, ndp);
			}
			swap(dp_pool, dp);
		} else {
			vector<Field> ndp;
			ndp.reserve(GREEDY_SPEC);
			for(auto&f: dp_pool) {
				bool ok=true;
				rep(l,n*n)if(diggedCount[l] != -1){
					if(f[l] != diggedCount[l]) {
						ok=false;
						break;
					}
				}
				if(ok) ndp.push_back(f);
			}
			swap(dp_pool, ndp);
		}

		/* 最も掘ることで情報が大きそうなマスを掘る */
		pair<float, int> maxEntropy = {-100000, -1};
		vector<float> probList(m+1, 0);

		rep(i,n*n)if(diggedCount[i]==-1){
			vector<float> values(m+1, 0);
			for(auto&f: dp_pool) values[f[i]] += 1;
			rep(j,m+1) values[j] /= sz(dp_pool);

			float entropy = 0;
			// if(values[0]) entropy = -values[0]*fasterlog2(values[0]);
			// if(1-values[0]) entropy -= (1-values[0])*fasterlog2((1-values[0]));
			rep(k,m+1)if(values[k]){
				entropy -= values[k]*fasterlog2(values[k]);
				if(abs(values[k]-1.0) <= 1e-6) {
					diggedCount[i] = k;
				}
			}
			if(chmax(maxEntropy, {entropy, i})){
				probList = values;
			}
		}
		if(maxEntropy.second == -1) return false;

		auto cnt = query.singleDig(maxEntropy.second);
		diggedCount[maxEntropy.second] = cnt;

		return true;
	}

	void shrink() {
		rep(i,n*n){
			int l=0, r=m;
			rep(j,m){
				if(overlaps[j].isExist(i)) {
					l++;
				}else if(overlaps[j].isNoExist(i)) {
					r--;
				}
			}
			// 既に個数が分かっているマスについて、
			if(diggedCount[i]!=-1){
				// もしあり得る油田の個数の最小値が個数通りなら、他のすべての油田はここには無い
				if(diggedCount[i]==l){
					rep(j,m){
						if(!overlaps[j].isExist(i)) {
							overlaps[j].decideNoExist(i);
						}
					}
				}
				// もしあり得る油田の個数の最大値が個数通りなら、他のすべての油田はここにある
				if(diggedCount[i]==r){
					rep(j,m){
						if(!overlaps[j].isNoExist(i)) {
							overlaps[j].decideExist(i);
						}
					}
				}
			}

			// 個数未定のマスでも、あり得る選択肢が1通りなら数字が確定
			// TODO: これ、turn内の処理で合流しているはず...?
			if(diggedCount[i]==-1){
				if(l==r){
					diggedCount[i] = l;
				}
			}
		}
	}

	// 0: 終了 1: もう1回
	bool check() {
		rep(5) shrink();

		bool isChanged = false;

		// 同型の要素がX個ある時、それぞれがX通りしかないなら割り当ててよい
		{
			UnionFind uf(m);
			rep(i,m)if(!overlaps[i].isDecided) rep(j,i)if(!overlaps[j].isDecided){
				if(isFieldEqual(polyominos[i].mino, polyominos[j].mino)) {
					uf.unite(i, j);
				}
			}
			for(auto [_, g]: uf.groups()) {
				rep(i,g.size()){
					if(sz(overlaps[g[i]].states) == (int)g.size()) {
						auto res = overlaps[g[i]].states[i];
						overlaps[g[i]].decideShape(res);
					}
				}
			}
		}
		// shrink();

		// 周囲を0で囲まれた領域があり、それに内包される未確定の油田が1つなら、場所が確定する
		// cout<<"#================================="<<endl;
		{
			float c=0;
			rep(i,m) c+= log10f(sz(overlaps[i].states));
			debug(query.queryCount, "\t", pow(10, c));
		}

		// 島についての議論
		{
			int minimumMinoSize = INF;
			auto islands = getIslands(diggedCount - allocatedCount);
			islands.reserve(10000);

			for(auto&island : islands){
				minimumMinoSize = INF;
				rep(i,m)if(!overlaps[i].isDecided) {
					chmin(minimumMinoSize, polyominos[i].d);
				}

				bool islandDecided = false;
				// out("# Island");
				// rep(j,n){
				// 	cout<<"#    ";
				// 	rep(k,n){
				// 		if(island[j*n+k] == 0) cout<<" ";
				// 		else cout<<island[j*n+k];
				// 	}
				// 	cout<<endl;
				// }

				vvi containsStates(m);
				rep(i,m)if(!overlaps[i].isDecided){
					// 各油田ごとに、その島に内包される配置パターンを列挙
					vi contains;
					rep(j,sz(overlaps[i].states)) {
						auto&state = overlaps[i].states[j];

						{
							// 島にその油田を置いた後の形が達成不能なら、その配置はあり得ない
							// TODO: 現状、油田の大きさが3以下かどうかだけ見ている
							auto [isValid, afterPlaced] = getStrictIslands(island-state);
							if(!isValid) {
								// 島に置けてない
								continue;
							}
							
							bool isEnable = true;
							for(auto&after: afterPlaced) {
								if(after.apply([](Cell x){return min(x, (Cell)1);}).sum() < minimumMinoSize) {
									isEnable = false;
									break;
								}
							}
							if(!isEnable) {
								overlaps[i].removeAt(j);
								j--;
								continue;
							}
						}

						// 島と完全に形状と数値が一致しているやつは、確定して問題ない
						if(isFieldEqual(island, state)) {
							overlaps[i].decideShape(state);
							// out("# Decided Equal", i);
							i=m;
							islandDecided = true;
							containsStates.clear();
							containsStates.resize(m);
							isChanged = true;
							// return true;
							break;
						}

						if(isFieldContained(island, state)) {
							contains.push_back(j);
						}
					}

					if(sz(contains) > 0){
						containsStates[i] = contains;
					}
				}
				if(islandDecided) continue;

				// 特定のマスをカバー可能な油田がただ1つの形状であれば確定
				{
					vector<HashSet<int>> placeableShapeSet(n*n);
					vi shapeTypeId(m); iota(all(shapeTypeId), 0);
					vvi stateMatrix(m, vi(n*n, -1));
					rep(i,m)if(sz(containsStates[i]) > 0){
						rep(j,i) if(sz(containsStates[j]) > 0) {
							if(isFieldEqual(polyominos[i].mino, polyominos[j].mino)) {
								shapeTypeId[i] = shapeTypeId[j];
								break;
							}
						}
						for(auto idx: containsStates[i]) {
							rep(j,n*n) if(overlaps[i].states[idx][j]) {
								placeableShapeSet[j].insert(shapeTypeId[i]);
								stateMatrix[i][j] = idx;
							}
						}
					}
					rep(i,n*n) if(sz(placeableShapeSet[i]) == 1) {
						int minoIdx = *begin(placeableShapeSet[i]);
						overlaps[minoIdx].decideShape(overlaps[minoIdx].states[stateMatrix[minoIdx][i]]);
						containsStates[minoIdx].clear();
						// out("# Decided", minoIdx);
						auto [isValid, afterPlaced] = getStrictIslands(island-overlaps[minoIdx].states[0]);
						islands.insert(islands.end(), all(afterPlaced));
						isChanged = true;
						// return true;
						break;
					}
				}
			}
		}
		shrink();
		// loose-島についての議論
		if(query.queryCount%2 == 0){
			int minimumMinoSize = INF;
			auto virtualField = (diggedCount - allocatedCount).apply([](Cell x){return x >= 0 ? x : numeric_limits<Cell>::max();});
			auto islands = getIslands(virtualField);
			islands.reserve(10000);

			for(auto&island : islands){
				minimumMinoSize = INF;
				rep(i,m)if(!overlaps[i].isDecided) {
					chmin(minimumMinoSize, polyominos[i].d);
				}

				bool islandDecided = false;

				vvi containsStates(m);
				bool placeableAny = false;
				rep(i,m)if(!overlaps[i].isDecided){
					// 各油田ごとに、その島に内包される配置パターンを列挙
					vi contains;
					rep(j,sz(overlaps[i].states)) {
						auto&state = overlaps[i].states[j];

						{
							// 島にその油田を置いた後の形が達成不能なら、その配置はあり得ない
							// TODO: 現状、油田の大きさが3以下かどうかだけ見ている
							auto [isValid, afterPlaced] = getStrictIslands(island-state);
							if(!isValid) {
								// 島に置けてない
								continue;
							}


							bool isEnable = true;
							for(auto&after: afterPlaced) {
								// after 
								// out("#! after", after.min());
								Cell minVal= numeric_limits<Cell>::max(), count = 0;
								rep(k,n*n) {
									if(after[k] == 0) continue;
									minVal = min(minVal, after[k]);
									count++;
									if(count >= minimumMinoSize) break;
								}
								if(count >= minimumMinoSize) continue;
								if(minVal >= 100) {
									//このエリアは全て空というだけ。セーフ
									continue;
								}
								if(count < minimumMinoSize) {
									isEnable = false;
									break;
								}
							}
							
							if(!isEnable) {
								overlaps[i].removeAt(j);
								j--;
								continue;
							}
						}

						if(!isFieldContained(island, state)) continue;

						contains.push_back(j);
						placeableAny = true;
					}

					if(sz(contains) > 0){
						containsStates[i] = contains;
					}
				}
				if (!placeableAny) {
					rep(i,n*n) {
						if(island[i] > 0) {
							diggedCount[i] = allocatedCount[i];
						}
					}
					continue;
				}
				if(islandDecided) continue;

				// 特定のマスをカバー可能な油田がただ1つの形状であれば確定
				{
					vector<HashSet<int>> placeableShapeSet(n*n);
					vi shapeTypeId(m); iota(all(shapeTypeId), 0);
					vector<vvi> stateMatrix(m, vvi(n*n, vi()));
					vector<vvi> stateDeMatrix(m, vvi(n*n, vi()));
					rep(i,m)if(sz(containsStates[i]) > 0){
						rep(j,i) if(sz(containsStates[j]) > 0) {
							if(isFieldEqual(polyominos[i].mino, polyominos[j].mino)) {
								shapeTypeId[i] = shapeTypeId[j];
								break;
							}
						}
						for(auto idx: containsStates[i]) {
							rep(j,n*n) if(overlaps[i].states[idx][j]) {
								placeableShapeSet[j].insert(shapeTypeId[i]);
								stateMatrix[i][j].push_back(idx);
							}
						}
					}
					// NOTE: ADD if(diggedCount[i] != -1)
					rep(i,n*n) if(diggedCount[i]-allocatedCount[i] >= 1) if(sz(placeableShapeSet[i]) == 1) {
						int minoIdx = *begin(placeableShapeSet[i]);
						if(sz(stateMatrix[minoIdx][i]) == 1){
							overlaps[minoIdx].decideShape(overlaps[minoIdx].states[stateMatrix[minoIdx][i][0]]);
							containsStates[minoIdx].clear();
							// out("# Decided", minoIdx, i/n ,i%n);
							auto [isValid, afterPlaced] = getStrictIslands(island-overlaps[minoIdx].states[0]);
							islands.insert(islands.end(), all(afterPlaced));
							isChanged = true;
							// return true;
							break;
						} else if (sz(stateMatrix[minoIdx][i]) < sz(overlaps[minoIdx].states)) {
							// いずれかで確定
							// TODO: この対応は外でやる
							// overlaps[minoIdx].decideExist(i);
							for(auto idx: stateDeMatrix[minoIdx][i] | ranges::views::reverse) {
								overlaps[minoIdx].removeAt(idx);
							}
							debug_f("!", sz(stateMatrix[minoIdx][i]));
						}
					}
				}
			}
		}
		shrink();

		return isChanged;
	}

	void solve() {
		// emptyCheck();
		while(query.queryCount < 2*n*n-1){ // ラスト1回は答えを送るためのクエリ
			if(false){
				out("#############################################################");
				out("# queryCount", query.queryCount);
				out("# diggedCount");
				rep(i,n){
					cout<<"#    ";
					rep(j,n){
						if(diggedCount[i*n+j] == -1) cout<<"-";
						else cout<<diggedCount[i*n+j];
					}
					cout<<endl;
				}
				out("# allocatedCount");
				rep(i,n){
					cout<<"#    ";
					rep(j,n){
						cout<<allocatedCount[i*n+j];
					}
					cout<<endl;
				}
				out("# digged-allocated");
				rep(i,n){
					cout<<"#    ";
					rep(j,n){
						cout<<diggedCount[i*n+j]-allocatedCount[i*n+j];
					}
					cout<<endl;
				}
				out("###################");
			}
			if(true){
				vs colors(n*n);
				float fMax=1;
				rep(i,n*n) {
					float f=0;
					rep(j,m) f += overlaps[j].prob(i);
					chmax(fMax, f);
				}

				rep(i,n*n) {
					float f=0;
					rep(j,m) f += overlaps[j].prob(i);
					colors[i] = getColorCode(f, fMax);
					if(f==0) colors[i] = "#000000";
				}

				rep(i,m)if(sz(overlaps[i].states) == 1) {
					rep(j,n*n)if(overlaps[i].sum[j] == 1) {
						colors[j] = "#00FF00";
					}
				}
				rep(i,n*n) out("#c", i/n, i%n, colors[i]);
			}


			ll c=1;
			rep(i,m) {
				if(LINF/c < sz(overlaps[i].states)) {
					c=LINF;
					break;
				}
				c*= sz(overlaps[i].states);
			}

			if(c<=GREEDY_SPEC){
				if(!turn_greedy()) {
					break; // TODO: checkで分岐しきるべき
				}
			} else {
				if(!turn()) {
					// out("# break Turn");
					break; // TODO: checkで分岐しきるべき
				}
			}
			while(check());
			// while(check());
			rep(3) shrink();

			bool isAllDecided = true;
			rep(i,m){
				isAllDecided &= overlaps[i].isDecided;
				// out("# overlap", i, overlaps[i].isDecided, sz(overlaps[i].states));
			}
			if(isAllDecided) break;
		}

		vector<int> ans;
		rep(i,n*n){
			if(diggedCount[i]!=-1) {
				if(diggedCount[i]) ans.push_back(i);
				continue;
			}
			int l=0;
			rep(j,m){
				if(overlaps[j].isExist(i)) {
					l++;
				}
			}
			if(l>0){
				ans.push_back(i);
			}
		}
		auto result = query.sendAnswer(ans);
		if (result == 1) return;
		// rep(i,m){
		// 	overlaps[i].output();
		// }
		assert(false);
	}
};


const map<int, PlobremInterface*> plobrems = {
	{10, new Plobrem<10>()},
	{11, new Plobrem<11>()},
	{12, new Plobrem<12>()},
	{13, new Plobrem<13>()},
	{14, new Plobrem<14>()},
	{15, new Plobrem<15>()},
	{16, new Plobrem<16>()},
	{17, new Plobrem<17>()},
	{18, new Plobrem<18>()},
	{19, new Plobrem<19>()},
	{20, new Plobrem<20>()},
};

int main() {
	cin>>_n>>m>>eps;

	auto plobrem = plobrems.at(_n);
	plobrem->input();
	plobrem->solve();
}