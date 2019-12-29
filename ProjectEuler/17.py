# 21124

ans = 11

data = {}
data[0] = ""
data[1] = "one"
data[2] = "two"
data[3] = "three"
data[4] = "four"
data[5] = "five"
data[6] = "six"
data[7] = "seven"
data[8] = "eight"
data[9] = "nine"
data[10] = "ten"
data[11] = "eleven"
data[12] = "twelve"
data[13] = "thirteen"
data[14] = "fourteen"
data[15] = "fifteen"
data[16] = "sixteen"
data[17] = "seventeen"
data[18] = "eighteen"
data[19] = "nineteen"
data[20] = "twenty"
data[30] = "thirty"
data[40] = "forty"
data[50] = "fifty"
data[60] = "sixty"
data[70] = "seventy"
data[80] = "eighty"
data[90] = "ninety"
data[100] = "hundred"


for i in range(1, 1000):
    val = ""
    if i >= 100:
        val += data[i // 100] + data[100]
        if i % 100 != 0:
            val += "and"
    if i % 100 in data:
        val += data[i % 100]
    else:
        val += data[i % 100 // 10 * 10] + data[i % 10]
    ans += len(val)
    print(i, val)

print(ans)
