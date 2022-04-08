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
	int n;
	cin>>n;
	vi v={1};
	for(int i=9;i<=100000;i*=9){
		v.push_back(i);
	}
	for(int i=6;i<=100000;i*=6){
		v.push_back(i);
	}
	sort(all(v));
	v.erase(unique(all(v)),v.end());
	reverse(all(v));
    vi dp(100001,INF);
    dp[0]=0;
    queue<int> q({0});
    while(!q.empty()){
        int c=q.front(); q.pop();
        for(auto p:v){
            if(c+p<=100000 and dp[c+p]==INF){
                dp[c+p]=dp[c]+1;
                q.push(c+p);
            }
        }
    }
    cout<<dp[n]<<endl;
    return 0;
}
