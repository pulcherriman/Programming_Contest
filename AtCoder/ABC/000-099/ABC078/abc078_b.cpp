#include <bits/stdc++.h>
using namespace std;
int main(){
  int x,y,z;
  cin>>x>>y>>z;
  x-=z;
  for(int i=0;true;i++){
    if(x<(y+z)*i){
      cout<<i-1;
      break;
    }
  }
}