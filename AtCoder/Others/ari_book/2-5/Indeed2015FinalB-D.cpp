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
	int h,w;
	cin>>h>>w;
	int sy,sx,ty,tx;
	ll ans=0;
	cin>>sx>>sy>>tx>>ty;
	vl f(10000,0);
	rep(i,h)rep(j,w){
		cin>>f[i*100+j];
		ans+=f[i*100+j];
	}
	int s=(sy-1)*100+sx-1;
	int t=(ty-1)*100+tx-1;
	using data=tuple<ll,ll,ll>;
	vector<vector<pll>> edge(10000);
	rep(i,h)rep(j,w){
		int p=i*100+j;
		if(j+1!=w){
			edge[p].emplace_back(p+1,f[p]*f[p+1]);
			edge[p+1].emplace_back(p,f[p]*f[p+1]);
		}
		if(i+1!=h){
			edge[p].emplace_back(p+100,f[p]*f[p+100]);
			edge[p+100].emplace_back(p,f[p]*f[p+100]);
		}
	}
	priority_queue<data> q;
	set<ll> st;
	q.emplace(0,0,0);
	while(!q.empty()){
		ll c,from,to;
		tie(c,from,to)=q.top();
		q.pop();
		if(st.find(to)!=st.end())continue;
		st.insert(to);
		ans+=c;
		//puta(c,from,to);
		for(auto&e:edge[to]){
			ll nxt,cost;
			tie(nxt,cost)=e;
			if(st.find(nxt)!=st.end())continue;
			q.emplace(cost,to,nxt);
		}
	}
	puta(ans);
	return 0;
}