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
using tlll=tuple<ll,ll,ll>;
using vs=vector<string>;
#define all(a) a.begin(),a.end()
#define rall(a) a.rbegin(),a.rend()
#define rep(i,n) range(i,0,n)
#define rrep(i,n) for(ll i=(n)-1;i>=0;i--)
#define range(i,a,n) for(ll i=(a);i<(n);i++)
#define LINF ((ll)1ll<<60)
#define INF ((int)1<<30)
#define EPS (1e-9)
#define MOD (1000000007ll)
#define fcout(a) cout<<setprecision(a)<<fixed
#define fs first
#define sc second
#define PI (3.1415926535897932384)

int dx[]={1,0,-1,0,1,-1,-1,1},dy[]={0,1,0,-1,1,1,-1,-1};
template<class T>bool chmax(T&a,T b){if(a<b){a=b; return true;}return false;}
template<class T>bool chmin(T&a,T b){if(a>b){a=b; return true;}return false;}
template<class S>S sum(vector<S>&a){return accumulate(all(a),S());}
template<class S>S max(vector<S>&a){return *max_element(all(a));}
template<class S>S min(vector<S>&a){return *min_element(all(a));}
ll max(int a,ll b){return max((ll)a,b);} ll max(ll a,int b){return max(a,(ll)b);}

template<class T>void puta(T&&t){cout<<t<<"\n";}
template<class H,class...T>void puta(H&&h,T&&...t){cout<<h<<' ';puta(t...);}
template<class S,class T>void tf(bool b,S t,T f){if(b)puta(t);else puta(f);}
void YN(bool b){tf(b,"YES","NO");}
void Yn(bool b){tf(b,"Yes","No");}
void yn(bool b){tf(b,"yes","no");}
template<class S,class T>ostream&operator<<(ostream&os,pair<S,T>p){os<<"["<<p.first<<", "<<p.second<<"]";return os;};
template<class S>auto&operator<<(ostream&os,vector<S>t){bool a=1;for(auto s:t){os<<(a?"":" ")<<s;a=0;}return os;}
template<class S>auto&operator>>(istream&is,vector<S>&t){for(S&a:t)cin>>a;return is;}

/*他のライブラリを入れる場所*/
int popcnt(int x){return __builtin_popcount(x);}
int popcnt(ll x){return __builtin_popcountll(x);}
int bitdig(int x){return 32 - __builtin_clz(x);}
int bitdig(ll x){return 64 - __builtin_clzll(x);}
int bitffs(int x){return __builtin_ffs(x);}
int bitffs(ll x){return __builtin_ffsll(x);}

bool get(int n,ll a,ll b,bool rev=false){
	vector<set<ll>> num(n+1);
	rep(i,1<<n){
		num[popcnt(i)].insert(i);
	}
	vl a1,a2,a3;
	while(1){
		a1.push_back(a);
		num[popcnt(a)].erase(a);
		if(a==0)break;
		a&=(a-1);
	}
	while(1){
		a3.push_back(b);
		num[popcnt(b)].erase(b);
		if(popcnt(b)==n)break;
		rep(i,n){
			ll tmp=b|(1<<i);
			if(num[popcnt(tmp)].find(tmp)==num[popcnt(tmp)].end())continue;
			b=tmp;
			break;
		}
	}
	int p=1;
	ll v=-1;
	while(1){
		if(num[p].size()==0)break;
		if(v==-1)v=*num[p].begin();
		a2.push_back(v);
		num[p].erase(v);
		if(num[p-1].size()!=0){
			p--;
			rep(i,n){
				if(num[p].find(v&(~(1<<i)))!=num[p].end()){
					v&=(~(1<<i));
					break;
				}
			}
			if(popcnt(v)==p)continue;
			p++;
		}
		if(num[p+1].size()!=0){
			p++;
			rep(i,n){
				if(num[p].find(v|(1<<i))!=num[p].end()){
					v|=(1<<i);
					break;
				}
			}
			if(popcnt(v)==p)continue;
			p--;
		}
		break;
	}
	if(a1.size()+a2.size()+a3.size()!=(1<<n)){
		return false;
	}
	reverse(all(a3));
	vl ans=a1;
	for(auto&t:a2)ans.push_back(t);
	for(auto&t:a3)ans.push_back(t);
	if(rev)reverse(all(ans));
	puta("YES");
	puta(ans);
	return true;
}

int main(){
	cin.tie(0);
	ios::sync_with_stdio(false);
	ll n,a,b;
	cin>>n>>a>>b;
	if(get(n,a,b))return 0;
	if(get(n,b,a,true))return 0;
	puta("NO");
	return 0;
}