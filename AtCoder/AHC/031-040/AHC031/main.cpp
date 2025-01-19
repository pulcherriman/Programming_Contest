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
	static const int TLE = 20000;
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


const int W=1000;
int d,n;
vvi a;


struct Coverage {
	int w;
	set<pair<int, int>> st;
	Coverage(int _w) : w(_w) {}
	void add(int l, int r) {
		st.insert(make_pair(-INF,-INF));
		st.insert(make_pair(INF,INF));
		auto it=st.lower_bound(make_pair(l,r)); it--;
		if(it->first <= l and l <= it->second){
			l=min(l,it->first); r=max(r,it->second);
			st.erase(it);
		}
		it=st.lower_bound(make_pair(l,r));
		while(1){
			if(l <= it->first and it->first <= r){ 
				r=max(r,it->second);
				it=st.erase(it);
			}
			else break;
		}
		st.insert(make_pair(l,r));
	}
};

int calcScore(int overCount, vector<tuple<int, int, int, int>> rects) {
	int score = overCount * 100;

	vector<bitset<W>> prevHorizontal(W+1), prevVertical(W+1);
	rep(day,d){
		vector<bitset<W>> horizontal(W+1), vertical(W+1);
		vector<Coverage> horizontalEdges(W+1, W), verticalEdges(W+1, W);

		rep(i,n){
			auto [y1,x1,y2,x2] = rects[day*n+i];
			horizontalEdges[y1].add(x1, x2);
			horizontalEdges[y2].add(x1, x2);
			verticalEdges[x1].add(y1, y2);
			verticalEdges[x2].add(y1, y2);
		}
		rep(i,W+1) {
			for(auto[l,r]:horizontalEdges[i].st) if(abs(l)!=INF) {
				rep(j,l,r) horizontal[i][j]=1;
			}
			for(auto[l,r]:verticalEdges[i].st) if(abs(l)!=INF) {
				rep(j,l,r) vertical[i][j]=1;
			}
		}
		if(day > 0) {
			rep(i,W+1) {
				score += (horizontal[i] ^ prevHorizontal[i]).count();
				score += (vertical[i] ^ prevVertical[i]).count();
			}
		}
		prevHorizontal = horizontal;
		prevVertical = vertical;
	}
	return score + 1;
}

namespace GreedySolver {

	vvi greedy_partition(vi tgts, int sep) {
		vvi res(sep);
		vi sum(sep, 0);
		rrep(i, tgts.size()) { // 大きい順
			int minidx = 0;
			rep(j, sep) {
				if(sum[j] < sum[minidx]) {
					minidx = j;
				}
			}
			res[minidx].pb(tgts[i]);
			sum[minidx] += tgts[i];
		}
		return res;
	}

	auto getPartialSum(int areaSize, vi&order) {
		vi psum(areaSize+1, -2);
		vi availables;

		bool isSparse = sz(order) <= 10;
		if(isSparse){
			map<int, int> mp;
			mp[0] = -1;
			rep(i, sz(order)) {
				for(auto [k, v] : mp | ranges::views::reverse) {
					if (v == -2) continue;
					if (v == i) continue;
					if (!mp.contains(k + order[i])) {
						mp[k + order[i]] = i;
					}
				}
			}

			for (auto [k, v] : mp) {
				if (v != -2 && k <= areaSize) {
					psum[k] = v;
					availables.pb(k);
				}
			}
		} else {
			// psum[i] = 面積iを達成するために最後に使用するオーダーのindex -2=不可能, -1=ここで終了
			int maxArea=0;
			psum[0] = -1;
			rep(i, sz(order)) {
				rrep(j, maxArea+1) {
					if (psum[j] == -2) continue;
					if(j + order[i] <= areaSize && psum[j + order[i]] == -2){
						psum[j + order[i]] = i;
						chmax(maxArea, j + order[i]);
					}
				}
			}

			rep(i,maxArea+1) if (psum[i] != -2) availables.pb(i);
		}

		return make_tuple(psum, availables);
	}

	using Rect = tuple<int, int, int, int>;

	using Line = pair<int, vi>;

