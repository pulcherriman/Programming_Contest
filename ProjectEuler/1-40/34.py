# 40730

from math import factorial

ans = 0

for i in range(3, 1000000):
    if sum(map(lambda x: factorial(int(x)), list(str(i)))) == i:
        ans += i

print(ans)
