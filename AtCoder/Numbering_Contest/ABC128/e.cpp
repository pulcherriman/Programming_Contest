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

struct RMQRUQ {
  int n;
  vector<int> dat, lazy;
 
  RMQRUQ(){}
  RMQRUQ(int n_) {
    n = 1; while(n < n_) n *= 2;
    dat.assign(n*2, INT_MAX);
    lazy.assign(n*2, INT_MAX);
  }
 
  void eval(int len, int k) {
    if(lazy[k] == INT_MAX) return;
    if(k*2+1 < n*2-1) {
      lazy[2*k+1] = lazy[k];
      lazy[2*k+2] = lazy[k];
    }
    dat[k] = lazy[k];
    lazy[k] = INT_MAX;
  }
 
  // [a, b)
  ll update(int a, int b, ll x, int k, int l, int r) {
    eval(r-l, k);
    if(b <= l || r <= a) return dat[k];
    if(a <= l && r <= b) {
      lazy[k] = x;
      return lazy[k];
    }
    return dat[k] = min(update(a, b, x, 2*k+1, l, (l+r)/2), update(a, b, x, 2*k+2, (l+r)/2, r));
  }
  ll update(int a, int b, ll x) { return update(a, b, x, 0, 0, n); }
 
  // [a, b)
  ll query(int a, int b, int k, int l, int r) {
    eval(r-l, k);
    if(b <= l || r <= a) return INT_MAX;
    if(a <= l && r <= b) return dat[k];
    ll vl = query(a, b, 2*k+1, l, (l+r)/2);
    ll vr = query(a, b, 2*k+2, (l+r)/2, r);
    return min(vl, vr);
  }
  ll query(int a, int b) { return query(a, b, 0, 0, n); }
};
 
map<int,int> zip;
vi unzip(700000,-1);

int compress(vi &x) {
    sort(x.begin(), x.end());
    x.erase(unique(x.begin(),x.end()),x.end());
    for(int i = 0; i < x.size(); i++){
        zip[x[i]] = i;
        unzip[i] = x[i];
    }
    return x.size();
}

vvi d;
vi x;

RMQRUQ st(700000);
int main(){
	cin.tie(0);
	ios::sync_with_stdio(false);
	ll n,q;
	cin>>n>>q;
	d.resize(n);
	rep(i,n){
		d[i].resize(3);
		cin>>d[i];
		d[i][0]-=d[i][2];
		d[i][1]-=d[i][2];
		x.push_back(d[i][0]);
		x.push_back(d[i][1]);
		x.push_back(d[i][0]+1);
		x.push_back(d[i][1]+1);
		x.push_back(d[i][0]-1);
		x.push_back(d[i][1]-1);
	}
	ll t=compress(x);
	
	st.update(0,700000,-1);
	sort(all(d),[](vi a,vi b){return a[2]>b[2];});
	rep(i,n){
		st.update(zip[d[i][0]],zip[d[i][1]],d[i][2]);
	}
	
	rep(i,q){
		try{
			int p;
			cin>>p;
			ll y=lower_bound(all(x),p)-x.begin();
			chmax(y,0ll);
			chmin(y,t);
			if(y>=t-1){
				puta(-1);
			}else puta(st.query(y,y+1));
		}catch(...){
			puta(-1);
		}
	}

	return 0;
}
