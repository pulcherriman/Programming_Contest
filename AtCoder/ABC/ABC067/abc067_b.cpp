#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main(void){
    int m,n,ans=0;
    cin>>m>>n;
    vector<int> ar(m);
    for(auto &i : ar){
        cin>>i;
    }
    sort(ar.begin(),ar.end(),[](int a, int b){return a>b;});
    for(int i=0;i<n;i++)
        ans+=ar[i];
    cout<<ans;
}
