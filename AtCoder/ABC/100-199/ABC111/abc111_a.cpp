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

int main(){
	cin.tie(0);
   	ios::sync_with_stdio(false);
	
    int n;
    cin>>n;
    cout<<1110-n<<endl;
}
