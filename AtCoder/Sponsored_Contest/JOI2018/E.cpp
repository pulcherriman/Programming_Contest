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

struct segTree{
	vl val,lazy;
	vector<bool> lazyFlag;
	int N;
	segTree():segTree(100000){}
	segTree(int n){
		N=1;
		while(N<n)N*=2;
		val.resize(N*2,0);
		lazy.resize(N*2,0);
		lazyFlag.resize(N*2,false);
	}
	
	void eval(int k, int l, int r){
		if(lazyFlag[k]){
			val[k]=lazy[k];
			if(r-l>1){
				lazy[2*k]=lazy[2*k+1]=lazy[k];
				lazyFlag[2*k]=lazyFlag[2*k+1]=true;
			}
			lazyFlag[k]=false;
		}
	}

	void update(int a, int b, ll x){return update(a,b,1,0,N,x);}
	void update(int a, int b, int k, int l, int r, ll x){
		eval(k,l,r);
		if(r<=a or l>=b) return;
		if(a<=l and r<=b) {
			lazy[k]=x;
			lazyFlag[k]=true;
			eval(k,l,r);
		}else{
			int m=(l+r)/2;
			update(a,b,2*k,l,m,x);
			update(a,b,2*k+1,m,r,x);
			val[k]=max(val[2*k],val[2*k+1]);
		}
	}
	
	ll query(int a, int b){return query(a,b,1,0,N);}
	ll query(int a, int b, int k, int l, int r){
		if(a>=b)return 0;
		eval(k,l,r);
		if(r<=a or l>=b) return -LINF;
		if(a<=l and r<=b) return val[k];
		int m=(l+r)/2;
		return max(query(a,b,k*2,l,m),query(a,b,k*2+1,m,r));
	}
};



int main(){
	cin.tie(0);
	ios::sync_with_stdio(false);
	ll n,m;
	cin>>n>>m;
	vl a(n);
	cin>>a;
	vector<pll> q(m);
	rep(i,m){
		cin>>q[i].fs>>q[i].sc;
	}
	sort(all(q));
	segTree t(n);
	rep(i,n)t.update(i,i+1,-i-1);
	
	rrep(i,m){
		t.update(q[i].fs-1,q[i].sc,-(q[i].fs));
	}

	segTree s(n+1);
	rep(i,n){
		ll tv=-t.query(i,i+1);
		ll v=0;
		if(tv>0)v=s.query(0,tv-1);
		if(s.query(i,i+1)<v+a[i])s.update(i,i+1,v+a[i]);
	}
	puta(s.query(0,n+1));
	return 0;
}