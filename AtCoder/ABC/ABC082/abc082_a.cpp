#include <bits/stdc++.h>
using namespace std;
constexpr int lcm(int a,int b){return b?lcm(b,a%b):a;}
constexpr int gcd(int a,int b){return a*b/lcm(a,b);}
 
int main(void){
    float a,b;
    cin>>a>>b;
    cout<<(int)ceil((a+b)/2)<<endl;
}