import bisect

N = int(input())
A = list(map(int, input().split()))
A.sort()
Q = int(input())
for i in range(Q):
  l, r = map(int, input().split())
  ps = bisect.bisect_right(A, r) - bisect.bisect_left(A, l)
  print(ps)
