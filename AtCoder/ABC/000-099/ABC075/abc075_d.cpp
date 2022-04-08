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

#define rep(i,n) for(int i=0;i<n;i++)
#define rrep(i,n) for(int i=n-1;i>=0;i--)
#define range(i,m,n) for(int i=m; i<n;i++)
#define each(i,n) for(auto i:n)
#define all(i) i.begin(),i.end()

#define makevv(i,j,k,l,m) vector<vector<i>> j(k,vector<i>(l,m))

using ll=long long;

using vi=std::vector<int>;
using vvi=std::vector<vi>;
using pii=std::pair<int,int>;
using pll=std::pair<ll,ll>;


template <typename T>
std::string printItr(T b, T e, std::string delim=" ")
{
    std::stringstream ss;
    std::ostream_iterator<decltype(*b)> out_it(ss, delim.c_str());
    std::copy(b,e - 1, out_it);
    ss<<*(e-1);
    return ss.str();
}
using namespace std;

int main(void){
    ll ans=LLONG_MAX;
    int n,k;
    cin>>n>>k;
    vector<pll> p(n);
    rep(i,n){
        cin>>p[i].first>>p[i].second;
    }
    sort(all(p));
    vector<ll> yp(n);
    rep(i,n)yp[i]=p[i].second;
    rep(i,n){
        range(j,i+1,n){
            if(j-i+1<k)continue;
            ll x=p[j].first-p[i].first,y=LLONG_MAX;
            vector<ll> tmp;
            range(l,i,j+1){
                tmp.push_back(yp[l]);
            }
            sort(all(tmp));
            rep(l,j-i+1-k+1){
                y=min(y,tmp[l+k-1]-tmp[l]);
            }
            ans=min(ans,x*y);
        }
    }
    cout<<ans;
}