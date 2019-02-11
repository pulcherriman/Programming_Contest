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

mt19937 _mt(chrono::steady_clock::now().time_since_epoch().count());
ll getRand(ll l,ll r){return uniform_int_distribution<ll>(l,r-1)(_mt);}

using point=complex<double>;
using data=pair<int,point>;

tuple<double,int,double> calcScore(vector<point>&def,vi&p){
	int n=200;
	double ret=0;
	double ave=0;
	int ind=0;double mval=0;
	vd d(n);
	rep(i,n){
		d[i]=abs(def[p[i]]-def[p[(i+1)%n]]);

	}
	ave=sum(d)/n;
	rep(i,n){
		if(chmax(mval,abs(ave-d[i])))ind=i;
		ret+=(d[i]-ave)*(d[i]-ave);
	}
	return make_tuple(ret,ind,ave);
}

int main(){
	cin.tie(0);
	ios::sync_with_stdio(false);
	ll n;
	cin>>n;
	vector<data> p(n);
	vector<point> def(n);
	point ave(0,0);
	rep(i,n){
		double x,y; cin>>x>>y;
		def[i]=point(x,y);
		p[i]=data(i,def[i]);
		ave+=p[i].sc;
	}
	vi ans(n);
	ave/=n;
	rep(i,n){
		sort(all(p),[&](data a,data b){return abs(ave-a.sc)>abs(ave-b.sc);});
		ans[i]=(p.back().fs);
		ave=p.back().sc;
		p.pop_back();
	}

	double score; int ind; double avr;
	tie(score,ind,avr)=calcScore(def,ans);

	range(lp,1,3){
		rep(x,n){
			vi nans;
			nans=ans;
			swap(nans[x],nans[(x+lp)%n]);
			double nscore,navr; int nind;
			tie(nscore,nind,navr)=calcScore(def,nans);
			if(nscore<score){
				ans=nans;
				score=nscore;
				ind=nind;
				avr=navr;
			}
		}
	}


	int ch=0,suc=0,fal=0;
	vi sucind;
	while(progress<1900){
		if(fal>10)ind=getRand(0,n);
		int x=ind,y=getRand(0,n);
		double cdist=abs(def[ans[x]]-def[ans[(x+1)%n]]);
		vi nans;
		if(progress<1200){
			while(abs(avr-abs(def[ans[x]]-def[ans[y]]))>abs(avr-cdist) or x==y){
				y=getRand(0,n);
			}
			rep(i,n){
				if(i==y)continue;
				nans.push_back(ans[i]);
				if(i==x)nans.push_back(ans[y]);
			}
		}else{
			while(x==y){
				y=getRand(0,n);
			}
			nans=ans;
			swap(nans[x],nans[y]);
		}
 
		double nscore,navr; int nind;
		tie(nscore,nind,navr)=calcScore(def,nans);
		ch++;
		if(nscore<score){
			suc++;
			ans=nans;
			score=nscore;
			ind=nind;
			avr=navr;
			fal=0;
			sucind.push_back(ch);
		}else{
			fal++;
		}
	}
	rep(i,n)puta(ans[i]);
	return 0;
}