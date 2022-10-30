// #pragma GCC optimize("Ofast")
// #pragma GCC optimize("unroll-loops")
// #pragma GCC optimize("inline")

// #pragma GCC diagnostic ignored "-Wunused-value"
#ifdef _DEBUG
// #define _GLIBCXX_DEBUG 1
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
#include <tuple>
#include <chrono>
#include <cstdlib>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;

/*
 * Additional Type Definition
 */
using ull=unsigned long long;
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
	static inline Timer timer = Timer(TLE-500);
	Mgr() {
		ios_base::sync_with_stdio(0); cin.tie(0);
		cerr<<fixed<<setprecision(3);
	}
	~Mgr(){
		debug_f(timer.get(), "ms")<<flush;
	}
} _manager;


template<typename T>
struct RangeSet{
	set<pair<T,T>> st;
	const static T TINF=numeric_limits<T>::max()/2;

	RangeSet(){
		st.emplace(TINF,TINF);
		st.emplace(-TINF,-TINF);
	}

	void insert(T l, T r){
		if(l>r) swap(l,r);
		st.emplace(l,r);
	}

	void insert(pair<T,T> p){
		insert(p.first,p.second);
	}

	bool isOverlap(T l, T r){
		if(l>r) swap(l,r);
		auto it=st.lower_bound({l,-TINF});
		if(it->first<r) return true;
		--it;
		if(it->second>l) return true;
		return false;
	}
};



int n, m;
vector<pii> p;

struct Field {
	vvi f;
	Field() {}
	void Init(){
		f.resize(n, vi(n, 0));
		for(auto [x, y] : p) f[x][y] = 1;
	}
	void output() {
		const static string s = " OX!";
		rrep(j,n){
			rep(i,n){
				cout<<s[f[i][j]];
			}
			cout<<endl;
		}
	}
};

struct Player {
	int totalScore = 0;
	using Rect = array<pii, 4>;
	Field field;
	vector<Rect> action;

	using Bit = bitset<64>;
	vector<Bit> horizontal, vertical, diagonal, diagonal2;
	vector<RangeSet<int>> lines_h, lines_v, lines_d, lines_d2;
	vvb used_hr_st, used_hr_ed, used_diag_st, used_diag_ed;

	void Output() const {
		out(action.size());
		for(auto&act : action){
			rep(i,3){
				cout<<act[i].first<<' '<<act[i].second<<' ';
			}
			cout<<act[3].first<<' '<<act[3].second<<endl;
		}
	}

	Player () {}
	void Init(){
		field.Init();
		horizontal.resize(n);
		vertical.resize(n);
		diagonal.resize(n*2-1);
		diagonal2.resize(n*2-1);
		lines_h.resize(n);
		lines_v.resize(n);
		lines_d.resize(n*2-1);
		lines_d2.resize(n*2-1);
		used_hr_st.resize(n, vb(n, false));
		used_hr_ed.resize(n, vb(n, false));
		used_diag_st.resize(n, vb(n, false));
		used_diag_ed.resize(n, vb(n, false));

		rep(i,n) rep(j,n) {
			horizontal[i][j] = field.f[i][j] == 1;
			vertical[i][j] = field.f[j][i] == 1;
			diagonal[i+j][j] = field.f[i][j] == 1;
			diagonal2[i-j+n-1][j] = field.f[i][j] == 1;
			if(field.f[i][j] == 1){
				totalScore += calcScore(i, j);
			}
		}
	}

	bool hasMarker(Bit&bit, int l, int r) {
		if(l>r)swap(l,r);
		Bit mask(((1ull<<r)-1)^((1ull<<(l+1))-1));
		return (bit&mask).any();
	}

	inline int calcScore(int l, int r) {
		const int c=(n-1)/2;
		return (c-l)*(c-l)+(c-r)*(c-r)+1;
	}

