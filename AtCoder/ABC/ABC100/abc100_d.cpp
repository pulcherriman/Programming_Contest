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
	
    int n,m;
    cin>>n>>m;
    struct Cake{ll x,y,z; Cake(){x=y=z=0;} void get(){cin>>x>>y>>z;}};
    vector<Cake> cake(n);
    for(auto&p:cake)p.get();
    ll ans=0;
    for(auto a:{-1,1})for(auto b:{-1,1})for(auto c:{-1,1}){
        sort(all(cake),[&a,b,c](Cake p, Cake q){return (p.x*a+p.y*b+p.z*c)<(q.x*a+q.y*b+q.z*c);});
        Cake total;
        rep(i,m){
            total.x+=cake[i].x;
            total.y+=cake[i].y;
            total.z+=cake[i].z;
        }
        ans=max(ans,llabs(total.x)+llabs(total.y)+llabs(total.z));
    }
    cout<<ans<<endl;
	return 0;
}
