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
	vl a(n),b(m);
	rep(i,n){ll t;cin>>t;t--;a[i]=t;}
	rep(i,m){ll t;cin>>t;t--;b[i]=t;}
	vl d(1000001,0);
	vl A=a,B=b;
	sort(all(A));
	sort(all(B));
	// vl ad(1000001,0);
	while(progress<1990){
		ll diff = getRand(0,min(max(A)-min(A), max(B)-min(B))+1);
		ll x=-1,y=-1,z=-1,w=-1;
		if(d[diff])continue;
		d[diff]=1;
		ll l=0,r=0;
		while(1){
			if(l==r){r++;continue;}
			if(r>=n)break;
			if(A[r]-A[l]<diff)r++;
			else if(A[r]-A[l]>diff)l++;
			else {x=l;z=r;break;}
		}
		if(x==-1)continue;
		l=0,r=0;
		while(1){
			if(l==r){r++;continue;}
			if(r>=m)break;
			if(B[r]-B[l]<diff)r++;
			else if(B[r]-B[l]>diff)l++;
			else {w=l;y=r;break;}
		}
		if(y==-1)continue;
		rep(i,n)if(a[i]==A[x]){x=i;break;}
		rep(i,n)if(a[i]==A[z]){z=i;break;}
		rep(i,m)if(b[i]==B[y]){y=i;break;}
		rep(i,m)if(b[i]==B[w]){w=i;break;}
		puta(x,y,z,w);
		return 0;
	}
	puta(-1);
	return 0;
}