N = int(input())
A = list(map(int, input().split()))

for i in range(N-1):
  for j in range (0, N-1-i):
    if A[j] > A[j+1]: A[j], A[j+1] = A[j+1], A[j]

for e in A:
  print(e, end = ' ')