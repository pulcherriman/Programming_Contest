n=int(input())
ans=1
for i in range(1,n):
    ans*=n/(n-i)
print(ans)