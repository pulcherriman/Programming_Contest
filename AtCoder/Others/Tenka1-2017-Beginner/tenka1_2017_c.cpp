#include <iostream>
#include <algorithm>
using namespace std;
using ll=long long;
int main(void){
    ll n;
    cin>>n;
    for(ll i=1;i<=3500;i++){
        for(ll j=1;j<=3500;j++){
            ll a=n*i*j,b=4*i*j-n*(i+j);
            if(b<=0)continue;
            ll w=a/b;
            if(a%b==0 && 3500>=w && w>0){
                cout<<i<<" "<<j<<" "<<(int)w<<endl;
                return 0;
            }
        }
    }

}
