#include <bits/stdc++.h>
#if defined(ONLINE_JUDGE) || defined(_DEBUG)
#include <atcoder/all>
using namespace atcoder;
#endif

using namespace std;
using ll=long long;
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

#define all(a) a.begin(),a.end()
#define rall(a) a.rbegin(),a.rend()
#define rep(i,n) range(i,0,n)
#define rrep(i,n) rrange(i,0,n)
#define range(i,a,n) for(ll i=((ll)a);i<((ll)n);++i)
#define rrange(i,a,n) for(ll i=((ll)n-1);i>=((ll)a);--i)
#define repsq(i,n) for(ll i=0;i*i<=n;++i)
#define LINF ((ll)1ll<<60)
#define INF ((int)1<<30)
#define EPS (1e-9)
#define MOD (1000000007ll)
#define fcout(a) cout<<setprecision(a)<<fixed
#define PI (3.1415926535897932384)

int dx[]={1,0,-1,0,1,-1,-1,1},dy[]={0,1,0,-1,1,1,-1,-1};
template<class T>bool chmax(T&a,T b){if(a<b){a=b; return true;}return false;}
template<class T>bool chmin(T&a,T b){if(a>b){a=b; return true;}return false;}
template<class S>S sum(vector<S>&a){return accumulate(all(a),S());}
template<class S>S max(vector<S>&a){return *max_element(all(a));}
template<class S>S min(vector<S>&a){return *min_element(all(a));}

//output
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
template<class T>void dump(const T&t){puta(t,cerr);}
template<class H,class...T>void dump(const H&h,const T&...t){cerr<<h<<' ';dump(t...);}
template<class...T>void dump(tuple<T...>const&t){puta(t,cerr);}
template<class S,class T>constexpr ostream&operator<<(ostream&os,pair<S,T>p){
    os<<'['<<p.first<<", ";
    if constexpr(hasItr<T>::v)puta(p.second,bool_constant<true>(),os,']');
    else os<<p.second<<']';
    return os;
};
template<class...T>constexpr ostream&operator<<(ostream&os,tuple<T...>t){
    puta(t,os); return os;
}

void YN(bool b){puta(b?"YES":"NO");}
void Yn(bool b){puta(b?"Yes":"No");}

#ifndef _DEBUG
#define dump(...) 
#endif

//input
template<class S>auto&operator>>(istream&is,vector<S>&t){for(S&a:t)cin>>a;return is;}
// #define geta(t,n,...) t n;cin>>n;geta(t,__VA_ARGS__)
// #define vec(t,a,h,...) vector<t>a(h);rep(i,n)a[i]=t(__VA_ARGS__);rep(i,n)cin>>a[i]
template<typename...S>void geta_(S&...s){((cin>>s),...);}

#define geta(t,...) t __VA_ARGS__;geta_(__VA_ARGS__)

 
class Timer {
	static const uint64_t ClocksPerMicrosec = 2987;
	const uint64_t start_clocks;
	uint64_t limit_clocks;
	uint64_t getClocks() const{
        unsigned int lo, hi;
        __asm__ volatile ("rdtsc" : "=a" (lo), "=d" (hi));
        return((uint64_t)hi<<32)|lo;
    }

public:
	Timer(uint64_t time_millisec): start_clocks(getClocks()), limit_clocks(start_clocks + time_millisec*1000 * ClocksPerMicrosec) {}
	uint64_t get() const{return (getClocks()-start_clocks)/ClocksPerMicrosec;}
    operator bool()const{return getClocks()<limit_clocks;}
};

