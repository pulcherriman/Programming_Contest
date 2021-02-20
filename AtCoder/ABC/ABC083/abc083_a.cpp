#include <iostream>
using namespace std;
int main(void){
    // Your code here!
    int a,b,c,d;
    cin>>a>>b>>c>>d;
    a+=b;c+=d;
    if(a==c)cout<<"Balanced";
    else if(a>c) cout<<"Left";
    else cout<<"Right";
}
