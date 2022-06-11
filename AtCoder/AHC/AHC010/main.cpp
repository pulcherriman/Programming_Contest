#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("inline")
#pragma GCC diagnostic ignored "-Wunused-value"
#ifdef _DEBUG
// #define _GLIBCXX_DEBUG 1
#endif

/* 
 * Include Headers
 */
#if defined(EVAL) || defined(ONLINE_JUDGE) || defined(_DEBUG)
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
#define __RRANGE(i,a,n) for(ll i=((ll)n-1);i>=((ll)a);--i)
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
	template<class...Ts> constexpr ostream& debug(Ts...args) { return pargs(cerr, args...)<<'\n'; }
	#else
	#define debug(...) if(false)debug_f(__VA_ARGS__)
	#endif


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
		debug_f(timer.get(), "ms")<<flush;
	}
} _manager;

namespace std::tr1 {
	template<class T>
	struct hash_base {
		const static inline size_t hash_value = 0x9e3779b9;
		static inline size_t hash_rnd = Random(0, numeric_limits<size_t>::max());
		template<class V> static size_t& do_hash(size_t&seed, V&v) {
			return seed ^= hash<V>{}(v) + hash_value + (seed<<6) + (seed>2);
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
}

// ./tester.exe ../../../a.exe < ./tools/in/0001.txt > ./tools/out/0001.txt

/*
 1
0 2
 3
*/

const int dy[] = {0,-1,0,1};
const int dx[] = {-1,0,1,0};
const int dnext[8][4] = {// パネルiに、方向jから入った場合、どの方向に出るか
    {1, 0, -1, -1},
    {3, -1, -1, 0},
    {-1, -1, 3, 2},
    {-1, 2, 1, -1},
    {1, 0, 3, 2},
    {3, 2, 1, 0},
    {2, -1, 0, -1},
    {-1, 3, -1, 1},
};
const int rot_index[] = {1,2,3,0,5,4,7,6};
const int open_dir[] = {0,0,2,1,0,0,0,1};
const int n=30;
using Field = array<array<int,n>,n>;

Field a;
void pfield(Field&b){
	rep(i,n){
		rep(j,n)cerr<<b[i][j];
		cerr<<'\n';
	}
}

int calc(Field&b){
	int sc1=0,sc2=0;
	Field vis;
	fill(vis.front().begin(), vis.back().end(), 0);

	rep(y,n)rep(x,n)if(!vis[y][x]){
		vis[y][x]=1;
		int i=y,j=x, d=open_dir[b[i][j]] ,ln=0;
		while(true) {
			int d2 = dnext[b[i][j]][d];
			if (d2 == -1) break;
			i += dy[d2];
			j += dx[d2];
			if (i < 0 || i >= 30 || j < 0 || j >= 30) break;
			vis[i][j]=1;
			d = (d2 + 2) % 4;
			ln++;
			if (i == y && j == x && d == open_dir[b[i][j]]) {
				if(chmax(sc2,ln)){
					if(sc1<sc2)swap(sc1,sc2);
				}
				break;
			}
		}
	}
	return sc1*sc2;
}

vi calc_inner(Field&b){
	vi scores(2,0);
	Field vis;
	fill(vis.front().begin(), vis.back().end(), 0);

	rep(y,n)rep(x,n)if(!vis[y][x]){
		vis[y][x]=1;
		int i=y,j=x, d=open_dir[b[i][j]] ,ln=0;
		while(true) {
			int d2 = dnext[b[i][j]][d];
			if (d2 == -1) break;
			i += dy[d2];
			j += dx[d2];
			if (i < 0 || i >= 30 || j < 0 || j >= 30) break;
			vis[i][j]=1;
			d = (d2 + 2) % 4;
			ln++;
			if (i == y && j == x && d == open_dir[b[i][j]]) {
				scores.push_back(ln);
				break;
			}
		}
	}
	sort(rall(scores));
	// debug(scores);
	return scores;
}

vi calc_path(Field&b){
	vi scores;
	vector<vvb> vis(n,vvb(n,vb(4,false)));
	vector<vvi> paths(n,vvi(n,vi(4,0)));

	rep(y,n)rep(x,n)rep(sd,4)if(!vis[y][x][sd]){
		if(dnext[b[y][x]][sd]==-1)continue;

		vis[y][x][sd]=1;
		int i=y,j=x, d=sd ,ln=0;
		while(true) {
			vis[i][j][d]=1;
			int d2 = dnext[b[i][j]][d];
			if (d2 == -1) {
				paths[y][x][sd]=ln;
				break;
			}
			if(i!=y or j!=x)vis[i][j][d2]=1;

			i += dy[d2];
			j += dx[d2];
			if (i < 0 || i >= 30 || j < 0 || j >= 30) {
				paths[y][x][sd]=ln+1;
				break;
			}
			d = (d2 + 2) % 4;
			ln++;
			if (i == y && j == x && d == sd) {
				scores.push_back(ln);
				break;
			}
		}
	}

	vi sc2;
	rep(i,n)rep(j,n)rep(d,4){
		if(paths[i][j][d]==0)continue;
		if(dnext[b[i][j]][d]==-1)continue;
		if(dnext[b[i][j]][d]>d)continue;
		int ln=paths[i][j][d] + paths[i][j][dnext[b[i][j]][d]] - 1;
		scores.push_back(ln);
	}
	sort(rall(scores));
	return scores;
}

void pans(Field&b){
	rep(i,n)rep(j,n){
		int dd=a[i][j];
		int c=0;
		while(dd!=b[i][j]){
			dd=rot_index[dd];
			c++;
		}
		cout<<c;
	}
	cout<<'\n';
	debug("Score:",calc(b));
}

// create cycle
void create_circle(Field&b){
	Field vis;
	fill(vis.front().begin(), vis.back().end(), 0);
	Field created;
	fill(created.front().begin(), created.back().end(), 0);
	rep(i,n)rep(j,n)if(b[i][j]>=6)vis[i][j]=1;

	rep(i,n-1)rep(j,n-1){
		if(b[i][j]>=6)continue;
		if(b[i][j+1]>=6)continue;
		if(b[i+1][j]>=6)continue;
		if(b[i+1][j+1]>=6)continue;
		if(vis[i][j] and b[i][j]!=2 and b[i][j]!=4)continue;
		if(vis[i][j+1] and b[i][j+1]!=1 and b[i][j+1]!=5)continue;
		if(vis[i+1][j] and b[i+1][j]!=3 and b[i+1][j]!=5)continue;
		if(vis[i+1][j+1] and b[i+1][j+1]!=0 and b[i+1][j+1]!=4)continue;

		vis[i][j]=1;
		if(b[i][j]<=3)b[i][j]=2;
		else b[i][j]=4;

		vis[i][j+1]=1;
		if(b[i][j+1]<=3)b[i][j+1]=1;
		else b[i][j+1]=5;

		vis[i+1][j]=1;
		if(b[i+1][j]<=3)b[i+1][j]=3;
		else b[i+1][j]=5;

		vis[i+1][j+1]=1;
		if(b[i+1][j+1]<=3)b[i+1][j+1]=0;
		else b[i+1][j+1]=4;
		created[i][j]=1;
		j++;
	}

	rep(i,n-1)rep(j,0,n)if(created[i][j]){
		if(created[i+1][j-1] and b[i+1][j]==5)b[i+1][j]=4;
		if(created[i+1][j+1] and b[i+1][j+1]==4)b[i+1][j+1]=5;
	}
}

tuple<int,int,int> modify_random(Field&b){
	int i=Random(0,n),j=Random(0,n),k=0;
	if(b[i][j]<=3){
		k=Random(0,3);
		if(b[i][j]>=k)k++;
	}else if(b[i][j]<=5)k=9-b[i][j];
	else k=13-b[i][j];
	return {i,j,k};
}
int modify_decided(Field&b, int i, int j, int d){
	if(b[i][j]<=3){
		return (b[i][j]+d+1)%4;
	}else if(b[i][j]<=5)return 9-b[i][j];
	else return 13-b[i][j];
}

int count_togire(Field&b, int i, int j){
	int c=0;
	if(i>0){
		if(dnext[b[i][j]][1]==-1 and dnext[b[i-1][j]][3]!=-1)c++;
	}
	if(i<n-1){
		if(dnext[b[i][j]][3]==-1 and dnext[b[i+1][j]][1]!=-1)c++;
	}
	if(j>0){
		if(dnext[b[i][j]][0]==-1 and dnext[b[i][j-1]][2]!=-1)c++;
	}
	if(j<n-1){
		if(dnext[b[i][j]][2]==-1 and dnext[b[i][j+1]][0]!=-1)c++;
	}
	return c;
}
int optimal_decided(Field&b, int i, int j){
	int mnc=count_togire(b,i,j), mnb=b[i][j], stb=b[i][j];
	rep(d,4){
		b[i][j]=rot_index[b[i][j]];
		if(b[i][j]==stb)break;
		if(int c=count_togire(b,i,j); c<mnc){
			mnc=c;
			mnb=b[i][j];
		}
	}
	return mnb;
}

int main() {
	// Mgr::timer
	rep(i,n){
		def(string,s);
		rep(j,n)a[i][j]=s[j]-'0';
	}
	Field b=a, mfield; vi mscore;
	create_circle(b);
	mfield=b; mscore=calc_path(b);

	while(Mgr::timer.get() <= 1500){
		rep(i,n)rep(j,n){
			int d=optimal_decided(b,i,j);
			b[i][j]=d;
		}
		rep(i,n){
			rep(j,n)rep(d,3){
				int k = modify_decided(b,i,j,d);
				int old=b[i][j];
				b[i][j]=k;
				auto paths=calc_path(b);

				bool modified=false, failed=false;
				rep(x,min(sz(paths),sz(mscore))){
					if(paths[x]<mscore[x]){
						failed=true;
						break;
					}
					if(paths[x]>mscore[x]){
						mscore=paths;
						mfield=b;
						modified=true;
						break;
					}
				}
				if(!modified){
					if(failed)b[i][j]=old;
				}
				// else cout<<Mgr::timer.get()<<","<<paths<<endl;;
			}
		}
	}

	mscore=calc_inner(mfield);
	int sc=mscore[0]*mscore[1];
	while(Mgr::timer){
		rep(i,n){
			rep(j,n)rep(d,mfield[i][j]<=3 ? 3 : 1){
				int k = modify_decided(mfield,i,j,d);
				int old=mfield[i][j];
				mfield[i][j]=k;
				if(chmax(mscore,calc_inner(mfield))){
					if(chmax(sc, mscore[0]*mscore[1])){
						// cout<<Mgr::timer.get()<<","<<i<<","<<j<<","<<d<<" = ";
						// pans(sc,mfield);
					}
				}else mfield[i][j]=old;
			}
		}
	}

	pans(mfield);

}