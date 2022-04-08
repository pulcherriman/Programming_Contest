#include <iostream>
#include <algorithm>
using namespace std;
int main(void){
    // Your code here!
    int a,b,n=1;
    cin>>a>>b;
    for(;a--;){
        n+=min(n,b);
    }
    cout<<n;
}
