#include <iostream>
using namespace std;
int main(void){
    int a,b;
    cin>>a>>b;
    int g1,g2;
    switch(a){
        case 2:
        g1=1;
        break;
        case 4:
        case 6:
        case 9:
        case 11:
        g1=2;
        break;
        default:
        g1=3;
    }
    switch(b){
        case 2:
        g2=1;
        break;
        case 4:
        case 6:
        case 9:
        case 11:
        g2=2;
        break;
        default:
        g2=3;
    }
    if(g1==g2){
        cout<<"Yes";
    }else cout<<"No";
}
