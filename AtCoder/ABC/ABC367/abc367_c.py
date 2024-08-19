import itertools


n,k = map(int, input().split())
r = list(map(int, input().split()))
for c in itertools.product(range(1, 6), repeat=n):
	ok = True
	for i in range(n):
		if r[i] < c[i]:
			ok = False
			break
	if not ok:
		continue
	if sum(c) % k != 0:
		ok = False
	if ok:
		print(*c)
