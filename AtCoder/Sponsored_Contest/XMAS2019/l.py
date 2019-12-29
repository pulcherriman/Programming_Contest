import re
l = [12, 62, 3, 38, 35, 59, 1, 13,
     46, 47, 14, 61, 11, 4, 43, 2,
     53, 30, 9, 10, 42, 26, 27, 15,
     18, 54, 17, 44, 49, 28, 32, 19,
     36, 21, 33, 22, 7, 8, 50, 40,
     34, 41, 25, 52, 60, 63, 20, 29,
     45, 56, 57, 31, 58, 23, 6, 39,
     51, 48, 55, 16, 64, 24, 5, 37]

ans = ["" for i in range(256)]

for i in range(64):
    with open(f"./back/{l[(i//8)*8 + (7-i%8)]}.txt") as f:
        p = f.readlines()
        for j in range(32):
            ans[(i//8)*32 + j] += p[j][0:-1]
print(ans)
s = re.sub(r'\.+', r',', ','.join(ans))
d = re.sub(r',,+', r',', s).split(',')

for i in range(2, 20):
    print(i)
    print(sorted([s for s in d if len(s) == i]))