	vector<vector<Line>> sortLines(int H, vector<vector<Line>> fields) {
		// out("H", H);
		// rep(day,d){
		// 	if(!fields[day].empty()) {
		// 		out("  day", day);
		// 		for(auto[h, usedArea] : fields[day]) {
		// 			out("   ", h, "\t", usedArea);
		// 		}
		// 	}
		// }
		vi yoyu(d, 0);

		int remainTotalHeight = H, activeCount = 0;;
		rep(day,d) {
			if(fields[day].empty()) continue;
			int heightSum = 0;
			for(auto[h, usedArea] : fields[day]) {
				heightSum += h;
			}
			yoyu[day] = H - heightSum;
			activeCount++;
			chmin(remainTotalHeight, heightSum);
		}

		// TODO: 日付間で横線の更新が無くなるように選ぶ ... X
			// NOTE: 高さに余裕があるとき、いい感じに足して1000にする
		// TODO: 縦線の更新が無くなるように選ぶ ... Y
			// NOTE: 幅に余裕があるとき、いい感じに足して1000にする
		vector<vector<Line>> fieldsAfter(d);
		int mode = 0;
		vb skipped(d, false);

		while(true){
			map<int,int> creatableHeight;
			map<int,vi> creatableHeightDetails;
			vvi heightPsums(d), heightAvailables(d), useRemains(d, vi(W, 0));
			rep(day,d){
				if(fields[day].empty()) continue;
				if(skipped[day]) continue;
				int heightSum = 0;
				vi heights;
				for(auto[h, usedArea] : fields[day]) {
					heightSum += h;
					heights.pb(h);
				}
				auto [psum, availables] = getPartialSum(heightSum, heights);
				if(mode == 0){
					for(auto&x:availables){
						if(x) {
							creatableHeight[x]++;
							creatableHeightDetails[x].pb(day);
						}
					}
					heightPsums[day] = psum;
					heightAvailables[day] = availables;
				} else {
					for(auto&x:availables){
						if(x) {
							creatableHeight[x]++;
							creatableHeightDetails[x].pb(day);
						}
					}
					heightPsums[day] = psum;
					heightAvailables[day] = availables;

					heightPsums[day].resize(H, -2);
					for(auto&x:availables){
						if(x==0) continue;
						rep(useRemain, 1, yoyu[day]+1) {
							if(heightPsums[day][x+useRemain] == -2) {
								creatableHeight[x+useRemain]++;
								creatableHeightDetails[x+useRemain].pb(day);
								heightPsums[day][x+useRemain] = heightPsums[day][x];
								heightAvailables[day].pb(x+useRemain);
								useRemains[day][x+useRemain] = useRemain;
							}
						}
					}
					sort(all(heightAvailables[day]));
				}
			}
			int sameHeight = -1, maxCnt = 1;
			int dayLeft = 0, dayRight = d-1;
			for(auto&[h, usage] : creatableHeightDetails){
				if(h>=remainTotalHeight) break;
				int maxTrail = 0, currentTrail = 0;
				int innerDayLeft = 0, innerDayRight = d-1;
				// usageの連続する数字の個数の最大値
				rep(i, sz(usage)-1){
					if(usage[i]+1 == usage[i+1]){
						currentTrail++;
					}else{
						if(chmax(maxTrail, currentTrail+1)){
							innerDayLeft = usage[i-currentTrail];
							innerDayRight = usage[i];
						}
						currentTrail = 0;
					}
				}
				if(chmax(maxTrail, currentTrail+1)){
					innerDayLeft = usage[sz(usage)-1-currentTrail];
					innerDayRight = usage[sz(usage)-1];
				}

				if(chmax(maxCnt, maxTrail)){
					sameHeight = h;
					dayLeft = innerDayLeft;
					dayRight = innerDayRight;
				}
			}
			if(mode==0 and maxCnt<activeCount) {
				mode = 1;
				continue;
			}

			if(sameHeight != -1){
				remainTotalHeight -= sameHeight;

				vector<vector<Line>> fieldsRecursive(d);
				rep(day,dayLeft, dayRight+1){
					if(fields[day].empty()) continue;
					if(skipped[day]) continue;
					if(mode==1){
						skipped[day] = true;
					}
		
					vector<Line> usedField;
					int remain = sameHeight - useRemains[day][sameHeight];
					if(heightPsums[day][remain] == -2) continue;
					yoyu[day] -=  useRemains[day][sameHeight];
					while(remain != 0) {
						auto idx = heightPsums[day][remain];
						usedField.pb(fields[day][idx]);
						remain -= fields[day][idx].first;
						fields[day].erase(fields[day].begin() + idx);
					}
					{
						sort(all(usedField), greater<>());
						vi heights;
						for(auto[h, usedArea] : usedField) {
							heights.pb(h);
						}
					}
					fieldsRecursive[day] = usedField;
				}

				auto recursiveSorted = sortLines(sameHeight+ (activeCount==d && maxCnt==d ? 0  : 0), fieldsRecursive); // + (mode==0 && activeCount==d && maxCnt==d ? 1 : 0)
				rep(day,d){
					if(fields[day].empty()) continue;
					// if(skipped[day]) continue;
					fieldsAfter[day].insert(fieldsAfter[day].end(), all(recursiveSorted[day]));
				}
			} else {
				if(mode == 0){
					mode = 1;
				} else {
					rep(day,d){
						if(fields[day].empty()) continue;
						sort(all(fields[day]), greater<>());
						fieldsAfter[day].insert(fieldsAfter[day].end(), all(fields[day]));
					}
					rep(day,d) {
						if(fields[day].empty()) continue;
						int heightSum = 0;
						for(auto[h, usedArea] : fieldsAfter[day]) {
							heightSum += h;
						}
						fieldsAfter[day].back().first += H - heightSum;
					}
					break;
				}
			}
		}
		// out("Result H", H);
		// rep(day,d){
		// 	if(!fieldsAfter[day].empty()) {
		// 		out("  day", day);
		// 		for(auto[h, usedArea] : fieldsAfter[day]) {
		// 			out("   ", h, "\t", usedArea);
		// 		}
		// 	}
		// }
		return fieldsAfter;
	}

