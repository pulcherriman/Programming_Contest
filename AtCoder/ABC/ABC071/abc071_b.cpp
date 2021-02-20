#include <iostream>
#include <vector>
using namespace std;
int main(void){
    int c;
    vector<int> a(26,0);
    while((c=getchar())!=10 && c!=-1){
        a[c-'a']++;
    }
    for(int i=0 ;i<26;i++){
        if(a[i]==0){
            cout<<(char)(i+'a');
            return 0;
        }
    }
    cout<<"None";
}
