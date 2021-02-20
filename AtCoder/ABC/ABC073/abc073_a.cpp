#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
int main(void){
int a;
cin>>a;
cout<<((a%10==9 || a/10==9)?"Yes":"No");
}
