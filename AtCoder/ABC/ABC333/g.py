from sympy import Rational,numer,denom
r = input()
d = int(input())
baser=Rational(r)
rat=baser.limit_denominator(d)


rat2 = baser*2 - rat
if denom(rat2) <= d:
  if rat-baser == baser-rat2:
    if rat2<rat:
      rat=rat2
print(numer(rat), denom(rat))
