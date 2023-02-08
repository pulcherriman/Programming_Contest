// cargo run --release --bin tester ../../../a.exe < in/0008.txt > out/0008.txt
#pragma GCC target("avx2")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("inline")
#pragma GCC diagnostic ignored "-Wunused-value"
#ifdef _DEBUG
// #define _GLIBCXX_DEBUG 1
#undef _DEBUG
#endif

/* 
 * Include Headers
 */
#include <algorithm>
#include <iostream>
#include <cstdio>
#include <map>
#include <numeric>
#include <cmath>
#include <set>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <complex>
#include <string.h>
#include <unordered_set>
#include <unordered_map>
#include <bitset>
#include <iomanip>
#include <sys/time.h>
#include <tuple>
#include <random>
#include <chrono>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;

/*
 * Additional Type Definition
 */
using vb=vector<bool>;
using vvb=vector<vb>;
using vi=vector<int>;
using vvi=vector<vi>;
using pii=pair<int,int>;
using vp=vector<pii>;
using ti2=tuple<int,int>;
using ti3=tuple<int,int,int>;
using ti4=tuple<int,int,int,int>;
using vs=vector<string>;
template<class K> using IndexedSet=__gnu_pbds::tree<K,__gnu_pbds::null_type,less<K>,__gnu_pbds::rb_tree_tag,__gnu_pbds::tree_order_statistics_node_update>;
template<class K> using HashSet=__gnu_pbds::gp_hash_table<K,__gnu_pbds::null_type>;
template<class K,class V> using IndexedMap=__gnu_pbds::tree<K,V,less<K>,__gnu_pbds::rb_tree_tag,__gnu_pbds::tree_order_statistics_node_update>;
template<class K,class V> using HashMap=__gnu_pbds::gp_hash_table<K,V>;
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
#define siz(a) ((int)(a).size())

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
		return pargs(cerr, args...)<<'\n';
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
	constexpr result_type operator()(){return operator()(min(),max());}
	static constexpr result_type max(){return numeric_limits<result_type>::max();}
	static constexpr result_type min(){return 0;}
	constexpr Random(const bool&isDeterministic):y(isDeterministic?2463534242ll:chrono::system_clock::now().time_since_epoch().count()){}
	constexpr result_type operator()(result_type a, result_type b){return next()%(b-a)+a;}
	result_type getSeed(){return y;}
	void setSeed(result_type seed){y=seed;}
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
	uint64_t get() const{return (getClocks()-start)/ClocksPerMsec;}
	operator bool()const{return getClocks()<limit;}
};
void wait(const int&msec){Timer tm(msec); while(tm);}

struct Mgr {
	static const int TLE = 5000;
	static inline Timer timer = Timer(TLE-20);
	Mgr() {
		cerr<<fixed<<setprecision(3);
	}
	~Mgr(){
		debug_f(timer.get(), "ms")<<flush;
	}
} _manager;


struct Graph {
	int n;
	vvb edges;
	Graph(){}
	Graph(int _n):n(_n),edges(n, vb(n, 0)){}
	Graph(string s){
		n = ceil(sqrt(s.size()*2));
		edges = vvb(n, vb(n, 0));
		int index = 0;
		rep(i,n) rep(j,i+1,n) addEdge(i, j, s[index++] == '1');
	}
	void addEdge(int a, int b, bool val=1){
		edge_count += val - edges[a][b];
		edges[a][b] = edges[b][a] = val;
	}
	string getStrExpression(){
		string s(n*(n-1)/2, '0');
		int index=0;
		rep(i,n)rep(j,i+1,n){
			if(edges[i][j]) s[index] = '1';
			index++;
		}
		return s;
	}
	vi GetDegrees(){
		vi degrees(n);
		rep(i,n)rep(j,n) degrees[i] += edges[i][j];
		sort(all(degrees));
		return degrees;
	}

	int edge_count = 0;
	int getEdgeCount() {
		return edge_count;
	}
};

struct StrategyBase {
	const int QUERY_COUNT = 100;
	int N = 100, M, E;
	vector<Graph> graphs;

	StrategyBase():StrategyBase(100,40){}
	StrategyBase(int m, int e):M(m),E(e){}
	virtual void CreateGraphs() = 0;
	virtual int PredictGraph(Graph&damaged) = 0;

