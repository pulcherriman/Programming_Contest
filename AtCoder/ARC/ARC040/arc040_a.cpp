#include <iostream>
#include <algorithm>
#include <string>
using namespace std;
int main(void){
    int n,a=0,b=0;
    string s;
    cin>>n;
    for(;n--;){
        cin>>s;
        a+=count(s.begin(),s.end(),'R');
        b+=count(s.begin(),s.end(),'B');
    }
    cout<<(a!=b?a>b?"TAKAHASHI":"AOKI":"DRAW")<<"\n";
}