struct Ad{
    int x,y,s,index,a,b,c,d;
    ll score;
    bool decided=false;
    void show(){puta(index,"(",decided,") :",x,y,s,a,b,c,d,"=>",score);}
    void reset(){
        decided=a=b=c=d=score=0;
    }
    int width(){return c-a;}
    int height(){return d-b;}
    void setPos(int _a, int _b, int _c, int _d){
        decided=true;
        a=_a;b=_b;c=_c;d=_d;
        score=0;
        // 以降、Validだった場合設定された場合
        if(isValid()){
            int area=abs(c-a)*abs(d-b);
            double areaDiff=1 - 1.0*min(area,s)/max(area,s);
            score=(1-areaDiff*areaDiff)*1e9;
        }
    }
    ll answer(){
        puta(a,b,c,d);
        return score;
    }
    bool isGiveUp(){
        return decided && height()==1 and width()==1;
    }
    bool isValid(){
        if(isGiveUp())return true;
        return decided and 0<=a and a<=x and x<c and c<=10000 and 0<=b and b<=y and y<d and d<=10000;
    }
    inline bool containPoint(int _x, int _y){
        return a<=_x && _x<c && b<=_y && _y<d;
    }
    bool isIndependent(Ad other){
        if(!isValid() or !other.isValid())return true;
        // if(containPoint(other.a, other.b))return false;
        // if(containPoint(other.a, other.d-1))return false;
        // if(containPoint(other.c-1, other.b))return false;
        // if(containPoint(other.c-1, other.d-1))return false;
        // if(other.containPoint(a, b))return false;
        // if(other.containPoint(a, d-1))return false;
        // if(other.containPoint(c-1, b))return false;
        // if(other.containPoint(c-1, d-1))return false;
        // return true;
        return max(a,other.a)>=min(c,other.c) or max(b,other.b)>=min(d,other.d);
    }
    bool operator<(const Ad& rhs) const{return score < rhs.score;}
    bool operator>(const Ad& rhs) const{return score > rhs.score;}
};


// mt19937 _mt(123);
mt19937 _mt(chrono::steady_clock::now().time_since_epoch().count());
ll getRand(ll l,ll r){return uniform_int_distribution<ll>(l,r-1)(_mt);}

using ResultType=pair<ll, vector<Ad>>;
using SolverFunc=function<ResultType(ll, ll, vector<Ad>)>;

int fieldL=0, fieldR=10000, fieldWidth=10000, fieldHeight=10000;
inline int fieldCurrentWidth(){return fieldR-fieldL;}

ll solve_line(ll n, vector<Ad>&ad){
    int used=0;
    ll lineScore=0;
    vector<pair<int,int>> heightList;
    rep(i,n){
        if(ad[i].decided or clamp(ad[i].x,fieldL,fieldR-1)!=ad[i].x)continue;
        heightList.emplace_back(i,ad[i].y);
    }
    heightList.emplace_back(-1,fieldHeight);
    rep(tmp,heightList.size()-1){
        auto [i,height]=heightList[tmp];
        auto [nxti,nxtheight]=heightList[tmp+1];
        int h=min((int)ceil(1.0*ad[i].s/fieldCurrentWidth()),nxtheight-used);
        int w=min((int)round(1.0*ad[i].s/h),fieldCurrentWidth());
        chmax(used,ad[i].y-h+1);
        if(used>ad[i].y or used==fieldHeight)continue;
        int woffset=max(ad[i].x-w+1,fieldL);
        woffset=clamp(woffset,fieldL,fieldR+w);
        used=clamp(used,0,fieldHeight-h);
        assert(clamp(woffset,fieldL,fieldR)==woffset);
        assert(clamp(woffset+w,fieldL,fieldR)==woffset+w);
        assert(clamp(used,0,fieldHeight)==used);
        assert(clamp(used+h,0,fieldHeight)==used+h);
        ad[i].setPos(woffset,used,woffset+w,used+h);
        lineScore+=ad[i].score;
        used+=h;
    }
    return (ll)round(lineScore/(heightList.size()-1));
}

