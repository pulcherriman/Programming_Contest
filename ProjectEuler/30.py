# 443839

ans = 0

for i in range(2, 1000000):
    if i == sum(map(lambda x: int(x)**5, list(str(i)))):
        ans += i

print(ans)
