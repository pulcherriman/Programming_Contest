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
using tllll=tuple<ll,ll,ll,ll>;
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

pll mov(int y, int x, int v){
	vi dx={0,1,1,0,-1,-1},dy={1,0,-1,-1,-1,0,1,1,0,-1,0,1};
	return pll(y+dy[v+(abs(x)%2*6)],x+dx[v]);
}

int main(){
	cin.tie(0);
	ios::sync_with_stdio(false);
	ll sx,sy,gx,gy,n,lx,ly;
	cin>>sx>>sy>>gx>>gy>>n;
	vvb w(203,vb(203,false));
	rep(i,n){
		int x,y;
		cin>>x>>y;
		w[y+101][x+101]=true;
	}
	cin>>lx>>ly;
	rep(i,203){
		w[ly+102][i]=true;
		w[100-ly][i]=true;
		w[i][lx+102]=true;
		w[i][100-lx]=true;
	}
	vector<vvi> dist(203,vvi(203,vi(6,INF)));

	deque<tllll> q;
	q.emplace_back(sy,sx,0,0);
	while(!q.empty()){
		int y,x,t,d;
		tie(y,x,t,d)=q.front();
		q.pop_front();
		if(dist[y+101][x+101][t]!=INF)continue;
		dist[y+101][x+101][t]=d;
		
		rep(v,6){ //iは方向
			int ny,nx;
			tie(ny,nx) = mov(y,x,v);
			if(w[ny+101][nx+101]) continue;
			if(v==abs(x*y*t)%6){
				q.emplace_front(ny,nx,(t+1)%6,d);
			}else{
				q.emplace_back(ny,nx,(t+1)%6,d+1);
			}
			q.emplace_back(y,x,(t+1)%6,d+1);
		}
	}

	int ans=min(dist[gy+101][gx+101]);
	if(ans==INF) puta(-1);
	else puta(ans);
	return 0;
}