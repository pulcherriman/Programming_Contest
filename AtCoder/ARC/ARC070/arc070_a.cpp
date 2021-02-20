 
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
#define rrep(i,n) for(int i=n-1;i>=0;i--)
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
#define MOD 1000000007
void bulk(){}template<class H,class...T>void bulk(H&h,T&...t){cin>>h;bulk(t...);}
#define get(...) int __VA_ARGS__; bulk(__VA_ARGS__);

int digsum(int n){if(n<10)return n; return n%10+digsum(n/10);}

int main(){
	get(n);
	rep(i,INF){
	    n-=i;
	    if(n<=0){cout<<i<<endl;return 0;}
	}
	return 0;
}
