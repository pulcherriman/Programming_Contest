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
} Random(0);

class Timer {
	#ifdef _DEBUG
	static constexpr uint64_t ClocksPerMsec = 3587000;
	#else
	static constexpr uint64_t ClocksPerMsec = 2987000;
	#endif
	const uint64_t start,limit,__limit;
	uint64_t getClocks() const{
		unsigned int lo,hi;
		__asm__ volatile ("rdtsc" : "=a" (lo), "=d" (hi));
		return((uint64_t)hi<<32)|lo;
	}
public:
	Timer(uint64_t _limit=1970): start(getClocks()),limit(start+_limit*ClocksPerMsec),__limit(_limit) {}
	uint64_t get() const { return (getClocks()-start)/ClocksPerMsec; }
	operator bool() const { return getClocks()<limit; }
	float persentile() const { return (float)get()/__limit; }
};
void wait(const int&msec){Timer tm(msec); while(tm);}

struct Mgr {
	static const int TLE = 2000;
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
const int n=15, m = 200;
int si,sj;
array<string, n> key;
array<string,m> tgt;
using Pos = int;
array<vector<Pos>, 26> keyByAb;
using Route = pair<int, vector<int>>;


auto solve(string s, bool isRequireInitialCost){
	vector<Route> routes;

	int ab = s[0]-'A';
	routes.resize(sz(keyByAb[ab]));
	// dp[k][l] = tgt[i]をk字目まで押してl種目のキーを押した時の(コストの最小値と前の文字の位置)
	vector<vp> dp(sz(s));
	rep(start,sz(keyByAb[ab])){
		dp = vector<vp>(sz(s));
		dp[0].resize(sz(keyByAb[ab]), {INF,-1});
		int initialCost = abs(si-keyByAb[ab][start]/n)+abs(sj-keyByAb[ab][start]%n)+1;
		dp[0][start]={isRequireInitialCost ? initialCost: 0,-1};

		ab = s[0]-'A';
		rep(j,sz(s)-1){
			int nxtab = s[j+1]-'A';
			dp[j+1].resize(sz(keyByAb[nxtab]), {INF,-1});
			rep(k,sz(keyByAb[ab])){
				auto [cost,prev] = dp[j][k];
				if(cost==INF) continue;
				rep(l,sz(keyByAb[nxtab])){
					int curPos = keyByAb[ab][k];
					int nxtPos = keyByAb[nxtab][l];
					int curi = curPos/n, curj = curPos%n;
					int nxti = nxtPos/n, nxtj = nxtPos%n;
					int d = abs(curi-nxti)+abs(curj-nxtj)+1;
					if(chmin(dp[j+1][l].first, cost+d)){
						dp[j+1][l] = {cost+d, k};
					}
				}
			}
			ab=nxtab;
		}

		auto minElem = min_element(all(dp[sz(s)-1]));
		auto [cost,prev] = *minElem;
		int minPos = minElem-dp[sz(s)-1].begin();
		routes[start].first = cost;
		routes[start].second.push_back(keyByAb[ab][minPos]);
		rep(j,sz(s)-1){
			ab = s[sz(s)-2-j]-'A';
			routes[start].second.push_back(keyByAb[ab][prev]);
			tie(cost,prev) = dp[sz(s)-2-j][prev];
		}
		reverse(all(routes[start].second));
	}
	return routes;
}

pair<int,string> getMaxCoverage(string a, string b){
	if(a.contains(b)) return {sz(b), a};

	int ret = 0; string ans;
	rep(2){
		rrep(k,1,min(sz(a), sz(b))+1){
			if(a.substr(sz(a)-k,k)==b.substr(0,k)){
				chmax(ret, k);
				ans = a+b.substr(k);
				break;
			}
		}
		swap(a,b);
	}
	return {ret,ans};
}

HashMap<int,int> memo;
pair<int,string> getMinDist(string a, string b){

	int ret = INF; string ans;
	rep(2){
		int c1=a.back()-'A', c2=b[0]-'A';
		int val=INF;
		if(memo.contains(c1*26+c2)) val = memo[c1*26+c2];
		else {
			for(auto&p1:keyByAb[c1])for(auto&p2:keyByAb[c2]){
				int i1=p1/n, j1=p1%n;
				int i2=p2/n, j2=p2%n;
				int d = abs(i1-i2)+abs(j1-j2)+1;
				chmin(val, d);
			}
			memo[c1*26+c2] = val;
			memo[c2*26+c1] = val;
		}
		if(chmin(ret, val)){
			ans = a+b;
		}
		swap(a,b);
	}
	return {ret,ans};
}

auto coverStr(vector<string> s){
	vvi cost(sz(s), vi(sz(s), INF));
	rep(i,sz(s)) rep(j,sz(s)) if(i!=j){
		// s[i]とs[j]をこの順に連結する。何文字重ならないか
		cost[i][j] = sz(s[j]);
		rrep(k,1,min(sz(s[i]), sz(s[j]))+1){
			int l = sz(s[i])-k;
			if(s[i].substr(k,l)==s[j].substr(0,l)){
				chmin(cost[i][j], sz(s[j])-l);
			}
		}
	}

	while(sz(s)>1){
		int maxCoverage = 0, maxI = -1, maxJ = -1; string maxStr;
		// int minDist = INF, minI = -1, minJ = -1; string minStr;
		rep(i,sz(s)) rep(j,i+1,sz(s)) {
			auto [coverage, str] = getMaxCoverage(s[i], s[j]);
			if(chmax(maxCoverage, coverage)){
				maxI = i;
				maxJ = j;
				maxStr = str;
			}
			// auto [dist, str2] = getMinDist(s[i], s[j]);
			// if(chmin(minDist, dist)){
			// 	minI = i;
			// 	minJ = j;
			// 	minStr = str2;
			// }
		}
		if(maxCoverage!=0) {
			swap(s[maxJ], s.back()); s.pop_back();
			swap(s[maxI], s.back()); s.pop_back();
			s.pb(maxStr);
		} else {
			// swap(s[minJ], s.back()); s.pop_back();
			// swap(s[minI], s.back()); s.pop_back();
			// s.pb(minStr);
			break;
		}
	}
	
	return s;

}

int main() { /**/
	{
		def(int,_,__);
	}
	cin>>si>>sj;
	rep(i,n) in(key[i]);
	rep(i,m) in(tgt[i]);
	rep(i,n) rep(j,n) keyByAb[key[i][j]-'A'].pb(i*n+j);

	vs covers = coverStr(vs(all(tgt)));
	covers = vs(all(tgt));

	vector<vector<Route>> allRoutes, allRoutes_zero;

	vector<vector<tuple<int,int,int, vi>>> startend(sz(covers));
	vector<vector<tuple<int,int,int, vi>>> startend_zero(sz(covers));

	rep(i,sz(covers)){
		auto routes = solve(covers[i] ,false);
		allRoutes.pb(routes);
		for(auto&route: routes){
			startend[i].pb({route.first, route.second.front(), route.second.back(), route.second});
		}

		routes= solve(covers[i], true);
		allRoutes_zero.pb(routes);
		for(auto&route: routes){
			startend_zero[i].pb({route.first, route.second.front(), route.second.back(), route.second});
		}
	}

	int challenge = 0;
	int ansCost = INF; vi ansPath;
	vector<tuple<int,int,int,vi>> startend_selected(sz(covers)), startend_zero_selected(sz(covers));
	rep(i,sz(covers)){
		startend_selected[i] = (*min_element(all(startend[i]), [](auto&a, auto&b){
			auto [ac,a1,a2,_]=a;
			auto [bc,b1,b2,__]=b;
			int ad = abs(a1/n-7)+abs(a1%n-7)+abs(a2/n-7)+abs(a2%n-7);
			int bd = abs(b1/n-7)+abs(b1%n-7)+abs(b2/n-7)+abs(b2%n-7);
			return ac<bc or (ac==bc and ad<bd) or (ac==bc and ad==bd and a<b);
		}));
		startend_zero_selected[i] = (*min_element(all(startend_zero[i]), [](auto&a, auto&b){
			auto [ac,a1,a2,_]=a;
			auto [bc,b1,b2,__]=b;
			// int ad = max(abs(a1/n-7)+abs(a1%n-7),abs(a2/n-7)+abs(a2%n-7));
			int ad = abs(a1/n-7)+abs(a1%n-7)+abs(a2/n-7)+abs(a2%n-7);
			int bd = abs(b1/n-7)+abs(b1%n-7)+abs(b2/n-7)+abs(b2%n-7);
			return ac<bc or (ac==bc and ad<bd) or (ac==bc and ad==bd and a<b);
		}));
	}
	while(Mgr::timer){
		auto check = [&startend_zero_selected,&startend_selected](vi&ans){
			int totalCost = get<0>(startend_zero_selected[ans[0]]);
			int prevPos = get<2>(startend_zero_selected[ans[0]]);
			rep(i,1,sz(ans)){
				auto [cost, curPos, nextPos, _] = startend_selected[ans[i]];
				int dist = abs(prevPos/n-curPos/n)+abs(prevPos%n-curPos%n)+1;
				totalCost += dist + cost;
				prevPos = nextPos;
			}
			return totalCost;
		};

		vi ans(sz(covers)); iota(all(ans), 0);
		int minCost = INF; vi minAns=ans;
		int i=0, j=1; bool modified = false;
		auto chYakinamashi = [&minAns, &challenge](int&minCost, int cost, vi&ans) {
			challenge++;
			if(cost<=minCost) {
				if(cost<minCost) minAns=ans;
				minCost=cost; return true;
			}
			auto thres = (1-Mgr::timer.persentile())/8/sqrt(cost-minCost);
			if(Random(0.0, 1.0)<thres) { minCost=cost; return true;}
			return false;
		};
		while(Mgr::timer){
			rep(md, 4){
				if(md==0){
					swap(ans[i], ans[j]);
					int cost = check(ans);
					if(chYakinamashi(minCost, cost, ans)) {
						modified = true;
					}else {
						swap(ans[i], ans[j]);
					}
				} else if(md==1){
					auto copyAns = ans;
					copyAns.insert(copyAns.begin()+i, copyAns[j]);
					copyAns.erase(copyAns.begin()+j+1);
					int cost = check(copyAns);
					if(chYakinamashi(minCost, cost, copyAns)) {
						modified = true;
						ans=copyAns;
					}else {
					}
				} else if(md==2){
					auto copyAns = ans;
					copyAns.insert(copyAns.begin()+j, copyAns[i]);
					copyAns.erase(copyAns.begin()+i);
					int cost = check(copyAns);
					if(chYakinamashi(minCost, cost, copyAns)) {
						modified = true;
						ans=copyAns;
					}else {}
				} else if(md==3){
					auto copyAns = ans;
					rotate(copyAns.begin()+i, copyAns.begin()+j, copyAns.end());
					int cost = check(copyAns);
					if(chYakinamashi(minCost, cost, copyAns)) {
						modified = true;
						ans=copyAns;
					}else {}
				}
			}
			j++;
			if(j==sz(ans)) {
				i++; j=i+1;
				if(j==sz(ans)) {
					if(!modified) {
						// break;
					}
					modified = false;
					i=0, j=1;
				}
			}
		}
		vi path = get<3>(startend_zero_selected[minAns[0]]);
		rep(i,1,sz(minAns)){
			auto rt = get<3>(startend_selected[minAns[i]]);
			path.insert(path.end(), all(rt));
		}
		if(chmin(ansCost, minCost)) {
			ansPath = path;
		}
		
		shuffle(all(ans), Random);

		// rep(i,sz(covers)){
		// 	int bestVal = get<0>(startend_selected[i]);
		// 	for(auto&[cost,_,__,___]:startend[i]){
		// 		if(bestVal == cost and Random(0,10)<10) {
		// 			startend_selected[i] = {cost,_,__,___};
		// 		}
		// 	}
		// }
	}

	string lastStr="";
	for(auto&p:ansPath){
		int i = p/n, j = p%n;
		lastStr += key[i][j];
	}
	auto routes = solve(lastStr, true);
	auto best = *min_element(all(routes));
	for(auto&p:best.second){
		int i = p/n, j = p%n;
		out(i,j);
	}
	debug_f(challenge);


	/**
	 * やきなまし
	 */
	// int challenge=0;
	// Route ansRoute = {INF, {}};
	// while(Mgr::timer){
	// 	Route bestRoute = {INF, {}};
	// 	int i=0,j=1;
	// 	bool modified = false;
	// 	while(Mgr::timer){
	// 		swap(covers[i], covers[j]);

	// 		string s;
	// 		for(auto&str:covers) s+=str;
	// 		auto routes = solve(s, true);
	// 		if(!chmin(bestRoute, *min_element(all(routes)))) {
	// 			swap(covers[i], covers[j]);
	// 			// debug("0 NG!");
	// 		}else {
	// 			debug("0 OK!", 10000-bestRoute.first);
	// 			modified = true;
	// 		}
	// 		j++;
	// 		if(j==sz(covers)) i++, j=i+1;
	// 		if(j==sz(covers)) {
	// 			if(!modified) {
	// 				break;
	// 			}
	// 			modified = false;
	// 			i=0, j=1;
	// 		}
	// 		challenge++;
	// 	}
		
	// 	debug_f(challenge);
	// 	chmin(ansRoute, bestRoute);
	// 	shuffle(all(covers), Random);
	// }

	// for(auto&p:ansRoute.second){
	// 	int i = p/n, j = p%n;
	// 	out(i,j);
	// }

}