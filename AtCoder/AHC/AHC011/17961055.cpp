#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("inline")
#pragma GCC diagnostic ignored "-Wunused-value"


/* 
 * Include Headers
 */
#include<bits/stdc++.h>
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

template<class V> using minpq = priority_queue<V, vector<V>, greater<V>>;

#define all(a) begin(a),end(a)
#define rall(a) rbegin(a),rend(a)
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
#define sz(a) ((int)(a).size())

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
template<class T>constexpr bool chmax(T&a,T b){return a<b?a=b,1:0;}
template<class T>constexpr bool chmin(T&a,T b){return a>b?a=b,1:0;}
template<class S>S sum(vector<S>&a){return accumulate(all(a),S());}
template<class S>S max(vector<S>&a){return *max_element(all(a));}
template<class S>S min(vector<S>&a){return *min_element(all(a));}

namespace IO {
	// container detection
	template<typename T, typename _=void> struct is_container : false_type {};
	template<> struct is_container<string> : false_type {};
	template<typename...Ts> struct is_container_helper {};
	template<typename T> struct is_container<T, conditional_t<
		true, void, is_container_helper<
			typename T::value_type, typename T::size_type, typename T::iterator,
			decltype(declval<T>().size()),
			decltype(declval<T>().begin()),
			decltype(declval<T>().end()) >>> : public true_type {};
	template<typename T,
		typename enable_if<is_container<T>{}, nullptr_t>::type = nullptr,
		char Separator = is_container<typename T::value_type>{} ? '\n' : ' ' >
	constexpr ostream&operator<<(ostream&os, T t){
		if(auto b=begin(t), e=end(t) ; !t.empty()) for(os<<(*b++);b!=e;os<<Separator<<(*b++)) ;
		return os;
	}

	// output
	template<class T, class...Ts> constexpr ostream& pargs(ostream&os, T&&t, Ts&&...args); // support clang
	template<class S,class T>constexpr ostream&operator<<(ostream&os,pair<S,T>p){ return os<<'['<<p.first<<", "<<p.second<<']'; };
	template<class...Ts>constexpr ostream&operator<<(ostream&os,tuple<Ts...>t){
		return apply([&os](auto&&t,auto&&...args)->ostream&{return pargs(os, t, args...);}, t);
	};
	template<class T, class...Ts> constexpr ostream& pargs(ostream&os, T&&t, Ts&&...args) {
		return ((os<<t)<<...<<(os<<' ', args));
	}

	template<class...Ts> constexpr ostream& out(Ts...args) { return pargs(cout, args...)<<'\n'; }
	template<class...Ts> constexpr ostream& debug_f(Ts...args) { return pargs(cerr, args...)<<'\n'; }
	#ifdef _DEBUG
	template<class...Ts> constexpr ostream& debug(Ts...args) { return pargs(cerr, args...)<<'\n'; }
	#else
	#define debug(...) if(false)debug_f(__VA_ARGS__)
	#endif
	void Yn(bool f) { out(f?"Yes":"No"); }

	// input
	template<class T, class...Ts> constexpr istream& gargs(istream&is, T&&t, Ts&&...args) {
		return ((is>>t)>>...>>args);
	}
	template<class S,class T>auto&operator>>(istream&is,pair<S,T>&p){return is>>p.first>>p.second;}
	template<class...Ts>constexpr istream&operator>>(istream&is,tuple<Ts...>&t){
		return apply([&is](auto&&t,auto&&...args)->istream&{return gargs(is, t, args...);}, t);
	};

	template<typename...S>auto&in(S&...s){return gargs(cin, s...);}
	#define def(t,...) t __VA_ARGS__; in(__VA_ARGS__)
	template<typename T, typename enable_if<is_container<T>{}, nullptr_t>::type = nullptr>
	auto&operator>>(istream&is,T&t){for(auto&a:t)is>>a; return is;}
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
	uint64_t get() const{return (getClocks()-start)/ClocksPerMsec;}
	operator bool()const{return getClocks()<limit;}
};
void wait(const int&msec){Timer tm(msec); while(tm);}