ResultType solve_maxWidth(ll n, ll sep, vector<Ad> ad){
    sort(all(ad), [](Ad&a,Ad&b){return a.y<b.y;});

    const int unitWidth=fieldWidth/sep;
    const int randRange=(unitWidth-10)/2;
    int rnd=0;
    rep(sloop,sep){
        int rnd2=getRand(-randRange,randRange);
        fieldL=unitWidth*sloop+rnd; fieldR=min(unitWidth*((int)sloop+1)+rnd2,fieldWidth);
        rnd=rnd2;
        
        if(sloop+1==sep)fieldR=fieldWidth;
        
        vector<Ad> lineResult(ad),invResult(ad);
        ll lineScore=solve_line(n,lineResult);
        rep(i,n){
            invResult[i].y=fieldHeight-1-invResult[i].y;
            auto tmp=fieldHeight-invResult[i].d;
            invResult[i].d=fieldHeight-invResult[i].b;
            invResult[i].b=tmp;
        }
        rep(i,n/2)swap(invResult[i], invResult[n-1-i]);
        ll invScore=solve_line(n,invResult);
        rep(i,n/2)swap(invResult[i], invResult[n-1-i]);
        rep(i,n){
            invResult[i].y=fieldHeight-1-invResult[i].y;
            auto tmp=fieldHeight-invResult[i].d;
            invResult[i].d=fieldHeight-invResult[i].b;
            invResult[i].b=tmp;
        }
        ad = lineScore>invScore ? lineResult : invResult;
    }

    sort(all(ad), [](Ad&a,Ad&b){return a.index<b.index;});

    ll score=0;
    for(auto&e:ad)score+=e.score;
    return {(ll)round(score/n), ad};
}

ResultType solve_maxWidth_Inv(ll n, ll sep,  vector<Ad> ad){
    rep(i,n)ad[i].y=fieldHeight-1-ad[i].y;

    auto[score,result]=solve_maxWidth(n,sep,ad);
    ad=result;

    rep(i,n){
        ad[i].y=fieldHeight-1-ad[i].y;
        auto tmp=fieldHeight-ad[i].d;
        ad[i].d=fieldHeight-ad[i].b;
        ad[i].b=tmp;
    }
    return {score,ad};
}

ResultType solve_maxHeight(ll n, ll sep, vector<Ad> ad){
    rep(i,n)swap(ad[i].x, ad[i].y);

    auto[score,result]=solve_maxWidth(n,sep,ad);
    ad=result;

    rep(i,n){
        swap(ad[i].x, ad[i].y);
        swap(ad[i].a, ad[i].b);
        swap(ad[i].c, ad[i].d);
    }
    return {score,ad};
}

ResultType solve_maxHeight_Inv(ll n, ll sep, vector<Ad> ad){
    rep(i,n)swap(ad[i].x, ad[i].y);

    auto[score,result]=solve_maxWidth_Inv(n,sep,ad);
    ad=result;

    rep(i,n){
        swap(ad[i].x, ad[i].y);
        swap(ad[i].a, ad[i].b);
        swap(ad[i].c, ad[i].d);
    }
    return {score,ad};
}

bool CheckCurrentForIndex(ll n, vector<Ad> ad, int index){
    if(!ad[index].decided)return false;
    rep(i,n)if(i!=index){
        if(!ad[i].decided)return false;
        if(!ad[index].isIndependent(ad[i])){
            // puta(i,"contains",index);
            return false;
        }
    }
    return true;
}

bool CheckCurrent(ll n, vector<Ad> ad){
    rep(i,n)if(!CheckCurrentForIndex(n,ad,i))return false;
    return true;
}

ResultType SolveForSolver(ll n, ll sep, vector<Ad> ad, SolverFunc solver){
    auto[_,result] = solver(n, sep, ad);
    ad=result;

    if(!CheckCurrent(n,ad)){
        return {-1,ad};
    }

    ll score=0;
    for(auto&e:ad)score+=e.score;
    return {(ll)round(score/n), ad};
}

