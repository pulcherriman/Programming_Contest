/*
 * Unsecured Optimization
 */
#pragma GCC optimize "O3" /* 最適化 */
#pragma GCC target "avx" /* SIMD(ベクトル化) */
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native") /* 浮動小数点数のSIMD */
// #pragma GCC optimize "fast-math"
// #pragma GCC optimize "unroll-loops" /* ループの展開 */
#ifdef _DEBUG
// #define _GLIBCXX_DEBUG 1
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
template<class K> using IndexedSet=__gnu_pbds::tree<K,__gnu_pbds::null_type,less<K>,__gnu_pbds::rb_tree_tag,__gnu_pbds::tree_order_statistics_node_update>;
template<class K> using HashSet=__gnu_pbds::gp_hash_table<K,__gnu_pbds::null_type>;
template<class K,class V> using IndexedMap=__gnu_pbds::tree<K,V,less<K>,__gnu_pbds::rb_tree_tag,__gnu_pbds::tree_order_statistics_node_update>;
template<class K,class V> using HashMap=__gnu_pbds::gp_hash_table<K,V>;

/*
 * Macros
 */
#define all(a) a.begin(),a.end()
#define rall(a) a.rbegin(),a.rend()
#define __LOOPSWITCH(_1, _2, _3, __LOOPSWITCH, ...) __LOOPSWITCH
#define rep(...) __LOOPSWITCH(__VA_ARGS__, __RANGE, __REP, __LOOP) (__VA_ARGS__)
#define rrep(...) __LOOPSWITCH(__VA_ARGS__, __RRANGE, __RREP, __LOOP) (__VA_ARGS__)
#define __LOOP(q) __LOOP2(q, __LINE__)
#define __LOOP2(q,l) __LOOP3(q,l)
#define __LOOP3(q,l) __REP(_lp ## l,q)
#define __REP(i,n) __RANGE(i,0,n)
#define __RANGE(i,a,n) for(ll i=((ll)a);i<((ll)n);++i)
#define __RREP(i,n) __RRANGE(i,0,n)
#define __RRANGE(i,a,n) for(ll i=((ll)n-1);i>=((ll)a);--i)
#define repsq(i,n) for(ll i=0;i*i<=n;++i)
#define each(v,a) for(auto v:a)
#define eachref(v,a) for(auto&v:a)
#define fcout(a) cout<<setprecision(a)<<fixed

/*
 * Constants
 */
constexpr ll LINF=1ll<<60;
constexpr int INF=1<<30;
constexpr double EPS=(1e-14);
constexpr long double PI=3.14159265358979323846;

/*
 * Utilities
 */
template<class T>constexpr bool chmax(T&a,T b){return a<b?a=b,1:0;}
template<class T>constexpr bool chmin(T&a,T b){return a>b?a=b,1:0;}
template<class S>S sum(vector<S>&a){return accumulate(all(a),S());}
template<class S>S max(vector<S>&a){return *max_element(all(a));}
template<class S>S min(vector<S>&a){return *min_element(all(a));}


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
	Timer(uint64_t _limit = 1970): start(getClocks()),limit(start+_limit*ClocksPerMsec) {}
	uint64_t get() const{return (getClocks()-start)/ClocksPerMsec;}
	operator bool()const{return getClocks()<limit;}
};
void wait(const int&msec){Timer tm(msec); while(tm);}

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




struct FoodManager {
	HashMap<string, int> mapper;
	vector<string> inverse;

	FoodManager() = default;
	
	int GetIndex(string s) {
		if (mapper.find(s) != mapper.end()) return mapper[s];
		mapper[s] = inverse.size();
		inverse.push_back(s);
		return mapper[s];
	}

	size_t size() {
		return inverse.size();
	}
};

struct Human {
	vector<int> likes;
	vector<int> dislikes;

	Human() = default;

	vector<int> LackLikes(HashSet<int>& foods) const {
		vector<int> lacks;
		for(auto&food : likes) {
			if(foods.find(food) == foods.end()) lacks.emplace_back(food);
		}
		return lacks;
	}

