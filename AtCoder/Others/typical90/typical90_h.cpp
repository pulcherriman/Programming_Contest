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
template <int mod> struct ModInt {
	constexpr static int get_mod() { return mod; }
	// 原始根 O(sqrt(N))
	static int get_primitive_root() {
		static int primitive_root = 0;
		if (!primitive_root) {
			primitive_root = -1;
			set<int> fac;
			int v=mod-1;
			for(ll i=2;i*i<=v;i++)while(v%i)fac.insert(i),v/=i;
			if(v>1)fac.insert(v);
			range(g,1,mod){
				bool ok=true;
				for(auto&i:fac) if(ModInt(g).pow((mod-1)/i)==1){ ok=false; break; }
				if(ok){ primitive_root=g; break; }
			}
		}
		return primitive_root;
	}
	int val;
	constexpr ModInt() : val(0) {}
	constexpr ModInt &_setval(ll v) { return val = (v >= mod ? v - mod : v), *this; }
	constexpr ModInt(ll v) { _setval(v % mod + mod); }
	constexpr explicit operator bool() const { return val != 0; }
	constexpr explicit operator ll() const { return val; }
	constexpr ModInt operator+(const ModInt &x) const { return ModInt()._setval((ll)val + x.val); }
	constexpr ModInt operator-(const ModInt &x) const { return ModInt()._setval((ll)val - x.val + mod); }
	constexpr ModInt operator*(const ModInt &x) const { return ModInt()._setval((ll)val * x.val % mod); }
	constexpr ModInt operator/(const ModInt &x) const { return ModInt()._setval((ll)val * x.inv() % mod); }
	constexpr ModInt operator-() const { return ModInt()._setval(mod - val); }
	constexpr ModInt &operator+=(const ModInt &x) { return *this = *this + x; }
	constexpr ModInt &operator-=(const ModInt &x) { return *this = *this - x; }
	constexpr ModInt &operator*=(const ModInt &x) { return *this = *this * x; }
	constexpr ModInt &operator/=(const ModInt &x) { return *this = *this / x; }
	friend constexpr ModInt operator+(ll a, const ModInt &x) { return ModInt()._setval(a % mod + x.val); }
	friend constexpr ModInt operator-(ll a, const ModInt &x) { return ModInt()._setval(a % mod - x.val + mod); }
	friend constexpr ModInt operator*(ll a, const ModInt &x) { return ModInt()._setval(a % mod * x.val % mod); }
	friend constexpr ModInt operator/(ll a, const ModInt &x) { return ModInt()._setval(a % mod * x.inv() % mod); }
	constexpr bool operator==(const ModInt &x) const { return val == x.val; }
	constexpr bool operator!=(const ModInt &x) const { return val != x.val; }
	constexpr bool operator<(const ModInt &x) const { return val < x.val; } // To use map<ModInt, T>
	friend istream &operator>>(istream &is, ModInt &x) { ll t; return is >> t, x = ModInt(t), is; }
	constexpr friend ostream &operator<<(ostream &os, const ModInt &x) { return os << x.val; }
	constexpr ModInt pow(ll n) const {
		ll ans=1, tmp=this->val;
		while(n){ if(n&1)ans=ans*tmp%mod; tmp=tmp*tmp%mod, n>>=1; }
		return ans;
	}

	// 逆元と階乗の事前計算 n<=2^20まで
	static vl facs, invs;
	constexpr static void _precalculation(int N) {
		int l0 = facs.size();
		if (N <= l0) return;
		facs.resize(N), invs.resize(N);
		for (int i = l0; i < N; i++) facs[i] = facs[i - 1] * i % mod;
		ll facinv = ModInt(facs.back()).pow(mod - 2).val;
		for (int i = N - 1; i >= l0; i--) {
			invs[i] = facinv * facs[i - 1] % mod;
			facinv = facinv * i % mod;
		}
	}
	constexpr ll inv() const {
		if(this->val < min(mod>>1, 1<<21)){
			while(this->val >= int(facs.size())) _precalculation(facs.size()*2);
			return invs[this->val];
		} else return this->pow(mod-2).val;
	}
	constexpr ModInt fac() const {
		while(this->val>=int(facs.size())) _precalculation(facs.size()*2);
		return facs[this->val];
	}

	// 二重階乗(!?)
	constexpr ModInt doublefac() const {
		ll k = (this->val + 1) / 2;
		return (this->val & 1) ? ModInt(k * 2).fac() / (ModInt(2).pow(k) * ModInt(k).fac())
							   : ModInt(k).fac() * ModInt(2).pow(k);
	}
	constexpr ModInt nCr(const ModInt &r) const {
		return (this->val<r.val)? 0 : this->fac()/((*this-r).fac()*r.fac());
	}
 
	ModInt sqrt() const {
		if (val==0) return 0;
		if (mod==2) return val;
		if (pow((mod-1)/2)!=1) return 0;
		ModInt b = 1;
		while (b.pow((mod-1)/2)==1)b+=1;
		int e=0, m=mod-1;
		while(m%2==0)m>>=1, e++;
		ModInt x=pow((m-1)/2), y=(*this)*x*x, z=b.pow(m);
		x*=(*this);
		while(y!=1){
			int j=0;
			ModInt t=y;
			while(t!=1)j++, t*=t;
			z=z.pow(1LL<<(e-j-1));
			x*=z,z*=z,y*=z,e=j;
		}
		return ModInt(min(x.val, mod-x.val));
	}
};
template <int mod> vector<ll> ModInt<mod>::facs = {1};
template <int mod> vector<ll> ModInt<mod>::invs = {0};
using mymint = ModInt<MOD>;
constexpr mymint operator"" _m(unsigned long long a){ return mymint(a); }


#pragma endregion


void Main(){
	geta(ll, n);
	geta(string,s);
	auto dp=vec(0_m,n+1,8);
	dp[0][0]=1;
	const string z="atcoder";
	rep(i,n){
		rep(j,8){
			if(j<7 and s[i]==z[j]){
				dp[i+1][j+1]+=dp[i][j];
			}
			dp[i+1][j]+=dp[i][j];
		}
	}
	puta(dp[n][7]);
}
