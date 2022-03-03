/*
 * Unsecured Optimization
 */
#pragma GCC optimize "O3" /* 最適化 */
#pragma GCC target "avx" /* SIMD(ベクトル化) */

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

struct Setup_io {
	Setup_io() {
		// ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
		// cout<<fixed<<setprecision(11);
	}
} setup_io;

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
#define __RANGE(i,a,n) for(ll i=((ll)a);i<((ll)n);++i)
#define __RREP(i,n) __RRANGE(i,0,n)
#define __RRANGE(i,a,n) for(ll i=((ll)n-1);i>=((ll)a);--i)
#define repsq(i,n) for(ll i=0;i*i<=n;++i)
#define each(v,a) for(auto v:a)
#define eachref(v,a) for(auto&v:a)
#define fcout(a) cout<<setprecision(a)<<fixed

/*
 * Constants
 */
constexpr ll LINF=1ll<<60;
constexpr int INF=1<<30;
constexpr double EPS=(1e-14);
constexpr ll MOD=998244353ll;
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
#define dump(...)cerr<<"  "<<string(#__VA_ARGS__)<<": ["<<to_string(__LINE__)<<":"<<__FUNCTION__<<"]\n	",dump_f(__VA_ARGS__)
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
template<class T> vector<pair<T,int>> addIndex(vector<T> a){
	vector<pair<T,int>> r;
	rep(i,a.size())r.emplace_back(a[i],i);
	return r;
}

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

// ここにライブラリを貼る
#include "togasat.hpp"

class Kropki {
public:
	Kropki() = default;
	Kropki(int _n): n(_n){
		SetEmpty();
	}
	Kropki(string _url){
		Reset();
		readURL(_url);
		dump("target URL:", url);
		dump("vertical marks:", vertical);
		dump("horizontal marks:", horizontal);
	}

	pair<bool, vvi> Solve(){
		dump("Start Solve");
		bool isSatisfiable = false;

		if(rules.empty()) {
			dump("Construct Rules");
			ConstructRules();
		}

		dump("Check Satisfiability");
		switch (auto [resultStatus, resultAnswer] = Satisfy() ; resultStatus) {
			case 0:
				status = SOLVE_STATUS::SOLVE_SUCCEEDED;
				isSatisfiable = true;
				answer = resultAnswer;
				break;
			case 1:
				status = SOLVE_STATUS::SOLVE_FAILED;
				break;
			default:
				status = SOLVE_STATUS::UNKNOWN;
				break;
		}

		return {isSatisfiable, answer};
	}

	bool isUniqueSolution() {
		if (status == SOLVE_STATUS::NO_CHECK) {
			Solve();
		}
		if (status == SOLVE_STATUS::UNIQUE_SUCCEEDED) {
			return true;
		}
		if (status != SOLVE_STATUS::SOLVE_SUCCEEDED) {
			return false;
		}
		
		{
			vi rule;
			rep(i,n)rep(j,n)rule.push_back(-GetIndex(i, j, answer[i][j]));
			rules.push_back(rule);
		}

		bool isUnique = false;
		switch (auto [resultStatus, resultAnswer] = Satisfy() ; resultStatus) {
			case 0:
				status = SOLVE_STATUS::UNIQUE_FAILED;
				break;
			case 1:
				status = SOLVE_STATUS::UNIQUE_SUCCEEDED;
				isUnique = true;
				break;
			default:
				status = SOLVE_STATUS::UNKNOWN;
				break;
		}

		rules.pop_back();
		return isUnique;
	}

	void PrintDimacs(){
		ConstructRules();
		puta("p cnf", n*n*n, rules.size());
		for(auto&ln:rules){
			puta(ln, cout, ' ');
			puta(0);
		}
	}

protected:
	enum struct SOLVE_STATUS {
		UNKNOWN,
		NO_CHECK,
		SOLVE_FAILED,
		SOLVE_SUCCEEDED,
		UNIQUE_FAILED,
		UNIQUE_SUCCEEDED,
	};

	SOLVE_STATUS status = SOLVE_STATUS::NO_CHECK;
	int n;
	string url;
	vvi rules;
	vi vertical, horizontal;
	vvi answer;

	void Reset(){
		status = SOLVE_STATUS::NO_CHECK;
		n = 0;
		url = "";
		rules.clear();
		vertical.clear();
		horizontal.clear();
		answer.clear();
	}

	void SetEmpty(){
		assert(n != 0);
		status = SOLVE_STATUS::NO_CHECK;
		rules.clear();
		vertical.clear();
		vertical.resize(n * (n-1), 0);
		horizontal.clear();
		horizontal.resize(n * (n-1), 0);
		answer.clear();
	}

