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
#define range(i,a,n) for(int i=(a);i<(n);i++)
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
void OUT(bool b){cout<<(b?"YES":"NO")<<endl;}
void Out(bool b){cout<<(b?"Yes":"No")<<endl;}
void out(bool b){cout<<(b?"yes":"no")<<endl;}
int popcnt(int x){return __builtin_popcount(x);}
int popcnt(ll x){return __builtin_popcountll(x);}
int bsr(int x){return 31 - __builtin_clz(x);}
int bsr(ll x){return 63 - __builtin_clzll(x);}
int bsf(int x){return __builtin_ctz(x);}
int bsf(ll x){return __builtin_ctzll(x);}

/*他のライブラリを入れる場所*/

int main(){
	cin.tie(0);
	ios::sync_with_stdio(false);
	int n;
	string s;
	cin>>n>>s;
	rep(t,4){
		vi ans(n);
		ans[0]=t/2, ans[1]=t%2;
		range(i,2,n){
			if(s[i-1]=='o')ans[i]=ans[i-1]^!ans[i-2];
			if(s[i-1]=='x')ans[i]=ans[i-1]^ans[i-2];
		}
		bool ok1=false,ok2=false;
		if(s[n-1]=='o' and ans[n-1] and ans[0]==ans[n-2])ok1=true;
		if(s[n-1]=='o' and !ans[n-1] and ans[0]!=ans[n-2])ok1=true;
		if(s[n-1]=='x' and ans[n-1] and ans[0]!=ans[n-2])ok1=true;
		if(s[n-1]=='x' and !ans[n-1] and ans[0]==ans[n-2])ok1=true;
		if(s[0]=='o' and ans[0] and ans[1]==ans[n-1])ok2=true;
		if(s[0]=='o' and !ans[0] and ans[1]!=ans[n-1])ok2=true;
		if(s[0]=='x' and ans[0] and ans[1]!=ans[n-1])ok2=true;
		if(s[0]=='x' and !ans[0] and ans[1]==ans[n-1])ok2=true;
		if(ok1 and ok2){
			rep(i,n) cout<<(ans[i]?"S":"W");
			cout<<endl;
			return 0;
		}
	}
	cout<<-1<<endl;

	return 0;
}