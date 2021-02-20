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
template<class S>auto&operator<<(ostream&os,vector<S>t){bool a=1; for(auto s:t){os<<(a?"":"\n")<<s; a=0;} return os;}

using data=tuple<int,int,int>;
queue<data> q;

int main(){
	cin.tie(0);
   	ios::sync_with_stdio(false);
   	int n,m,l;
   	cin>>n>>m>>l;
   	vi t(n);
   	vvi M(n),L(n);
   	vector<pii> Q;
   	rep(i,n)cin>>t[i];
   	int last=0;
   	rep(i,m){
   	    int x,a;
   	    cin>>x>>a;
   	    M[x-1].push_back(a);
   	    last=max(last,a);
   	}
   	rep(i,l){
   	    int x,a;
   	    cin>>x>>a;
   	    L[x-1].push_back(a);
   	}
   	rep(i,n){
   	    sort(all(L[i]));
   	    for(auto&d:M[i]){
   	        int index=upper_bound(all(L[i]),d+t[i])-L[i].begin();
   	        if(index!=L[i].size()) Q.emplace_back(d,L[i][index]+t[i]+1);
   	    }
   	}
   	sort(all(Q),[](pii a,pii b){return a.fs<b.fs;});
   	sort(all(Q),[](pii a,pii b){return a.sc<b.sc;});
   	//cout<<Q<<endl;
    int today=1,ans=0;
    rep(i,Q.size()){
        if(Q[i].fs<today)continue;
        ans+=2;
        today=Q[i].sc;
    }
   	if(last>=today)ans++;
   	cout<<ans<<endl;
	return 0;
}
