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

struct Judge {
	#ifdef _DEBUG // ローカル
	vi correspond;
	#endif

	void initialize() {
		in(L,N,S);
		rep(N){
			def(int,y,x);
			P.push_back(y*L+x);
		}

	#ifdef _DEBUG // ローカル
		correspond.resize(N);
		in(correspond);
	#endif
	}
} judge;

vector<pair<int,int>> getDiffs(){
	static	vector<pair<int,int>> diff;
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
	vi power;
	vi powerOrder;
	vector<vector<tuple<int,int,int>>> history;

	Solver() {
		power.resize(L*L, 0);
		powerOrder.resize(N);
		history.resize(N);
	}

	void place() {
		decidePlace();
		vi tmp(L);
		rep(i,L){
			rep(j,L) tmp[j] = power[i*L+j];
			out(tmp);
		}
	}

	int require=0;
	map<ll,int> townHash; vi hashValues;
	void decidePlace() {
		const int basePower = min(S*2,1000);
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
							v= v*2+value[(i+diff[k].first+L)%L][(j+diff[k].second+L)%L];
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
					ll cur = value[i][j] * basePower;
					ll below = value[(i+L-1)%L][j] * basePower;
					ll right = value[i][(j+L-1)%L] * basePower;
					placementScore += (cur-below)*(cur-below) + (cur-right)*(cur-right);
				}
				return make_tuple(ok, placementScore);
			};

			vvi initValue(L, vi(L));
			rep(i,L) rep(j,L) {
				// initValue[i][j] = Random(0,3) ? 0 : 1;
				initValue[i][j] = Random(0,2);
			}

			auto [cnt, pScore] = getFieldRec(initValue);
			rep(30000){
				auto value = initValue;
				int i = Random(0,L), j = Random(0,L), r = Random(0, 2);
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

			return make_pair(cnt, initValue);
		};

		// 各タウンについて、ハッシュ値とpowerを計算する
		auto [cnt, value] = getField();
		require = cnt;
		rep(i,L)rep(j,L) power[i*L+j] = value[i][j]*basePower;
		townHash.clear();
		hashValues.clear();
		rep(t,N){
			auto[i,j]=towns[t];
			ll v=0;
			rep(k,require){
				v= v*2+value[(i+diff[k].first+L)%L][(j+diff[k].second+L)%L];
			}
			townHash[v]=t;
			hashValues.push_back(v);
		}
		debug("Require Hash Length: ", require);

		smooth();
	}

	void smooth() {
		// ハッシュ値調査で使用されないセルに、配置コストが最小になるような数値を埋める
		const auto diff=getDiffs();
		set<int> town;
		for(auto p:P){
			int i=p/L, j=p%L;
			rep(k,require){
				town.insert(((i+diff[k].first+L)%L)*L+((j+diff[k].second+L)%L));
			}
		}


		vvi score(L,vi(L, 0));
		int dy[] = {0,1,0,-1}, dx[] = {1,0,-1,0};

		rep(i,L)rep(j,L) {
			int adjacent = 0;
			// torus
			rep(k,4) {
				int y = (i+dy[k]+L)%L, x = (j+dx[k]+L)%L;
				adjacent += (power[i*L+j] - power[y*L+x]) * (power[i*L+j] - power[y*L+x]);
			}
			score[i][j] = adjacent;
		}

		// 山登り
		rep(100)rep(i,L)rep(j,L){
			if(town.count(i*L+j)) continue;
			int tgtValue=0;
			rep(k,4) {
				int y = (i+dy[k]+L)%L, x = (j+dx[k]+L)%L;
				tgtValue += power[y*L+x];
			}
			tgtValue /= 4;
			clamp(tgtValue, 0, 1000);

			int adjacent = 0;
			rep(k,4) {
				int y = (i+dy[k]+L)%L, x = (j+dx[k]+L)%L;
				adjacent += (tgtValue - power[y*L+x]) * (tgtValue - power[y*L+x]);
			}
			if(adjacent < score[i][j]) {
				power[i*L+j] = tgtValue;
				score[i][j] = adjacent;

				// update adjacent score
				rep(k,4) {
					int y = (i+dy[k]+L)%L, x = (j+dx[k]+L)%L;
					score[y][x] = 0;
					rep(l,4) {
						int yy = (y+dy[l]+L)%L, xx = (x+dx[l]+L)%L;
						score[y][x] += (power[y*L+x] - power[yy*L+xx]) * (power[y*L+x] - power[yy*L+xx]);
					}
				}
			}
		}
		// rep(i,L)rep(j,L) {
		// 	power[i*L+j] = (i+j)%4;
		// 	power[i*L+j] = min(power[i*L+j], 4-power[i*L+j]);
		// 	power[i*L+j] *= 500;
		// }
	}
	
	int _mCnt=0;
	vi _mRnd;
	HashMap<tuple<int,int,int>,int> _memoSum, _memoCnt;
	int measurement(int index, int dy = 0, int dx = 0) {
		out(index, dy, dx);
		int r;
		#ifdef _DEBUG
		if(_mCnt<10000){
			_mCnt++;
			cin>>r;
			_mRnd.push_back(r);
		}else{
			_mCnt++;
			r=_mRnd[_mCnt%10000];
		}
		int tgt = P[judge.correspond[index]];
		int y = tgt / L, x = tgt % L;
		y = (y + dy + L) % L;
		x = (x + dx + L) % L;
		tgt = y * L + x;
		r = max(0, min(1000, power[tgt] + r));
		#else
		cin>>r;
		#endif
		history[index].emplace_back(dy, dx, r);
		_memoCnt[make_tuple(index, dy, dx)]++;
		_memoSum[make_tuple(index, dy, dx)] += r;
		return _memoSum[make_tuple(index, dy, dx)] / _memoCnt[make_tuple(index, dy, dx)];
	}

	vector<int> predict() {
		vi ans(N,-1);
		const auto diff=getDiffs();
		auto remainHash = townHash;

		HashMap<int,ll> undef;
		rep(i,N){ // ワームホールiについて
			// iに対応する出口のハッシュを計算
			ll v=0;
			rep(j,require){
				float sum = 0;
				auto r=measurement(i, diff[j].first, diff[j].second);
				sum += r;
				v = v*2+(sum>=min(S*2,1000)/2 ? 1 : 0);
			}

			// ハッシュに完全一致する出口があればそれを採用
			if(remainHash.find(v) != remainHash.end()) {
				ans[i] = remainHash[v];
				remainHash.erase(v);
			} else undef[i] = v;
		}

		// 決まらなかったもの全てについて、
		for(auto&[i,v]:undef){
			int minPopcnt = 1000; ll h = 0;
			// 全ての出口のハッシュと比較して、差が一番少ないものを採用
			for(auto&[th, j]:remainHash){
				int popcnt = __builtin_popcountll(v ^ th);
				if(chmin(minPopcnt, popcnt)) h = th;
			}
			ans[i] = remainHash[h];
			remainHash.erase(h);
		}
		return ans;
	}

	vi prevPredict;
	int sameCnt = 0, challenge=0;
	void answer() {
		vi ans;
		while(true){
			challenge++;
			if(challenge > 10000/require/N) break;
			ans = predict();
			if(ans == prevPredict) {
				sameCnt++;
			} else {
				sameCnt = 0;
			}
			if(sameCnt == 3) break;
			prevPredict = ans;
		}

		out(-1, -1, -1);
		rep(i,N){
			out(ans[i]);
			#ifdef _DEBUG
			if(ans[i] != judge.correspond[i]) {
				debug("Hole", i, ":", ans[i], "(", judge.correspond[i], ")");
			}
			#endif
		}

	}
};

int main() {
	judge.initialize();

	debug(P);
	Solver solver;
	solver.place();

	solver.answer();
}