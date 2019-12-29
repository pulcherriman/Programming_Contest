from scipy.special import comb
# 20492570929


ans = 0
length = 50

for b in [2, 3, 4]:
    for i in range(1, length // b + 1):
        ans += comb(i + length - b * i, i, exact=True)

print(ans)
