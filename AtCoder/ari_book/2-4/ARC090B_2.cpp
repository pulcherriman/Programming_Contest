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
struct UnionFind {
	vi p,r;vl w;
	UnionFind(int n):p(n),r(n,0),w(n,0){iota(all(p),0);}
	int root(int x) {
		if(p[x]==x)return x;
		int r=root(p[x]);
		w[x]+=w[p[x]];
		return p[x]=r;
	}
	ll weight(int x){return w[root(x)];}
	bool issame(int x,int y){return root(x)==root(y);}
	//w[y]-w[x];
	ll diff(int x,int y){return weight(y)-weight(x);}
	//w[x]+W=w[y]
	bool merge(int x,int y,ll W=0) {
		if(issame(x,y)){
			puta(x,root(x));
			puta(y,root(y));
			puta(x,y,W,weight(x));
			return diff(x,y)==0;
		}
		W+=weight(x);W-=weight(y);
		x=root(x); y=root(y);
		if(r[x]<r[y])swap(x,y),W=-W;
		if(r[x]==r[y])++r[x];
		p[y]=x;w[y]=W;
		return true;
	}
};

int main(){
	cin.tie(0);
	ios::sync_with_stdio(false);
	int n,m;
	cin>>n>>m;
	UnionFind uf(n);
	rep(i,m){
		int a,b,c;
		cin>>a>>b>>c;
		if(!uf.merge(a-1,b-1,c)){
			Out(0);
			return 0;
		}
	}
	Out(1);
	return 0;
}