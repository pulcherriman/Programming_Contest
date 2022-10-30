#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("inline")

#pragma GCC diagnostic ignored "-Wunused-value"

#include <algorithm>
#include <iostream>
#include <cstdio>
#include <map>
#include <numeric>
#include <cmath>
#include <set>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <complex>
#include <string.h>
#include <unordered_set>
#include <unordered_map>
#include <bitset>
#include <iomanip>
#include <sys/time.h>
#include <tuple>
#include <random>
#include <chrono>
using namespace std;

/*
 * Additional Type Definition
 */
using vb=vector<bool>;
using vvb=vector<vb>;
using vi=vector<int>;
using vvi=vector<vi>;
using ll=long long;
using vl=vector<ll>;
using vvl=vector<vl>;
using ld=float;
using vd=vector<ld>;
using vvd=vector<vd>;
using pii=pair<int,int>;
using vp=vector<pii>;
using ti2=tuple<int,int>;
using ti3=tuple<int,int,int>;
using ti4=tuple<int,int,int,int>;
using vs=vector<string>;

#define all(a) begin(a),end(a)
#define rall(a) rbegin(a),rend(a)
#define __LOOPSWITCH(_1, _2, _3, __LOOPSWITCH, ...) __LOOPSWITCH
#define rep(...) __LOOPSWITCH(__VA_ARGS__, __RANGE, __REP, __LOOP) (__VA_ARGS__)
#define rrep(...) __LOOPSWITCH(__VA_ARGS__, __RRANGE, __RREP, __LOOP) (__VA_ARGS__)
#define __LOOP(q) __LOOP2(q, __LINE__)
#define __LOOP2(q,l) __LOOP3(q,l)
#define __LOOP3(q,l) __REP(_lp ## l,q)
#define __REP(i,n) __RANGE(i,0,n)
#define __RANGE(i,a,n) for(int i=((int)a);i<((int)n);++i)
#define __RREP(i,n) __RRANGE(i,0,n)
#define __RRANGE(i,a,n) for(int i=((int)((n)-1));i>=((int)a);--i)
#define siz(a) ((int)(a).size())

/*
 * Constants
 */
constexpr int INF=1<<30;

/*
 * Utilities
 */
template<class T>constexpr bool chmax(T&a,T b){return a<b?a=b,1:0;}
template<class T>constexpr bool chmin(T&a,T b){return a>b?a=b,1:0;}
template<class S>S sum(vector<S>&a){return accumulate(all(a),S());}
template<class S>S max(vector<S>&a){return *max_element(all(a));}
template<class S>S min(vector<S>&a){return *min_element(all(a));}

namespace IO {
	// container detection
	template<typename T, typename _=void> struct is_container : false_type {};
	template<> struct is_container<string> : false_type {};
	template<typename...Ts> struct is_container_helper {};
	template<typename T> struct is_container<T, conditional_t<
		true, void, is_container_helper<
			typename T::value_type, typename T::size_type, typename T::iterator,
			decltype(declval<T>().size()),
			decltype(declval<T>().begin()),
			decltype(declval<T>().end()) >>> : public true_type {};
	template<typename T,
		typename enable_if<is_container<T>{}, nullptr_t>::type = nullptr,
		char Separator = is_container<typename T::value_type>{} ? '\n' : ' ' >
	constexpr ostream&operator<<(ostream&os, T t){
		if(auto b=begin(t), e=end(t) ; !t.empty()) for(os<<(*b++);b!=e;os<<Separator<<(*b++)) ;
		return os;
	}

	// output
	template<class T, class...Ts> constexpr ostream& pargs(ostream&os, T&&t, Ts&&...args); // support clang
	template<class S,class T>constexpr ostream&operator<<(ostream&os,pair<S,T>p){ return os<<'['<<p.first<<", "<<p.second<<']'; };
	template<class...Ts>constexpr ostream&operator<<(ostream&os,tuple<Ts...>t){
		return apply([&os](auto&&t,auto&&...args)->ostream&{return pargs(os, t, args...);}, t);
	};
	template<class T, class...Ts> constexpr ostream& pargs(ostream&os, T&&t, Ts&&...args) {
		return ((os<<t)<<...<<(os<<' ', args));
	}

