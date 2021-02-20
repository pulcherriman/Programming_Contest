#include <iostream>
#include <string>
using namespace std;
int main(void){
    int n,f=0;
    string str,ns="";
    cin>>n>>str;
    for(auto c:str){
        if(c=='('){
            f++;
        }else{
            if(f!=0){
                f--;
            }else{
                ns+=')';
            }
        }
    }
    for(int i=0;i<ns.length();i++){cout<<'(';}
    cout<<str;
    for(;f--;){cout<<')';}
}
