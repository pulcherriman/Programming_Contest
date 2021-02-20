#include <iostream>
#include <string>
#include <algorithm>

int main(){
 std::string s,l="aiueo";
 std::cin>>s;
 for(auto c:s){
  if(l.find(c)==-1)
   std::cout<<c;
 }
 std::cout<<"\n";
}