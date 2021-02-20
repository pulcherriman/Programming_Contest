#include <bits/stdc++.h>
using namespace std;
#define rep(i,n) range(i,0,n)
#define range(i,a,n) for(int i=a;i<n;i++)
#define all(a) a.begin(),a.end()
#define INF     	((int)1<<30)

template<class S,class T>ostream& operator<<(ostream&os,pair<S,T>p){os<<"["<<p.first<<", "<<p.second<<"]";return os;};
template<class S>auto&operator<<(ostream&os,vector<S>t){bool a=1; for(auto s:t){os<<(a?"":" ")<<s; a=0;} return os;}

using vs=vector<string>;
using vi=vector<int>;
using vvi=vector<vi>;
using pii=pair<int,int>;

random_device rndDev;
mt19937 mt(rndDev());
#define rnd(a,b) (mt()%(b-a)+a)
#define cTime (chrono::system_clock::now())

#define DEBUG 0

struct Stage{
	vs f;
	int n,m,l,score,yakiCount,yakiMiss;
	vvi result,isYaki;
	vector<pair<int,pii>> posList;
	Stage(int N,int M,int L){
		n=N,m=M,l=L,score=-1,yakiCount=0,yakiMiss=0;
		f.resize(m,"");
		rep(i,m)rep(j,m){
			if(i%(m-1)==0 or j%(m-1)==0) f[i]+='#';
			else f[i]+='.';
		}
		f[14][14]='D';
		f[15][14]='#';
		isYaki.resize(m,vi(m,0));
	}
	void output(){
	    for(auto&a:f)cout<<a<<endl;
	}
	
	void calc(vs&s){
		simulate(s);
		int dx[]={0,1,0,-1},dy[]={-1,0,1,0};
		range(i,1,m-1)range(j,1,m-1)if(result[i][j]>4){
			//f[i][j]='#';
		}
		range(i,1,m-1)range(j,1,m-1){
			yakinamasi2(s,i,j,"LR"s);
		}
		if(DEBUG)for(auto&l:f)cout<<l<<endl;
	}
	
	pair<pii,bool> move(string&s,int cy=-1,int cx=-1){
		bool check=false;
		int x=14,y=14,v=0;
		int dx[]={0,1,0,-1},dy[]={-1,0,1,0};
		for(auto&c:s){
			if(c=='S'){
				int nx=x,ny=y,w=1;
				if(f[y][x]=='D')w=2;
				if(f[y][x]=='T')w=3;
				rep(i,w){
					nx+=dx[v], ny+=dy[v];
					if(f[ny][nx]=='#')break;
					x=nx, y=ny;
					if(x==cx and y==cy) check=true;
				}
			}else{
				if(f[y][x]=='R')turnRight(v,1);
				else if(f[y][x]=='L')turnLeft(v,1);
				else{
					int w=1;
					if(f[y][x]=='D')w=2;
					if(f[y][x]=='T')w=3;
					if(c=='L')turnLeft(v,w);
					else turnRight(v,w);
				}
			}
		}
		return make_pair(pii{y,x},check);
	}
	
	void simulate(vs&s){
		vvi res(m,vi(m,0));
		for(auto&command:s){
			auto r=move(command).first;
			res[r.first][r.second]++;
		}
		score=getScore(res);
		result=res;
	}
	
	int getScore(vvi&res){
		int sc=0;
		range(i,1,m-1)range(j,1,m-1){
			switch(res[i][j]){
				case 1: sc+=10; break;
				case 2: sc+=3; break;
				case 3: sc+=1; break;
				default: break;
			}
		}
		return sc;
	}
	
	pair<vvi,vi> yakiSim(vs&s,int cy,int cx){
		vvi res(m,vi(m,0));
		vi isPass;
		rep(i,n){
			auto r=move(s[i],cy,cx);
			if(r.second){
				isPass.push_back(i);
			}else{
				res[r.first.first][r.first.second]++;
			}
		}
		return make_pair(res,isPass);
	}
	
	void yakinamasi(vs&s){
		int mx=-1,my=-1,mv=0;
		if(posList.size()==0){
			for(int j=m-2;j>0;j--)range(i,1,m-1){
				if(f[i][j]=='.')
				posList.emplace_back(result[i][j],pii{i,j});
			}
			//sort(all(posList));
		}

		my=posList.back().second.first;
		mx=posList.back().second.second;
		posList.pop_back();
		if(mx==-1){
			isYaki.clear();
			isYaki.resize(m,vi(m,0));
			if(DEBUG)cout<<"<<<Reset>>>"<<endl;
			return;
		}
		isYaki[my][mx]=1;
		yakinamasi2(s,my,mx,"#RLDT"s);
	}
	
	void yakinamasi2(vs&s,int my,int mx,string command){
		vvi res; vi pass;
		tie(res,pass)=yakiSim(s,my,mx);
		
		int ms=score; char mc=f[my][mx],oldc=f[my][mx];
		vvi mRes=result;
		for(char c:command){
			if(c==oldc) continue;
			auto resCopy=res;
			f[my][mx]=c;
			for(auto&index:pass){
				auto r=move(s[index]).first;
				resCopy[r.first][r.second]++;
			}
			int cs=getScore(resCopy);
			if(ms<cs){
				ms=cs; mc=c; mRes=resCopy;
			}
		}

		if(oldc!=mc){
			yakiCount++;
			if(DEBUG)cout<<"miss: "<<yakiMiss<<endl;
			yakiMiss=0;
			if(DEBUG)cout<<score<<" => "<<ms<<" (+"<<ms-score<<")"<<endl;
			if(DEBUG)cout<<pii{my,mx}<<","<<mc<<endl;
		}else{
			yakiMiss++;
		}


		f[my][mx]=mc;
		if(oldc!=mc){
			yakiCount++;
			score=ms;
			result=mRes;
		}
	}

	void turnLeft(int&v,int c){ v=(v-c+4)%4; }
	void turnRight(int&v,int c){ v=(v+c)%4; }
};

#define progress (chrono::duration_cast<chrono::milliseconds>(cTime-sTime).count())

int main(){
	auto sTime=cTime;
	
	int n,m,l;
	vs s;
	
	cin.tie(0);
   	ios::sync_with_stdio(false);
    cin>>n>>m>>l;
    s.resize(n);
    rep(i,n)cin>>s[i];

	Stage best(n,m,l);
	best.calc(s);

	if(DEBUG)cout<<progress<<endl;
	int p=0;
	while(progress<2980){
		best.yakinamasi(s);
		p++;
	}

	if(DEBUG)cout<<"SCORE:"<<best.score<<endl;
	if(DEBUG)cout<<"Yakin:"<<best.yakiCount<<"/"<<p<<endl;
	best.output();
	return 0;
}
