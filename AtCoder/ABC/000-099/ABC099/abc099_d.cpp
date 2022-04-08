#include <bits/stdc++.h>
#include <cxxabi.h>
using namespace std;
using ll=long long;
using vi=vector<int>;
using vvi=vector<vi>;
using pii=pair<int,int>;
#define rep(i,n) range(i,0,n)
#define range(i,a,n) for(int i=a;i<n;i++)
#define all(a) a.begin(),a.end()
#define LINF    ((ll)1ll<60)
#define INF     ((int)1<<30)
#define EPS     (1e-9)
#define MOD     (1000000007)
template<class S,class T>ostream& operator<<(ostream&os,pair<S,T>p){os<<"["<<p.first<<", "<<p.second<<"]";return os;};
template<class T,typename I=typename T::iterator>auto&operator<<(ostream&os,T t){bool b=1;for(auto s:t)os<<(abi::__cxa_demangle(typeid(decltype(*declval<I>())).name(),0,0,0)[2]=='d'||exchange(b,0)?"":" ")<<s;return os<<endl;}

int main(){
	int n,c;
	cin>>n>>c;
	vvi f(3,vi(c,0));
	vvi cost(c,vi(c));
	rep(i,c)rep(j,c)cin>>cost[i][j];
	rep(i,n){
	    rep(j,n){
	        int t; cin>>t;
	        f[(i+j)%3][t-1]++;;
	    }
	}
	int ans=INF;
	rep(q,c)rep(w,c)rep(e,c){
	    if(q==w or q==e or w==e) continue;
	    vi color={q,w,e};
	    int p=0;
	    rep(i,3)rep(j,c){
	        p+=cost[j][color[i]]*f[i][j];
	    }
	    ans=min(ans,p);
	}
	cout<<ans<<endl;
    return 0;
}
