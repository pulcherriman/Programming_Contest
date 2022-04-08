#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
#include <set>
#include <iterator>
using namespace std;
int main(void){
    int n,m,p,q;
    set<int> a,b,r;
    cin>>n>>m;
    for(;m--;){
        cin>>p>>q;
        if(p==1)a.insert(q);
        if(q==n)b.insert(p);
    }
    set_intersection(a.begin(),a.end(),b.begin(),b.end(),inserter(r,r.end()));
    if(r.size()!=0){
        cout<<"POSSIBLE";
    }else{
        cout<<"IMPOSSIBLE";
    }
}
