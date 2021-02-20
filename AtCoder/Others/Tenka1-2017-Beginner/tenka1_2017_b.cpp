#include <iostream>
using namespace std;
int main(void){
    int a=0,b,n;
    cin>>n;
    for(;n--;){
        int p,q;
        cin>>p>>q;
        if(a<p){
            a=p,b=q;
        }
    }
    cout<<a+b;
}
