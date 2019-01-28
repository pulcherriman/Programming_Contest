import random

l=[1000,1000,9]
l2=[1]*9
print(*l)
print(*l2)

c=1
for i in range(1000):
	l=""
	for j in range(1000):
		if i//100==c and j//100==c:
			l+=str(c)
			c+=1
		else:
			l+=('.' if random.randint(0,10)>0 else '#')
	print(l)