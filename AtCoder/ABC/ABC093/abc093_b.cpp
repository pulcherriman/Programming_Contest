#include <bits/stdc++.h>
using namespace std;

int main(){
  int a,b,l;
  cin>>a>>b>>l;
  set<int> s;
  for(int i=a;i<=b;i++){
  	if(i<a+l or i>b-l) s.insert(i);
  }
  for(auto i:s)cout<<i<<endl;
}