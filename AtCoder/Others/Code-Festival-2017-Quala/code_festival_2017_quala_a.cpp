#include <iostream>
#include <string>
using namespace std;
int main(void){
    string str;
    cin>>str;
    if(str.find("YAKI") == 0){
        cout<<"Yes";
    }else{
        cout<<"No";
    }
}
