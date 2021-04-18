#pragma GCC target("avx")
#pragma GCC optimize("O3,inline,omit-frame-pointer,no-asynchronous-unwind-tables,fast-math")
#pragma GCC optimize("unroll-loops")

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
class Random{
	unsigned y;
	constexpr unsigned next(){return y^=(y^=(y^=y<<13)>>17)<<5;}
public:
	constexpr Random(const bool&isDeterministic):y(isDeterministic?2463534242:chrono::system_clock::now().time_since_epoch().count()){}
	constexpr int operator()(int a,int b){return next()%(b-a)+a;}
	constexpr ll operator()(ll a,ll b){return (((ull)next())<<32|next())%(b-a)+a;}
	constexpr double operator()(double a,double b){return (b-a)*next()/4294967296.0+a;}
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
	Timer& operator=(const Timer&) = default;
};
void wait(const int&msec){Timer tm(msec); while(tm);}

struct InputData{
	int l,n,m;
	vi r,p,a,b,c,d;

	void Input(){
		cin>>l>>n>>m;
		r.resize(n);
		p.resize(n);
		a.resize(m);
		b.resize(m);
		c.resize(m);
		d.resize(m);
		rep(i,n)cin>>r[i]>>p[i];
		rep(i,m){
			cin>>a[i]>>b[i]>>c[i]>>d[i];
			a[i]--; b[i]--;
		}
	}
};

struct OutputData{
	vi x,y,z;

	void Output(){
		rep(i,x.size()){
			puta(x[i],y[i],z[i]);
		}
	}


	inline bool isPlaced(int i){ return x[i]!=-1; }

	bool CheckInBoxSingle(InputData&in, int i){
		if(!isPlaced(i)) return true;
		if(x[i]-in.r[i]<0) return false;
		if(y[i]-in.r[i]<0) return false;
		if(z[i]-in.r[i]<0) return false;
		if(x[i]+in.r[i]>in.l) return false;
		if(y[i]+in.r[i]>in.l) return false;
		if(z[i]+in.r[i]>in.l) return false;
		return true;
	}

	inline bool CheckCollisionPair(InputData&in, int i, int j){
		return hypot(x[i]-x[j], y[i]-y[j], z[i]-z[j]) - EPS > in.r[i]+in.r[j];
	}

	tuple<bool, bool, bool> CheckCollisionSingle(InputData&in, int i){
		// 置けるか
		// ぶつかる場合、ほかの球すべての合計よりもスコアが大きくなるか
		// ぶつかる場合、ほかの球すべてより自分が小さいか
		bool ok=true,smaller=true;
		ll score=0;
		rep(j,in.n)if(i!=j){
			if(!CheckCollisionPair(in, i, j)){
				ok=false;
				score+=in.p[j];
				smaller &= in.r[i]<in.r[j];
			}
		}
		return {ok, score<in.p[i], smaller};
	}

	bool CheckValidSingle(InputData&in, int i){
		if(!CheckInBoxSingle(in,i))return false;
		if(auto [ok,score,small]=CheckCollisionSingle(in,i); !ok) return false;
		return true;
	}

	bool CheckValid(InputData&in){
		rep(i,in.n)if(!CheckValidSingle(in,i))return false;
		return true;
	}

	ll Score(InputData&in){
		// if(!CheckValid(in)) return 0;
		ll score=0;
		rep(i,in.n)if(isPlaced(i))score+=in.p[i];
		return score;
	}
};

class Solver : public InputData, OutputData{
public:
	Solver(int limitMsec) : InputData(), OutputData(), timer(limitMsec) {}
	void Solve(){
		Input();
		Init();
		while(timer){
			iteration++;
			Calc();
		}
		Output();
		dump(timer.get(), ",", iteration);
	}
	void Init();
	void Calc();
	int iteration = 0;
private:
	Timer timer;
};

void Solver::Init(){
	x.resize(n,-1);
	y.resize(n,-1);
	z.resize(n,-1);
}

void Solver::Calc(){
	int px,py,pz;
	rep(i,n){
		px=x[i], py=y[i], pz=z[i];
		x[i]=Random(r[i], l-r[i]+1);
		y[i]=Random(r[i], l-r[i]+1);
		z[i]=Random(r[i], l-r[i]+1);
		if(auto[ok,score,small]=CheckCollisionSingle(*this,i);!ok){
			if(score){//他を全てどかしてでもiを置いたほうが点数が良くなる
				rep(j,n)if(i!=j and !CheckCollisionPair(*this,i,j)) {
					x[j]=y[j]=z[j]=-1;
				}
			}else{
				x[i]=px, y[i]=py, z[i]=pz;
			}
		}
	}
}

void Main(){
	Solver solver(2950);
	solver.Solve();
}
