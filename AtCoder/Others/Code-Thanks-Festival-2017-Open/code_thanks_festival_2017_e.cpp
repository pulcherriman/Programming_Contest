 
#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using vi=vector<int>;
using vvi=vector<vi>;
using pii=pair<int,int>;
#define rep(i,n) range(i,0,n)
#define range(i,a,n) for(int i=a;i<n;i++)
#define all(a) a.begin(),a.end()
#define INF ((int)1e9)
#define EPS (1e-9)
#define MOD (1000000007)
void put(string d){}template<class H,class...T>void put(string d,H&h,T&...t){cout<<h;if(sizeof...(t))cout<<d;put(d,t...);}
template<class T>void puti(T&a,string d=" "){bool f=1;for(auto&_:a)cout<<(exchange(f,0)?"":d)<<_;cout<<endl;}
template<class T>void putii(T&a,string d=" "){for(auto&_:a)puti(_,d);}
template<class S,class T>ostream& operator<<(ostream&os,pair<S,T>p){os<<"["<<p.first<<", "<<p.second<<"]";return os;};


int main(){
	cin.tie(0);
   	ios::sync_with_stdio(false);
	vi a={0,8,88,888,8888,88888};
	int n;
	cin>>n;
	vi ans(n);
	rep(t,ceil(n/5.0)){
		int cnt=0;
		vi query(n,0);
		rep(i,n){
			if(t*5<=i and i<(t+1)*5){
				query[i]=pow(10,i%5);
				cnt++;
			}
		}
		cout<<"? "; puti(query);
		int in; cin>>in;
		in-=a[cnt];
		rep(i,n){
			if(t*5<=i and i<(t+1)*5){
				ans[i]=in/(int)pow(10,i%5)%10;
				ans[i]%=2;
			}
		}
	}
	cout<<"! "; puti(ans);
	return 0;
}
