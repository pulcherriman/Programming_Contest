#include <bits/stdc++.h>
using namespace std;
int main(void){
    // Your code here!
    int n;
    cin>>n;
    if((n%1000)%111==0 || (n/10)%111==0){
        cout<<"Yes";
    }else cout<<"No";
}
