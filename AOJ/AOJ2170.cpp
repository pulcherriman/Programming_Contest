#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using vl =vector<ll>;
#define rep(i,n) range(i,0,n)
#define range(i,a,n) for(ll i=(a);i<(n);i++)
#define all(a) a.begin(),a.end()
struct UnionFind{
    vl par,rank;
    UnionFind(int x){par.resize(x); iota(all(par),0); rank.resize(x,0);}
    int find(int x){
        if(par[x] == x) return x;
        else return par[x]=find(par[x]);
    }
    void unite(int x, int y){ // xにyをつなぐ
        if(same(x,y))return;
        x=find(x); 
        par[y]=x;
    }
    bool same(int x, int y){
        return find(x)==find(y);
    }
};

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    ll n,q;
    while(cin>>n>>q, n){
        vl p(n,0);
        rep(i,n-1){cin>>p[i+1];p[i+1]--;}
        vector<char> type(q);
        vl query(q);

        vl marked(n,0);
        marked[0]=1;
        rep(i,q){
            char c; ll num;
            cin>>c>>num;
            type[i]=c;
            query[i]=num-1;
            if(c=='M'){
                marked[query[i]]++;
            }
        }
        
        UnionFind uf(n);
        rep(i,n)if(marked[i]==0){
            uf.unite(p[i], i);
        }

        ll ans=0;
        for(ll i=q-1; i>=0;i--){
            if(type[i]=='M'){
                marked[query[i]]--;
                if(marked[query[i]]==0){
                    uf.unite(p[query[i]], query[i]);
                }
            }else{
                ans += uf.find(query[i])+1;
            }
        }
        cout<<ans<<endl;
    }
}