#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using vi=vector<int>;
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
	
	int h,w;
	cin>>h>>w;
	vvi f(h,vi(w));
	rep(i,h)rep(j,w)cin>>f[i][j];
	int ans=0;
	vvi answers;
	rep(i,h)rep(j,w){
	    if(f[i][j]%2==0)continue;
	    if(j+1!=w){
	        f[i][j]--;
	        f[i][j+1]++;
            ans++;
	        answers.push_back(vi{i+1,j+1,i+1,j+2});
	    }else if(i+1!=h){
	        f[i][j]--;
	        f[i+1][j]++;
            ans++;
	        answers.push_back(vi{i+1,j+1,i+2,j+1});
	    }
	}
	cout<<ans<<endl;
	for(auto a:answers)cout<<a<<endl;
	
	return 0;
}
