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
#define LINF ((ll)1ll<<62)
#define INF ((int)1<<30)
#define EPS (1e-10)
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
int sgn(double&r){return (r>EPS)-(r<-EPS);} // a>0  : sgn(a)>0
int sgn(double&a,double&b){return sgn(a-b);} // b<=c : sgn(b,c)<=0

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
double p,t;

double calc(double l, double r, double a, double b, int dep, double cur_prob=1.0){
	// puta("  call :", l,r,a,b,dep);
	if(dep==0){
		double td=(l+r)/2;
		if(sgn(a,td)<=0 and sgn(td,b)<=0)return cur_prob;
		else return 0;
	}
	if(sgn(a,l)<=0 and sgn(r,b)<=0) return cur_prob;
	if(sgn(l,b)>0 or sgn(a,r)>0) return 0;
	double m=(l+r)/2,ret=0;
	if(m-EPS<=t){
		ret=calc(l,m,a,b,dep-1, cur_prob*(p))+calc(m,r,a,b,dep-1, cur_prob*(1-p));
	}else{
		ret=calc(l,m,a,b,dep-1, cur_prob*(1-p))+calc(m,r,a,b,dep-1, cur_prob*(p));
	}
	// puta("return :",l,r,a,b,dep,"=",ret);
	return ret;
}
int main(){
	cin.tie(0);
	ios::sync_with_stdio(false);
	ll k; double l,r,e;
	cin>>k>>l>>r>>p>>e>>t;

	fcout(10)<<calc(l,r,t-e,t+e,k)<<endl;
	return 0;
}