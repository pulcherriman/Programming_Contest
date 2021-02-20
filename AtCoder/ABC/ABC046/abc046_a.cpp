#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
int main(void){
    vector<int> a(3);
    for(auto &i : a)cin>>i;
    sort(a.begin(),a.end());
    if(a[0]==a[2])cout<<1;
    else if(a[0]==a[1]||a[1]==a[2])cout<<2;
    else cout<<3;
}