struct Mgr {
	static const int TLE = 3000;
	static inline Timer timer = Timer(TLE-100);
	Mgr() {
		ios_base::sync_with_stdio(0); cin.tie(0);
		cout<<fixed<<setprecision(11);
		cerr<<fixed<<setprecision(3);
	}
	~Mgr(){
		debug_f(timer.get(), "ms")<<flush;
	}
} _manager;

struct UnionFind{
	vi par,dist;
	UnionFind(int x){par.assign(x,-1); dist.assign(x,0);}
	int find(int x){return par[x]<0?x:find(par[x]);}
	int depth(int x){return par[x]<0?0:depth(par[x])+dist[x];}
	bool same(int x,int y){return find(x)==find(y);}
	int size(int x){return -par[find(x)];}
	int diff(int x,int y){return same(x,y)?depth(x)-depth(y):INF;}
	bool unite(int x,int y,int k=0){
		k+=depth(y); k-=depth(x); k=-k;
		x=find(x); y=find(y);
		if(x==y)return false;
		if(size(x)<size(y)){swap(x,y);k=-k;}
		par[x]+=par[y]; par[y]=x; dist[y]=k;
		return true;
	}
};

enum DIR {
	LEFT = 1,
	UP = 2,
	RIGHT = 4,
	DOWN = 8,
};

const int InverseInt[]={0,2,3,0,0,0,0,0,1};

int n,t;
struct Field{
private:
	vl a;
	vl compressedMove;
public:
	int mvLength=0,by,bx;
	friend bool operator<(const Field&l, const Field&r){
		return l.mvLength>r.mvLength;
	};
	Field(vl&_a):a(_a){
		rep(i,n)rep(j,n)if(get(i,j)==0){by=i; bx=j; return;}
	}
	void addMove(ll dirIndex){
		if((mvLength&31)==0)compressedMove.emplace_back(dirIndex);
		else{
			const int shift = (mvLength&31)*2;
			compressedMove.back() &= ~(3ll<<shift);
			compressedMove.back() |= dirIndex<<shift;
		}
		mvLength++;
	}
	void removeMove(){
		mvLength--;
		if((mvLength&31)==0)compressedMove.pop_back();
	}
	int lastMove(){
		return (compressedMove.back()>>(((mvLength-1)&31)*2))&3;
	}
	bool move(DIR d){
		if(mvLength and lastMove()==InverseInt[d]){
			return false;
		}
		switch(d){
			case RIGHT: 
				if(bx+1==n)return false;
				addMove(2);
				swap(by, bx, by, bx+1); ++bx; break;
			case UP:
				if(by==0)return false;
				addMove(1);
				swap(by, bx, by-1, bx); --by; break;
			case LEFT:
				if(bx==0)return false;
				addMove(0);
				swap(by, bx, by, bx-1); --bx; break;
			case DOWN:
				if(by+1==n)return false;
				addMove(3);
				swap(by, bx, by+1, bx); ++by; break;
		}
		return true;
	}
	bool back(){
		switch(lastMove()){
			case 2: swap(by, bx, by, bx-1); --bx; break;
			case 1: swap(by, bx, by+1, bx); ++by; break;
			case 0: swap(by, bx, by, bx+1); ++bx; break;
			case 3: swap(by, bx, by-1, bx); --by; break;
		}
		removeMove();
		return true;
	}
	bool random_walk(){
		return move((DIR)(1<<Random(0,4)));
	}
	inline ll get(int i, int j){
		return (a[i]>>(j*4))&15;
	}
	void swap(int i1, int j1, int i2, int j2){
		ll d=get(i1,j1);
		a[i1]&=~(15ll<<(j1*4));
		a[i1]|=get(i2,j2)<<(j1*4);
		a[i2]&=~(15ll<<(j2*4));
		a[i2]|=d<<(j2*4);
	}
	string getString() {
		string ret, val="LURD";
		rep(i,mvLength){
			ret+=val[(compressedMove[i/32]>>((i&31)*2))&3];
		}
		return ret;
	}
};

