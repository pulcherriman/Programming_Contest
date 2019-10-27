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
typedef double Type;
typedef vector<vector<Type>> Matrix;
int GetRank(Matrix a) {
        int h = a.size(), w = a[0].size();
        int res = 0, now = 0;
        for (int i = 0; i < h; i ++) {
                Type ma = 0.0;
                int pivot;
                for (int j = i; j < h; j ++) {
                        if (a[j][now] > ma) {
                                ma = a[j][now];
                                pivot = j;
                        }
                }
                if (ma == 0.0) {
                        now ++;
                        if (now == w) break;
                        i --;
                        continue;
                }
                if (pivot != i) {
                        for (int j = 0; j < w; j ++) { 
                                swap(a[i][j], a[pivot][j]);
                        }

                }
                Type tmp = 1.0 / a[i][now];
                for (int j = 0; j < w; j ++) a[i][j] *= tmp;
                for (int j = 0; j < h; j ++) {
                        if (i != j) {
                                Type tmp2 = a[j][now];
                                for (int k = 0; k < w; k ++) {
                                        a[j][k] -= a[i][k] * tmp2;
                                }
                        }
                }
                res ++;
        }
        return res;
}
bool Inv(Matrix a, Matrix &inv) {
        assert(a.size() == a[0].size() && inv.size() == inv[0].size());
        int n = a.size();
        for (int i = 0; i < n; i ++) {
                for (int j = 0; j < n; j ++) {
                        inv[i][j] = (i == j ? 1.0 : 0.0);
                }
        }
        for (int i = 0; i < n; i ++) {
                Type ma = 0.0;
                int pivot;
                for (int j = i; j < n; j ++) { 
                        if (a[j][i] > ma) {
                                ma = a[j][i];
                                pivot = j;
                        }
                }
                if (ma == 0.0) return false;
                if (pivot != i) {
                        for (int j = 0; j < n; j ++) { 
                                swap(a[i][j], a[pivot][j]);
                                swap(inv[i][j], inv[pivot][j]);
                        }

                }
                Type tmp = 1.0 / a[i][i];
                for (int j = 0; j < n; j ++) {
                        a[i][j] *= tmp;
                        inv[i][j] *= tmp;
                }
                for (int j = 0; j < n; j ++) {
                        if (i != j) {
                                Type tmp2 = a[j][i];
                                for (int k = 0; k < n; k ++) {
                                        a[j][k] -= a[i][k] * tmp2;
                                        inv[j][k] -= inv[i][k] * tmp2;
                                }
                        }
                }
        }
        return true;
}
Matrix Add(const Matrix &a, const Matrix &b, bool minus = false) {
        assert(a.size() == b.size() && a[0].size() == b[0].size());
        int h = a.size(), w = a[0].size();
        Matrix c(h, vector<Type> (w));
        for (int i = 0; i < h; i ++) {
                for (int j = 0; j < w; j ++) {
                        c[i][j] = a[i][j] + (minus ? -1 : 1) * b[i][j];
                }
        }
        return c;
}
Matrix Sub(const Matrix &a, const Matrix &b) {
        return Add(a, b, true);
}
Matrix Mul(const Matrix &a, const Matrix &b) {
        assert(a[0].size() == b.size());
        Matrix c(a.size(), vector<Type> (b[0].size()));
        for (int i = 0; i < a.size(); i ++) {
                for (int k = 0; k < b.size(); k ++) {
                        for (int j = 0; j < b[0].size(); j ++) {
                                c[i][j] = (c[i][j] + a[i][k] * b[k][j]);
                        }
                }
        }
        return c;
}
Matrix Pow(Matrix a, long long n) {
        assert(a.size() == a[0].size());
        Matrix b(a.size(), vector<Type> (a.size()));
        for (int i = 0; i < a.size(); i ++) {
                b[i][i] = 1;
        }
        while (n > 0) {
                if (n & 1) b = Mul(b, a);
                a = Mul(a, a);
                n >>= 1;
        }
        return b;
}
void PrintMatrix(const Matrix &a) {
        int h = a.size(), w = a[0].size();
        for (int i = 0; i < h; i ++) {
                for (int j = 0; j < w; j ++) {
                        cout << a[i][j] << ' ';
                }
                cout << endl;
        }
}

int main(){
	cin.tie(0);
	ios::sync_with_stdio(false);
	ll n;
	cin>>n;
	Matrix a(n),b(n),c(n),ainv(n);
	rep(i,n){a[i].resize(n,0);rep(j,n){char ch;cin>>ch;a[i][j]=ch-'0';}}
	rep(i,n){b[i].resize(n,1);}
	rep(i,n){c[i].resize(n,0);rep(j,n){char ch;cin>>ch;c[i][j]=ch-'0';}}
	rep(i,n)rep(j,n)if(c[i][j]==0){
		rep(k,n)if(a[i][k]!=0){
			b[k][j]=0;
		}
	}

	rep(i,n){
		vector<Type> check(n,0);
		rep(j,n)if(a[i][j]==1){
			rep(k,n)if(b[j][k]!=0)check[k]=1;
		}
		if(c[i]!=check){
			puta(-1);
			return 0;
		}
	}

	rep(i,n){rep(j,n)cout<<b[i][j];cout<<endl;}

	

	return 0;
}