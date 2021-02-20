#include <bits/stdc++.h>
#define rep(i,n) range(i,0,n)
#define range(i,a,n) for(int i=a;i<(n);i++)
using namespace std;

int main(){
    long long h,w,n; cin>>h>>w>>n;
    set<tuple<int,int,int,int>> edge;
    rep(_,n){
        int p,q,v[]={-1,0,1,0,-1}; cin>>p>>q;
        rep(i,4){
            int np=p+v[i], nq=q+v[i+1];
            if(np>0 and nq>0 and np<=h and nq<=w) {
                edge.emplace(p,q,np,nq);
                edge.emplace(np,nq,p,q);
            }
        }
    }
    cout<<(h-1)*w+(w-1)*h-edge.size()/2<<endl;;
	return 0;
}
