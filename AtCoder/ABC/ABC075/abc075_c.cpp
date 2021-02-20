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
    int n,m,ans=0;
    cin>>n>>m;
    vector<vector<int>> lst(n);
    vector<vector<int>> edge(m);
    for(int i=0;i<m;i++){
        int a,b;
        cin>>a>>b;
        lst[a-1].push_back(b-1);
        lst[b-1].push_back(a-1);
        edge[i]={a-1,b-1};
    }
    each(e,edge){
        queue<int> stk;
        vi cost(n,0);
        stk.push(0);
        while(!stk.empty()){
            cost[stk.front()]=1;
            each(i,lst[stk.front()]){
                if(cost[i]==0 && (stk.front()!=e[0] || i!=e[1]) && (stk.front()!=e[1] || i!=e[0])){
                    stk.push(i);
                }
            }
            stk.pop();
        }
        bool is=false;
        each(i,cost){
            is|=(i==0);
        }
        if(is)ans++;
    }
    cout<<ans;


}