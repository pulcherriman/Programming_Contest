#include <iostream>
#include <algorithm>
using namespace std;
int main(void){
    int n,k,ans=0;
    cin>>n>>k;
    for(int i=0;i<n;i++){
        int p;
        cin>>p;
        ans+=min(p,k-p);
    }
    cout<<ans*2;
}
