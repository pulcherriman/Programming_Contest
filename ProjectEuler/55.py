# 249

ans = 0

for n in range(1, 10001):
    v = n
    ok = True
    for i in range(50):
        v += int("".join(reversed(list(str(v)))))
        if v == int("".join(reversed(list(str(v))))):
            ok = False
        if not ok:
            break
    if ok:
        ans += 1

print(ans)
