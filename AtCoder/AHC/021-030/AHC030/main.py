import z3
n, m, eps = input().split()
n = int(n)
m = int(m)
eps = float(eps)

polyomino = [list(map(int, input().split())) for _ in range(m)]
cnt = [polyomino[i][0] for i in range(m)]
height = [max(polyomino[i][1::2])+1 for i in range(m)]
width = [max(polyomino[i][2::2])+1 for i in range(m)]
positions = [[polyomino[i][j]*n + polyomino[i][j+1] for j in range(1, cnt[i]*2+1, 2)] for i in range(m)]


vars = [z3.Int('b_%d' % (i)) for i in range(m)]
field = [z3.Int('f_%d_%d' % (j, k)) for j in range(n) for k in range(n)]
solver = z3.Solver()

for i in range(m):
	solver.add(vars[i] >= 0, vars[i] <= n*n)

	for j in range(n):
		for k in range(n):
			if j + height[i] > n or k + width[i] > n:
				solver.add(vars[i] != j*n+k)

moving = [[] for _ in range(n*n)]
for i in range(m):
	vs = [[] for _ in range(n*n)]
	for dy in range(n-height[i]+1):
		for dx in range(n-width[i]+1):
			for p in positions[i]:
				vs[p+dy*n+dx].append(dy*n+dx)
	for j in range(n*n):
		if len(vs[j]) != 0:
			moving[j].append(z3.Or(*[vars[i] == v for v in vs[j]]))

for j in range(n):
	for k in range(n):
		solver.add(0 <= field[j*n+k], field[j*n+k] <= m)
		for i in range(m+1):
			solver.add(z3.PbEq([(v, 1) for v in moving[j*n+k]], i) == (field[j*n+k] == i))

for i in range(n):
	f = list(map(int, input().split()))
	for j in range(n):
		solver.add(field[i*n+j] == f[j])


if solver.check() == z3.sat:
	model = solver.model()
	for i in range(m):
		print(i, model[vars[i]])
