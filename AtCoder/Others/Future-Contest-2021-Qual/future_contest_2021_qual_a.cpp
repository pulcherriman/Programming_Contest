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

class Result{
    public:
    int x=0,y=0,n=100,w=20,h=20,tx=14,ty=14;
    bool isTgtOptimise = false;
;
    vl px,py;
    string ans="";

    int nxt = 0, score=4000;
    vl deck;
    vvl stage;

    void Init(){
        px.resize(n);
        py.resize(n);
        deck.resize(1,-1);
        rep(i,n)cin>>py[i]>>px[i];
        stage = vvl(h,vl(w, -1));
        rep(i,n)stage[py[i]][px[i]] = i;
    }

    void Up(bool isPrinted=true){
        bool ok=isTgtOptimise && stage[y][x]!=-1 && stage[y-1][x]==-1 && DistPos(y,x,ty,tx)>DistPos(y-1,x,ty,tx);
        if(ok)Pick(isPrinted);
        y--;
        if(isPrinted){score--;ans += 'U';}
        if(ok)Put(isPrinted);
    }
    void Down(bool isPrinted=true){
        bool ok=isTgtOptimise && stage[y][x]!=-1 && stage[y+1][x]==-1 && DistPos(y,x,ty,tx)>DistPos(y+1,x,ty,tx);
        if(ok)Pick(isPrinted);
        y++; 
        if(isPrinted){score--; ans += 'D';}
        if(ok)Put(isPrinted);
    }
    void Left(bool isPrinted=true){
        bool ok=isTgtOptimise && stage[y][x]!=-1 && stage[y][x-1]==-1 && DistPos(y,x,ty,tx)>DistPos(y,x-1,ty,tx);
        if(ok)Pick(isPrinted);
        x--;
        if(isPrinted){score--;ans += 'L';}
        if(ok)Put(isPrinted);
    }
    void Right(bool isPrinted=true){
        bool ok=isTgtOptimise && stage[y][x]!=-1 && stage[y][x+1]==-1 && DistPos(y,x,ty,tx)>DistPos(y,x+1,ty,tx);
        if(ok)Pick(isPrinted);
        x++;
        if(isPrinted){score--; ans += 'R';}
        if(ok)Put(isPrinted);
    }
    void Pick(bool isPrinted=true){
        if(stage[y][x]==-1)return;
        if(isPrinted) ans += 'I';
        if(stage[y][x]==nxt && deck.size()-1==nxt)nxt++;
        deck.push_back(stage[y][x]);
        stage[y][x]=-1;
    }
    void Put(bool isPrinted=true){
        if(deck.back()==nxt-1 && deck.size()-1==nxt)return; //置く必要がない
        if(isPrinted)ans += 'O';
        py[deck.back()]=y, px[deck.back()]=x;
        stage[y][x]=deck.back();
        deck.pop_back();
    }

    void To(int gy, int gx){
        if(y==gy and x==gx) return;
        if(y!=gy && x!=gx && stage[y][x]!=-1 && stage[y][x+(x>gx?-1:1)]==-1){
            if(x>gx) Left();
            if(x<gx) Right();
            if(y>gy) Up();
            if(y<gy) Down();
        }else{
            if(y>gy) Up();
            if(y<gy) Down();
            if(x>gx) Left();
            if(x<gx) Right();
        }
        To(gy,gx);
    }

    void To(int num){
        To(py[num], px[num]);
    }

    int DistPos(int gy, int gx, int gy2=-1, int gx2=-1){
        if(gy2==-1)gy2=y, gx2=x;
        return abs(gy-gy2)+abs(gx-gx2);
    }
    int Dist(int num, int num2=-1)
    {
        if(num2==-1)return DistPos(py[num], px[num]);
        return DistPos(py[num], px[num], py[num2], px[num2]);
    }
    void To2(int num){
        vl go(1,num);
        if(Dist(num+1) + Dist(num+1,num) == Dist(num)){
            go.push_back(num+1);
        }

        while(!go.empty()){
            int to=go.back();
            go.pop_back();
            To(to);
            Pick();
            isTgtOptimise = false;
        }

        stack<int> cmd;
        int tmp=deck.size()-1;
        while(deck[tmp] != nxt-1){
            Undo();
            if(stage[y][x]==num) tmp--;
            if(stage[y][x]==-1){
                cmd.push(undo);
                tmp--;
            }
        }
        while(undo){
            if(cmd.size() && undo==cmd.top()){
                int p=num+cmd.size();
                stage[py[p]][px[p]]=-1;
                stage[y][x]=p;
                py[p]=y, px[p]=x;
                deck.pop_back();
                cmd.pop();
                int l=ans.length()-undo;
                ans = ans.substr(0,l)+'O'+ans.substr(l,undo);
            }
            Redo();
        }
        isTgtOptimise = true;
        nxt=num+1;
    }

