#include <bits/stdc++.h>
using namespace std;

int main(void){
    int n,h,w;
    cin>>n>>h>>w;
    vector<int> win(n*w+1,0);
    win[0]=1;
    win[n*w]=-1;
    for(int i=0;i<n;i++){
        int p;cin>>p;
        win[i*w]--;
        win[i*w+w]++;
        if(i%2==0){
            win[i*w+p]++;
            win[i*w+p+w]--;
        }else{
            win[i*w-p]++;
            win[i*w-p+w]--;
        }
        //for(auto i:win)cout<<i;cout<<endl;
    }
    int p=0,ans=0;
    for(auto i:win){
        p+=i;
        if(p>0)ans++;
    }
    cout<<(n*w-ans)*h<<endl;
}
