n = int(input())
a = [list(map(int,input().split())) for i in range(n)]

for i in range(n):
 x=0
 y=0
 for j in range(n):
  p=a[i][0]-a[j][0]
  q=a[i][1]-a[j][1]
  d=p*p+q*q
  if x<d:
   y=j+1
   x=d
 print(y)