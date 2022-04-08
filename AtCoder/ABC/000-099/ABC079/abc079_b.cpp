#include <bits/stdc++.h>
using namespace std;
using ll=long long;
int main(void){
    // Your code here!
    int n;
    vector<ll> ryuka={2,1};
    cin>>n;
    for(int i=2;i<=n;i++){
        ryuka.push_back(ryuka[i-1]+ryuka[i-2]);
    }
    cout<<ryuka[n];
}
