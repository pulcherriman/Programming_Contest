#include <iostream>
#include <vector>
#include <vector>
#include <algorithm>
using namespace std;
int main(void){
    int n,c,ans=0;
    cin>>n>>c;
    vector<int> a,u(n,0);
    for(int i=0;i<n;i++){
        int tmp;
        cin>>tmp;
        a.push_back(tmp);
    }
    sort(a.begin(),a.end());
    for(int i=n-1;i>=0;i--){
        if(u[i]==1)continue;
        ans++;
        u[i]=1;
        int ind=upper_bound(a.begin(),a.end(),c-a[i]-1)-a.begin()-1;
        while(ind>=0){
            if(u[ind]==0){
                u[ind]=1;
                break;
            }else{
                ind--;
            }
        }
    }
    cout<<ans;
}