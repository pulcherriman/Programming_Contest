#pragma region Perfect Template
#pragma region Unsecured Optimization
// #pragma GCC target("avx")
// #pragma GCC optimize("O3,inline,omit-frame-pointer,no-asynchronous-unwind-tables,fast-math")
// #pragma GCC optimize("unroll-loops")
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
using vb=vector<char>;
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
#pragma endregion

#pragma region Macros
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
	virtual void show(){
		rep(i,size)for(auto&[from,val]:edge[i])
			puta(i,"=>",from,", cost :",val);
	}
	// 強連結成分分解
	// return: {縮約後のDAG, 元々i番目の頂点がDAG上で何番目に縮約されたか？}
	pair<Graph<T>, vi> scc(){
		vi visit(size,0),backward,group(size);
		function<void(int)> dfs=[&](int p){
			visit[p]=1;
			for(auto&[to,_]:edge[p])if(!visit[to])dfs(to);
			backward.emplace_back(p);
		};
		Graph ginv(size);
		rep(i,size){
			if(!visit[i])dfs(i);
			for(auto&[to,_]:edge[i])ginv.add(to,i,1,true);
		}
		fill(all(visit),0);
		ll pcnt=0;
		function<void(int)> dfs2=[&](int p){
			visit[p]=1, group[p]=pcnt;
			for(auto&[to,_]:ginv.edge[p])if(!visit[to])dfs2(to);
		};
		rrep(i,size)if(!visit[backward[i]]){
			dfs2(backward[i]);
			pcnt++;
		}
		Graph r(pcnt);
		rep(i,size)for(auto&[to,_]:edge[i])if(group[i]!=group[to])r.add(group[i],group[to],1,true);
		return {r,group};
	}
};

struct GridGraph : public Graph<int>{
	int h,w;
	vs field;
	GridGraph(int h, int w):Graph(1,0),h(h),w(w){field.resize(h);}
	void input(bool needOutline=true){
		rep(i,h)cin>>field[i];
		if(needOutline){
			field.resize(h+2);
			rrep(i,h)field[i+1]='#'+field[i]+'#';
			field[0]=field[h+1]=string(w+2,'#');
			h+=2; w+=2;
		}
		create();
	}
	void create(){
		edge.clear();
		edge.resize(size=h*w);
		range(i,1,h-1)range(j,1,w-1)if(field[i][j]=='.'){
			if(field[i+1][j]=='.')add(pos2index(i,j,w), pos2index(i+1,j,w), 1);
			if(field[i][j+1]=='.')add(pos2index(i,j,w), pos2index(i,j+1,w), 1);
		}
	}
	void show() override{ each(s,field)puta(s); }
private:
	static constexpr int pos2index(int y, int x, int w){ return y*w+x; }
};

template<class T=ll>struct Tree : public Graph<T>{
	Tree(int n, T inf=LINF):Graph<T>(n,inf){}

	pair<T,vi> diameter(){
		// if(_diameter.first==this->INF_VAL){
		// 	BFS bfs(*this);
		// 	auto [s,_]=getMaxAndIndex(bfs.calc(0));
		// 	auto [t,w]=getMaxAndIndex(bfs.calc(s));
		// 	_diameter=bfs.calc(s,t);
		// }
		return _diameter;
	}
private:
	pair<T,vi> _diameter = {this->INF_VAL, vi()};
};

#pragma endregion


void Main(){
	geta(ll, n,m);
	Graph g(n);
	loop(m){
		geta(ll,a,b);
		a--;b--;
		g.add(a,b,1,true);
	}

	auto[rg,group]=g.scc();

	ll ans=0;
	vl res(rg.size,0);
	rep(i,n)res[group[i]]++;
	for(auto i:res)ans+=i*(i-1)/2;
	puta(ans);	
}
