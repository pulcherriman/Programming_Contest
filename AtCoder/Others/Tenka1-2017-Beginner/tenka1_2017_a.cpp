#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
int main(void){
    string s;
    cin>>s;
    cout<<count(s.begin(),s.end(),'1');
}
