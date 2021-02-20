#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
#include <set>
#include <iterator>
using namespace std;
int main(void){
    string s;
    cin>>s;
    for(auto c:s){
        if(s.find(c)!=s.rfind(c)){
            cout<<"no";
            return 0;
        }
    }
    cout<<"yes";
}
