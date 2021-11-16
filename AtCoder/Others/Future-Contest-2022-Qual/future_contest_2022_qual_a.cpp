/*
 * Unsecured Optimization
 */
// #pragma GCC target "avx" /* SIMD(ベクトル化) */
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native") /* 浮動小数点数のSIMD */
// #pragma GCC optimize "O3" /* 最適化 */
// #pragma GCC optimize "fast-math"
// #pragma GCC optimize "unroll-loops" /* ループの展開 */
#ifdef _DEBUG
// #define _GLIBCXX_DEBUG 1
#endif

/* 
 * Include Headers
 */
#if defined(EVAL) || defined(ONLINE_JUDGE) || defined(_DEBUG)
#include <atcoder/all>
using namespace atcoder;
#endif
#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;

void Main();
int main(){cin.tie(nullptr);ios::sync_with_stdio(false);Main();return 0;}

/*
 * Additional Type Definition
 */
using ll=long long;
using ld=long double;
using ull=unsigned long long;
using vb=vector<bool>;
using vvb=vector<vb>;
using vd=vector<ld>;
using vvd=vector<vd>;
using vi=vector<int>;
using vvi=vector<vi>;
using vl=vector<ll>;
using vvl=vector<vl>;
using pll=pair<ll,ll>;
using vp=vector<pll>;
using tl2=tuple<ll,ll>;
using tl3=tuple<ll,ll,ll>;
using vs=vector<string>;
template<class K> using IndexedSet=__gnu_pbds::tree<K,__gnu_pbds::null_type,less<K>,__gnu_pbds::rb_tree_tag,__gnu_pbds::tree_order_statistics_node_update>;
template<class K> using HashSet=__gnu_pbds::gp_hash_table<K,__gnu_pbds::null_type>;
template<class K,class V> using IndexedMap=__gnu_pbds::tree<K,V,less<K>,__gnu_pbds::rb_tree_tag,__gnu_pbds::tree_order_statistics_node_update>;
template<class K,class V> using HashMap=__gnu_pbds::gp_hash_table<K,V>;


/*
 * Macros
 */
#define all(a) a.begin(),a.end()
#define rall(a) a.rbegin(),a.rend()
#define __LOOPSWITCH(_1, _2, _3, __LOOPSWITCH, ...) __LOOPSWITCH
#define rep(...) __LOOPSWITCH(__VA_ARGS__, __RANGE, __REP, __LOOP) (__VA_ARGS__)
#define rrep(...) __LOOPSWITCH(__VA_ARGS__, __RRANGE, __RREP, __LOOP) (__VA_ARGS__)
#define __LOOP(q) __LOOP2(q, __LINE__)
#define __LOOP2(q,l) __LOOP3(q,l)
#define __LOOP3(q,l) __REP(_lp ## l,q)
#define __REP(i,n) __RANGE(i,0,n)
#define __RANGE(i,a,n) for(ll i=((ll)a);i<((ll)n);++i)
#define __RREP(i,n) __RRANGE(i,0,n)
#define __RRANGE(i,a,n) for(ll i=((ll)n-1);i>=((ll)a);--i)
#define repsq(i,n) for(ll i=0;i*i<=n;++i)
#define each(v,a) for(auto v:a)
#define eachref(v,a) for(auto&v:a)
#define fcout(a) cout<<setprecision(a)<<fixed

/*
 * Constants
 */
constexpr ll LINF=1ll<<60;
constexpr int INF=1<<30;
constexpr double EPS=(1e-9);
constexpr ll MOD=1000000007ll;
constexpr long double PI=3.14159265358979323846;

/*
 * Output Assist
 */
template<class T>struct hasItr{
	template<class U>static constexpr true_type check(class U::iterator*);
	template<class U>static constexpr false_type check(...);
	static constexpr bool v=decltype(check<T>(nullptr))::value;
};
template<>struct hasItr<string>{static constexpr bool v=false;};

