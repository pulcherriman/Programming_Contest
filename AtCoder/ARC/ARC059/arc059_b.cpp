 
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
    string s;
    cin>>s;
    vvi p(26);
    rep(i,s.size()){
        int d=s[i]-'a';
        for(int j=0;j<p[d].size();j++){
            int l=i-p[d][j]+1;
            int c=p[d].size()-j+1;
            if(l<c*2){cout<<p[d][j]+1<<" "<<i+1<<endl;return 0;}
        }
        p[d].pb(i);
    }
    cout<<"-1 -1"<<endl;
	return 0;
}
