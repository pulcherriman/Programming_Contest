 
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
void bulk(){}template<class H,class...T>void bulk(H&h,T&...t){cin>>h;bulk(t...);}
#define get(...) ll __VA_ARGS__; bulk(__VA_ARGS__);


int main(){
    vector<ll> a(3);
    bulk(a[0],a[1],a[2]);
    sort(all(a));
    if(a[0]%2==0||a[1]%2==0||a[2]%2==0)cout<<0<<endl;
    else cout<<a[0]*a[1]<<endl;
	return 0;
}
