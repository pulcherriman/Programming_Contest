# coding: utf-8
x={}
n,k=map(int,input().split())
for i in range(n):
    a,b=map(int,input().split())
    if a in x:
        x[a]+=b
    else:
        x[a]=b
x=sorted(x.items(),key=lambda x:x[0])
a=0
for i in x:
    a+=i[1]
    if(a>=k):
        print(i[0])
        break;