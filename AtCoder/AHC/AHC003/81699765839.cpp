#pragma region Perfect Template
#pragma region Unsecured Optimization
// #pragma GCC target("avx")
// #pragma GCC optimize("O3,inline,omit-frame-pointer,no-asynchronous-unwind-tables,fast-math")
// #pragma GCC optimize("unroll-loops")
#ifdef _DEBUG
#define _GLIBCXX_DEBUG 1
#endif
#pragma endregion

#pragma region Include Headers
#if defined(EVAL) || defined(ONLINE_JUDGE) || defined(_DEBUG)
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
template<class T>T gcd(vector<T> v){return accumulate(all(v),T(),gcd<T,T>);}
template<class T> pair<int,T> getMaxAndIndex(vector<T> a){
	int p=-1; T v=numeric_limits<T>::min();
	rep(i,a.size())if(chmax(v,a[i]))p=i;
	return {p,v};
}
#pragma endregion
#pragma endregion

class Random {
	unsigned y;
	constexpr unsigned next(){return y^=(y^=(y^=y<<13)>>17)<<5;}
public:
	typedef ll result_type;
	constexpr result_type operator()(){return operator()((ll)min(),(ll)max());}
	static constexpr result_type max(){return numeric_limits<result_type>::max();}
	static constexpr result_type min(){return 0;}

	constexpr Random(const bool&isDeterministic):y(isDeterministic?2463534242:chrono::system_clock::now().time_since_epoch().count()){}
	constexpr int operator()(int a,int b){return next()%(b-a)+a;}
	constexpr ll operator()(ll a,ll b){return (((ull)next())<<32|next())%(b-a)+a;}
	constexpr double operator()(double a,double b){return (b-a)*next()/4294967296.0+a;}
} Random(0);

constexpr int F=30;
struct ScoreCalculator{
	constexpr static int Q=1000;
	static int h[F-1][F];
	static int w[F][F-1];
	static vi hav,wav;
	static int si[Q],sj[Q],ti[Q],tj[Q],a[Q];
	static float e[Q];
	static float p998[Q];
	static int length[Q];

	ScoreCalculator(){
		#ifdef _DEBUG
		rep(i,F)rep(j,F-1)cin>>w[i][j];
		rep(i,F-1)rep(j,F)cin>>h[i][j];
		rep(i,Q)cin>>si[i]>>sj[i]>>ti[i]>>tj[i]>>a[i]>>e[i];
		hav.resize(F,0);
		wav.resize(F,0);
		rep(i,F){
			rep(j,F-1){
				hav[i]+=h[j][i];
				wav[i]+=w[i][j];
			}
		}
		rep(i,F)wav[i]/=F-1;
		rep(i,F)hav[i]/=F-1;
		#else
		rep(i,F)rep(j,F-1)h[i][j]=-1;
		rep(i,F-1)rep(j,F)w[i][j]=-1;
		#endif
		p998[0]=1;
		rep(i,Q-1) p998[i+1]=p998[i]*0.998;
	}
	static tuple<int,int,int,int> getQuery(int i){
		#ifndef _DEBUG
		cin>>si[i]>>sj[i]>>ti[i]>>tj[i];
		#endif
		return make_tuple(si[i],sj[i],ti[i],tj[i]);
	}
	static int calc(int i, string path){
		float s=0;
		#ifdef _DEBUG
		cout<<path<<endl;
		int pi=si[i], pj=sj[i];
		for(char&c:path){
			switch(c){
				case 'U':
					pi--;
					s+=h[pi][pj];
					break;
				case 'D':
					s+=h[pi][pj];
					pi++;
					break;
				case 'L':
					pj--;
					s+=w[pi][pj];
					break;
				case 'R':
				default:
					s+=w[pi][pj];
					pj++;
					break;				
			}
			// dump(pi,pj,s);
			if(pi<0 or pj<0 or pi>=F or pj>=F) return -1;
		}
		if(pi!=ti[i] or pj!=tj[i]) return -1;
		length[i]=s;
		// dump(pi,pj,s);
		s*=e[i];
		#else
		cout<<path<<endl;
		cin>>s;
		#endif
		return round(s);
		// return round(2312311 * p998[Q-1-i] * a[i] / s);
	}
};
int ScoreCalculator::h[F-1][F];
int ScoreCalculator::w[F][F-1];
vi ScoreCalculator::hav;
vi ScoreCalculator::wav;
int ScoreCalculator::si[Q];
int ScoreCalculator::sj[Q];
int ScoreCalculator::ti[Q];
int ScoreCalculator::tj[Q];
int ScoreCalculator::a[Q];
float ScoreCalculator::e[Q];
float ScoreCalculator::p998[Q];
int ScoreCalculator::length[Q];

