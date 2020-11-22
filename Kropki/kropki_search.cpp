#pragma GCC target("avx2")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

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
#define _cTime (chrono::system_clock::now())
#define progress (chrono::duration_cast<chrono::milliseconds>(_cTime-_sTime).count())
#define reset _sTime=_cTime
auto reset;

pair<int, vi> readURL(string s){
    s = s.substr(28,1000);
    int n = 0;
    rep(i,10){
        if(isdigit(s[i])){
            n = n*10+(s[i]-'0');
        }else{
            s=s.substr(i*2+2,1000);
            break;
        }
    }
    vi marks;
    for(auto&c:s){
        int v;
        if(isdigit(c)){
            v = c-'0';
        }else v = c-'a'+10;
        marks.emplace_back(v/9);
        marks.emplace_back(v/3%3);
        marks.emplace_back(v%3);
    }
    return make_pair(n, marks);
}

bool isWhite(int a, int b){
    return a-b==1 or b-a==1;
}
bool isBlack(int a, int b){
    return a*2==b or a==b*2;
}

enum{HORIZONTAL, VERTICAL};
int getMark(int n, vi&marks, int direction, int y, int x){
    if(direction == HORIZONTAL){
        return marks[y*(n-1)+x];
    }else{
        return marks[n*(n-1) + y*n+x];
    }
}

int dx[]={1,0,-1,0,1,-1,-1,1},dy[]={0,1,0,-1,1,1,-1,-1};
bool isRelatedBlack(int n, vi&marks, int y, int x){
    bool ret=true;
    rep(v,4){
        int ny=y+dy[v];
        int nx=x+dx[v];
        if(nx<0 or ny<0 or ny>=n or nx>=n)continue;
        ret &= (ny<y and getMark(n, marks, HORIZONTAL, ny, nx));
        ret &= (nx<y and getMark(n, marks, VERTICAL, ny, nx));
        ret &= (ny>y and getMark(n, marks, HORIZONTAL, y, x));
        ret &= (nx>x and getMark(n, marks, HORIZONTAL, y, x));
    }
    return ret;
}


pair<int, vvi> solve(int n, vi&marks, int y=-1, int x=-1, vvi field=vvi()){
    int ansCount=0, childAnsCount=0;
    vvi answer, childAnswer;

    int ny=y+((x+1)%n==0);
    int nx=(x+1)%n;

    if(ny==n){
        ansCount = 1;
        return make_pair(ansCount, field);
    }
    if(ny+nx==0){
        field.resize(n, vi(n));
    }

    vi putable(n+1,true); putable[0]=false;
    rep(i,n){
        putable[field[i][nx]]=false;
        putable[field[ny][i]]=false;
    }
    if(isRelatedBlack(n, marks, ny, nx)){
        range(i,1,n+1){
            if(i%2==1 and i*2>n)putable[i]=false;
        }
    }
    
    range(i,1,n+1)if(putable[i]){
        if(ny>0){
            switch(getMark(n, marks, VERTICAL, ny-1, nx)){
                case 0:
                    putable[i] &= !isWhite(field[ny-1][nx], i);
                    putable[i] &= !isBlack(field[ny-1][nx], i);
                    break;
                case 1:
                    putable[i] &= isWhite(field[ny-1][nx], i);
                    break;
                case 2:
                    putable[i] &= isBlack(field[ny-1][nx], i);
                    break;
                default:
                    break;
            }
        }
        if(nx>0){
            switch(getMark(n, marks, HORIZONTAL, ny, nx-1)){
                case 0:
                    putable[i] &= !isWhite(field[ny][nx-1], i);
                    putable[i] &= !isBlack(field[ny][nx-1], i);
                    break;
                case 1:
                    putable[i] &= isWhite(field[ny][nx-1], i);
                    break;
                case 2:
                    putable[i] &= isBlack(field[ny][nx-1], i);
                    break;
                default:
                    break;
            }
        }
    }

    range(i,1,n+1)if(ansCount<=1 and putable[i]){
        field[ny][nx]=i;
        tie(childAnsCount, childAnswer) = solve(n,marks,ny,nx,field);
        if(childAnsCount){
            ansCount += childAnsCount;
            answer = childAnswer;
        }
    }
    return make_pair(ansCount, answer);
}

string getDatetimeStr() {
    time_t t = time(nullptr);
    const tm* localTime = localtime(&t);
    stringstream s;
    s << "20" << localTime->tm_year - 100;
    s << setw(2) << setfill('0') << localTime->tm_mon + 1;
    s << setw(2) << setfill('0') << localTime->tm_mday;
    s << setw(2) << setfill('0') << localTime->tm_hour;
    s << setw(2) << setfill('0') << localTime->tm_min;
    s << setw(2) << setfill('0') << localTime->tm_sec;
    return s.str();
}

int main(){
	cin.tie(0);
	ios::sync_with_stdio(false);
	string s;
    cin>>s;
    int n; vi marks;
    tie(n, marks) = readURL(s);
    
    int ansCount; vvi answer;
    tie(ansCount, answer) = solve(n, marks);

    if(ansCount==1){
        int level = progress;
        ofstream ofstr("./Data/"+to_string(n)+"/"+to_string(n)+"_"+to_string(level)+"_"+getDatetimeStr()+".txt");

        streambuf* strbuf;
        strbuf = cout.rdbuf( ofstr.rdbuf() );
    
        puta("URL:", s);
        puta("");
        puta("Calculate Time:", progress, "ms");
        if(ansCount==0){
            puta("Answer is not found.");
        }else if(ansCount==1){
            puta("Answer is found.");
            rep(i,n)puta(answer[i]);
        }else{
            puta("Answer is not unique.");
        }

        cout.rdbuf( strbuf );
    }else{
        cout<<"Failed."<<endl;
    }
	return 0;
}