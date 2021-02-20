#include <bits/stdc++.h>
using namespace std;
constexpr int lcm(int a,int b){return b?lcm(b,a%b):a;}
constexpr int gcd(int a,int b){return a*b/lcm(a,b);}

int main(void){
    string a,b;
    cin>>a>>b;
    sort(a.begin(),a.end());
    sort(b.rbegin(),b.rend());
    cout<<(a<b?"Yes":"No")<<endl;
}
