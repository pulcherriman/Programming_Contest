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

#define _cTime (chrono::system_clock::now())
#define progress (chrono::duration_cast<chrono::milliseconds>(_cTime-_sTime).count())
#define reset _sTime=_cTime
auto reset;


int main(){
	cin.tie(0);
	ios::sync_with_stdio(false);
	ll h,w;
	cin>>h>>w;
	vl vv(w,0),vx(w,0),vp(w),hv(h,0),hx(h,0),hp(h);
	vvl a(h,vl(w));
	rep(i,h)rep(j,w){
		ll t=0;
		cin>>t;
		a[i][j]=t;
		vv[j]+=t;
		hv[i]+=t;
		if(chmax(vx[j],t)) vp[j]=i;
		if(chmax(hx[i],t)) hp[i]=j;;
	}
	ll ans=0;
	ll v=0;
	vs f(h,string(w,'#'));
	vs af(h,string(w,'#')), bf(h,string(w,'#'));
	rep(i,h){
		if(i%2)v+=hx[i];
		else v+=hv[i];
		rep(j,w)if(i%2 and hp[i]!=j)af[i][j]='.';
	}
	if(h%2==0)rep(j,w){
		if(abs(hp[h-1]-j)>1 and abs(hp[h-1]-j)%2==0)af[h-1][j]='#';
	}
	if(chmax(ans,v))f=af;

	bool rev=false;
	{
		v=0;
		swap(h,w);
		bf=vs(h,string(w,'#'));
		rep(i,h){
			if(i%2)v+=vx[i];
			else v+=vv[i];
			rep(j,w)if(i%2 and vp[i]!=j)bf[i][j]='.';
		}
		if(chmax(ans,v)){
			f=bf;
			rev=true;
		}
	}


	if(rev){
		swap(h,w);
		vs cf(h,string(w,'#'));
		rep(i,h)rep(j,w)cf[i][j]=f[j][i];
		f=cf;
	}
	rep(i,h)puta(f[i]);
	return 0;
}
