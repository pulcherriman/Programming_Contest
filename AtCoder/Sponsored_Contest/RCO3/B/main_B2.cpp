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

#define _cTime (chrono::system_clock::now())
#define progress (chrono::duration_cast<chrono::milliseconds>(_cTime-_sTime).count())
#define reset _sTime=_cTime
auto reset;

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


int main(){
	cin.tie(0);
	ios::sync_with_stdio(false);
	ll n,m;
	cin>>n>>m;
	vvi a(n,vi(n));
	rep(i,n)cin>>a[i];
	int cnt=0,loop=0;
	vvb harvest(n,vb(n,false));

	vector<pll> vec;
	rep(i,n)rep(j,n)vec.emplace_back(i,j);
	sort(all(vec),[](pll a,pll b){return hypot(a.fs-24.5,a.sc-24.5)<hypot(b.fs-24.5,b.sc-24.5);});
	range(v,1,6){
		for(auto&p:vec){
			int i=p.fs,j=p.sc;
			if(a[i][j]>v)continue;
			cnt++;
			puta(1,i,j);
			a[i][j]++;
			if(cnt>=2440){i=j=v=n;break;}
		}
	}
	vvb sed=harvest;
	vector<tlll> ans;

	for(auto&p:vec){
		int i=p.fs,j=p.sc;
		if(sed[i][j])continue;
		queue<pll> q;
		q.emplace(i,j);
		int c=0;
		vi vy,vx;
		while(!q.empty()){
			int y,x;
			tie(y,x)=q.front(); q.pop();
			if(sed[y][x])continue;
			sed[y][x]=true;
			c++;
			vy.push_back(y);
			vx.push_back(x);
			rep(v,4){
				int ny=y+dy[v],nx=x+dx[v];
				if(ny<0 or nx<0 or ny-n>=0 or nx-n>=0)continue;
				if(a[y][x]==a[ny][nx])q.emplace(ny,nx);
			}
		}
		if(c>=a[i][j]){
			ans.emplace_back(a[i][j]*c,i,j);
			rep(k,vy.size())harvest[vy[k]][vx[k]]=true;
		}
	}
	sort(rall(ans));
	rep(i,ans.size()){
		puta(2,get<1>(ans[i]),get<2>(ans[i]));
		cnt++;
		if(cnt==2500)break;
	}
	return 0;
}
