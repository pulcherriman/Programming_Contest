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
   	int n,m,k;
   	cin>>n>>m>>k;
   	vi p(n+1),d(n+1,INF);
   	d[0]=-1;
   	vvi edge(n+1);
   	int r=0;
   	rep(i,n){
   	    cin>>p[i+1];
   	    if(p[i+1]==0)r=i+1;
   	    edge[p[i+1]].push_back(i+1);
   	}
   	queue<int> q;
   	q.push(r);
   	while(!q.empty()){
   	    int c=q.front(); q.pop();
   	    d[c]=d[p[c]]+1;
   	    for(auto&nc:edge[c])q.push(nc);
   	}

    //K回操作できない
   	int maxMove=accumulate(all(d),1);
   	if(maxMove<k-m){
   	    cout<<-1<<endl;
   	    return 0;
   	}
   	//K回以内にM枚置けない
   	auto cd=d;
   	sort(all(cd));
   	int minMove=0;
   	rep(i,m){
   	    minMove+=cd[i+1];
   	}
   	if(minMove+m>k){
   	    cout<<-1<<endl;
   	    return 0;
   	}
   	int nokori=k;
   	vi ans;
   	rep(coin,m){//mまいのコインについて
   	    if(coin!=ans.size()){
   	        cout<<-1<<endl;
   	        return 0;
   	    }
   	    if(coin==m-1){//最後は使い切らなければいけない
            nokori-=1;//根に置く
            range(i,1,n+1){
                if(d[i]==nokori){
                    ans.push_back(i);
                    break;
                }
            }
            if(ans.size()!=m){
                while(1){ans.back()++;}
            }
            break;
   	    }
   	    range(i,1,n+1){ //辞書順最小になるように貪欲に置いていく
   	        if(d[i]==-1)continue;//すでにその場所に置けない場合パス
   	        int newNokori=nokori-1-d[i];
   	        if(newNokori<0)continue; //根に置いたコインをK回以内にもっていけない
   	        //置けるとき、残り操作回数以内に理論上置ければ置く
   	        cd=d;
   	        q.push(i);
   	        while(!q.empty()){
           	    int c=q.front(); q.pop();
           	    cd[c]=-1;
           	    for(auto&nc:edge[c])q.push(nc);
           	}
           	auto ccd=cd;
           	sort(all(cd));
           	int cntX=count(all(cd),-1);
           	minMove=0;
           	maxMove=0;
           	rep(j,m-coin-1){//これを置いた後、残りm-coin-1枚を置くのに必要な最小のmove
           	    if(j+cntX>=cd.size()){minMove=INF; break;}
           	    minMove+=cd[j+cntX];
           	    if(cd[cd.size()-1-j]==-1){maxMove=-INF; break;}
           	    maxMove+=cd[cd.size()-1-j];
           	}
           	if(minMove+(m-coin-1)>newNokori)continue;//残り回数でコインを置けない
           	if(maxMove+(m-coin-1)<newNokori)continue;//残り回数でコインをどうおいても回数が余る
           	//置けるので置く
           	d=ccd;
           	nokori=newNokori;
           	ans.push_back(i);
           	break;
   	    }
   	    // cout<<minMove+(m-coin-1)<<endl;
   	    // cout<<nokori<<endl;
   	    // cout<<d<<endl;
   	    //cout<<ans<<endl;
   	}
   	cout<<ans<<endl;
}
