#include <iostream>
#include <algorithm>
#include <map>
using namespace std;
int main(void){
    int n,ans=0;
    cin>>n;
    map<int,int> mp;
    for(;n--;){
        int p;
        cin>>p;
        if(mp.find(p)==mp.end()){
            mp[p]=1;
        }else{
            mp[p]++;
        }
        if(mp[p]%2==1){
            ans++;
        }else{
            ans--;
        }
    }
    cout<<ans;
}