	using transition = tuple<int, int, bool, Rect>;
	vector<transition> Analyze(){
		vp marks;
		rep(i,n) rep(j,n) if(field.f[i][j] > 0) marks.emplace_back(i,j);

		vp marks_st, marks_ed, marks_diag_st, marks_diag_ed;
		rep(i,n) rep(j,n) if(field.f[i][j] > 0) {
			if(!used_hr_st[i][j]) marks_st.emplace_back(i,j);
			if(!used_hr_ed[i][j]) marks_ed.emplace_back(i,j);
			if(!used_diag_st[i][j]) marks_diag_st.emplace_back(i,j);
			if(!used_diag_ed[i][j]) marks_diag_ed.emplace_back(i,j);
		}

		int minLength = INF;
		vector<transition> pq;
		for(auto[i,j]:marks_st)
		for(auto[i2,j2]:marks_ed)if(i<i2 and j!=j2){
			const int len = abs(i-i2)*2+abs(j-j2)*2;
			if(len>minLength) continue;
			bool exist1 = field.f[i][j2] > 0;
			bool exist2 = field.f[i2][j] > 0;
			if (!(exist1^exist2)) continue;

			if(hasMarker(horizontal[i], j, j2)) continue;
			if(hasMarker(horizontal[i2], j, j2)) continue;
			if(hasMarker(vertical[j], i, i2)) continue;
			if(hasMarker(vertical[j2], i, i2)) continue;

			if(lines_h[i].isOverlap(j, j2)) continue;
			if(lines_h[i2].isOverlap(j, j2)) continue;
			if(lines_v[j].isOverlap(i, i2)) continue;
			if(lines_v[j2].isOverlap(i, i2)) continue;

			
			Rect points;
			{
				if(exist1) points = {pii(i2,j), pii(i,j), pii(i,j2), pii(i2,j2)};
				else points = {pii(i,j2), pii(i,j), pii(i2,j), pii(i2,j2)};
			}
			// debug(i,j,i2,j2);

			chmin(minLength, len);
			const int score = calcScore(points[0].first, points[0].second);
			pq.emplace_back(-score/len, 0, true, points);
		}

		// diagonal rect
		for(auto[i,j]:marks_diag_st)for(auto[i2,j2]:marks_diag_ed)if(i!=i2 or j!=j2){
			if(i+j>=i2+j2) continue;
			if((i+j)%2 != (i2+j2)%2) continue;
			int i3, j3, i4, j4;
			{
				int t=i2+j2-i-j; t/=2;
				i3 = i2-t; j3 = j2-t;
				i4 = i+t; j4 = j+t;
			}
			if(i3<0 || i3>=n || j3<0 || j3>=n) continue;
			if(i4<0 || i4>=n || j4<0 || j4>=n) continue;
			const int len = abs(i-i3)*2+abs(j-j4)*2;
			if(len>minLength) continue;

			bool exist1 = field.f[i3][j3] > 0;
			bool exist2 = field.f[i4][j4] > 0;
			if (!(exist1^exist2)) continue;

			if(hasMarker(diagonal[i+j], j, j3)) continue;
			if(hasMarker(diagonal[i2+j2], j2, j4)) continue;
			if(hasMarker(diagonal2[i-j+n-1], j, j4)) continue;
			if(hasMarker(diagonal2[i2-j2+n-1], j2, j3)) continue;

			if(lines_d[i+j].isOverlap(j, j3)) continue;
			if(lines_d[i2+j2].isOverlap(j2, j4)) continue;
			if(lines_d2[i-j+n-1].isOverlap(j, j4)) continue;
			if(lines_d2[i2-j2+n-1].isOverlap(j2, j3)) continue;

			Rect points;
			{
				if(exist1) points = {pii(i4,j4), pii(i,j), pii(i3,j3), pii(i2,j2)};
				else points = {pii(i3,j3), pii(i,j), pii(i4,j4), pii(i2,j2)};
			}
			
			chmin(minLength, len);
			const int score = calcScore(points[0].first, points[0].second);
			pq.emplace_back(-score/len, 0, false, points);
		}

		if(pq.empty()) return pq;

		sort(all(pq));
		int length = min(10, (int)pq.size());
		pq.erase(pq.begin()+length, pq.end());
		return pq;
	}


	int lengthSum = 0;
	void AddRect(transition&info){
		auto&[len, score, isHorizontal, points] = info;
		lengthSum += len;
		if(isHorizontal){
			AddRectHorizontal(points);
		}else{
			AddRectDiagonal(points);
		}
	}

	void AddRectHorizontal(Rect&rect){
		totalScore += calcScore(rect[0].first, rect[0].second);
		action.push_back(rect);
		{
			auto [y,x]=rect[0];
			field.f[y][x]=2;
			horizontal[y][x]=1;
			vertical[x][y]=1;
			diagonal[y+x][x]=1;
			diagonal2[y-x+n-1][x]=1;
		}
		auto [minY, maxY] = minmax(rect[0].first, rect[2].first);
		auto [minX, maxX] = minmax(rect[0].second, rect[2].second);
		lines_h[minY].insert(minX, maxX);
		lines_h[maxY].insert(minX, maxX);
		lines_v[minX].insert(minY, maxY);
		lines_v[maxX].insert(minY, maxY);
		used_hr_st[minY][minX]=used_hr_st[minY][maxX]=1;
		used_hr_ed[maxY][minX]=used_hr_ed[maxY][maxX]=1;
	}