	void PrintGraphsInfo(){
		cout<<N<<endl;
		for(auto&g:graphs)cout<<g.getStrExpression()<<endl;
	}

	#ifdef _DEBUG
	int _current_answer = 0;
	#endif

	// ジャッジが改変した入力を受け取る
	Graph GetDamagedGraph(){
		Graph h(N);

		#ifdef _DEBUG
			int ans; cin>>ans;
			_current_answer = ans;

			Graph g=graphs[ans];
			rep(i,N)rep(j,i+1,N)if(i<j){
				if((int)Random(0,100)<E) g.addEdge(i,j,!g.edges[i][j]);
			}
			vi nodeMap(N,0); iota(all(nodeMap),0);
			shuffle(all(nodeMap), Random);
			rep(i,N)rep(j,i+1,N){
				if(g.edges[i][j]) {
					h.addEdge(nodeMap[i], nodeMap[j]);
				}
			}
		#else
			string s; cin>>s;
			h = Graph(s);
		#endif
		return h;
	}

	int Test(int repeat = 1){
		int failed = 0;
		vi nodeMap(N,0); iota(all(nodeMap),0);
		Graph h(N);
		rep(repeat)rep(g,siz(graphs)){
			shuffle(all(nodeMap), Random);
			rep(i,N)rep(j,i+1,N){
				h.addEdge(nodeMap[i], nodeMap[j], graphs[g].edges[i][j] ^ ((int)(Random(0,100))<E));
			}
			if(PredictGraph(h) != g) failed++;
		}
		float failed_average = (float)failed / repeat / siz(graphs) * 100;
		debug("!", failed_average, "%");
		return round(1e9 / N * pow(0.9, failed_average));
	}

	vi TestAnalysis(int repeat = 1){
		vi result(siz(graphs), 0);
		vi nodeMap(N,0); iota(all(nodeMap),0);
		Graph h(N);
		rep(repeat)rep(g,siz(graphs)){
			shuffle(all(nodeMap), Random);
			rep(i,N)rep(j,i+1,N){
				h.addEdge(nodeMap[i], nodeMap[j], graphs[g].edges[i][j] ^ ((int)(Random(0,100))<E));
			}
			if(PredictGraph(h) != g) result[g]++;
		}
		return result;
	}

};

// エラーが無い場合の理論値解
struct NoErrorStrategy : public StrategyBase {
	NoErrorStrategy(int m, int e):StrategyBase(m,e){}

	void CreateGraphs() override {
		if(M <= 11) N = 4;
		else if(M <= 34) N = 5;
		else N = 6;
		GraphEnumerate(N);
	}

	// グラフの同型判定
	bool isIsomorphic(Graph&g1, Graph&g2){
		if(g1.n!=g2.n) return false;
		int n = g1.n;
		if(g1.GetDegrees() != g2.GetDegrees()) return false;

		vi perm(n); iota(all(perm), 0);
		do {
			bool isIsomorphic = true;
			rep(i,n)rep(j,n){
				if(g1.edges[perm[i]][perm[j]] != g2.edges[i][j]){
					isIsomorphic = false;
					break;
				}
			}
			if(isIsomorphic) return true;
		} while(next_permutation(all(perm)));
		return false;
	}

	// グラフの列挙
	void GraphEnumerate(int node) {
		map<vi, vector<Graph>> graphsByDegrees;
		int edge_count = node*(node-1)/2;
		
		vi nodes(1<<edge_count, 0); iota(all(nodes), 0);
		shuffle(all(nodes), Random);
		for(auto&edges:nodes){
			Graph g(node);
			int index = 0;
			rep(i,node)rep(j,i+1,node){
				if(edges>>index&1) g.addEdge(i, j);
				index++;
			}

			// 同型のグラフがないか
			bool isAlreadyExist = false;
			auto degrees = g.GetDegrees();
			for(auto&g2 : graphsByDegrees[degrees]){
				if(isIsomorphic(g, g2)) {
					isAlreadyExist = true;
					break;
				}
			}
			if(isAlreadyExist) continue;
			graphsByDegrees[degrees].push_back(g);
			graphs.push_back(g);
			if(siz(graphs)>=M) return;
		}
	}

