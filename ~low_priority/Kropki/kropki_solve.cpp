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

pair<ll, vl> readURL(string s){
    s = s.substr(28,1000);
    ll n = 0;
    rep(i,10){
        if(isdigit(s[i])){
            n = n*10+(s[i]-'0');
        }else{
            s=s.substr(i*2+2,1000);
            break;
        }
    }
    vl marks;
    for(auto&c:s){
        ll v;
        if(isdigit(c)){
            v = c-'0';
        }else v = c-'a'+10;
        marks.emplace_back(v/9);
        marks.emplace_back(v/3%3);
        marks.emplace_back(v%3);
    }
    return make_pair(n, marks);
}

bool isWhite(ll a, ll b){
    return abs(a-b)==1;
}
bool isBlack(ll a, ll b){
    return a*2==b or a==b*2;
}
vl OK(ll v1, ll v2){
    return vl{v1, v2, 0};
}
vl NG(ll v1, ll v2){
    return vl{-v1, -v2, 0};
}

vvl solve(ll n, vl&marks){
    vvl rules;
    vl rule;
    // At Least One
    range(num,1,n+1){
        rep(i,n){
            rule.clear();
            rep(j,n)rule.emplace_back(i*n*n+j*n+num);
            rule.emplace_back(0);
            rules.push_back(rule);
            rule.clear();
            rep(j,n)rule.emplace_back(j*n*n+i*n+num);
            rule.emplace_back(0);
            rules.push_back(rule);
        }
    }
    // At Most One
    range(num,1,n+1){
        rep(r,n){
            rep(c,n)range(c2,c+1,n){
                rules.push_back(vl{-(r*n*n+c*n+num), -(r*n*n+c2*n+num), 0});
            }
        }
        rep(c,n){
            rep(r,n)range(r2,r+1,n){
                rules.push_back(vl{-(r*n*n+c*n+num), -(r2*n*n+c*n+num), 0});
            }
        }
    }
    rules.clear();
    // Marks
    ll mc=0;
    rep(i,n)rep(j,n-1){
        ll m=marks[mc++];
        rep(num1,n)rep(num2,n){
            ll v1=i*n*n+j*n+num1;
            ll v2=i*n*n+(j+1)*n+num2;
            if(m==0){
                
            }
        }
    }
    return rules;
}

int main(){
	cin.tie(0);
	ios::sync_with_stdio(false);
	string s;
    cin>>s;
    ll n; vl marks;
    tie(n, marks) = readURL(s);
    vvl rules = solve(n, marks);
    cout<<"p cnf "<<n*n*n<<" "<<rules.size()<<endl;
    for(auto&l:rules)puta(l);
	return 0;
}