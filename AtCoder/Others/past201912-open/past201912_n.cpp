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
#define rep(i,n) for(ll i=0;i<(n);i++)
#define rrep(i,n) for(ll i=(n)-1;i>=0;i--)
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

template<typename T> class segtree {
private:
    int n,sz,h;
    vector<pair<T, int> > node;
    vector<T> lazy;
    void eval(int k) {
        if(lazy[k]){
            node[k].first += lazy[k];
            if(k < n) {
                lazy[k*2] += lazy[k], lazy[k*2+1] += lazy[k];
            }
            lazy[k] = 0;
        }
    }
 
public:
    segtree(const vector<T>& v) : sz((int)v.size()), h(0) {
        n = 1;
        while(n < sz) n *= 2, h++;
        node.resize(2*n, pair<T, int>(numeric_limits<T>::max(), sz));
        lazy.resize(2*n, 0);
        for(int i = 0; i < sz; i++){
            node[i+n] = make_pair(v[i], i);
        }
        for(int i = n-1; i >= 1; i--){
             node[i] = max(node[2*i], node[2*i+1]);
        }
    }
    void range(int a, int b, T x, int k=1, int l=0, int r=-1){
        if(r < 0) r = n;
        eval(k);
        if(b <= l || r <= a){
            return;
        }
        if(a <= l && r <= b){
            lazy[k] += x;
            eval(k);
        }else{
            range(a, b, x, 2*k, l, (l+r)/2);
            range(a, b, x, 2*k+1, (l+r)/2, r);
            node[k] = max(node[2*k], node[2*k+1]);
        }
    }
    pair<T, int> query(int a, int b) {
        a += n, b += n - 1;
        for(int i = h; i > 0; i--) eval(a >> i), eval(b >> i);
        b++;
        pair<T, int> res1 = make_pair(numeric_limits<T>::min(), sz);
        pair<T, int> res2 = make_pair(numeric_limits<T>::min(), sz);
        while(a < b) {
            if(a & 1) eval(a), res1 = max(res1, node[a++]);
            if(b & 1) eval(--b), res2 = max(res2, node[b]);
            a >>= 1, b >>= 1;
        }
        return max(res1, res2);
    }
    void print() {
        for(int i = 0; i < sz; i++){
            pair<T,int> p;
            p = query(i,i+1);
            cout << "st[" << i << "]: " << p.first << " " << p.second << endl;
        }
    }
};

map<ll,ll> zip;
vl unzip;

int compress(vector<ll> &x) {
    sort(x.begin(), x.end());
    x.erase(unique(x.begin(),x.end()),x.end());
    // puta(x);
    unzip = vl(x.size(),0);
    for(int i = 0; i < x.size(); i++){
        zip[x[i]] = i;
        unzip[i] = x[i];
    }
    return x.size();
}


int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    ll n,w,c;
    cin>>n>>w>>c;
    vl l(n),r(n),v(n);
    vl p;
    ll ow=w;

    rep(i,n){
        cin>>l[i]>>r[i]>>v[i];
        p.push_back(l[i]);
        p.push_back(max(0,l[i]-c+1));
        p.push_back(r[i]);
    }
    p.push_back(0);
    w = compress(p);

    segtree<ll> st(vl(w+1,0));

    rep(i,n){
        st.range(zip[max(0,l[i]-c+1)], zip[r[i]], v[i]);
    }
    ll ans=LINF;
    // rep(i,w)puta(unzip[i],c,w, st.query(i,i+1).fs);
    rep(i,w){
        if(unzip[i]+c>ow)break;
        chmin(ans, st.query(i,i+1).fs);
    }
    puta(ans);

    return 0;
}