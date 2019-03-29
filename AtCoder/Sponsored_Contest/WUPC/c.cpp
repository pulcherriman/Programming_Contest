// not accepted
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vb = vector<bool>;
using vvb = vector<vb>;
using vd = vector<double>;
using vvd = vector<vd>;
using vi = vector<int>;
using vvi = vector<vi>;
using vl = vector<ll>;
using vvl = vector<vl>;
using pll = pair<ll, ll>;
using tll = tuple<ll, ll>;
using tlll = tuple<ll, ll, ll>;
using vs = vector<string>;
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

int dx[] = { 1,0,-1,0,1,-1,-1,1 }, dy[] = { 0,1,0,-1,1,1,-1,-1 };
template<class T>bool chmax(T&a, T b) { if (a<b) { a = b; return true; }return false; }
template<class T>bool chmin(T&a, T b) { if (a>b) { a = b; return true; }return false; }
template<class S>S sum(vector<S>&a) { return accumulate(all(a), S()); }
template<class S>S max(vector<S>&a) { return *max_element(all(a)); }
template<class S>S min(vector<S>&a) { return *min_element(all(a)); }
ll max(int a, ll b) { return max((ll)a, b); } ll max(ll a, int b) { return max(a, (ll)b); }

template<class T>void puta(T&&t) { cout << t << "\n"; }
template<class H, class...T>void puta(H&&h, T&&...t) { cout << h << ' '; puta(t...); }
template<class S, class T>void tf(bool b, S t, T f) { if (b)puta(t); else puta(f); }
void YN(bool b) { tf(b, "YES", "NO"); }
void Yn(bool b) { tf(b, "Yes", "No"); }
void yn(bool b) { tf(b, "yes", "no"); }
template<class S, class T>ostream&operator<<(ostream&os, pair<S, T>p) { os << "[" << p.first << ", " << p.second << "]"; return os; };
template<class S>auto&operator<<(ostream&os, vector<S>t) { bool a = 1; for (auto s : t) { os << (a ? "" : " ") << s; a = 0; }return os; }
template<class S>auto&operator >> (istream&is, vector<S>&t) { for (S&a : t)cin >> a; return is; }

/*他のライブラリを入れる場所*/
vi ans;
ll n, m;
vector<set<int>> as;

void solve(int p) {
 vi t;
 int q = 0;
 for (auto&ch : as[p]) {
  if (!as[ch].size()) {
   q++;
   t.push_back(ch);
  }
 }
 if (q == 0) {
  for (auto&ch : as[p]) {
   if (as[p].size()==1) as[ch].insert(p);
   as[p].erase(ch);
   solve(ch);
  }
 }
 else {
  t.push_back(p);
  rep(i, t.size()) {
   ans[t[i]] = t[(i + 1) % t.size()];
  }
  for (auto&ch : as[p]) {
   if (as[ch].size()) {
    as[p].erase(ch);
    solve(ch);
   }
  }
 }
}

int main() {
 cin.tie(0);
 ios::sync_with_stdio(false);

 cin >> n >> m;
 vvi adj(n);
 rep(i, m) {
  int a, b;
  cin >> a >> b;
  a--, b--;
  adj[a].push_back(b);
  adj[b].push_back(a);
 }
 vi used(n, 0);
 queue<int> q;
 q.push(0);
 as.resize(n);
 while (!q.empty()) {
  int p = q.front();
  q.pop();
  if (used[p]==2)continue;
  used[p] = 2;
  for (auto&i : adj[p]) {
   if (!used[i]) {
    used[i] = 1;
    q.push(i);
    as[p].insert(i);
   }
  }
 }
 // rep(i,n){cout<<i<<":";
 // for(auto&j:as[i])cout<<j<<",";
 // cout<<endl;}
 ans.assign(n, -1);
 solve(0);
 rep(i, n)ans[i]++;
 puta(ans);
 return 0;
}