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
template<class T>bool chmax(T&a,T b){if(a<b){a=b; return true;}return false;}
template<class T>bool chmin(T&a,T b){if(a>b){a=b; return true;}return false;}
template<class S>S sum(vector<S>&a){return accumulate(all(a),S());}
template<class S>S max(vector<S>&a){return *max_element(all(a));}
template<class S>S min(vector<S>&a){return *max_element(all(a));}

template<class T>void puta(T&&t){cout<<t<<endl;}
template<class H,class...T>void puta(H&&h,T&&...t){cout<<h<<' ';puta(t...);}
template<class S,class T>void tf(bool b,S t,T f){if(b)puta(t);else puta(f);}
void OUT(bool b){tf(b,"YES","NO");}
void Out(bool b){tf(b,"Yes","No");}
void out(bool b){tf(b,"yes","no");}
template<class S,class T>ostream&operator<<(ostream&os,pair<S,T>p){os<<"["<<p.first<<", "<<p.second<<"]";return os;};
template<class S>auto&operator<<(ostream&os,vector<S>t){bool a=1;for(auto s:t){os<<(a?"":" ")<<s;a=0;}return os;}
template<class S>auto&operator>>(istream&is,vector<S>&t){for(S&a:t)cin>>a;return is;}

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
	int n,m,s,t;
	cin>>n>>m>>s>>t;
	vector<vector<pll>> yen(n+1);
	vector<vector<pll>> snuuk(n+1);
	rep(i,m){
		ll a,b,c,d;
		cin>>a>>b>>c>>d;
		yen[a].emplace_back(b,c);
		yen[b].emplace_back(a,c);
		snuuk[a].emplace_back(b,d);
		snuuk[b].emplace_back(a,d);
	}
	vl cost_y(n+1,1);
	vl cost_s(n+1,1);
	priority_queue<pll> q;
	q.emplace(0,s);
	while(!q.empty()){
		ll cost,point;
		tie(cost,point)=q.top();
		q.pop();
		if(cost_y[point]!=1)continue;
		cost_y[point]=cost;
		for(auto&e:yen[point]){
			ll to,need;
			tie(to,need)=e;
			if(cost_y[to]==1){
				q.emplace(cost-need,to);
			}
		}
	}
	q.emplace(0,t);
	while(!q.empty()){
		ll cost,point;
		tie(cost,point)=q.top();
		q.pop();
		if(cost_s[point]!=1)continue;
		cost_s[point]=cost;
		for(auto&e:snuuk[point]){
			ll to,need;
			tie(to,need)=e;
			if(cost_s[to]==1){
				q.emplace(cost-need,to);
			}
		}
	}
	vl ans(n+1,0);
	rep(_,n){
		int i=n-_;
		ans[i]=max(ans[i+1],1000000000000000ll+cost_y[i]+cost_s[i]);
	}
	range(i,1,n+1)puta(ans[i]);
	return 0;
}