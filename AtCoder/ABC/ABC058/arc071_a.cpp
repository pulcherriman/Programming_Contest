#include <iostream>
#include <string>
#include <vector>
using namespace std;
int main(void){
    int n,t;
    string buf;
    cin>>n;
    vector<vector<int>> l(n+1,vector<int>(26,0));
    for(int i=0;i<n;i++){
        cin>>buf;
        for(int j=0;j<buf.length();j++){
            l[i][buf[j]-'a']++;
        }
    }
    
    for(int i=0;i<26;i++){
        t=10000;
        for(int j=0;j<n;j++){
            if(t>l[j][i]) t=l[j][i];
        }
        for(int j=0;j<t;j++){
            cout<<(char)('a'+i);
        }
    }
    cout<<endl;
}
