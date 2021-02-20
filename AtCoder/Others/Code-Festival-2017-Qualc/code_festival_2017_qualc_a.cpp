//#include <bits/stdc++.h>
#include <vector>
#include <list>
#include <queue>
#include <deque>
#include <map>
#include <stack>
#include <bitset>
#include <array>
#include <set>
#include <string>

#include <iterator>
#include <algorithm>
#include <numeric>

#include <ios>
#include <sstream>
#include <iostream>
#include <fstream>

#include <climits>
#include <cmath>

using namespace std;

#define EPS (1e-7)
#define MOD ((int)1e9+7)
#define PI (atan(1.0)*4)

using ll=long long;
using vi=vector<int>;
using vll=vector<ll>;
using vvi=vector<vi>;
using vs=vector<string>;
using pii=pair<int,int>;
using pll=pair<ll,ll>;

void OUT(bool isTrue, string t="YES", string f="NO"){
    cout<<(isTrue?t:f)<<endl;
}
void out(bool isTrue, string t="Yes", string f="No"){
    cout<<(isTrue?t:f)<<endl;
}

template <typename T>
string printItr(T b, T e, string delim=" ")
{
    stringstream ss;
    ostream_iterator<decltype(*b)> out_it(ss, delim.c_str());
    copy(b,e - 1, out_it);
    ss<<*(e-1);
    return ss.str();
}

void bulk(){}
template <class Head, class... Tail>
void bulk(Head& head, Tail&... tail){
    cin>>head;
    bulk(tail...);
}

ll inv_pow(ll x, ll n, ll mod) {
  ll res = 1;
  for(;n>0;n>>=1){
    if(n&1) res=res*x%mod;
    x=x*x%mod;
  }
  return res;
}

void factMod(ll x, ll n, ll mod, vll& v) {
    v.resize(n+1);
    v[0]=1;
    for(int i=1;i<=n;i++){
        v[i]=v[i-1]*(i%mod)%mod;
    }
}

void factInv(ll x, ll n, ll mod, vll& v){
    v.resize(n+1);
    v[x]=inv_pow(x,mod-2,mod);
    for(int i=n;i>=0;i--){
        v[i-1]=v[i]*(x%mod)%mod;
    }
}

#define rep(i,n) for(int i=0;i<n;i++)
#define rrep(i,n) for(int i=n-1;i>=0;i--)
#define range(i,m,n) for(int i=m; i<n;i++)
#define each(i,n) for(auto i:n)
#define all(i) i.begin(),i.end()
#define cint(...) int __VA_ARGS__;bulk(__VA_ARGS__);


int main(void){
    string s;
    cin>>s;
    out(s.find("AC")!=-1);
}