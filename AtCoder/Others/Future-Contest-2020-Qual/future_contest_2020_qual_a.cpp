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
 
int dx[]={0,0,-1,1},dy[]={-1,1,0,0};
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
 
#define _cTime (chrono::system_clock::now())
#define progress (chrono::duration_cast<chrono::milliseconds>(_cTime-_sTime).count())
#define reset _sTime=_cTime
auto reset;


mt19937 _mt(chrono::steady_clock::now().time_since_epoch().count());
ll getRand(ll l,ll r){return uniform_int_distribution<ll>(l,r-1)(_mt);}

ll n,m,b;
ll gy,gx;
struct robot{
    ll y,x,c;
    robot(ll Y,ll X,char C){y=Y,x=X;c="UDLR"s.find(C);}
};
vector<robot> r;

pair<ll,vvl> walk(vvl f){
    ll ret=0;

    vector<vvl> v(n,vvl(n,vl(4,0)));
    queue<tlll> q;
    rep(i,m){
        q.emplace(r[i].y, r[i].x, r[i].c);
    }
    while(!q.empty()){
        ll y,x,c;
        tie(y,x,c) = q.front(); q.pop();
        if(y>=n)y=0;
        if(x>=n)x=0;
        if(y<0)y=n-1;
        if(x<0)x=n-1;
        if(v[y][x][c])continue;
        if(f[y][x]==-10)continue;
        v[y][x][c]=1;
        if(y==gy and x==gx){continue;}
        if(f[y][x]==-1){
            q.emplace(y+dy[c], x+dx[c], c);
        }else{
            ll nc=f[y][x];
            q.emplace(y+dy[nc], x+dx[nc], nc);
        }
    }
    vvl r(n,vl(n,0));
    rep(i,n)rep(j,n)ret+=r[i][j]=max(v[i][j]);
    return make_pair(ret,r);
}



pair<ll,vvl> bfs(vvl f){
    queue<tlll> q;
    rep(i,4){
        q.emplace(gy+dy[i], gx+dx[i], i);
    }
    vector<vvl> v(n,vvl(n,vl(4,0)));
    rep(i,4)v[gy][gx][i]=1;
    while(!q.empty()){
        ll y,x,c;
        tie(y,x,c) = q.front(); q.pop();
        if(y>=n)y=0;
        if(x>=n)x=0;
        if(y<0)y=n-1;
        if(x<0)x=n-1;

        if(v[y][x][c])continue;
        if(f[y][x]==-10){rep(i,4)v[y][x][i]=-1; continue;}
        v[y][x][c]=1;
        if(y==gy and x==gx)continue;

        if(f[y][x]==-1){
            q.emplace(y+dy[c], x+dx[c], c);
        }else{
            ll nc=f[y][x]^1;
            if(c==nc){
                rep(i,4){
                    q.emplace(y+dy[i], x+dx[i], i);
                }
            }
        }
    }
    ll a=0,b=0,c=0;
    rep(i,m){
        ll st = f[r[i].y][r[i].x];
        if(st==-1){
            if(v[r[i].y][r[i].x][r[i].c^1])a+=1000;
        }else{
            if(v[r[i].y][r[i].x][st^1])a+=1000;
        }
    }
    rep(i,n)rep(j,n){
        if(f[i][j]>=0)b+=10;
    }
    tie(c,f) = walk(f);
    return make_pair(a-b+c,f);
}


pair<ll,vvl> bfs_init(vvl f){
   stack<tlll> q;
    rep(i,4){
        q.emplace(gy+dy[i], gx+dx[i], i);
    }
    vector<vvl> v(n,vvl(n,vl(4,0)));
    rep(i,4)v[gy][gx][i]=1;
    while(!q.empty()){
        ll y,x,c;
        tie(y,x,c) = q.top(); q.pop();
        if(y>=n)y=0;
        if(x>=n)x=0;
        if(y<0)y=n-1;
        if(x<0)x=n-1;

        if(v[y][x][c])continue;
        if(f[y][x]==-10){rep(i,4)v[y][x][i]=1; continue;}
        v[y][x][c]=1;
        if(y==gy and x==gx)continue;

        if(f[y][x]==-1){
            f[y][x]=c^1;
            rep(i,4){
                q.emplace(y+dy[i], x+dx[i], i);
            }
        }
    }

    return make_pair(0,f);
}

