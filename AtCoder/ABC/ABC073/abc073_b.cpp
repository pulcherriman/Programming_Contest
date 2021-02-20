#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
int main(void){
    int n,ans=0;
    cin>>n;
    for(;n--;){
        int p,q;
        cin>>p>>q;
        ans+=q+1-p;
    }
    cout<<ans;
}