    int undo=0;
    void Undo(){
        undo++;
        if(ans[ans.length()-undo]=='U')Down(false);
        if(ans[ans.length()-undo]=='D')Up(false);
        if(ans[ans.length()-undo]=='L')Right(false);
        if(ans[ans.length()-undo]=='R')Left(false);
        if(ans[ans.length()-undo]=='I')Put(false);
        if(ans[ans.length()-undo]=='O')Pick(false);
    }
    void Redo(){
        if(ans[ans.length()-undo]=='U')Up(false);
        if(ans[ans.length()-undo]=='D')Down(false);
        if(ans[ans.length()-undo]=='L')Left(false);
        if(ans[ans.length()-undo]=='R')Right(false);
        if(ans[ans.length()-undo]=='I')Pick(false);
        if(ans[ans.length()-undo]=='O')Put(false);
        undo--;
    }

    void PP_Pick1(int r){
        while(true){
            if(y%2)Left();else Right();
            if(stage[y][x]!=-1)Pick();
            if((y%2&&x==0)||(y%2==0&&x==19)){
                if(y==r-1)break;
                Down();
                if(stage[y][x]!=-1)Pick();
            }
        }
        while(true){
            if(x%2)Up();else Down();
            if(stage[y][x]!=-1)Pick();
            if((x%2&&y==r)||(x%2==0&&y==19)){
                Right();
                if(x==r)break;
                if(stage[y][x]!=-1)Pick();
            }
        }
    }

    void PP_Pick2(int r){
        while(true){
            if(x%2)Up();else Down();
            if(stage[y][x]!=-1)Pick();
            if((x%2&&y==0)||(x%2==0&&y==19)){
                if(x==r-1)break;
                Right();
                if(stage[y][x]!=-1)Pick();
            }
        }
        while(true){
            if(y%2)Left();else Right();
            if(stage[y][x]!=-1)Pick();
            if((y%2&&x==r)||(y%2==0&&x==19)){
                Down();
                if(y==r)break;
                if(stage[y][x]!=-1)Pick();
            }
        }
    }

    void PP_Put1(int r){
        rep(_,(10-r)/2){Down();Right();}
        while(true){
            if(stage[y][x]==-1)Put();
            if(x%2)Up();else Down();
            if((x%2&&y==r)||(x%2==0&&y==(14+r/2))){
                if(stage[y][x]==-1)Put();
                if(x==(14+r/2))break;
                Right();
            }
        }
    }

    void PP_Put2(int r){
        rep(_,(10-r)/2){Down();Right();}
        while(true){
            if(stage[y][x]==-1)Put();
            if(y%2)Left();else Right();
            if((y%2&&x==r)||(y%2==0&&x==(14+r/2))){
                if(stage[y][x]==-1)Put();
                if(y==(14+r/2))break;
                Down();
            }
        }
    }

    void PreProcess1(int r=10){
        PP_Pick1(r);
        PP_Put1(r);
    }

    void PreProcess2(int r=10){
        PP_Pick1(r);
        PP_Put2(r);
    }

    void PreProcess3(int r=10){
        PP_Pick2(r);
        PP_Put1(r);
    }

    void PreProcess4(int r=10){
        PP_Pick2(r);
        PP_Put2(r);
    }

    void PreProcessAdapter(int i, int r=10){
        isTgtOptimise = false;
        if(i==0)PreProcess1(r);
        if(i==1)PreProcess2(r);
        if(i==2)PreProcess3(r);
        if(i==3)PreProcess4(r);
        PostProcess();
        isTgtOptimise = true;
    }

    void PostProcess(){
        while(true){
            string ans2=ans;
            ans = regex_replace(ans, regex("(LDR|RDL)"), "D", regex_constants::format_first_only);
            if(ans.length() ==ans2.length())break;
            else score+=2;
        }
        while(true){
            string ans2=ans;
            ans = regex_replace(ans, regex("(URD|DUR)"), "R", regex_constants::format_first_only);
            if(ans.length() ==ans2.length())break;
            else score+=2;
        }
    }

    void Calc(int _ty, int _tx){
        ty=_ty, tx=_tx;
        rep(i,n) To2(i);
    }

    void OutPut(){puta(ans);}
};


int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    Result b;
    b.Init();
    vector<Result> ps;
    int maxScore=0,i=0;
    for(int d: {2,4,6,8,10}){
        rep(_,4){
            range(ty,d,20)range(tx,d,20){
                ps.push_back(b);
                ps[i].PreProcessAdapter(i%4,d);
                // cerr<<ps.back().ans.length()<<endl;
                ps[i].Calc(ty,tx);
                chmax(maxScore, ps[i].score);
                // cerr<<i<<","<<d<<" ("<<ty<<","<<tx<<") : "<<ps[i].score<<endl;
                i++;
            }
        }
    }
    for(auto p : ps){
        if(p.score==maxScore){
            p.OutPut();
            cerr<<p.score<<endl;
            break;
        }
    }
    return 0;
}