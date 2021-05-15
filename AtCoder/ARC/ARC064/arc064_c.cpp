#pragma region Perfect Template
#pragma region Unsecured Optimization
// #pragma GCC target("avx")
// #pragma GCC optimize("O3,inline,omit-frame-pointer,no-asynchronous-unwind-tables,fast-math")
// #pragma GCC optimize("unroll-loops")
#ifdef _DEBUG
#define _GLIBCXX_DEBUG 1
#endif
#pragma endregion

#pragma region Include Headers
#if defined(EVAL) || defined(ONLINE_JUDGE) || defined(_DEBUG)
#include <atcoder/all>
using namespace atcoder;
#endif
#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;

void Main();
int main(){cin.tie(nullptr);ios::sync_with_stdio(false);Main();return 0;}
#pragma endregion

#pragma region Additional Type Definition
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
using pll=pair<ll,ll>;
using tll=tuple<ll,ll>;
using tlll=tuple<ll,ll,ll>;
using vs=vector<string>;
template<class K> using IndexedSet=__gnu_pbds::tree<K,__gnu_pbds::null_type,less<K>,__gnu_pbds::rb_tree_tag,__gnu_pbds::tree_order_statistics_node_update>;
template<class K> using HashSet=__gnu_pbds::gp_hash_table<K,__gnu_pbds::null_type>;
template<class K,class V> using IndexedMap=__gnu_pbds::tree<K,V,less<K>,__gnu_pbds::rb_tree_tag,__gnu_pbds::tree_order_statistics_node_update>;
template<class K,class V> using HashMap=__gnu_pbds::gp_hash_table<K,V>;
#pragma endregion

#pragma region Macros
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
#pragma endregion

#pragma region Constants
constexpr ll LINF=1ll<<60;
constexpr int INF=1<<30;
constexpr double EPS=(1e-9);
constexpr ll MOD=1000000007ll;
constexpr long double PI=3.14159265358979323846;
#pragma endregion

#pragma region Output Assist
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
#pragma endregion

#pragma region Input Assist
template<class S>auto&operator>>(istream&is,vector<S>&t){for(S&a:t)cin>>a;return is;}
template<typename...S>void geta_(S&...s){((cin>>s),...);}
#define geta(t,...) t __VA_ARGS__;geta_(__VA_ARGS__)
template<class T,class...Args>auto vec(T x,int arg,Args...args){if constexpr(sizeof...(args)==0)return vector(arg,x);else return vector(arg,vec(x,args...));}
#define getv(a,...) auto a=vec(__VA_ARGS__);cin>>a
#pragma endregion

#pragma region Utilities
template<class T>constexpr bool chmax(T&a,T b){return a<b?a=b,1:0;}
template<class T>constexpr bool chmin(T&a,T b){return a>b?a=b,1:0;}
template<class S>S sum(vector<S>&a){return accumulate(all(a),S());}
template<class S>S max(vector<S>&a){return *max_element(all(a));}
template<class S>S min(vector<S>&a){return *min_element(all(a));}
template<class T>T gcd(vector<T> v){return accumulate(all(v),T(),gcd<T,T>);}
template<class T> pair<int,T> getMaxAndIndex(vector<T> a){
	int p=-1; T v=numeric_limits<T>::min();
	rep(i,a.size())if(chmax(v,a[i]))p=i;
	return {p,v};
}
#pragma endregion
#pragma endregion

// ここにライブラリを貼る
// regionのfoldは[Ctrl+K] => [Ctrl+8] expandは9
#pragma region Additional Libraries
template<class T=ll>struct Graph{
	int size;
	T INF_VAL;
	vector<vector<tuple<ll,T>>>edge;
	Graph(int n=1,T inf=LINF):size(n),INF_VAL(inf){edge.resize(size);}
	void add(ll from, ll to, T cost, bool directed=false){
		edge[from].emplace_back(to,cost);
		if(!directed) edge[to].emplace_back(from,cost);
	}
	friend ostream &operator<<(ostream &os, const Graph<T> &g) {
		rep(i,g.size)for(auto[from,val]:g.edge[i])puta(make_tuple(i,"=>",from,", cost :",val),os);
		return os;
	}
	static pair<int,Graph<T>> input(bool directed=false){
		geta(int,n,m);
		Graph<T> g(n);
		rep(m){
			geta(int,a,b);
			g.add(a-1,b-1,1,directed);
		}
		return {n,g};
	}
	static pair<int,Graph<T>> inputWeighted(bool directed=false){
		geta(int,n,m);
		Graph<T> g(n);
		rep(m){
			geta(int,a,b); geta(T,c);
			g.add(a-1,b-1,c,directed);
		}
		return {n,g};
	}

	struct DFSResult{
		vb connected;
		vector<T> distance;
		vl preorder, postorder, eulertour, subtreeCount;
		DFSResult(Graph<T>&g):
			connected(g.size,false),
			distance(g.size,g.INF_VAL),
			preorder(g.size,-1),
			postorder(g.size,-1),
			subtreeCount(g.size,1){
				eulertour.reserve(g.size*2);
			}
	};
	// s始点で深さ優先探索して情報を返す。木以外で使うのか？
	// この関数は変更しない
	DFSResult dfs(int s){
		int pre=0,post=0;
		DFSResult ret(*this);
		ret.distance[s]=0;
		function<void(int)> dfsrec=[&](int p){
			ret.connected[p]=true;
			ret.preorder[p]=pre++;
			ret.eulertour.emplace_back(p);
			for(auto[to,cost]:edge[p])if(!ret.connected[to]){
				ret.distance[to]=ret.distance[p]+cost;
				dfsrec(to);
				ret.subtreeCount[p]+=ret.subtreeCount[to];
			}
			ret.postorder[p]=post++;
			ret.eulertour.emplace_back(p);
		};
		dfsrec(s);
		return ret;
	};
	// BFSする。この関数は変更しない
	vector<T> bfs(int s){
		vector<T> ret(size,INF_VAL);
		queue<int> q;
		ret[q.emplace(s)]=0;
		while(!q.empty()){
			int p=q.front(); q.pop();
			for(auto[to,cost]:edge[p])if(ret[to]==INF_VAL)ret[q.emplace(to)]=ret[p]+cost;
		}
		return ret;
	}
	// BFSしてパスを復元する。
	// 余分にO(N)掛けてるので、距離だけほしい場合はbfs(s)[t]を見るとよい
	pair<T,vi> bfs(int s, int t){
		auto dist=bfs(s);
		vi path(1,t);
		while(path.back()!=s)for(auto[to,_]:edge[path.back()])if(dist[to]==dist[path.back()]-1){path.emplace_back(to);break;}
		reverse(all(path));
		return {dist[t], path};
	}
};

