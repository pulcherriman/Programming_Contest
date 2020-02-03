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
int sgn(const double&r){return (r>EPS)-(r<-EPS);} // a>0  : sgn(a)>0
int sgn(const double&a,const double&b){return sgn(a-b);} // b<=c : sgn(b,c)<=0

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

vl bfs(tlll st, vvl&rev, vl&depth, ll tgt=-1){
	ll prev,cur,dep;
	tie(prev,cur,dep)=st;
	// puta(cur,prev,dep,tgt);

	if(dep==1){
		if(cur==tgt)return vl(1,cur);
		else return vl(0);
	}
	vl ret;
	for(auto&e:rev[cur]){
		if(depth[e]==dep-1){
			vl tmp = bfs(tlll(cur,e,dep-1), rev,depth,tgt==-1?prev:tgt);
			if(tmp.size()==dep-1){
				ret=tmp;
				ret.push_back(cur);
			}
		}
	}
	return ret;
}

int main(){
	cin.tie(0);
	ios::sync_with_stdio(false);
	ll n,m;
	cin>>n>>m;
	vvl edge(n),rev(n);
	rep(i,m){
		ll a,b;cin>>a>>b;
		a--;b--;
		edge[a].push_back(b);
		rev[b].push_back(a);
	}
	queue<tlll> q;
	vvl ans(n);

	rep(start,n){
		q.emplace(start,-1,1);
		vl v(n,0);
		ll mn=LINF; tlll st;
		while(!q.empty()){
			ll cur,prev,dep;
			tie(cur,prev,dep)=q.front();
			q.pop();
			if(v[cur]){
				if(cur!=start)continue;
				ll len=dep-v[cur];
				if(mn>len){
					mn=len;
					st=tlll(cur,prev,dep-1);
				}
				continue;
			}
			v[cur]=dep;
			for(auto&nxt:edge[cur]){
				if(v[nxt]==0 or nxt==start)
				q.emplace(nxt,cur,dep+1);
			}
		}
		// puta(start,mn,get<0>(st),get<1>(st),get<2>(st));
		// puta(v);
		// puta("===v");
		if(mn==LINF)ans[start]=vl(2000,0);
		else ans[start] = bfs(st,rev,v);
		// puta(ans[start]);
		// puta("===^");
	}
	ll mn=LINF;
	rep(i,n)chmin(mn,(ll)ans[i].size());

	vl a;
	if(mn==2000){
		puta(-1);
		return 0;
	}
	puta(mn);
	rep(i,n)if(ans[i].size()==mn){
		for(auto&e:ans[i])puta(e+1);
		return 0;
	}
	return 0;
}