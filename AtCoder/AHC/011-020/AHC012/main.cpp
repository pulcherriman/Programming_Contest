#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("inline")

#pragma GCC diagnostic ignored "-Wunused-value"
#ifdef _DEBUG
// #define _GLIBCXX_DEBUG 1
#endif
int _TEMPORARY_DEBUG = 1;


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
template<class V> using minpq = priority_queue<V, vector<V>, greater<V>>;
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
#define sz(a) ((int)(a).size())

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
		if(_TEMPORARY_DEBUG) return pargs(cerr, args...)<<'\n';
		else return cerr;
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
	constexpr result_type operator()(){return operator()((ll)min(),(ll)max());}
	static constexpr result_type max(){return numeric_limits<result_type>::max();}
	static constexpr result_type min(){return 0;}
	constexpr Random(const bool&isDeterministic):y(isDeterministic?2463534242ll:chrono::system_clock::now().time_since_epoch().count()){}
	constexpr int operator()(int a,int b){return next()%(b-a)+a;}
	constexpr ll operator()(ll a,ll b){return (((ull)next())<<32|next())%(b-a)+a;}
	constexpr double operator()(double a,double b){return (b-a)*next()/4294967296.0+a;}
	result_type getSeed(){return y;}
	void setSeed(result_type seed){y=seed;}
private:
	result_type y;
	constexpr result_type next(){return y^=(y^=(y^=y<<13)>>17)<<5;}
}
#ifdef _DEBUG
Random(1);
#else
Random(1);
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
	static const int TLE = 3000;
	static inline Timer timer = Timer(TLE-20);
	Mgr() {
		ios_base::sync_with_stdio(0); cin.tie(0);
		cout<<fixed<<setprecision(11);
		cerr<<fixed<<setprecision(3);
	}
	~Mgr(){
		debug_f(timer.get(), "ms")<<flush;
	}
} _manager;


template<class T>class Compress{
	int _size;
	HashMap<T,int> _zip;
	vector<int> _unzip;
public:
	Compress(){}
	void init(vector<T> in){
		sort(all(in));
		in.erase(unique(all(in)),in.end());
		_unzip.resize(_size=in.size());
		rep(i,_size){_unzip[_zip[in[i]] = i] = in[i];}
	}
	int size(){return _size;}
	int zip(T v){return _zip[v];}
	T unzip(int v){return _unzip[v];}
};

int n=0, piece=0;
const int k=100;
const int t=10;
using Info = array<int, t>;
Info year;
Compress<int> compressY, compressX;
// イチゴ
vector<pii> strawberry, berry;
vvi field;

// 端は-1
int ichigoCount(int y1, int y2, int x1, int x2){
	int ret = field[y2][x2];
	if(y1!=-1) ret -= field[y1][x2];
	if(x1!=-1) ret -= field[y2][x1];
	if(y1!=-1 && x1!=-1) ret += field[y1][x1];
	return ret;
}

/**
 * @brief 解く
 * スコア
 *   10^6 * (配れたピースの個数) → 個数のみ、イチゴの多寡は問わない
 * 基本方針
 * 1. 水平線を決め打つ
 * 2. 垂直線をDPで求める
 * 
 * データ
 *   x+0.5で切ること → xと表現
 */

