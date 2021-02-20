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

using namespace std;

using ll=long long;

using vi=vector<int>;
using vvi=vector<vi>;
using pii=pair<int,int>;
using pll=pair<ll,ll>;

void OUT(bool isTrue, string t="YES", string f="NO"){
    cout<<(isTrue?t:f)<<endl;
}
void out(bool isTrue, string t="yes", string f="yes"){
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

int main(void){
    vi a(3),b={5,5,7};
    cin>>a[0]>>a[1]>>a[2];
    sort(all(a));
    OUT(a==b);
}