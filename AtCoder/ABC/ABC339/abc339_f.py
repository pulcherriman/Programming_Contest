import bisect
n = int(input())
a = sorted([int(input()) for _ in range(n)])

ans = 0
for i in range(n):
	for k in range(n):
		if a[k] % a[i] != 0:
			continue
		aj = a[k] // a[i]

		l = bisect.bisect_left(a, aj)
		r = bisect.bisect_right(a, aj)
		ans += r - l

print(ans)


