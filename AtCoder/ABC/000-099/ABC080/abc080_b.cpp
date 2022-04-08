#include <bits/stdc++.h>
using namespace std;
using vi=vector<int>;
using vvi=vector<vi>;
using vs=vector<string>;
void bulk(){}template<class H,class...T>void bulk(H&h,T&...t){cin>>h;bulk(t...);}
#define rep(i,n) for(int i=0;i<n;i++)
#define all(i) i.begin(),i.end()
int main(void){
    // Your code here!
    int n,f=0;
    cin>>n;
    int m=n;
    while(m){
        f+=m%10;
        m/=10;
    }
    if(n%f==0)cout<<"Yes";else cout<<"No";
}
