#include <bits/stdc++.h>
using namespace std;
int main(void){
    int n;
    cin>>n;
    vector<string> s(n);
    for(auto&i:s)cin>>i;
    string t;
    cin>>t;
    int l=0,r=0;
    for(auto i:s){
        auto p=regex_replace(i,regex("\\?"),"a");
        auto q=regex_replace(i,regex("\\?"),"z");
        if(p<=t) l++;
        if(t<=q) r++;
    }
    for(int i=n+1-r;i<=l+1;i++){
        cout<<i<<(i==l+1?"\n":" ");
    }
}
