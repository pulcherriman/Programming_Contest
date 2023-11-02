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
#define __RANGE(i,a,n) for(int i=((int)a);i<((int)n);++i)
#define __RREP(i,n) __RRANGE(i,0,n)
#define __RRANGE(i,a,n) for(int i=((int)(n)-1);i>=((int)a);--i)
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
	uint64_t get() const { return (getClocks()-start)/ClocksPerMsec; }
	operator bool() const { return getClocks()<limit; }
	float persentile() const { return (float)get()/limit; }
};
void wait(const int&msec){Timer tm(msec); while(tm);}

struct Mgr {
	static const int TLE = 2000;
	static inline Timer timer = Timer(TLE-70);
	Mgr() {
		ios_base::sync_with_stdio(0); cin.tie(0);
		cout<<fixed<<setprecision(11);
		cerr<<fixed<<setprecision(3);
	}
	~Mgr(){
		cout<<flush;
		// debug_f(timer.get(), "ms")<<flush;
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


template<class T>struct Graph;
template<class T>struct DFSResult{
	vb connected;
	vector<T> distance;
	vi preorder, postorder, eulertour, subtreeNodeCount;
	vl subtreePathLengthSum;
	DFSResult(Graph<T>&g):
		connected(g.size,false),
		distance(g.size,g.INF_VAL),
		preorder(g.size,-1),
		postorder(g.size,-1),
		subtreeNodeCount(g.size,1),
		subtreePathLengthSum(g.size,0){
			eulertour.reserve(g.size*2);
	}
};
template<class T=ll>struct Graph{
	int size;
	T INF_VAL;
	vector<vector<tuple<ll,T>>>edge;
	Graph(int n=1,T inf=LINF):size(n),INF_VAL(inf){edge.resize(size);}
	constexpr void add(ll from, ll to, T cost, bool directed=false){
		edge[from].emplace_back(to,cost);
		if(!directed) edge[to].emplace_back(from,cost);
	}
	constexpr friend ostream &operator<<(ostream &os, const Graph<T> &g) {
		rep(i,g.size)for(auto[from,val]:g.edge[i])pargs(os, i,"=>",from,", cost :",val)<<'\n';
		return os;
	}
	constexpr static pair<int,Graph<T>> input(bool weighted=false, bool directed=false){
		def(int,n,m);
		Graph<T> g(n);
		g.inputEdge(m,weighted,directed);
		return {n,g};
	}

	// s始点で深さ優先探索して情報を返す。木以外で使うのか？
	// この関数は変更しない
	constexpr DFSResult<T> dfs(int s){
		int pre=0,post=0;
		DFSResult<T> ret(*this);
		ret.distance[s]=0;
		const function<void(int)> dfsrec=[this, &ret ,&pre, &post, &dfsrec](int p){
			ret.connected[p]=true;
			ret.preorder[p]=pre++;
			ret.eulertour.emplace_back(p);
			for(auto[to,cost]:edge[p])if(!ret.connected[to]){
				ret.distance[to]=ret.distance[p]+cost;
				dfsrec(to);
				ret.subtreePathLengthSum[p]+=ret.subtreePathLengthSum[to] + ret.subtreeNodeCount[to] * cost;
				ret.subtreeNodeCount[p]+=ret.subtreeNodeCount[to];
			}
			ret.postorder[p]=post++;
			ret.eulertour.emplace_back(p);
		};
		dfsrec(s);
		return ret;
	};
	// BFSする。この関数は変更しない
	constexpr vector<T> bfs(int s){
		vector<T> ret(size,INF_VAL);
		deque<int> q;
		ret[q.emplace_back(s)]=0;
		while(!q.empty()){
			int p=q.front(); q.pop_front();
			for(auto[to,cost]:edge[p])if(chmin(ret[to],ret[p]+cost)){
				if(cost==0)q.emplace_front(to); else q.emplace_back(to);
			}
		}
		return ret;
	}
	// BFSしてパスを復元する。
	// 余分にO(N)掛けてるので、距離だけほしい場合はbfs(s)[t]を見るとよい
	constexpr pair<T,vi> bfs(int s, int t){
		auto dist=bfs(s);
		vi path(1,t);
		while(path.back()!=s)for(auto[to,_]:edge[path.back()])if(dist[to]==dist[path.back()]-1){path.emplace_back(to);break;}
		reverse(all(path));
		return {dist[t], path};
	}
	
	constexpr void inputEdge(int edgeCount, bool weighted, bool directed){
		int a,b; T c=1;
		rep(i,edgeCount){
			cin>>a>>b; if(weighted)cin>>c;
			add(a-1,b-1,c,directed);
		}
	}

	// ノードを追加
	int addNode(){
		edge.emplace_back();
		return size++;
	}

	// 入次数を返す
	vi inDegree(){
		vi in(size,0);
		for(auto&e:edge)for(auto&[to,_]:e)in[to]++;
		return in;
	}

	// トポロジカルソート
	pair<bool,vi> topologicalSort(){
		queue<int> st;
		vi ans, in=inDegree();
		rep(i,size)if(in[i]==0)st.push(i);
		while(!st.empty()){
			int p=st.front(); st.pop();
			ans.push_back(p);
			for(auto&[to,cost]:edge[p]){
				if(--in[to]==0)st.push(to);
			}
		}
		return {(int)ans.size()==size, ans};
	}
};

class GridGraphBase{
protected:
	static const char ROAD_CHAR='.', WALL_CHAR='#', DIRECTION_CHAR[];
	static const int DY[],DX[];
};
const int GridGraphBase::DY[]={0,1,0,-1,1,1,-1,-1};
const int GridGraphBase::DX[]={1,0,-1,0,1,-1,-1,1};
const char GridGraphBase::DIRECTION_CHAR[]="RDLU";

template<class Cell=int>struct GridGraph : public Graph<int> , private GridGraphBase{
	int h,w;
	vector<Cell> field;
	constexpr typename vector<Cell>::iterator operator[](int i) { return field.begin() + i * w; }
	constexpr Cell &at(int i, int j) { return field[i*w+j]; }
	constexpr Cell get(int i, int j) const { return field[i*w+j]; }

	GridGraph(int&_h, int&_w):Graph((_h+=2)*(_w+=2),INF),h(_h),w(_w){
		edge.resize(h*w);
		field.resize(h*w,ROAD);
		rep(i,h)at(i,0)=at(i,w-1)=WALL;
		rep(j,w)at(0,j)=at(h-1,j)=WALL;
	}
	constexpr void input(){
		char c;
		rep(i,1,h-1)rep(j,1,w-1){cin>>c; at(i,j)=(c==WALL_CHAR?WALL:ROAD);}
		rep(i,1,h-1)rep(j,1,w-1)if(get(i,j)==ROAD){
			if(get(i+1,j)==ROAD)add(i*w+j, i*w+j+w, 1);
			if(get(i,j+1)==ROAD)add(i*w+j, i*w+j+1, 1);
		}
	}
	constexpr friend ostream &operator<<(ostream &os, const GridGraph<Cell> &g) {
		rep(i,g.h){rep(j,g.w)os<<(g.get(i,j)==WALL?WALL_CHAR:ROAD_CHAR);os<<endl;}
		return os;
	}
	template<int tgt=4> constexpr vector<tuple<int,int,int>> neighborIndex(int y, int x, Cell v=ROAD){
		vector<tuple<int,int,int>> p;
		rep(i,tgt)if(get(y+DY[i],x+DX[i])==v)p.emplace_back(y+DY[i],x+DX[i],i);
		return p;
	}
	template<int tgt=4> constexpr vector<reference_wrapper<Cell>> neighborCell(int y, int x, Cell v=ROAD){
		vector<reference_wrapper<Cell>> p;
		rep(i,tgt)if(get(y+DY[i],x+DX[i])==v)p.push_back(at(y+DY[i],x+DX[i]));
		return p;
	}
private:
	static constexpr Cell ROAD=0, WALL=-1;
};

template<class T=int>struct Tree : public Graph<T>{
	Tree(int n, T inf=INF):Graph<T>(n,inf){}

	static pair<int,Tree<T>> input(bool weighted=false, bool directed=false){
		def(int,n);
		Tree<T> g(n);
		g.inputEdge(n-1,weighted,directed);
		return {n,g};
	}

	pair<T,vi> diameter(){
		auto [s,_]=getMaxAndIndex(this->bfs(0));
		auto [t,w]=getMaxAndIndex(this->bfs(s));
		return this->bfs(s,t);
	}
};

template<class T=ll>
struct ZobristHash {
	ZobristHash() {}
	ll get_or_create(T key) {
		if(mp.find(key)==mp.end())mp[key]=Random(1ll,numeric_limits<ll>::max());
		return mp[key];
	}
	ll calc_hash(vector<T>&v) {
		HashSet<T> hs;
		ll ret=0;
		for(auto&a:v){
			if(hs.find(a)!=hs.end())continue;
			ret^=get_or_create(a);
			hs.insert(a);
		}
		return ret;
	}
	// vの先頭からi-1番目までの集合のハッシュ 同じ数字はスルー
	vector<ll> calc_hash_seq(vector<T>&v) {
		HashSet<T> hs;
		vector<ll> ret(1,0);
		for(auto&a:v){
			ret.emplace_back(ret.back());
			if(hs.find(a)==hs.end()){
				ret.back()^=get_or_create(a);
				hs.insert(a);
			}
		}
		return ret;
	}
private:
	HashMap<T,ll> mp;
};

int n,d,q;

vi getBaseValues(){
	static vi ret;
	if(!ret.empty()) return ret;

	double r = floor(1e5*n/d) + 0.5;
	double hosei = 1 - exp(-1e-5 * r);
	rep(i,1,n+1){
		ret.pb(round(-1e5 * hosei * (log(n-i+0.5) - log(n))));
	}
	sort(rall(ret));
	return ret;
}
struct Input {
	#ifdef _DEBUG
	vi arr;
	#endif
	void init() {
		#ifdef _DEBUG
		arr.resize(n);
		rep(i,n)cin>>arr[i];
		#endif
	}
	int qs=0;
	
	using hashKey=__int128;
	map<pair<hashKey,hashKey>, char> memo2;
	pair<bool,char> query(vi l, vi r){
		if(qs==q) return {true, '-'};

		hashKey lhash2=0, rhash2=0;
		for(auto&v:l){
			lhash2|=((__int128)1)<<v;
		}
		for(auto&v:r){
			rhash2|=((__int128)1)<<v;
		}
		if(memo2.find({lhash2,rhash2})!=memo2.end()){
			return {true,memo2[{lhash2,rhash2}]};
		}

		for(auto&[mp,mc]:memo2){
			auto[ml,mr]=mp;
			if(mc=='<'){
				//ml<mrのとき、ml⊇l、r⊇mrなら、自明に'<'
				if((ml&lhash2)==lhash2 and (rhash2&mr)==mr){
					memo2[{lhash2,rhash2}]='<';
					memo2[{rhash2,lhash2}]='>';
					return {true,'<'};
				}
			} else if(mc=='>'){
				//ml>mrのとき、l⊇ml、mr⊇rなら、自明に'>'
				if((lhash2&ml)==ml and (mr&rhash2)==rhash2){
					memo2[{lhash2,rhash2}]='>';
					memo2[{rhash2,lhash2}]='<';
					return {true,'>'};
				}
			} else {
				//ml=mrのとき、l=ml、mr=rなら、自明に'='
				if(lhash2==ml and rhash2==mr){
					memo2[{lhash2,rhash2}]='=';
					memo2[{rhash2,lhash2}]='=';
					return {true,'='};
				}
			}
		}

		qs++;
		out(sz(l), sz(r), l, r)<<flush;
		#ifdef _DEBUG
		int lsum=0, rsum=0;
		for(auto i:l)lsum+=arr[i];
		for(auto i:r)rsum+=arr[i];
		char res = lsum>rsum?'>':lsum<rsum?'<':'=';
		#else
		char res;
		cin>>res;
		#endif
		memo2[{lhash2,rhash2}]=res;
		memo2[{rhash2,lhash2}]=(res=='='?'=':res=='<'?'>':'<');
		return {false, res};
	}

	void dummy(){
		qs++;
		out_f(1,1,0,1);
		#ifndef _DEBUG
		char res;
		cin>>res;
		#endif
	}

	vi predictArr_topologicalDecided(vi top){
		auto a = getBaseValues();
		vi predictedArr(n);
		rep(i,n)predictedArr[top[i]]=a[i];
		return predictedArr;
		
		vector<pair<vi,vi>> constraint;
		for(auto&[mp,mc]:memo2){
			auto[ml,mr]=mp;
			vi l,r;
			rep(i,n){
				if(ml&(((__int128)1)<<i)) l.pb(i);
				if(mr&(((__int128)1)<<i)) r.pb(i);
			}
			if(mc!='<') swap(l,r);
			constraint.emplace_back(l,r);
		}

		rep(1000){
			bool ok=true;
			for(auto&[l,r]:constraint){
				int lsum=0, rsum=0;
				for(auto&i:l) lsum+=predictedArr[i];
				for(auto&i:r) rsum+=predictedArr[i];
				if(lsum>=rsum){
					ok=false;
					for(auto&i:r) predictedArr[i] += (lsum-rsum) / sz(r) + 1;
				}
			}
			if(ok) return predictedArr;
		}
		return vi(n,-1);
	}

	vi predictArr(vi top){
		auto base = getBaseValues();
		vi predictedArr(n,0);
		
		vector<pair<vi,vi>> constraint;
		for(auto&[mp,mc]:memo2){
			auto[ml,mr]=mp;
			vi l,r;
			rep(i,n){
				if(ml&(((__int128)1)<<i)) l.pb(i);
				if(mr&(((__int128)1)<<i)) r.pb(i);
			}
			if(mc!='<') swap(l,r);
			constraint.emplace_back(l,r);
		}

		ll sum=0;

		rep(itr,1000){
			bool ok=true;
			for(auto&[l,r]:constraint){
				int lsum=0, rsum=0;
				for(auto&i:l) lsum+=predictedArr[i];
				for(auto&i:r) rsum+=predictedArr[i];
				if(lsum>=rsum){
					ok=false;
					for(auto&i:r) predictedArr[i] += (lsum-rsum) / sz(r) + 1;
					sum += ((lsum-rsum) / sz(r) + 1) * sz(r);
					if(sum >= 2e5*n) {
						rep(i,n) predictedArr[i] /=4;
						sum/=4;
						// vp tmp(n);
						// rep(i,n) tmp[i]={predictedArr[i],i};
						// sort(rall(tmp));
						// sum=0;
						// rep(i,n) {
						// 	sum += predictedArr[tmp[i].second]=base[i];
						// }
					}
				}
			}
			// if(itr%1==0){
			// 	out("# !", predictedArr);
			// }
			if(ok) {
				float bairitu = 1e5*n / sum;
				rep(i,n) predictedArr[i] *= bairitu;
				return predictedArr;
			}

		}
		return vi(n,-1);
	}
};
Input input;


vi separate() {
	vi a=getBaseValues();

	minpq<pair<int,vi>> pq;
	rep(d)pq.emplace(0,vi());
	rep(i,n){
		auto [val,used]=pq.top();
		pq.pop();
		used.push_back(i);
		pq.emplace(val+a[i],used);
	}

	vi ans(n,-1);
	rep(i,d){
		auto [val,used]=pq.top();
		pq.pop();
		for(auto&v:used)ans[v]=i;
	}
	return ans;
}

vi separateByValues(vi values) {
	vp a(n);
	rep(i,n){
		a[i].first=values[i];
		a[i].second=i;
	}
	sort(rall(a));

	minpq<pair<int,vi>> pq;
	rep(d)pq.emplace(0,vi());
	rep(i,n){
		auto [val,used]=pq.top();
		pq.pop();
		used.push_back(a[i].second);
		pq.emplace(val+a[i].first,used);
	}

	vi ans(n,-1);
	rep(i,d){
		auto [val,used]=pq.top();
		pq.pop();
		for(auto&v:used)ans[v]=i;
	}
	return ans;
}


int main() {
	cin>>n>>d>>q;
	input.init();

	Graph<int> g(n,INF);
	int lock=0;
	auto query=[&](vi l, vi r){
		if(q-input.qs<=lock) return pair(false, '-');
		auto [known, res] = input.query(l,r);
		if(!known and sz(l)==1 and sz(r)==1){
			if(res=='<')g.add(r[0],l[0],1,true);
			else if(res=='>')g.add(l[0],r[0],1,true);
			else g.add(min(l[0],r[0]),max(l[0],r[0]),1,true);
		}
		return pair(known,res);
	};


	// vi tgt = g.topologicalSort().second;
	// while(sz(tgt)>1){
	// 	vi tgt2;
	// 	rep(ii,sz(tgt)/2){
	// 		int i=ii*2;

	// 		auto [known,res]=query({tgt[i]}, {tgt[i+1]});
	// 		if(res=='-')break;
	// 		if(res=='<'){
	// 			tgt2.pb(tgt[i+1]);
	// 		} else {
	// 			tgt2.pb(tgt[i]);
	// 		}
	// 		++i;
	// 	}

	// 	if(sz(tgt)%2==1)tgt2.pb(tgt.back());
	// 	tgt=tgt2;
	// }


	vi insertOrder = g.topologicalSort().second;

	vvi grp(d);
	rep(i,d){
		int tgt=insertOrder[i];
		grp[d-1-i].pb(tgt);
	}

	int current = 0;
	
	rep(i,d,n){
		int tgt=insertOrder[i];
		int nxt = (current+1)%d;
		auto [known, res] = query({grp[current]},{grp[nxt]});
		if(res=='-') {
			rep(j,i,n){
				grp[current].pb(insertOrder[j]);
				current=(current+1)%d;
			}
			break;
		}
		if(res!='<'){
			current=nxt;
			i--;
			continue;
		}
		// debug("# push", tgt, "to", current);
		grp[current].pb(tgt);
	}

	Graph<int> grpDiff(d,INF);
	while(Mgr::timer){
		bool changed=false;
		vi ap=grpDiff.topologicalSort().second;
		vi bp=ap; reverse(all(bp));
		rep(aa,d){
			rep(bb,aa+1,d)if(aa!=bb){
				int a=aa, b=bb;
				
				char res;
				if(grpDiff.bfs(a)[b]!=INF){
					res='>';
				}else if(grpDiff.bfs(b)[a]!=INF){
					res='<';
				}else{
					bool known;
					tie(known,res)=query(grp[a], grp[b]);
					if(res=='-') goto finish;
					if(res=='<') grpDiff.add(b,a,1,true);
					else if(res=='>') grpDiff.add(a,b,1,true);
					else grpDiff.add(min(a,b),max(a,b),1,true);
				}

				if(res=='-') goto finish;
				if(res=='=') continue;
				if(res=='>') swap(a,b);
				if(sz(grp[b])<=1) continue;
				//grp[b]の方が大きい
				vi ii(sz(grp[b])); iota(all(ii),0); 
				for(auto i:ii){
					auto ac=grp[a], bc=grp[b];
					ac.push_back(grp[b][i]);
					bc.erase(find(all(bc),grp[b][i]));
					auto [known,res2]=query(ac, bc);
					if(res2=='-') goto finish;
					if(res2=='<') {
						grp[a]=ac;
						grp[b]=bc;
						changed=true;
						vi ans(n);
						rep(i,d)for(auto&v:grp[i])ans[v]=i;
						out_f("#c",ans);
						goto nxta;
					}
				}

			}
			nxta:;
		}
		if(!changed)break;
	} finish:;

	out("# query usage: ", input.qs, q-input.qs, input.qs);
	while(q>input.qs){
		input.dummy();
	}


	vi ans(n);
	rep(i,d){
		for(auto&v:grp[i])ans[v]=i;
	}
	out(ans);

}