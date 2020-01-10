# 1389019170

for n in range(101010101, 138902664):
    d = n**2
    if str(d)[::2] == "123456789":
        print(n * 10, d * 100)
        break
