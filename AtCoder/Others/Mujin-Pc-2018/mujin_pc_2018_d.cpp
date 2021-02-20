#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using vi=vector<int>;
using vvi=vector<vi>;
using vd=vector<double>;
using vvd=vector<vd>;
using vb=vector<bool>;
using vvb=vector<vb>;
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
	int a,b,ans=0;
	vvb res(1000,vb(1000,false));

	cin>>a>>b;
	if(a>b)swap(a,b);

	range(i,1,a+1)range(j,1,b+1){
	    if(i>j){
	        if(res[j][i]==1)ans++;
	        continue;
	    }
	    int x=i,y=j;
	    bool ok=true;
	    rep(c,100){
			if(x>y) swap(x, y);
			if(x<10);
			else if(x<100)x=x%10*10+x/10;
			else x=x%10*100+x/10%10*10+x/100;
			if ( x < y ) y = y - x; else x = x - y;
			if ( x > y ) swap(x, y);
            if(x<=11 or y<=11) ok=false;
            if(!ok or res[x][y])break;
	    }
	    if(ok){
	        res[i][j]=res[j][i]=true;
	        ans++;
	    }
	}
	cout<<ans<<endl;
	return 0;
}
