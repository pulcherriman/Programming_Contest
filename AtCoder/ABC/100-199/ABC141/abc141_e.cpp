#include <bits/stdc++.h>
#if defined(ONLINE_JUDGE) || defined(_DEBUG)
#include <atcoder/all>
using namespace atcoder;
#endif

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
#define rrep(i,n) rrange(i,0,n)
#define range(i,a,n) for(ll i=((ll)a);i<((ll)n);++i)
#define rrange(i,a,n) for(ll i=((ll)n-1);i>=((ll)a);--i)
#define repsq(i,n) for(ll i=0;i*i<=n;++i)
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
template<class...T>constexpr ostream&operator<<(ostream&os,tuple<T...>t){
	puta(t,os); return os;
}

void YN(bool b){puta(b?"YES":"NO");}
void Yn(bool b){puta(b?"Yes":"No");}

#ifndef _DEBUG
#define dump(...) 
#endif

//input
template<class S>auto&operator>>(istream&is,vector<S>&t){for(S&a:t)cin>>a;return is;}
// #define geta(t,n,...) t n;cin>>n;geta(t,__VA_ARGS__)
// #define vec(t,a,h,...) vector<t>a(h);rep(i,n)a[i]=t(__VA_ARGS__);rep(i,n)cin>>a[i]
template<typename...S>void geta_(S&...s){((cin>>s),...);}

#define geta(t,...) t __VA_ARGS__;geta_(__VA_ARGS__)


class RollingHash{
using u64=uint_fast64_t;
using i128=__int128_t;
public:
	string str;
	RollingHash(const string&str):str(str){
		h.resize(str.size()+1,0);
		p.resize(str.size()+1,1);
		rep(i,str.size()){
			p[i+1]=mul(p[i],base);
			h[i+1]=mul(h[i],base)+xorshift(str[i]+1);
			if(h[i+1]>=mod)h[i+1]-=mod;
		}
	}
	u64 get()const{return h.back();}
	u64 get(int l,int r)const{u64 v=mod+h[r]-mul(h[l],p[r-l]);return v<mod?v:v-mod;}
private:
	vector<u64> h,p;
	static constexpr u64 mod=(1ull<<61)-1;
	static constexpr u64 base=36000*__TIME__[0]+3600*__TIME__[1]+600*__TIME__[3]+60*__TIME__[4]+10*__TIME__[6]+__TIME__[7];
	static constexpr u64 mul(i128 a,i128 b){i128 t=a*b;t=(t>>61)+(t&mod);return t<mod?t:t-mod;}
	static constexpr int xorshift(int x){x^=x<<13;x^=x>>17;return x^=x<<5;}
};


int main(){
	cin.tie(0);
	ios::sync_with_stdio(false);
	geta(ll, n);
	geta(string,s);

	ll ans=0;
	RollingHash hash(s);
	rep(i,s.size()){
		range(j,i,s.size()){
			while(i + ans < j and j + ans < n) {
				if(hash.get(i, i + ans + 1) != hash.get(j, j + ans + 1)) break;
				ans++;
			}
		}
	}
	puta(ans);
	
	return 0;
}
