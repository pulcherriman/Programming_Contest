// #pragma GCC target("avx")
// #pragma GCC optimize("O3,inline,omit-frame-pointer,no-asynchronous-unwind-tables,fast-math")
// #pragma GCC optimize("unroll-loops")

#define _USE_MATH_DEFINES
#ifndef _DEBUG
#define NDEBUG
#endif
#if defined(ONLINE_JUDGE) || defined(_DEBUG)
#include <atcoder/all>
using namespace atcoder;
#endif
#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using ll=long long;
using ld=long double;
using ull=unsigned long long;
using vb=vector<bool>;
using vvb=vector<vb>;
using vd=vector<double>;
using vvd=vector<vd>;
using vi=vector<int>;
using vvi=vector<vi>;
using vl=vector<ll>;
using vvl=vector<vl>;
using pll=pair<ll,ll>;
using tll=tuple<ll,ll>;
using tlll=tuple<ll,ll,ll>;
using vs=vector<string>;
template<class K> using IndexedSet=__gnu_pbds::tree<K,__gnu_pbds::null_type,less<K>,__gnu_pbds::rb_tree_tag,__gnu_pbds::tree_order_statistics_node_update>;
template<class K> using HashSet=__gnu_pbds::gp_hash_table<K,__gnu_pbds::null_type>;
template<class K,class V> using IndexedMap=__gnu_pbds::tree<K,V,less<K>,__gnu_pbds::rb_tree_tag,__gnu_pbds::tree_order_statistics_node_update>;
template<class K,class V> using HashMap=__gnu_pbds::gp_hash_table<K,V>;

#define all(a) a.begin(),a.end()
#define rall(a) a.rbegin(),a.rend()
#define loop(q) __loop(q, __LINE__)
#define __loop(q,l) __loop2(q,l)
#define __loop2(q,l) rep(_lp ## l,q)
#define rep(i,n) range(i,0,n)
#define rrep(i,n) rrange(i,0,n)
#define range(i,a,n) for(ll i=((ll)a);i<((ll)n);++i)
#define rrange(i,a,n) for(ll i=((ll)n-1);i>=((ll)a);--i)
#define repsq(i,n) for(ll i=0;i*i<=n;++i)
#define each(v,a) for(auto v:a)
#define eachref(v,a) for(auto&v:a)
#define fcout(a) cout<<setprecision(a)<<fixed
constexpr ll LINF=1ll<<60;
constexpr int INF=1<<30;
constexpr double EPS=(1e-9);
constexpr ll MOD=1000000007ll;
constexpr double PI=3.1415926535897932384;

void Main();
int main(){cin.tie(nullptr);ios::sync_with_stdio(false);Main();return 0;}
template<class T>constexpr bool chmax(T&a,T b){return a<b?a=b,1:0;}
template<class T>constexpr bool chmin(T&a,T b){return a>b?a=b,1:0;}
template<class S>S sum(vector<S>&a){return accumulate(all(a),S());}
template<class S>S max(vector<S>&a){return *max_element(all(a));}
template<class S>S min(vector<S>&a){return *min_element(all(a));}

//output
template<class T>struct hasItr{
	template<class U>static constexpr true_type check(class U::iterator*);
	template<class U>static constexpr false_type check(...);
	static constexpr bool v=decltype(check<T>(nullptr))::value;
};
template<>struct hasItr<string>{static constexpr bool v=false;};

template<class T>void puta(T&t,false_type,ostream&os,[[maybe_unused]]char el){os<<t;}
template<class T>void puta(T&t,true_type,ostream&os,char el){
	constexpr bool h=hasItr<typename T::value_type>::v;
	bool F=true,I;
	for(auto&i:t){
		if(!F)os<<' ';
		puta(i,bool_constant<h>(),os,el);
		F=I=h;
	}
	if(!I)os<<el;
}
template<class T>void puta(const T&t, ostream&os=cout, char el='\n'){
	puta(t,bool_constant<hasItr<T>::v>(),os,el);
	if(!hasItr<T>::v)os<<el;
}
template<class H,class...T>void puta(const H&h,const T&...t){cout<<h<<' ';puta(t...);}
template<size_t i,class...T>void puta(tuple<T...>const&t, ostream&os){
	if constexpr(i==sizeof...(T)-1)puta(get<i>(t),os);
	else{os<<get<i>(t)<<' ';puta<i+1>(t,os);}
}
template<class...T>void puta(tuple<T...>const&t, ostream&os=cout){puta<0>(t,os);}
template<class S,class T>constexpr ostream&operator<<(ostream&os,pair<S,T>p){
	os<<'['<<p.first<<", ";
	if constexpr(hasItr<T>::v)puta(p.second,bool_constant<true>(),os,']');
	else os<<p.second<<']';
	return os;
};
template<class...T>constexpr ostream&operator<<(ostream&os,tuple<T...>t){puta(t,os); return os;}
void YN(bool b){puta(b?"YES":"NO");}
void Yn(bool b){puta(b?"Yes":"No");}

#ifdef _DEBUG
template<class T>void dump_f(const T&t){puta(t,cerr);}
template<class H,class...T>void dump_f(const H&h,const T&...t){cerr<<h<<' ';dump_f(t...);}
template<class...T>void dump_f(tuple<T...>const&t){puta(t,cerr);}
#define dump(...)cerr<<"  "<<string(#__VA_ARGS__)<<": ["<<to_string(__LINE__)<<":"<<__FUNCTION__<<"]\n    ",dump_f(__VA_ARGS__)
#else
#define dump(...)                                                              
#endif