tuple<bool,ll,Ad> RandomMoveAd(ll n, vector<Ad> ads, Ad ad){
    int randRange=100,minDiff=-10;
    ll currentScore=ad.score;

    int rv=getRand(-randRange,randRange+1);
    switch(getRand(4,6)){
        case 4:
            ad.setPos(ad.a+rv, ad.b, ad.c+rv, ad.d);
            break;
        case 5:
            ad.setPos(ad.a, ad.b+rv, ad.c, ad.d+rv);
            break;
    }
    ads[ad.index]=ad;
    return {ad.isValid() && CheckCurrentForIndex(n,ads,ad.index),ad.score-currentScore,ad};
}
tuple<bool,ll,Ad> RandomChangeAd(ll n, vector<Ad> ads, Ad ad){
    int randRange=10,minDiff=-10;
    ll currentScore=ad.score;

    int rv=getRand(-randRange,randRange+1);
    switch(getRand(0,4)){
        case 0:
            ad.setPos(ad.a+rv, ad.b, ad.c, ad.d);
            break;
        case 1:
            ad.setPos(ad.a, ad.b+rv, ad.c, ad.d);
            break;
        case 2:
            ad.setPos(ad.a, ad.b, ad.c+rv, ad.d);
            break;
        case 3:
            ad.setPos(ad.a, ad.b, ad.c, ad.d+rv);
            break;
    }
    ads[ad.index]=ad;
    return {ad.isValid() && CheckCurrentForIndex(n,ads,ad.index),ad.score-currentScore,ad};
}

void solve(){
    // input
    geta(ll,n);
    vector<Ad> ad(n);
    rep(i,n){
        geta(int,x,y,s);
        ad[i]=Ad{x,y,s,i};
    }

    //try
    ll maxScore=0,scoredTime=0,scoredSep,tryCount=0; vector<Ad> maxResult;
    vector funcs={
        solve_maxWidth,
        solve_maxHeight,
    };

    const int TotalTimeCount = 4900;
    const int FirstTimeCount = 1000;
    const int SecondTimeCount = TotalTimeCount-FirstTimeCount;

    Timer firstTimer(FirstTimeCount);

    while(firstTimer){
        for(auto&func:funcs){
            ll sepCount=5;
            while(sepCount<=50){
                sepCount++;
                tryCount++;
                if(auto[score,result]=SolveForSolver(n,sepCount,ad,func); chmax(maxScore,score)){
                    maxResult=result;
                    scoredSep=sepCount;
                    scoredTime=firstTimer.get();
                    dump("Total:",tryCount,":",scoredTime, scoredSep, score);
                }
            }
        }
    }

    if(maxScore==0){
        dump("マジ？");
        rep(i,n)ad[i].setPos(ad[i].x,ad[i].y,ad[i].x+1,ad[i].y+1);
    }
    dump(scoredSep,":",maxScore,"(",scoredTime,")");


    Timer secondTimer(SecondTimeCount);
    ll totalDiff=0,challenge=0,scoreThreshold=-2000000;

    while(secondTimer){
        rep(i,n){
            auto ad=maxResult[i];
            if(ad.isGiveUp())continue;
            challenge++;
            auto[succeeded, scoreDiff, newad]=RandomMoveAd(n,maxResult,ad);
            if(succeeded)maxResult[i]=newad;
        }
        rep(i,n){
            auto ad=maxResult[i];
            if(ad.isGiveUp())continue;
            challenge++;
            auto[succeeded, scoreDiff, newad]=RandomChangeAd(n,maxResult,ad);
            scoreThreshold=-2000000ll*(SecondTimeCount-(ll)(secondTimer.get())/1000)/SecondTimeCount;
            if(succeeded){
                if(scoreDiff>=scoreThreshold){
                    totalDiff += scoreDiff;
                    maxResult[i]=newad;
                }
            }
        }
    }
    dump(challenge);

    //output
    for(auto&e:maxResult)e.answer();
    dump(scoredSep,":",maxScore+totalDiff/n,"(",scoredTime,")");
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    solve();
    return 0;
}
