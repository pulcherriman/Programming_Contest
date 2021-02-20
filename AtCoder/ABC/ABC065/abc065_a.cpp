#include <iostream>
using namespace std;
int main(void){
    int q,w,e;
    cin>>q>>w>>e;
    if(w-e>=0)
        cout<<"delicious";
    else if(e-w<=q)
        cout<<"safe";
    else
        cout<<"dangerous";
}
