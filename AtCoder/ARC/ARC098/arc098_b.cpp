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
    int n; cin>>n;
    vi a(n+1),b(n+1,0),x(n+1,0); range(i,1,n+1)cin>>a[i];
    rep(i,n)b[i+1]=b[i]+a[i+1];
    rep(i,n)x[i+1]=x[i]^a[i+1];
    ll ans=0;
    rep(i,n){
        int l=i+1,r=n+1;
        while(abs(r-l)>1){
            int m=(r+l)/2;
            if(b[m]-b[i]==(x[m]^x[i])){
                l=m;
            }else{
                r=m;
            }
        }
        ans+=l-i;
    }
    cout<<ans<<endl;
	return 0;
}
