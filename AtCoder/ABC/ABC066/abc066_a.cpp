#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
  vector<int> a(3);
  for(auto &i :a){
    cin>>i;
  }
  sort(a.begin(),a.end());
  cout<<a[0]+a[1];
}