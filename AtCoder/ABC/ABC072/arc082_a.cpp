#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main(void){
    int n;
    vector<int> v(100002,0);
    cin>>n;
    for(;n--;){
        int p;
        cin>>p;
        v[p]++;
        v[p+1]++;
        v[p+2]++;
    }
    cout<<v[max_element(v.begin(),v.end())-v.begin()];
    
}
