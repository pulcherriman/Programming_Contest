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
#define LINF    	((ll)1ll<<60)
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
	
	int n,m;
	cin>>n>>m;
	using data=tuple<int,int,int>;
	vector<data> ans;
	vector<vector<pii>> d(n+1);
	rep(i,m){
	    int p,y;
	    cin>>p>>y;
	    d[p].emplace_back(y,i);
	}
	rep(i,n+1){
	    sort(all(d[i]));
	    rep(j,d[i].size()){
	        ans.emplace_back(d[i][j].second,i,j+1);
	    }
	}
	sort(all(ans));
	for(auto&ln:ans){
	    int p,l,r;
	    tie(p,l,r)=ln;
	    cout<<to_string(l+1000000).substr(1)<<to_string(r+1000000).substr(1)<<endl;
	}
}
