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
#define rrep(i,n) for(ll i=((ll)n)-1;i>=0;i--)
#define range(i,a,n) for(ll i=((ll)a);i<((ll)n);i++)
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
    
    ll testcase;
    cin>>testcase;
    rep(tc,testcase){
        cout<<"Case #"<<tc+1<<": ";
        ll l,r;
        cin>>l>>r;
        ll l2=l,r2=r;
        ll d=max(l,r)-min(l,r);
        ll p=0;
        if(l<r){
            range(i,-10,10){
                p=max(sqrt(d*2)+i,0);
                if(p*(p+1)/2>=d)break;
            }
            r-=p*(p+1)/2;
            if(r<0){
                r+=p;p--;
            }
        }else if(l>r){
            range(i,-10,10){
                p=max(sqrt(d*2)+i,0);
                if(p*(p+1)/2>d)break;
            }
            l-=p*(p-1)/2;
            p--;
        }

        if(p<=max(l,r)){
            ll c,c2;
            {
                ll ok=0,ng=2000000000ll;
                while(ng-ok>1){
                    ll m=(ok+ng)/2;
                    if(p*m+m*m<=l){
                        ok=m;
                    }else ng=m;
                }
                c=ok;
            }
            {
                ll ok=0,ng=2000000000ll;
                while(ng-ok>1){
                    ll m=(ok+ng)/2;
                    if(p*m+m*m+m<=r){
                        ok=m;
                    }else ng=m;
                }
                c2=ok;
            }
            c=c2=min(c,c2);
            l-=p*c+c*c;
            r-=p*c2+c2*c2+c2;
            p+=c+c2;
            
        }
        
        {
            ll ok=0,ng=2000000000ll;
            while(ng-ok>1){
                ll m=(ok+ng)/2;
                if(p*m+m*(m+1)/2<=l){
                    ok=m;
                }else ng=m;
            }
            l-=p*ok+ok*(ok+1)/2;
            p+=ok;
        }
        {
            ll ok=0,ng=2000000000ll;
            while(ng-ok>1){
                ll m=(ok+ng)/2;
                if(p*m+m*(m+1)/2<=r){
                    ok=m;
                }else ng=m;
            }
            r-=p*ok+ok*(ok+1)/2;
            p+=ok;

        }

        // ll p2=0;
        // range(i,1,2000000000ll){
        //     if(l2>=r2){if(l2>=i)l2-=i;else break;}
        //     else{if(r2>=i)r2-=i;else break;}
        //     p2++;
        // }
        puta(p,l,r);
        // puta(p2,l2,r2);
    }
    return 0;
}