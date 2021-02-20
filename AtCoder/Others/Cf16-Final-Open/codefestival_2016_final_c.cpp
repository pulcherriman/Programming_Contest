 
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
 
struct UnionFind{
    int n;
    vi p,r;
    UnionFind(int N):n(N){
        p.resize(n);
    	iota(all(p),0);
        r.resize(n);
        fill(all(r),0);
    }
    void unite(int a, int b){
        int c=root(a),d=root(b); 
        if(c!=d) {
            if(r[c]<r[d]){
                p[c]=d;
            }else{
                p[d]=c;
                if(r[c]==r[d])r[c]++;
            }
        }
    }
    int root(int a){return p[a]=(p[a]==a?a:root(p[a]));}
    bool same(int a, int b){return root(a)==root(b);}
};

int main(){
	int n,m;
	cin>>n>>m;
	vector<set<int>> s(m+1);
	rep(i,n){
	    int p;cin>>p;
	    rep(j,p){
	        int q;cin>>q;
	        s[q].insert(i+1);
	    }
	}

	UnionFind u(n+1);
	rep(i,m+1){
	    auto t=s[i];
	    if(t.size()<2)continue;
	    auto eitr=t.end();
	    eitr--;
	    for(auto itr=t.begin();itr!=(--t.end());){
	        u.unite(*++itr,*itr);
	    }
	    //range(j,1,n+1){cout<<u.p[j];}cout<<endl;
	}
	bool ans=true;
	range(i,2,n+1) {
	    ans&=u.same(1,i);
    }
    cout<<(ans?"YES":"NO")<<endl;
	return 0;
}
