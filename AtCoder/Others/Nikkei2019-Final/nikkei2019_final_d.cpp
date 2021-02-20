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
struct query{
	int type;//0=empty, 1=add-sum ,2=set-min
	ll value;
	query(int a=0,ll b=0):type(a),value(b) {}
};

struct segtree{
	int n;
	vector<query> s;
	vl t;// sum-add
	vl u;// min-set
	segtree(int N){
		n=1; while(n<=N)n*=2;
		s.assign(n*2,query());
		t.assign(n*2,0);
		u.assign(n*2,0);
	}
 
	void func(int k,int l,int r,query q){
		if(q.type==1){
			if(s[k].type==0)s[k]=q;
			else s[k].value+=q.value;
			t[k]+=q.value*(r-l);
			u[k]+=q.value;
		}
		if(q.type==2){
			s[k]=q;
			t[k]=q.value*(r-l);
			u[k]=q.value;
		}
	}
 
	void compute(int k,int l,int r){
		query q=s[k];
		s[k]=query();
		if(q.type==0||r-l==1)return;
		int m=(l+r)/2;
		func(k*2+1,l,m,q);
		func(k*2+2,m,r,q);
	}
 
 	void Update(int a,int b,query x){Update(a,b,x,0,0,n);}
	void Update(int a,int b,query x,int k,int l,int r){
		if(b<=l || r<=a)return;
		compute(k,l,r);
		if(a<=l && r<=b){
			func(k,l,r,x);
		}else{
			int m=(l+r)/2;
			Update(a,b,x,k*2+1,l,m);
			Update(a,b,x,k*2+2,m,r);
			t[k]=t[k*2+1]+t[k*2+2];
			u[k]=min(u[k*2+1],u[k*2+2]);
		}
	}

	ll Dfs(int type,int a,int b){return Dfs(type,a,b,0,0,n);}
	ll Dfs(int type,int a,int b,int k,int l,int r){
		if(b<=l || r<=a){
			if(type==1)return 0; //add
			if(type==2)return INF; // min
		}
		compute(k,l,r);
		if(a<=l && r<=b){
			if(type==1)return t[k];
			if(type==2)return u[k];
		}else{
			int m=(l+r)/2;
			ll lv=Dfs(type,a,b,k*2+1,l,m);
			ll rv=Dfs(type,a,b,k*2+2,m,r);
			if(type==1)return lv+rv; // add
			if(type==2)return min(lv,rv); // min
		}
	}
 
	ll Getsum(int a,int b){
		return Dfs(1,a,b);
	}
 
	ll Getmin(int a,int b){
		return Dfs(2,a,b);
	}
 
};

int main(){
	cin.tie(0);
	ios::sync_with_stdio(false);
	ll n,m;
	cin>>n>>m;
	segtree st(n);
	rep(i,m){
		ll t,l,r; cin>>t>>l>>r;
		st.Update(l-1,r,query(2,t));
	}
	puta(st.Getsum(0,n));
	return 0;
}