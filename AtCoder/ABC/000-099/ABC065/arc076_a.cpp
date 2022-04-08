#include <iostream>
using namespace std;
int main(void){
    int n,m;
    cin>>n>>m;
    unsigned long long a[100001]={1,1};
    for(int i=2;i<=100000;i++){
        a[i]=a[i-1]*i%1000000007;
    }
 
    if(n==m){
        a[0]=a[n]*a[m]*2%1000000007;
        cout<<a[0];
    }else if(n-m==1 || m-n==1){
        a[0]=a[n]*a[m]%1000000007;
        cout<<a[0];
    }else
        cout<<0;
    
}