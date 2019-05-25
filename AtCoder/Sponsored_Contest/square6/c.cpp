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

pll bfs(vs&f, int sy, int sx, bool down){
	int h=f.size();
	int w=f[0].size();
	int v=down?0:h;
	vvb s(h,vb(w,false));
	queue<pll> q;
	q.emplace(sy,sx);
	while(!q.empty()){
		int y,x;
		tie(y,x)=q.front();
		q.pop();
		if(s[y][x])continue;
		s[y][x]=true;
		if(down){
			chmax(v,y);
			if(x+1<w and f[y][x+1]=='.')q.emplace(y,x+1);
			if(y+1<h and f[y+1][x]=='.')q.emplace(y+1,x);
		}else{
			chmin(v,y);
			if(x-1>=0 and f[y][x-1]=='.')q.emplace(y,x-1);
			if(y-1>=0 and f[y-1][x]=='.')q.emplace(y-1,x);
		}
	}
	return down?pll(0,v):pll(v,h-1);
}

int main(){
	cin.tie(0);
	ios::sync_with_stdio(false);
	ll h,w;
	cin>>h>>w;
	vs f(h);
	cin>>f;
	pll dw=bfs(f,0,0,true);
	pll up=bfs(f,h-1,w-1,false);
	rep(i,h){
		if(count(all(f[i]),'.')!=w) continue;
		if(i<=dw.sc and up.fs<=i){
			puta("Yay!");
			return 0;
		}
	}
	puta(":(");
	return 0;
}