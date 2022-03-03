/*
 * Unsecured Optimization
 */
#pragma GCC optimize "O3" /* 最適化 */
#pragma GCC target "avx" /* SIMD(ベクトル化) */
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native") /* 浮動小数点数のSIMD */
// #pragma GCC optimize "fast-math"
// #pragma GCC optimize "unroll-loops" /* ループの展開 */
#ifdef _DEBUG
// #define _GLIBCXX_DEBUG 1
#endif

/* 
 * Include Headers
 */
#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;

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
using pii=pair<int,int>;
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
constexpr double EPS=(1e-14);
constexpr long double PI=3.14159265358979323846;

/*
 * Utilities
 */
template<class T>constexpr bool chmax(T&a,T b){return a<b?a=b,1:0;}
template<class T>constexpr bool chmin(T&a,T b){return a>b?a=b,1:0;}
template<class S>S sum(vector<S>&a){return accumulate(all(a),S());}
template<class S>S max(vector<S>&a){return *max_element(all(a));}
template<class S>S min(vector<S>&a){return *min_element(all(a));}


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
	Timer(uint64_t _limit = 1970): start(getClocks()),limit(start+_limit*ClocksPerMsec) {}
	uint64_t get() const{return (getClocks()-start)/ClocksPerMsec;}
	operator bool()const{return getClocks()<limit;}
};
void wait(const int&msec){Timer tm(msec); while(tm);}


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


struct SkillMap {
	HashMap<string, int> mapper;
	vector<string> inverse;

	SkillMap() = default;
	
	int GetIndex(string s) {
		if (mapper.find(s) != mapper.end()) return mapper[s];
		mapper[s] = inverse.size();
		inverse.push_back(s);
		return mapper[s];
	}

	size_t size() {
		return inverse.size();
	}

};

struct Human {
	int id;
	string name;
	HashMap<int, int> skills;
	int currentTask = -1;
	int limitDate = -1;

	Human() = default;
	Human(int _id, string _name) : id(_id), name(_name) {}

	int AddSkillLv(int skillId, int skillLevel) {
		return skills[skillId] += skillLevel;
	}

	void LearnSkill(int skillId, int skillLevel) {
		if(skills[skillId] <= skillLevel) {
			skills[skillId] += 1;
		}
	}

	bool IsWorking() {
		return currentTask != -1;
	}

};

struct Skill {
	int skillId, skillLv;
	Skill() = default;
	Skill(int _skillId, int _skillLv) : skillId(_skillId), skillLv(_skillLv) {}

	bool Satisfy(Human& human) {
		return human.skills[skillId] >= skillLv;
	}
};

struct Task {
	int id, requireDayCount, score, dueDate;
	string name;
	vector<Skill> skills;
	bool finished = false;

	Task() = default;
	Task(int _id, string _name, int _requireDayCount, int _score, int _dueDate) : id(_id), name(_name), requireDayCount(_requireDayCount), score(_score), dueDate(_dueDate) {}


	/* humansを適当に割り当てる */
	bool Assign(vector<Human>& humans, vector<int>&assignedIndex) {
		HashSet<int> assignedId;
		int maxLimitDate = -1;
		HashMap<int,int> skillSet;

		for(auto&skill : skills) {
			/*割り当てる人を決める*/
			int requireLevel = skill.skillLv;
			if(skillSet.find(skill.skillId) != skillSet.end()) {
				if(skillSet[skill.skillId] >= requireLevel) requireLevel--;
			}
			bool ok = false;
			rep(i,humans.size()){
				Human&human = humans[i];

				if(human.skills[skill.skillId] >= requireLevel) {
					if(assignedId.find(i) != assignedId.end()) continue;
					ok = true;
					assignedIndex.push_back(i);
					assignedId.insert(i);
					chmax(maxLimitDate, human.limitDate);

					for(auto&[skillId, skillLv] : human.skills) {
						chmax(skillSet[skillId], skillLv);
					}
					break;
				}
			}
			if(!ok) {
				return false;
			}
		}

		// maxLimitDate+1日目から作業可能
		int finishDate = maxLimitDate + requireDayCount;

		// TEST: 点数が入らない場合飛ばす C,Fのみ有効
		if(finishDate - dueDate >= score ) {
			return false;
		}
		
		rep(i, assignedIndex.size()){
			/*割り当て可能なので、完了してレベルアップ処理*/
			Human& human = humans[assignedIndex[i]];
			human.currentTask = id;
			human.limitDate = finishDate;
			human.LearnSkill(skills[i].skillId, skills[i].skillLv);

			assignedIndex[i] = human.id; // 返した先で参照しやすいようにidで返す
		}
		
		finished = true;

		return true;
	}

};

struct StaticDataStore {
private:
	StaticDataStore() = default;

public:
	static inline int humanCount;
	static inline int taskCount;

	static inline SkillMap skillMap;
	static inline vector<Human> humans;
	static inline vector<Task> tasks;


