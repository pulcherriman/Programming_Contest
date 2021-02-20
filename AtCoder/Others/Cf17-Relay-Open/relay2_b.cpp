#include <bits/stdc++.h>
using namespace std;
int main(void){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n,q;
    cin>>n>>q;
    for(;q--;){
        int v,w;
        cin>>v>>w;
        if(n==1){
            cout<<min(v,w)<<endl;
        }else{
            v+=n-2;
            w+=n-2;
            while(v!=w){
                if(v>w){
                    v=v/n+n-2;
                }else{
                    w=w/n+n-2;
                }
            }
            cout<<v-n+2<<endl;
        }
    }
}
