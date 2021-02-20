#include <bits/stdc++.h>
using namespace std;

int main(){
  string s;
  cin>>s;
  if(s.length()!=26){
  	for(char c='a';c<='z';c++){
    	if(s.find(c)==-1){
        	cout<<s<<(char)c<<endl;
          	return 0;
        }
    }
  }else{
  	for(int i=s.size();i>0;i--){
    	if(s[i]>s[i-1]){
          	auto p=s.substr(i);
          	sort(p.begin(),p.end());
          	for(auto c:p){
            	if(s[i-1]<c){
		        	cout<<s.substr(0,i-1)<<c<<endl;
                  	return 0;
                }
            }
        }
    }
  }
  cout<<-1<<endl;
}