 
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
	int n,c,k;
	cin>>n>>c>>k;
	vi p(n);
	rep(i,n){
	    cin>>p[i];
	}
	sort(all(p));
	int ans=0;
	rep(i,n){
	    int lt=p[i]+k;
	    int l=c;
	    for(;p[i]<=lt && l>0;i++){
	        //cout<<i<<"("<<p[i]<<")"<<",";
	        l--;
	    }
	    //cout<<endl;
	    i--;
	    ans++;
	}
	cout<<ans<<endl;
	
	return 0;
}
