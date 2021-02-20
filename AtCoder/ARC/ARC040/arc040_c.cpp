#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;
int main(void){
    int n,cost=0;
    cin>>n;
    vector<string> f(n);
    for(auto &s : f){
        cin>>s;
    }
    for(int i=0;i<n;i++){
        for(int j=n-1;j>=0;j--){
            if(i==n)break;
            if(f[i][j]=='.'){
                cost++;
                i++;
            }
        }
    }
    cout<<cost<<endl;
}
