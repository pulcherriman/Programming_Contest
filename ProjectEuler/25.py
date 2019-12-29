fib = [1, 1]

while True:
    fib.append(fib[-1]+fib[-2])
    if len(str(fib[-1])) == 1000:
        print(len(fib))
        break