	pair<int, vector<tuple<int, int, int, int>>> entry() {
		int overSum = 0;
		vector<Rect> ans(d*n);

		vector<vector<Line>> fields;

		rep(day, d) {
			vi val = a[day];
			map<int, int> areaToIdx;
			rep(i, n) areaToIdx[val[i]] = i;
			vb used(n, false);

			vector<Line> field;

			rrep(rect, n) {
				if(used[rect]) continue;

				int heightLowerLimit = (val[rect]+W-1) / W;// 最低でもこの高さの行が要る

				int bestWidth = INF;
				int bestHeight = heightLowerLimit; 
				vi bestPSum, bestAvailables, indicesMap;
				rep(i,rect+1)if(!used[i]){
					indicesMap.pb(i);
				}
				vi usedItems, usedArea(1, val[rect]);

				if(sz(indicesMap) > 1) {
					rep(h, heightLowerLimit, min(heightLowerLimit + 100, W+1)) {
						vi ws;
						rep(i,rect+1)if(!used[i]){
							ws.pb(val[i] / h + !!(val[i] % h));
						}

						// 最大のを使う
						int widthRemain = W - ws.back();
						ws.pop_back();

						auto [psum, availables] = getPartialSum(widthRemain, ws);
						auto availableMax = *(--upper_bound(all(availables), W));

						int failedArea = h * (widthRemain - availableMax) + (val[rect] + h - 1) / h * h - val[rect];
						// NOTE: 無駄になる面積の最大値は、要素数*高さ
						//       大きい奴から使う、高さが低いものを採用するなどで対応
						if(!availables.empty()){
							int remain = availables.back();
							while(remain != 0 and failedArea < bestWidth) {
								const int usedWidth = (val[indicesMap[psum[remain]]] + h - 1) / h;
								failedArea += usedWidth * h - val[indicesMap[psum[remain]]];
								remain -= usedWidth;
							}
						}
						if(chmin(bestWidth, failedArea)) {
							bestHeight = h;
							bestPSum = psum;
							bestAvailables = availables;
							if(failedArea == 0) break; // いいのが見つかったら抜ける NOTE: 最善とは限らん
						}
					}

					if(!bestAvailables.empty()){
						int remain = bestAvailables.back();
						while(remain != 0) {
							usedArea.pb(val[indicesMap[bestPSum[remain]]]);
							remain -= (val[indicesMap[bestPSum[remain]]] + bestHeight - 1) / bestHeight;
						}
					}

					for(auto&x : usedArea) {
						auto idx = areaToIdx[x]--;
						usedItems.pb(idx);
						used[idx] = true;
					}
				}
				field.emplace_back(bestHeight, usedArea);
			}
			// TODO: Heightがあふれるとき、全てのLineを適切に減らしてみて、最善の所を採用
			fields.pb(field);
		}

		auto fieldsAfter = sortLines(W, fields);

		rep(day,d){
			map<int, int> areaToIdx;
			rep(i, n) areaToIdx[a[day][i]] = i;
			int heightSum = 0;

			int cnt = 0;
			for(auto[h, usedArea] : fieldsAfter[day]) {
				cnt++;
				int widthSum = 0;
				rep(i, sz(usedArea)){
					int area = usedArea[i];
					int width = (area + h - 1) / h;
					if(i+1 == sz(usedArea)) {
						width = W - widthSum; // NOTE: Y をやったら消す
					}
					// if(cnt==sz(fieldsAfter[day])){
					// 	ans[day*n + areaToIdx[area]--] = {heightSum, widthSum, W, widthSum + width};
					// }else{
					ans[day*n + areaToIdx[area]--] = {heightSum, widthSum, min(heightSum + h, W), widthSum + width};
					// }
					widthSum += width;
				}
				heightSum += h;
			}
		}


		rep(i,d)rep(j,n){
			auto [y1, x1, y2, x2] = ans[i*n+j];
			overSum += max(0, a[i][j] - (y2-y1)*(x2-x1));
		}

		return {overSum, ans};
	}
}