int main(){
	cin.tie(0);
	ios::sync_with_stdio(false);
	cin>>n>>m>>b;
	cin>>gy>>gx;
	rep(i,m){
	    ll y,x; char c;
	    cin>>y>>x>>c;
	    r.emplace_back(y,x,c);
	}

	vvl f(n,vl(n,-1));
	rep(i,b){
	    ll y,x;cin>>y>>x;
	    f[y][x]=-10;
	}
	
	ll best; vvl v;
	tie(best,f) = bfs_init(f);
    tie(best,v) = bfs(f);
	
    ll suc=0,cha=0,tmp=0,tsuc=0;
    ll tq=0;
    bool isnone=false;

	{
    
        ll lim=2990;
        vl able(n*n,0);
        iota(all(able),0);
    
    	while(progress<lim){
    	    auto nf=f;
    	    ll y,x;
    	    while(progress<lim){
    	        if(tq>=0){
    	            if(tq==0)isnone=true;
    	            y=tq/n, x=tq%n;
    	            tq++;
    	            if(tq>=n*n){
                        tie(best,v) = bfs(f);
    	                if(isnone){
    	                    tq=-1;
	                    }else{
	                       // puta("retry", progress);
	                        tq=0;
	                    }
    	                continue;
    	            }
    	            if(f[y][x]<0 or (y==gy and x==gx))continue;
    	            nf[y][x]=-1;
    	            if(!v[y][x]){f=nf;continue;}
    	            
            	    ll score; vvl nv; tie(score,nv) = bfs(nf);
    	            if(best<score){best=score; f=nf; v=nv; isnone=false;if(tq==-1){suc++;if(nf[y][x]==-1)tsuc++;}}

    	            break;
    	        }else{
    	            if(able.size()==0){
    	                able=vl(n*n,0);
    	                iota(all(able),0);
    	                tq=0;
    	                continue;
    	            }
    	            ll p=getRand(0,able.size());
        	        y=able[p]/n;
        	        x=able[p]%n;
        	        if(f[y][x]<0 or (f[y][x]==-1 and !v[y][x]) or (y==gy and x==gx)){
        	            able.erase(able.begin() + p);
        	            continue;
        	        }
        	        else {
        	            able.erase(able.begin() + p);
        	            rep(i,4){
            	            nf[y][x]=i;
            	            if(nf[y][x]==f[y][x] or nf[y][x]<0)nf[y][x]=-1;
            	            if(nf[y][x]==f[y][x])continue;
            	            if(tq==-1){if(nf[y][x]==-1)tmp++; cha++;}
                    	    ll score; vvl nv; tie(score,nv) = bfs(nf);
            	            if(best<score){best=score; f=nf; v=nv; isnone=false;if(tq==-1){suc++;if(nf[y][x]==-1)tsuc++;}}
        	            }

        	            break;
        	        }
    	        }
    	    }
    	}
	}
	
    // puta(suc,"(",tsuc,")","/",cha,"(",tmp,")"," : ",best);
    // rep(i,n){
    //     rep(j,n)if(f[i][j]==-10)cout<<"■"<<",";
    //     else cout<<(v[i][j]?"#":" ")<<",";
    //     puta("");
    // }

	ll ans=0;
	rep(i,n)rep(j,n){
	    if(f[i][j]>=0)ans++;
	}
	puta(ans);
	rep(i,n)rep(j,n){
	    if(f[i][j]>=0)puta(i,j,"UDLR"[f[i][j]]);
	}
	return 0;
}
