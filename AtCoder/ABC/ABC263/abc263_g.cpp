#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
#define FOR(i,m,n) for(int i=(m);i<(n);++i)
#define REPPP(i,n) FOR(i,0,n)
#define ALL(v) (v).begin(),(v).end()
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
#define rep(...) __LOOPSWITCH(__VA_ARGS__, __RANGE, __REPPP, __LOOP) (__VA_ARGS__)
#define rrep(...) __LOOPSWITCH(__VA_ARGS__, __RRANGE, __RREPPP, __LOOP) (__VA_ARGS__)
#define __LOOP(q) __LOOP2(q, __LINE__)
#define __LOOP2(q,l) __LOOP3(q,l)
#define __LOOP3(q,l) __REPPP(_lp ## l,q)
#define __REPPP(i,n) __RANGE(i,0,n)
#define __RANGE(i,a,n) for(ll i=((ll)a);i<((ll)n);++i)
#define __RREPPP(i,n) __RRANGE(i,0,n)
#define __RRANGE(i,a,n) for(ll i=((ll)(n)-1);i>=((ll)a);--i)
#define sz(a) ((ll)(a).size())template <typename T> using posteriority_queue = priority_queue<T, vector<T>, greater<T> >;
const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fLL;
const double EPS = 1e-8;
const int MOD = 1000000007;
// const int MOD = 998244353;
const int dy[] = {1, 0, -1, 0}, dx[] = {0, -1, 0, 1};
// const int dy[] = {1, 1, 0, -1, -1, -1, 0, 1}, dx[] = {0, -1, -1, -1, 0, 1, 1, 1};
template <typename T, typename U> inline bool chmax(T &a, U b) { return a < b ? (a = b, true) : false; }
template <typename T, typename U> inline bool chmin(T &a, U b) { return a > b ? (a = b, true) : false; }
template <typename T> void unique(vector<T> &a) { a.erase(unique(ALL(a)), a.end()); }
struct IOSetup {
  IOSetup() {
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);
    cout << fixed << setprecision(20);
  }
} iosetup;


template <class T>
struct Edge {
    int rev, from, to;  // rev:逆向きの辺の番号
    T cap, original_cap;
    Edge(int r, int f, int t, T c) : rev(r), from(f), to(t), cap(c), original_cap(c) {}
};
template <class T>
struct Graph {
    vector<vector<Edge<T>>> G;
    Graph(int n = 0) : G(n) {}
    vector<Edge<T>>& operator[](int i) { return G[i]; }
    const size_t size() const { return G.size(); }
    Edge<T>& redge(Edge<T> e) {  // 逆向きの辺を返す
        return G[e.to][e.rev];   // 自己ループはないと仮定（あれば G[e.to][e.rev + 1] とする必要がある）
    }
    void add_edge(int from, int to, T cap) {  // 有向辺を加える
        G[from].push_back(Edge<T>((int)G[to].size(), from, to, cap));
        G[to].push_back(Edge<T>((int)G[from].size() - 1, to, from, 0));
    }
};
/* FordFulkerson: Ford-Fulkersonのアルゴリズムで最大流を求める構造体
    max_flow(G,s,t)：sからtへのグラフGの最大流を求める
    副作用：G は最大流の残余ネットワークになる
    計算量: O(|f*||E|) (f*:最大流) (この最悪ケースになることはほぼ無い)
*/
template <class T>
struct FordFulkerson {
    const T INF = 1e9;
    vector<int> used;
    FordFulkerson(){};
    T dfs(Graph<T>& G, int v, int t, T f) {  // 増加可能経路を見つけて増加分のフローを返す
        if (v == t) return f;
        used[v] = true;
        for (auto& e : G[v]) {
            if (!used[e.to] && e.cap > 0) {
                T d = dfs(G, e.to, t, min(f, e.cap));
                if (d > 0) {
                    e.cap -= d;
                    G.redge(e).cap += d;
                    return d;
                }
            }
        }
        return 0;
    }
    T max_flow(Graph<T>& G, int s, int t) {
        T flow = 0;
        while (true) {
            used.assign(G.size(), 0);
            T f = dfs(G, s, t, INF);  // f が増加分のフロー
            if (f == 0) {
                return flow;
            } else {
                flow += f;
            }
        }
        return 0;
    }
};


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

