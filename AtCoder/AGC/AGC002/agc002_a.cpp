 
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
void bulk(){}template<class H,class...T>void bulk(H&h,T&...t){cin>>h;bulk(t...);}
#define get(...) int __VA_ARGS__; bulk(__VA_ARGS__);

int f(int x){
    if(x>0)return 1;
    if((-x)%2==0) return 1;
    return -1;
}

int main(){
	get(a,b);
	if(a==0 || b==0 ||(a<0&&0<b)){cout<<"Zero"<<endl;return 0;}
	if(a>0)cout<<"Positive"<<endl; 
	else if((-a+b)%2==1)cout<<"Positive"<<endl; 
	else cout<<"Negative"<<endl;
	return 0;
}
