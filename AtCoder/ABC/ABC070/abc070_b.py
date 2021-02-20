a=list(map(int,input().split()))
n=min(a[1],a[3])-max(a[0],a[2])
print(n if n>0 else 0)