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
#if defined(EVAL) || defined(ONLINE_JUDGE) || defined(_DEBUG)
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
#define __RANGE(i,a,n) for(int i=((ll)a);i<((ll)n);++i)
#define __RREP(i,n) __RRANGE(i,0,n)
#define __RRANGE(i,a,n) for(int i=((ll)(n)-1);i>=((ll)a);--i)
#define sz(a) ((int)(a).size())
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
	static const int TLE = 2000;
	static inline Timer timer = Timer(TLE-20);
	Mgr() {
		ios_base::sync_with_stdio(0);
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

int L,N,S;
vi P;
vvi placedPower;

struct Judge {
	int _mCnt=0;
#ifdef _DEBUG
	vi correspond;
	vi _mRnd;
#endif

	void initialize() {
		in(L,N,S);
		rep(N){
			def(int,y,x);
			P.push_back(y*L+x);
		}
		placedPower = vvi(L, vi(L, -1));

#ifdef _DEBUG
		correspond.resize(N);
		in(correspond);
#endif
	}

	void placement() {
		smooth();
		for(auto&line: placedPower) out(line);
	}

	void smooth() {
		// ハッシュ値調査で使用されないセルに、配置コストが最小になるような数値を埋める
		set<int> keep;
		rep(i,L)rep(j,L) {
			if(placedPower[i][j] != -1) keep.insert(i*L+j);
			else placedPower[i][j] = 0;
		}

		vvi score(L,vi(L, 0));
		int dy[] = {0,1,0,-1}, dx[] = {1,0,-1,0};

		rep(i,L)rep(j,L) {
			int adjacent = 0;
			// torus
			rep(k,4) {
				int y = (i+dy[k]+L)%L, x = (j+dx[k]+L)%L;
				int diff = placedPower[i][j] - placedPower[y][x];
				adjacent += diff * diff;
			}
			score[i][j] = adjacent;
		}

		// 山登り
		rep(100)rep(i,L)rep(j,L){
			if(keep.count(i*L+j)) continue;
			int tgtValue=0;
			rep(k,4) {
				int y = (i+dy[k]+L)%L, x = (j+dx[k]+L)%L;
				tgtValue += placedPower[y][x];
			}
			tgtValue /= 4;
			tgtValue = clamp(tgtValue + Random(-10, 10+1), 0, 1000);

			int adjacent = 0;
			rep(k,4) {
				int y = (i+dy[k]+L)%L, x = (j+dx[k]+L)%L;
				int diff = tgtValue - placedPower[y][x];
				adjacent += diff * diff;
			}
			if(adjacent < score[i][j]) {
				placedPower[i][j] = tgtValue;
				score[i][j] = adjacent;

				// update adjacent score
				rep(k,4) {
					int y = (i+dy[k]+L)%L, x = (j+dx[k]+L)%L;
					score[y][x] = 0;
					rep(l,4) {
						int yy = (y+dy[l]+L)%L, xx = (x+dx[l]+L)%L;
						int diff = placedPower[y][x] - placedPower[yy][xx];
						score[y][x] += diff * diff;
					}
				}
			}
		}
	}

	bool isEmergency = false;
	using MeasureQuery = tuple<int,int,int>;
	HashMap<tuple<int,int,int>,int> _memoSum, _memoCnt;
	int measurement(int index, int dy, int dx, bool isMeasure=true) {		
		const MeasureQuery query = make_tuple(index, dy, dx);
		if (!isMeasure) {
			return _memoSum[query] / _memoCnt[query];
		}
		if(_mCnt >= 10000) {
			isEmergency = true;
			return _memoSum[query] / _memoCnt[query];
		}
		_mCnt++;
		out(index, dy, dx);
		int r;
#ifdef _DEBUG
		if(_mCnt<10000){
			cin>>r;
			_mRnd.push_back(r);
		}else{
			_mCnt++;
			r=_mRnd[_mCnt%10000];
		}
		int tgt = P[correspond[index]];
		int y = tgt / L, x = tgt % L;
		y = (y + dy + L) % L;
		x = (x + dx + L) % L;
		r = max(0, min(1000, placedPower[y][x] + r));
#else
		cin>>r;
#endif
		_memoCnt[query]++;
		_memoSum[query] += r;
		return _memoSum[query] / _memoCnt[query];
	}
	
} judge;

vector<pair<int,int>> getDiffs(){
	static vector<pair<int,int>> diff;
	if(diff.empty()){
		rep(d,L*2){
			rep(i,L) rep(j,L) {
				if(i+j==d) {
					diff.emplace_back(i,j);
					if(i!=0) diff.emplace_back(-i,j);
					if(j!=0) diff.emplace_back(i,-j);
					if(i!=0&&j!=0) diff.emplace_back(-i,-j);
				}
			}
		}
	}
	return diff;
}

struct Solver {
	int D=0, R=0, SP=0;

	Solver() {
		D = min(S * 3 + 1, 1000);	// 3sigma ~= 99.7%
		R = 2;
		SP = 1000 / D + 1;
	}

	ll hashize(vi indices) {
		ll h = 0;
		for(auto i : indices) h = h * SP + i;
		return h;
	}

	vi dehashize(ll h) {
		vi indices;
		rep(hashSize) {
			indices.push_back(h%SP);
			h /= SP;
		}
		reverse(all(indices));
		return indices;
	}

	vvi getIndicesCandidates(int baseLength) {
		vvi indicesList;
		rep(i,SP) indicesList.push_back({i});

		int cur=0;
		while(true){
			if(sz(indicesList[cur])==baseLength) break;
			rep(i,SP){
				indicesList.push_back(indicesList[cur]);
				indicesList.back().push_back(i);
			}
			cur++;
		}
		reverse(all(indicesList));
		while(sz(indicesList.back())!=baseLength) indicesList.pop_back();

		shuffle(all(indicesList), Random);

		sort(all(indicesList), [&](vi&l, vi&r){
			int maxL = max(l), maxR = max(r);
			if(maxL!=maxR) return maxL<maxR;
			return min(l) > min(r);
		});

		return indicesList;
	}

	// ハッシュをどの順で配置するか
	vector<pair<int,int>> getDiffs(){
		static vector<pair<int,int>> diff;
		if(!diff.empty()) return diff;
		rep(d,L*2) rep(i,L) rep(j,L) if(i+j==d) {
			diff.emplace_back(i,j);
			if(i!=0) diff.emplace_back(-i,j);
			if(j!=0) diff.emplace_back(i,-j);
			if(i!=0&&j!=0) diff.emplace_back(-i,-j);
		}
		return diff;
	}

	bool isPlaceableHash(int doorIndex, vi indices) {
		const auto diff = getDiffs();
		const int tgt = P[doorIndex];
		const int y = tgt / L, x = tgt % L;

		bool ok=true;
		rep(i, indices.size()) {
			const auto [dy, dx] = diff[i];
			const int ny = (y + dy + L) % L, nx = (x + dx + L) % L;
			if(placedPower[ny][nx] != -1 and placedPower[ny][nx] != D*indices[i]) {
				ok=false;
				break;
			}
		}
		if (!ok) return false;
		
		rep(i, indices.size()) {
			const auto [dy, dx] = diff[i];
			const int ny = (y + dy + L) % L, nx = (x + dx + L) % L;
			placedPower[ny][nx] = D*indices[i];
		}
		return true;
	}

	using PlaceInfo = tuple<int, ll, vvi, map<ll, int>>;
	// このハッシュはどの出口のものか
	map<ll, int> hashMemo;
	// この出口のハッシュは何か
	vl doorHashMemo;
	
	PlaceInfo randomPlacement() {
		placedPower = vvi(L, vi(L, -1));
		hashMemo.clear();

		vector<pair<int,int>> towns;
		rep(i,N){
			towns.emplace_back(P[i]/L, P[i]%L);
		}
		const auto diff=getDiffs();
		const auto getField = [&]() {
			const auto getFieldRec = [&](vvi value) {
				int ok=15, ng=0;
				while(ok-ng>1) {
					int mid = (ok+ng)/2;
					HashSet<ll> hs;

					bool truthy=true;
					for(auto[i,j]:towns){
						ll v=0;
						rep(k,mid){
							v= v*SP+value[(i+diff[k].first+L)%L][(j+diff[k].second+L)%L];
						}
						if(hs.find(v) != hs.end()) {
							truthy = false;
							break;
						}
						hs.insert(v);
					}
					if(truthy) ok = mid;
					else ng = mid;
				}

				ll placementScore = 0;
				rep(i,L)rep(j,L){
					ll cur = value[i][j] * D;
					ll below = value[(i+L-1)%L][j] * D;
					ll right = value[i][(j+L-1)%L] * D;
					placementScore += (cur-below)*(cur-below) + (cur-right)*(cur-right);
				}
				return make_tuple(ok, placementScore);
			};

			vvi initValue(L, vi(L));
			rep(i,L) rep(j,L) {
				initValue[i][j] = Random(0,SP);
			}

			auto [cnt, pScore] = getFieldRec(initValue);
			rep(30000){
				auto value = initValue;
				int i = Random(0,L), j = Random(0,L), r = Random(0, SP);
				rep(dy,2)rep(dx,-1,2){
					value[(i+dy+L)%L][(j+dx+L)%L] = r;
				}
				const auto [cnt2, pScore2] = getFieldRec(value);
				if(cnt2<cnt or (cnt2==cnt and pScore2<pScore)) {
					cnt = cnt2;
					pScore = pScore2;
					initValue = value;
					debug(cnt, pScore);
				}
			}

			return make_tuple(cnt, initValue, pScore);
		};

		// 各タウンについて、ハッシュ値とpowerを計算する
		auto [cnt, value, placeScore] = getField();
		rep(i,L)rep(j,L) {
			placedPower[i][j] = value[i][j] * D;
		}
		rep(i,N){
			vi indices;
			rep(j,cnt) {
				const auto [dy, dx] = diff[j];
				const int ny = (towns[i].first + dy + L) % L, nx = (towns[i].second + dx + L) % L;
				indices.push_back(value[ny][nx]);
			}
			hashMemo[hashize(indices)] = i;
		}

		judge.smooth();
		ll placementScore = 0;
		rep(i,L)rep(j,L){
			ll cur = placedPower[i][j];
			ll below = placedPower[(i+L-1)%L][j];
			ll right = placedPower[i][(j+L-1)%L];
			placementScore += (cur-below)*(cur-below) + (cur-right)*(cur-right);
		}

		return {cnt, placeScore, placedPower, hashMemo};
	}

	PlaceInfo challengePlacement(int baseLength) {
		placedPower = vvi(L, vi(L, -1));
		hashMemo.clear();
		auto candidate = getIndicesCandidates(baseLength);
		debug("challenge :", baseLength, sz(candidate));

		bool ok=true;
		rep(tgt, N){
			bool placed = false;
			rep(j, sz(candidate)) {
				if(isPlaceableHash(tgt, candidate[j])) {
					hashMemo[hashize(candidate[j])] = tgt;
					placed = true;
					// delete candidate[j];
					candidate.erase(candidate.begin()+j);
					break;
				}
			}
			if(!placed) {
				ok=false;
				break;
			}
		}
		debug("  ->", ok);

		judge.smooth();
		ll placementScore = 0;
		rep(i,L)rep(j,L){
			ll cur = placedPower[i][j];
			ll below = placedPower[(i+L-1)%L][j];
			ll right = placedPower[i][(j+L-1)%L];
			placementScore += (cur-below)*(cur-below) + (cur-right)*(cur-right);
		}

		return {baseLength, ok ? placementScore : LINF, placedPower, hashMemo};
	}

	int hashSize = 1;
	void thinkBestPlacement() {
		auto [initLength, bestScore, bestPlacedPower, bestHashMemo] = randomPlacement();
		hashSize = initLength;
		
		rep(30) rep(baseLength, 1, 15) {
			auto [_, score, placedPower, hashMemo] = challengePlacement(baseLength);
			if(chmin(bestScore, score)) {
				hashSize = baseLength;
				bestScore = score;
				bestPlacedPower = placedPower;
				bestHashMemo = hashMemo;
			}
			if(score != LINF) break;
		}

		placedPower = bestPlacedPower;
		hashMemo = bestHashMemo;
		doorHashMemo.resize(N, 0);
		for(auto&[h, i]:hashMemo) {
			doorHashMemo[i] = h;
		}

		judge.placement();
	}

	/**
	 * 入口を指定して、対応する出口のハッシュを返す
	 */
	pair<int, vi> predict(int holeIndex, bool isMeasure) {
		const auto diff = getDiffs();
		
		vi indices;
		rep(i, hashSize) {
			const auto [dy, dx] = diff[i];
			const auto val = judge.measurement(holeIndex, dy, dx, isMeasure);
			const auto h = val-(val/D)*D < (val/D)*D+D-val ? val/D : val/D+1;
			indices.push_back(clamp(h, 0, SP-1));
		}
		if (hashMemo.count(hashize(indices))) {
			return {hashMemo[hashize(indices)], indices};
		}
		return {-1, indices};
	}

	tuple<bool, bool, vi> predictAll(bool isMeasure) {
		vi ans(N);
		bool isAllocated = true;
		vi undef;
		set<int> allocatedHole;
		rep(i,N) {
			ans[i] = predict(i, isMeasure).first;
			if(ans[i]==-1) {
				isAllocated = false;
				undef.push_back(i);
			} else {
				allocatedHole.insert(i);
			}
		}
		// is unique?
		isAllocated &= sz(set<int>(all(ans))) == sz(ans);

		// undefな要素に対し、近い物で重複が無いように割り振る
		for(auto i:undef) {
			auto [_, indices] = predict(i, false); // isMeasureにして重点的に見てもいいかも
			int minDiff = INF, minIndex = -1;
			rep(j,N) if(!allocatedHole.count(j) or true) {
				auto holeIndices = dehashize(doorHashMemo[j]);
				int diff = 0;
				rep(k, hashSize) {
					diff += abs(indices[k] - holeIndices[k]);
				}

				if(diff < minDiff) {
					minDiff = diff;
					minIndex = j;
				}
			}
			ans[i] = minIndex;
			allocatedHole.insert(minIndex);
		}

		bool isFinished = isAllocated | judge.isEmergency;

		return {isAllocated, isFinished, ans};
	}

	void answer() {
		auto [isAllocated, _, ans] = predictAll(false);
		out(-1, -1, -1);
		rep(i,N){
			out(ans[i]);
		}
	}

};

int main() {
	judge.initialize();

	debug(P);
	Solver solver;

	solver.thinkBestPlacement();

	int sameAns = 0; vi prevAns;
	do {
		auto [_, isFinished, ans] = solver.predictAll(true);
		if(prevAns == ans) sameAns++;
		else {
			sameAns = 0;
			prevAns = ans;
		}
		if (isFinished or sameAns >= 3) break;
	} while(true);
	solver.answer();
}