	int PredictGraph(Graph&damaged) override {
		rep(i,M) if(isIsomorphic(damaged, graphs[i])) return i;
		return Random(0,M);
	}
};

struct FailSafeStrategy : StrategyBase {
	FailSafeStrategy(int m, int e):StrategyBase(m,e){}

	void CreateGraphs() override {
		N = 4;
		rep(i,M){
			Graph g(N);
			if(i>=M/2)rep(j,N)rep(k,j+1,N) g.addEdge(j,k);
			graphs.push_back(g);
		}
	}

	int PredictGraph(Graph&damaged) override {
		int edge_count = damaged.getEdgeCount();
		if(edge_count <= 3) return Random(0, M/2);
		else return Random(M/2, M);
	}
};

class FastFourierTransform {
using mycomplex = complex<long double>;
private:
    static void dft(vector<mycomplex>& func, int inverse) {
        int sz = func.size();
        if (sz == 1)return;
        vector<mycomplex> veca, vecb;
        rep(i, sz / 2) {
            veca.push_back(func[2 * i]);
            vecb.push_back(func[2 * i + 1]);
        }
        dft(veca, inverse); dft(vecb, inverse);
        mycomplex now = 1, zeta = polar(1.0, inverse * 2.0 * acos(-1) / sz);
        rep(i, sz) {
            func[i] = veca[i % (sz / 2)] + now * vecb[i % (sz / 2)];
            now *= zeta;
        }
    }
public:
    template<typename T>
    static vector<long double> multiply(vector<T> f, vector<T> g, int ans_size) {
        vector<mycomplex> nf, ng;
        int sz = 1;
        while (sz < ans_size)sz *= 2;
        nf.resize(sz); ng.resize(sz);
        rep(i, f.size()) nf[i] = f[i];
       	rep(i, g.size()) ng[i] = g[i];

        dft(nf, 1);
        dft(ng, 1);
        rep(i, sz)nf[i] *= ng[i];
        dft(nf, -1);
        vector<long double> res;
        rep(i, sz)res.push_back(nf[i].real() / sz);
        return res;
    }
};


struct EdgeCountStrategy : public StrategyBase {
	EdgeCountStrategy(): StrategyBase(){}
	EdgeCountStrategy(int m, int e):StrategyBase(m,e){}

