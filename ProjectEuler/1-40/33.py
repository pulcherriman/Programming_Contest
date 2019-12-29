
# 100

from math import gcd

a, b = 1, 1

for p in range(10, 100):
    for q in range(p + 1, 100):
        if p % 10 == 0 and q % 10 == 0:
            continue

        ok = False
        if p % 10 == q % 10:
            ok |= p / q == (p // 10) / (q // 10)
        if p // 10 == q % 10:
            ok |= p / q == (p % 10) / (q // 10)
        if p % 10 == q // 10 and q % 10 != 0:
            ok |= p / q == (p // 10) / (q % 10)
        if p // 10 == q // 10 and q % 10 != 0:
            ok |= p / q == (p % 10) / (q % 10)
        if ok:
            a *= p
            b *= q

print(b // gcd(a, b))
