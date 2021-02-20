#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
int main(void){
    string s="aiueo",c;
    cin>>c;
    cout<<(s.find(c)==-1?"consonant":"vowel");
}
