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
	
	int h,w;
	cin>>h>>w;
	vs f(h);
	rep(i,h)cin>>f[i];
	using data=tuple<int,int,string>;
	queue<data> q;
	q.emplace(h-1,f[h-1].find('s'),"");
	
	while(!q.empty()){
	    int i,j;
	    string s;
	    tie(i,j,s)=q.front();
	    if(i==0){
	        cout<<s<<endl;
	        return 0;
	    }
	    q.pop();
	    for(auto v:{-1,0,1}){
	        if(j+v<0 or j+v>=w)continue;
	        if(f[i-1][j+v]=='x')continue;
	        string u=v!=-1?v!=0?"R":"S":"L";
	        q.emplace(i-1,j+v,s+u);
	    }
	}
	cout<<"impossible"<<endl;
	return 0;
}
