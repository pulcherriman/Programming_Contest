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
int n;
using pii=pair<int,int>;
/*他のライブラリを入れる場所*/
int solve(vl&vertex, vector<vector<pii>> edge, vb isSearch, ll prevSum=LINF){

	int cnt=0;
	ll sum=0;
	rep(i,n)if(!isSearch[i])sum+=vertex[i];
	
	rep(i,n)if(!isSearch[i]){
		for(auto&e:edge[i]){
			if(e.sc>sum and e.sc<=prevSum)cnt++;
		}
	}
	if(cnt==0)return 0;

	vb isBFS=isSearch;
	rep(i,n)if(!isBFS[i]){
		vector<vector<pii>> nextedge(n);
		vb nextis(n,true);
		queue<int> q;
		q.push(i);
		ll vsum=0;
		ll emax=0;
		while(!q.empty()){
			int p=q.front();
			q.pop();
			if(isBFS[p])continue;
			isBFS[p]=true;
			nextis[p]=false;
			vsum+=vertex[p];
			for(auto&e:edge[p]){
				int nxt; ll cst;
				tie(nxt,cst)=e;
				if(cst>sum)continue;
				chmax(emax,cst);
				nextedge[p].emplace_back(nxt,cst);
				nextedge[nxt].emplace_back(p,cst);
				if(isBFS[nxt])continue;
				q.push(nxt);
			}
		}
		if(vsum<emax) cnt+=solve(vertex,nextedge,nextis,sum);
	}
	return cnt;
}
int main(){
	cin.tie(0);
	ios::sync_with_stdio(false);
	int m;
	cin>>n>>m;
	vl a(n);
	rep(i,n)cin>>a[i];
	vector<vector<pii>> b(n);
	rep(i,m){
		int x,y,c;
		cin>>x>>y>>c;
		x--; y--;
		b[x].emplace_back(y,c);
		b[y].emplace_back(x,c);
	}
	vb is(n,false);
	cout<<solve(a,b,is)/2<<endl;
	return 0;
}