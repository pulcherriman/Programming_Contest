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
enum SegType{SEG_MIN,SEG_MAX,SEG_SUM};
 
struct SegmentTree{
    using Func=function<ll(ll,ll)>;
    using Attr=tuple<ll,Func,Func>;
    int n;
    vl val;
    ll e;
    Func f,g;
    const vector<Attr> tmpAttr{
        Attr(LINF,[](ll a,ll b){return min(a,b);},[](ll a,ll b){return b;}),
        Attr(-LINF,[](ll a,ll b){return max(a,b);},[](ll a,ll b){return b;}),
        Attr(0,[](ll a,ll b){return a+b;},[](ll a,ll b){return a+b;}),
    };
    SegmentTree(int N){
        n=1; while(n<=N)n*=2;
    }
    SegmentTree(int N,int t):SegmentTree(N){tie(e,f,g)=tmpAttr[t];val.assign(n*2,e);}
    SegmentTree(int N,ll E,Func F,Func G):SegmentTree(N){tie(e,f,g)=Attr(E,F,G);val.assign(n*2,e);}
    void update(ll k,ll a){
        k+=n;
        val[k]=g(val[k],a);
        while(k){
            k/=2;
            val[k]=f(val[k*2],val[k*2+1]);
        }
    }
    ll query(int a, int b){return query(a,b,1,0,n);}
    ll query(int a, int b, int k, int l, int r){
        if(r<=a or l>=b) return e;
        if(a<=l and r<=b) return val[k];
        int m=(l+r)/2;
        return f(query(a,b,k*2,l,m),query(a,b,k*2+1,m,r));
    }   
};
int main(){
	cin.tie(0);
	ios::sync_with_stdio(false);
	ll n,m;
	cin>>n>>m;

	SegmentTree st(n,SEG_SUM);
	rep(i,m){
		ll t,a,b;
		cin>>t>>a>>b;
		if(t==0) st.update(a,b);
		else puta(st.query(a,b+1));
	}

	return 0;
}
