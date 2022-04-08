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
	
	int n;
	cin>>n;
    vi pr(100,1);
    range(i,1,n+1){
        int p=i;
        range(j,2,101){
            if(p%j==0){
                pr[j]++;
                p/=j;
                j--;
            }
        }
    }
    int ans=0;
    rep(i,100){
        if(pr[i]>74)ans++;
        range(j,i+1,100){
            if(pr[i]>4 and pr[j]>14) ans++;
            if(pr[i]>14 and pr[j]>4) ans++;
            if(pr[i]>2 and pr[j]>24) ans++;
            if(pr[i]>24 and pr[j]>2) ans++;
            range(k,j+1,100){
                if(pr[i]>2 and pr[j]>4 and pr[k]>4)ans++;
                if(pr[i]>4 and pr[j]>2 and pr[k]>4)ans++;
                if(pr[i]>4 and pr[j]>4 and pr[k]>2)ans++;
            }
        }
    }
    cout<<ans<<endl;
	return 0;
}