struct UnionFind{
	vl par,dist;
	UnionFind(int x){par.assign(x,-1); dist.assign(x,0);}
	ll find(ll x){return par[x]<0?x:find(par[x]);}
	ll depth(ll x){return par[x]<0?0:depth(par[x])+dist[x];}
	bool same(ll x,ll y){return find(x)==find(y);}
	ll size(ll x){return -par[find(x)];}
	ll diff(ll x,ll y){return same(x,y)?depth(x)-depth(y):LINF;}
	bool unite(ll x,ll y,ll k=0){
		k+=depth(y); k-=depth(x); k=-k;
		x=find(x); y=find(y);
		if(x==y)return false;
		if(size(x)<size(y)){swap(x,y);k=-k;}
		par[x]+=par[y]; par[y]=x; dist[y]=k;
		return true;
	}
};
struct Analyser{
	bool decided=false;
	int decidedCount=0;
	UnionFind uf;
	int edge[F][F][3];
	vi dch,dcw,adch,adcw;
	Analyser() : uf(F*2), dch(F,-1), dcw(F,-1), adch(F,-1), adcw(F,-1){
		rep(i,F)rep(j,F)edge[i][j][2]=-1;
	}
	// void decide(int hi, int hx, int wi, int wx, int v){
	// 	queue<int> q;
	// 	q.push(hi);
	// 	vi ch=dch,cw=dcw;
	// 	ch[hi]=2352;
	// 	while(!q.empty()){
	// 		int p=q.front();
	// 		q.pop();
	// 		if(p==wi+F){
	// 			dump("!",cw[p-F],"(ans:",ScoreCalculator::wav[wi],")");
	// 			return;
	// 		}
	// 		if(p>=F){
	// 			p-=F;
	// 			rep(i,F)if(edge[i][p][2]!=-1){
	// 				if(ch[i]==-1){
	// 					ch[i]=1.0*(edge[i][p][2]-cw[p]*edge[i][p][1])/edge[i][p][0];
	// 					q.push(i);
	// 				}
	// 			}
	// 		}else{
	// 			rep(i,F)if(edge[p][i][2]!=-1){
	// 				if(cw[i]==-1){
	// 					cw[i]=1.0*(edge[p][i][2]-ch[p]*edge[p][i][0])/edge[p][i][1];
	// 					q.push(i+F);
	// 				}
	// 			}
	// 		}
	// 	}
	// }

	void bfs(int i, int v=-1){
		queue<int> q;
		q.push(i);
		vi ch=adch,cw=adcw;
		if(v!=-1){
			(i>=F?ch:cw)[i%F]=v;
		}

		while(!q.empty()){
			int p=q.front();
			q.pop();
			if(p>=F){
				p-=F;
				rep(i,F)if(edge[i][p][2]!=-1){
					if(ch[i]==-1){
						ch[i]=1.0*(edge[i][p][2]/Random(0.9,0.9)-cw[p]*edge[i][p][1])/edge[i][p][0];
						ch[i]=clamp(ch[i],1950,8150);
						q.push(i);
					}
				}
			}else{
				rep(i,F)if(edge[p][i][2]!=-1){
					if(cw[i]==-1){
						cw[i]=1.0*(edge[p][i][2]/Random(0.9,0.9)-ch[p]*edge[p][i][0])/edge[p][i][1];
						cw[i]=clamp(cw[i],1950,8150);
						q.push(i+F);
					}
				}
			}
		}
		rep(i,F){
			update(i,ch[i]);
			update(i+F,cw[i]);
		}
	}

	void update(int i, int v){
		if(v==-1)return;
		v=clamp(v,1950,8150);
		if(i>=F){
			if(dcw[i-F]==-1){
				dcw[i-F]=v;
				decidedCount++;
			} else dcw[i-F]=(dcw[i-F]+v)/2;
		}else{
			if(dch[i]==-1){
				dch[i]=v;
				decidedCount++;
			} else dch[i]=(dch[i]+v)/2;
		}
		decided=decidedCount==F*2;
	}