	template<class...Ts> constexpr ostream& out(Ts...args) { return pargs(cout, args...)<<'\n'; }
	template<class...Ts> constexpr ostream& debug_f(Ts...args) { return pargs(cerr, args...)<<'\n'; }
	#ifdef _DEBUG
	template<class...Ts> constexpr ostream& debug(Ts...args) { 
		return pargs(cerr, args...)<<'\n';
	}
	#else
	#define debug(...) if(false)debug_f(__VA_ARGS__)
	#endif
	void Yn(bool f) { out(f?"Yes":"No"); }

	// input
	template<class T, class...Ts> constexpr istream& gargs(istream&is, T&&t, Ts&&...args) {
		return ((is>>t)>>...>>args);
	}
	template<class S,class T>auto&operator>>(istream&is,pair<S,T>&p){return is>>p.first>>p.second;}
	template<class...Ts>constexpr istream&operator>>(istream&is,tuple<Ts...>&t){
		return apply([&is](auto&&t,auto&&...args)->istream&{return gargs(is, t, args...);}, t);
	};

	template<typename...S>auto&in(S&...s){return gargs(cin, s...);}
	#define def(t,...) t __VA_ARGS__; in(__VA_ARGS__)
	template<typename T, typename enable_if<is_container<T>{}, nullptr_t>::type = nullptr>
	auto&operator>>(istream&is,T&t){for(auto&a:t)is>>a; return is;}
}
using namespace IO;

class Random {
public:
	using result_type = unsigned int;
	constexpr result_type operator()(){return operator()(min(),max());}
	static constexpr result_type max(){return numeric_limits<result_type>::max();}
	static constexpr result_type min(){return 0;}
	constexpr Random(const bool&isDeterministic):y(isDeterministic?2463534242ll:chrono::system_clock::now().time_since_epoch().count()){}
	constexpr result_type operator()(result_type a, result_type b){return next()%(b-a)+a;}
	result_type getSeed(){return y;}
	void setSeed(result_type seed){y=seed;}
private:
	result_type y;
	constexpr result_type next(){return y^=(y^=(y^=y<<13)>>17)<<5;}
}
#ifdef _DEBUG
Random(1);
#else
Random(0);
#endif

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
	Timer(uint64_t _limit=1970): start(getClocks()),limit(start+_limit*ClocksPerMsec) {}
	uint64_t get() const{return (getClocks()-start)/ClocksPerMsec;}
	operator bool()const{return getClocks()<limit;}
};
void wait(const int&msec){Timer tm(msec); while(tm);}

struct Mgr {
	static const int TLE = 5000;
	static inline Timer timer = Timer(TLE-100);
	Mgr() {
		ios_base::sync_with_stdio(0); cin.tie(0);
		cerr<<fixed<<setprecision(3);
	}
	~Mgr(){
		debug_f(timer.get(), "ms")<<flush;
	}
} _manager;

/**
 * 問題文が長い　わからん
 * 
 * M=10~20台の設備がある
 * 各設備ごとに、X=8~16週間分の稼働時間を決定する
 * X週間のあいだに、N=(masked)件の注文を処理する必要がある
 */

/** @paragraph 注文データについて(masked)
 * 各注文は以下のように定義される
 * 	納期D_i>0, 開始からの秒数 
 * 	完了までに必要な工程数J_i=???
 * 	各工程を処理する設備R_ij∈M と時間T_ij<=2880[sec]
 * 工程が進むと設備番号が大きくなる
 * @note この注文情報は渡されない なんでやねん
 */

