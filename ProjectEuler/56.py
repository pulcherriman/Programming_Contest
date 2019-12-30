# 972
ans = 0

for a in range(1, 100):
    for b in range(1, 100):
        d = sum(map(int, list(str(a**b))))
        ans = max(ans, d)

print(ans)
