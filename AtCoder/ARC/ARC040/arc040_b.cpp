#include <iostream>
#include <vector>
#include <string>
using namespace std;
int main(void){
    int n,r,cost;
    string s;
    cin>>n>>r>>s;
    cost=max((int)s.rfind(".")-r+1,0);
    for(int i=0;i<n;i++){
        if(s[i]=='.'){
            cost++;
            i+=r-1;
        }
    }
    cout<<cost<<"\n";
}
