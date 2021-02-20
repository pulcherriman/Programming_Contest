#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using vi=vector<int>;
using vvi=vector<vi>;
using pii=pair<int,int>;
#define rep(i,n) for(int i=0;i<n;i++)
#define range(i,a,n) for(int i=a;i<n;i++)
#define all(a) a.begin(),a.end()
#define rall(a) a.rbegin(),a.rend()
#define INF 1e9
#define EPS 1e-9
#define MOD (1e9+7)
void put(string d){}template<class H,class...T>void put(string d,H&h,T&...t){cout<<h;if(sizeof...(t))cout<<d;put(d,t...);}
template<class T>void puti(T&a,string d=" "){bool f=1;for(auto&_:a)cout<<(exchange(f,0)?"":d)<<_;cout<<endl;}
template<class T>void putii(T&a,string d=" "){for(auto&_:a)puti(_,d);}

int main(){
    ll h,w,m,n;
    cin>>h>>w>>m>>n;
    vector<string> a(m);
    rep(i,m)cin>>a[i];
    vector<pair<pii,pii>> r;
    vector<int> x,y;
    rep(i,m){
        rep(j,n){
            if(a[i][j]=='#'){
                r.push_back({{i,j},{i+h-m,j+w-n}});
                y.push_back(i);
                y.push_back(i+h-m);
                
                y.push_back(i+1);
                y.push_back(i+h-m+1);
                if(i!=0)y.push_back(i-1);
                y.push_back(i+h-m-1);
                
                x.push_back(j);
                x.push_back(j+w-n);
                
                x.push_back(j+1);
                x.push_back(j+w-n+1);
                if(j!=0)x.push_back(j-1);
                x.push_back(j+w-n-1);
                
            }
        }
    }
    sort(all(y));
    sort(all(x));
    y.erase(unique(all(y)),y.end());
    x.erase(unique(all(x)),x.end());
    map<int,int> px,py;
    rep(i,y.size()) py[y[i]]=i;
    rep(i,x.size()) px[x[i]]=i;
    vvi f(y.size()+1, vi(x.size()+1,0));
    for(auto e:r){
        int sx,sy,tx,ty;
        sy=py[e.first.first];
        sx=px[e.first.second];
        ty=py[e.second.first]+1;
        tx=px[e.second.second]+1;
        f[sy][sx]++;
        f[ty][tx]++;
        f[ty][sx]--;
        f[sy][tx]--;
    }
    rep(i,y.size()+1)partial_sum(all(f[i]),f[i].begin());
    rep(i,y.size())rep(j,x.size()+1){
        f[i+1][j]+=f[i][j];
        f[i][j]=!!f[i][j];
    }
    ll ans=0;
    rep(i,y.size())rep(j,x.size()){
        if(f[i][j]==0)continue;
        //cout<<y[i]<<","<<x[j]<<"~"<<(i+1==y.size()?h:y[i+1])<<","<<(j+1==x.size()?w:x[j+1])<<endl;
        ll sx=x[j],sy=y[i];
        ll tx=(j+1==x.size()?w:x[j+1]),ty=(i+1==y.size()?h:y[i+1]);
        //cout<<ty-sy<<"-"<<tx-sx<<endl;
        ans+=(tx-sx)*(ty-sy);
    }
    cout<<ans<<endl;
    //putii(f);
	return 0;
}
