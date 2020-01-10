# 49
import math

ans = 0


for n in range(1, 10000):
    ok = False
    diff = 0
    for i in range(1, 10000):
        if len(str((i**n))) == n:
            diff += 1
            ok = True
        elif ok:
            if diff:
                print(n, i - 1,  diff)
            break
    ans += diff
    if diff == 0:
        break
print(ans)
