#include <iostream>
#include <vector>
using namespace std;

int main(){
	int n,i,p;
	cin>>n;
	i=n%2;
	vector<int> b(0);
	while(cin>>p){
		if(i%2)
			b.insert(b.begin(),p);
		else
			b.push_back(p);
		i++;
	}
	for(int j=0;j<n;j++){
		cout<<b[j]<<(b.size()==j+1?"":" ");
	}
}