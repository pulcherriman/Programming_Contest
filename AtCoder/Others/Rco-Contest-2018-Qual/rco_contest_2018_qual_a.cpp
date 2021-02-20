
#include <bits/stdc++.h>
using namespace std;
using vi=vector<int>;
using vvi=vector<vi>;
using vs=vector<string>;
using msi=map<string,int>;
using mii=map<int,int>;
//using pii=pair<int,int>;
using vlai=valarray<int>;
using ll=long long;
using pii=pair<ll,ll>;
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
#define MOD (1e9+7)
void get(){}template<class H,class...T>void get(H&h,T&...t){cin>>h;get(t...);}
#define dcl(...) int __VA_ARGS__;get(__VA_ARGS__);
 
int main(){
    dcl(n,k,h,w,t);
    vvi f(n,vi(h*w,0));
    vvi exist(n,vi(h*w,true));
    vi pos(n);
    vector<pii> able(n,{0,0});
    vector<pii> result(n,{0,0});

    rep(i,n){
        result[i].fs=i;
        rep(y,h)rep(x,w){
            char c;cin>>c;
            if(c=='x') f[i][y*w+x]=-1;
            if(c=='#') {f[i][y*w+x]=1; exist[i][y*w+x]=false;}
            if(c=='@') pos[i]=y*w+x;
        }
        vi tmp=f[i];
        queue<int> q;
        q.push(pos[i]);
        able[i].fs=i;
        while(!q.empty()){
            int cur=q.front(); q.pop();
            for(auto v : {-1,1,-w,w}){
                if(tmp[cur+v]==0){
                    q.push(cur+v);
                    tmp[cur+v]=1;
                }
            }
            able[i].sc++;
        }
        f[i][pos[i]]=2;
    }
    sort(all(able),[](pii a, pii b){return a.sc>b.sc;});
    vvi use=f;
    vi upos=pos;
    vi route;
    
    vi isGo(n,1);
    vi vect={-1,1,-w,w};
    rep(turn,t){
        vi coin(4,0),trap(4,0);
        rep(vec,4){
            int v=vect[vec];
            rep(i,n){
                if(isGo[i]) if(exist[i][upos[i]+v]) coin[vec]++;
            }
        }
        int decide=0;
        range(i,1,4){
            if(coin[decide]<coin[i]){
                decide=i;
            }
        }
        rep(i,n){
            if(isGo[i])
            if(use[i][upos[i]+vect[decide]] != 1){
                upos[i]+=vect[decide];
                exist[i][upos[i]]=false;
                if(use[i][upos[i]]==0){
                    result[i].sc++;
                    use[i][upos[i]]=2;
                }
                if(use[i][upos[i]]==-1){
                    isGo[i]=0;
                }
            }
        }
        route.pb(decide);
    }
    sort(all(result),[](pii a, pii b){return a.sc>b.sc;});
    rep(i,k){
        cout<<result[i].fs;
        if(i+1==k)cout<<endl; else cout<<" ";
    }
    for(auto v:route)cout<<"LRUD"s[v];
    cout<<endl;
}