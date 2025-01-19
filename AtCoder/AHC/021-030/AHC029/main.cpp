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

int CardCnt, ProjectCnt, AddCardCnt, money=0; const int TURN = 1000;

struct __Input {
	#ifdef _DEBUG
	vector<pair<int,int>> initialProject, additionalProject, initialCard;
	vector<vector<tuple<int,int,int>>> additionalCard;
	#endif
	auto getInitialInput() {
		int _;
		cin>>CardCnt>>ProjectCnt>>AddCardCnt>>_;
		#ifdef _DEBUG
		initialProject.resize(ProjectCnt);
		rep(i,ProjectCnt) cin>>initialProject[i].first>>initialProject[i].second;

		additionalProject.resize(ProjectCnt*TURN);
		rep(i,ProjectCnt*TURN) cin>>additionalProject[i].first>>additionalProject[i].second;

		initialCard.resize(CardCnt);
		rep(i,CardCnt) cin>>initialCard[i].first>>initialCard[i].second;

		additionalCard.resize(TURN);
		rep(i,TURN) {
			additionalCard[i].resize(AddCardCnt);
			rep(j,AddCardCnt) cin>>get<0>(additionalCard[i][j])>>get<1>(additionalCard[i][j])>>get<2>(additionalCard[i][j]);
		}
		reverse(all(initialProject));
		reverse(all(additionalProject));
		reverse(all(initialCard));
		#endif
	}

	auto getInitialProject() {
		#ifdef _DEBUG
		auto val = initialProject.back();
		initialProject.pop_back();
		return val;
		#else
		int c,v; cin>>c>>v;
		return make_pair(c,v);
		#endif
	}

	auto getAdditionalProject(int useExCnt) {
		#ifdef _DEBUG
		auto val = additionalProject.back();
		additionalProject.pop_back();
		val.first *= (1<<useExCnt);
		val.second *= (1<<useExCnt);
		return val;
		#else
		int c,v; cin>>c>>v;
		return make_pair(c,v);
		#endif
	}

	auto getInitialCard() {
		#ifdef _DEBUG
		auto val = initialCard.back();
		initialCard.pop_back();
		return val;
		#else
		int t,w; cin>>t>>w;
		return make_pair(t,w);
		#endif
	}

	auto getAdditionalCard(int turn, int useExCnt) {
		#ifdef _DEBUG
		auto cards = additionalCard[turn];
		rep(i,AddCardCnt) {
			get<1>(cards[i]) *= (1<<useExCnt);
			get<2>(cards[i]) *= (1<<useExCnt);
		}
		return cards;
		#else
		vector<tuple<int,int,int>> val(AddCardCnt);
		rep(i,AddCardCnt) cin>>get<0>(val[i])>>get<1>(val[i])>>get<2>(val[i]);
		return val;
		#endif
	}

} Input;


enum CardType: int {
	Single = 0, Full = 1, Change = 2, Reload = 3, Ex = 4
};
struct Cards {
	vector<pair<int,int>> info;
	vi single, full;
	int change=0, reload=0, ex=0;
	Cards(int _cnt): info(_cnt) {}
	
	void addCard(int idx, int t, int w) {
		switch(t){
			case CardType::Single: single.pb(w); break;
			case CardType::Full: full.pb(w); break;
			case CardType::Change: change++; break;
			case CardType::Reload: reload++; break;
			case CardType::Ex: ex++; break;
		}
		info[idx] = {t,w};
	}

	int decideUseCard(int t, int w=0) {
		int idx;
		switch(t) {
			case CardType::Single: {
				idx = find_if(all(info), [&](auto&v){return v.first==0 and v.second==w;}) - begin(info);
				break;
			}
			case CardType::Full: {
				idx = find_if(all(info), [&](auto&v){return v.first==1 and v.second==w;}) - begin(info);
				break;
			}
			case CardType::Change: {
				idx = find_if(all(info), [&](auto&v){return v.first==2;}) - begin(info);
				break;
			}
			case CardType::Reload: {
				idx = find_if(all(info), [&](auto&v){return v.first==3;}) - begin(info);
				break;
			}
			case CardType::Ex: {
				idx = find_if(all(info), [&](auto&v){return v.first==4;}) - begin(info);
				break;
			}
		}

		return idx;
	}

