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


int main(){
	cin.tie(0);
	ios::sync_with_stdio(false);
	ll n;
	cin>>n;
	vl a(n);
	cin>>a;
	vl lr(n),rl(n),z(n,0),lrz(n),rlz(n);
	rep(i,n){if(a[i]==0)z[i]=1;}
	partial_sum(all(a),lr.begin());
	partial_sum(rall(a),rl.rbegin());
	partial_sum(all(z),lrz.begin());
	partial_sum(rall(z),rlz.rbegin());
	int l=n-1,r=0;
	rrep(i,n){
		if(z[i]==1 and lrz[i]>=lr[i])break;
		l=i;
	}
	rep(i,n){
		if(z[i]==1 and rlz[i]>=rl[i])break;
		r=i;
	}
	//puta(pll(l,r));

	//l=0,r=n-1;
	vl b(n,0);
	rep(i,n)if(a[i]%2==0)b[i]=1;else b[i]=-1;

	vl ad(n+1,0);
	partial_sum(all(b),ad.begin()+1);
	//puta(ad);
	ll und=(l>0?lr[l-1]:0)+(lr[n-1]-lr[r]);
	ll ans=und;
	//puta(ans);
	range(i,l,r+1)if(a[i]%2==0)ans++;
	ll lm=-LINF,mr=-LINF;
	vl al(n+1,0),ar(n+1,0);
	range(i,l,r+2){
		chmax(al[i],ad[i]-ad[l]);
		chmax(ar[i],ad[r+1]-ad[i]);
	}
	rep(i,n)chmax(al[i+1],al[i]);
	rrep(i,n)chmax(ar[i+1],ar[i]);
	ll x=0;
	range(i,l,r+2){
		chmax(x,al[i]+ar[i]);
	}
	puta(max(und,ans-x));
	return 0;
}