	static void Input() {
		cin>>humanCount>>taskCount;

		{
			string name, skillName; int skillCount, skillLv;
			rep(i,humanCount){
				cin>>name>>skillCount;
				humans.emplace_back(i, name);
				rep(skillCount){
					cin>>skillName>>skillLv;
					int skillId = skillMap.GetIndex(skillName);
					humans.back().AddSkillLv(skillId, skillLv);
				}
			}
		}

		{
			string name, skillName;
			int requireDayCount, score, dueDate, skillCount, skillLv;
			rep(i,taskCount){
				cin>>name>>requireDayCount>>score>>dueDate>>skillCount;
				tasks.emplace_back(i, name, requireDayCount, score, dueDate);
				rep(skillCount){
					cin>>skillName>>skillLv;
					int skillId = skillMap.GetIndex(skillName);
					tasks.back().skills.emplace_back(skillId, skillLv);
				}
			}
		}
	}
};

struct _Construct {
	_Construct(){
		StaticDataStore::Input();
	}
} _construct;


struct SolverInterface {
	virtual int Solve() = 0;
	virtual void Print() = 0;

protected:

};


struct GreedySolver : public SolverInterface {
	int score = 0;
	int day = 0;


	vector<Task> tasks;
	vector<Human> humans;

	vector<string> answerTaskNames;
	vector<vector<int>> answerTaskHumans;


	GreedySolver() {
		for(auto&task : StaticDataStore::tasks){
			// if(task.)
			tasks.push_back(task);
		}
		sort(all(tasks), [](Task&a, Task&b) {
			return a.requireDayCount < b.requireDayCount;
		});

		humans = StaticDataStore::humans;
	}

	int Solve() {
		Timer timer(3000);
		int taskRemain = tasks.size();
		while(timer){
			bool isAssigned = false;
			vector<int> assignedId;
			rep(i,taskRemain){
				Task&task = tasks[i];
				if(task.finished) continue;
				assignedId.clear();
				if(task.Assign(humans, assignedId)) {
					answerTaskNames.push_back(task.name);
					answerTaskHumans.push_back(assignedId);
					isAssigned = true;
					taskRemain--;
					swap(tasks[taskRemain], tasks[i]);
					break;
				}
			}
			if(!isAssigned) break;
			sort(all(humans), [](Human&a, Human&b) {
				return a.limitDate < b.limitDate;
			});
		}
		
		return score;
	}

	void Print() {
		/* 結果を出力 */
		cout<<answerTaskNames.size()<<endl;
		rep(i, answerTaskNames.size()){
			cout<<answerTaskNames[i]<<endl;
			bool fs=true;
			for(auto&humanId : answerTaskHumans[i]){
				if(fs){
					cout<<StaticDataStore::humans[humanId].name;
					fs=false;
				}else{
					cout<<" "<<StaticDataStore::humans[humanId].name;
				}
			}
			cout<<endl;
		}
	}
};

struct HogeSolver : public SolverInterface {
	int score = 0;
	int day = 0;


	vector<Task> tasks;
	vector<Human> humans;

	HogeSolver() {
		tasks = StaticDataStore::tasks;
		sort(all(tasks), [](Task&a, Task&b) {
			return a.dueDate < b.dueDate;
		});

		humans = StaticDataStore::humans;
	}

	// 人目線アルゴリズム
	int Solve() {
		// タスクごとに、「現在何人アサインされているか」変数を持つ
		// 人は、自分のスキルとレベルと、部屋に入って何ターン待機しているか(不要かも)のパラメータを持つ
		// ターン数でループ(問題中の時間とは別)
			// 人をrandomに並べ替える
			// 人でループ
				// 待機ターンが0の人は、
					// 仕事一覧の中から自分が取り組めるものを探し、部屋に入ってほかのメンバーを待つ
					// もちろん、すでに入っている人の指導を受けられる前提で入る
						// 仕事一覧の中から自分が取り組めるものを探すアルゴリズム
						// hashmap<スキル：pair<タスク番号:レベル>> のテーブルを用意しておく
						// 人は、自分の持っているスキルから適当に一つ選び、テーブルから受けられるタスクを探す
							// 受けられるタスクが見つかったら、そのpair<タスク番号:レベル>を人が持ち、テーブルから消す
							// タスク番号に対応するタスクの「現在何人アサインされているか」を増やす
						// 三つくらいスキルを適当に選んでも達成できなかったら、あきらめる
				// 待機ターンが0ではない人は、
					// 待機ターンを1増やす
					// 適当に3とかでに決めた最大ターン数が経過していたら、その部屋を抜けて待機ターンを0にする
			// タスクでループ
				// 部屋に必要な人数が集まっていたら、即時そのタスクをクリアしたことにし、レベルアップする
				// ここでは人数比較のみでOK、なぜならここではクリア可能な前提で入っているため
	}

	void Print() {
		/* 結果を出力 */
		cout<<score<<endl;
	}
};

int main(){
	Timer timer;

	SolverInterface* solver = new GreedySolver();

	cerr<<solver->Solve()<<endl;

	solver->Print();

	cerr<<timer.get()<<" ms"<<endl;
}
