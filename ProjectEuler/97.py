# 8739992577

d = 10000000000


def mpow(n, m):
    r, v = 1, n
    while m:
        if m % 2 == 1:
            r = r * v % d
            m -= 1
        v = v * v % d
        m //= 2
    return r


print((mpow(2, 7830457) * 28433 + 1) % d)
