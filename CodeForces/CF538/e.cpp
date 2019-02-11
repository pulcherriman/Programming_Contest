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

template<class T>void puta(T&&t){cout<<t<<endl;}
template<class H,class...T>void puta(H&&h,T&&...t){cout<<h<<' ';puta(t...);}
template<class S,class T>void tf(bool b,S t,T f){if(b)puta(t);else puta(f);}
void YN(bool b){tf(b,"YES","NO");}
void Yn(bool b){tf(b,"Yes","No");}
void yn(bool b){tf(b,"yes","no");}
template<class S,class T>ostream&operator<<(ostream&os,pair<S,T>p){os<<"["<<p.first<<", "<<p.second<<"]";return os;};
template<class S>auto&operator<<(ostream&os,vector<S>t){bool a=1;for(auto s:t){os<<(a?"":" ")<<s;a=0;}return os;}
template<class S>auto&operator>>(istream&is,vector<S>&t){for(S&a:t)cin>>a;return is;}

mt19937 _mt(chrono::steady_clock::now().time_since_epoch().count());
ll getRand(ll l,ll r){return uniform_int_distribution<ll>(l,r-1)(_mt);}

/*他のライブラリを入れる場所*/

int query(ll m){
	ll maskVal=24;
	if(maskVal>m)return 1; else return 0;
}
int fn(ll m){
	vl mask={14,24,9,19};
	return mask[m-1];
}

bool debug=0;
int q=0;
ll getMax(ll l=-1,ll r=1000000000){
	if(r-l<=1){
		return r;
	}
	ll m=(l+r)/2;
	q++;
	puta(">",m);
	int res;
	if(debug) res=query(m); else cin>>res;
	if(res){
		return getMax(m,r);
	}else{
		return getMax(l,m);
	}
}
constexpr int gcd(int a,int b){return b?gcd(b,a%b):a;}
constexpr int lcm(int a,int b){return a*b/gcd(a,b);}


int main(){
	cin.tie(0);
	ios::sync_with_stdio(false);
	ll n;
	cin>>n;
	ll mx=getMax();
	//puta(mx);
	set<int> s;
	vl val;//(1,mx);


	set<int> st;
	rep(i,min(60ll-q,n)){
		ll vl=0;
		do{
			vl=random_Range(1,n+1);
		}while(st.find(vl)!=st.end());
		st.insert(vl);
	}
	for(auto x:st){
		puta("?",x);
		ll t;
		if(debug) t=fn(x); else cin>>t;
		val.push_back(t);
	}
	sort(all(val));
	ll g=val[1]-val[0];
	rep(i,val.size())range(j,i+1,val.size()){
		//puta("gcd",g);
		if(val[i]!=val[j]) g=gcd(g,val[j]-val[i]);
		//puta(val[j]-val[i],g);
	}
	ll mn=mx-g*(n-1);
	puta("!",mn,g);
	return 0;
}