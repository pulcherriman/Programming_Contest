#include <iostream>
#include <algorithm>
using namespace std;
int main(void){
    string s;
    cin>>s;
    replace(s.begin(),s.end(),',',' ');
    cout<<s;
}
