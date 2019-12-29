# 210

s = ""

for i in range(1000000):
    s += str(i)
    if len(s) > 1000000:
        break

ans = 1
ans *= int(s[1])
ans *= int(s[10])
ans *= int(s[100])
ans *= int(s[1000])
ans *= int(s[10000])
ans *= int(s[100000])
ans *= int(s[1000000])

print(ans)
