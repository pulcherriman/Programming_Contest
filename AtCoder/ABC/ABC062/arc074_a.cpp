#include <iostream>
using namespace std;
#define ll long long
ll min(ll a,ll b){return a<b?a:b;}
ll max(ll a,ll b){return a>b?a:b;}
 
ll sep(int a, int b){
    ll pre=1<<30,a1,a2;
    for(ll i=1;i<a;i++){
        a1=max(llabs(b*i-b*((a-i)/2)),llabs(b*i-b*(a-i-(a-i)/2)));
        a2=max(llabs(b*i-(a-i)*(b/2)),llabs(b*i-(a-i)*(b-b/2)));
        pre=min(pre,min(a1,a2));
    }
    return pre;
}
 
int main(void){
    ll h,w;
    cin>>h>>w;
    cout<<min(sep(h,w),sep(w,h));
}