#include <stdio.h>
int main(void){
    int n,a[9]={0},i,t;
    scanf("%d",&n);
    for(i=0;i<n;i++){
        scanf("%d",&t);
        a[t>=3200?8:t/400]++;
    }
    for(t=i=0;i<8;i++){
        t+=!!a[i];
    }
    printf("%d %d", t==0?1:t, a[8]+t);
}
