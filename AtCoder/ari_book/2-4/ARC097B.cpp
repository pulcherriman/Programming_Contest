#include <bits/stdc++.h>
using namespace std;
using ll=long long;
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
using vs=vector<string>;
#define all(a) a.begin(),a.end()
#define rall(a) a.rbegin(),a.rend()
#define rep(i,n) range(i,0,n)
#define range(i,a,n) for(ll i=(a);i<(n);i++)
#define LINF ((ll)1ll<<60)
#define INF ((int)1<<30)
#define EPS (1e-9)
#define MOD (1000000007ll)
#define fcout(a) cout<<setprecision(a)<<fixed
#define fs first
#define sc second
#define PI 3.1415926535897932384

int dx[]={1,0,-1,0,1,-1,-1,1},dy[]={0,1,0,-1,1,1,-1,-1};
template<class S,class T>ostream&operator<<(ostream&os,pair<S,T>p){os<<"["<<p.first<<", "<<p.second<<"]";return os;};
template<class S>auto&operator<<(ostream&os,vector<S>t){bool a=1; for(auto s:t){os<<(a?"":" ")<<s;a=0;} return os;}
template<class S>void tf(bool b,S t,S f){cout<<(b?t:f)<<endl;}
void OUT(bool b){tf(b,"YES","NO");}
void Out(bool b){tf(b,"Yes","No");}
void out(bool b){tf(b,"yes","no");}
template<class T>void puta(T&&t){cout<<t<<endl;}
template<class H,class...T>void puta(H&&h,T&&...t){cout<<h<<' ';puta(t...);}

int popcnt(int x){return __builtin_popcount(x);}
int popcnt(ll x){return __builtin_popcountll(x);}
int bsr(int x){return 31 - __builtin_clz(x);}
int bsr(ll x){return 63 - __builtin_clzll(x);}
int bsf(int x){return __builtin_ctz(x);}
int bsf(ll x){return __builtin_ctzll(x);}
template<class T>bool chmax(T&a,T b){if(a<b){a=b; return true;}return false;}
template<class T>bool chmin(T&a,T b){if(a>b){a=b; return true;}return false;}

/*他のライブラリを入れる場所*/
struct UnionFind{
	vi p;
	UnionFind(int s):p(s,-1){}
	void unite(int a,int b){
		a=root(a);b=root(b);
		if(a!=b){
			if(p[b]<p[a])swap(a,b);
			p[a]+=p[b];p[b]=a;
		}
	}
	bool same(int a,int b){return root(a)==root(b);}
	int root(int a){return p[a]<0?a:p[a]=root(p[a]);}
};

int main(){
	cin.tie(0);
	ios::sync_with_stdio(false);
	int n,q;
	cin>>n>>q;
	UnionFind uf(n*2);
	rep(i,q){
		int w,x,y,z;
		cin>>w>>x>>y>>z;
		x--; y--;
		if(w==1){
			if(z%2){
				uf.unite(x*2  , y*2+1);
				uf.unite(x*2+1, y*2  );
			}else{
				uf.unite(x*2  , y*2  );
				uf.unite(x*2+1, y*2+1);
			}
		}else{
			OUT(uf.same(x*2,y*2));
		}
	}
	return 0;
}