namespace EaseGreedySolver {

	vvi greedy_partition(vi&tgts, int sep) {
		vvi res(sep);
		vi sum(sep, 0);
		rrep(i, tgts.size()) { // 大きい順
			int minidx = 0;
			rep(j, sep) {
				if(sum[j] < sum[minidx]) {
					minidx = j;
				}
			}
			res[minidx].pb(tgts[i]);
			sum[minidx] += tgts[i];
		}
		return res;
	}

	auto getPartialSum(int areaSize, vi&order) {
		vi psum(areaSize+1, -2);
		vi availables;

		bool isSparse = sz(order) <= 10;
		if(isSparse){
			map<int, int> mp;
			mp[0] = -1;
			rep(i, sz(order)) {
				for(auto [k, v] : mp | ranges::views::reverse) {
					if (v == -2) continue;
					if (v == i) continue;
					if (!mp.contains(k + order[i])) {
						mp[k + order[i]] = i;
					}
				}
			}

			for (auto [k, v] : mp) {
				if (v != -2 && k <= areaSize) {
					psum[k] = v;
					availables.pb(k);
				}
			}
		} else {
			// psum[i] = 面積iを達成するために最後に使用するオーダーのindex -2=不可能, -1=ここで終了
			int maxArea=0;
			psum[0] = -1;
			rep(i, sz(order)) {
				rrep(j, maxArea+1) {
					if (psum[j] == -2) continue;
					if(j + order[i] <= areaSize && psum[j + order[i]] == -2){
						psum[j + order[i]] = i;
						chmax(maxArea, j + order[i]);
					}
				}
			}

			rep(i,maxArea+1) if (psum[i] != -2) availables.pb(i);
		}

		return make_tuple(psum, availables);
	}

	using Rect = tuple<int, int, int, int>;

	using Line = pair<int, vi>;

