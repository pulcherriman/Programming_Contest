#include <bits/stdc++.h>
long M=1e9+7,n,a,i;
long P(long n){long a=n*n%M,b=a*a%M;return b*b%M*a%M;}
int main(){
    for(scanf("%ld",&n);++i<=n;a=(a+P(n/i)*(P(i)-P(i-1)+M))%M);
    printf("%ld",a);
}
