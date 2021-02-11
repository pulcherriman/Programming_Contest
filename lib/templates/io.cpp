#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using ll=long long;
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

#define all(a) a.begin(),a.end()
#define rall(a) a.rbegin(),a.rend()
#define rep(i,n) range(i,0,n)
#define rrep(i,n) for(ll i=((ll)n)-1;i>=0;i--)
#define range(i,a,n) for(ll i=((ll)a);i<((ll)n);i++)
#define LINF ((ll)1ll<<60)
#define INF ((int)1<<30)
#define EPS (1e-9)
#define MOD (1000000007ll)
#define fcout(a) cout<<setprecision(a)<<fixed
#define PI (3.1415926535897932384)

int dx[]={1,0,-1,0,1,-1,-1,1},dy[]={0,1,0,-1,1,1,-1,-1};
template<class T>bool chmax(T&a,T b){if(a<b){a=b; return true;}return false;}
template<class T>bool chmin(T&a,T b){if(a>b){a=b; return true;}return false;}
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

template<class T>void puta(T&t,false_type,ostream&os,char el){os<<t;}
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
template<class T>void dump(const T&t){puta(t,cerr);}
template<class H,class...T>void dump(const H&h,const T&...t){cerr<<h<<' ';dump(t...);}
template<class...T>void dump(tuple<T...>const&t){puta(t,cerr);}
template<class S,class T>constexpr ostream&operator<<(ostream&os,pair<S,T>p){
	os<<'['<<p.first<<", ";
	if constexpr(hasItr<T>::v)puta(p.second,bool_constant<true>(),os,']');
	else os<<p.second<<']';
	return os;
};

void YN(bool b){puta(b?"YES":"NO");}
void Yn(bool b){puta(b?"Yes":"No");}
//input
template<class S>auto&operator>>(istream&is,vector<S>&t){for(S&a:t)cin>>a;return is;}
#define geta(t,n) t n;cin>>n
#define vec(t,a,h,...) vector<t>a(h);rep(i,n)a[i]=t(__VA_ARGS__);rep(i,n)cin>>a[i]

int main(){
	cin.tie(0);
	ios::sync_with_stdio(false);

	// Yes/No
	Yn(true);
	puta("============");

	// 1変数&定数
	int x=0;
	puta(x);
	puta(1.2);
	puta("3456");
	puta("============");

	// 複数変数&定数
	puta(x, 1.2, "3456");
	dump(x, 1.2, "3456");
	puta("============");

	//タプル
	puta(make_tuple(0, 1.2, "3456", 7890ll));
	dump(make_tuple(0, 1.2, "3456", 7890ll));
	puta("============");

	// 数値配列
	vl a={1,2,3,4};
	puta(a);
	dump(a);
	puta("============");
	
	// 文字列/二重配列
	vector<vs> b={{"ab","cd","ef"}, {"gh","ij"}};
	puta(b);
	dump(b);
	puta("============");

	// pairを含むvector
	vector<pll> c={{1,2}, {3,4},{5,6}};
	puta(c);
	dump(c);
	puta("============");

	// map
	map<string,ll> d;
	d["hoge"]=123;
	d["fuga"]=456;
	puta(d);
	dump(d);
	puta("============");

	map<string,string> e;
	e["hoge"]="HOGE";
	e["fuga"]="FUGA";
	puta(e);
	dump(e);
	puta("============");

	map<string, vl> f;
	f.emplace("abc", vl{1, 2, 3});
	f.emplace("xyz", vl{123, 456, 789});
	puta(f);
	dump(f);
	puta("============");

	map<string, vs> g;
	g.emplace("abc", vs{"ab", "bc", "ca"});
	g.emplace("xyz", vs{"xy", "yz", "zx"});
	puta(g);
	dump(g);
	puta("============");

	// input
	geta(int, n);	// int n; cin>>n;
	vec(ll,h,n);	// vector<ll> h(n); cin>>h;
	vec(vl,h,10,5);	// vector<vl> h(10,vl(5)); cin>>h;
	puta(n);
	puta(h);

	return 0;
}