	void AddRectDiagonal(Rect&rect){
		totalScore += calcScore(rect[0].first, rect[0].second);
		action.push_back(rect);
		{
			auto [y,x]=rect[0];
			field.f[y][x]=2;
			horizontal[y][x]=1;
			vertical[x][y]=1;
			diagonal[y+x][x]=1;
			diagonal2[y-x+n-1][x]=1;
		}
		{ // diagonal
			int base = rect[1].first + rect[1].second;
			if(rect[0].first + rect[0].second == base){
				lines_d[base].insert(minmax(rect[0].second, rect[1].second));
				lines_d[rect[3].first+rect[3].second].insert(minmax(rect[2].second, rect[3].second));
				used_diag_st[rect[0].first][rect[0].second]=1;
				used_diag_st[rect[1].first][rect[1].second]=1;
				used_diag_ed[rect[2].first][rect[2].second]=1;
				used_diag_ed[rect[3].first][rect[3].second]=1;

			}else{
				lines_d[base].insert(minmax(rect[2].second, rect[1].second));
				lines_d[rect[3].first+rect[3].second].insert(minmax(rect[0].second, rect[3].second));
				used_diag_st[rect[2].first][rect[2].second]=1;
				used_diag_st[rect[1].first][rect[1].second]=1;
				used_diag_ed[rect[0].first][rect[0].second]=1;
				used_diag_ed[rect[3].first][rect[3].second]=1;
			}
		}
		{ // diagonal2
			int base = rect[1].first - rect[1].second + n-1;
			if(rect[0].first - rect[0].second == base-n+1){
				lines_d2[base].insert(minmax(rect[0].second, rect[1].second));
				lines_d2[rect[3].first-rect[3].second+n-1].insert(minmax(rect[2].second, rect[3].second));
			}else{
				lines_d2[base].insert(minmax(rect[2].second, rect[1].second));
				lines_d2[rect[3].first-rect[3].second+n-1].insert(minmax(rect[0].second, rect[3].second));
			}
		}
	}
};

bool operator< (const Player &p1, const Player &p2){
	return p1.totalScore < p2.totalScore;
	// return p1.lengthSum > p2.lengthSum || (p1.lengthSum == p2.lengthSum && p1.totalScore < p2.totalScore);
};

const int maxTurn = 800, chokudaiWidth = 1;
vector<priority_queue<Player>> queues(maxTurn+1);


#define ESCAPE if(!Mgr::timer){goto escape;}
int main() {
	cin>>n>>m;
	p.resize(m);
	cin>>p;

	float scoreBase=1e6*n*n/m;
	{
		int weightSum = 0;
		rep(i,n)rep(j,n) weightSum += (i-n/2)*(i-n/2) + (j-n/2)*(j-n/2)+1;
		scoreBase /= weightSum;
	}

	Player initial;
	initial.Init();
	queues[0].emplace(initial);

	int maxScore = 0;
	Player bestPlayer;

	while(Mgr::timer){
		rep(t,maxTurn){
			if(queues[t].size() >= 30){
				vector<Player> tmp;
				rep(5){
					tmp.emplace_back(queues[t].top());
					queues[t].pop();
				}
				while(!queues[t].empty()) queues[t].pop();
				for(auto& p : tmp) queues[t].emplace(p);
			}
			
			rep(i, chokudaiWidth){
				if(queues[t].empty()) break;
				Player player = queues[t].top(); queues[t].pop();
				auto nexts = player.Analyze();
				if(nexts.empty()) {
					if(chmax(maxScore, player.totalScore)){
						debug(Mgr::timer.get(), maxScore);
						bestPlayer = player;
					}
				}
				ESCAPE;
				shuffle(all(nexts), Random);
				rep(j,min(siz(nexts), t<=10 ? 3 : 3)){
					Player nextPlayer = player;
					nextPlayer.AddRect(nexts[j]);
					queues[t+1].emplace(nextPlayer);
				}
				ESCAPE;
			}

			ESCAPE;
		}
		ESCAPE;
	}

	escape:;
	rrep(t,maxTurn+1){
		if(!queues[t].empty()){
			if(chmax(maxScore, queues[t].top().totalScore)){
				bestPlayer = queues[t].top();
			}
			break;
		}
	}

	debug((int)round(bestPlayer.totalScore * scoreBase), Mgr::timer.get());
	bestPlayer.Output();

}
