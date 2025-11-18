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

int N,M,H;
vi A;
vector<vector<int>> G;
vi Cx, Cy, Cd;


int calcScore() {
	return 0;
}

ll initialSum = 0, initialCnt = 0;
auto getInitial() {
	const int connectCount[] = {
		1,1,1,1,1,2,2,2,3,3,100
	};
	int bestScore = 0;
	vi bestParent(N, -1);
	int tried = 0;
	while(tried++ < 100) {
		vi parent(N, -1);
		int score = 0;
		HashSet<int> used;
		vector<int> roots;
		rep(i,N) {
			if(A[i] <= 40) roots.push_back(i);
		}
		shuffle(all(roots), Random);

		vi depth(N, -1);
		while(roots.size()) {
			int p = roots.back(); roots.pop_back();
			if(used.contains(p)) continue;

			queue<int> q;
			q.push(p);
			depth[p] = 0;
			used.insert(p);
			score += A[p];
			while(q.size()) {
				int v = q.front(); q.pop();
				int conCnt = 0;
				for(int u : G[v]) {
					if(depth[u] != -1) continue;
					depth[u] = depth[v] + 1;
					parent[u] = v;
					used.insert(u);
					score += A[u] * (depth[u]+1);
					conCnt++;
					if(depth[u] == H) continue;
					q.push(u);
					// if(conCnt >= max(depth[u]-3, 1)) break;
					if(conCnt >= connectCount[depth[u]]) break;
				}

				if(conCnt==0) {
					for(int u : G[v]) {
						if(depth[u] != -1) continue;
						depth[u] = depth[v] + 1;
						parent[u] = v;
						if(depth[u] == H) continue;
						q.push(u);
					}
				}
			}
		}
		rep(i,N){
			if(!used.contains(i)) {
				score += A[i];
			}
		}
		if(chmax(bestScore, score)) {
			bestParent = parent;
		}
	}
	initialSum += bestScore;
	initialCnt++;
	return make_pair(bestScore, bestParent);
}

int climbCount = 0;
void climbing(int&score, vi& parent) {
	climbCount++;
	vector<HashSet<int>> children(N);
	rep(i,N) {
		if(parent[i] != -1) children[parent[i]].insert(i);
	}
	vi depth(N, -1);
	{
		queue<int> q;
		rep(i,N) if(parent[i] == -1) {
			q.push(i);
			depth[i] = 0;
		}
		while(q.size()) {
			int v = q.front(); q.pop();
			for(int u : children[v]) {
				depth[u] = depth[v] + 1;
				q.push(u);
			}
		}
	}

	int v=0;
	bool changed = false;
	while(Mgr::timer) {
		if(v==0) {
			changed=false;
		}

		// 葉について
		if(children[v].size() == 0) {
			int mxj = v;
			for(int j : G[v]) {
				if(depth[j]==H) continue;
				if(depth[mxj] < depth[j]) mxj = j;
				if(depth[mxj] == depth[j] && children[parent[mxj]].size() <= children[parent[j]].size()) mxj = j;
			}
			// 自身をより深い位置に移動可能 or 同じ深さでより多く子を持っている親に移動可能 なら移動
			if(mxj != v) {
				if(parent[v]!=-1) children[parent[v]].erase(v);
				parent[v] = mxj;
				children[mxj].insert(v);
				score -= A[v] * (depth[v]+1);
				depth[v] = depth[mxj] + 1;
				score += A[v] * (depth[v]+1);
				changed = true;
			}
		}
		v = (v+1)%N;
		if(v==0 && !changed) break;
	}
}


int annealCount = 0;
auto annealing(int score, vi parent) {
	annealCount++;
	vector<HashSet<int>> children(N);
	rep(i,N) {
		if(parent[i] != -1) children[parent[i]].insert(i);
	}

	vi tgt;
	{
		queue<int> q;
		rep(i,N) if(parent[i] == -1) {
			for(int u : children[i]) {
				if(children[u].size()) tgt.push_back(u);
			}
		}
	}

	vector<pair<int, vi>> results;

	for(auto t : tgt) {
		int score2 = score;
		vi parent2 = parent;
		parent2[t] = -1;

		queue<int> q;
		q.push(t);
		while(q.size()) {
			int v = q.front(); q.pop();
			score2 -= A[v];
			for(int u : children[v]) {
				q.push(u);
			}
		}
		results.push_back(make_pair(score2, parent2));
	}
	return results;
}


int main() { /**/
	in(N,M,H);
	A.resize(N);
	in(A);
	G.resize(N);
	rep(M) {
		def(int,a,b);
		G[a].push_back(b);
		G[b].push_back(a);
	}
	rep(i,N){
		sort(all(G[i]), [&](int a, int b) {
			return A[a] < A[b];
			// return A[a] * G[a].size() < A[b] * G[b].size();
		});
	}
	Cx.resize(N);
	Cy.resize(N);
	Cd.resize(N);
	rep(i,N){
		in(Cx[i], Cy[i]);
		Cx[i]-=500; Cy[i]-=500;
		Cd[i] = hypot(Cx[i], Cy[i]);
	}

	int answerScore = 0; vi answerParent(N, -1);

	while(Mgr::timer) {
		auto [score, parent] = getInitial();
		climbing(score, parent);
		if(score < answerScore - 5000) {
			continue;
		}
		if(chmax(answerScore, score)) {
			answerParent = parent;
			out(parent);
		}
		debug("climbing 1\t", score);

		int remain = 3;
		while(Mgr::timer && remain--) {
			auto results = annealing(score, parent);

			int aScore = 0; vi aParent(N, -1);
			for(auto [s, p] : results) {
				climbing(s, p);
				if(chmax(aScore, s)) {
					aParent = p;
				}
			}
			auto diff = score - aScore;
			// debug("diff\t", diff, "prob\t", exp(-diff/100));
			if(diff < 0 || Random(0.0, 1.0) < exp(-diff/100)) {
				debug("annealing\t", score, "->", aScore);
				score = aScore;
				parent = aParent;
				if(chmax(answerScore, score)) {
					answerParent = parent;
					out(parent);

					remain = 3;
					debug("best!!!!");
				}
			} else break;
		}
	}

	out(answerParent);
	debug_f("score\t", answerScore);
	debug_f("predict\t", answerScore * 150);
	debug_f("climbCount\t", climbCount);
	debug_f("annealCount\t", annealCount);
	debug_f("initialSum\t", initialSum);
	debug_f("initialCnt\t", initialCnt);
	debug_f("initialAvg\t", (double)initialSum/initialCnt);

}