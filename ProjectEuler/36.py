# 872187

ans = 0

for i in range(1000001):
    if str(i) == "".join(reversed(str(i))) and bin(i)[2:] == "".join(reversed(bin(i)[2:])):
        ans += i

print(ans)