	void deleteCard(int idx) {
		auto [t,w] = info[idx];
		switch(t) {
			case CardType::Single: {
				auto itr = find(all(single), w);
				single.erase(itr);
				break;
			}
			case CardType::Full: {
				auto itr = find(all(full), w);
				full.erase(itr);
				break;
			}
			case CardType::Change: {
				change--;
				break;
			}
			case CardType::Reload: {
				reload--;
				break;
			}
			case CardType::Ex: {
				ex--;
				break;
			}
		}
	}
};

struct Project {
	int cost, value;
	Project() {}
	Project(int _cost, int _value): cost(_cost), value(_value) {}
};
struct Projects : public vector<Project> {
	vi liveCnt;
	Projects(int _cnt): vector<Project>(_cnt), liveCnt(_cnt, 0) {}	
};


struct Plan {
	Cards cards;
	Projects projects;
	int money=0, turn=0, useExCnt=0;
	vector<pair<int,int>> actions;
	Plan(Cards _cards, Projects _projects): cards(_cards), projects(_projects) {}

	
	pair<int,int> DecideUseCardAction() {
		// 残costを0にできるなら、できる限り少ないパワーの労働が良い
		// fullは、1:ロスが発生しないときに使うのがいい 2:多くのPJを終了させられるときに使うのがいい
		// changeは、コスパが悪いPJに使うのがいい
		// reloadは、手持ちのPJの多くが悪くなった時に使うのがいい
		// exは、1:獲得したら即座に使うのがいい 2:他なんかあるか？戦略を決定づける大事な要素なのでよく考える

		int idx=0, tgt=0;
		if(cards.ex and useExCnt < 20 and turn < 900) {
			idx = cards.decideUseCard(CardType::Ex);
		// }else if(auto minLiveCnt = min(projects.liveCnt); cards.reload and minLiveCnt >= 5) {
		// 	idx = cards.decideUseCard(CardType::Reload);
		// }else if(auto maxLiveItr = max_element(all(projects.liveCnt)); cards.change and *maxLiveItr >= 10) {
		// 	idx = cards.decideUseCard(CardType::Change);
		// 	tgt = maxLiveItr - begin(projects.liveCnt);
		// }else if(auto minPjItr=min_element(all(projects), [](auto&a, auto&b){return a.cost<b.cost;}); cards.reload and (*minPjItr).cost >= 20*(1<<useExCnt)) {
		// 	idx = cards.decideUseCard(CardType::Reload);
		// }else if(auto maxPjItr=max_element(all(projects), [](auto&a, auto&b){return a.cost<b.cost;}); cards.change and (*maxPjItr).cost >= 30*(1<<useExCnt)) {
		// 	idx = cards.decideUseCard(CardType::Change);
		// 	tgt = maxPjItr - begin(projects);
		}else if(cards.full.size()) {
			idx = cards.decideUseCard(CardType::Full, max(cards.full));
		}else if(cards.single.size()) {
			int maxPerf=-1;
			rep(i,CardCnt) if(cards.info[i].first==CardType::Single) {
				rep(j,ProjectCnt) {
					int cardPower = cards.info[i].second;
					int projectCost = projects[j].cost;
					int projectValue = projects[j].value;
					if(cardPower >= projectCost) {
						int perf = 1000 * projectValue / cardPower;
						if(chmax(maxPerf, perf)) {
							idx = i;
							tgt = j;
						}
					}
				}
			}
			if(maxPerf == -1) {
				idx = cards.decideUseCard(CardType::Single, max(cards.single));
				tgt = max_element(all(projects), [&](auto&l, auto&r){
					return l.cost*r.value > r.cost*l.value;
				}) - begin(projects);
			}
		}
		return {idx, tgt};
	}

