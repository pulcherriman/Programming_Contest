#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using vi=vector<int>;
using vvi=vector<vi>;
using vd=vector<double>;
using vvd=vector<vd>;
using vl=vector<ll>;
using vvl=vector<vl>;
using pii=pair<int,int>;
using vs=vector<string>;
#define rep(i,n) range(i,0,n)
#define range(i,a,n) for(int i=a;i<n;i++)
#define all(a) a.begin(),a.end()
#define LINF    	((ll)1ll<<60)
#define INF     	((int)1<<30)
#define EPS     	(1e-9)
#define MOD     	(1000000007)
#define fcout(a)	cout<<setprecision(a)<<fixed
#define fs 			first
#define sc			second
#define PI			3.141592653589793

template<class S,class T>ostream& operator<<(ostream&os,pair<S,T>p){os<<"["<<p.first<<", "<<p.second<<"]";return os;};
template<class S>auto&operator<<(ostream&os,vector<S>t){bool a=1; for(auto s:t){os<<(a?"":" ")<<s; a=0;} return os;}
/*
 * sepstr("hoge,fuga:piyo/poya", ",:/");    //1つ目の文字列を、2つ目で与えた区切り文字のセットで分割した結果を返す。O(ND)
 *                                          //この例だと、{"hoge", "fuga", "piyo", "poya"}が返る
 * bitstr(100)          //引数の数値をビット列を示す文字列に変換する
 *                      //宣言内のto_string()には引数を入れることが出来、例えば('_','#')とすると、0をアンダーバー、1を#として表示できる
 * bitcnt(100)          //引数の数値が何ビット立っているか返す
 * bitdig(100)          //ビット列が何ビットあるか返す。
 * bitpow(100)          //その数字の約数に2がいくつあるか。8なら3, 16なら4, 20なら2
 */



template<class T>string bitstr(T x){return typeid(T)==typeid(int)?bitset<32>(x).to_string():bitset<64>(x).to_string();}
template<class T>int bitcnt(T x){return typeid(T)==typeid(int)?__builtin_popcount(x):__builtin_popcountll(x);}
template<class T>int bitdig(T x){return x?typeid(T)==typeid(int)?32-__builtin_clz(x):64-__builtin_clzll(x):0;}
template<class T>int bitpow(T x){return x?typeid(T)==typeid(int)?__builtin_ctz(x):__builtin_ctzll(x):0;}
/*
 * 自明
 */

constexpr ll gcd(ll a,ll b){return b?gcd(b,a%b):a;}
constexpr ll lcm(ll a,ll b){return a*b/gcd(a,b);}

/* nCrを高速に求める
 * 前計算：O(n)
 * 本計算：O(1)
 *
 * Fermat fer(10);	//n,rは引数以下の値を使用できる。この例では、11C1などは計算できない
 * cout<<fer.comb(10,3)<<endl;
 */
class Fermat{
  private:
	int z;
	vector<ll> fact_mod, fact_invmod;
	ll modpow(ll a, ll n){
		if(n==1)return a;
		ll half=modpow(a,n/2);
		return half*half%MOD*(n%2?a:1)%MOD;
	}
  public:
	Fermat(int Z):z(Z){
	    fact_mod=vector<ll>(z+1,1);
		fact_invmod.resize(z+1);
		range(i,1,z+1) fact_mod[i]=fact_mod[i-1]*i%MOD;
		fact_invmod[z]=modpow(fact_mod[z],MOD-2);
		for(int i=z-1;i>=0;i--) fact_invmod[i]=fact_invmod[i+1]*(i+1)%MOD;
	}
	ll comb(int n,int r){return fact_mod[n] * fact_invmod[r]%MOD * fact_invmod[n-r]%MOD;}
};

int main(){
	cin.tie(0);
   	ios::sync_with_stdio(false);
	
	int n,m,a,b;
	cin>>n>>m>>a>>b;
	vi x(n,0);
	rep(i,m){
	    int l,r;
	    cin>>l>>r;
	    range(j,l,r+1){
	        x[j-1]=1;
	    }
	}
	int p=0;
	rep(i,n)p+=x[i];
	cout<<p*a+(n-p)*b<<endl;
	return 0;
}
