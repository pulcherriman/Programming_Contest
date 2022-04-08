#include <iostream>
using namespace std;
int main(void){
    int n,p=0,ans=0,dist,l;
    cin>>n;
    for(int i=1;i<=n;i++){
        cout << "? " << 1 << " " << i << endl;
        cin >> dist;
        if(p<dist){
            p=dist;
            l=i;
        }
    }
    for(int i=1;i<=n;i++){
        cout << "? " << l << " " << i << endl;
        cin >> dist;
        if(ans<dist)ans=dist;
    }
    cout<<"! "<<ans<<endl;
}
