#include <bits/stdc++.h>
using namespace std;

int main(){
	int n;
  	cin>>n;
  	long long a=1,b=1;
  	for(int lp=0;lp<n;lp++){
    	long long xa,xb,x;
	    cin>>xa>>xb;
      	x=max(a/xa+!!(a%xa),b/xb+!!(b%xb));
      	a=xa*x, b=xb*x;
    }
    cout<<a+b<<endl;
}