	const static inline vvi n_for_m_e = {
		{5,8,10,12,14,16,17,19,21,22,24,25,27,29,30,32,34,36,38,39,42,44,46,48,51,54,57,60,63,67,71,75,80,85,91,98,100,100,100,100,100},
		{5,8,12,13,16,18,19,21,23,25,26,28,30,32,34,35,38,40,42,44,46,49,51,54,57,60,63,67,70,74,79,84,89,95,100,100,100,100,100,100,100},
		{6,10,12,15,16,19,21,23,25,27,29,31,33,35,37,39,41,44,46,48,51,54,56,59,62,66,69,73,78,82,87,92,98,100,100,100,100,100,100,100,100},
		{6,11,13,16,19,21,23,25,27,29,32,34,36,38,40,43,45,47,50,53,55,58,61,65,68,72,76,80,85,89,95,100,100,100,100,100,100,100,100,100,100},
		{6,11,14,17,20,22,25,27,29,32,34,36,39,41,44,46,49,51,54,57,60,63,67,70,74,78,82,87,92,97,100,100,100,100,100,100,100,100,100,100,100},
		{6,11,15,18,21,24,27,29,32,34,37,39,42,44,47,50,52,55,58,62,65,68,72,76,80,84,89,93,99,100,100,100,100,100,100,100,100,100,100,100,100},
		{6,13,16,20,23,26,29,31,34,37,39,42,45,48,50,53,56,59,63,66,69,73,77,81,85,90,95,100,100,100,100,100,100,100,100,100,100,100,100,100,100},
		{7,13,17,21,24,27,31,33,36,39,42,45,48,51,54,57,60,63,67,70,74,78,82,86,91,96,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100},
		{7,14,18,22,26,29,32,35,38,42,45,48,51,54,57,60,64,67,71,75,79,83,87,92,97,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100},
		{7,14,19,23,27,31,34,37,41,44,47,50,54,57,60,64,67,71,75,79,83,88,92,97,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100},
		{7,15,20,25,28,32,36,40,43,46,50,53,57,60,64,67,71,75,79,83,88,93,98,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100},
		{7,16,21,26,30,34,38,42,45,49,52,56,60,63,67,71,75,79,83,88,93,98,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100},
		{7,16,22,27,32,36,40,44,47,51,55,59,63,66,70,75,79,83,88,92,97,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100},
		{8,17,23,27,33,38,42,46,50,54,58,62,66,70,74,78,82,87,92,97,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100},
		{8,17,24,30,35,39,44,48,52,56,60,64,69,73,77,82,86,91,96,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100},
		{8,19,25,31,36,41,46,50,54,58,63,67,72,76,81,85,90,95,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100},
		{8,19,26,32,38,43,47,52,57,61,65,70,75,79,84,89,94,99,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100},
		{8,19,27,33,39,44,49,54,59,63,68,73,77,82,87,92,97,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100},
		{8,20,28,35,40,46,51,56,61,66,71,76,80,85,91,96,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100},
		{8,20,29,36,42,48,53,58,63,68,73,78,83,89,94,99,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100},
		{9,22,30,37,43,49,55,60,66,71,76,81,87,92,97,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100},
		{9,21,31,38,45,51,57,62,68,73,78,84,89,95,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100},
		{9,23,32,40,47,53,59,64,70,76,81,87,92,98,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100},
		{9,23,33,41,48,54,60,66,72,78,84,90,95,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100},
		{9,25,34,42,50,56,62,68,74,80,86,92,98,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100},
		{9,25,35,44,51,58,64,71,77,83,89,95,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100},
		{9,26,36,44,52,59,66,73,79,85,91,98,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100},
		{9,26,37,46,54,61,68,75,81,88,94,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100},
		{10,26,38,47,55,63,70,77,83,90,97,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100},
		{10,28,39,49,57,64,72,79,86,92,99,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100},
		{10,27,40,50,58,66,74,81,88,95,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100},
		{10,29,41,51,60,68,75,83,90,97,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100},
		{10,29,42,52,61,70,77,85,92,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100},
		{10,31,43,54,62,71,79,87,95,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100},
		{10,31,44,55,64,73,81,89,97,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100},
		{10,33,45,56,66,75,83,91,99,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100},
		{10,32,46,57,67,76,85,93,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100},
		{11,34,47,58,69,78,87,95,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100},
		{11,34,48,60,70,80,89,97,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100},
		{11,34,49,61,72,81,90,99,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100},
		{11,36,50,63,73,83,92,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100},
		{11,35,51,63,74,85,94,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100},
		{11,37,52,65,76,86,96,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100},
		{11,37,53,66,77,88,98,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100},
		{11,39,54,68,79,90,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100},
		{11,38,55,69,81,91,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100},
		{11,40,56,70,82,93,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100},
		{12,40,57,71,83,95,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100},
		{12,42,58,72,85,96,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100},
		{12,42,59,74,86,98,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100},
		{12,42,60,75,88,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100},
		{12,43,61,76,89,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100},
		{12,43,62,77,91,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100},
		{12,45,63,79,93,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100},
		{12,45,64,80,94,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100},
		{12,46,66,82,95,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100},
		{12,46,66,82,97,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100},
		{12,48,67,84,98,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100},
		{13,48,68,85,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100},
		{13,50,70,87,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100},
		{13,49,70,88,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100},
		{13,50,71,89,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100},
		{13,51,72,90,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100},
		{13,51,74,91,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100},
		{13,52,75,93,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100},
		{13,52,76,94,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100},
		{13,54,77,95,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100},
		{13,54,78,96,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100},
		{13,56,79,98,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100},
		{13,55,80,99,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100},
		{14,57,81,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100},
		{14,57,82,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100},
		{14,58,83,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100},
		{14,59,84,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100},
		{14,59,85,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100},
		{14,60,86,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100},
		{14,60,87,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100},
		{14,62,88,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100},
		{14,61,89,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100},
		{14,63,90,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100},
		{14,63,91,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100},
		{14,65,92,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100},
		{14,65,93,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100},
		{15,66,94,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100},
		{15,66,95,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100},
		{15,66,96,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100},
		{15,68,97,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100},
		{15,68,98,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100},
		{15,69,99,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100},
		{15,69,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100},
		{15,71,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100},
	};
	