	void readURL(string rawUrl){
		assert(rawUrl != "");
		auto tmpUrl = rawUrl.substr(28);
		rep(i,10){
			if(isdigit(tmpUrl[i])){
				n = n*10 + (tmpUrl[i]-'0');
			}else{
				tmpUrl = tmpUrl.substr(i*2+2);
				break;
			}
		}

		vi marks;
		for(auto&c:tmpUrl){
			int v = c-'0';
			if(!isdigit(c)) v = c-'a'+10;
			marks.emplace_back(v/9);
			marks.emplace_back(v/3%3);
			marks.emplace_back(v%3);
		}

		url = rawUrl;
		vertical = vi(marks.begin(), marks.begin() + (n * (n-1)));
		horizontal = vi(marks.begin() + (n * (n-1)), marks.end());
	}

	pair<togasat::lbool, vvi> Satisfy(){
		togasat::lbool solverStatus = false;
		vvi satisfyValues(n, vi(n, 0));

		togasat::Solver solver;
		dump("Add clauses");
		for(auto&ln:rules)solver.addClause(ln);

		dump("Start SAT solver");
		if ((solverStatus = solver.solve()) == 0) {
			rep(id,n*n*n){
				if(solver.assigns[id] == 0){
					satisfyValues[id/n/n][id/n%n] = id%n + 1;
				}
			}
		}
		return {solverStatus, satisfyValues};
	}

	int GetIndex(int y, int x, int v){
		assert(0 <= y and y < n);
		assert(0 <= x and x < n);
		assert(1 <= v and v <= n);
		return (y*n + x)*n + v;
	}

	void ConstructRules(){
		status = SOLVE_STATUS::NO_CHECK;
		rules.clear();
		AddRulesByNotEmpty();
		AddRulesByAtLeastOne();
		AddRulesByAtMostOne();
		AddRulesByOptimize();
		rep(i,n)rep(j,n-1){
			int markId = i*(n-1) + j;
			AddRulesByMark(i, j, i, j+1, vertical[markId]);
		}
		rep(i,n-1)rep(j,n){
			int markId = i*n + j;
			AddRulesByMark(i, j, i+1, j, horizontal[markId]);
		}
	}

	void AddRulesByOptimize(){
		// black which upper than n/2
		vi largeOddNumbers;
		rep(p,n/2+1, n+1)if(p%2 == 1)largeOddNumbers.emplace_back(p);

		vvi isAdjacentBlack(n, vi(n, 0));
		rep(i,n)rep(j,n-1){
			int markId = i*(n-1) + j;
			if(vertical[markId] == 2){
				isAdjacentBlack[i][j] = 1;
				isAdjacentBlack[i][j+1] = 1;
			}
		}
		rep(i,n-1)rep(j,n){
			int markId = i*n + j;
			if(horizontal[markId] == 2){
				isAdjacentBlack[i][j] = 1;
				isAdjacentBlack[i+1][j] = 1;
			}
		}

		rep(i,n)rep(j,n)if(isAdjacentBlack[i][j]) each(p,largeOddNumbers){
			rules.emplace_back(1, -GetIndex(i,j,p));
		}
	}

	void AddRulesByNotEmpty(){
		{
			vi rule(n*n*n, 0);
			iota(all(rule), 1);
			rules.push_back(rule);
		}
		rep(i,n)rep(j,n){
			int id = GetIndex(i, j, 1);
			vi rule(n);
			iota(all(rule), id);
			rules.push_back(rule);
		}
	}

	void AddRulesByAtLeastOne(){
		vi rule(n);
		rep(v,1,n+1)rep(i,n){
			rep(j,n) rule[j] = GetIndex(i, j, v);
			rules.push_back(rule);
			rep(j,n) rule[j] = GetIndex(j, i, v);
			rules.push_back(rule);
		}
	}

	void AddRulesByAtMostOne(){
		rep(i,n)rep(j1,n)rep(j2,j1+1,n)rep(v,1,n+1){
			int id1 = GetIndex(i, j1, v);
			int id2 = GetIndex(i, j2, v);
			rules.push_back(NG(id1, id2));
		}
	}

	using Condition = function<bool(int, int)>;
	static const bool isSatisfyBlank(int v1, int v2){
		return !isSatisfyWhite(v1, v2) and !isSatisfyBlack(v1, v2);
	}

	static const bool isSatisfyWhite(int v1, int v2){
		return v1+1 == v2 or v1 == v2+1;
	}

	static const bool isSatisfyBlack(int v1, int v2) {
		return v1*2 == v2 or v1 == v2*2;
	}

	static inline const function<bool(int, int)> markToCondition[] = {
		isSatisfyBlank, 
		isSatisfyWhite,
		isSatisfyBlack
	};

