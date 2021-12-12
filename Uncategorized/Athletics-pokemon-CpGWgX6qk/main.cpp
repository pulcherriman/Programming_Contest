/*
 * Unsecured Optimization
 */
// #pragma GCC target "avx"
// #pragma GCC target "sse4.2"
// #pragma GCC optimize "O3"
// #pragma GCC optimize "fast-math"
// #pragma GCC optimize "unroll-loops"
#ifdef _DEBUG
#define _GLIBCXX_DEBUG 1
#endif

/* 
 * Include Headers
 */
#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using vl=vector<ll>;
using vvl=vector<vl>;

/*
 * Macros
 */
#define all(a) a.begin(),a.end()
#define rall(a) a.rbegin(),a.rend()
#define __LOOPSWITCH(_1, _2, _3, __LOOPSWITCH, ...) __LOOPSWITCH
#define rep(...) __LOOPSWITCH(__VA_ARGS__, __RANGE, __REP, __LOOP) (__VA_ARGS__)
#define rrep(...) __LOOPSWITCH(__VA_ARGS__, __RRANGE, __RREP, __LOOP) (__VA_ARGS__)
#define __LOOP(q) __LOOP2(q, __LINE__)
#define __LOOP2(q,l) __LOOP3(q,l)
#define __LOOP3(q,l) __REP(_lp ## l,q)
#define __REP(i,n) __RANGE(i,0,n)
#define __RANGE(i,a,n) for(ll i=((ll)a);i<((ll)n);++i)
#define __RREP(i,n) __RRANGE(i,0,n)
#define __RRANGE(i,a,n) for(ll i=((ll)n-1);i>=((ll)a);--i)

/*
 * Utilities
 */
template<class T>constexpr bool chmax(T&a,T b){return a<b?a=b,1:0;}
template<class S>S max(vector<S>&a){return *max_element(all(a));}

// ここにライブラリを貼る


int main(){
	cin.tie(nullptr);
	ios::sync_with_stdio(false);
	
	ll step, n;
	cin>>step>>n;
	
	vl a(n);
	rep(i,n) cin>>a[i];

	// 後ろから見る
	vvl ans(n, vl(n+1, -1));
	ans[n-1][0]=ans[n-1][1]=0;

	rrep(i,1,n){
		rep(j,n+1)if(ans[i][j]!=-1){
			chmax(ans[i-1][j], ans[i][j] + j * a[i-1]);
			if(j+1<=n) chmax(ans[i-1][j+1], ans[i][j]);
		}
	}
	cout<<max(ans[0])<<endl;
}
