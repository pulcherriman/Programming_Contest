#include <iostream>
#include <vector>
#include <algorithm>
#define ll long long
using namespace std;
int main(void){
    int n;
    ll p=((ll)1<<50);
    cin>>n;
    vector<ll> ar(n+1,0);
    for(int i=1;i<=n;i++)cin>>ar[i];
    for(int i=1;i<=n;i++){
        ar[i]+=ar[i-1];
    }
    for(int i=1;i<n;i++){
        //cout<<ar[i]<<","<<ar[n]-ar[i]<<endl;
        if(p>llabs(ar[n]-ar[i]*2))p=llabs(ar[n]-ar[i]*2);
    }
    cout<<p;
}