	int get_N(){
		return n_for_m_e[M-10][E];
	}
	void CreateGraphs() override {
		CreateConstTable(5500);
		N=get_N();
		auto failed_count = 100 - getExpectedCount(N);
		int score = round(1e9 / N * pow(0.9, failed_count));
		cerr<<"Predicted on N="<<N<<": "<<failed_count<<","<<score<<endl;
	}

	// n頂点と決め打った時の、用意するM個のグラフの辺の本数
	vi getEdgeCounts(int n){
		const int edge_count = n*(n-1)/2;

		const long double P_damage = E/100.0;
		const long double P_not_damage = 1-P_damage;

		// 辺がi本のグラフを損傷させた時、何本になるか
		vector<long double> damaged_edge(edge_count+1, 0);
		rep(i, edge_count+1){
			damaged_edge[i] = i*P_not_damage + (edge_count - i)*P_damage;
		}

		// damaged_edgeからM個選んだときの、各要素の差の最小値が最大になるような選びかた
		vi ret(M, 0);
		rep(i,edge_count) ret[1 + i%(M-1)]++; // TODO: edge_count/M個ずつ割り振って高速化できる
		partial_sum(all(ret), begin(ret));

		graphs.clear();
		rep(i,M) {
			Graph g(n);
			int index=0;
			rep(a, n)rep(b, a+1, n) if(index++<ret[i]) g.addEdge(a,b);
			graphs.push_back(g);
		}
		return ret;
	}

	static inline int calced_e=-1, calced_n=-1;
	static inline vector<vector<long double>> comb_map = vector<vector<long double>>(5501, vector<long double>(5501, 0));
	static inline vector<long double> pow_damage_map = vector<long double>(5501, 1);
	static inline vector<long double> pow_not_damage_map = vector<long double>(5501, 1);
	void CreateConstTable(int n){
		if(calced_e == E and n <= calced_n){
			return;
		}
		calced_e = E, calced_n = n;

		rep(i,n+1) comb_map[i][0] = comb_map[i][i] = 1;
		rep(i,1,n+1)rep(j,1,i) comb_map[i][j] = comb_map[i-1][j-1] + comb_map[i-1][j];

		const long double P_damage = E/100.0, P_not_damage = 1-P_damage;
		rep(i,n) {
			pow_damage_map[i+1] = pow_damage_map[i] * P_damage;
			pow_not_damage_map[i+1] = pow_not_damage_map[i] * P_not_damage;
		}
	}


	vector<pair<int, long double>> PREDICT_TABLE;
	// n頂点と決め打った時の正解数の期待値
	long double getExpectedCount(int n){
		cerr<<"Node count: "<<n<<endl;
		// グラフの構築
		getEdgeCounts(n);

		int edge_count = n*(n-1)/2;

		// probArray[i][j] := グラフiを損傷させたときj本になる確率
		vector<vector<long double>> probArray(M, vector<long double>(edge_count+1, 0));

		rep(i,M){
			int graph_edge_count = graphs[i].getEdgeCount();
			int graph_empty_count = edge_count - graph_edge_count;
			vector<long double> prob_of_edge(graph_edge_count+1, 0);
			vector<long double> prob_of_empty(graph_empty_count+1, 0);

			rep(j, graph_edge_count+1){
				prob_of_edge[j] = comb_map[graph_edge_count][j] * pow_not_damage_map[j] * pow_damage_map[graph_edge_count-j];
			}

			rep(j, graph_empty_count+1){
				prob_of_empty[j] = comb_map[graph_empty_count][j] * pow_damage_map[j] * pow_not_damage_map[graph_empty_count-j];
			}

			probArray[i] = FastFourierTransform::multiply(prob_of_edge, prob_of_empty, edge_count+1);
		}
		// rep(j, edge_count+1) if(probArray[30][j] >= 0.01) cerr<<j<<" "<<probArray[30][j]<<endl;


		
		// predict_table[i] = 損傷後にi本の辺が残ったとき、{正解と思われるグラフ、正解確率}
		vector<pair<int, long double>> predict_table(edge_count+1);
		rep(j, edge_count+1){
			long double prob_sum=0, prob_max=0; int prob_index=0;
			rep(i,M){
				prob_sum += probArray[i][j];
				if(chmax(prob_max, probArray[i][j])) prob_index = i;
			}
			predict_table[j] = {prob_index, prob_max / prob_sum};
			// out(j, predict_table[j]);
		}

		// expected_count[i] = 正解にグラフiが使われたときの正解確率
		vector<long double> expected_table(M, 0);
		rep(j, edge_count+1){
			auto [predicted, _] = predict_table[j];
			expected_table[predicted] += probArray[predicted][j];
		}


		long double expected = 0;
		rep(i,M){ 
			expected += expected_table[i];
			// cerr<<i<<": "<<expected_table[i]<<endl;
		}
		PREDICT_TABLE = predict_table;
		return expected / M * 100;
	}


