/*
 * Unsecured Optimization
 */
// #pragma GCC target "avx" /* SIMD(ベクトル化) */
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native") /* 浮動小数点数のSIMD */
// #pragma GCC optimize "O3" /* 最適化 */
// #pragma GCC optimize "fast-math"
// #pragma GCC optimize "unroll-loops" /* ループの展開 */
#ifdef _DEBUG
#define _GLIBCXX_DEBUG 1
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

void Main();
int main(){cin.tie(nullptr);ios::sync_with_stdio(false);Main();return 0;}

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
using pll=pair<ll,ll>;
using vp=vector<pll>;
using tl2=tuple<ll,ll>;
using tl3=tuple<ll,ll,ll>;
using vs=vector<string>;
template<class K> using IndexedSet=__gnu_pbds::tree<K,__gnu_pbds::null_type,less<K>,__gnu_pbds::rb_tree_tag,__gnu_pbds::tree_order_statistics_node_update>;
template<class K> using HashSet=__gnu_pbds::gp_hash_table<K,__gnu_pbds::null_type>;
template<class K,class V> using IndexedMap=__gnu_pbds::tree<K,V,less<K>,__gnu_pbds::rb_tree_tag,__gnu_pbds::tree_order_statistics_node_update>;
template<class K,class V> using HashMap=__gnu_pbds::gp_hash_table<K,V>;

/*
 * Macros
 */
#define all(a) a.begin(),a.end()
#define rall(a) a.rbegin(),a.rend()
#define __LOOPSWITCH(_1, _2, _3, __LOOPSWITCH, ...) __LOOPSWITCH
#define rep(...) __LOOPSWITCH(__VA_ARGS__, __RANGE, __REP, __LOOP) (__VA_ARGS__)
#define rrep(...) __LOOPSWITCH(__VA_ARGS__, __RRANGE, __RREP, __LOOP) (__VA_ARGS__)
#define __LOOP(q) __LOOP2(q, __LINE__)
#define __LOOP2(q,l) __LOOP3(q,l)
#define __LOOP3(q,l) __REP(_lp ## l,q)
#define __REP(i,n) __RANGE(i,0,n)
#define __RANGE(i,a,n) for(int i=((ll)a);i<((ll)n);++i)
#define __RREP(i,n) __RRANGE(i,0,n)
#define __RRANGE(i,a,n) for(int i=((ll)n-1);i>=((ll)a);--i)
#define repsq(i,n) for(ll i=0;i*i<=n;++i)
#define each(v,a) for(auto v:a)
#define eachref(v,a) for(auto&v:a)
#define fcout(a) cout<<setprecision(a)<<fixed

/*
 * Constants
 */
constexpr ll LINF=1ll<<60;
constexpr int INF=1<<30;
constexpr double EPS=(1e-9);
constexpr ll MOD=1000000007ll;
constexpr long double PI=3.14159265358979323846;

/*
 * Output Assist
 */
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

/*
 * Input Assist
 */
template<class S,class T>auto&operator>>(istream&is,pair<S,T>&p){is>>p.first>>p.second;return is;}
template<class S>auto&operator>>(istream&is,vector<S>&t){for(S&a:t)is>>a;return is;}
template<typename...S>void geta_(S&...s){((cin>>s),...);}
#define geta(t,...) t __VA_ARGS__;geta_(__VA_ARGS__)
template<class T,class...Args>auto vec(T x,int arg,Args...args){if constexpr(sizeof...(args)==0)return vector(arg,x);else return vector(arg,vec(x,args...));}
#define getv(a,...) auto a=vec(__VA_ARGS__);cin>>a

/*
 * Utilities
 */
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

// ここにライブラリを貼る
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
	Timer(uint64_t _limit): start(getClocks()),limit(start+_limit*ClocksPerMsec) {}
	uint64_t get() const{return (getClocks()-start)/ClocksPerMsec;}
	operator bool()const{return getClocks()<limit;}
};
void wait(const int&msec){Timer tm(msec); while(tm);}

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

constexpr int TLE=1930;

struct P {
	int y,x;
	void input(){
		cin>>y>>x;
	}
};

struct Mino {
	int h, w, c;
	vs form;
	void input() {
		cin>>h>>w>>c;
		form.resize(h);
		cin>>form;
	}
};

const int dy[]={0,1,0,-1};
const int dx[]={1,0,-1,0};
int b;
vector<Mino> minoInfo;
struct Field {
	int offy=0,offx=0;
	const int n=50;
	int k;
	vector<P> points;
	vvb f;
	vvb pf;

	vvi minos;
	void input() {
		int _;
		cin>>_>>k>>b;
		points.resize(k);
		rep(i,k)points[i].input();
		f=vvb(n,vb(n,0));
		pf=vvb(n,vb(n,0));
		rep(i,k){
			pf[points[i].y][points[i].x]=1;
		}
	}

	void clear() {
		f=vvb(n,vb(n,0));
		minos.clear();
	}