	vector<vector<Line>> sortLines(int H, vector<vector<Line>> fields) {
		// out("H", H);
		// rep(day,d){
		// 	if(!fields[day].empty()) {
		// 		out("  day", day);
		// 		for(auto[h, usedArea] : fields[day]) {
		// 			out("   ", h, "\t", usedArea);
		// 		}
		// 	}
		// }
		vi yoyu(d, 0);

		int remainTotalHeight = H, activeCount = 0;;
		rep(day,d) {
			if(fields[day].empty()) continue;
			int heightSum = 0;
			for(auto[h, usedArea] : fields[day]) {
				heightSum += h;
			}
			yoyu[day] = H - heightSum;
			activeCount++;
			chmin(remainTotalHeight, heightSum);
		}

		// TODO: 日付間で横線の更新が無くなるように選ぶ ... X
			// NOTE: 高さに余裕があるとき、いい感じに足して1000にする
		// TODO: 縦線の更新が無くなるように選ぶ ... Y
			// NOTE: 幅に余裕があるとき、いい感じに足して1000にする
		vector<vector<Line>> fieldsAfter(d);
		int mode = 0;
		vb skipped(d, false);

		while(true){
			HashMap<int,int> creatableHeight;
			HashMap<int,vi> creatableHeightDetails;
			vvi heightPsums(d), heightAvailables(d), useRemains(d, vi(W, 0));
			rep(day,d){
				if(fields[day].empty()) continue;
				if(skipped[day]) continue;
				int heightSum = 0;
				vi heights;
				for(auto[h, usedArea] : fields[day]) {
					heightSum += h;
					heights.pb(h);
				}
				auto [psum, availables] = getPartialSum(heightSum, heights);
				if(mode == 0){
					for(auto&x:availables){
						if(x) {
							creatableHeight[x]++;
							creatableHeightDetails[x].pb(day);
						}
					}
					heightPsums[day] = psum;
					heightAvailables[day] = availables;
				} else {
					for(auto&x:availables){
						if(x) {
							creatableHeight[x]++;
							creatableHeightDetails[x].pb(day);
						}
					}
					heightPsums[day] = psum;
					heightAvailables[day] = availables;

					heightPsums[day].resize(H, -2);
					for(auto&x:availables){
						if(x==0) continue;
						rep(useRemain, 1, yoyu[day]+1) {
							if(heightPsums[day][x+useRemain] == -2) {
								creatableHeight[x+useRemain]++;
								creatableHeightDetails[x+useRemain].pb(day);
								heightPsums[day][x+useRemain] = heightPsums[day][x];
								heightAvailables[day].pb(x+useRemain);
								useRemains[day][x+useRemain] = useRemain;
							}
						}
					}
					sort(all(heightAvailables[day]));
				}
			}
			int sameHeight = -1, maxCnt = 1;
			int dayLeft = 0, dayRight = d-1;
			for(auto&[h, usage] : creatableHeightDetails){
				if(h>=remainTotalHeight) break;
				int maxTrail = 0, currentTrail = 0;
				int innerDayLeft = 0, innerDayRight = d-1;
				// usageの連続する数字の個数の最大値
				rep(i, sz(usage)-1){
					if(usage[i]+1 == usage[i+1]){
						currentTrail++;
					}else{
						if(chmax(maxTrail, currentTrail+1)){
							innerDayLeft = usage[i-currentTrail];
							innerDayRight = usage[i];
						}
						currentTrail = 0;
					}
				}
				if(chmax(maxTrail, currentTrail+1)){
					innerDayLeft = usage[sz(usage)-1-currentTrail];
					innerDayRight = usage[sz(usage)-1];
				}

				if(chmax(maxCnt, maxTrail)){
					sameHeight = h;
					dayLeft = innerDayLeft;
					dayRight = innerDayRight;
				}
			}
			if(mode==0 and maxCnt<activeCount) {
				mode = 1;
				continue;
			}

			if(sameHeight != -1){
				remainTotalHeight -= sameHeight;

				vector<vector<Line>> fieldsRecursive(d);
				rep(day,dayLeft, dayRight+1){
					if(fields[day].empty()) continue;
					if(skipped[day]) continue;
					if(mode==1){
						skipped[day] = true;
					}
		
					vector<Line> usedField;
					int remain = sameHeight - useRemains[day][sameHeight];
					if(heightPsums[day][remain] == -2) continue;
					yoyu[day] -=  useRemains[day][sameHeight];
					while(remain != 0) {
						auto idx = heightPsums[day][remain];
						usedField.pb(fields[day][idx]);
						remain -= fields[day][idx].first;
						fields[day].erase(fields[day].begin() + idx);
					}
					{
						sort(all(usedField), greater<>());
						vi heights;
						for(auto[h, usedArea] : usedField) {
							heights.pb(h);
						}
					}
					fieldsRecursive[day] = usedField;
				}

				auto recursiveSorted = sortLines(sameHeight, fieldsRecursive); // + (mode==0 && activeCount==d && maxCnt==d ? 1 : 0)
				int afterHeight = sameHeight;
				rep(day,d){
					if(fields[day].empty()) continue;
					// if(skipped[day]) continue;
					fieldsAfter[day].insert(fieldsAfter[day].end(), all(recursiveSorted[day]));
					int heightSum = 0;
					for(auto[h, usedArea] : recursiveSorted[day]) {
						heightSum += h;
					}
					chmax(afterHeight, heightSum);
				}
				remainTotalHeight -= (afterHeight - sameHeight);
			} else {
				if(mode == 0){
					mode = 1;
				} else {
					rep(day,d){
						if(fields[day].empty()) continue;
						sort(all(fields[day]), greater<>());
						fieldsAfter[day].insert(fieldsAfter[day].end(), all(fields[day]));
					}
					rep(day,d) {
						if(fields[day].empty()) continue;
						int heightSum = 0;
						for(auto[h, usedArea] : fieldsAfter[day]) {
							heightSum += h;
						}
						fieldsAfter[day].back().first += H - heightSum;
					}
					break;
				}
			}
		}
		// out("Result H", H);
		// rep(day,d){
		// 	if(!fieldsAfter[day].empty()) {
		// 		out("  day", day);
		// 		for(auto[h, usedArea] : fieldsAfter[day]) {
		// 			out("   ", h, "\t", usedArea);
		// 		}
		// 	}
		// }
		return fieldsAfter;
	}

