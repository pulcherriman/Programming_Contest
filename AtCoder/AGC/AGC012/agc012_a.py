n=int(input())
print(sum(sorted(map(int,input().split()))[n::2]))