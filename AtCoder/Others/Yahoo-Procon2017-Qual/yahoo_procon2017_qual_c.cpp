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

int main(){
	cin.tie(0);
   	ios::sync_with_stdio(false);
	
	int n,k;
	cin>>n>>k;
	vi a(n,0);
	int tInd=0;
	rep(i,k){
	    int t;
	    cin>>t;
	    tInd=t-1;
	    a[t-1]=1;
	}
	vs s(n);
	rep(i,n){
	    cin>>s[i];
	}
	if(n==k){
	    cout<<""<<endl;
	    return 0;
	}
	string tgt=s[tInd];
	vi suf(n,0);
	rep(i,n){
	    rep(j,min(s[i].size(),tgt.size())){
	        if(s[i][j]==tgt[j])suf[i]++;
	        else break;
	    }
	}
	int omin=INF,omax=0,xmin=INF,xmax=0;
    rep(i,n){
        if(a[i]){
            omin=min(omin,suf[i]);
            omax=max(omax,suf[i]);
        }else{
            xmin=min(xmin,suf[i]);
            xmax=max(xmax,suf[i]);
        }
    }
    //cout<<pii(omin,omax)<<pii(xmin,xmax)<<endl;
    if(omin<=xmax)cout<<-1<<endl;   //ダメなうち最長の一致列が、合致する最短のものと同じか長い場合、どうとってもダメ
    else cout<<s[tInd].substr(0,xmax+1)<<endl;  //ダメなもののうち最長の一致列が、合致する最短のものより短い場合、そこで切ればよい
    
	return 0;
}
