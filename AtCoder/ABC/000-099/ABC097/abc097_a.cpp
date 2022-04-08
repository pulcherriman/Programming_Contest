#include <bits/stdc++.h>
#define rep(i,n) range(i,0,n)
#define range(i,a,n) for(int i=a;i<(n);i++)
using namespace std;

int main(){
	int a,b,c,d;
	cin>>a>>b>>c>>d;
	if(abs(a-c)<=d or (abs(a-b)<=d and abs(b-c)<=d)) cout<<"Yes"<<endl;
	else cout<<"No"<<endl;
	return 0;
}
