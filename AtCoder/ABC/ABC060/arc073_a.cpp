#include <iostream>
#include <string>
using namespace std;
int main(void){
 unsigned long long n,t,a,b,ans=0;
 cin>>n>>t>>a;
 for(int i=0;i<n-1;i++){
     cin>>b;
     if(b-a>t){
         ans+=t;
     }else ans+=(b-a);
     a=b;
 }
 cout<<ans+t;
}