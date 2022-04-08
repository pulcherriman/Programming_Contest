#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
#include <set>
#include <iterator>
using namespace std;
int main(void){
    string a,b;
    cin>>a>>b;
    if(a==b){
        cout<<"EQUAL";
    }else if(a.size()==b.size()){
        for(int i=0;i<a.size();i++){
            if(a[i]<b[i]){
                cout<<"LESS";
                return 0;
            }else{
                cout<<"GREATER";
                return 0;
            }
        }
    }else if(a.size()<b.size()){
        cout<<"LESS";
    }else{
        cout<<"GREATER";
    }
}
