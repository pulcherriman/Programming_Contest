# coding: utf-8
# Here your code !
s=input()
p=''.join(s.split('x'));
if p==p[::-1]:
    a=[0]
    for i in range(len(s)):
        if s[i]=='x':
            a[-1]+=1
        else:
            a.append(0)

    for i in range(len(a)//2):
        a[i]=abs(a[i]-a[-i-1])
    print(sum(a[:len(a)//2]))
else:
    print(-1)    