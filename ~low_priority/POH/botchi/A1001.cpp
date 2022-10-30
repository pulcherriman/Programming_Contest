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
vvi f;
vvi d;
vvi d2(4);
/* 0
  3 1
   2  */
void build(int y, int x, int p){
	rep(i,d[p][0])rep(j,d[p][1]){
		f[i+y][j+x]=p+1;
	}
}

int getArea(vi v){
	return v[0]*v[1];
}

int main(){
	cin.tie(0);
	ios::sync_with_stdio(false);
	int h,w,n;
	cin>>h>>w>>n;
	f=vvi(h,vi(w,0));
	d=vvi(n,vi(5));
	int v=0,p;
	rep(i,n){
		rep(j,4)cin>>d[i][j];
		if(d[i][2]==1) d[i][4]=0;
		if(d[i][3]==d[i][1]) d[i][4]=1;
		if(d[i][2]==d[i][0]) d[i][4]=2;
		if(d[i][3]==1) d[i][4]=3;
		d2[d[i][4]].push_back(i);
		if(chmax(v,d[i][0]*d[i][1]))p=i;
	}
	for(auto&l:d2){
		sort(all(l),[&](int a,int b){return getArea(d[a])>getArea(d[b]);});
		cout<<l<<endl;
	}
	build(0,0,p);
	for(auto&l:f)cout<<l<<endl;
	return 0;
}