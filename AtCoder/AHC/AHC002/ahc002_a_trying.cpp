#pragma region Perfect Template
#pragma region Unsecured Optimization
#pragma GCC target("avx")
// #pragma GCC optimize("O3,inline,omit-frame-pointer,no-asynchronous-unwind-tables,fast-math")
#pragma GCC optimize("unroll-loops")
#pragma endregion

#pragma region Include Headers
#if defined(ONLINE_JUDGE) || defined(_DEBUG)
#include <atcoder/all>
using namespace atcoder;
#endif
#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;

void Main();
int main(){cin.tie(nullptr);ios::sync_with_stdio(false);Main();return 0;}
#pragma endregion

#pragma region Additional Type Definition
using ll=long long;
using ld=long double;
using ull=unsigned long long;
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
template<class K> using IndexedSet=__gnu_pbds::tree<K,__gnu_pbds::null_type,less<K>,__gnu_pbds::rb_tree_tag,__gnu_pbds::tree_order_statistics_node_update>;
template<class K> using HashSet=__gnu_pbds::gp_hash_table<K,__gnu_pbds::null_type>;
template<class K,class V> using IndexedMap=__gnu_pbds::tree<K,V,less<K>,__gnu_pbds::rb_tree_tag,__gnu_pbds::tree_order_statistics_node_update>;
template<class K,class V> using HashMap=__gnu_pbds::gp_hash_table<K,V>;
#pragma endregion

#pragma region Macros
#define all(a) a.begin(),a.end()
#define rall(a) a.rbegin(),a.rend()
#define loop(q) __loop(q, __LINE__)
#define __loop(q,l) __loop2(q,l)
#define __loop2(q,l) rep(_lp ## l,q)
#define rep(i,n) range(i,0,n)
#define rrep(i,n) rrange(i,0,n)
#define range(i,a,n) for(ll i=((ll)a);i<((ll)n);++i)
#define rrange(i,a,n) for(ll i=((ll)n-1);i>=((ll)a);--i)
#define repsq(i,n) for(ll i=0;i*i<=n;++i)
#define each(v,a) for(auto v:a)
#define eachref(v,a) for(auto&v:a)
#define fcout(a) cout<<setprecision(a)<<fixed
#pragma endregion

#pragma region Constants
constexpr ll LINF=1ll<<60;
constexpr int INF=1<<30;
constexpr double EPS=(1e-9);
constexpr ll MOD=1000000007ll;
constexpr long double PI=3.14159265358979323846;
#pragma endregion

#pragma region Output Assist
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
#pragma endregion

#pragma region Input Assist
template<class S>auto&operator>>(istream&is,vector<S>&t){for(S&a:t)cin>>a;return is;}
template<typename...S>void geta_(S&...s){((cin>>s),...);}
#define geta(t,...) t __VA_ARGS__;geta_(__VA_ARGS__)
template<class T,class...Args>auto vec(T x,int arg,Args...args){if constexpr(sizeof...(args)==0)return vector(arg,x);else return vector(arg,vec(x,args...));}
#define getv(a,...) auto a=vec(__VA_ARGS__);cin>>a
#pragma endregion

#pragma region Utilities
template<class T>constexpr bool chmax(T&a,T b){return a<b?a=b,1:0;}
template<class T>constexpr bool chmin(T&a,T b){return a>b?a=b,1:0;}
template<class S>S sum(vector<S>&a){return accumulate(all(a),S());}
template<class S>S max(vector<S>&a){return *max_element(all(a));}
template<class S>S min(vector<S>&a){return *min_element(all(a));}
template<class T> pair<int,T> getMaxAndIndex(vector<T> a){
	int p=-1; T v=numeric_limits<T>::min();
	rep(i,a.size())if(chmax(v,a[i]))p=i;
	return {p,v};
}
#pragma endregion
#pragma endregion

// ここにライブラリを貼る
// regionのfoldは[Ctrl+K] => [Ctrl+8] expandは9
#pragma region Additional Libraries
class Random{
	unsigned y;
	constexpr unsigned next(){return y^=(y^=(y^=y<<13)>>17)<<5;}
public:
	constexpr Random(const bool&isDeterministic):y(isDeterministic?2463534242:chrono::system_clock::now().time_since_epoch().count()){}
	constexpr int operator()(int a,int b){return next()%(b-a)+a;}
	constexpr ll operator()(ll a,ll b){return (((ull)next())<<32|next())%(b-a)+a;}
	constexpr double operator()(double a,double b){return (b-a)*next()/4294967296.0+a;}
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
	Timer(uint64_t _limit): start(getClocks()),limit(start+_limit*ClocksPerMsec) {}
	uint64_t get() const{return (getClocks()-start)/ClocksPerMsec;}
	operator bool()const{return getClocks()<limit;}
};
void wait(const int&msec){Timer tm(msec); while(tm);}