template<class T>void puta(T&t,false_type,ostream&os,[[maybe_unused]]char el){os<<t;}
template<class T>void puta(T&t,true_type,ostream&os,char el){
	constexpr bool h=hasItr<typename T::value_type>::v;
	bool F=true,I;
	for(auto&i:t){
		if(!F)os<<' ';
		puta(i,bool_constant<h>(),os,el);
		F=I=h;
	}
	if(!I)os<<el;
}
template<class T>void puta(const T&t, ostream&os=cout, char el='\n'){
	puta(t,bool_constant<hasItr<T>::v>(),os,el);
	if(!hasItr<T>::v)os<<el;
}
template<class H,class...T>void puta(const H&h,const T&...t){cout<<h<<' ';puta(t...);}
template<size_t i,class...T>void puta(tuple<T...>const&t, ostream&os){
	if constexpr(i==sizeof...(T)-1)puta(get<i>(t),os);
	else{os<<get<i>(t)<<' ';puta<i+1>(t,os);}
}
template<class...T>void puta(tuple<T...>const&t, ostream&os=cout){puta<0>(t,os);}
template<class S,class T>constexpr ostream&operator<<(ostream&os,pair<S,T>p){
	os<<'['<<p.first<<", ";
	if constexpr(hasItr<T>::v)puta(p.second,bool_constant<true>(),os,']');
	else os<<p.second<<']';
	return os;
};
template<class...T>constexpr ostream&operator<<(ostream&os,tuple<T...>t){puta(t,os); return os;}
void YN(bool b){puta(b?"YES":"NO");}
void Yn(bool b){puta(b?"Yes":"No");}

#ifdef _DEBUG
template<class T>void dump_f(const T&t){puta(t,cerr);}
template<class H,class...T>void dump_f(const H&h,const T&...t){cerr<<h<<' ';dump_f(t...);}
template<class...T>void dump_f(tuple<T...>const&t){puta(t,cerr);}
#define dump(...)cerr<<"  "<<string(#__VA_ARGS__)<<": ["<<to_string(__LINE__)<<":"<<__FUNCTION__<<"]\n    ",dump_f(__VA_ARGS__)
#else
#define dump(...)                                                              
#endif

/*
 * Input Assist
 */
template<class S,class T>auto&operator>>(istream&is,pair<S,T>&p){is>>p.first>>p.second;return is;}
template<class S>auto&operator>>(istream&is,vector<S>&t){for(S&a:t)is>>a;return is;}
template<typename...S>void geta_(S&...s){((cin>>s),...);}
#define geta(t,...) t __VA_ARGS__;geta_(__VA_ARGS__)
template<class T,class...Args>auto vec(T x,int arg,Args...args){if constexpr(sizeof...(args)==0)return vector(arg,x);else return vector(arg,vec(x,args...));}
#define getv(a,...) auto a=vec(__VA_ARGS__);cin>>a

/*
 * Utilities
 */
template<class T>constexpr bool chmax(T&a,T b){return a<b?a=b,1:0;}
template<class T>constexpr bool chmin(T&a,T b){return a>b?a=b,1:0;}
template<class S>S sum(vector<S>&a){return accumulate(all(a),S());}
template<class S>S max(vector<S>&a){return *max_element(all(a));}
template<class S>S min(vector<S>&a){return *min_element(all(a));}
template<class T>T gcd(vector<T> v){return accumulate(all(v),T(),gcd<T,T>);}
template<class T> pair<int,T> getMaxAndIndex(vector<T> a){
	int p=-1; T v=numeric_limits<T>::min();
	rep(i,a.size())if(chmax(v,a[i]))p=i;
	return {p,v};
}

// ここにライブラリを貼る
class Random {
public:
	typedef uint_fast32_t result_type;
	constexpr result_type operator()(){return operator()((ll)min(),(ll)max());}
	static constexpr result_type max(){return numeric_limits<result_type>::max();}
	static constexpr result_type min(){return 0;}
	constexpr Random(const bool&isDeterministic):y(isDeterministic?2463534242:chrono::system_clock::now().time_since_epoch().count()){}
	constexpr int operator()(int a,int b){return next()%(b-a)+a;}
	constexpr ll operator()(ll a,ll b){return (((ull)next())<<32|next())%(b-a)+a;}
	constexpr double operator()(double a,double b){return (b-a)*next()/4294967296.0+a;}
private:
	result_type y;
	constexpr result_type next(){return y^=(y^=(y^=y<<13)>>17)<<5;}
} Random(0);

class Timer {
	#ifdef _DEBUG
	static constexpr uint64_t ClocksPerMsec = 3587000;
	#else
	static constexpr uint64_t ClocksPerMsec = 2987000;
	#endif
	const uint64_t start,limit;
	uint64_t getClocks() const{
		unsigned int lo,hi;
		__asm__ volatile ("rdtsc" : "=a" (lo), "=d" (hi));
		return((uint64_t)hi<<32)|lo;
	}
public:
	Timer(uint64_t _limit): start(getClocks()),limit(start+_limit*ClocksPerMsec) {}
	uint64_t get() const{return (getClocks()-start)/ClocksPerMsec;}
	operator bool()const{return getClocks()<limit;}
};
void wait(const int&msec){Timer tm(msec); while(tm);}

#if !defined(ONLINE_JUDGE)
#define LOCAL
// #define OPTIMAL
#endif