	pair<int, vector<tuple<int, int, int, int>>> entry() {
		int overSum = 0;
		vector<Rect> ans(d*n);

		vector<vector<Line>> fields;


		rep(day, d) {
			vi val = a[day];
			HashMap<int, int> areaToIdx;
			rep(i, n) areaToIdx[val[i]] = i;
			vb used(n, false);

			vector<Line> field;

			rrep(rect, n) {
				if(used[rect]) continue;

				int heightLowerLimit = (val[rect]+W-1) / W;// 最低でもこの高さの行が要る

				int threshold = 100;
				if(day && sz(fields[day-1]) > sz(field)) {
					auto prevLine = fields[day-1][sz(field)];
					if(heightLowerLimit <= prevLine.first) {
						heightLowerLimit = prevLine.first;
						threshold = 1;
					}
				}

				int bestHeight = heightLowerLimit; 
				vi indicesMap, usedArea(1, val[rect]);
				rep(i,rect+1)if(!used[i]){
					indicesMap.pb(i);
				}

				if(sz(indicesMap) > 1) {
					int bestWidth = INF;
					vi bestPSum, bestAvailables;

					rep(h, heightLowerLimit, min(heightLowerLimit + threshold, W+1)) {
						vi ws;
						rep(i,rect+1)if(!used[i]){
							ws.pb(val[i] / h + !!(val[i] % h));
						}

						// 最大のを使う
						int widthRemain = W - ws.back();
						ws.pop_back();

						auto [psum, availables] = getPartialSum(widthRemain, ws);
						auto availableMax = *(--upper_bound(all(availables), W));

						int failedArea = h * (widthRemain - availableMax) + (val[rect] + h - 1) / h * h - val[rect];
						// NOTE: 無駄になる面積の最大値は、要素数*高さ
						//       大きい奴から使う、高さが低いものを採用するなどで対応
						if(!availables.empty()){
							int remain = availables.back();
							while(remain != 0 and failedArea < bestWidth) {
								const int usedWidth = (val[indicesMap[psum[remain]]] + h - 1) / h;
								failedArea += usedWidth * h - val[indicesMap[psum[remain]]];
								remain -= usedWidth;
							}
						}
						if(chmin(bestWidth, failedArea)) {
							bestHeight = h;
							bestPSum = psum;
							bestAvailables = availables;
							if(failedArea == 0) break; // いいのが見つかったら抜ける NOTE: 最善とは限らん
						}
					}


					if(!bestAvailables.empty()){
						int remain = bestAvailables.back();
						while(remain != 0) {
							usedArea.pb(val[indicesMap[bestPSum[remain]]]);
							remain -= (val[indicesMap[bestPSum[remain]]] + bestHeight - 1) / bestHeight;
						}
					}

					for(auto&x : usedArea) {
						auto idx = areaToIdx[x]--;
						used[idx] = true;
					}
				} else {
					heightLowerLimit = (val[rect]+W-1) / W;
				}
				field.emplace_back(bestHeight, usedArea);
			}
			// TODO: Heightがあふれるとき、全てのLineを適切に減らしてみて、最善の所を採用
			fields.pb(field);
		}

		auto fieldsAfter = sortLines(W, fields);

		rep(day,d){
			HashMap<int, int> areaToIdx;
			rep(i, n) areaToIdx[a[day][i]] = i;
			int heightSum = 0;

			int cnt = 0;
			for(auto[h, usedArea] : fieldsAfter[day]) {
				cnt++;
				int widthSum = 0;
				rep(i, sz(usedArea)){
					int area = usedArea[i];
					int width = (area + h - 1) / h;
					if(i+1 == sz(usedArea)) {
						width = W - widthSum; // NOTE: Y をやったら消す
					}
					// if(cnt==sz(fieldsAfter[day])){
					// 	ans[day*n + areaToIdx[area]--] = {heightSum, widthSum, W, widthSum + width};
					// }else{
					ans[day*n + areaToIdx[area]--] = {heightSum, widthSum, heightSum + h, widthSum + width};
					// }
					if(heightSum + h  > W) {
						return {INF, {}};
					}
					if(widthSum + width > W) {
						return {INF, {}};
					}
					widthSum += width;
				}
				heightSum += h;
			}
		}


		rep(i,d)rep(j,n){
			auto [y1, x1, y2, x2] = ans[i*n+j];
			overSum += max(0, a[i][j] - (y2-y1)*(x2-x1));
		}

		return {overSum, ans};
	}
}


namespace RecursiveSolver {
	struct Point {
		int y=0, x=0;
	};

	struct Line {
		bool isHorizontal=false;
		int relPos=0;
	};

	struct Rect {
		Point tl, br;
		Line sep;
		int area=0;
		Rect *left, *right;

		Rect() {}
		Rect(Point _tl, Point _br) : tl(_tl), br(_br) {
			area = (br.y - tl.y) * (br.x - tl.x);
		}
		inline int width() const { return br.x - tl.x; }
		inline int height() const { return br.y - tl.y; }
		inline int sepLength() const { return sep.isHorizontal ? width() : height(); }
	};

