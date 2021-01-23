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

#define _cTime (chrono::system_clock::now())
#define progress (chrono::duration_cast<chrono::milliseconds>(_cTime-_sTime).count())
#define reset _sTime=_cTime
auto reset;

mt19937 _mt(chrono::steady_clock::now().time_since_epoch().count());
ll getRand(ll l,ll r){return uniform_int_distribution<ll>(l,r-1)(_mt);}

int main(){
	cin.tie(0);
	ios::sync_with_stdio(false);
	ll n,m;
	cin>>n>>m;
	vvl edge(n);
	rep(i,m){
		ll a,b;
		cin>>a>>b;
		a--;b--;
		edge[a].push_back(b);
	}
	double ans=100000;
	vl sel(n,-1);
	vl sel2(n,-1);
	{
		vd cost(n,0);
		vd odds(n,0);
		odds[0]=1;
		rep(i,n){
			double v=edge[i].size();
			for(auto&nxt:edge[i]){
				odds[nxt]+=odds[i]/v;
				cost[nxt]+=(cost[i]+odds[i])/v;
			}
		}
		ans=cost[n-1];
		rep(i,n){
			if(edge[i].size()==1)continue;
			double v=0,v2=0;
			for(auto&nxt:edge[i]){
				double p=cost[n-1]-cost[nxt];
				ll tmp=sel[i];
				if(v<p){
					swap(v,p);
					sel[i]=nxt;
				}
				if(v2<p){
					swap(v2,p);
					sel2[i]=tmp;
				}
			}
		}
	}
	rep(s,n){
		if(sel[s]==-1)continue;
		vd cost(n,0);
		vd odds(n,0);
		odds[0]=1;
		rep(i,n){
			double v=edge[i].size()-(i==s?1:0);
			for(auto&nxt:edge[i]){
				if(i==s and nxt==sel[i])continue;
				odds[nxt]+=odds[i]/v;
				cost[nxt]+=(cost[i]+odds[i])/v;
			}
		}
		if(cost[n-1]!=0)chmin(ans,cost[n-1]);
	}
	rep(s,n){
		if(sel2[s]==-1)continue;
		vd cost(n,0);
		vd odds(n,0);
		odds[0]=1;
		rep(i,n){
			double v=edge[i].size()-(i==s?1:0);
			for(auto&nxt:edge[i]){
				if(i==s and nxt==sel2[i])continue;
				odds[nxt]+=odds[i]/v;
				cost[nxt]+=(cost[i]+odds[i])/v;
			}
		}
		if(cost[n-1]!=0)chmin(ans,cost[n-1]);
	}

	fcout(10)<<ans<<endl;
	return 0;
}