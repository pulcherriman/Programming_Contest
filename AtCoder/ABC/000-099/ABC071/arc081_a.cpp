#include <iostream>
#include <map>
using namespace std;
int main(void){
    int n,a=0,b=0;
    cin>>n;
    map<int,int> mp;
    for(int i=0;i<n;i++){
        int p;
        cin>>p;
        auto itr = mp.find(p);
        if(itr == mp.end()){
            mp[p]=1;
        }else{
            mp[p]++;
            if(mp[p]%2==0){
                a=max(a,p);
                if(a>b){
                    p=a;a=b;b=p;
                };
            }
        }
    }
    cout<<(unsigned long long)a*(unsigned long long)b;
}