	auto justFit(Rect&rect, vi order) {
		// 横割り
		vi leftOrder, rightOrder;
		{
			rep(i,sz(order)) {
				if (order[i] % rect.width() == 0) {
					rect.sep.isHorizontal = true;
					rect.sep.relPos = order[i] / rect.width();
					rect.left = new Rect(rect.tl, Point{rect.tl.y + rect.sep.relPos, rect.br.x});
					rect.right = new Rect(Point{rect.tl.y + rect.sep.relPos, rect.tl.x}, rect.br);
					leftOrder = vi(1, order[i]);
					rightOrder = order;
					rightOrder.erase(rightOrder.begin() + i);
					return make_tuple(leftOrder, rightOrder);
				}
			}
		}
		{
			rep(i,sz(order)) {
				if (order[i] % rect.height() == 0) {
					rect.sep.isHorizontal = false;
					rect.sep.relPos = order[i] / rect.height();
					rect.left = new Rect(rect.tl, Point{rect.br.y, rect.tl.x + rect.sep.relPos});
					rect.right = new Rect(Point{rect.tl.y, rect.tl.x + rect.sep.relPos}, rect.br);
					leftOrder = vi(1, order[i]);
					rightOrder = order;
					rightOrder.erase(rightOrder.begin() + i);
					return make_tuple(leftOrder, rightOrder);
				}
			}
		}
		return make_tuple(leftOrder, rightOrder);
	}


	auto getPartialSum(int areaSize, vi&order, int requireAvailableValue) {
		vi psum(areaSize+1, -2);
		vi availables;
		int okValue = areaSize;

		bool isSparse = sz(order) <= 10;
		if(isSparse){
			map<int, int> mp;
			mp[0] = -1;
			rep(i, sz(order)) {
				for(auto [k, v] : mp | ranges::views::reverse) {
					if (v == -2) continue;
					if (v == i) continue;
					if (!mp.contains(k + order[i])) {
						mp[k + order[i]] = i;
					}
				}
			}

			for (auto [k, v] : mp) {
				if (v != -2) {
					psum[k] = v;
					availables.pb(k);
				}
			}
		} else {
			// psum[i] = 面積iを達成するために最後に使用するオーダーのindex -2=不可能, -1=ここで終了
			int maxArea=0;
			psum[0] = -1;
			rep(i, sz(order)) {
				rrep(j, min(maxArea, okValue)+1) {
					if (psum[j] == -2) continue;
					if(psum[j + order[i]] == -2){
						psum[j + order[i]] = i;
						chmax(maxArea, j + order[i]);
						if(j+order[i] >= requireAvailableValue) chmin(okValue, j+order[i]);
					}
				}
			}

			rep(i,maxArea+1) if (psum[i] != -2) availables.pb(i);
		}

		return make_tuple(psum, availables);
	}

	auto calcPsum(Rect&rect, vi order) {	
		int remain = rect.area - sum(order);
		if (remain < 0) return make_tuple(vi(), vi());

		sort(all(order));
		if (sz(order) == 1) {
			// TODO
		}
		int requireAvailableValue = (rect.area-remain)/2-1;
		if (rect.sep.relPos != 0) { chmax(requireAvailableValue, rect.left->area - remain/2); }
		auto [psum, availables] = getPartialSum(rect.area, order, requireAvailableValue);

		{
			bool isHorizontal = rect.width() < rect.height();
			int leftArea = *lower_bound(all(availables), (rect.area-remain)/2); // NOTE: 必ず半分以上になる分け方が存在する
			bool isSameSeparate = false;
			if (rect.sep.relPos != 0) {
				int newLeftArea = *(upper_bound(all(availables), rect.left->area - remain/2) - 1);
				if (newLeftArea > 0 and newLeftArea < sum(order)) {
					isSameSeparate = true;
					isHorizontal = rect.sep.isHorizontal;
					leftArea = newLeftArea;
				}
			}

			vi leftOrder, rightOrder;
			{
				int idx = psum[leftArea], remainLeftArea = leftArea;
				while (idx != -1) {
					leftOrder.pb(order[idx]);
					remainLeftArea -= order[idx];
					idx = psum[remainLeftArea];
				}

				rightOrder = order;
				for (auto&x : leftOrder) {
					auto it = find(all(rightOrder), x);
					rightOrder.erase(it);
				}
			}

			// 割る方向の決定
			if (isHorizontal) {
				int leftHeight = (leftArea + rect.width() - 1) / rect.width();
				int rightHeight = (sum(order) - leftArea + rect.width() - 1) / rect.width();
				if(leftHeight + rightHeight > rect.height()) return make_tuple(vi(), vi());
				int lineRemain = rect.height() - leftHeight - rightHeight;

				int lineThresholdL = 2, lineThresholdR = 2;
				if(sz(leftOrder) == 2) lineThresholdL = 1;
				if(sz(rightOrder) == 2) lineThresholdR = 1;
				if(sz(leftOrder) == 1) lineThresholdL = 0;
				if(sz(rightOrder) == 1) lineThresholdR = 0;

				if (!isSameSeparate or !(leftHeight+lineThresholdL <= rect.sep.relPos and rect.sep.relPos <= leftHeight + lineRemain-lineThresholdR)) {
					leftHeight += lineRemain / 2;
					rect.sep.isHorizontal = true;
					rect.sep.relPos = leftHeight;

					rect.left = new Rect(rect.tl, Point{rect.tl.y + leftHeight, rect.br.x});
					rect.right = new Rect(Point{rect.tl.y + leftHeight, rect.tl.x}, rect.br);
				}
			} else {
				int leftWidth = (leftArea + rect.height() - 1) / rect.height();
				int rightWidth = (sum(order) - leftArea + rect.height() - 1) / rect.height();
				if(leftWidth + rightWidth > rect.width()) return make_tuple(vi(), vi());
				int lineRemain = rect.width() - leftWidth - rightWidth;
				
				int lineThresholdL = 2, lineThresholdR = 2;
				if(sz(leftOrder) == 2) lineThresholdL = 1;
				if(sz(rightOrder) == 2) lineThresholdR = 1;
				if(sz(leftOrder) == 1) lineThresholdL = 0;
				if(sz(rightOrder) == 1) lineThresholdR = 0;

				if (!isSameSeparate or !(leftWidth+lineThresholdL <= rect.sep.relPos and rect.sep.relPos <= leftWidth + lineRemain-lineThresholdR)) {
					leftWidth += lineRemain / 2;
					rect.sep.isHorizontal = false;
					rect.sep.relPos = leftWidth;

					rect.left = new Rect(rect.tl, Point{rect.br.y, rect.tl.x + leftWidth});
					rect.right = new Rect(Point{rect.tl.y, rect.tl.x + leftWidth}, rect.br);
				}
			}
		
			return make_tuple(leftOrder, rightOrder);
		}
	}

