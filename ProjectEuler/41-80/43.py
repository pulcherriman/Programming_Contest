# 16695334890

from itertools import permutations

ans = 0
div = [1, 2, 3, 5, 7, 11, 13, 17]

for p in permutations(range(10), 10):
    ok = True
    for i in range(8):
        ok &= int(''.join(map(str, p))[i: i + 3]) % div[i] == 0
        if not ok:
            break
    if ok:
        ans += int(''.join(map(str, p)))

print(ans)