/** @paragraph 設備の稼働時間について
 * 設備稼働の時間帯は、9パターンから選択する
 * 	1: 休む
 * 	2: 9:00~12:00
 * 	3: 13:00~18:00
 * 	4: 9:00~12:00, 13:00~18:00
 * 	5: 9:00~12:00, 13:00~20:00
 * 	6: 9:00~12:00, 13:00~22:00
 * 	7: 9:00~12:00, 13:00~24:00
 * 	8: 9:00~12:00, 13:00~26:00
 * 	9: 9:00~12:00, 13:00~28:00
 * 稼働パターンは、平日と休日の境でしか変更できない
 * 設備の稼働にはコストがかかり、設備ごと、平日/休日、稼働パターンごとに異なる
 * コストは非負整数で、パターン番号に対して単調非減少
 * パターンの切り替え回数は、設備ごとにC=2~8回まで
 * 	切り替えとは、i週目の平日(休日)とi+1週目の平日(休日)でパターンが異なることを指す 
 * 	@todo 平日と休日の間は好きに切り替えてよいということ？多分？
 */

/** @paragraph やること
 * 1. X週間・M台ぶんの稼働パターンを出力する
 * 2. ジャッジが、稼働パターン+注文データ(マスクデータ。なんでやねん)から計画を作成する
 * 3. ジャッジから、「計画の評価指標」が返却される
 * という手順を、E={50,100,300}回実行し、その中で最善の出力が採用される
 * なお、納期遅れが発生しないような稼働パターンが存在する。
 * @todo 全部9を出せば必ず遅れないということ？
 */

/** @paragraph 計画プログラムの挙動
 * 注文iの工程jを(i,j)と表記する
 * 計画の際は以下のルールがある
 * 	(i,j+1)の開始は(i,j)の開始以降
 * 	(i,j+1)の終了は(i,j)の終了以降
 * すなわち、連続する工程は異なる設備で同時に実行可能であるが、飛び越えて終了することはできない。
 */

/** @paragraph 計画のアルゴリズム（あとで）
 * 
 */

/** @paragraph ジャッジの返却内容
 * 計画の結果は以下の数値データで返却される。
 * 	1. スコア
 * 	2. 稼働パターンの切り替え回数が上限を超えた回数
 * 	3. 遅れた注文の数
 * 	4. 各設備、各週の負荷率（作業時間/稼働時間）
 * 	5. 各設備、各週に割り当てられている遅れ作業の個数
 */

/** @paragraph スコア計算
 * 稼働パターンの切り替え回数が上限を超える or 1つでも納期遅れすると0点
 * そうでない場合、まず「コスト」を求める
 * 	コスト=稼働コストの週当たりの平均（全稼働コストの和/X）の切り捨て
 * スコアは以下の計算式で与えられる。
 * 	round(10^9 * (10 - log10(コスト)))
 * @note 制約上、フル稼働時のコスト<10^10なので、フル稼働で正の得点が出る
 */

/** @paragraph テスト
 * 暫定テストは50ケース、システスは3000ケース
 */

struct Const {
private:
	Const() = default;

public:
	static const int ACT_PATTERN = 9;
	static inline int Week, Machine, Change, Interact;
	static inline vector<array<int, ACT_PATTERN>> cost_weekday, cost_holiday;

	static void Input() {
		cin >> Week >> Machine >> Change >> Interact;
		cost_weekday.resize(Machine);
		cost_holiday.resize(Machine);
		rep(i,Machine){
			rep(j,ACT_PATTERN){
				cin >> cost_weekday[i][j] >> cost_holiday[i][j];
			}
		}
	}
};

struct _Construct {
	_Construct(){
		Const::Input();
	}
	~_Construct(){

	}
} _construct;

struct Plan {
	vs plan;
	ll score = 0;
	int change_over, delay_count;
	vvd load_rate; vvi late_work;
	Plan() {
		plan.resize(Const::Machine, string(Const::Week*2, '1'));
		load_rate.resize(Const::Machine, vd(Const::Week));
		late_work.resize(Const::Machine, vi(Const::Week));
	}

	void getResult() {
		cin >> score >> change_over >> delay_count;
		rep(i,Const::Machine){
			rep(j,Const::Week){
				cin >> load_rate[i][j] >> late_work[i][j];
			}
		}

		// debug("RESULT:");
		// debug(score, change_over, delay_count);
		// debug(calcScore());
		// debug("kadouritu:");
		// debug(load_rate);
		// debug("okuresuu:");
		// debug(late_work);

	}

