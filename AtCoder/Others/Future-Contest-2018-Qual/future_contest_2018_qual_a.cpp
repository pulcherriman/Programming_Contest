#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using vi=vector<int>;
using vvi=vector<vi>;
using vs=vector<string>;
using msi=map<string,int>;
using mii=map<int,int>;
using psi=pair<string,int>;
using pii=pair<int,int>;
using vlai=valarray<int>;
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
template<class T>void geti(T&a){for(auto&_:a)cin>>_;}
template<class T>void getii(T&a){for(auto&_:a)geti(_);}
void put(string d){cout<<endl;}template<class H,class...T>void put(string d,H&h,T&...t){cout<<h;if(sizeof...(t))cout<<d;put(d,t...);}
template<class T>void puti(T&a,string d=" "){bool f=1;for(auto&_:a)cout<<(exchange(f,0)?"":d)<<_;cout<<endl;}
template<class T>void putii(T&a,string d=" "){for(auto&_:a)puti(_,d);}
#define dcl(...) int __VA_ARGS__;get(__VA_ARGS__)
#define dclt(t,...) t __VA_ARGS__;get(__VA_ARGS__)

int n=100;


vi decide2(vvi f){
    int x=-1,y=-1,h=-1;
    rep(i,n)rep(j,n){
        if(f[i][j]>h){
            x=j;
            y=i;
            h=f[i][j];
        }
    }
    if(h<=0) return {-1,-1,-1};
    h=min(h,n);
    for(int hh=h;hh>0;hh--){
        bool ok=true;
        rep(i,n){
            rep(j,n){
                if(abs(y-i)+abs(x-j)<hh){
                    if(f[i][j]-(hh-(abs(y-i)+abs(x-j)))<0){
                        ok=false;
                        i=j=n;
                        break;
                    }
                }
            }
        }
        if(ok){
            h=hh;
            vi ret={x,y,h};
            return ret;
        }
    }
    return {-1,-1,-1};
}



vi decide(vvi f){
    int x=-1,y=-1,h=-1;
    vi hor(n,0),ver(n,0);
    
    rep(i,n)rep(j,n){
        hor[i]+=sqrt(f[i][j]);
        ver[j]+=sqrt(f[i][j]);
    }
    rep(i,n){
        if(h<hor[i]){
            h=hor[i];
            y=i;
        }
    }
    h=-1;
    rep(i,n){
        if(h<ver[i]){
            h=ver[i];
            x=i;
        }
    }
    h=f[y][x];
    if(h<=0) return {-1,-1,-1};
    h=min(h,n);
    for(int hh=h;hh>0;hh--){
        bool ok=true;
        rep(i,n){
            rep(j,n){
                if(abs(y-i)+abs(x-j)<hh){
                    if(f[i][j]-(hh-(abs(y-i)+abs(x-j)))<0){
                        ok=false;
                        i=j=n;
                        break;
                    }
                }
            }
        }
        if(ok){
            h=hh;
            vi ret={x,y,h};
            return ret;
        }
    }
    return {-1,-1,-1};
}

void paint(vvi &f, vi stat){
    int x=stat[0];
    int y=stat[1];
    int h=stat[2];
    rep(i,n){
        rep(j,n){
            if(abs(y-i)+abs(x-j)<h){
                f[i][j]-=h-(abs(y-i)+abs(x-j));
            }
        }
    }
}

int main(){
    vvi field(n,vi(n));
    getii(field);
    int query=0;
    vvi answer;
    int depth=0;
    int step=0;
    while(1){
        vi dec1,dec2;
        dec1=decide(field);
        dec2=decide2(field);
		if(max(dec1[2],dec2[2])<=0) break;
		query++;
        
		if(dec1[2]>dec2[2]){
			paint(field,dec1);
			answer.pb(dec1);
		}else{
			paint(field,dec2);
			answer.pb(dec2);
		}
        if(query==1000-depth)break;
    }
    put(" ",query);
    putii(answer);
    
}