// cargo run --release --bin tester ../../../a.exe < in/0008.txt > out/0008.txt

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
#define __RANGE(i,a,n) for(ll i=((ll)a);i<((ll)n);++i)
#define __RREP(i,n) __RRANGE(i,0,n)
#define __RRANGE(i,a,n) for(ll i=((ll)(n)-1);i>=((ll)a);--i)
#define sz(a) ((ll)(a).size())

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
template<class T>constexpr bool chmax(T&a,T b){return a<b?a=b,1:0;}
template<class T>constexpr bool chmin(T&a,T b){return a>b?a=b,1:0;}
template<class S>S sum(vector<S>&a){return accumulate(all(a),S());}
template<class S>S max(vector<S>&a){return *max_element(all(a));}
template<class S>S min(vector<S>&a){return *min_element(all(a));}

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
		ios_base::sync_with_stdio(0); cin.tie(0);
		cout<<fixed<<setprecision(11);
		cerr<<fixed<<setprecision(3);
	}
	~Mgr(){
		// debug_f(timer.get(), "ms")<<flush;
	}
} _manager;
// 標準偏差
const ll QUERY = 1000, R=1000000000, D=1000000, N=50;
const ld distScale=1/1.26, stddev_multiple=3.5;;
const ll init_dist = R*2;
ld stddev;

ll found = 0;
vector<tuple<ll,ll,ld>> dousing, dousingAll;
ll dist = init_dist, cy = 0, cx = 0; ld cr=0;

// rad2つが大体同じ方向かどうか
bool isSameVector(ld r1, ld r2){
	auto diff= abs(r2-r1);
	if(diff>2*PI) diff-=2*PI;
	if(diff>2*PI) diff-=2*PI;
	return diff < stddev*stddev_multiple or diff >2*PI - stddev*stddev_multiple;
}

int startCount = 0;
void onFound(ll x, ll y, bool isForce = false){
	// ここでダウジング結果を更新する
	vector<pair<ld, tuple<ll,ll,ld>>> dousing2;
	for(auto [cx,cy,cr]: dousing){
		auto r = atan2(y-cy, x-cx);
		if(!isSameVector(r, cr) or isForce) {
			ld ok = 0, ng = 2*R+1;
			while(ng-ok>0.1){
				ld mid = (ok+ng)/2;
				ld nx = cx + mid*cos(cr), ny = cy + mid*sin(cr);
				if(nx*nx+ny*ny > R*R) ng = mid;
				else ok = mid;
			}
			dousing2.emplace_back(ok, make_tuple(cx,cy,cr));
		}
	}

	startCount = dousing2.size();

	dousing.clear();
	if(dousing2.empty()){
		dist = init_dist;
		return;
	}

	sort(rall(dousing2));
	for(auto [d, t]: dousing2){
		auto [cx,cy,cr] = t;
		cout<<"# "<<cx<<' '<<cy<<" "<<cr<<" "<<d<<endl;
		cout<<"#c "<<cx<<' '<<cy<<" "<<" 255 0 0"<<endl;
		dousing.emplace_back(t);
	}
	dist=dousing2.back().first/2;
}

pair<ll,ll> getCrossPoint(ll x1, ll y1, ld r1, ll x2, ll y2, ld r2){
	ld d2 = ((y2-y1) - (x2-x1) * tan(r1)) / (cos(r2) * tan(r1) - sin(r2));
	ld d1 = ((x2-x1) + d2 * cos(r2)) / cos(r1);
	if(d1 < 0 || d2 < 0) return {LINF, LINF};
	return {x2+d2*cos(r2), y2+d2*sin(r2)};
}

// 過去のダウジング結果から特定できそうな物があるか
// 51回ダウジングをしたら、同じ埋蔵品を指しているダウジング対がある
bool onInverse = false;
pair<bool, pair<ll,ll>> analyseHistory(){
	if(dousing.empty()) {
		dist = init_dist;
		return { false, {0,0} };
	}else{
		tie(cx,cy,cr) = dousing.back();
		cout<<"#c "<<cx<<' '<<cy<<" 0 0 255"<<endl;
	}

	bool inv = false; ld dist2=LINF;
	if(sz(dousing) >= 2){
		auto [x2,y2,r2] = dousing[sz(dousing)-1];
		for(auto [x1,y1,r1]: dousing){
			if(x1 == x2 && y1 == y2) continue;
			cout<<"#?"<<x1<<' '<<y1<<" "<<r1<<" "<<r2<<" -> "<<isSameVector(r1, r2+PI)<<endl;
			// if(isSameVector(r1, r2+PI)) {
				ld d = sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
				auto x3 = x2+d*cos(r2), y3 = y2+d*sin(r2);
				auto threshold = d * sin(stddev*stddev_multiple / 2) * 2 + D;
				if(hypot(x3-x1, y3-y1) > threshold) {
					cout<<"#c "<<x1<<' '<<y1<<" 0 255 255"<<endl;
					continue;
				}
				auto x4 = x1+d*cos(r1), y4 = y1+d*sin(r1);
				if(hypot(x4-x2, y4-y2) > threshold) {
					continue;
				}
				inv = true;
				cout<<"#c "<<x1<<' '<<y1<<" 255 0 255"<<endl;
				cout<<"#c "<<x2<<' '<<y2<<" 255 0 255"<<endl;
				chmin(dist2, d);
				cout<<"# inverse! "<<dist2<<endl;
			// }
		}
	}
	if(inv) {
		if(!onInverse){
			dist = dist2;
		}
		onInverse = true;
		dist *= 0.5;
	}else{
		dist *= distScale;
	}

	if(dist<D*1){
		while(true) {
			if(sz(dousing) > startCount) dousing.pop_back();
			else break;
		}
		if(!dousing.empty()) dousing.pop_back();
		onFound(0, 0, true);
		onInverse = false;
		return analyseHistory();
	}

	ll ny = cy + sin(cr)*dist, nx = cx + cos(cr)*dist;
	cout<<"#! "<<nx<<' '<<ny<<" "<<nx*nx+ny*ny<<endl;
	if(nx*nx+ny*ny > R*R) {
		ld ok = 0, ng = 2*R;
		while(abs(ok-ng) > 1e-6){
			ld mid = (ok+ng)/2;
			ll ny = cy + sin(cr)*mid, nx = cx + cos(cr)*mid;
			if(nx*nx+ny*ny > R*R) ng = mid;
			else ok = mid;
		}
		dist = ok / 2;
		ny = cy + sin(cr)*dist, nx = cx + cos(cr)*dist;
	}

	return {true,{nx, ny}};
}

bool query(ll cnt) {
	onInverse = false;

	auto [detected, point] = analyseHistory();
	if(!detected) {
		point = {0, 0};
		dist = init_dist;
	}
	cout<<point.first<<' '<<point.second<<endl<<flush;

	ll result; cin>>result;
	if(result == 0){// not found
		ld vec; cin>>vec;
		dousing.emplace_back(point.first, point.second, vec);
		dousingAll.emplace_back(point.first, point.second, vec);
		return false;
	}
	found++;
	cin>>point;
	onFound(point.first, point.second);
	return result == 2;
}

int main() {
	cin>>stddev;

	rep(i,QUERY){
		bool finished = query(i);
		if(finished) break;
	}

	return 0;
}