	void setWeekdayPlan(int machine, int week, int pattern) {
		plan[machine][week*2] = '0' + pattern;
	}
	void setHolidayPlan(int machine, int week, int pattern) {
		plan[machine][week*2+1] = '0' + pattern;
	}
	void setWeekPlan(int machine, int week, int pattern) {
		plan[machine][week*2] = plan[machine][week*2+1] = '0' + pattern;
	}
	void setAllPlan(int machine, int pattern) {
		plan[machine] = string(Const::Week*2, '0' + pattern);
	}

	ll calcScore(){
		ll costSum = 0;
		rep(i,Const::Machine){
			rep(j,Const::Week){
				costSum += Const::cost_weekday[i][plan[i][j*2]-'1'];
				costSum += Const::cost_holiday[i][plan[i][j*2+1]-'1'];
			}
		}
		return round(1e9 * (10 - log10(costSum/Const::Week)));
	}
};

struct PlanEditor {
	vi weekday_before, weekday_after, weekday_split;
	vi holiday_before, holiday_after, holiday_split;
	PlanEditor() {
		weekday_before.resize(Const::Machine,9);
		weekday_after.resize(Const::Machine,9);
		weekday_split.resize(Const::Machine,Const::Week);
		holiday_before.resize(Const::Machine,9);
		holiday_after.resize(Const::Machine,9);
		holiday_split.resize(Const::Machine,Const::Week);
	}

	void setPlan(Plan&plan){
		rep(i,Const::Machine){
			rep(j,Const::Week){
				if(j<weekday_split[i]){
					plan.setWeekdayPlan(i, j, weekday_before[i]);
				}else{
					plan.setWeekdayPlan(i, j, weekday_after[i]);
				}
				if(j<holiday_split[i]){
					plan.setHolidayPlan(i, j, holiday_before[i]);
				}else{
					plan.setHolidayPlan(i, j, holiday_after[i]);
				}
			}
		}
	}

	static PlanEditor oneValue(int weekday, int holiday){
		PlanEditor pe;
		rep(i,Const::Machine){
			pe.weekday_before[i] = pe.weekday_after[i] = weekday;
			pe.holiday_before[i] = pe.holiday_after[i] = holiday;
		}
		return pe;
	}

	bool decrementMachinePattern(int machine){
		if(weekday_before[machine]<=2) return false;
		weekday_before[machine]--;
		weekday_after[machine]--;
		holiday_before[machine]--;
		holiday_after[machine]--;
		return true;
	}

	bool decrementWeekdaySplit(int machine){
		if(weekday_split[machine]==0) return false;
		weekday_split[machine]--;
		return true;
	}

	bool decrementHolidaySplit(int machine){
		if(holiday_split[machine]==0) return false;
		holiday_split[machine]--;
		return true;
	}

	static PlanEditor createFromPlan(Plan&plan){
		PlanEditor pe;
		rep(i,Const::Machine){
			pe.weekday_before[i] = plan.plan[i].front()-'0';
			pe.weekday_after[i] = plan.plan[i][Const::Week*2-2]-'0';
			pe.holiday_before[i] = plan.plan[i][1]-'0';
			pe.holiday_after[i] = plan.plan[i][Const::Week*2-1]-'0';

			rep(j,1,Const::Week){// 0!=1 ならi
				if(plan.plan[i][j*2-2]!=plan.plan[i][j*2]){
					pe.weekday_split[i] = j;
				}
				if(plan.plan[i][j*2-1]!=plan.plan[i][j*2+1]){
					pe.holiday_split[i] = j;
				}
			}
		}
		return pe;
	}

};

struct SolverInterface {
	int turn = 0;
	vector<Plan> plans;
	SolverInterface() {

	}

	void nextTurn(){
		turn++;
	}

	virtual int planning() = 0;