	int PredictGraph(Graph&damaged) override {
		return PREDICT_TABLE[damaged.getEdgeCount()].first;
	}
};


template<int DEF_N=100>
struct DualStrategy : public StrategyBase {
	DualStrategy(int m,int e) : StrategyBase(m,e) {}

	int Pattern1 = 0;
	vi params;
	EdgeCountStrategy dual2;

	int FRONT_DELETION = 5;
	void CreateGraphs() override {
		N = DEF_N;
		float PATTARN1_THRESHOLD = E/2.+2+(40-E)/40.;

		const float e1 = (N-1) * (1-E/100.0);
		while(true){
			Pattern1 = 0;
			graphs.clear();
			params.clear();
			rep(i,1,N){
				float e2 = i * (1-2*E/100.0) + (N-1) * E/100.0;
				if(e1-e2 >= PATTARN1_THRESHOLD){
					Pattern1++;
					Graph g(N);
					rep(j,i) rep(k,j+1,N) g.addEdge(j,k);
					params.push_back(i);
					graphs.push_back(g);
					if(siz(graphs) == M) break;
				}
			}
			if(siz(graphs) >= M/2) break;
			PATTARN1_THRESHOLD-=1;
			if(PATTARN1_THRESHOLD < 0) break;
		}
		if(Pattern1 == M-1){
			Pattern1--;
			graphs.pop_back();
			params.pop_back();
		}
		{
			debug("START");
			auto analysis = TestAnalysis(11);
			rep(i,siz(graphs))if(analysis[i] >= 6){
				while(siz(graphs) > i) {
					Pattern1--;
					graphs.pop_back();
					params.pop_back();
				}
				break;
			}
		}
		if(siz(graphs) == M) return;


		dual2.M = M - Pattern1 + FRONT_DELETION; dual2.E = E;
		dual2.CreateConstTable(N*(N-1)/2);
		dual2.getExpectedCount(N);
		// 辺を均一化する
		rep(i,FRONT_DELETION, siz(dual2.graphs)){
			string edges = dual2.graphs[i].getStrExpression();
			shuffle(all(edges), Random);
			graphs.push_back(Graph(edges));
		}
	}

	float getVariance(vi&a){
		float ave = accumulate(all(a), 0.0) / siz(a), var = 0;
		for(auto&x : a) var += (x-ave)*(x-ave);
		return var / siz(a);
	}

	int PredictGraph(Graph&damaged) override {
		{// Pattern 1
			auto degrees = damaged.GetDegrees();
			int ans=-1, diff=1000;
			const float e1 = (N-1) * (1-E/100.0);
			rep(_g,Pattern1){
				int g = params[_g];
				float e2 = g * (1-2*E/100.0) + (N-1) * E/100.0;
				int cnt1=degrees.end() - lower_bound(all(degrees), (e1+e2) / 2);
				if(chmin(diff, abs(g-cnt1))) ans = _g;
			}
			if(getVariance(degrees) >= 25) return clamp(ans,0,M-1);
		}
		if(!dual2.graphs.empty()){// Pattern2
			int ans = Pattern1 + dual2.PredictGraph(damaged) - FRONT_DELETION;
			return clamp(ans,0,M-1);
		}
		return Random(0,M);
	}
};