	bool add(int hi, int hx, int wi, int wx, int v){
		if(hx==0){
			update(wi+F, v/wx);
			adcw[wi]=v/wx;
			bfs(wi+F);
			return false;
		}
		if(wx==0){
			update(hi, v/hx);
			adch[hi]=v/hx;
			bfs(hi);
			return false;
		}

		if(!uf.unite(hi, wi+F)){
			return true;
		}else{
			edge[hi][wi][0]=hx;
			edge[hi][wi][1]=wx;
			edge[hi][wi][2]=v;
			rep(i,F){
				if(dch[hi]==-1 and dch[i]!=-1 and uf.same(i,hi)){
					bfs(i,dch[i]);
				}
				if(dch[wi]==-1 and dcw[i]!=-1 and uf.same(i+F,wi)){
					bfs(i+F,dcw[i]);
				}
			}
		}
		rep(i,F)if(adch[i]!=-1)bfs(i);
		rep(i,F)if(adcw[i]!=-1)bfs(i+F);
		rep(100){
			rep(i,F)if(adch[i]!=-1)bfs(i);
			rep(i,F)if(adcw[i]!=-1)bfs(i+F);
		}
		return false;
	}
	int getLR(int h){ return dcw[h]==-1?5000:dcw[h]; }
	int getUD(int w){ return dch[w]==-1?5000:dch[w]; }
};

string solve(int si, int sj, int ti, int tj, bool rev=false){
	string path="";
	if(rev){
		if(si<ti)rep(ti-si)path+='D';
		if(si>ti)rep(si-ti)path+='U';
		if(sj<tj)rep(tj-sj)path+='R';
		if(sj>tj)rep(sj-tj)path+='L';
	}else{
		if(sj<tj)rep(tj-sj)path+='R';
		if(sj>tj)rep(sj-tj)path+='L';
		if(si<ti)rep(ti-si)path+='D';
		if(si>ti)rep(si-ti)path+='U';
	}
	return path;
}

Analyser analyser;
string solve2(int si, int sj, int ti, int tj){
	int i=si, di=(ti-si>=0)?1:-1, dj=(tj-sj>=0)?1:-1;
	// puta(si,sj,ti,tj);
	auto ret=vec(INF,F,F);
	auto path=vec(""s,F,F);
	ret[si][sj]=0;
	do{
		int j=sj;
		do{
			// puta(i,j,ret[i][j],path[i][j]);
			if(i!=ti){
				if(chmin(ret[i+di][j],ret[i][j]+analyser.getUD(j))){
					path[i+di][j]=path[i][j]+((di==1)?'D':'U');
				}
			}
			if(j!=tj){
				if(chmin(ret[i][j+dj],ret[i][j]+analyser.getLR(i))){
					path[i][j+dj]=path[i][j]+((dj==1)?'R':'L');
				}
			}
			j+=dj;
		}while(j!=tj+dj);
		i+=di;
	}while(i!=ti+di);
	return path[ti][tj];
}

void Main(){
	ScoreCalculator();
	rep(k,ScoreCalculator::Q){
		auto[si,sj,ti,tj]=ScoreCalculator::getQuery(k);
		if(analyser.decided){
			string path=solve2(si,sj,ti,tj);
			int score=ScoreCalculator::calc(k, path);
			bool looped = analyser.add(sj, abs(si-ti), ti, abs(sj-tj), score);
		}else{
			int s=0,rs=0;
			if(k%2==1){
				string path=solve(si,sj,ti,tj,true);
				int score=ScoreCalculator::calc(k, path);
				bool looped = analyser.add(sj, abs(si-ti), ti, abs(sj-tj), score);
			}else{
				string path=solve(si,sj,ti,tj);
				int score=ScoreCalculator::calc(k, path);
				bool looped = analyser.add(tj, abs(si-ti), si, abs(sj-tj), score);
			}
		}
		
		if(k%100==0){
			dump(ScoreCalculator::hav);
			dump(ScoreCalculator::wav);
			dump(analyser.dch);
			dump(analyser.dcw);
			dump(analyser.adch);
			dump(analyser.adcw);
			dump("====");
		}
		// break;

		// if(looped)return;
	}
}
