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


int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    ll n,m,v,p;
    cin>>n>>m>>v>>p;
    vl a(n); cin>>a;

    sort(all(a));
    // puta(a);
    ll ok=n-1,ng=-1;
    while(ok-ng>1){
        ll mid=(ok+ng)/2;
        ll tgt=a[mid] + m;
        ll need=(v-1)*m;
        ll life = p-1;
        ll near=0;
        deque<ll> dq;
        rep(i,n)if(i!=mid){
            ll diff=tgt-a[i];
            if(diff<0){//すでに越されているなら，どうせ無理なので全力で振っていい．ただし猶予は減る
                need-=m;
                life--;
            }else if(diff>=m){//限界まで振っても並ぶか未満なので振っていい
                need-=m;
            }else{
                // diff回振ると，まだ振る猶予がm-diff回ある状態で同じになってしまう
                need-=diff;
                near++;
                dq.push_front(m-diff);
            }
        }
        if(need<=0){//振り切った場合
            if(life>=0){//tgtを超えたものがp-1個以下
                ok=mid;
            }else{
                ng=mid;
            }
        }else{//まだneed回残ってる
            if(life<0){
                ng=mid;
            }else{
                //life個の余裕がある
                //nearなものに1でも振ると越される，ただしどうせ降るなら限界まで振っていい
                rep(i,dq.size()){
                    need-=dq[i];
                    life--;
                    if(life<0 or need<=0)break;
                }
                if(life>=0){//tgtを超えたものがp-1個以下
                    ok=mid;
                }else{
                    ng=mid;
                }
            }
        }
        // puta(ok,ng);
    }
    puta(n-ok);

    return 0;
}