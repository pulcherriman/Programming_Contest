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
using tlll=tuple<ll,ll,ll>;
using vs=vector<string>;
#define all(a) a.begin(),a.end()
#define rall(a) a.rbegin(),a.rend()
#define rep(i,n) range(i,0,n)
#define rrep(i,n) for(ll i=(n)-1;i>=0;i--)
#define range(i,a,n) for(ll i=(a);i<(n);i++)
#define LINF ((ll)1ll<<60)
#define INF ((int)1<<30)
#define EPS (1e-9)
#define MOD (1000000007ll)
#define fcout(a) cout<<setprecision(a)<<fixed
#define fs first
#define sc second
#define PI (3.1415926535897932384)

int dx[]={1,0,-1,0,1,-1,-1,1},dy[]={0,1,0,-1,1,1,-1,-1};
template<class T>bool chmax(T&a,T b){if(a<b){a=b; return true;}return false;}
template<class T>bool chmin(T&a,T b){if(a>b){a=b; return true;}return false;}
template<class S>S sum(vector<S>&a){return accumulate(all(a),S());}
template<class S>S max(vector<S>&a){return *max_element(all(a));}
template<class S>S min(vector<S>&a){return *min_element(all(a));}
ll max(int a,ll b){return max((ll)a,b);} ll max(ll a,int b){return max(a,(ll)b);}

template<class T>void puta(T&&t){cout<<t<<"\n";}
template<class H,class...T>void puta(H&&h,T&&...t){cout<<h<<' ';puta(t...);}
template<class S,class T>void tf(bool b,S t,T f){if(b)puta(t);else puta(f);}
void YN(bool b){tf(b,"YES","NO");}
void Yn(bool b){tf(b,"Yes","No");}
void yn(bool b){tf(b,"yes","no");}
template<class S,class T>ostream&operator<<(ostream&os,pair<S,T>p){os<<"["<<p.first<<", "<<p.second<<"]";return os;};
template<class S>auto&operator<<(ostream&os,vector<S>t){bool a=1;for(auto s:t){os<<(a?"":" ")<<s;a=0;}return os;}
template<class S>auto&operator>>(istream&is,vector<S>&t){for(S&a:t)cin>>a;return is;}

/*他のライブラリを入れる場所*/
struct UnionFind{
	vl par,dist;
	UnionFind(int x){par.assign(x,-1); dist.assign(x,0);}
	ll find(ll x){return par[x]<0?x:find(par[x]);}
	ll depth(ll x){return par[x]<0?0:depth(par[x])+dist[x];}
	bool same(ll x,ll y){return find(x)==find(y);}
	ll size(ll x){return -par[find(x)];}
	ll diff(ll x,ll y){return same(x,y)?depth(x)-depth(y):LINF;}
	void unite(ll x,ll y,ll k=0){
		k+=depth(y); k-=depth(x); k=-k;
		x=find(x); y=find(y);
		if(x==y)return;
		if(size(x)<size(y)){swap(x,y);k=-k;}
		par[x]+=par[y]; par[y]=x; dist[y]=k;
	}
};

int main(){
	cin.tie(0);
	ios::sync_with_stdio(false);
	ll h,w,n;
	cin>>h>>w>>n;
	vl v(h*w);
	cin>>v;
	map<ll,vl> mp;
	rep(i,h*w){
		if(mp.find(-v[i]+1)==mp.end()) mp[-v[i]+1]=vl();
		mp[-v[i]+1].push_back(i);
	}

	vb used(h*w,false);
	UnionFind uf(h*w);
	ll ans=0,cur=0;
	bool isAns=false;
	for(auto&p:mp){
		if(isAns){
			ans=-p.fs+1;
			isAns=false;
		}
		for(auto&t:p.sc){
			vl moore;
			if(t+w<h*w)moore.push_back(t+w);
			if(t-w>=0)moore.push_back(t-w);
			if(t%w!=0)moore.push_back(t-1);
			if(t%w!=w-1)moore.push_back(t+1);
			//puta("!",t,"!",moore);
			set<ll> pars;
			rep(i,moore.size()){
				bool ok=!used[moore[i]];
				rep(j,i)ok|=uf.same(moore[i],moore[j]);
				if(ok)continue;
				cur--;
				uf.unite(t,moore[i]);
				//puta("unite",t,moore[i]);
			}
			cur++;
			used[t]=true;
		}
		puta("ans",-p.fs,cur);
		if(cur==n){
			isAns=true;
		}
	}
	if(isAns){
		ans=0;
	}
	puta(ans);
	return 0;
}