	void output() {
		rep(i,Const::Machine){
			cout << plans[turn].plan[i] << '\n';
		}
		cout<<flush;
		plans[turn].getResult();
	}

	virtual bool isFinish() {
		return false;
	}

	virtual void takenOver(SolverInterface* prev){
		turn = prev->turn;
		plans = prev->plans;
	}

	Plan getBestPlan(){
		ll bestScore=0;
		Plan& bestPlan = plans.front();
		for(auto&plan: plans){
			if(chmax(bestScore, plan.score)){
				bestPlan = plan;
			}
		}
		return bestPlan;
	}
};


struct InitializeSolver : public SolverInterface {
	InitializeSolver(): SolverInterface() {}

	int ok=9, ng=4;

	int planning() {
		plans.emplace_back();
		int mid = (ok+ng)/2;
		auto editor = PlanEditor::oneValue(mid, mid);
		editor.setPlan(plans[turn]);
		return 0;
	}
	
	bool isFinish() override{
		if(plans[turn].score > 0){
			ok = (ok+ng)/2;
		}else{
			ng = (ok+ng)/2;
		}
		if(abs(ok-ng)<=1){
			auto editor = PlanEditor::oneValue(ok, ok);
			editor.setPlan(plans[turn]);
			return true;
		}
		return SolverInterface::isFinish();
	}
};


struct FinalizeSolver : public SolverInterface {
	FinalizeSolver(): SolverInterface() {
		uncanny.resize(Const::Machine, vi(Const::Week*2, 0));
	}

	bool continuous = true;
	int tgti, tgtj;
	vvi uncanny;

	int planning() {
		if(!continuous){
			uncanny = vvi(Const::Machine, vi(Const::Week*2, 0));
		}

		Plan bestPlan = getBestPlan();
		vector<tuple<ll, float, int, int, char>> rates;
		vi changed(Const::Machine,0);
		rep(i,Const::Machine){
			rep(j,Const::Week-1){
				if(bestPlan.plan[i][j*2]!=bestPlan.plan[i][j*2+2]){
					changed[i]++;
				}
				if(bestPlan.plan[i][j*2+1]!=bestPlan.plan[i][j*2+3]){
					changed[i]++;
				}
			}
			rep(j,Const::Week){
				if(bestPlan.load_rate[i][j]!=0){
					if(uncanny[i][j*2+1]==0){
						char holiday = bestPlan.plan[i][j*2+1];
						rep(c,max((char)(holiday-1), '1'), holiday){
							int require = 0;
							if(j!=0 and bestPlan.plan[i][j*2-1]!=holiday){
								require--;
							}
							if(j+1!=Const::Week and bestPlan.plan[i][j*2+3]!=holiday){
								require--;
							}
							if(j!=0 and bestPlan.plan[i][j*2-1]!=c){
								require++;
							}
							if(j+1!=Const::Week and bestPlan.plan[i][j*2+3]!=c){
								require++;
							}
							if(changed[i] + require > Const::Change) continue;
							ll increasedScore = Const::cost_holiday[i][holiday+1-'1'] - Const::cost_holiday[i][c-'1'];
							// debug(i,j,increasedScore);
							rates.emplace_back(increasedScore, -bestPlan.load_rate[i][j],i,j*2+1,c);
						}
					}
					if(uncanny[i][j*2]==0){
						char weekday = bestPlan.plan[i][j*2];
						rep(c,max((char)(weekday-1), '1'), weekday){
							int require = 0;
							if(j!=0 and bestPlan.plan[i][j*2-2]!=weekday){
								require--;
							}
							if(j+1!=Const::Week and bestPlan.plan[i][j*2+2]!=weekday){
								require--;
							}
							if(j!=0 and bestPlan.plan[i][j*2-2]!=c){
								require++;
							}
							if(j+1!=Const::Week and bestPlan.plan[i][j*2+2]!=c){
								require++;
							}
							if(changed[i] + require > Const::Change) continue;
							ll increasedScore = Const::cost_weekday[i][weekday+1-'1'] - Const::cost_weekday[i][c-'1'];
							// debug(i,j,increasedScore);
							rates.emplace_back(increasedScore, -bestPlan.load_rate[i][j],i,j*2,c);
						}
					}

				}
			}
		}
		if(!rates.empty()){
			sort(rall(rates));
			auto [_, __, i, j, c] = rates.front();
			tgti = i, tgtj = j;
			bestPlan.plan[i][j] = c;
		}else{
			continuous = false;
		}

		plans.push_back(bestPlan);
		return 0;
	}

