#include <cstdio>
 #define Case break;case 
int main(){
 int n;
 scanf("%d",&n);
 switch(n){
  Case 0 ... 99:
   printf("00\n");
  Case 100 ... 5000:
   printf("%02d\n",n/100);
  Case 6000 ... 30000:
   printf("%02d\n",n/1000+50);
  Case 35000 ... 70000:
   printf("%02d\n",(n/1000-30)/5+80);
   break;
  default:
   printf("89\n");
 }
}