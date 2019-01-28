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

int main(){
	cin.tie(0);
	ios::sync_with_stdio(false);
	vvi f(4,vi(4,0));
	string s;
	cin>>s;
	using pii=pair<int,int>;
	for(auto&c:s){
		int t='1'-c;
		vector<pii> p;
		rep(i,4-t)rep(j,3+t){
			if(f[i][j]==0 and f[i+t][j+1-t]==0){
				p.emplace_back(i,j);
			}
		}
		vi del(p.size(),0);
		rep(ind,p.size()){
			int y,x; tie(y,x)=p[ind];
			auto cp=f;
			cp[y][x]=cp[y+t][x+1-t]=1;
			vvi d(4,vi(4,0));
			rep(i,4){
				bool d1=true,d2=true;
				rep(j,4){
					d1&=(cp[i][j]==1);
					d2&=(cp[j][i]==1);
				}
				if(d1)rep(j,4)d[i][j]=1;
				if(d2)rep(j,4)d[j][i]=1;
			}
			rep(i,4)rep(j,4){
				if(d[i][j])del[ind]++;
			}
		}
		int ind=max_element(all(del))-del.begin();
		int y,x; tie(y,x)=p[ind];
		puta(y+1,x+1);
		f[y][x]=f[y+t][x+1-t]=1;
		vvi d(4,vi(4,0));
		rep(i,4){
			bool d1=true,d2=true;
			rep(j,4){
				d1&=(f[i][j]==1);
				d2&=(f[j][i]==1);
			}
			if(d1)rep(j,4)d[i][j]=1;
			if(d2)rep(j,4)d[j][i]=1;
		}
		rep(i,4)rep(j,4){
			if(d[i][j])f[i][j]=0;
		}
	}
	return 0;
}