	bool isFinish() override{
		if(continuous){
			if(plans[turn].score > 0){
				debug("!! succeeded waruagaki", turn, tgti, tgtj, plans[turn].score);
				// if(tgtj-2>=0) uncanny[tgti][tgtj-2]=0;
				// if(tgtj+2<Const::Week) uncanny[tgti][tgtj+2]=0;
			}else{
				uncanny[tgti][tgtj]++;
				debug("?? failed waruagaki", turn, tgti, tgtj);
			}
		}
		return SolverInterface::isFinish();
	}

	void takenOver(SolverInterface* prev) override {
		SolverInterface::takenOver(prev);
	}
};

struct OptimizeMachineSolver : public SolverInterface {
	OptimizeMachineSolver(): SolverInterface() {
		ok = vi(Const::Machine, 9);
		ng = vi(Const::Machine, 1);
	}

	PlanEditor editor;
	int target = 0;
	vi ok, ng;

	int planning() {
		target = -1;
		ll maxCost= 0;
		rep(i,Const::Machine){
			if(abs(ok[i]-ng[i])<=1) continue;
			ll currentCost = Const::cost_weekday[i][ok[i]-1] + Const::cost_holiday[i][ok[i]-1];
			if(chmax(maxCost, currentCost)){
				target = i;
			}
		}

		int mid=(ok[target]+ng[target])/2;
		editor.weekday_before[target] = mid;
		editor.holiday_before[target] = mid;

		auto& plan = plans.emplace_back();
		editor.setPlan(plan);
		return 0;
	}

	int remainMachine = Const::Machine;
	bool isFinish() override{
		if(plans[turn].score > 0){
			ok[target] = (ok[target]+ng[target])/2;
		}else{
			ng[target] = (ok[target]+ng[target])/2;
		}
		if(abs(ok[target]-ng[target])<=1){
			editor.weekday_before[target] = ok[target];
			editor.holiday_before[target] = ok[target];
			editor.setPlan(plans.back());
			remainMachine--;
			if(remainMachine==0){
				return true;
			}
		}
		return SolverInterface::isFinish();
	}

	void takenOver(SolverInterface* prev) override {
		SolverInterface::takenOver(prev);
		int pattern = plans.back().plan.back()[0] - '0';
		editor = PlanEditor::oneValue(pattern, pattern);
		rep(i,Const::Machine){
			ok[i] = pattern;
		}
	}
};


struct OptimizeWeekSolver : public SolverInterface {
	OptimizeWeekSolver(): SolverInterface() {}

	PlanEditor editor;
	bool checked = false;

	int planning() {
		auto& plan = plans.emplace_back();
		editor.setPlan(plan);
		return 0;
	}

	bool isFinish() override{
		if(checked){
			return true;
		}

		checked = true;
		rep(i, Const::Machine){
			editor.weekday_after[i] = editor.holiday_after[i] = 1;
			editor.weekday_split[i] = editor.holiday_split[i] = Const::Week;
			auto& rate = plans.back().load_rate[i];
			rep(j, Const::Week-1){
				if(rate[j]!=0 and rate[j+1]==0){
					editor.weekday_split[i] = j+1;
					editor.holiday_split[i] = j+1;
					break;
				}
			}
		}
		return SolverInterface::isFinish();
	}

	void takenOver(SolverInterface* prev) override {
		SolverInterface::takenOver(prev);
		Plan bestPlan = getBestPlan();
		editor = PlanEditor::createFromPlan(bestPlan);
	}
};



struct OptimizeWeekdaySolver : public SolverInterface {
	OptimizeWeekdaySolver(): SolverInterface() {}

