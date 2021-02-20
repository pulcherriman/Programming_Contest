 
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
	int n,y;
	cin>>n>>y;
	vi a(n),b(n);
	rep(i,n){
	    cin>>a[i]>>b[i];
	}
	
	int mx=*max_element(all(a));
	sort(rall(b));
	int ans=0;
	for(int i=0;i<b.size();i++){
	    if(b[i]<mx)break;
	    y-=b[i];
	    ans++;
	    if(y<=0){
	        cout<<ans<<endl;return 0;
	    }
	}
	ans+=(int)ceil((double)y/mx);
	        cout<<ans<<endl;return 0;
}
