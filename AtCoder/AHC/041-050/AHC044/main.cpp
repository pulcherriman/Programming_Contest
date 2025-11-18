/**
 * C++23 Template @ AtCoder
 * - official support library
 *   - AC Library@1.5.1
 *   - Boost@1.82.0
 *   - GMP@6.2.1
 *   - Eigen@3.4.0-2ubuntu2
 * - compile option
 *   g++-12 -std=gnu++2b -O2 -DONLINE_JUDGE -DATCODER \
 *      -Wall -Wextra \
 *      -mtune=native -march=native \
 *      -fconstexpr-depth=2147483647 -fconstexpr-loop-limit=2147483647 -fconstexpr-ops-limit=2147483647 \
 *      -I/opt/ac-library -I/opt/boost/gcc/include -L/opt/boost/gcc/lib \
 *      -o a.out Main.cpp \
 *      -lgmpxx -lgmp \
 *      -I/usr/include/eigen3
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
		static inline size_t hash_rnd = Random(0,true)(); // 適当に初期化
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
 
 /* ------ ここから下が必要な実装 ------ */
 
 using Flag = __int128_t;
 const int N = 100, L=500000;
 vi T(N);
 
 /**
  * 与えられた遷移先配列 t を用いて L=500000 回移動したとき、
  * 各頂点が出現した回数 cnt[i] と、与えられた理想回数 T[i] の誤差を
  * 合計した値を「スコア」として返す。
  */
 inline bool flag(Flag&f, int i) { return (f >> i) & 1; }
 inline void toggle(Flag&f, int i) { f ^= ((Flag)1 << i); }
 

 
vi test(const vi&input) {
	vi sim(N,2);
	vi lazy(N+1,0);
	vi diff(N,0);
	rrep(i,N){
		lazy[i] += lazy[i+1];
		diff[i] += lazy[i];
		sim[i] += diff[i];
		if(input[i]==i) continue;
		lazy[i]+=sim[i];
		if(input[i])lazy[input[i]-1]-=sim[i];
	}
	return sim;
}

int solve1(const vi &t, const vi &Tgt){
	auto cnt = test(t);
	int loopTurn = sum(cnt);
	int loopReq = L / loopTurn;
	rep(i,N) cnt[i] *= loopReq;

	int cur = 0;
	Flag vis = 0;
	rep(turn, loopTurn*loopReq, L){
		cnt[cur]++;
		if(flag(vis,cur)){
			toggle(vis,cur);
			cur = (cur + 1) % N;
		} else {
			toggle(vis,cur);
			cur = t[cur];
		}
	}

	int res = 0;
	rep(i,N){
		res += abs(cnt[i] - Tgt[i]);
	}
	return res;
}


auto solver1() {
	// 例: T[i] が大きい順に並べてみるなど (高速化の一例)
	HashMap<int,int> imap, iunmap;
	{
		vp tmp;
		rep(i,1,N) tmp.pb({T[i],i});
		sort(rall(tmp));
		imap[0]   = 0;
		iunmap[0] = 0;
		rep(i,1,N) {
			imap[tmp[i-1].second]   = i;
			iunmap[i]               = tmp[i-1].second;
		}
	}
	sort(T.rbegin(), T.rend()-1);
 
	// 初期解を作る (適当)
	vi cur(N,0); iota(all(cur), 0);
	rep(i,2,N) cur[i] = i-1;
	int curScore = solve1(cur, T);
 
	// best にもコピーしておく
	vi best = cur;
	int bestScore = curScore;
 
	// 焼きなまし用パラメータ
 	int challenge=0;

	rrep(tgt,2,N){
		int prev = cur[tgt];
		rrep(to, 0, tgt+1){
			challenge++;
			cur[tgt] = to;
			int newScore = solve1(cur, T);
			if(newScore < curScore){
				curScore = newScore;
				if(chmin(bestScore, newScore)){
					best = cur;
					debug("Update greedy:", bestScore);
				}
			} else {
				cur[tgt] = prev;
			}
		}
	}

	// 最終的な best 解を出力
	// (例: ans[i] = { best[i], (i+1)%N } としているが、元コードの出力例に合わせる)
	vp ans(N);
	// imap/iunmapのマッピングを反映（例として：ans[iunmap[i]] = (iunmap[best[i]], iunmap[(i+1)%N])）

	rep(i,N){
		ans[iunmap[i]] = { iunmap[best[i]], iunmap[(i+1) % N] };
	}
	rep(i,N) out(ans[i].first, ans[i].second);
 
	debug_f("Challenge", challenge);
	debug_f("predicted", 1000000-bestScore);
}

 int main() {
	// 入力を受け取る
	{
		def(int,_,__);
		in(T);
	}
	auto T_backup = T;
	solver1();
	T = T_backup;
 	return 0;
 }
 