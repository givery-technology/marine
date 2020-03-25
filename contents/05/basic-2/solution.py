N = int(input())
A = list(map(int, input().split()))
A.sort()

for e in A:
    print(e, end=' ')