#include <iostream>
#include <algorithm>
using namespace std;
int main(void){
    int a,b;
    cin>>a>>b;
    a=(a+11)%13;
    b=(b+11)%13;
    if(a==b)cout<<"Draw";
    else cout<<(a>b?"Alice":"Bob");
}
