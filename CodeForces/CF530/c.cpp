#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using vb=vector<bool>;
using vvb=vector<vb>;
using vd=vector<double>;
using vvd=vector<vd>;
using vi=vector<int>;
using vvi=vector<vi>;
using vl=vector<ll>;
using vvl=vector<vl>;
using pll=pair<ll,ll>;
using tll=tuple<ll,ll>;
using vs=vector<string>;
#define all(a) a.begin(),a.end()
#define rall(a) a.rbegin(),a.rend()
#define rep(i,n) range(i,0,n)
#define range(i,a,n) for(ll i=(a);i<(n);i++)
#define LINF ((ll)1ll<<60)
#define INF ((int)1<<30)
#define EPS (1e-9)
#define MOD (1000000007ll)
#define fcout(a) cout<<setprecision(a)<<fixed
#define fs first
#define sc second
#define PI 3.1415926535897932384

int dx[]={1,0,-1,0,1,-1,-1,1},dy[]={0,1,0,-1,1,1,-1,-1};
template<class S,class T>ostream&operator<<(ostream&os,pair<S,T>p){os<<"["<<p.first<<", "<<p.second<<"]";return os;};
template<class S>auto&operator<<(ostream&os,vector<S>t){bool a=1; for(auto s:t){os<<(a?"":" ")<<s;a=0;} return os;}
void OUT(bool b){cout<<(b?"YES":"NO")<<endl;}
void Out(bool b){cout<<(b?"Yes":"No")<<endl;}
void out(bool b){cout<<(b?"yes":"no")<<endl;}
template<class T>
void puta(T&&t){cout<<t<<endl;}
template<class H,class...T>
void puta(H&&h,T&&...t){cout<<h<<' ';puta(t...);}

int popcnt(int x){return __builtin_popcount(x);}
int popcnt(ll x){return __builtin_popcountll(x);}
int bsr(int x){return 31 - __builtin_clz(x);}
int bsr(ll x){return 63 - __builtin_clzll(x);}
int bsf(int x){return __builtin_ctz(x);}
int bsf(ll x){return __builtin_ctzll(x);}

/*他のライブラリを入れる場所*/

int main(){
	cin.tie(0);
	ios::sync_with_stdio(false);
	string s;
	int n;
	cin>>s>>n;
	int mn=0,mx=0;
	bool isRep=false;
	rep(i,s.size()){
		if(isalpha(s[i])){
			mn++; mx++;
		}else if(s[i]=='?'){
			mn--;
		}else{
			mn--;
			isRep=true;
		}
	}
	//puta(mn,mx);
	if(n<mn or (!isRep and n>mx)){
		cout<<"Impossible"<<endl;
		return 0;
	}
	int l=s.size();
	if(n<=mx){
		int need=n-mn;
		rep(i,s.size()){
			if(isalpha(s[i])){
				if(i+1!=l){
					if(isalpha(s[i+1])){
						cout<<s[i];
					}else if(need>0){
						cout<<s[i];
						need--;
					}
				}else{
					cout<<s[i];
				}
			}
		}
	}else{
		int need=n-mx;
		rep(i,s.size()){
			if(isalpha(s[i])){
				cout<<s[i];
			}
			if(s[i]=='*'){
				rep(j,need)cout<<s[i-1];
				need=0;
			}
		}
	}
	cout<<endl;
	return 0;
}