	void AddRulesByMark(int y1, int x1, int y2, int x2, int mark){
		rep(v1,1,n+1)rep(v2,1,n+1){
			if(!markToCondition[mark](v1,v2)){
				int id1 = GetIndex(y1, x1, v1);
				int id2 = GetIndex(y2, x2, v2);
				rules.push_back(NG(id1, id2));
			}
		}
	}

	vi OK(int v1, int v2){
		return vi{v1, v2};
	}
	
	vi NG(int v1, int v2){
		return vi{-v1, -v2};
	}

};


class KropkiCreator : public Kropki{
public:
	KropkiCreator(int _n): Kropki(_n) {}

	void ConstruceIncompletedRules(){
		// 1~nが1つずつ の制約のみ
		this->status = SOLVE_STATUS::NO_CHECK;
		this->rules.clear();
		this->AddRulesByNotEmpty();
		this->AddRulesByAtLeastOne();
		this->AddRulesByAtMostOne();
	}

	void AddRulesByRandom(){
		vi values(n);
		iota(all(values), 1);

		// 1を決め打ち
		// shuffle(all(values), Random);
		// rep(i,n)this->rules.push_back(vi(1, GetIndex(i, values[i]-1, 1)));


		// rep(i,n){
		// 	rep(j,n){
		// 		shuffle(all(values), Random);
		// 		vi rule;
		// 		rep(t, 6){
		// 			int id = this->GetIndex(i, j, values[t]);
		// 			rule.push_back(id);
		// 		}
		// 		this->rules.push_back(rule);
		// 	}
		// }
		rep(i,n){
			int j = Random(0,n-1);
			// rep(j,n-1)if(Random(0,7)) {
				AddRulesByMark(i,j,i,j+1,1);
			// }
		}
		rep(i,n-1){
			int j = Random(0,n);
			// rep(j,n)if(Random(0,7)) {
				AddRulesByMark(i,j,i+1,j,1);
			// }
		}
	}

	bool Step(){
		dump("construct incomplete rules");
		ConstruceIncompletedRules();
		AddRulesByRandom();

		dump("find specific answer");
		if(auto [isSolved, _] = this->Solve() ; isSolved){
			dump("    -> success");
			// 見つかった解を満たすようにマークを設定
			rep(i,n)rep(j,n-1){
				rrep(t,3){
					if(this->markToCondition[t](this->answer[i][j], this->answer[i][j+1])) {
						this->vertical[i*(n-1) + j] = t;
					}
				}
			}
			rep(i,n-1)rep(j,n){
				rrep(t,3){
					if(this->markToCondition[t](this->answer[i][j], this->answer[i+1][j])) {
						this->horizontal[i*n + j] = t;
					}
				}
			}

			this->ConstructRules();
			dump("check unique answer");
			if(this->isUniqueSolution()){
				dump("    -> success");
				return true;
			} else {
				dump("    -> fail");
			}
		} else {
			dump("    -> fail");
		}
		return false;
	}

	pair<bool, vvi> Create(int msec=1000){
		int cnt=0;

		Timer timer(msec);
		while(timer){
			dump(++cnt);
			if(Step()) return {true, this->answer};
		}
		return {false, vvi()};
	}

	string GetURL(){
		this->url = "http://pzv.jp/p.html?kropki/" + to_string(n) + "/" + to_string(n) + "/";
		
		const string chr = "0123456789abcdefghijklmnopqrstuvwxyz";
		const int pw3[]={1,3,9};

		int val=0, cnt=0;
		for(auto&mark : this->vertical){
			val += mark * pw3[2-cnt];
			cnt++;
			if(cnt == 3){
				this->url += chr[val];
				val = cnt = 0;
			}
		}
		
		for(auto&mark : this->horizontal){
			val += mark * pw3[2-cnt];
			cnt++;
			if(cnt == 3){
				this->url += chr[val];
				val = cnt = 0;
			}
		}

		if(cnt)this->url += chr[val];
		return this->url;
	}

	pair<int, int> GetMarkInfo(){
		int white=0, black=0;
		each(t, this->vertical) {
			if(t==1) white++;
			if(t==2) black++;
		}
		each(t, this->horizontal) {
			if(t==1) white++;
			if(t==2) black++;
		}
		return {black, white};
	}
};

int main(){
	geta(string, url);
	Kropki kropki(url);

	Timer timer(10000);
	auto [isSolved, answer] = kropki.Solve();
	puta(isSolved ? "SOLVED" : "UNSOLVED");
	if(isSolved){
		auto isUnique = kropki.isUniqueSolution();
		puta(isUnique ? "UNIQUE" : "NOT UNIQUE");
		puta(isUnique ? "UNIQUE" : "NOT UNIQUE");
		puta("");
		puta(answer);
		puta("");
	}
	puta(timer.get(), "ms");
}