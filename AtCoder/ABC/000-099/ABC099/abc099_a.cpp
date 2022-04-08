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
	if (n>999) cout<<"ABD"<<endl;
	else  cout<<"ABC"<<endl;
    return 0;
}