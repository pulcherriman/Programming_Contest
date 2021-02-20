 
#include <bits/stdc++.h>
using namespace std;
using vi=vector<int>;
using vvi=vector<vi>;
using vs=vector<string>;
using msi=map<string,int>;
using mii=map<int,int>;
//using pii=pair<int,int>;
using vlai=valarray<int>;
using ll=long long;
using pii=pair<ll,ll>;
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
#define MOD (1e9+7)
void get(){}template<class H,class...T>void get(H&h,T&...t){cin>>h;get(t...);}
#define dcl(...) ll __VA_ARGS__;get(__VA_ARGS__);


int main(){
    dcl(n,a,b);
    if(a>b)cout<<0<<endl;
    else if(n==1)cout<<(a==b?1:0)<<endl;
    else cout<<(b-a)*(n-2)+1<<endl;
	return 0;
}
