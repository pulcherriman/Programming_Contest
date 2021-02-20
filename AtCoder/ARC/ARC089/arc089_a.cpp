 
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
	int n;cin>>n;
	int tm=0,cx=0,cy=0;
	rep(i,n){
	    int t,x,y;
	    cin>>t>>x>>y;
	    int dt=t-tm,dx=x-cx,dy=y-cy;
	    //cout<<dt<<","<<dx<<","<<dy<<endl;
	    int len=abs(dx)+abs(dy);
	    if(len>dt || len%2!=dt%2){
	        cout<<"No"<<endl;
	        return 0;
	    }
	    tm=t,cx=x,cy=y;
	}
	cout<<"Yes"<<endl;
	return 0;
}