//input
template<class S>auto&operator>>(istream&is,vector<S>&t){for(S&a:t)cin>>a;return is;}
template<typename...S>void geta_(S&...s){((cin>>s),...);}
#define geta(t,...) t __VA_ARGS__;geta_(__VA_ARGS__)
template<class T,class...Args>auto vec(T x,int arg,Args...args){if constexpr(sizeof...(args)==0)return vector(arg,x);else return vector(arg,vec(x,args...));}
#define getv(a,...) auto a=vec(__VA_ARGS__);cin>>a

// ライブラリ貼るスペース
template<class T=ll>struct Graph{
	int size;
	T INF_VAL;
	vector<vector<tuple<ll,T>>>edge;
	Graph(int n=1,T inf=LINF):size(n),INF_VAL(inf){edge.resize(size);}
	void add(ll from, ll to, T cost, bool directed=false){
		edge[from].emplace_back(to,cost);
		if(!directed) edge[to].emplace_back(from,cost);
	}
	void show(){
		rep(i,size)for(auto&[from,val]:edge[i])
			puta(i,"=>",from,", cost :",val);
	}
};

struct UnionFind{
	vl par,dist;
	UnionFind(int x){par.assign(x,-1); dist.assign(x,0);}
	ll find(ll x){return par[x]<0?x:find(par[x]);}
	ll depth(ll x){return par[x]<0?0:depth(par[x])+dist[x];}
	bool same(ll x,ll y){return find(x)==find(y);}
	ll size(ll x){return -par[find(x)];}
	ll diff(ll x,ll y){return same(x,y)?depth(x)-depth(y):LINF;}
	bool unite(ll x,ll y,ll k=0){
		k+=depth(y); k-=depth(x); k=-k;
		x=find(x); y=find(y);
		if(x==y)return false;
		if(size(x)<size(y)){swap(x,y);k=-k;}
		par[x]+=par[y]; par[y]=x; dist[y]=k;
		return true;
	}
};

template<class T=ll>struct Dijkstra{
	Graph<T> g;
	Dijkstra(Graph<T> g):g(g){}
	vector<T>dist(ll s){
		vector<T> ret(g.size, g.INF_VAL);
		priority_queue<tuple<T,ll>> q;
		q.emplace(T(),s);
		while(!q.empty()){
			auto[c,p]=q.top(); q.pop();
			if(ret[p]!=g.INF_VAL)continue;
			ret[p]=c=-c;
			for(auto&[nxt,cost]:g.edge[p]){
				if(ret[nxt]<=ret[p]+cost)continue;
				q.emplace(-ret[p]-cost,nxt);
			}
		}
		return ret;
	}
	T dist(ll s,ll t){return dist(s)[t];}
};

template<class T>struct Kruskal{
	Graph<T> g;
	Kruskal(Graph<T> g):g(g){}
	tuple<T,Graph<T>,vector<pll>> calc(){
		Graph<T> newg(g.size);
		vector<pll> unused;
		T ans=0;
		UnionFind uf(g.size);
		vector<tuple<T,ll,ll>> edge;
		rep(from,g.size)for(auto&[to,cost]:g.edge[from])edge.emplace_back(cost,from,to);
		sort(all(edge));
		for(auto&[cost,from,to]:edge){
			if(uf.unite(from,to)){
				ans+=cost;
				newg.add(from,to,cost);
			}else if(from<to){
				unused.emplace_back(from,to);
			}
		}
		return {ans,newg,unused};
	}
};


template<class T=ll>struct LCA{
	Graph<T> g;
	vvi parent;
	vi dist;
	LCA(Graph<T> g, int root=0):g(g){
		int K=1;
		while((1<<K)<g.size)K++;
		parent.assign(K, vi(g.size,-1));
		dist.assign(g.size, -1);
		dfs(root,-1,0);
		// dump("OK");
		rep(k,K-1)rep(v,g.size){
			parent[k + 1][v]=parent[k][v]<0 ? -1 : parent[k][parent[k][v]];
		}
	}
	void dfs(int v, int p, int d) {
		parent[0][v]=p, dist[v]=d;
		for(auto&[to,_]:g.edge[v])if(to!=p)dfs(to,v,d+1);
	}
	ll get(ll u, ll v){
		if(dist[u]<dist[v])swap(u,v);
		int K = parent.size();
		rep(k,K)if((dist[u]-dist[v])>>k&1)u=parent[k][u];
		if(u==v)return u;
		rrep(k,K)if(parent[k][u]!=parent[k][v])u=parent[k][u],v=parent[k][v];
		return parent[0][u];
	}
};

void Main(){
	geta(ll, n,m);
	Graph g(n);
	rep(i,m){
		geta(ll,a,b);
		g.add(a-1,b-1,1);
	}
	auto[_,tree,unused]=Kruskal(g).calc();

	set<int> heiro;
	each(e,unused){
		heiro.insert(e.first);
		heiro.insert(e.second);
	}

	map<pll,ll> hdist;
	each(a,heiro){
		vl d=Dijkstra(g).dist(a);
		each(b,heiro){
			hdist[{a,b}]=d[b];
		}
	}

	ll st=0;
	rep(i,n)if(tree.edge[i].size()==1){st=i;break;}

	LCA lca(tree,st);

	geta(ll,Q);
	auto dstf=[&](int a, int b){
		ll lc=lca.get(a,b);
		return lca.dist[a]+lca.dist[b]-2*lca.dist[lc];
	};
	
	loop(Q){
		geta(ll,a,b);
		a--;b--;
		ll lc=lca.get(a,b);
		ll ans=lca.dist[a]+lca.dist[b]-2*lca.dist[lc];

		each(s,heiro)each(t,heiro){
			chmin(ans, dstf(s,a) + hdist[{s,t}] + dstf(t,b));
		}
		puta(ans);
	}
}
