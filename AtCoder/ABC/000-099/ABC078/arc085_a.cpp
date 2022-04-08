#include <bits/stdc++.h>
using namespace std;
int main(){
  int n,m;
  cin>>n>>m;
  cout<<pow(2,m)*(1900*m + 100*(n-m));
}