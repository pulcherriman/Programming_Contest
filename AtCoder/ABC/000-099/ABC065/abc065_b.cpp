#include <iostream>
#include <vector>
using namespace std;
int main(void){
    int n;
    cin>>n;
    vector<int> a(n+1);
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    int p=1,c=0;
    while(true){
        c++;
        if(a[p]==0){
            cout<<-1;
            break;
        }
        if(a[p]==2){
            cout<<c;
            break;
        }
        int q=p;
        q=a[p];
        a[p]=0;
        p=q;
    }
}
