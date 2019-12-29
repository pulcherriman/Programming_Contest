from scipy.special import comb
# 100808458960497


ans = 0
length = 50

for u2 in range(length // 2 + 1):
    for u3 in range(length // 3 + 1):
        if u2 * 2 + u3 * 3 > length:
            break
        for u4 in range(length // 4 + 1):
            if u2 * 2 + u3 * 3 + u4 * 4 > length:
                break
            cell = length - u2 * 1 - u3 * 2 - u4 * 3
            ans += comb(cell, u2, exact=True) * comb(cell - u2, u3,
                                                     exact=True) * comb(cell - u2 - u3, u4, exact=True)

print(ans)