	void useCardAction(int idx, int tgt) {
		auto [t,w] = cards.info[idx];
		cards.deleteCard(idx);
		#ifdef _DEBUG
		switch(t) {
			case CardType::Single: {
				if((projects[tgt].cost -= w) <= 0) {
					money += projects[tgt].value;
					auto [c,v] = Input.getAdditionalProject(useExCnt);
					projects[tgt].cost = c;
					projects[tgt].value = v;
					projects.liveCnt[tgt] = 0;
				}
				rep(i,ProjectCnt) {
					projects.liveCnt[i]++;
				}
				break;
			}
			case CardType::Full: {
				rep(i,ProjectCnt) {
					if((projects[i].cost -= w) <= 0) {
						money += projects[i].value;
						auto [c,v] = Input.getAdditionalProject(useExCnt);
						projects[i].cost = c;
						projects[i].value = v;
						projects.liveCnt[i] = 0;
					}
					projects.liveCnt[i]++;
				}
				break;
			}
			case CardType::Change: {
				auto [c,v] = Input.getAdditionalProject(useExCnt);
				projects[tgt].cost = c;
				projects[tgt].value = v;
				projects.liveCnt[tgt] = 1;
				break;
			}
			case CardType::Reload: {
				rep(i,ProjectCnt) {
					auto [c,v] = Input.getAdditionalProject(useExCnt);
					projects[i].cost = c;
					projects[i].value = v;
					projects.liveCnt[i] = 1;
				}
				break;
			}
			case CardType::Ex: {
				useExCnt++;
				break;
			}
		}
		#else
		rep(i,ProjectCnt){
			auto [c,v] = Input.getAdditionalProject(useExCnt);
			projects[i].cost = c;
			projects[i].value = v;
		}
		cin>>money;
		#endif
	}

	auto DecideGetCardAction() {
		auto cand = Input.getAdditionalCard(turn, useExCnt);
		// out("#", "== cand == ");

		vector<tuple<int,int,int,int>> availableCand;
		rep(i,AddCardCnt) {
			auto [t,w,p] = cand[i];
			// out("#", i,t,w,p);
			if(p > money) continue;
			availableCand.eb(i,t,w,p);
		}
		const auto evaluate = [&](int i, int t, int w, int p) -> int {
			if(turn >= 800) return -p;
			if(t==CardType::Ex and useExCnt+cards.ex < 20) return 1000000000;
			if(t==CardType::Ex) return -1000000000;
			// if(int minPjCost=(*min_element(all(projects), [](auto&a, auto&b){return a.cost<b.cost;})).cost ; t==CardType::Reload and minPjCost >= 20 * (1<<useExCnt)) return minPjCost * 1000 / (p+1);
			// if(int maxPjCost=(*max_element(all(projects), [](auto&a, auto&b){return a.cost<b.cost;})).cost ; t==CardType::Change and maxPjCost >= 30 * (1<<useExCnt)) return maxPjCost * 1000 / (p+1);
			if(t==CardType::Full) return w * ProjectCnt * 2000  / min(p+1, p/(money/10+1)*(money/10+1)+1);
			if(t==CardType::Single) return w * 1000 / min(p+1, p/(money/12+1)*(money/12+1)+1);
			return 0;
		};
		sort(all(availableCand), [&](auto&l, auto&r){
			auto [i1,t1,w1,p1] = l;
			auto [i2,t2,w2,p2] = r;
			return evaluate(i1,t1,w1,p1) > evaluate(i2,t2,w2,p2);
		});
		auto [i,t,w,p] = availableCand[0];
		return tuple{i,t,w,p};
	}

	void act() {
		actions.pb(DecideUseCardAction());
		auto [idx, tgt] = actions.back();
		cout<<idx<<' '<<tgt<<endl;
		useCardAction(idx, tgt);

		auto [candIdx, tp, wg, pr] = DecideGetCardAction();
		cout<<candIdx<<endl;
		money -= pr;
		cards.addCard(idx, tp, wg);
		turn++;
	}

};

int main() { /**/
	Input.getInitialInput();
	
	Cards cards(CardCnt);
	Projects projects(ProjectCnt);
	rep(i,CardCnt) {
		auto [t,w] = Input.getInitialCard();
		cards.addCard(i,t,w);
	}
	rep(i,ProjectCnt) {
		auto [c,v] = Input.getInitialProject();
		projects[i] = Project(c,v);
	}

	Plan plan(cards, projects);
	
	rep(TURN){
		// out("#", "Turn", plan.turn, "==");
		plan.act();
		// out("#", "== projects ==");
		// rep(i,ProjectCnt){
		// 	out("#", plan.projects[i].cost, plan.projects[i].value);
		// }
		// out("#", "== cards ==");
		// rep(i,CardCnt){
		// 	auto [t,w] = plan.cards.info[i];
		// 	out("#", t,w);
		// }
		// out("#", "== money ==");
		// out("#", plan.money);
		// out("#", "=============")<<flush;
	}
}