#pragma endregion
struct Cell{
	int y,x,p;
	bool v=false,v2=false;
	Cell*o;
};
struct Stage{
	const int h=50, w=50;
	const int dy[4]={1,0,-1,0}, dx[4]={0,1,0,-1};
	const string moveStr="DRUL";
	int sy,sx;
	vector<Cell> cells;
	vvi pairs;
	void get(){
		cin>>sy>>sx;
		pairs=vvi(h,vi(w));
		cin>>pairs;
		cells.resize(h*w);

		rep(i,h)rep(j,w){
			cin>>cells[i*w+j].p;
		}
		init();
	}
	void init(){
		rereference();
		cy=sy,cx=sx;
		score=cells[sy*w+sx].p;
		cells[sy*w+sx].v=true;
		engine=mt19937(Random(0,INF));
		pospath.clear();
		pospath.emplace_back(sy*w+sx);
	}
	void rereference(){
		rep(i,h)rep(j,w){
			cells[i*w+j].y=i;
			cells[i*w+j].x=j;
			rep(k,4){
				if(i+dy[k]<0 or i+dy[k]>=h or j+dx[k]<0 or j+dx[k]>=w)continue;
				if(pairs[i+dy[k]][j+dx[k]]==pairs[i][j]){
					cells[i*w+j].o=&cells[(i+dy[k])*w+j+dx[k]];
					break;
				}
				cells[i*w+j].o=&cells[i*w+j];
			}
		}
	}

	// score
	int score=0,cy,cx;
	vi path,pospath;
	mt19937 engine;
	array<int,4> dir={0,1,2,3};
	int moveCnt=0,removeCnt=0;
	int cellScore(int y, int x){
		int v=0;
		rep(k,4){
			int ny=y+dy[k], nx=x+dx[k];
			if(ny<0 or ny>=h or nx<0 or nx>=w){
				// 壁
				v+=-1000;
				continue;
			}
			if(cells[ny*w+nx].v or cells[ny*w+nx].o->v){
				// 行けない
				v-=1000;
			}

			if(!cells[ny*w+nx].v and cells[ny*w+nx].v2){
				// 行けはするが過去の探索で行ったことがある
			}
		}
		return v;
	}
	int randomWalk(){
		shuffle(all(dir),engine);
		// dump(dir);
		for(int&k:dir){
			int ny=cy+dy[k], nx=cx+dx[k];
			if(ny<0 or ny>=h or nx<0 or nx>=w)continue;
			if(cells[ny*w+nx].v or cells[ny*w+nx].v2 or cells[ny*w+nx].o->v)continue;
			return k;
		}
		return -1;
	}
	void move(int k){
		moveCnt++;
		path.emplace_back(k);
		cy+=dy[k],cx+=dx[k];
		score+=cells[cy*w+cx].p;
		cells[cy*w+cx].v=true;
		cells[cy*w+cx].v2=true;
		pospath.emplace_back(cy*w+cx);
	}
	void remove(){
		if(path.empty())return;
		removeCnt++;
		int k=path.back();
		path.pop_back();
		pospath.pop_back();
		score-=cells[cy*w+cx].p;
		cells[cy*w+cx].v=false;
		cy-=dy[k],cx-=dx[k];
	}
	void out(){
		string ans;
		each(i,path)ans+=moveStr[i];
		puta(ans);
	}
	Stage DeepCopy(){
		Stage stg;
		stg.sy=sy;
		stg.sx=sx;
		stg.cy=cy;
		stg.cx=cx;
		stg.pairs=pairs;
		stg.cells=cells;
		stg.score=score;
		stg.path=path;
		stg.pospath=pospath;
		stg.engine=mt19937(Random(0,INF));
		stg.dir={0,1,2,3};
		stg.moveCnt=moveCnt;
		stg.removeCnt=removeCnt;
		return stg;
	}
	void SetOther(Stage&stg){
		sy=stg.sy;
		sx=stg.sx;
		cy=stg.cy;
		cx=stg.cx;
		pairs=stg.pairs;
		cells=stg.cells;
		score=stg.score;
		path=stg.path;
		pospath=stg.pospath;
		engine=mt19937(Random(0,INF));
		dir={0,1,2,3};
		moveCnt=stg.moveCnt;
		removeCnt=stg.removeCnt;
	}

