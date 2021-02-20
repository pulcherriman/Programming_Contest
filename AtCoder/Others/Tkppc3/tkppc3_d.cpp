#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using vi=vector<ll>;
using vvi=vector<vi>;
using vd=vector<double>;
using vvd=vector<vd>;
using vl=vector<ll>;
using vvl=vector<vl>;
using pii=pair<int,int>;
using vs=vector<string>;
#define rep(i,n) range(i,0,n)
#define range(i,a,n) for(int i=a;i<n;i++)
#define all(a) a.begin(),a.end()
#define LINF    	((ll)1ll<60)
#define INF     	((int)1<<30)
#define EPS     	(1e-9)
#define MOD     	(1000000007)
#define fcout(a)	cout<<setprecision(a)<<fixed
#define fs 			first
#define sc			second
#define PI			3.141592653589793

template<class S,class T>ostream& operator<<(ostream&os,pair<S,T>p){os<<"["<<p.first<<", "<<p.second<<"]";return os;};
template<class S>auto&operator<<(ostream&os,vector<S>t){bool a=1; for(auto s:t){os<<(a?"":" ")<<s; a=0;} return os;}

int main(){
	cin.tie(0);
   	ios::sync_with_stdio(false);
	
	int h,w,q;
	cin>>h>>w>>q;
	vi a(h),b(w),ws(w),hs(h);
	rep(i,h){
	    cin>>a[i];
	    if(i<2)hs[i]=a[i];
	    else hs[i]=a[i]+hs[i-2];
	}
	rep(i,w){
	    cin>>b[i];
	    if(i<2)ws[i]=b[i];
	    else ws[i]=b[i]+ws[i-2];
    }
	rep(_,q){
	    int px,py,qx,qy;
	    ll ans=0,exlen,eylen,oxlen,oylen;
	    cin>>py>>px>>qy>>qx;
	    px--,py--,qx--,qy--;
	    int oxs,oxl,oys,oyl,exs,exl,eys,eyl;
	    oxs= px%2 ? px : px+1;
        oxl= qx%2 ? qx : qx-1;
        oys= py%2 ? py : py+1;
        oyl= qy%2 ? qy : qy-1;
	    exs= px%2==0 ? px : px+1;
        exl= qx%2==0 ? qx : qx-1;
        eys= py%2==0 ? py : py+1;
        eyl= qy%2==0 ? qy : qy-1;
        eylen=(eyl<0?0:hs[eyl])-(eys<2?0:hs[eys-2]);
        exlen=(exl<0?0:ws[exl])-(exs<2?0:ws[exs-2]);
        oylen=(oyl<0?0:hs[oyl])-(oys<2?0:hs[oys-2]);
        oxlen=(oxl<0?0:ws[oxl])-(oxs<2?0:ws[oxs-2]);
        // cout<<pii(px,qx)<<endl;
        // cout<<pii(exs,exl)<<endl;
        // cout<<pii(oxs,oxl)<<endl;
        // cout<<pii(eylen,oylen)<<endl;
        // cout<<pii(exlen,oxlen)<<endl;
        ans+=eylen*exlen;
        ans+=oylen*oxlen;
        ans-=eylen*oxlen;
        ans-=oylen*exlen;
        cout<<ans<<endl;
	}
	return 0;
}
