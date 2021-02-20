#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using vi=vector<int>;
using vvi=vector<vi>;
using vl=vector<ll>;
using vd=vector<double>;
using vvl=vector<vl>;
using pii=pair<int,int>;
#define rep(i,n) range(i,0,n)
#define range(i,a,n) for(int i=a;i<n;i++)
#define all(a) a.begin(),a.end()
#define LINF    	((ll)1ll<<60)
#define INF     	((int)1<<30)
#define fs 			first
#define sc			second
#define cTime (chrono::system_clock::now())
#define progress (chrono::duration_cast<chrono::milliseconds>(cTime-sTime).count())

template<class S,class T>ostream& operator<<(ostream&os,pair<S,T>p){os<<"["<<p.first<<", "<<p.second<<"]";return os;};
template<class S>auto&operator<<(ostream&os,vector<S>t){bool a=1; for(auto s:t){os<<(a?"":" ")<<s; a=0;} return os;}

int t,n,m;

vi weight,w2;
struct quest{
	int a,b;
	ll c;
	vi s;
	bool isFinished;
	quest(){a=b=c=0; isFinished=false;}
	void get(){
		cin>>a>>b>>c;
		s.resize(n);
		rep(i,n){
			cin>>s[i];
			if(c>10000)
				weight[i]+=s[i]*s[i];
			if(c>100000)
				w2[i]=max(w2[i],s[i]);
		}
	}
	ll eval(vd skill, int t){
		if(t<a or b<t) return 0;
		int d=0;
		rep(i,n) d+=max(0.0,s[i]-skill[i]);
		double rate=1+9.0*(t-a)/(b-a);
		if(d==0) return floor(c*10*rate);
		else return floor((c>>d)*rate);
	}
};

using act=vector<pii>;
using status=tuple<vd,ll,act>;
vector<quest> data;
vvi able; 
vl need{0,2,10,34,98,258,642,1538,3586,8194,18434};
int turn;
ll statusEval(status a){
	ll ret=get<ll>(a);
	int cnt=100;
	if(turn<400){
		ret=0;
		rep(i,n){
			ret+=10000ll*need[(int)floor(get<vd>(a)[i])];
			ret+=(int)floor(get<vd>(a)[i])*1000000ll;
			if((int)floor(get<vd>(a)[i])==10)ret+=10000000ll;
			cnt-=get<vd>(a)[i];
		}
		ret+=get<ll>(a)/cnt;
	}
	return ret;
}

auto statusCmp=[](status a, status b){return statusEval(a)>statusEval(b);};

int main(){
	auto sTime=cTime;
	cin.tie(0);
   	ios::sync_with_stdio(false);
	
	cin>>t>>n>>m;
	data.resize(m);
	able.resize(t+1);
	weight=vi(n,0);
	w2=vi(n,0);
	rep(i,m){
		data[i].get();
		able[data[i].b].push_back(i);
		able[data[i].b-1].push_back(i);
	}

	vector<deque<status>> dq(t+1);
	dq[0].emplace_back(vd(10,0),1000,act());
	int beam=10000;

	int found=0;
	ll maxScore=0ll;
	act ans;
	//選べる限り貪欲に
	for(turn=0;turn<t;turn++){
		while(!dq[turn].empty() && found<beam){
			vd c_skill; ll c_score; act c_act;
			tie(c_skill,c_score,c_act)=dq[turn].front();
			dq[turn].pop_front();

			act copy_act;
			bool isTrained=false;
			int minJump=100;
			rep(i,n)if(c_skill[i]<10){
				int c_level=(int)floor(c_skill[i]);
				ll needScore=10000ll*(need[c_level+1]-need[c_level]);
				if(needScore<=c_score && turn+c_level+1<=t){
					isTrained=true;
					vd copy_skill=c_skill;
					copy_act=c_act;
					rep(_,c_level+1){
						copy_act.emplace_back(1,i+1);
					}
					copy_skill[i]+=1.0;
					dq[turn+c_level+1].emplace_back(copy_skill, c_score-needScore,copy_act);
					minJump=min(minJump,c_level);
				}
			}
			if(minJump!=100){
				turn+=minJump;
				break;
			}

			int mID=-1; ll mScore=1000ll;
			for(auto&id:able[turn+1]){
				if(c_act.size()!=0 && c_act.back().first==2 && c_act.back().second==id+1) continue;
				ll getScore=data[id].eval(c_skill, turn+1);
				if(getScore>mScore){
					mID=id;
					mScore=getScore;
				}
			}

			if(mID==-1){ //クエストを受けられない
				copy_act=c_act;
				copy_act.emplace_back(3,0);
				dq[turn+1].emplace_back(c_skill, c_score+1000, copy_act);
			}else{
				act copy_act=c_act;
				copy_act.emplace_back(2,mID+1);
				dq[turn+1].emplace_back(c_skill, c_score+mScore, copy_act);
			}
		}
		sort(all(dq[turn+1]),statusCmp);
		dq[turn+1].erase(unique(all(dq[turn+1])),dq[turn+1].end());
		if(dq[turn+1].size()>beam){
			dq[turn+1].resize(beam);
			dq[turn+1].shrink_to_fit();
		}
	}
	ans=get<act>(dq[t].front());
	for(auto&p:ans){
		if(p.first==3){
			cout<<p.first<<endl;
		}else{
			cout<<p.first<<" "<<p.second<<endl;
		}
	}
	//cout<<progress<<endl;
	return 0;
}
