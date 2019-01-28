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
using pii=pair<int,int>;
/*他のライブラリを入れる場所*/

int main(){
	cin.tie(0);
	ios::sync_with_stdio(false);
	int h,w,p,lst=0;
	cin>>h>>w>>p;
	vi s(p),dec(p,0),ans(p,0);
	rep(i,p)cin>>s[i];
	using data=tuple<int,int,int>;
	vector<queue<data>> vq(p);
	vs f(h+2,string(w+2,'#'));
	rep(i,h){
		cin>>f[i+1];
		f[i+1]="#"+f[i+1]+"#";
		range(j,1,w+1){
			if(isdigit(f[i+1][j])){
				vq[f[i+1][j]-'1'].emplace(i+1,j,0);
			}
			if(f[i+1][j]!='#') lst++;
		}
	}

	int c=0,z=0;
	bool beg=true;
	while(lst>0){
		if(c==0)z=0;
		if(vq[c].empty())z++;
		while(!vq[c].empty() and lst>0){
			int y,x,d;
			tie(y,x,d)=vq[c].front();
			if(d>=dec[c]+s[c] or (beg and d==1)){
				dec[c]+=beg?1:s[c];
				break;
			}
			vq[c].pop();
			if(f[y][x]!='.' and f[y][x]-'1'!=c)continue;
			if(f[y][x]-'1'==c and !beg)continue;
			f[y][x]=c+'1';
			ans[c]++;
			lst--;
			rep(i,4){
				if(f[y+dy[i]][x+dx[i]]=='.'){
					vq[c].emplace(y+dy[i],x+dx[i],d+1);
				}
			}
		}
		c=(c+1)%p;
		if(c==0)beg=false;
		if(z==p)break;
	}
	//for(auto l:f)cout<<l<<endl;
	cout<<ans<<endl;
	return 0;
}