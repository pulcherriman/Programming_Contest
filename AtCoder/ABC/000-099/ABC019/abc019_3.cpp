#include <iostream>
#include <set>
#include <algorithm>
using namespace std;
int main(void){
    set<int> v;
    int n;
    cin>>n;
    for(int i=0;i<n;i++){
        int p;
        cin>>p;
        while(p%2==0){
            p>>=1;
        }
        v.insert(p);
    }
    cout<<v.size()<<endl;
}
