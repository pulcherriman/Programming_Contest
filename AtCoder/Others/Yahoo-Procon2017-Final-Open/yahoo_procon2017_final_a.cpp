#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using vi=vector<int>;
using vvi=vector<vi>;
using vd=vector<double>;
using vvd=vector<vd>;
using vl=vector<ll>;
using vvl=vector<vl>;
using pii=pair<int,int>;
using vs=vector<string>;
#define rep(i,n) range(i,0,n)
#define range(i,a,n) for(int i=a;i<n;i++)
#define all(a) a.begin(),a.end()
#define LINF    	((ll)1ll<<60)
#define INF     	((int)1<<30)
#define EPS     	(1e-9)
#define MOD     	(1000000007)
#define fcout(a)	cout<<setprecision(a)<<fixed
#define fs 			first
#define sc			second
#define PI			3.141592653589793

template<class S,class T>ostream& operator<<(ostream&os,pair<S,T>p){os<<"["<<p.first<<", "<<p.second<<"]";return os;};
template<class S>auto&operator<<(ostream&os,vector<S>t){bool a=1; for(auto s:t){os<<(a?"":" ")<<s; a=0;} return os;}
/*
 * 自明
 */

constexpr ll gcd(ll a,ll b){return b?gcd(b,a%b):a;}
constexpr ll lcm(ll a,ll b){return a*b/gcd(a,b);}
double dh=360.0/(12*60*60);
double dm=360.0/(60*60);
double ds=360.0/(60);

bool isHM(int s){
    double H=s%(12*3600)*dh;
    double M=s%3600*dm;
    // if(s%3600==3599){
    //     cout<<H<<","<<M<<endl;
    //     cout<<H+dh<<","<<M+dm<<endl;
    // }
    if(M==H) return true;
    if(M<H and M+dm>H+dh+EPS) return true;
    if(M>H and M+dm+EPS<H+dh) return true;
    return false;
}

bool isMS(int s){
    double M=s%3600*dm;
    double S=s%60*ds;
    if(M==S) return true;
    if(M<S and M+dm>S+ds+EPS) return true;
    if(M>S and M+dm+EPS<S+ds) return true;
    return false;
}

int main(){
	cin.tie(0);
   	ios::sync_with_stdio(false);
	
	string s;
	cin>>s;
	int n=s.size();
	
	//sのi文字目までを使って、"yahoo".substr(0,j+1)をつくる
	vvi dp(n+1,vi(5,INF));
	dp[0][0]=0;
	dp[0][1]=1;
	dp[0][2]=2;
	dp[0][3]=3;
	dp[0][4]=4;
	rep(i,n){
	    rep(_,2)
	    rep(j,5){
	        if(s[i]=="oyaho"s[j%5]) dp[i+1][j]=min(dp[i+1][j],dp[i][(j+4)%5]);//正しい
	        dp[i+1][j]=min(dp[i+1][j],dp[i][(j+4)%5]+1);//置換
	        dp[i+1][j]=min(dp[i+1][j],dp[i][j]+1);//削除
	        dp[i][j]=min(dp[i][j],dp[i][(j+4)%5]+1);//挿入
	    }
	}
	cout<<dp[n][0]<<endl;
	return 0;
}
