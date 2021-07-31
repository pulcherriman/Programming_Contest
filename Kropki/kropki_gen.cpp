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
template<class T>bool chmin(T&a,T b){if(a>=b){a=b; return true;}return false;}
template<class S>S sum(vector<S>&a){return accumulate(all(a),S());}
template<class S>S max(vector<S>&a){return *max_element(all(a));}
template<class S>S min(vector<S>&a){return *min_element(all(a));}
ll max(int a,ll b){return max((ll)a,b);} ll max(ll a,int b){return max(a,(ll)b);}
int sgn(const double&r){return (r>EPS)-(r<-EPS);} // a>0  : sgn(a)>0
int sgn(const double&a,const double&b){return sgn(a-b);} // b<=c : sgn(b,c)<=0

template<class T>void puta(T&&t){cout<<t<<endl;}
template<class H,class...T>void puta(H&&h,T&&...t){cout<<h<<' ';puta(t...);}
template<class S,class T>void tf(bool b,S t,T f){if(b)puta(t);else puta(f);}
void YN(bool b){tf(b,"YES","NO");}
void Yn(bool b){tf(b,"Yes","No");}
void yn(bool b){tf(b,"yes","no");}
template<class S,class T>ostream&operator<<(ostream&os,pair<S,T>p){os<<"["<<p.first<<", "<<p.second<<"]";return os;};
template<class S>auto&operator<<(ostream&os,vector<S>t){bool a=1;for(auto s:t){os<<(a?"":" ")<<s;a=0;}return os;}
template<class S>auto&operator>>(istream&is,vector<S>&t){for(S&a:t)cin>>a;return is;}

/*他のライブラリを入れる場所*/
#define _cTime (chrono::system_clock::now())
#define progress (chrono::duration_cast<chrono::milliseconds>(_cTime-_sTime).count())
#define reset _sTime=_cTime
auto reset;

mt19937 _mt(chrono::steady_clock::now().time_since_epoch().count());
ll getRand(ll l,ll r){return uniform_int_distribution<ll>(l,r-1)(_mt);}

void change(vvl&f, ll rc, ll ind, ll ind2){
    ll n = f.size();
    if(rc==0)rep(i,n)swap(f[i][ind], f[i][ind2]);
    else rep(j,n)swap(f[ind][j], f[ind2][j]);
}

void init(vvl&f){
    ll n = f.size();
    vl fs(n); iota(all(fs), 1);
    vl sc(n); iota(all(sc), 1);
    rep(i,n){
        swap(fs[i], fs[getRand(i,n)]);
        swap(sc[i], sc[getRand(i,n)]);
    }

    rep(i,n)rep(j,n){
        f[i][j]=fs[(sc[i]+j)%n];
    }
}

ll evaluate(vvl&f, ll b, ll w){
    ll n = f.size();
    vvl odd(n, vl(n,0));
    ll score = 0, white =0, black = 0;
    rep(i,n)rep(j,n-1){
        if(abs(f[i][j]-f[i][j+1])==1){
            odd[i][j] += 1;
            odd[i][j+1] += 1;
            white++;
        }
    }
    rep(i,n-1)rep(j,n){
        if(abs(f[i][j]-f[i+1][j])==1){
            odd[i][j] += 1;
            odd[i+1][j] += 1;
            white++;
        }
    }

    rep(i,n)rep(j,n-1){
        if(f[i][j]*2 == f[i][j+1] or f[i][j] == f[i][j+1]*2){
            odd[i][j] += 1;
            odd[i][j+1] += 1;
            black++;
        }
    }
    rep(i,n-1)rep(j,n){
        if(f[i][j]*2 == f[i+1][j] or f[i][j] == f[i+1][j]*2){
            odd[i][j] += 1;
            odd[i+1][j] += 1;
            black++;
        }
    }
	// if(white>0)return LINF+1;
	if(black+white==0)return LINF+1;
	return black*100-black;
	return black+white;
    return (black-b)*(black-b) + (white-w)*(white-w);
}

ll getMark(ll a, ll b){
    if(abs(a-b)==1)return 1;
    else if(a*2==b or a==b*2)return 2;
    return 0;
}

string getURL(vvl&f){
    ll n = f.size();
    string url = "http://pzv.jp/p.html?kropki/" + to_string(n) + "/" + to_string(n) + "/";
    string chr = "0123456789abcdefghijklmnopqrstuvwxyz";
    vl pw3{1,3,9};

    ll val=0, cnt=0;
    rep(i,n){
        rep(j,n-1){
            val += getMark(f[i][j], f[i][j+1]) * pw3[2-cnt];
            cnt++;
            if(cnt == 3){
                url+=chr[val];
                val = cnt = 0;
            }
        }
    }
    rep(i,n-1){
        rep(j,n){
            val += getMark(f[i][j], f[i+1][j]) * pw3[2-cnt];
            cnt++;
            if(cnt == 3){
                url+=chr[val];
                val = cnt = 0;
            }
        }
    }
    if(cnt)url+=chr[val];
    return url;
}

pair<vvl, ll> solve(ll n, ll b, ll w){
    vvl f(n, vl(n));
    init(f);
    ll prev = evaluate(f, b, w);
    reset;

    rep(_,1000){
        ll r = getRand(0,2);
        ll c = getRand(0,n-1);
        ll c2 = getRand(0,n-1);
        if(c==c2)continue;
        change(f,r,c,c2);
        ll cur = evaluate(f, b, w);
        if(prev<=cur){
            change(f,r,c,c2);
        }else{
            prev = cur;
        }
    }
    return make_pair(f, prev);
}

int main(){
	cin.tie(0);
	ios::sync_with_stdio(false);
    ll n,b,w; cin>>n>>b>>w;
    vvl f; ll score = LINF;
    rep(i,10000){
        vvl tf; ll tscore;
        tie(tf,tscore) = solve(n, b, w);
		if(chmin(score,tscore)){
			f=tf;
		    puta(getURL(f));
		}
    }
	return 0;
}