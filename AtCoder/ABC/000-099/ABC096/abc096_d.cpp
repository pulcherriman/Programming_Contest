 
#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using vi=vector<int>;
using vvi=vector<vi>;
using pii=pair<int,int>;
#define rep(i,n) for(int i=0;i<n;i++)
#define range(i,a,n) for(int i=a;i<n;i++)
#define all(a) a.begin(),a.end()
#define rall(a) a.rbegin(),a.rend()
#define INF 1e9
#define EPS 1e-9
#define MOD (1e9+7)
void put(string d){}template<class H,class...T>void put(string d,H&h,T&...t){cout<<h;if(sizeof...(t))cout<<d;put(d,t...);}
template<class T>void puti(T&a,string d=" "){bool f=1;for(auto&_:a)cout<<(exchange(f,0)?"":d)<<_;cout<<endl;}
template<class T>void putii(T&a,string d=" "){for(auto&_:a)puti(_,d);}
class Eratosthenes{
  public:
    int n, sqlim;
    vector<bool> prime;
    Eratosthenes(int N):n(N+1){
        sqlim=(int)ceil(sqrt(n));
        prime=vector<bool>(n,1); prime[0]=prime[1]=0;
        for(int i=2;i<=sqlim;i++) if(prime[i]) for(int j=i*i;j<=n;j+=i) prime[j]=0;}
    vector<int> primeArray(){vi ret; for(int i=2;i<=55555;i++) if(prime[i]) ret.push_back(i); return ret;}
};


int main(){
	int n;cin>>n;
	Eratosthenes e(55555);
	vi v=e.primeArray(),ans;
	for(auto i:v){
		if(i%5==1)ans.push_back(i);
		if(ans.size()==n)break;
	}
	puti(ans);
	return 0;
}