pair<int, vi> calcVertical(vi&horizontal){
	int score=0;
	vi vertical;
	auto remain = year;
	int lastCut=-1;

	/**
	 * @return { 何ピース成立するか, いくつのイチゴが無駄になるか}
	 */
	const auto checkVertical = [&](int i){
		bool onlyOver10 = true;
		int enablePiece=0, mudaIchigo=0;
		Info rem = remain;
		rep(j, horizontal.size()+1){
			int l = j==0 ? -1 : horizontal[j-1];
			int r = j==sz(horizontal) ? compressY.size()-1 : horizontal[j];
			int cnt =  ichigoCount(l,r,lastCut,i);
			if(cnt<=t)onlyOver10=false;
			if(cnt>0 and cnt<=t and rem[cnt-1]>0){
				enablePiece++;
				rem[cnt-1]--;
			}else{
				mudaIchigo+=cnt;
			}
		}
		return make_pair(onlyOver10 ? -1 : enablePiece, -mudaIchigo);
	};

	const auto cutVertical = [&](int i){
		rep(j, horizontal.size()+1){
			int l = j==0 ? -1 : horizontal[j-1];
			int r = j==sz(horizontal) ? compressY.size()-1 : horizontal[j];
			int cnt =  ichigoCount(l,r,lastCut,i);
			if(cnt>0 and cnt<=t and remain[cnt-1]>0){
				score++;
				remain[cnt-1]--;
			}
		}
		vertical.emplace_back(i);
		lastCut=i;
	};

	rep(100){
		pii bestValue={1,-INF};
		int bestIndex=-1;
		rep(i,lastCut+1,compressX.size()){
			auto val=checkVertical(i);
			if(val.first==-1)break;
			if(chmax(bestValue, val)){
				bestIndex=i;
			}
		}
		if(bestIndex==-1) break;
		cutVertical(bestIndex);
	}

	return {score, vertical};
}

int calcScore(vi&horizontal, vi&vertical){
	int score=0, lastCut=-1;
	Info remain=year;
	for(auto&i:vertical){
		rep(j, horizontal.size()+1){
			int l = j==0 ? -1 : horizontal[j-1];
			int r = j==sz(horizontal) ? compressY.size()-1 : horizontal[j];
			int cnt =  ichigoCount(l,r,lastCut,i);
			if(cnt>0 and cnt<=t and remain[cnt-1]>0){
				score++;
				remain[cnt-1]--;
			}
		}
		lastCut=i;
	};
	return score;
}

