 
#include <bits/stdc++.h>
using namespace std;
using vi=vector<int>;
using vvi=vector<vi>;
using vs=vector<string>;
using msi=map<string,int>;
using mii=map<int,int>;
using pii=pair<int,int>;
using vlai=valarray<int>;
using ll=long long;
#define rep(i,n) for(int i=0;i<n;i++)
#define range(i,s,n) for(int i=s;i<n;i++)
#define all(a) a.begin(),a.end()
#define rall(a) a.rbegin(),a.rend()
#define fs first
#define sc second
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define INF 1e9
#define EPS 1e-9
class Eratosthenes{
  public:
    int n, sqlim;
    vector<bool> prime;
    Eratosthenes(int N):n(N+1){
        sqlim=(int)ceil(sqrt(n));
        prime=vector<bool>(n,1); prime[0]=prime[1]=0;
        for(int i=2;i<=sqlim;i++) if(prime[i]) for(int j=i*i;j<=n;j+=i) prime[j]=0;}
    vector<int> primeArray(int s=0, int l=10000){vi ret; for(int i=s;ret.size()!=l;i++) if(prime[i]) ret.push_back(i); return ret;}
};


int main(){
	int n;
	cin>>n;
	Eratosthenes e(100001);
	vi is(100000,0);
    for(int i=1;i<=99999;i+=2){
	    if(e.prime[i] && e.prime[(i+1)/2]){
	        is[i]=1;
	    }
	}
	partial_sum(all(is),is.begin());
	rep(i,n){
	    int l,r;cin>>l>>r;
	    cout<<is[r]-is[max(l-2,0)]<<endl;
	}
	return 0;
}
