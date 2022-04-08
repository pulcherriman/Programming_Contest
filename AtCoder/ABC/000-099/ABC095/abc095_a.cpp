#include <bits/stdc++.h>
using namespace std;
using ll=long long;
#define rep(i,n) for(int i=0;i<n;i++)
#define range(i,a,n) for(int i=a;i<n;i++)
int main(){
  string s;
  cin>>s;
  cout<<700+count(s.begin(),s.end(),'o')*100<<endl;
}