	void place(int index, int y, int x){
		minos.push_back({index+1, y, x});
		auto mino=minoInfo[index];
		rep(h,mino.h)rep(w,mino.w)if(mino.form[h][w]=='#'){
			f[y+h][x+w]=1;
		}
	}

	void connectSingle(){
		for(auto&p:points){
			vvi visited(n,vi(n,-1));
			// puta("===");
			// puta(p.y, p.x);

			if(f[p.y][p.x])continue;
			queue<tl3> q;
			q.emplace(p.y, p.x, 0);
			int toy,tox;
			while(!q.empty()){
				auto[y,x,c]=q.front(); q.pop();
				if(visited[y][x]!=-1)continue;
				visited[y][x]=c;
				if(f[y][x]){
					toy=y, tox=x;
					break;
				}
				rep(v,4){
					unsigned int ny=y+dy[v], nx=x+dx[v];
					if(ny>=n or nx>=n)continue;
					if(visited[ny][nx]!=-1)continue;
					q.emplace(ny,nx,c+1);
				}
			}

			// puta(visited);
			// puta(p.y,p.x, toy,tox);

			while(!q.empty())q.pop();
			q.emplace(toy,tox,0);
			while(!q.empty()){
				auto[y,x,_]=q.front(); q.pop();
				// if()
				rep(v,4){
					unsigned int ny=y+dy[v], nx=x+dx[v];
					if(ny>=n or nx>=n)continue;
					if(visited[ny][nx]+1==visited[y][x]){
						if(!f[ny][nx])place(0,ny,nx);
						// puta(0,ny,nx);
						// puta(ny,nx,visited[ny][nx]);
						if(visited[ny][nx]==0)break;
						q.emplace(ny,nx,0);
						break;
					}
				}
			}
		}
	}

	void connectAllMino(int index){
		set<pll> st;
		auto mino=minoInfo[index];
		UnionFind uf((n/mino.h)*(n/mino.w));

		int sy,sx;
		rep(h,mino.h)rep(w,mino.w)if(mino.form[h][w]=='#'){
			sy=h,sx=w;
			h=w=INF;
		}

		rep((n/mino.h)*(n/mino.w)){
			int iscurind=0;
			deque<tl3> q;
			q.emplace_back(sy,sx,0);
			vvi visited(n,vi(n,-1));
			int toy,tox;
			while(!q.empty()){
				auto[y,x,c]=q.front(); q.pop_front();
				if(visited[y][x]!=-1)continue;
				visited[y][x]=c;
				if(f[y][x]){
					toy=y, tox=x;
					int istoind=(toy/mino.h)*(n/mino.w)+(tox/mino.w);
					if(!uf.same(0,istoind)){
						uf.unite(0,istoind);
						break;
					}
				}
				rep(v,4){
					unsigned int ny=y+dy[v], nx=x+dx[v];
					if(ny>=n or nx>=n)continue;
					if(visited[ny][nx]!=-1)continue;
					if(f[ny][nx]){
						q.emplace_front(ny,nx,c);
					}else{
						q.emplace_back(ny,nx,c+1);
					}
					
				}
			}

			while(!q.empty())q.pop_front();
			q.emplace_back(toy,tox,0);
			while(!q.empty()){
				auto[y,x,_]=q.front(); q.pop_front();

				rep(v,4){
					unsigned int ny=y+dy[v], nx=x+dx[v];
					if(ny>=n or nx>=n)continue;
					if(visited[ny][nx]==-1)continue;
					if(visited[ny][nx]==visited[y][x]){
						if(!f[ny][nx]){
							place(0,ny,nx);
						}
						if(visited[ny][nx]==0)break;
						q.emplace_back(ny,nx,0);
					}
					if(visited[ny][nx]<visited[y][x]){
						if(!f[ny][nx]){
							place(0,ny,nx);
						}
						if(visited[ny][nx]==0)break;
						q.emplace_back(ny,nx,0);
					}
				}
				visited[y][x]=-1;
			}
		}
	}

	void initialize(int index){
		clear();
		auto mino=minoInfo[index];
		rep(i,n/mino.h)rep(j,n/mino.w){
			bool ok=false;
			rep(h,mino.h)rep(w,mino.w){
				int y=i*mino.h+h, x=j*mino.w+w;
				place(index, i*mino.h, j*mino.w);
				h=INF,w=INF;
			}
		}
		connectAllMino(index);
		connectSingle();
	}

	int calc(){
		int v=0;
		for(auto mino:minos){
			v+=minoInfo[mino[0]-1].c;
		}
		return v;
	}

	void output(){
		puta(minos.size());
		puta(minos);
	}
};


void Main(){
	Timer timer(TLE);

	Field field;
	field.input();
	minoInfo.resize(b);
	rep(i,b)minoInfo[i].input();

	int minscore=INF;
	vvi ans;
	int i=0;
	while(timer){
		field.initialize(i);
		if(chmin(minscore, field.calc())){
			ans=field.minos;
		}
		i++;
		if(i==b)i=0;
	}
	field.minos=ans;
	field.output();

}