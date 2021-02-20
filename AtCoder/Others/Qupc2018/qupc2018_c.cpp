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
template<class S>auto&operator<<(ostream&os,vector<S>t){bool a=1; for(auto s:t){os<<(a?"":"\n")<<s; a=0;} return os;}

using data=tuple<int,int,int>;
queue<data> q;

void IFS(vs f, vs&ff){
    vi v={1,0,-1,0,1};
    while(!q.empty()){
        int y,x,d;
        tie(y,x,d)=q.front(); q.pop();
        if(f[y][x]=='#') continue;
        ff[y][x]=f[y][x]='#';
        if(d==0)continue;
        
        rep(i,4){
            if(f[y+v[i]][x+v[i+1]]!='#'){
                q.emplace(y+v[i],x+v[i+1],d-1);
            }
        }
    }
}

int BFS(vs&ff, int dy, int dx){
    vi v={1,0,-1,0,1};
    q=queue<data>();
    q.emplace(dy,dx,0);
    while(!q.empty()){
        int y,x,d;
        tie(y,x,d)=q.front(); q.pop();
        if(ff[y][x]=='#') continue;
        if(ff[y][x]=='G'){
            return d;
        }
        ff[y][x]='#';
        rep(i,4){
            if(ff[y+v[i]][x+v[i+1]]!='#'){
                q.emplace(y+v[i],x+v[i+1],d+1);
            }
        }
    }
    return -1;
}


int main(){
	cin.tie(0);
   	ios::sync_with_stdio(false);
	
	int h,w,x;
	cin>>h>>w>>x;
	vs f(h),fc,ff;
	rep(i,h)cin>>f[i];
	ff=fc=f;
	rep(i,h)rep(j,w){
	    if(fc[i][j]=='@') q.emplace(i,j,x);
	}
	IFS(ff,ff);
	rep(i,h)rep(j,w){
	    if(fc[i][j]=='G') if(ff[i][j]!='G'){
	        cout<<-1<<endl;
	        return 0;
	    }
	}
	rep(i,h)rep(j,w){
	    if(fc[i][j]=='S'){
	        cout<<BFS(ff,i,j)<<endl;
	        return 0;
	    }
	}
	return 0;
}
