#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using vd = vector<double>;
using vvd = vector<vd>;
using vl = vector<ll>;
using vvl = vector<vl>;
using pii = pair<int, int>;
using vs = vector<string>;
#define rep(i,n) range(i,0,n)
#define range(i,a,n) for(int i=a;i<n;i++)
#define all(a) a.begin(),a.end()
#define LINF    	((ll)1ll<60)
#define INF     	((int)1<<30)
#define EPS     	(1e-9)
#define MOD     	(1000000007)
#define fcout(a)	cout<<setprecision(a)<<fixed
#define fs 			first
#define sc			second
#define PI 3.1415926535897932384

template<class S, class T>ostream& operator<<(ostream&os, pair<S, T>p) { os << "[" << p.first << ", " << p.second << "]"; return os; };
template<class S>auto&operator<<(ostream&os, vector<S>t) { bool a = 1; for (auto s : t) { os << (a ? "" : " ") << s; a = 0; } return os; }


//int dx[]={1,1,1,0,-1,-1,-1,0},dy[8]={1,0,-1,-1,-1,0,1,1,1};
//
constexpr ll gcd(ll a, ll b) { return b ? gcd(b, a%b) : a; }
//

int main() {
	cin.tie(0); ios::sync_with_stdio(false);
	ll a, b;
	ll ans = 0;
	cin >> a >> b;
	vl odd,even;
	for (ll i = a; i <= b; i++) {
		(i&1?odd:even).push_back(i);
	}
	vector<vector<bool>> judge(odd.size(), vector<bool>(odd.size(), true));
	rep(j, odd.size()) {
		rep(k, j) {
			if (gcd(odd[j], odd[k]) != 1ll) {
				judge[j][k] = judge[k][j] = false;
			}
		}
	}
	vi judge_e(even.size(),0);
	rep(i,even.size()){
		rep(j,odd.size()){
			if(gcd(even[i],odd[j])==1)judge_e[i]|=(1<<j);
		}
	}

	rep(i, 1 << odd.size()) {
		vi tmp;
		int p=i;
		while(p) {
			tmp.push_back(__builtin_ctzll(p));
			p&=p-1;
		}

		bool fl = true;
		rep(j, tmp.size()) {
			rep(k, j) {
				if (!judge[tmp[j]][tmp[k]]) {
					fl = false;
					break;
				}
			}
		}
		if (fl) {
			ans++;
			rep(j,even.size()) {
				if((judge_e[j]&i)==i)ans++;
			}
		}
	}
	cout << ans << endl;

}