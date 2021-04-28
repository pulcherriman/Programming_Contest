#pragma region Perfect Template
#pragma region Unsecured Optimization
// #pragma GCC target("avx")
// #pragma GCC optimize("O3,inline,omit-frame-pointer,no-asynchronous-unwind-tables,fast-math")
// #pragma GCC optimize("unroll-loops")
#pragma endregion

#pragma region Include Headers
#if defined(ONLINE_JUDGE) || defined(_DEBUG)
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


#pragma endregion

int K=3;
Timer timer(1900);
ll solve(vl p, vvi edge){
	// if(!timer)return 0;
	// if(isZero)return 0;
	int n=p.size();
	// 点
	if(n==1)return K;

	UnionFind uf(n);
	vi deg(n,0);
	int ecount=0;
	rep(i,n)range(j,i+1,n)if(edge[i][j]){ deg[i]++; deg[j]++; uf.unite(i,j); ecount++; }

	// 非連結
	if(uf.size(0)!=n){
		dump("not connected",n);
		ll ans=1;
		vb checked(n,false);
		rep(i,n)if(!checked[i]){
			vl np;
			rep(j,n)if(uf.same(i,j)){ checked[j]=true; np.emplace_back(j); }
			auto nedge=vec(0,np.size(),np.size());
			rep(j,np.size())rep(k,np.size())nedge[j][k]=edge[np[j]][np[k]];
			iota(all(np),0);
			ll v=solve(np,nedge);
			if(v==0)return 0;
			ans*=v;
		}
		return ans;
	}

	// 木
	if(ecount==n-1){
		dump("tree",n);
		ll ans=K;
		loop(n-1)ans*=K-1;
		return ans;
	}

	// 完全グラフ
	if(ecount==n*(n-1)/2){
		dump("complete",n);
		ll ans=1;
		rep(i,n)ans*=K-i;
		return ans;
	}

	// 閉路
	bool isCycle=true;
	rep(i,n)isCycle&=deg[i]==2;
	if(isCycle){
		dump("closest",n);
		ll ans=1;
		loop(n)ans*=K-1;
		return ans+(n%2==0 ? K-1 : -K+1);
	}

	// 葉を取る
	ll ans=1;
	bool existLeaf=false;
	while(true){
		bool changed=false;
		rep(i,n)if(deg[i]==1){
			changed=existLeaf=true;
			rep(j,n)if(edge[i][j]){//ただ1つ
				ans*=K-1;
				edge[i][j]=edge[j][i]=0;
				deg[i]--; deg[j]--;
			}
		}
		if(!changed)break;
	}
	if(existLeaf){// なくなった頂点を一回消す　この操作で非連結にはなっていない
		dump("leaf",n);
		vl np;
		rep(i,n)if(deg[i])np.emplace_back(i);
		n=np.size();
		auto nedge=vec(0,n,n);
		rep(j,n)rep(k,n)nedge[j][k]=edge[np[j]][np[k]];
		iota(all(np),0);
		return ans*solve(np,nedge);
	}

	// 連結かつ全頂点の次数が2以上：縮約
	// 次数最小の頂点から消していく
	int mindeg=n+1, index=0;
	rep(i,n)if(chmin(mindeg,deg[i]))index=i;
	if(index!=n-1){	// n-1番に寄せる
		swap(edge[index],edge[n-1]);
		rep(i,n)swap(edge[i][index],edge[i][n-1]);
	}

	rep(i,n)if(edge[i][n-1]){//辺i~(n-1)を取り除く
		dump("syukuyaku",n);
		edge[i][n-1]=edge[n-1][i]=0;
		ans=solve(p,edge);
		if(ans==0)return 0;
		dump(ans, edge);
		
		//縮約
		bool changed=false;
		rep(j,n-1){
			if(i!=j and edge[j][n-1]){
				if(edge[i][j]==0)changed=true;
				edge[i][j]=edge[j][i]=1;
			}
			edge[j].pop_back();
		}
		edge.pop_back();
		p.pop_back();

		ans-=solve(p,edge);
		return ans;
	}
	return 0;
}

void Main(){
	geta(ll, n, m);
	auto edge=vec(0,n,n);
	loop(m){
		geta(ll,a,b);
		a--; b--;
		edge[a][b]=edge[b][a]=1;
	}
	vl p(n);
	iota(all(p),0);
	
	puta(solve(p,edge));
}
