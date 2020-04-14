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
#define MOD (998244353ll)
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
	ll testcase,b;
    string res;
	cin>>testcase>>b;
	rep(_,testcase){
	    ll turn=0;
	    vvl ans(1,vl(b,2));
	    bool ac=false;
	    while(turn<150){
            bool fin=ans.size()==1;
            rep(i,b)fin&=ans[0][i]!=2;
            if(fin){
                rep(i,b)cout<<ans[0][i];
                cout<<endl;
                cin>>res;
                if(res=="N")return 0;
                else {ac=true; break;}
            }
	        turn++;
            // {
            //     puta("Turn: ", turn);
            //     rep(i,ans.size()){
            //        cout<<i+1<<": ";
            //        rep(j,b)cout<<ans[i][j];
            //        cout<<endl;
            //     }
            // }

	        if(turn>=11 and turn%10 == 1){
	            //量子の揺らぎ
	            vl tmp(b);
	            rep(i,b)tmp[i]=ans[0][b-1-i];
	            if(ans[0]!=tmp)ans.push_back(tmp);
	            rep(i,b)tmp[i]=ans[0][i]==2 ? 2 : 1-ans[0][i];
	            if(ans[0]!=tmp)ans.push_back(tmp);
	            rep(i,b)tmp[i]=ans[0][b-1-i]==2 ? 2 : 1-ans[0][b-1-i];
	            if(ans[0]!=tmp)ans.push_back(tmp);
	        }
	        if(ans.size()==1){
	            rep(i,b){
	                if(ans[0][i]==2){
	                    cout<<i+1<<endl;
	                    cin>>res;
	                    if(res=="N")return 0;
	                    ans[0][i]=res[0]-'0';
	                    break;
	                }
	                if(ans[0][b-1-i]==2){
	                    cout<<b-i<<endl;
	                    cin>>res;
	                    if(res=="N")return 0;
	                    ans[0][b-1-i]=res[0]-'0';
	                    break;
	                }
	            }
	            
	        }else{
	            bool del=false;
	            rep(i,b){
	                bool ng=true;
	                for(auto&a:ans)ng&=(a[i]==ans[0][i]);
	                if(ng)continue;
	                cout<<i+1<<endl;
	                cin>>res;
	                if(res=="N")return 0;
	                rep(cnt,ans.size()){
	                    if(cnt>=ans.size())break;
	                    if(ans[cnt][i]!=res[0]-'0'){
	                        range(j,cnt+1,ans.size()){
	                            ans[j-1]=ans[j];
	                        }
	                        ans.pop_back();
	                        cnt--;
        	                del=true;
	                    }
	                }
	                break;
	            }
	            if(!del)return 0;
	        }
	    }
	    if(!ac)return 0;
	}

	return 0;
}