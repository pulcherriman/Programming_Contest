 
#include <bits/stdc++.h>
using namespace std;
using vi=vector<int>;
using vvi=vector<vi>;
using vs=vector<string>;
using msi=map<string,int>;
using mii=map<int,int>;
using pii=pair<int,int>;
using vlai=valarray<int>;
using ll=long long;
#define rep(i,n) for(int i=0;i<n;i++)
#define range(i,s,n) for(int i=s;i<n;i++)
#define all(a) a.begin(),a.end()
#define rall(a) a.rbegin(),a.rend()
#define fs first
#define sc second
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define INF 1e9
#define EPS 1e-9

int main(){
	string s;
	cin>>s;
	stack<string> t;
	bool ok=true;
	int d=0, md=-1;
	for(int i=0;i<s.size();i++){
	    string c=""s+s[i];
        if(c=="2"){
	        if(t.empty()) {t.push(c); d++;}
	        else if(t.top().back()=='5') t.top()+=c;
	        else {t.push(c); d++;}
	    }else{
	        if(t.empty()) {ok=false; break;}
	        else if(t.top().back()=='2') t.top()+=c;
	        else {t.pop(); i--; d--;}
	    }
	    md=max(md,d);
	}
	if(ok && t.size()==1 && t.top().back()=='5'){
	    cout<<md<<endl;
	}else cout<<-1<<endl;
	return 0;
}
