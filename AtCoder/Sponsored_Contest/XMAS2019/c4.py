ans = [0]
for i in range(30):
    ans.append(sum(ans)+11*i+135)
    print(i, ans[-2])
print(ans)
print(sum(ans)+2)
