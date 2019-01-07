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
	int h,w;
	cin>>h>>w;
	vs f(h);
	rep(i,h)cin>>f[i];
	vs d={
		"AC","GT","AT","CG","CT","AG"
	};
	int ans=INF;
	int index=0;
	int type=0;
	vi rev;
	rep(lp,6){
		vs s={d[lp],d[lp^1]};
		rep(isV,2){
			int sum=0;
			vi r;
			if(isV==0){
				rep(i,h){
					int cng=0,cngR=0;
					rep(isR,2){
						rep(j,w){
							if(isR){
								if(f[i][j]!=s[i%2][!(j%2)])cngR++;
							}else{
								if(f[i][j]!=s[i%2][(j%2)])cng++;
							}
						}
					}
					r.push_back(cngR<cng);
					sum+=min(cng,cngR);
				}
			}else{
				rep(j,w){
					int cng=0,cngR=0;
					rep(isR,2){
						rep(i,h){
							if(isR){
								if(f[i][j]!=s[j%2][!(i%2)])cngR++;
							}else{
								if(f[i][j]!=s[j%2][(i%2)])cng++;
							}
						}
					}
					r.push_back(cngR<cng);
					sum+=min(cng,cngR);
				}
			}
			if(ans>sum){
				ans=sum;
				index=lp;
				type=isV;
				rev=r;
			}
		}
	}
	vs op;

	vs s={d[index],d[index^1]};
	if(type==0){
		rep(i,h){
			op.push_back("");
			rep(j,w){
				if(rev[i]){
					op.back()+=s[i%2][!(j%2)];
				}else{
					op.back()+=s[i%2][(j%2)];
				}
			}
		}
	}else{
		rep(j,w){
			op.push_back("");
			rep(i,h){
				if(rev[j]){
					op.back()+=s[j%2][!(i%2)];
				}else{
					op.back()+=s[j%2][(i%2)];
				}
			}
		}
	}
	if(type==0){
		rep(i,h){
			rep(j,w)cout<<op[i][j];
			cout<<endl;
		}
	}else{
		rep(i,h){
			rep(j,w)cout<<op[j][i];
			cout<<endl;
		}
	}
	return 0;
}