int calcCount=0;
int calculate(Field&f) {
	calcCount++;
	int ret=1;
	UnionFind uf(n*n);
	rep(i,n)rep(j,n){
		if(j!=n-1 and (f.get(i,j)&DIR::RIGHT) and (f.get(i,j+1)&DIR::LEFT)){
			if(!uf.unite(i*n+j,i*n+j+1)) {
				return 0;
			}
		}
		if(i!=n-1 and (f.get(i,j)&DIR::DOWN) and (f.get(i+1,j)&DIR::UP)){
			if(!uf.unite(i*n+j,(i+1)*n+j)) {
				return 0;
			}
		}
		chmax(ret, (int)uf.size(i*n+j));
	}
	return ret;
}

void display(Field&f){
	const static int d[3][3]={
		{0,2,0},
		{1,15,4},
		{0,8,0}
	};
	rep(i,n)rep(h,3){
		rep(j,n)rep(w,3){
			if(f.get(i,j) & d[h][w])cerr<<"##";
			else cerr<<"  ";
		}
		cerr<<"\n";
	}
}

int main() {
	/* N=6,7,8,9,10 のケースで、木を作る
	 * T=2*N^3 回以内の操作で達成せよ
	 * T 回以内の操作により、(N−1,N−1) に空きマスを配置した状態の、大きさ N ^2−1 の木を作成出来ることは保証されている
	 * スコアは、全域木を作れなかった場合500000*木の大きさの割合
	 * 全域木の場合、500000*(2-操作回数/T)
	 */
	cin>>n>>t;
	const int maxTurn = 200;
	vl init(n);
	{
		string s;
		rep(i,n){
			cin>>s;
			reverse(all(s));
			init[i]=stoll(s,nullptr,16);
		}
	}
	
	vector<vector<pair<int, Field>>> q(maxTurn+1);
	Field f(init);
	q[0].emplace_back(calculate(f), f);

	int maxScore = 0;
	Field answer=f;

	// const int beam_width = 5000;
	const int bwList[]={
		5000,1,10,
		20,30,40,50,60,70,80,90,100,
		200,300,400,500,600,700,800,900,1000,
		2000,3000,4000,5000,6000,7000,8000,9000,10000,
	};
	for(auto&beam_width:bwList){
		rep(i,maxTurn){
			if(q[i].size()>beam_width){
				sort(rall(q[i]));
				q[i].erase(q[i].begin()+beam_width, q[i].end());
				q[i].shrink_to_fit();
			}
			for(auto&[score,field]:q[i]){
				rep(j,4){
					if(!field.move((DIR)(1<<j)))continue;
					int ns=calculate(field);
					if(chmax(maxScore, ns)){
						answer = field;
					}
					q[i+1].emplace_back(ns, field);
					field.back();
					if(!Mgr::timer)break;
				}
				if(!Mgr::timer)break;
			}
			
			q[i].erase(q[i].begin()+1, q[i].end());
			q[i].shrink_to_fit();
			if(!Mgr::timer)break;
			sort(rall(q[i+1]));
		}
		if(!Mgr::timer)break;
		debug("DEPTH", beam_width, calculate(answer));

		rep(i,maxTurn+1){
			out(i, q[i].size());
		}
		break;
	}

	debug_f("Score:", maxScore);
	display(answer);
	out(answer.getString());
	debug_f("calcCount",calcCount);
}

// g++ -std=gnu++17 -Wall -Wno-unknown-pragmas -O2 -g -D_DEBUG ".\AtCoder\AHC\AHC011\main.cpp"