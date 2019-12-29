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
mt19937 _mt(chrono::steady_clock::now().time_since_epoch().count());
ll getRand(ll l,ll r){return uniform_int_distribution<ll>(l,r-1)(_mt);}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    ll n; cin>>n;
    if(n%3==0){
        vs d={"abb","a.c","ddc"};
        rep(i,n){
            rep(j,n){
                cout<<d[i%3][j%3];
            }
            cout<<endl;
        }
    }else if(n%4==0){
        vs d={"abcc","abdd","eefg","hhfg"};
        rep(i,n){
            rep(j,n){
                cout<<d[i%4][j%4];
            }
            cout<<endl;
        }
    }else if(n%5==0){
        vs d={"abbcc","a.dee","ffd.g","..hig","jjhi."};
        rep(i,n){
            rep(j,n){
                cout<<d[i%5][j%5];
            }
            cout<<endl;
        }
    }else if(n%7==0){
        vs d={"a.bb.cc","ad.ee..",".df.gg.","h.f...i","hj....i",".jkk..l","mm..nnl"};
        rep(i,n){
            rep(j,n){
                cout<<d[i%7][j%7];
            }
            cout<<endl;
        }
    }else{
        bool ok=false;
        if(!ok){
            rep(d9,n/9+1){
                if((n-d9*9)%8==0){
                    ll d8=(n-d9*9)/8;
                    ok=true;
                    vs s9={
                        "abbabbabb",
                        "a.ca.ca.c",
                        "ddcddcddc",
                        "abbabbabb",
                        "a.ca.ca.c",
                        "ddcddcddc",
                        "abbabbabb",
                        "a.ca.ca.c",
                        "ddcddcddc",
                    };
                    vs s8={
                        "abccabcc",
                        "abddabdd",
                        "eefgeefg",
                        "hhfghhfg",
                        "abccabcc",
                        "abddabdd",
                        "eefgeefg",
                        "hhfghhfg",
                    };
                    rep(i,n){
                        rep(j,n){
                            if(i<d9*9 and j<d9*9 and i/9==j/9){
                                cout<<s9[i%9][j%9];
                            }else if(i>=d9*9 and j>=d9*9 and (i-d9*9)/8==(j-d9*9)/8){
                                cout<<s8[(i-d9*9)%8][(j-d9*9)%8];
                            }else cout<<".";
                        }
                        cout<<endl;
                    }
                }
                if(ok)break;
            }
        }
        if(!ok){
            rep(d9,n/9+1){
                if((n-d9*9)%10==0){
                    ll d10=(n-d9*9)/10;
                    ok=true;
                    vs s9={
                        "abbabbabb",
                        "a.ca.ca.c",
                        "ddcddcddc",
                        "abbabbabb",
                        "a.ca.ca.c",
                        "ddcddcddc",
                        "abbabbabb",
                        "a.ca.ca.c",
                        "ddcddcddc",
                    };
                    vs s10={
                        "abbccabbcc",
                        "a.deea.dee",
                        "ffd.gffd.g",
                        "..hig..hig",
                        "jjhi.jjhi.",
                        "abbccabbcc",
                        "a.deea.dee",
                        "ffd.gffd.g",
                        "..hig..hig",
                        "jjhi.jjhi.",
                    };
                    rep(i,n){
                        rep(j,n){
                            if(i<d9*9 and j<d9*9 and i/9==j/9){
                                cout<<s9[i%9][j%9];
                            }else if(i>=d9*9 and j>=d9*9 and (i-d9*9)/10==(j-d9*9)/10){
                                cout<<s10[(i-d9*9)%10][(j-d9*9)%10];
                            }else cout<<".";
                        }
                        cout<<endl;
                    }
                }
                if(ok)break;
            }
        }

        //14
        if(!ok){
            rep(d8,n/8+1){
                if((n-d8*8)%14==0){
                    ll d14=(n-d8*8)/14;
                    ok=true;
                    vs s8={
                        "abccabcc",
                        "abddabdd",
                        "eefgeefg",
                        "hhfghhfg",
                        "abccabcc",
                        "abddabdd",
                        "eefgeefg",
                        "hhfghhfg",
                    };
                    vs s14={
                        "a.bb.cca.bb.cc",
                        "ad.ee..ad.ee..",
                        ".df.gg..df.gg.",
                        "h.f...ih.f...i",
                        "hj....ihj....i",
                        ".jkk..l.jkk..l",
                        "mm..nnlmm..nnl",
                        "a.bb.cca.bb.cc",
                        "ad.ee..ad.ee..",
                        ".df.gg..df.gg.",
                        "h.f...ih.f...i",
                        "hj....ihj....i",
                        ".jkk..l.jkk..l",
                        "mm..nnlmm..nnl",
                    };
                    rep(i,n){
                        rep(j,n){
                            if(i<d8*8 and j<d8*8 and i/8==j/8){
                                cout<<s8[i%8][j%8];
                            }else if(i>=d8*8 and j>=d8*8 and (i-d8*8)/14==(j-d8*8)/14){
                                cout<<s14[(i-d8*8)%14][(j-d8*8)%14];
                            }else cout<<".";
                        }
                        cout<<endl;
                    }
                }
                if(ok)break;
            }
        }

        //14
        if(!ok){
            rep(d8,n/8+1){
                if((n-d8*8)%10==0){
                    ll d10=(n-d8*8)/10;
                    ok=true;
                    vs s8={
                        "abccabcc",
                        "abddabdd",
                        "eefgeefg",
                        "hhfghhfg",
                        "abccabcc",
                        "abddabdd",
                        "eefgeefg",
                        "hhfghhfg",
                    };
                    vs s10={
                        "abbccabbcc",
                        "a.deea.dee",
                        "ffd.gffd.g",
                        "..hig..hig",
                        "jjhi.jjhi.",
                        "abbccabbcc",
                        "a.deea.dee",
                        "ffd.gffd.g",
                        "..hig..hig",
                        "jjhi.jjhi.",
                    };
                    rep(i,n){
                        rep(j,n){
                            if(i<d8*8 and j<d8*8 and i/8==j/8){
                                cout<<s8[i%8][j%8];
                            }else if(i>=d8*8 and j>=d8*8 and (i-d8*8)/10==(j-d8*8)/10){
                                cout<<s10[(i-d8*8)%10][(j-d8*8)%10];
                            }else cout<<".";
                        }
                        cout<<endl;
                    }
                }
                if(ok)break;
            }
        }



        //14
        if(!ok){
            rep(d9,n/9+1){
                if((n-d9*9)%14==0){
                    ll d14=(n-d9*9)/14;
                    ok=true;
                    vs s9={
                        "abbabbabb",
                        "a.ca.ca.c",
                        "ddcddcddc",
                        "abbabbabb",
                        "a.ca.ca.c",
                        "ddcddcddc",
                        "abbabbabb",
                        "a.ca.ca.c",
                        "ddcddcddc",
                    };
                    vs s14={
                        "a.bb.cca.bb.cc",
                        "ad.ee..ad.ee..",
                        ".df.gg..df.gg.",
                        "h.f...ih.f...i",
                        "hj....ihj....i",
                        ".jkk..l.jkk..l",
                        "mm..nnlmm..nnl",
                        "a.bb.cca.bb.cc",
                        "ad.ee..ad.ee..",
                        ".df.gg..df.gg.",
                        "h.f...ih.f...i",
                        "hj....ihj....i",
                        ".jkk..l.jkk..l",
                        "mm..nnlmm..nnl",
                    };
                    rep(i,n){
                        rep(j,n){
                            if(i<d9*9 and j<d9*9 and i/9==j/9){
                                cout<<s9[i%9][j%9];
                            }else if(i>=d9*9 and j>=d9*9 and (i-d9*9)/14==(j-d9*9)/14){
                                cout<<s14[(i-d9*9)%14][(j-d9*9)%14];
                            }else cout<<".";
                        }
                        cout<<endl;
                    }
                }
                if(ok)break;
            }
        }

        //14
        if(!ok){
            rep(d10,n/10+1){
                if((n-d10*10)%14==0){
                    ll d14=(n-d10*10)/14;
                    ok=true;
                    vs s10={
                        "abbccabbcc",
                        "a.deea.dee",
                        "ffd.gffd.g",
                        "..hig..hig",
                        "jjhi.jjhi.",
                        "abbccabbcc",
                        "a.deea.dee",
                        "ffd.gffd.g",
                        "..hig..hig",
                        "jjhi.jjhi.",
                    };
                    vs s14={
                        "a.bb.cca.bb.cc",
                        "ad.ee..ad.ee..",
                        ".df.gg..df.gg.",
                        "h.f...ih.f...i",
                        "hj....ihj....i",
                        ".jkk..l.jkk..l",
                        "mm..nnlmm..nnl",
                        "a.bb.cca.bb.cc",
                        "ad.ee..ad.ee..",
                        ".df.gg..df.gg.",
                        "h.f...ih.f...i",
                        "hj....ihj....i",
                        ".jkk..l.jkk..l",
                        "mm..nnlmm..nnl",
                    };
                    rep(i,n){
                        rep(j,n){
                            if(i<d10*10 and j<d10*10 and i/10==j/10){
                                cout<<s10[i%10][j%10];
                            }else if(i>=d10*10 and j>=d10*10 and (i-d10*10)/14==(j-d10*10)/14){
                                cout<<s14[(i-d10*10)%14][(j-d10*10)%14];
                            }else cout<<".";
                        }
                        cout<<endl;
                    }
                }
                if(ok)break;
            }
        }


        if(!ok){
            rep(d4,n/4+1){
                if((n-d4*4)%5==0){
                    ll d5=(n-d4*4)/5;
                    ok=true;
                    vs s4={"abcc","abdd","eefg","hhfg"};
                    vs s5={"abbcc","a.dee","ffd.g","..hig","jjhi."};
                    rep(i,n){
                        rep(j,n){
                            if(i<d4*4 and j<d4*4 and i/4==j/4){
                                cout<<s4[i%4][j%4];
                            }else if(i>=d4*4 and j>=d4*4 and (i-d4*4)/5==(j-d4*4)/5){
                                cout<<s5[(i-d4*4)%5][(j-d4*4)%5];
                            }else cout<<".";
                        }
                        cout<<endl;
                    }
                }
                if(ok)break;
            }
        }
        if(!ok){
            puta(-1);
            // if(n==7)cout<<vl{1,}[-100000000000000ll]<<endl;
        }
    }
    return 0;
}