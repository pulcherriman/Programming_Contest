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
    int n,a,b;
    cin>>n>>a>>b;
    cout<<min(n*a,b);
}
