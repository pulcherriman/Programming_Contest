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
template<class S>auto&operator<<(ostream&os,vector<S>t){bool b=1;for(auto s:t)os<<(exchange(b,0)||strlen(abi::__cxa_demangle(typeid(S).name(),0,0,0))>20?"":" ")<<s;return os<<endl;}

int main(){
	cin.tie(0);
   	ios::sync_with_stdio(false);
	
	int n;
	cin>>n;
	int ans=INF;
	rep(i,n){
		string s;
		cin>>s;
		int cnt=0;
		for(int j=s.size()-1;j>=0;j--){
			if(s[j]=='0')cnt++;
			else break;
		}
		ans=min(ans,cnt);
	}
	cout<<ans<<endl;
	return 0;
}
