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
	static const int TLE = 20000;
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

	vector<vector<tuple<ll,T>>>edge, inv_edge;
	Graph(int n=1,T inf=LINF):size(n),INF_VAL(inf){
		edge.resize(size);
		inv_edge.resize(size);
	}
	constexpr void add(ll from, ll to, T cost, bool directed=false){
		edge[from].emplace_back(to,cost);
		if(!directed) edge[to].emplace_back(from,cost);
		else inv_edge[to].emplace_back(from,cost);
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
	constexpr vector<T> inv_bfs(int s){
		vector<T> ret(size,INF_VAL);
		deque<int> q;
		ret[q.emplace_back(s)]=0;
		while(!q.empty()){
			int p=q.front(); q.pop_front();
			for(auto[to,cost]:inv_edge[p])if(chmin(ret[to],ret[p]+cost)){
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
	pair<bool,char> query(vi l, vi r, bool dryrun=false){
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
			}
		}
		if(dryrun) return {false, '?'};

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
		if(res=='=') res= lhash2>rhash2 ? '<' : '>';
		memo2[{lhash2,rhash2}]=res;
		memo2[{rhash2,lhash2}]=res=='<'?'>':'<';

		// for(auto&[mp,mc]:memo2){
		// 	auto[ml,mr]=mp;
		// 	if(res!=mc) swap(ml,mr);
		// 	/**
		// 	 * ml < mr, lhash2 < rhash2 （複合同順）
		// 	 */
		// 	if((ml|mr) != (lhash2|rhash2)) continue;
		// 	if(memo2.find({ml&lhash2, mr&rhash2})!=memo2.end()) continue;
		// 	memo2[{ml&lhash2, mr&rhash2}] = res;
		// 	memo2[{mr&rhash2, ml&lhash2}] = res=='<'?'>':'<';
		// }

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

		ll sum=accumulate(all(a), 0ll);

		rep(1000){
			bool ok=true;
			for(auto&[l,r]:constraint){
				int lsum=0, rsum=0;
				for(auto&i:l) lsum+=predictedArr[i];
				for(auto&i:r) rsum+=predictedArr[i];
				if(lsum>=rsum + 1e3){
					ok=false;
					for(auto&i:r) predictedArr[i] += (lsum-rsum) / 2.0 / sz(r) + 1;
					for(auto&i:l) predictedArr[i] -= (lsum-rsum) / 2.0 / sz(l) + 1;
					sum += ((lsum-rsum) / 2.0 / sz(r) + 1) * sz(r);
					sum -= ((lsum-rsum) / 2.0 / sz(l) + 1) * sz(l);
				}
			}
			if(ok) return predictedArr;
		}
		return predictedArr;
	}
};
Input input;


vi separate() {
	exponential_distribution<float> dist(1e-5);
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
	int tier = round(1.0*q/n);
	input.init();

	Graph<int> g(n,INF);
	auto query=[&](vi l, vi r, bool dryrun=false){
		if(sz(l)==1 and sz(r)==1){
			if(g.bfs(l[0])[r[0]]!=g.INF_VAL) {
				return pair(true,'>');
			} else if(g.bfs(r[0])[l[0]]!=g.INF_VAL) {
				return pair(true,'<');
			}
		}
		auto [known, res] = input.query(l,r, dryrun);
		if(dryrun) return pair(known,res);
		if(!known and sz(l)==1 and sz(r)==1){

			if(res=='<')g.add(r[0],l[0],1,true);
			else if(res=='>')g.add(l[0],r[0],1,true);
			else if(res=='=')g.add(min(l[0],r[0]),max(l[0],r[0]),1,true);
		}
		return pair(known,res);
	};

	int pc1=0, pc2=0, pc3=0;

	float predictedThreshold=93.77365378681901 
				- 2.30357162 * n 
				- 21.6464247 * d 
				+ 1.06850783 * q 
				+ 0.00211965463 * n * n 
				- 0.0485017953 * n * d 
				+ 0.0000370250176 * n * q 
				+ 1.42427597 * d * d 
				- 0.0255629323 * d * q 
				+ 0.00000322608232 * q * q;
	int threshold=clamp((int)predictedThreshold, 0, q-n);
	if(tier==2) threshold=0;
	// if(tier<=3) threshold=0;
	bool decideLarge = false;
	{
		{
			vi tgt = g.topologicalSort().second;
			while(sz(tgt)>1){
				vi tgt2;
				rep(ii,sz(tgt)/2){
					int i=ii*2;
					if(threshold<=input.qs)break;
					auto [known,res]=query({tgt[i]}, {tgt[i+1]});
					if(res=='-')break;
					if(res=='<'){
						tgt2.pb(tgt[i+1]);
					} else {
						tgt2.pb(tgt[i]);
					}
					++i;
				}

				if(sz(tgt)%2==1)tgt2.pb(tgt.back());
				tgt=tgt2;
			}
		}
		// TODO: edgeの縮約が効率化につながる可能性
		{
			vi tgt = g.topologicalSort().second;
			queue<int> qu;
			qu.push(tgt[0]);
			vb used(n,false);
			used[tgt[0]]=true;

			while(!qu.empty()){
				if(threshold<=input.qs)break;
				int p=qu.front(); qu.pop();
				vi children;
				for(auto&[to,_]:g.edge[p]){
					children.pb(to);
				}
				sort(all(children),[&](int a, int b){
					// if(g.bfs(a)[b]!=g.INF_VAL)return false;
					// if(g.bfs(b)[a]!=g.INF_VAL)return true;
					return query({a}, {b}).second=='<';
				});
				for(auto&to:children)if(!used[to]){
					used[to]=true;
					qu.push(to);
				}
			}
		}


		while(threshold > input.qs){
			// 回数が余っていたら、全順序を特定しに掛かる
			vi tgt = g.topologicalSort().second;
			// 全順序が確定したら終了
			bool completed=true;
			rep(i,n){
				if(threshold<=input.qs)break;
				auto dist=g.bfs(tgt[i]);
				rep(j,i+1,n){
					if(threshold<=input.qs)break;
					if(dist[tgt[j]]==g.INF_VAL){
						completed=false;
						query({tgt[i]}, {tgt[j]});
					}
				}
				if(!completed)break;
			}
			if(completed)break;
		}
		if (threshold > input.qs) {
			decideLarge = true;
		}
	}

	pc1=input.qs;

	vvi grp(d);
	Graph<int> grpDiff(d,INF);
	{
		auto sep=separate();
		auto top=g.topologicalSort().second;
		if(decideLarge){
			rep(n){
				vi tgt(n); iota(all(tgt),0);
				shuffle(all(tgt),Random);
				vi l,r;
				rep(i,d)l.pb(tgt[i]);
				rep(i,d,d*2)r.pb(tgt[i]);
				query(l,r);
			}

			auto val = input.predictArr_topologicalDecided(top);
			if(val[0]!=-1){
				sep = separateByValues(val);
				rep(i,n){
					grp[sep[i]].push_back(i);
				}
			} else {
				rep(i,n){
					grp[sep[i]].push_back(top[i]);
				}
			}
		}else{
			for(auto&i:top){
				grp[sep[i]].push_back(top[i]);
			}
		}
	}
	
	vi ans(n);
	rep(i,d)for(auto&v:grp[i])ans[v]=i;
	// TODO Qに余裕がある時、最大の山を積極的に崩そうとする

	bool isDryRun=false;
	while(Mgr::timer){
		int marks=input.qs;
		auto top = g.topologicalSort().second;
		reverse(all(top));

		vp searchIndex;
		if(tier <= 3){
			rep(aa,n){
				int a = top[aa];
				rep(bb,aa+1,n){
					int b = top[n-bb+aa];
					searchIndex.emplace_back(a,b);
				}
			}
		} else if(tier <= 6) {
			rrep(a,n){
				rrep(b,a){
					searchIndex.emplace_back(a,b);
				}
			}
		} else {
			rep(aa,n){
				int a = top[aa];
				rep(bb,aa+1,n){
					int b = top[bb];
					searchIndex.emplace_back(a,b);
				}
			}
		}

		int skipA = -1;
		for(auto[a,b]:searchIndex){{
			// if(tier<=3 and q-input.qs<=n)break;
			if(input.qs==q or !Mgr::timer) goto finish;
			if(skipA==a)continue;
			int aGrp = ans[a];
			auto aParents = g.inv_bfs(a);
			auto aChildren = g.bfs(a);
			int bGrp = ans[b];
			if(aGrp==bGrp)continue;
				retry:;
				auto aNew = grp[aGrp], bNew = grp[bGrp];
				if(grpDiff.bfs(bGrp)[aGrp]!=grpDiff.INF_VAL){
					// bGrp > aGrp
					aNew.push_back(b);
					bNew.erase(find(all(bNew),b));
					if(!bNew.empty()) {
						auto [known,res]=query(aNew, bNew);
						if(res=='-') goto finish;
						if(res=='<'){
							// bを引っこ抜いても大丈夫
							grp[aGrp]=aNew, grp[bGrp]=bNew;
							ans[b]=aGrp;
							//bGrpより小さいことになっていたaGrp以外のやつとは、大小関係が分からなくなる
							grpDiff.edge[bGrp] = grpDiff.edge[aGrp];
							grpDiff.edge[bGrp].eb(aGrp,1);
							goto changed;
						}
					}
					if(aParents[b]!=g.INF_VAL){
						// bGrp > aGrp && b > a
						// aとbを入れ替えても大丈夫
						aNew.erase(find(all(aNew),a));
						bNew.push_back(a);
						auto [known,res]=query(aNew, bNew);
						if(res=='-') goto finish;
						if(res=='<'){
							grp[aGrp]=aNew, grp[bGrp]=bNew;
							ans[a]=bGrp, ans[b]=aGrp;
							//bGrpより小さいことになっていたaGrp以外のやつとは、大小関係が分からなくなる
							grpDiff.edge[bGrp] = grpDiff.edge[aGrp];
							grpDiff.edge[bGrp].eb(aGrp,1);
							
							//aGrpより大きいことになっていたbGrp以外のやつとは、大小関係が分からなくなる
							// NOTE : bGrpより大きい奴はそのまま残して良い
							rep(otherGrp,d)if(otherGrp!=bGrp){
								auto itr=find(all(grpDiff.edge[otherGrp]),make_tuple(aGrp,1));
								if(itr!=grpDiff.edge[otherGrp].end())grpDiff.edge[otherGrp].erase(itr);
							}
						}
						goto changed;
					}
					continue;
				} else if(grpDiff.bfs(aGrp)[bGrp]!=grpDiff.INF_VAL){
					if(sz(grp[aGrp])==1)continue;
					// aGrp > bGrp
					bNew.push_back(a);
					aNew.erase(find(all(aNew),a));
					if(!aNew.empty()){
						auto [known,res]=query(aNew, bNew);
						if(res=='-') goto finish;
						if(res=='>'){
							// aを引っこ抜いても大丈夫
							grp[aGrp]=aNew, grp[bGrp]=bNew;
							ans[a]=bGrp;
							//aGrpより小さいことになっていたbGrp以外のやつとは、大小関係が分からなくなる
							grpDiff.edge[aGrp] = grpDiff.edge[bGrp];
							grpDiff.edge[aGrp].eb(bGrp,1);
							goto changed;
						}
					}
					if(aChildren[b]!=g.INF_VAL){
						// aGrp > bGrp && a > b
						// aとbを入れ替えても大丈夫
						aNew.push_back(b);
						bNew.erase(find(all(bNew),b));
						auto [known,res]=query(aNew, bNew);
						if(res=='-') goto finish;
						if(res=='>'){
							grp[aGrp]=aNew, grp[bGrp]=bNew;
							ans[a]=bGrp, ans[b]=aGrp;
							//aGrpより小さいことになっていたbGrp以外のやつとは、大小関係が分からなくなる
							grpDiff.edge[aGrp] = grpDiff.edge[bGrp];
							grpDiff.edge[aGrp].eb(bGrp,1);

							//bGrpより大きいことになっていたaGrp以外のやつとは、大小関係が分からなくなる
							// NOTE : aGrpより大きい奴はそのまま残して良い
							rep(otherGrp,d)if(otherGrp!=aGrp){
								auto itr=find(all(grpDiff.edge[otherGrp]),make_tuple(bGrp,1));
								if(itr!=grpDiff.edge[otherGrp].end())grpDiff.edge[otherGrp].erase(itr);
							}
						}
						goto changed;
					}
					continue;
				} else {
					if(isDryRun) continue;
					// aGrpとbGrpの大小関係が不明
					auto [known,res]=query(grp[aGrp], grp[bGrp]);
					if(res=='-') goto finish;
					if(res=='<') grpDiff.add(bGrp,aGrp,1,true);
					else if(res=='>') grpDiff.add(aGrp,bGrp,1,true);
					else grpDiff.add(min(aGrp,bGrp),max(aGrp,bGrp),1,true);
					// out_f("Retry");
					goto retry;
				}
				changed:;
				out("#c", ans);
				skipA = a;
			}
		}
		if(marks==input.qs){
			if(isDryRun) isDryRun=false;
			else break;
		}else{
			isDryRun=true;
		}
	} finish:;
	pc2=input.qs-pc1;


	int status=2;
	int bcnt = 2;
	while(Mgr::timer){
		int marks=input.qs;
		auto top = g.topologicalSort().second;
		vi topMap(n);
		rep(i,n)topMap[top[i]]=i;
		auto grpTop = grpDiff.topologicalSort().second;
		rep(i,d){
			sort(all(grp[i]),[&](int a, int b){
				return topMap[a]<topMap[b];
			});
		}
		// bcnt=max(status,2);
		rep(ag,d){
			int aGrp = grpTop[ag];
			rrep(bg,ag+1,d){
				int bGrp = grpTop[bg];
				if(sz(grp[bGrp])<bcnt)continue;
				bool swapped=false;
				if(grpDiff.bfs(aGrp)[bGrp]==grpDiff.INF_VAL) {
					if(status>0) continue;
					auto [known,res]=query(grp[aGrp], grp[bGrp]);
					if(res=='-') goto finish2;
					if(res=='<') grpDiff.add(bGrp,aGrp,1,true);
					else if(res=='>') grpDiff.add(aGrp,bGrp,1,true);
					else grpDiff.add(min(aGrp,bGrp),max(aGrp,bGrp),1,true);
					if(res!='<') {
						swap(aGrp,bGrp);
						swapped=true;
					}
				}

				// aGrp > bGrp
				for(auto a: grp[aGrp]){
					if(input.qs==q or !Mgr::timer) goto finish2;
					vi as(1,a);
					vi bs;
					if(status==2){
						bs = {grp[bGrp][sz(grp[bGrp])-1], grp[bGrp][sz(grp[bGrp])-2]};
					} else {
						sample(all(grp[bGrp]), back_insert_iterator(bs), bcnt, Random);
					}
					auto [known,res] = query(as, bs, status!=0);
					if(status!=0 and !known) continue;
					if(res=='-') goto finish2;
					if(res!='>') continue;

					auto aNew = grp[aGrp], bNew = grp[bGrp];
					aNew.erase(find(all(aNew),a));
					for(auto b:bs)bNew.erase(find(all(bNew),b));
					for(auto b:bs)aNew.push_back(b);
					bNew.push_back(a);

					tie(known,res)=query(aNew, bNew);
					if(res=='-') goto finish2;
					if(res!='>') continue;

					grp[aGrp]=aNew, grp[bGrp]=bNew;
					sort(all(grp[aGrp]),[&](int a, int b){
						return topMap[a]<topMap[b];
					});
					sort(all(grp[bGrp]),[&](int a, int b){
						return topMap[a]<topMap[b];
					});
					ans[a]=bGrp;
					for(auto b:bs)ans[b]=aGrp;
					grpDiff.edge[aGrp] = grpDiff.edge[bGrp];
					grpDiff.edge[aGrp].eb(bGrp,1);
					rep(otherGrp,d)if(otherGrp!=aGrp){
						auto itr=find(all(grpDiff.edge[otherGrp]),make_tuple(bGrp,1));
						if(itr!=grpDiff.edge[otherGrp].end())grpDiff.edge[otherGrp].erase(itr);
					}
					out("#c", ans);
					goto aNxt2;
				}
				if(swapped) swap(aGrp,bGrp);
			}
			aNxt2:;
		}

		if(marks==input.qs){
			if(status==0) break;
			else status--;
		}else{
			if(status<2) status++;
		}
	} finish2:;

	pc3=input.qs-pc1-pc2;
	while(q>input.qs){
		input.dummy();
	}

	out(ans);

	#ifdef _DEBUG
	vp tmp;
	rep(i,n)tmp.emplace_back(input.arr[i],i);
	sort(rall(tmp));
	vi correct;
	for(auto&[_,v]:tmp)correct.pb(v);

	out("# topological prediction");
	out("#   correct",correct);
	out("#   predict", g.topologicalSort().second);
	out("# query usage: ",pc1,pc2,pc3);
	out("# value prediction");
	out("#   correct",input.arr);
	#endif
}