map<tuple<string, int, int>, StrategyBase*> strategyMap;


template<class T>
void RunStrategy(int m, int e) {
	cerr<<"Selected: "<<typeid(T).name()<<endl;
	StrategyBase* strategy = strategyMap[{typeid(T).name(), m, e}];
	strategy->PrintGraphsInfo();
	rep(strategy->QUERY_COUNT){
		Graph h = strategy->GetDamagedGraph();
		int ans = strategy->PredictGraph(h);
		cout<<ans<<endl;
	}
}

void NoError(int m, int e){
	RunStrategy<NoErrorStrategy>(m, e);
}

void EdgeCount(int m, int e){
	RunStrategy<EdgeCountStrategy>(m, e);
}

void FailSafe(int m, int e){
	RunStrategy<FailSafeStrategy>(m, e);
}

template<int DEF_N=100>
void Dual(int m, int e){
	RunStrategy<DualStrategy<DEF_N>>(m, e);
}

template<class T>
int TestStrategy(int m, int e, int repeat=10) {
	cerr<<"Test: "<<typeid(T).name()<<endl;
	T* strategy = new T(m, e);
	strategy->CreateGraphs();
	int score = strategy->Test(repeat);
	strategyMap[make_tuple(typeid(T).name(), m, e)] = strategy;
	return score;
}


char SelectBest(int m, int e) {
	vector<pair<int, char>> results = {
		{TestStrategy<NoErrorStrategy>(m, e), 'N'},
		{TestStrategy<EdgeCountStrategy>(m, e), 'E'},
		{TestStrategy<FailSafeStrategy>(m, e), 'F'},
	};


	if(Mgr::TLE-Mgr::timer.get() >= 1000){
		results.emplace_back(TestStrategy<DualStrategy<100>>(m, e), 'D');
	}

	if(Mgr::TLE-Mgr::timer.get() >= 200){
		results.emplace_back(TestStrategy<DualStrategy<20>>(m, e), '2');
	}

	if(Mgr::TLE-Mgr::timer.get() >= 900){
		results.emplace_back(TestStrategy<DualStrategy<90>>(m, e), '9');
	}

	if(Mgr::TLE-Mgr::timer.get() >= 500){
		results.emplace_back(TestStrategy<DualStrategy<50>>(m, e), '5');
	}

	if(Mgr::TLE-Mgr::timer.get() >= 800){
		results.emplace_back(TestStrategy<DualStrategy<80>>(m, e), '8');
	}

	if(Mgr::TLE-Mgr::timer.get() >= 400){
		results.emplace_back(TestStrategy<DualStrategy<40>>(m, e), '4');
	}

	if(Mgr::TLE-Mgr::timer.get() >= 700){
		results.emplace_back(TestStrategy<DualStrategy<70>>(m, e), '7');
	}

	if(Mgr::TLE-Mgr::timer.get() >= 300){
		results.emplace_back(TestStrategy<DualStrategy<30>>(m, e), '3');
	}

	if(Mgr::TLE-Mgr::timer.get() >= 600){
		results.emplace_back(TestStrategy<DualStrategy<60>>(m, e), '6');
	}

	if(Mgr::TLE-Mgr::timer.get() >= 100){
		results.emplace_back(TestStrategy<DualStrategy<10>>(m, e), '1');
	}

	sort(all(results));
	return results.back().second;
}


int main() {
	int M, E;
	cin>>M;
	{ long double f; cin>>f; E = round(f*100); }

	char strategy = SelectBest(M,E);

	switch(strategy){
		case 'N': NoError(M,E); break;
		case 'E': EdgeCount(M,E); break;
		case 'F': FailSafe(M,E); break;
		case 'D': Dual<100>(M,E); break;
		case '9': Dual<90>(M,E); break;
		case '8': Dual<80>(M,E); break;
		case '7': Dual<70>(M,E); break;
		case '6': Dual<60>(M,E); break;
		case '5': Dual<50>(M,E); break;
		case '4': Dual<40>(M,E); break;
		case '3': Dual<30>(M,E); break;
		case '2': Dual<20>(M,E); break;
		case '1': Dual<10>(M,E); break;
	}
	return 0;
}