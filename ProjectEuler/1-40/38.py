# 932718654

ans = 0

for i in range(1, 10000):
    s = ""
    for j in range(1, 10):
        s += str(i * j)
        if len(s) > 9:
            break
        if "".join(sorted(list(s))) == "123456789":
            ans = max(ans, int(s))

print(ans)
