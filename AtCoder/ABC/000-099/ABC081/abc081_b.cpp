#include <iostream>
using namespace std;
int main(void){
    int n;
    cin>>n;
    
    int num=0,ans=0;
    for(int i=0;i<n;i++){
        int t; cin>>t;
        num|=t;
    }
    while(num%2==0){
        ans++;
        num/=2;
    }
    cout<<ans<<endl;
}
