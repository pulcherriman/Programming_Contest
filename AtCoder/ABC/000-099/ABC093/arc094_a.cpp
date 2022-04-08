#include <bits/stdc++.h>
using namespace std;
int main(void){
    // Your code here!
    vector<int> a(3);
    cin>>a[0]>>a[1]>>a[2];
    sort(a.begin(),a.end());
    int ans=0;
    if(a[2]%2!=a[1]%2 or a[2]%2!=a[0]%2){
        if(a[0]%2==a[1]%2){
            a[0]++; a[1]++;
        }else if(a[0]%2==a[2]%2){
            a[0]++; a[2]++;
        }else{
            a[1]++;a[2]++;
        }
        ans=1;
    } 
    cout<<ans+(a[2]-a[1])/2+(a[2]-a[0])/2<<endl;
    
}