pair<vi,vi> solve(){
	const int BEAM_WIDTH = 30;
	int challengeCount=0;
	int maxScore=0;
	vi maxHorizontal, maxVertical;
	vector<tuple<int, vi, vi>> kouho;
	rep(100){
		vi horizontal;
		int edgeCnt=Random(5,10);
		int width = compressY.size() / (edgeCnt+1);
		rep(i,edgeCnt){
			horizontal.emplace_back(width * (i+1) + Random(-width/3, width/3));
		}

		auto [score, vertical] = calcVertical(horizontal);
		kouho.emplace_back(score, horizontal, vertical);
	}
	sort(all(kouho), [](const auto&a, const auto&b){
		return get<0>(a)>get<0>(b);
	});
	kouho.erase(kouho.begin()+BEAM_WIDTH, kouho.end());
	for(auto&[score, horizontal, vertical]:kouho){
		debug(score);
	}


	int currentScore=0;
	vi vertical, horizontal;
	const int typeSp=10;
	vi typeCount(typeSp,0);
	while(Mgr::timer){
		rep(1){
			int kouhoSize=kouho.size();
			rep(i,kouhoSize)rep(type,typeSp){
				tie(currentScore, horizontal, vertical) = kouho[i];
				challengeCount++;
				// int type=Random(0,typeSp);
				if(type==0){
					int target=Random(0, horizontal.size());
					horizontal[target] = Random(0,compressY.size());
					sort(all(horizontal));
					horizontal.erase(unique(all(horizontal)), horizontal.end());
				}else if(type==1){
					int target=Random(0, vertical.size());
					vertical[target] = Random(0,compressX.size());
					sort(all(vertical));
					vertical.erase(unique(all(vertical)), vertical.end());
				}else if(type==2){
					int target=Random(0, horizontal.size());
					horizontal.erase(horizontal.begin()+target);
				}else if(type==3){
					int target=Random(0, vertical.size());
					vertical.erase(vertical.begin()+target);
				}else if(type==4){
					if(horizontal.size()+vertical.size()==100)continue;
					horizontal.emplace_back(Random(0,compressY.size()));
					sort(all(horizontal));
					horizontal.erase(unique(all(horizontal)), horizontal.end());
				}else if(type==5){
					if(horizontal.size()+vertical.size()==100)continue;
					vertical.emplace_back(Random(0,compressX.size()));
					sort(all(vertical));
					vertical.erase(unique(all(vertical)), vertical.end());
				}else if(type==6){
					int target=Random(0, vertical.size());
					if(vertical[target]==compressX.size()-1)continue;
					vertical[target]++;
					vertical.erase(unique(all(vertical)), vertical.end());
				}else if(type==7){
					int target=Random(0, vertical.size());
					if(vertical[target]==0)continue;
					vertical[target] --;
					vertical.erase(unique(all(vertical)), vertical.end());
				}else if(type==8){
					int target=Random(0, horizontal.size());
					if(horizontal[target]==compressY.size()-1)continue;
					horizontal[target] ++;
					horizontal.erase(unique(all(horizontal)), horizontal.end());
				}else if(type==9){
					int target=Random(0, horizontal.size());
					if(horizontal[target]==0)continue;
					horizontal[target]--;
					horizontal.erase(unique(all(horizontal)), horizontal.end());
				}
				if(horizontal.size()+vertical.size()>k)continue;

				int score=calcScore(horizontal, vertical);
				if(currentScore <= score){
					typeCount[type]++;
					kouho.emplace_back(score, horizontal, vertical);
				}
			}
		}
		sort(all(kouho), [](const auto&a, const auto&b){
			return get<0>(a)>get<0>(b);
		});
		kouho.erase(kouho.begin()+BEAM_WIDTH, kouho.end());

		#ifdef _DEBUG
		if(chmax(maxScore, get<0>(kouho.front()))){
			debug("!!",maxScore,":",Mgr::timer.get(),"ms");
		}
		#endif
	}

	#ifdef _DEBUG
	debug(typeCount);
	for(auto [score, horizontal, vertical]:kouho){
		cerr<<score<<",";
	}
	cerr<<endl;
	#endif

	tie(maxScore, maxHorizontal, maxVertical) = kouho.front();

	debug_f("challengeCount:", challengeCount);
	debug_f("Acceptance:",maxScore);
	debug_f("Score:", (int)round(1e6*maxScore/piece));
	debug("Horizontal:",maxHorizontal);
	debug("Vertical: ", maxVertical);

	return {maxHorizontal, maxVertical};
}


int main() {
	{
		int _;
		cin>>n>>_;
		cin>>year;
		strawberry.resize(n);
		cin>>strawberry;

		vi y(n),x(n);
		rep(i,n){
			swap(strawberry[i].first,strawberry[i].second);
			y[i] = strawberry[i].first;
			x[i] = strawberry[i].second;
		}
		compressY.init(y);
		compressX.init(x);
		berry.resize(n);
		field.resize(compressY.size(), vi(compressX.size(), 0));
		rep(i,n){
			berry[i] = {compressY.zip(y[i]), compressX.zip(x[i])};
			field[berry[i].first][berry[i].second]++;
		}
		rep(i,compressY.size()){
			rep(j,compressX.size()-1){
				field[i][j+1] += field[i][j];
			}
		}
		rep(i,compressX.size()){
			rep(j,compressY.size()-1){
				field[j+1][i] += field[j][i];
			}
		}

		rep(i,t)piece += year[i];

	}
	debug_f("target :", year);
	debug_f("piece count :", piece);

	auto [horizontal, vertical] = solve();

	const int FAR = 1000000000;
	out(horizontal.size() + vertical.size());
	for(auto&cy:horizontal){
		int y=compressY.unzip(cy);
		out(-FAR, y, FAR, y+1);
	}
	for(auto&cx:vertical){
		int x=compressX.unzip(cx);
		out(x, -FAR, x+1, FAR);
	}
}
