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


#define rep(i,n) for(int i=0;i<n;i++)
#define rrep(i,n) for(int i=n-1;i>=0;i--)
#define range(i,m,n) for(int i=m, i<n;i++)
#define each(i,n) for(auto i:n)
#define all(i) i.begin(),i.end()

#define makevv(i,j,k,l,m) vector<vector<i>> j(k,vector<i>(l,m))

using vi=std::vector<int>;
using vvi=std::vector<vi>;
using pii=std::pair<int,int>;
using ll=long long;


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
    int a,b,c;
    cin>>a>>b>>c;
    if(a==b){
        cout<<c;
    }else if(a==c){
        cout<<b;
    }else cout<<a;

}