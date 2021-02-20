 
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
int main(){
	get(n,m);
    vvi p(n,vi(2));
    vvi q(m,vi(2));
    rep(i,n)cin>>p[i][0]>>p[i][1];
    rep(i,m)cin>>q[i][0]>>q[i][1];
    for(auto a:p){
        int dist=INF,id=0;
        rrep(i,m){
            int d=abs(a[0]-q[i][0])+abs(a[1]-q[i][1]);
            if(d<=dist){
                dist=d; id=i+1;
            }
        }
        cout<<id<<endl;
    }
	return 0;
}
