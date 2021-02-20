#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
#include <set>
#include <iterator>
using namespace std;
int main(void){
    string a,b,c;
    cin>>a>>b>>c;
    a=a[0];
    a+=b[0];
    a+=c[0];
    
    for_each(a.begin(),a.end(),[](char &c){return c=toupper(c);});
    cout<<a;
}
