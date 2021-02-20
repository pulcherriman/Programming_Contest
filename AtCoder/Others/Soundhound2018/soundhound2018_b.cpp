 
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

int l,r;

int cl(int n){ if(l>n)return l; if(n>r)return r; return n;}

int main(){
    int n;
    bulk(n,l,r);
    
    rep(i,n){
        get(p);
        cout<<cl(p);
        if(i+1==n)cout<<endl; else cout<<" ";
    }
	return 0;
}
