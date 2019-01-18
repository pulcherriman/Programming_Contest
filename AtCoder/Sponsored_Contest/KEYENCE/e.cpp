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

/*他のライブラリを入れる場所*/

static const int MAX_SIZE = 1 << 17;

typedef long long Int;
ll segMin[2 * MAX_SIZE - 1], segAdd[2 * MAX_SIZE - 1];

void add(int a, int b, ll x, int k = 0, int l = 0, int r = MAX_SIZE)
{
	if (r <= a || b <= l) return;
	
	if (a <= l && r <= b){ 
		segAdd[k] += x; 
		return;
	}
	
	add(a, b, x, k * 2 + 1, l, (l + r) / 2);
	add(a, b, x, k * 2 + 2, (l + r) / 2, r);

	segMin[k] = min(segMin[k * 2 + 1] + segAdd[k * 2 + 1], segMin[k * 2 + 2] + segAdd[k * 2 + 2]);
}

ll getMin(int a, int b, int k = 0, int l = 0, int r = MAX_SIZE)
{
	if (r <= a || b <= l) return (LLONG_MAX);
	
	if (a <= l && r <= b) return (segMin[k] + segAdd[k]);
	
	ll left = getMin(a, b, k * 2 + 1, l, (l + r) / 2);
	ll right = getMin(a, b, k * 2 + 2, (l + r) / 2, r);
	
	return (min(left, right) + segAdd[k]);
	
}
int main(){
	cin.tie(0);
	ios::sync_with_stdio(false);
	int n; ll d;
	cin>>n>>d;
	vl a(n);
	rep(i,n){
		cin>>a[i];
		add(i,i+1,a[i]+d*i);
	}
	ll ans=0;
	int p=min_element(all(a))-a.begin();
	ll t=(p*(p+1)/2)+((n-p-1)*(n-p)/2);
	ans=accumulate(all(a),0ll)+a[p]*(n-2)+t*d;

	rep(j,n){
		if(j!=p){
			ll c=abs(j-p)*d+a[p];
			ll e=min(getMin(0,j),getMin(j+1,n));
			if(c>e){
				ans-=c-e;
				//puta("j",j,c,e,c-e);
			}
		}
		add(0,j+1,d);
		add(j+1,n,-d);
	}
	cout<<ans<<endl;
	return 0;
}