	bool IsSatisfyDislikes(HashSet<int>& foods) const {
		for(auto&food : dislikes) {
			if(foods.find(food) != foods.end()) return false;
		}
		return true;
	}
};

struct StaticDataStore {
private:
	StaticDataStore() = default;

public:
	static inline int n;

	static inline FoodManager foodMgr;
	static inline vector<Human> humans;

	static void Input() {
		cin>>n;
		humans.resize(n);

		for(auto&human : humans){
			int t; string s;

			cin>>t;
			rep(t) {
				cin>>s;
				human.likes.push_back(foodMgr.GetIndex(s));
			}

			cin>>t;
			rep(t) {
				cin>>s;
				human.dislikes.push_back(foodMgr.GetIndex(s));
			}
		}
	}
};


struct _Construct {
	_Construct(){
		StaticDataStore::Input();
	}
} _construct;

struct Pizza {
	Pizza() = default;

	HashSet<int> useFoods;
};

struct SolverInterface {
	virtual int Solve() = 0;
	virtual void Print() = 0;

protected:
	void Print(Pizza&pizza) {
		cout<<pizza.useFoods.size();
		for(auto&food : pizza.useFoods) {
			cout<<' '<<StaticDataStore::foodMgr.inverse[food];
		}
		cout<<endl;
	}
};

struct GreedySolver : public SolverInterface {
	Pizza pizza;

	int Solve() {
		int score = 0;
		for(auto&human : StaticDataStore::humans){
			if(!human.IsSatisfyDislikes(pizza.useFoods)) continue;
			for(auto&food : human.LackLikes(pizza.useFoods)) {
				pizza.useFoods.insert(food);
			}
			score++;
		}
		return score;
	}

	void Print() {
		SolverInterface::Print(pizza);
	}
};

struct PriorMinimalSolver : public SolverInterface {
	Pizza pizza;
	HashSet<int> dislikeFoods;

	int Solve() {
		int score = 0;
		auto greater = [this](const Human*a, const Human*b){
			if(!b->IsSatisfyDislikes(pizza.useFoods)) return false;
			if(!a->IsSatisfyDislikes(pizza.useFoods)) return true;
			return a->LackLikes(pizza.useFoods).size() > b->LackLikes(pizza.useFoods).size();
		};

		priority_queue<Human*, vector<Human*>, decltype(greater)> q(greater);
		for(auto&human : StaticDataStore::humans) {
			q.push(&human);
		}
		
		while(!q.empty()){
			auto human = *q.top();
			q.pop();

			// 嫌いなアイテムが選ばれているならパス
			if(!human.IsSatisfyDislikes(pizza.useFoods)) continue;
			auto lacks = human.LackLikes(pizza.useFoods);
			bool ok = true;
			for(auto&food : lacks) {
				// 既に選んだ人の嫌いなアイテムを足す必要があるならパス
				if (dislikeFoods.find(food) != dislikeFoods.end()) ok=false;
			}
			if (!ok) continue;


			for(auto&food : lacks) {
				pizza.useFoods.insert(food);
			}
			for(auto&food : human.dislikes) {
				dislikeFoods.insert(food);
			}

			score++;
			// for(auto&food : pizza.useFoods) {
			// 	cerr<< StaticDataStore::foodMgr.inverse[food]<<' ';
			// }
			// cerr<<endl;
			// cerr<<score<<endl;

			make_heap(const_cast<Human**>(&q.top()),
				const_cast<Human**>(&q.top()) + q.size(),
				greater);
		}

		return score;
	}

	void Print() {
		SolverInterface::Print(pizza);
	}
};

int main(){
	Timer timer;

	// SolverInterface* solver = new GreedySolver();
	SolverInterface* solver = new PriorMinimalSolver();

	cerr<<solver->Solve()<<endl;

	solver->Print();

	cerr<<timer.get()<<" ms"<<endl;
}
