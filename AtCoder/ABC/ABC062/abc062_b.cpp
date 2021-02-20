#include <iostream>
#include <string>
using namespace std;
int main(void){
    int h,w;
    cin>>h>>w;
    for(int i=0;i<w+2;i++){
        cout<<"#";
    }
    cout<<endl;
    string s;
    for(int i=0;i<h;i++){
        cin>>s;
        cout<<"#"<<s<<"#"<<endl;
    }
    for(int i=0;i<w+2;i++){
        cout<<"#";
    }
    
}
