from collections import defaultdict
n = int(input())
a = [list(map(int,input().split())) for i in range(n)]


dc = defaultdict (lambda: 10**10)
for v,k in a:
 dc[k]= min(dc[k] , v)
print(max(*dc.values()))