	// ランダムな1箇所を切り開いて、そこを拡張できるか判定
	void Optimize(Timer timer){
		int len=path.size();
		int index=0;
		do{
			index=Random(0,len);
			int l=pospath[index], r=pospath[index+1];
			if(path[index]%2==0){//縦移動
				if(cells[l].x>0){//左側が空いているか
					if(!cells[l-1].v and !cells[l-1].o->v and !cells[r-1].v and !cells[r-1].o->v){
						Stage stage=DeepCopy();
						stage.rereference();
						if(stage.challenge(index, 3, l-1, r)){
							SetOther(stage);
							break;
						}
					}
				}
				if(cells[l].x<w-1){//右側が空いているか
					// dump("Start");
					// dump(cells[l+1].o->p,cells[r+1].o->p);
					// dump(!cells[l+1].v , !cells[l+1].o->v , !cells[r+1].v , !cells[r+1].o->v);
					if(!cells[l+1].v and !cells[l+1].o->v and !cells[r+1].v and !cells[r+1].o->v){
						Stage stage=DeepCopy();
						stage.rereference();
						if(stage.challenge(index, 1, l+1, r)){
							SetOther(stage);
							break;
						}
					}
					// dump("Fin");
				}
			}else{// 横
				if(cells[l].y>0){//上側が空いているか
					if(!cells[l-w].v and !cells[l-w].o->v and !cells[r-w].v and !cells[r-w].o->v){
						Stage stage=DeepCopy();
						stage.rereference();
						if(stage.challenge(index, 2, l-w, r)){
							SetOther(stage);
							break;
						}
					}
				}
				if(cells[l].y<h-1){//上側が空いているか
					if(!cells[l+w].v and !cells[l+w].o->v and !cells[r+w].v and !cells[r+w].o->v){
						Stage stage=DeepCopy();
						stage.rereference();
						if(stage.challenge(index, 0, l+w, r)){
							SetOther(stage);
							break;
						}
					}
				}
			}
		}while(timer);
	}

	bool challenge(int p, int d, int cur, int tgt){
		// p手目の処理をmoveStr[d]に変更して、curからtgtまでやってみる
		dump(p,d,cur,tgt);
		dump(cells[cur].v);
		vi tmp=path;
		path[p]=d;
		pospath[p+1]=cur;
		cells[cur].v=cells[cur].v2=true;
		vi after,afterpos;
		int z=path.size();
		range(i,p+1,z){
			after.emplace_back(path.back());
			path.pop_back();
		}
		z=pospath.size();
		range(i,p+2,z){
			afterpos.emplace_back(pospath.back());
			pospath.pop_back();
		}
		dump(path.back());
		dump(after);

		cy=cur/w, cx=cur%w;
		while(true){
			if(int k=randomWalk(); k>=0){
				move(k);
				if(cy*w+cx==tgt){
					while(after.size()>0){
						path.emplace_back(after.back());
						after.pop_back();
					}
					dump(pospath);
					while(afterpos.size()>0){
						pospath.emplace_back(afterpos.back());
						afterpos.pop_back();
					}
					puta(tmp);
					puta(pospath);
					dump("success");
					return true;
				}
			}else{
				if(pospath.back()==cur)break;
				remove();
				if(pospath.back()==cur)break;
			}
		}
		return false;
	}
};

Stage InitialResult(const int limit){
	Timer timer(limit);
	Stage defaultStage,result;
	defaultStage.get();
	int challenge=0;

	while(timer){
		Stage stage=defaultStage.DeepCopy();
		stage.rereference();
		challenge++;
		while(timer){
			if(int k=stage.randomWalk(); k>=0){
				stage.move(k);
				if(chmax(result.score, stage.score)){
					result.path=stage.path;
					result.pospath=stage.pospath;
				}
			}else{
				if(stage.path.size()==0)break;
				stage.remove();
			}
		}
	}
	defaultStage.path=result.path;
	defaultStage.pospath=result.pospath;
	defaultStage.score=result.score;
	dump(challenge);
	return defaultStage;
}

void Main(){
	Timer timer(1970);
	const int initialLimit=200;
	Stage result = InitialResult(initialLimit);
	#ifdef _DEBUG
	{
		puta(result.score);
		result.out();
		puta(result.path.size(),result.pospath.size());
		puta(result.path);
		puta(result.pospath);
		puta(result.cells.size());
	}
	#endif

	while(timer){
		result.Optimize(timer);
		break;
	}
	result.out();
}
