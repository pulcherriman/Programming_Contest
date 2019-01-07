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
void OUT(bool b){cout<<(b?"YES":"NO")<<endl;}
void Out(bool b){cout<<(b?"Yes":"No")<<endl;}
void out(bool b){cout<<(b?"yes":"no")<<endl;}
template<class T>
void puta(T&&t){cout<<t<<endl;}
template<class H,class...T>
void puta(H&&h,T&&...t){cout<<h<<' ';puta(t...);}

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
	cin>>n;
	vvi edge(n);
	vi oya(n,0);
	rep(i,n-1){
		int t;cin>>t;
		oya[i+1]=t-1;
		edge[t-1].push_back(i+1);
	}
	vl s(n);
	rep(i,n)cin>>s[i];
	queue<int> q;
	q.push(0);
	ll ans=0;
	vl a(n,0);
	while(!q.empty()){
		int ind=q.front();
		q.pop();
		ll mn=INF,mx=-1;
		for(auto&ch:edge[ind]){
			mn=min(mn,s[ch]);
			mx=max(mn,s[ch]);
			q.push(ch);
		}
		if(s[ind]==-1){
			if(mn==INF){s[ind]=s[oya[ind]];}
			else s[ind]=mn;
		}
		if(ind==0){
			a[ind]=s[ind];
		}else{
			a[ind]=s[ind]-s[oya[ind]];
		}
		if(a[ind]<0){cout<<-1<<endl;return 0;}
	}
	//cout<<a<<endl;
	cout<<accumulate(all(a),0ll)<<endl;
	return 0;
}