template<class Cell=int>struct GridGraph : public Graph<int>{
	static constexpr int dy[8]={0,1,0,-1,1,1,-1,-1};
	static constexpr int dx[8]={1,0,-1,0,1,-1,-1,1};
	static constexpr char dirstr[]="RDLU";
	int h,w;
	bool outLine;
	vector<Cell> field;
	typename vector<Cell>::iterator operator[](int i) { return field.begin() + i * w; }
	inline Cell &at(int i, int j) { return field[i*w+j]; }
	inline Cell get(int i, int j) const { return field[i*w+j]; }
	GridGraph(int _h, int _w, bool needOutline=true):Graph(1,0),h(_h),w(_w),outLine(needOutline){
		if(needOutline){
			h+=2; w+=2;
			field.resize(h*w,0);
			rep(i,h)at(i,0)=at(i,w-1)=-1;
			rep(j,w)at(0,j)=at(h-1,j)=-1;
		}else field.resize(h*w,0);
	}
	void inputMap(){
		char c;
		rep(i,h)rep(j,w){cin>>c; at(i+outLine,j+outLine)=(c=='#'?-1:0);}
		create();
	}
	void create(){
		edge.clear();
		edge.resize(size=h*w);
		rep(i,1,h-1)rep(j,1,w-1)if(field[i][j]=='.'){
			if(field[i+1][j]=='.')add(i*w+j, i*w+j+w, 1);
			if(field[i][j+1]=='.')add(i*w+j, i*w+j+1, 1);
		}
	}
	friend ostream &operator<<(ostream &os, const GridGraph<Cell> &g) {
		rep(i,g.h){rep(j,g.w)os<<(g.get(i,j)==-1?'#':' ');os<<endl;}
		return os;
	}
	vector<pair<int,int>> neighbor4(int y, int x, Cell v){
		vector<pair<int,int>> p;
		rep(i,4)if(get(y+dy[i],x+dx[i])==v)p.emplace_back(y+dy[i],x+dx[i]);
		return p;
	}
	vector<pair<int,int>> neighbor8(int y, int x, Cell v){
		vector<pair<int,int>> p;
		rep(i,8)if(get(y+dy[i],x+dx[i])==v)p.emplace_back(y+dy[i],x+dx[i]);
		return p;
	}
};

template<class T=ll>struct Tree : public Graph<T>{
	Tree(int n, T inf=LINF):Graph<T>(n,inf){}

	static pair<int,Tree<T>> input(bool directed=false){
		geta(int,n);
		Tree<T> g(n);
		rep(n-1){
			geta(int,a,b);
			g.add(a-1,b-1,1,directed);
		}
		return {n,g};
	}

	static pair<int,Tree<T>> inputWeighted(bool directed=false){
		geta(int,n);
		Tree<T> g(n);
		rep(n-1){
			geta(int,a,b); geta(T,c);
			g.add(a-1,b-1,c,directed);
		}
		return {n,g};
	}

	pair<T,vi> diameter(){
		if(_diameter.first==this->INF_VAL){
			auto [s,_]=getMaxAndIndex(this->bfs(0));
			auto [t,w]=getMaxAndIndex(this->bfs(s));
			_diameter=this->bfs(s,t);
		}
		return _diameter;
	}
private:
	pair<T,vi> _diameter = {this->INF_VAL, vi()};
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
			ret[p]=-c;
			for(auto&[nxt,cost]:g.edge[p]){
				if(ret[nxt]<=ret[p]+cost)continue;
				q.emplace(-ret[p]-cost,nxt);
			}
		}
		return ret;
	}
	T dist(ll s,ll t){return dist(s)[t];}
};

#pragma endregion


void Main(){
	fcout(10);
	geta(ll, sx,sy,tx,ty,n);
	getv(p,0.L,n,3);

	Graph<ld> g(n+2);
	g.add(n,n+1,hypot(tx-sx, ty-sy));
	rep(i,n){
		g.add(n,i,max(hypot(p[i][0]-sx, p[i][1]-sy)-p[i][2], 0.L));
		g.add(n+1,i,max(hypot(p[i][0]-tx, p[i][1]-ty)-p[i][2], 0.L));
		rep(j,i+1,n){
			g.add(i,j,max(hypot(p[i][0]-p[j][0], p[i][1]-p[j][1])-p[i][2]-p[j][2], 0.L));
		}
	}

	puta(Dijkstra(g).dist(n,n+1));
}
