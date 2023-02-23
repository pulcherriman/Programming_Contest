import functools
import math

def gcd(*numbers):
	return functools.reduce(math.gcd, numbers)

# ax + by = gcd(a, b) を満たす非零整数の組(x, y)
def extGCD(a,b):
	assert gcd(a, b) == 1
	x, y, u, v = 1, 0, 0, 1
	while b:
		k = a // b
		x -= k * u
		y -= k * v
		x, y, u, v, a, b = u, v, x, y, b, a % b
	return x, y

# mod p におけるaの乗法的逆元(1/a)
def modinv(a, p):
	assert gcd(a, p) == 1
	x, _ = extGCD(a, p)
	return x % p



def multicase(f):
	def wrapper(*args, **kwargs):
		t = int(input())
		for _ in range(t):
			f(*args, **kwargs)
	return wrapper

@multicase
def main():
	n,s,k = map(int, input().split())
	g = gcd(n, s, k)
	n, s, k = n//g, s//g, k//g

	# minimize x s.t. s+kx = 0 (mod n)
	# x = -s/k (mod n)
	try:
		print(-s * modinv(k, n) % n)
	except AssertionError:
		print(-1)


if __name__ == '__main__':
	main()
