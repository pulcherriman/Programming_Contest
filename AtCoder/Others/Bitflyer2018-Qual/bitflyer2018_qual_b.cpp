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
    int a,b,n;
    cin>>a>>b>>n;
    string s;
    cin>>s;
    for(auto c:s){
        if(c=='S'){
            if(a>0)a--;
        }else if(c=='C'){
            if(b>0)b--;
        }else{
            if(a>b or (a>0 and a==b))a--;
            else if(b>0) b--;
        }
    }
    cout<<a<<endl<<b<<endl;
	return 0;
}