	pair<int, vector<tuple<int, int, int, int>>> entry() {
		int overSum = 0;
		vector<tuple<int, int, int, int>> rects;

		Rect root(Point{0, 0}, Point{W, W});

		vi remainThresholds = {20000, 35000, 70000};
		rep(day,d) {
			for(auto remainThreshold : remainThresholds){
				auto b = a[day];
				{
					int remain = W*W - sum(b);
					float moreRemain = remainThreshold - remain;
					if(moreRemain > 0) {
						rep(i,n) {
							b[i] -= moreRemain * b[i] / (W*W - remain);
						}
					}
				}

				HashMap<int, int> areaToIdx;
				rep(i, n) areaToIdx[b[i]] = i;
				vector<Rect> ans(n);

				function<bool(Rect&, vi)> separate = [&](Rect&rect, vi order) {
					auto [leftOrder, rightOrder] = calcPsum(rect, order);
					if(sz(leftOrder) == 0) return false;

					bool ret = true;
					if (sz(leftOrder) > 1) {
						ret &= separate(*rect.left, leftOrder);
					} else {
						ans[areaToIdx[leftOrder[0]]--] = *(rect.left);
					}
					if(!ret) return false;

					if (sz(rightOrder) > 1) {
						ret &= separate(*rect.right, rightOrder);
					} else {
						ans[areaToIdx[rightOrder[0]]--] = *(rect.right);
					}
					return ret;
				};
				auto ok = separate(root, b);
				if(ok) {
					rep(j, n) {
						auto&x = ans[j];
						rects.emplace_back(x.tl.y, x.tl.x, x.br.y, x.br.x);
						overSum += max(0, a[day][j] - x.area);
					}
					break;
				}
			}
		}
		return {overSum, rects};
	}
}


int main() { /**/
	{
		def(int,_);
		cin>>d>>n;
		a.resize(d, vi(n));
		in(a);

		int score = INF; vector<tuple<int, int, int, int>> ans;
		auto update = [&](pair<int, vector<tuple<int, int, int, int>>>&&solved){
			if(solved.first==INF)return;
			int tmp = calcScore(solved.first, solved.second);
			if(chmin(score, tmp)) ans = solved.second;
		};

		update(EaseGreedySolver::entry());
		debug_f(Mgr::timer.get());
		update(GreedySolver::entry());

		debug_f(Mgr::timer.get());

		{
			int remain = W*W*d;
			rep(day,d)rep(i,n) remain -= a[day][i];
			remain/=d;
			if(remain>=20000){
				update(RecursiveSolver::entry());
				debug_f(Mgr::timer.get());
			}
		}

		debug_f(score);
		for(auto&[y1,x1,y2,x2]:ans){
			out(y1,x1,y2,x2);
		}
	}
}