// #pragma GCC optimize "O3" /* 最適化 */
// #pragma GCC target "avx" /* SIMD(ベクトル化) */

#include<bits/stdc++.h>

using namespace std;

using vi=vector<int>;

#define rep(i,n) for(int i=0;i<((int)n);++i)
#define range(i,a,n) for(int i=a;i<((int)n);++i)

int main(){
	cin.tie(NULL);
	cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	int n, k; cin>>n>>k;
	vi a(n);
	rep(i,n) cin>>a[i];

	priority_queue<int,vector<int>,greater<int>> pq;

	rep(i,k){
		pq.push(a[i]);
	}
	
	range(i,k,n+1){
		cout<<pq.top()<<'\n';
		if(i<n){
			pq.push(a[i]);
			pq.pop();
		}
	}
}
