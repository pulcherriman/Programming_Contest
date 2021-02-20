#include <bits/stdc++.h>
using namespace std;
int main(void){
    // Your code here!
    string s;cin>>s;
    for(int i=0;i<s.size();i++){
        if(s[i]=='C'){
            for(;i<s.size();i++){
                if(s[i]=='F'){
                    cout<<"Yes"<<endl;
                    return 0;
                }
            }
        }
    }
    cout<<"No"<<endl;
}
