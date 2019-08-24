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
int sgn(const double&r){return (r>EPS)-(r<-EPS);} // a>0  : sgn(a)>0
int sgn(const double&a,const double&b){return sgn(a-b);} // b<=c : sgn(b,c)<=0

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


int main(){
	cin.tie(0);
	ios::sync_with_stdio(false);
	ll n;
	cin>>n;
	vvi isUsed(n,vi(n,-1));
	vl cnt(n,n-1);
	int st=0,level=1;
	while(1){
		if(st==n)break;
		if(cnt[st]==0){
			st++; continue;
		}
		// puta("CNT",cnt);
		vi costs(n,-1);
		stack<tlll> q;
		range(i,st,n){
			q.emplace(-1,i,costs[i]==-1?0:costs[i]);
			while(!q.empty()){
				ll prev,cur,cost;
				tie(prev, cur,cost)=q.top(); q.pop();
				if(prev!=-1 and isUsed[prev][cur]!=-1)continue;
				if(costs[cur]!=-1 and costs[cur]%2 != cost%2)continue;
				// puta("use",level,prev,cur);
				if(prev!=-1) isUsed[prev][cur]=isUsed[cur][prev]=level;
				if(prev!=-1) {cnt[prev]--; cnt[cur]--;}
				if(costs[cur]!=-1) continue;
				costs[cur]=cost;
				rep(i,n){
					// puta("OK", cur,i,isUsed[cur][i],costs[i],costs[cur]);
					if(cur!=i and isUsed[cur][i]==-1 and (costs[i]!=-1 or costs[i]%2 != costs[cur]%2)){
						q.emplace(cur,i,cost+1);
					}
				}
			}
		}
		level++;
	}
	rep(i,n){
		range(j,i+1,n)cout<<isUsed[i][j]<<(j+1!=n?" ":"");
		cout<<endl;
	}

	return 0;
}