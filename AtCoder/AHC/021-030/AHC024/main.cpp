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
template<class K> using IndexedSet=__gnu_pbds::tree<K,__gnu_pbds::null_type,less<K>,__gnu_pbds::rb_tree_tag,__gnu_pbds::tree_order_statistics_node_update>;
template<class K> using HashSet=__gnu_pbds::gp_hash_table<K,__gnu_pbds::null_type,hash<K>>;
template<class K,class V> using IndexedMap=__gnu_pbds::tree<K,V,less<K>,__gnu_pbds::rb_tree_tag,__gnu_pbds::tree_order_statistics_node_update>;
template<class K,class V> using HashMap=__gnu_pbds::gp_hash_table<K,V,hash<K>>;
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
#define __RANGE(i,a,n) for(ll i : views::iota(a,n))
#define __RREP(i,n) __RRANGE(i,0,n)
#define __RRANGE(i,a,n) for(ll i : views::iota(a,n) | views::reverse)
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
const int n=52, m=101;

int dy[]={1,0,-1,0};
int dx[]={0,1,0,-1};

vvi field(n, vi(n, 0));

bool solve(bool allowToZero){
	bool changed = false;
	vi colorCnt(m,0);
	vvi connect(m,vi(m,0)); 
	rep(i,n)rep(j,n){
		rep(v,4){
			int y=i+dy[v], x=j+dx[v];
			if(y<0 or x<0 or y>=n or x>=n) continue;
			connect[field[i][j]][field[y][x]]++;
		}
	}
	rep(i,n)rep(j,n) colorCnt[field[i][j]]++;

	rep(2){
		vvi used;
		vi usedColor(m,0);

		rrep(ln,1,n-1){
			if(count(all(field[ln]), 0)==n) continue;
			auto field2=field;
			field2.erase(field2.begin()+ln);
			field2.push_back(vi(n,0));
			vvi connect2(m,vi(m,0)); 
			rep(i,n)rep(j,1,n){
				rep(v,4){
					int y=i+dy[v], x=j+dx[v];
					if(y<0 or x<0 or y>=n or x>=n) continue;
					connect2[field2[i][j]][field2[y][x]]++;
				}
			}
			

			rep(i,1,m)rep(j,m)if(!!connect[i][j]!=!!connect2[i][j]) goto failed;
			// 各数字の島が2つに分かれていないか
			used = vvi(n,vi(n,0));
			fill(all(usedColor), 0);
			rep(i,1,n-1)rep(j,1,n-1) {
				if(field2[i][j]==0) continue;
				if(used[i][j]) continue;
				if(usedColor[field2[i][j]]) goto failed;
				queue<pii> que;
				que.emplace(i,j);
				used[i][j]=true;
				usedColor[field2[i][j]]=true;
				while(!que.empty()){
					auto [y,x] = que.front(); que.pop();
					rep(v,4){
						int ny=y+dy[v], nx=x+dx[v];
						if(ny<0 or nx<0 or ny>=n or nx>=n) continue;
						if(used[ny][nx]) continue;
						if(field2[ny][nx]!=field2[i][j]) continue;
						used[ny][nx]=true;
						que.emplace(ny,nx);
					}
				}
			}

			rep(j,n) {
				colorCnt[field[ln][j]]--;
				colorCnt[0]++;
			}
			field=field2;
			connect=connect2;
			changed=true;
			{
				vvi ans(n-2, vi(n-2, 0));
				rep(i,n-2)rep(j,n-2) ans[i][j] = field[i+1][j+1];
				out(ans);
			}

			failed: continue;
		}
		// 転置
		rep(i,n)rep(j,i) swap(field[i][j], field[j][i]);
	}

	rep(i,1,n-1){
		if(count(all(field[i]), 0)==n) break;
		rep(j,1,n-1){
			if(field[i][j]==0) continue;

			vector<tuple<int,int,int,int>> adj;
			if(field[i][j]!=field[i+1][j]) adj.emplace_back(field[i+1][j], -1, -1, abs(n/2-i-1) + abs(n/2-j));
			if(field[i][j]!=field[i][j+1]) adj.emplace_back(field[i][j+1], -1, -1, abs(n/2-i) + abs(n/2-j-1));
			if(field[i][j]!=field[i-1][j]) adj.emplace_back(field[i-1][j], -1, -1, abs(n/2-i+1) + abs(n/2-j));
			if(field[i][j]!=field[i][j-1]) adj.emplace_back(field[i][j-1], -1, -1, abs(n/2-i) + abs(n/2-j+1));
			if(adj.size()==0) continue;
			if(adj.size()==4) continue;
			

			// セル四隅それぞれの、隣接する色の種類数
			vi corner;
			rep(y,i,i+2)rep(x,j,j+2){
				set<int> st;
				st.insert(field[y-1][x]);
				st.insert(field[y][x-1]);
				st.insert(field[y-1][x-1]);
				st.insert(field[y][x]);
				st.erase(0);
				corner.pb(st.size());
			}

			for(auto&[c, yy, xx ,v] : adj) {
				if(!allowToZero and c==0) continue;
				bool ok=true;
				//field[i][j]をc色に変える
				auto connect2=connect;
				rep(v,4){
					int y=i+dy[v], x=j+dx[v];
					connect2[field[i][j]][field[y][x]]--;
					connect2[field[y][x]][c]++;
				}
				rep(v,4){
					int y=i+dy[v], x=j+dx[v];
					if(field[y][x]!=field[i][j] and connect2[field[i][j]][field[y][x]]==0) ok=false;
					if(field[y][x]!=c and connect[field[y][x]][c]==0 and connect2[field[y][x]][c]!=0) ok=false;
				}
				
				if(!ok) continue;

				int currentColor = field[i][j];
				field[i][j] = c;
				colorCnt[currentColor]--;
				colorCnt[c]++;
				// 連結性判定
				vb used(n*n,false);

				rep(v,4){
					fill(all(used), false);
					int y=i+dy[v], x=j+dx[v];
					int tgtColor = field[y][x];
					queue<pii> que;
					que.emplace(y,x);
					used[y*n+x]=true;
					int cnt=0;
					while(!que.empty()){
						auto [y,x] = que.front(); que.pop();
						cnt++;
						rep(v,4){
							int ny=y+dy[v], nx=x+dx[v];
							if(ny<0 or nx<0 or ny>=n or nx>=n) continue;
							if(used[ny*n+nx]) continue;
							if(field[ny][nx]!=tgtColor) continue;
							used[ny*n+nx]=true;
							que.emplace(ny,nx);
						}
					}
					if(cnt!=colorCnt[tgtColor]) {
						ok=false;
						break;
					}
				}
				if(!ok) {
					field[i][j] = currentColor;
					colorCnt[currentColor]++;
					colorCnt[c]--;
					continue;
				}
				// セル四隅それぞれの、隣接する色の種類数
				vi corner2;
				rep(y,i,i+2)rep(x,j,j+2){
					set<int> st;
					st.insert(field[y-1][x]);
					st.insert(field[y][x-1]);
					st.insert(field[y-1][x-1]);
					st.insert(field[y][x]);
					st.erase(0);
					corner2.pb(st.size());
				}
				yy=sum(corner)-sum(corner2);
				xx=max(corner)-max(corner2);
				if(allowToZero) {
					xx=yy;
					yy=c==0;
				}
				field[i][j] = currentColor;
				colorCnt[currentColor]++;
				colorCnt[c]--;
			}
			sort(all(adj), [&](auto a, auto b){
				return get<1>(a) > get<1>(b) or (get<1>(a)==get<1>(b) and get<2>(a) > get<2>(b)) or (get<1>(a)==get<1>(b) and get<2>(a)==get<2>(b) and get<3>(a) < get<3>(b));
			});

			auto [c, yy, xx, __] = adj[0];
			if(yy >= 0) {
				rep(v,4){
					int y=i+dy[v], x=j+dx[v];
					connect[field[y][x]][field[i][j]]--;
					connect[field[i][j]][field[y][x]]--;
					connect[field[y][x]][c]++;
					connect[c][field[y][x]]++;
				}
				colorCnt[c]++;
				colorCnt[field[i][j]]--;
				field[i][j] = c;
				changed=true;
			}
		}
	}
	if(!changed) return false;

	return true;
}

int main() { /**/
	{int _; cin>>_>>_;}
	rep(i,1,n-1)rep(j,1,n-1) cin>>field[i][j];

	rep(200){
		if(!solve(false)) break;
		if(Mgr::timer.get() >= 1600) break;
	}
	debug_f(Mgr::timer.get(), "ms");

	rep(1000){
		if(!solve(true)) break;
		rep(i,n)rep(j,n) if(j<n-j-1)swap(field[i][j], field[i][n-j-1]);
		if(Mgr::timer.get() >= 1900) break;
	}




	vvi ans(n-2, vi(n-2, 0));
	rep(i,n-2)rep(j,n-2) ans[i][j] = field[i+1][j+1];
	out(ans);
}