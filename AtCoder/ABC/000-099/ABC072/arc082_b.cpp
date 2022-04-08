#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main(void){
    int n,ans=0;
    cin>>n;
    vector<int> v(n);
    for(int i=0;i<n;i++){
        cin>>v[i];
    }
    for(int i=0;i<n;i++){
        if(v[i]==i+1){
            ans++;
            if(i+1!=n){
                swap(v[i],v[i+1]);
            }
        }
    }
    cout<<ans;
}
