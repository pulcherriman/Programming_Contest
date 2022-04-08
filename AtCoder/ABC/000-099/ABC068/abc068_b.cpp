#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
using namespace std;
int main(void){
    int n;
    cin>>n;
    cout<<(1<<(int)floor(log2(n)));
}
