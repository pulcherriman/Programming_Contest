/*
 * Unsecured Optimization
 */
#pragma GCC optimize "O3" /* 最適化 */
#pragma GCC target "avx" /* SIMD(ベクトル化) */
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native") /* 浮動小数点数のSIMD */
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

struct Setup_io {
	Setup_io() {
		ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
		cout<<fixed<<setprecision(11);
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

// ここにライブラリを貼る
class Field{
public:
	Field(string _url){
		Reset();
		readURL(_url);
		dump("target URL:", url);
		dump("vertical marks:", vertical);
		dump("horizontal marks:", horizontal);
	}

	pair<int, vvi> solve(){
		ConstructRules();
		return {n*n*n, rules};
	}

private:
	int n;
	string url;
	vvi rules;
	vi vertical, horizontal;

	void Reset(){
		n = 0;
		url = "";
		rules.clear();
		vertical.clear();
		horizontal.clear();
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

	int GetIndex(int y, int x, int v){
		assert(0 <= y and y < n);
		assert(0 <= x and x < n);
		assert(1 <= v and v <= n);
		return (y*n + x)*n + v;
	}

	void ConstructRules(){
		AddRulesByNotEmpty();
		AddRulesByAtLeastOne();
		AddRulesByAtMostOne();
		rep(i,n)rep(j,n-1){
			int markId = i*(n-1) + j;
			AddRulesByMark(i, j, i, j+1, vertical[markId]);
		}
		rep(i,n-1)rep(j,n){
			int markId = i*n + j;
			AddRulesByMark(i, j, i+1, j, horizontal[markId]);
		}
	}

	void AddRulesByNotEmpty(){
		rep(i,n)rep(j,n){
			int id = GetIndex(i, j, 1);
			vi rule(n);
			iota(all(rule), id);
			rule.emplace_back(0);
			rules.push_back(rule);
		}
	}

	void AddRulesByAtLeastOne(){
		vi rule(n+1, 0);
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
		return vi{v1, v2, 0};
	}
	
	vi NG(int v1, int v2){
		return vi{-v1, -v2, 0};
	}

};



int main(){
	geta(string, url);
	Field field(url);
	auto [cnt, rules] = field.solve();
	puta("p cnf", cnt, rules.size());
	for(auto&ln:rules)puta(ln);
}