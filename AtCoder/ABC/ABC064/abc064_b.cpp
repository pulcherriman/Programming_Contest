#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main(){
 vector<int> num;
 int n;
 cin>>n;
 for(int i=0;i<n;i++){
  int p;
  cin>>p;
  num.push_back(p);
 }
 sort(num.begin(),num.end());
 cout<<num.back()-num.front();
}