const int n=1000, m=20;
int k;

struct Task{
	int level=0, parentCount=0;
    int taskId;
	int remainDay=0, descendantsCount=0;
	vi skill;
	vi parent, child;
	void init(int index){
    	taskId=index;
		skill.resize(k);
		cin>>skill;
		level=sum(skill)-max(skill);
	}

	int priority(int type){
		return remainDay;
		
		// 0=1000, 5=3000, 6=2000, 10=1500, 18=2500
		if(type == 0)
			// 0=1525, 5=1891, 6=2088, 10=2076, 18=1892
			return descendantsCount;
		if(type == 1)
			// 0=1910, 5=1615, 6=2081, 10=2107, 18=1845
			return remainDay;
	}
};
vector<Task> tasks(n);

struct Member{
	bool working = false;
	int memberId=0;
	int assignedTask = -1;
	int startDate=-1;
	int clearTaskCount=0;
	vi skill, skillAnswer, skillMinimum;

	void init(int index){
		memberId=index;
		skill=vec(3,k);
		skillMinimum=vec(0,k);
		#ifdef LOCAL
		skillAnswer.resize(k);
		cin>>skillAnswer;
		#ifdef OPTIMAL
		skill=skillMinimum=skillAnswer;
		#endif
		#endif
	}

	void outputPredictedSkill(){
		puta("#s", memberId+1, skill);
	}

	int predict(int taskId, bool strict=false){
		if(!strict && clearTaskCount==0){
			return 0; //一度も出ていない場合、まず一度出てもらう
		}
		int w=0;
		rep(i,k)w+=max(0, tasks[taskId].skill[i]-skillMinimum[i]);
		if(w==0) return 1;
		else return w;
	}

	void assign(int taskId, int currentDate){
		puta("#", memberId+1, "を", taskId+1, "に割り当て");
		outputPredictedSkill();
		working=true;
		assignedTask=taskId;
		startDate=currentDate;
	}

	void finish(int currentDate){
		working=false;
		clearTaskCount++;
		#ifdef OPTIMAL
		return;
		#endif
		int date=currentDate-startDate+1;
		// assignedTaskの完了にdate日かかった
		bool isMinimumUpdate=false;
		if(date==1){
			// 即日完了したなら、タスクを即座にこなせる実力まで予測値を引き上げる
			rep(i,k)isMinimumUpdate|=chmax(skillMinimum[i], tasks[assignedTask].skill[i]);
		}else{
			rep(i,k){
				isMinimumUpdate|=chmax(skillMinimum[i], tasks[assignedTask].skill[i]-date);
				// chmax(skill[i], skillMinimum[i]);
			}
            rep(i,k){
                int taskLv=tasks[assignedTask].level;
                int requireLv=tasks[assignedTask].skill[i];
                int predictedRatio = (requireLv * (taskLv - date) + taskLv-1) / taskLv;
				int diff = predictedRatio-skill[i];
				diff=(abs(diff)+4)/5 * 0 + (diff>0?1:-1);
				skill[i]+=diff;
            }
		}
		if(isMinimumUpdate){
			puta("#", memberId+1, "のMinimumを更新 : ", currentDate);
		}
        rep(i,k)chmax(skill[i],skillMinimum[i]);
		puta("#", memberId+1, "が", assignedTask+1, "から", date, "日で帰還");
		outputPredictedSkill();
	}
};
vector<Member> members(m);

struct Simulator{
	enum ASSIGN_STATUS{
		SUCCESS,
		INEFFICIENT,
		BUSY,
	};
	int finishedTaskCount=0;
	vvi requireDate;
	void input(){
		requireDate = vec(0,n,m);
		cin>>requireDate;
	}

	int day=0;
	vi assignedList;

	int getPredictedDate(int memberId, int taskId, bool strict=false){
		// #ifdef OPTIMAL
		// return requireDate[memberId][taskId];
		// #endif
		return members[memberId].predict(taskId,strict);
	}

	void assignTask(int memberId, int taskId){
		members[memberId].assign(taskId, day);
		assignedList.push_back(memberId+1);
		assignedList.push_back(taskId+1);
	}

	// 日付を進める
	void sleep(){
		day++;
		assignedList.clear();
		puta("###################");
		puta("#", day, "日目 残タスク", n-finishedTaskCount,"個");
		puta("###################");
	}
	
	// 割り当てたメンバーを送り出す
	void go(){
		if(!assignedList.empty()){
			puta(assignedList.size()/2, assignedList);
		}else{
			puta(0);
		}
		cout.flush();
	}

