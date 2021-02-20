#include <iostream>
#include <vector>
using namespace std;
int main(void){
    int m,n,a,b;
    cin>>n>>m;
    vector<int> x(n,0);
    for(int i=0;i<m;i++){
        cin>>a>>b;
        x[a-1]++,x[b-1]++;
    }
    for(auto i : x){
        cout<<i<<endl;
    }
}
