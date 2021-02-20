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

	using pdi = pair<double,double>;
	vector<pdi> p(n);
	rep(i,n){
		cin>>p[i].fs>>p[i].sc;
	}
	sort(all(p));

	double ans = 0;
	vd ltr(n,0.0), rtl(n,0.0);

	double r1=0.0, r2=0.0;
	rep(j,n){
		ltr[j]=r1;
		r1=pow(pow(r1,3)+pow(p[j].sc,3), 1.0/3);
		r1=max(0.0,r1-(p[j+1].fs-p[j].fs));
	}
	rrep(j,n){
		rtl[j]=r2;
		r2=pow(pow(r2,3)+pow(p[j].sc,3), 1.0/3);
		r2=max(0.0,r2-(p[j].fs-p[j-1].fs));
	}

	rep(i,n){
		//puta(r1,p[i].sc,r2);
		chmax(ans, pow(pow(ltr[i],3) + pow(p[i].sc,3) + pow(rtl[i],3), 1.0/3));
	}

	fcout(10)<<ans<<endl;
	return 0;
}