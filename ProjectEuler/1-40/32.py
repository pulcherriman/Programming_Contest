# 45228

import itertools

s = set()

for v in itertools.permutations(map(str, range(1, 10)), 9):
    for i in range(1, 8):
        for j in range(i + 1, 9 - i):
            if int("".join(v[0:i])) * int("".join(v[i:j])) == int("".join(v[j:])):
                s.add(int("".join(v[j:])))

print(sum(s))
