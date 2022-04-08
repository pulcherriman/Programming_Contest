# coding: utf-8
# Your code here!

s=input()
if int(s)%sum(map(int,list(s)))==0:
    print("Yes")
else:
    print("No")