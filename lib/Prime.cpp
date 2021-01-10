#include <bits/stdc++.h>
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
#define fs first
#define sc second
#define PI (3.1415926535897932384)

int dx[]={1,0,-1,0,1,-1,-1,1},dy[]={0,1,0,-1,1,1,-1,-1};
template<class T>bool chmax(T&a,T b){if(a<b){a=b; return true;}return false;}
template<class T>bool chmin(T&a,T b){if(a>b){a=b; return true;}return false;}
template<class S>S sum(vector<S>&a){return accumulate(all(a),S());}
template<class S>S max(vector<S>&a){return *max_element(all(a));}
template<class S>S min(vector<S>&a){return *min_element(all(a));}
ll max(int a,ll b){return max((ll)a,b);} ll max(ll a,int b){return max(a,(ll)b);}
int sgn(const double&r){return (r>EPS)-(r<-EPS);} // a>0  : sgn(a)>0
int sgn(const double&a,const double&b){return sgn(a-b);} // b<=c : sgn(b,c)<=0

template<class S,class T>ostream&operator<<(ostream&os,pair<S,T>p){os<<"["<<p.first<<", "<<p.second<<"]";return os;};
template<class S>auto&operator<<(ostream&os,vector<S>t){bool a=1;for(auto s:t){os<<(a?"":" ")<<s;a=0;}return os;}
template<class S,class T>auto&operator<<(ostream&os,map<S,T>mp){bool a=1;for(auto p:mp){os<<(a?"":", ")<<p;a=0;}return os;}
template<class S>auto&operator>>(istream&is,vector<S>&t){for(S&a:t)cin>>a;return is;}
template<class T>void puta(T&&t){cout<<t<<"\n";}
template<class H,class...T>void puta(H&&h,T&&...t){cout<<h<<' ';puta(t...);}
template<class S,class T>void tf(bool b,S t,T f){if(b)puta(t);else puta(f);}
void YN(bool b){tf(b,"YES","NO");}
void Yn(bool b){tf(b,"Yes","No");}
void yn(bool b){tf(b,"yes","no");}

/*他のライブラリを入れる場所*/
struct _Prime{
	const int arr32[3]={2,7,61};
	const int arr64[12]={2,3,5,7,11,13,17,19,23,29,31,37};
	
	bool IsPrime(ll n){
		if(n<2)return false;
		if(n==2)return true;
		if((n&1)==0)return false;
		if(n<=INT_MAX)return IsPrime32(n);
		return IsPrime64(n);
	}
	map<ll,int> Factorize(ll n){
		map<ll,int> r;
		if(n!=1){
			ll x=pollard_single(n);
			if(x==n)r[x]=1;
			else{
				r=Factorize(x);
				auto ri=Factorize(n/x);
				for(auto&v:ri)r[v.first]+=v.second;
			}
		}
		return r;
	}
	private:
	template<class T,class U>
	T pmod(T x,U n,T md) {
		T r=1%md;
		while(x%=md,n){if(n&1)r=r*x%md;x*=x;n>>=1;}
		return r;
	}
	bool IsPrime32(int n){
		for(ll a:arr32){
			bool c=true;
			ll m=n-1;
			while((m&1)==0)c&=pmod<ll>(a,m>>=1,n)!=n-1;
			c&=pmod<ll>(a,m?:1,n)!=1;
			if(c)return n<=a;
		}
		return true;
	}
	bool IsPrime64(ll n){
		for(int a:arr64){
			bool c=true;
			ll m=n-1;
			while((m&1)==0)c&=pmod<__int128_t>(a,m>>=1,n)!=n-1;
			c&=pmod<__int128_t>(a,m?:1,n)!=1;
			if(c)return n<=a;
		}
		return true;
	}
	ll fast_gcd(ll _a,ll _b) {
		static auto bsf=[](ull x){return __builtin_ctzll(x);};
		ull a=abs(_a),b=abs(_b);
		if(a==0)return b;
		if(b==0)return a;
		int s=bsf(a|b);
		a>>=bsf(a);
		do{if(a>(b>>=bsf(b)))swap(a,b);}while(b-=a);
		return a<<s;
	}
	ll pollard_single(ll n){
		static auto f=[&](ll x){return(__int128_t(x)*x+1)%n;};
		if((n&1)==0)return 2;
		if(IsPrime(n))return n;
		ll st=0;
		while(true){
			ll x=++st,y=f(x);
			while(true){
				ll p=fast_gcd(y-x+n,n);
				if(p==0||p==n)break;
				if(p!=1)return p;
				x=f(x);
				y=f(f(y));
			}
		}
	}
};
_Prime Prime;

int main(){
	cin.tie(0);
	ios::sync_with_stdio(false);

	puta(Prime.IsPrime(10123457689ll)); // True
	puta(Prime.Factorize(1565912117761ll)); // [1162193, 1] [1347377, 1]
	puta(Prime.Factorize(10123457689ll)); // [10123457689, 1]
	puta(Prime.Factorize(999381247093216751ll)); // [999665081, 1], [999716071, 1]
	return 0;
}