	pair<bool,vi> getResult(){
		int cnt=0; vi finishedMembers;
		#ifdef LOCAL
		if(day==2000)return {false, {}};

		rep(i,m)if(members[i].working){
			int req=requireDate[members[i].assignedTask][i];
			if(req==day-members[i].startDate+1){
				finishedMembers.push_back(i+1);
				finishedTaskCount++;
			}
		}
		if(finishedTaskCount==n)return {false, {}};
		cnt=finishedMembers.size();
		#else
		cin>>cnt;
		if(cnt==-1) return {false, {}};
		finishedMembers.resize(cnt);
		cin>>finishedMembers;
		finishedTaskCount += cnt;
		#endif
		// puta("#x", cnt, "人が帰還");

		vi finishedTasks;
		each(memberId, finishedMembers){
			members[memberId-1].finish(day);
			// puta("#d", day, "日目に",members[memberId-1].assignedTask,"が終了");

			finishedTasks.push_back(members[memberId-1].assignedTask);
		}
		return {true, finishedTasks};
	}

	bool isBusy(){
		bool isBusy=true;
		each(member,members)isBusy&=member.working;
		return isBusy;
	}

	// 指定したタスクに、最善の暇人を割り当てる
	ASSIGN_STATUS decideAssign(int taskId, bool forceSelect=false){
		if(isBusy()) return BUSY;

		vector<pair<int,int>> p;
		if(forceSelect){
			// 今空いている誰かを必ず割り振る
			rep(i,m)if(!members[i].working)p.emplace_back(getPredictedDate(i,taskId), i);
			sort(all(p));
			assignTask(p[0].second, taskId);
			return SUCCESS;
		}else{
			// 今空いている誰かを、「その人より早く達成できる人がいない場合」割り振る
			rep(i,m)p.emplace_back(getPredictedDate(i,taskId), i);
			sort(all(p));
			
			rep(i,m)if(!members[p[i].second].working){
				if(p[i].first==p[0].first){
					assignTask(p[i].second, taskId);
					return SUCCESS;
				}
			}
			return INEFFICIENT;
		}
	}
};

void Main(){
	Simulator simulator;
	{
		int _,r; cin>>_>>_;
		cin>>k>>r;

		rep(i,n){
			tasks[i].init(i);
		}
		rep(r){
			geta(int, u,v);
			tasks[u-1].child.push_back(v-1);
			tasks[v-1].parent.push_back(u-1);
			tasks[v-1].parentCount++;
		}

		rep(i,m){
			members[i].init(i);
		}

		#ifdef LOCAL
		simulator.input();
		#endif
	}

	// 各タスクにlevel日掛かる時、このタスクを何日前に開始する必要があるか？
	{
		queue<int> q;
		vi childCount(n,0);
		rep(i,n)childCount[i]=tasks[i].child.size();
		rep(i,n)if(childCount[i]==0)q.push(i);
		while(!q.empty()){
			auto p=q.front(); q.pop();
			for(auto&c:tasks[p].child){
				chmax(tasks[p].remainDay, tasks[c].remainDay);
				tasks[p].descendantsCount += tasks[c].descendantsCount+1;
			}
			tasks[p].remainDay+=tasks[p].level;
			for(auto&parent:tasks[p].parent)if((--childCount[parent])==0)q.push(parent);
		}
	}


	int type=1;

	vi parentCount(n,0);
	rep(i,n)parentCount[i]=tasks[i].parent.size();
	priority_queue<pair<int,int>> q;
	rep(i,n)if(parentCount[i]==0)q.emplace(tasks[i].priority(type), i);
	
	rep(2000){
		simulator.sleep();

		vector<pair<int,int>> skippedTasks;
		// cerr<<"START"<<endl;
		while(!q.empty()){
			auto[level, taskId]=q.top();

			auto result = simulator.decideAssign(taskId);
			// cerr<<level<<","<<taskId<<" : "<<result<<endl;
			if(result == Simulator::BUSY){
				break;
			}
			q.pop();
			if(result == Simulator::INEFFICIENT){
				skippedTasks.emplace_back(level, taskId);
			}
		}
		// cerr<<"FINISH"<<endl;

		each(t,skippedTasks)q.push(t);
		while(!q.empty()){
			auto[level, taskId]=q.top();
			if(simulator.decideAssign(taskId, true)==Simulator::SUCCESS){
				q.pop();
			}else break;
		}

		simulator.go();

		auto[ok,task]=simulator.getResult();
		if(!ok)break;
		each(t,task){
			for(auto&c:tasks[t].child){
				if(--parentCount[c] == 0)q.emplace(tasks[c].priority(type), c);
			}
		}
	}
	cerr<<3000-simulator.day<<endl;
	rep(i,m)puta("#s",i+1,members[i].skill);

}
