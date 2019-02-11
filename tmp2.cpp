#include <bits/stdc++.h>

using namespace std;
#define _cTime (chrono::system_clock::now())
#define progress (chrono::duration_cast<chrono::milliseconds>(_cTime-_sTime).count())
#define reset _sTime=_cTime
auto reset;

using int64 = long long;

int main() {
	long long int a,b,k,bis=1,yen=0;
	cin>>k>>a>>b;
	for(int i=0;i<k;i++){
		if(b-a<2){
			bis++;
		}else{
			if(yen>0){
				yen--;
				bis=bis+b;
			}else if(bis>=a&&i!=k-1){
				bis=bis-a;
				yen++;
			}else{
				bis++;
			}
		}
	}
	cout<<bis<<endl;
	cout<<progress<<endl;
}

