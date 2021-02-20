# coding: utf-8
# Your code here!
a,b=map(int,input().split())
s=input().split('-')
if len(s)!=2:
    print("No")
elif len(s[0])!=a or len(s[1])!=b:
    print("No")
else:
    print("Yes")
