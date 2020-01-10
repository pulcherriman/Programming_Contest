# 153

a, b = 2, 3
ans = 0

for i in range(1000):
    if len(str(b)) > len(str(a)):
        ans += 1
    a, b = a + b, a * 2 + b

print(ans)