	PlanEditor editor;
	int target = Const::Machine - 1;
	int ok = Const::Week, ng = 2;

	int planning() {
		int mid=(ok+ng)/2;
		editor.weekday_split[target] = mid;
		// debug("!!", target, editor.weekday_before[target], editor.weekday_after[target], editor.weekday_split[target]);

		auto& plan = plans.emplace_back();
		editor.setPlan(plan);

		return 0;
	}

	bool isFinish() override{
		if(plans[turn].score > 0){
			ok = (ok+ng)/2;
		}else{
			ng = (ok+ng)/2;
		}
		if(abs(ok-ng)<=1){
			editor.weekday_split[target] = ok;
			editor.setPlan(plans.back());
			target--;
			if(target<0){
				return true;
			}
			ok = editor.weekday_split[target];
			ng = -1;
		}
		return SolverInterface::isFinish();
	}

	void takenOver(SolverInterface* prev) override {
		SolverInterface::takenOver(prev);
		Plan bestPlan = getBestPlan();

		editor = PlanEditor::createFromPlan(bestPlan);
		rep(i, Const::Machine){
			editor.weekday_after[i] = 1;
		}
		ok=editor.weekday_split.back();
	}
};


struct OptimizeHolidaySolver : public SolverInterface {
	OptimizeHolidaySolver(): SolverInterface() {}

	PlanEditor editor;
	int target = Const::Machine - 1;
	int ok = Const::Week, ng = -1;

	int planning() {
		int mid=(ok+ng)/2;
		editor.holiday_split[target] = mid;
		// debug("!!", target, editor.weekday_before[target], editor.weekday_after[target], editor.weekday_split[target]);

		auto& plan = plans.emplace_back();
		editor.setPlan(plan);

		return 0;
	}

	bool isFinish() override{
		if(plans[turn].score > 0){
			ok = (ok+ng)/2;
		}else{
			ng = (ok+ng)/2;
		}
		if(abs(ok-ng)<=1){
			editor.holiday_split[target] = ok;
			editor.setPlan(plans.back());
			target--;
			if(target<0){
				return true;
			}
			ok = editor.holiday_split[target];
			ng = -1;
		}
		return SolverInterface::isFinish();
	}

	void takenOver(SolverInterface* prev) override {
		SolverInterface::takenOver(prev);
		Plan bestPlan = getBestPlan();

		editor = PlanEditor::createFromPlan(bestPlan);
		rep(i, Const::Machine){
			editor.holiday_after[i] = 1;
		}

		ok = editor.holiday_split.back();
	}
};

int main() {
	debug("start", Const::Week, Const::Machine, Const::Change, Const::Interact);
	deque<SolverInterface*> solvers;
	solvers.push_back(new InitializeSolver());
	solvers.push_back(new OptimizeMachineSolver());
	solvers.push_back(new OptimizeWeekSolver());
	if(Const::Interact==300)solvers.push_back(new OptimizeHolidaySolver());
	if(Const::Interact==300) solvers.push_back(new OptimizeWeekdaySolver());
	solvers.push_back(new FinalizeSolver());

	rep(i,Const::Interact){
		auto&solver = solvers[0];
		
		if(solver->planning() > 0){
			// 計画失敗
			solvers[1]->takenOver(solvers[0]);
			solvers.pop_front();
			debug("Change algorithm", "turn :",solver->turn, "remain", solvers.size());
			for(auto&s:solver->getBestPlan().plan){
				debug(s);
			}
			debug(solver->getBestPlan().score);
			continue;
		}

		solver->output();

		if(solver->isFinish()){
			// 計画完了
			solvers[1]->takenOver(solvers[0]);
			solvers.pop_front();
			solver = solvers[0];
			debug("Change algorithm", "turn :",solver->turn, "remain", solvers.size());
			for(auto&s:solver->getBestPlan().plan){
				debug(s);
			}
			debug(solver->getBestPlan().score);
		}
		
		solver->nextTurn();
	}
}
