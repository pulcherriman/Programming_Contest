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

long double calc(vvl&gts, vvl&spr, long double val, int y, int x){
	return min((long double)gts[y][x], spr[y][x]+val);
}

int main(){
	cin.tie(0);
	ios::sync_with_stdio(false);
	ll w,h;
	cin>>w>>h;

	vs f(h);
	cin>>f;

	ll sy,sx,gy,gx,br=0;
	vvl spr(h,vl(w,LINF));
	vvl gts(h,vl(w,LINF));
	queue<tlll> q;
	rep(i,h)rep(j,w){
		if(f[i][j]=='*'){
			q.emplace(i,j,0);
		}else if(f[i][j]=='s'){
			sy=i, sx=j, br++;
		}else if(f[i][j]=='g'){
			gy=i, gx=j;
		}else if(f[i][j]=='.'){
			br++;
		}
	}

	while(!q.empty()){
		int y,x,d;
		tie(y,x,d) = q.front();
		q.pop();
		if(spr[y][x]!=LINF)continue;
		spr[y][x]=d;
		rep(i,4)if(spr[y+dy[i]][x+dx[i]]==LINF and ".s"s.find(f[y+dy[i]][x+dx[i]])!=-1){
			q.emplace(y+dy[i], x+dx[i], d+1);
		}
	}

	q.emplace(gy,gx,0);
	while(!q.empty()){
		int y,x,d;
		tie(y,x,d) = q.front();
		q.pop();
		if(gts[y][x]!=LINF)continue;
		gts[y][x]=d;
		rep(i,4)if(gts[y+dy[i]][x+dx[i]]==LINF and ".s"s.find(f[y+dy[i]][x+dx[i]])!=-1){
			q.emplace(y+dy[i], x+dx[i], d+1);
		}
	}


	long double ok=1e10, ng=0;
	while(abs(ok-ng)>=1e-9){
		long double mid=(ok+ng)/2, val = 0;

		rep(i,h)rep(j,w)if(".s"s.find(f[i][j])!=-1){
			val += calc(gts, spr, mid, i, j);
		}

		if(br*mid >= val){
			ok=mid;
		}else{
			ng=mid;
		}
	}
	long double ans = calc(gts, spr, ok, sy, sx);
	fcout(15)<<ans<<endl;
	return 0;
}