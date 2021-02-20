 
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
#define get(...) int __VA_ARGS__; bulk(__VA_ARGS__);


int main(){
    string s;cin>>s;
    int f=0;
    if(s.find('N')!=string::npos) f^=1;
    if(s.find('S')!=string::npos) f^=1;
    if(s.find('E')!=string::npos) f^=2;
    if(s.find('W')!=string::npos) f^=2;
    if(f) cout<<"No"<<endl;
	else cout<<"Yes"<<endl;
	return 0;
}
