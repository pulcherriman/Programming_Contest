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

int dx[]={1,0,-1,0,1,-1,-1,1},dy[]={0,1,0,-1,1,1,-1,-1};
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
class _Prime{
    public:
    ll target,c,block=2*3*5*7*11*13*17*2;
    vb firstb;
    vector<short> al;
    vi pr,li;
    vl primes;
    void calc(){
        firstb.assign(block,false);
        al.assign(block,0);
        primes.clear();
        c=0;
        firstcalc();
        for(ll i=block;i<target;i+=block)calc(i);
    }
    void firstcalc(){
        for(int&p:vi{2,3,5,7,11,13,17}){
            if(p>target)break;
            add(p);
            if((ll)p*p<target){
                pr.push_back(p);
                for(ll j=p*2;j<block;j+=p)firstb[j]=true;
            }
        }
        c++;
        li.push_back(1);
        range(i,19,block){
            if(firstb[i])continue;
            li.push_back(i);
            if(al[i]==c)continue;
            if(i>target)break;
            add(i);
            if((ll)i*i<=target){
                pr.push_back(i);
                for(ll j=i*2;j<block;j+=i)al[j]=c;
            }
        }
    }

    void calc(ll b){
        c++;
        ll mv=b+block;
        for(int&p:pr){
            if((ll)p*p>mv)break;
            ll f=b%p;
            if(f)f=p-f;
            if((f&1)==0)f+=p;
            for(ll j=f;j<block;j+=p*2)al[j]=c;
        }
        for(int&i:li){
            if(al[i]==c)continue;
            if(b+i>target)break;
            add(b+i);
        }
    }
    void seg(ll l, ll r){
        chmax(l,2ll);
        firstb.assign(r-l,true);
        primes.clear();
        vl p=_Prime().sequence(block);
        for(ll i=0,j;p[i]*p[i]<r;++i){
            if(p[i]>=l)j=p[i]*p[i];
            else if(l%p[i]==0)j=l;
            else j=l-(l%p[i])+p[i];
            for(;j<r;j+=p[i])firstb[j-l]=false;
        }
        range(i,l,r)if(firstb[i-l])add(i);
    }


    void add(ll a){primes.push_back(a);}

    public:
    _Prime(){}
    vl sequence(ll n=100){
        assert(n<=100'000'000);
        target=n;calc();return primes;
    }
    vl segment(ll l=1000, ll r=2000){
        assert(r<=block*block); //1'0424'8184'0400ll ~= 10^12
        assert(r-l<=100'000'000);
        seg(l,r);return primes;
    }
    bool isPrime(ll n){
        assert(n<=block*block); //1'0424'8184'0400ll ~= 10^12
        for(ll&p:_Prime().sequence((ll)sqrt(n)+1))if(n%p==0)return false;
        return true;
    }
};
_Prime Prime;



int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);

    // puta(Prime.sequence(1e8).size()); // 5761455
    // puta(Prime.segment(1e12, 1e12+1e8).size()); // 3618282
    puta(Prime.isPrime(10123457689ll));
    
    return 0;
    
    

}