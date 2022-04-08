#include <bits/stdc++.h>
#define rep(i,n) range(i,0,n)
#define range(i,a,n) for(int i=a;i<(n);i++)
using namespace std;

int main(){
	int n,m=0;
  	cin>>n;
	range(i,1,35)range(j,2,10){
     	if(pow(i,j)>n) break;
      	m=max(m,(int)pow(i,j));
    }  
    cout<<m<<endl;
	return 0;
}
