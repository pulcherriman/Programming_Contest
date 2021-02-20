#include <bits/stdc++.h>
#include <cxxabi.h>
using namespace std;
using ll=long long;
using vi=vector<int>;
using vvi=vector<vi>;
using pii=pair<int,int>;
#define rep(i,n) range(i,0,n)
#define range(i,a,n) for(int i=a;i<n;i++)
#define all(a) a.begin(),a.end()
#define LINF    ((ll)1ll<60)
#define INF     ((int)1<<30)
#define EPS     (1e-9)
#define MOD     (1000000007)
template<class S,class T>ostream& operator<<(ostream&os,pair<S,T>p){os<<"["<<p.first<<", "<<p.second<<"]";return os;};
template<class S>auto&operator<<(ostream&os,vector<S>t){bool b=1;for(auto s:t)os<<(exchange(b,0)||strlen(abi::__cxa_demangle(typeid(S).name(),0,0,0))>20?"":" ")<<s;return os<<endl;}

ll solve(string &s){
	ll ans=0;
	vi par(s.size(),-1);
	vi chain(s.size(),0);
	
	bool f=false;
	rep(i,s.size()){
		if(f){
			f=false;
			if(s[i]==')'){
				int bt=i-1;
				while(bt!=-1 and par[bt]!=-1){
					bt=par[bt]-1;
				}
				if(bt!=-1 and s[bt]=='('){
					par[i]=bt;
					par[bt]=i;
					if(bt>0 and par[bt-1]!=-1){
						chain[i]=chain[bt-1]+1;
						chain[bt-1]=0;
					}
					ans++;
					f=true;
				}
			}
		}
		if(!f and i+1!=s.size() and s[i]=='(' and s[i+1]==')'){
			par[i]=i+1;
			par[i+1]=i;
			chain[i+1]=0;
			if(i>0 and par[i-1]!=-1){
				chain[i+1]=chain[i-1]+1;
				chain[i-1]=0;
			}
			ans++;
			f=true;
			i++;
		}
	}
	for(auto i:chain){
		if(i) ans+=(ll)i*(i+1)/2;
	}
	return ans;
}

int main(){
	cin.tie(0);
   	ios::sync_with_stdio(false);
	
	string s;
	cin>>s;
	cout<<solve(s)<<endl;
	return 0;
}
 