struct Prime {
private:
	static constexpr ull fast_gcd(ull a, ull b) {
		if(a==0||b==0)return a+b;
		int n=__builtin_ctzll(a),m=__builtin_ctzll(b);
		a>>=n; b>>=m;
		while(a!=b){ int x=__builtin_ctzll(a-b); a=(max(a,b)-(b=min(a,b)))>>x; }
		return a<<min(n,m);
	}
	static constexpr ull mul (ull a,ull b,ull&mod) {
		ll ret=a*b-mod*(ull)(1.L/mod*a*b);
		return ret+(ret<0)*mod-(ret>=(ll)mod)*mod;
	}
	static constexpr ull mod128 (ull a,ull e,ull&mod) {
		ull ret=1;
		while(e){ if(e&1)ret=mul(ret,a,mod); a=mul(a,a,mod),e>>=1; }
		return ret;
	}
	static constexpr inline ull pollard_f(ull x, ull&n, ull&c){ return mul(x,x,n)+c; }
	static ull pollard(ull n){
		ull t=0,prod=2,q,x=0,y=0,c=0,i=2;
		while((t++&127) or fast_gcd(prod,n)==1){
			if(x==y)y=pollard_f(x=i,n,c=Random(1ll,n));
			if((q=mul(prod,max(x,y)-min(x,y),n)))prod=q;
			x=pollard_f(x,n,c),y=pollard_f(pollard_f(y,n,c),n,c);
		}
		return fast_gcd(prod,n);
	}
	static inline const auto pollard_seed={2, 7, 61};
	static inline const auto pollard_seed_64={2, 325, 9375, 28178, 450775, 9780504, 1795265022};
public:
	static constexpr bool isPrime (ull n) {
		if(n<=1)return false;
		if(n<4)return true;
		if(n%6%4!=1)return false;
		ull s=__builtin_ctzll(n-1),d=n>>s;

		for(auto x:(n<(1<<30) ? pollard_seed : pollard_seed_64)){
			ull p=mod128(x,d,n),i=s;
			while(p!=1 and p!=n-1 and x%n and i--)p=mul(p,p,n);
			if(p!=n-1 and i!=s) return false;
		}
		return true;
	}

	static vector<ull> factor(ull n){
		if (n==1) return{};
		if (isPrime(n)) return{n};
		ull x=pollard(n);
		auto l=factor(x),r=factor(n/x);
		l.insert(l.end(),all(r));
		return l;
	}

	static vector<ull> divisor(ull n){
		HashSet<ull> st;
		vector<ull> tmp;
		st.insert(1);
		for(auto&f:factor(n)){
			tmp.clear();
			for(auto&d:st)tmp.emplace_back(d*f);
			for(auto&d:tmp)st.insert(d);
		}
		return vector<ull>(all(st));
	}

	static int divisorCount(ull n){
		int ret=1; ull v=0,c=0;
		auto fac=factor(n);
		sort(all(fac)); fac.emplace_back(-1);
		for(auto&f:fac){if(f!=v)ret*=c+1, v=f, c=0; c++;}
		return ret;
	}
};

int main() {
  int n; cin >> n;
  vector<pair<int,int>> a,b;
  REPPP(i, n){
	int x,y; cin>>x>>y;
	a.emplace_back(x,y);
	
  }

  Graph<ll> g(n*2+2);

  rep(i,n)rep(j,n){
	if(Prime::isPrime(a[i].first+a[j].first)){
	  g.add_edge(i,j+n,min(a[i].second,a[j].second));
	}
  }
  rep(i,n){
	g.add_edge(n*2,i,a[i].second);
	g.add_edge(i+n,n*2+1,a[i].second);
  }
  FordFulkerson<ll> f;

  cout<<f.max_flow(g, n*2, n*2+1)/2<<endl;

  return 0;
}

