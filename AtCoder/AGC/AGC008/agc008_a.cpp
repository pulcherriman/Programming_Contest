 
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

int main(){
    int a,b;cin>>a>>b;
    if(abs(a)<abs(b)){
        cout<<abs(b)-abs(a)+(a<0?1:0)+(b<0?1:0)<<endl;
    }else if(abs(a)==abs(b)){
        cout<<1<<endl;
    }else{
        cout<<abs(a)-abs(b)+(a>0?1:0)+(b>0?1:0)<<endl;
    }
	return 0;
}
