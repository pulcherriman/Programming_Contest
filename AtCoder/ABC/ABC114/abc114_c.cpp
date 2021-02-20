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

ll n;
vi ans;

void rec(ll p){
    if(p<=n){
        auto s=to_string(p);
        if(s.find('3')!=-1 and s.find('5')!=-1 and s.find('7')!=-1)
            ans.push_back(p);
        rec(p*10+3);
        rec(p*10+5);
        rec(p*10+7);
    }
}

int main(){
	cin.tie(0);
   	ios::sync_with_stdio(false);
	
	cin>>n;
	rec(0);
	cout<<ans.size();
	return 0;
}
