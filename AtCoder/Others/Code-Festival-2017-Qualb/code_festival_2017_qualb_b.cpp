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

int main(void){/*
    makevv(int,v,4,4,0);
    rep(i,4){
        iota(all(v[i]),i*4);
    }
    each(p,v){
        cout<<printItr(all(p),"+")<<"="<<accumulate(all(p),0)<<endl;
    }
    vi nv(3,0);
    each(&n,nv){
        n++;
    }
    cout<<printItr(all(nv))<<endl;
    each(n,nv){
        n++;
    }
    cout<<printItr(all(nv),",")<<endl;*/
    int n,m;
    cin>>n;
    multiset<int> a;
    rep(i,n){int p;cin>>p;a.insert(p);}
    cin>>m;
    multiset<int> b;
    rep(i,m){int p;cin>>p;b.insert(p);}
    multiset<int> r;
    set_difference(b.begin(), b.end(),
                      a.begin(), a.end(),
                      std::inserter(r, r.end()));
    if(r.empty()){
        cout<<"YES";
    }else cout<<"NO";
    
}