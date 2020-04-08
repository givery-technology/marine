N = int(input())
A = list(map(int, input().split()))
Q = int(input())
for _ in range(Q):
  x = int(input())
  lv = -1
  rv = N
  while rv - lv > 1:
    mid = (rv + lv) // 2
    if A[mid] >= x:
      rv = mid
    else:
      lv = mid
  pos = rv
  if pos == N:
    print("No")
  else:
    if A[pos] == x:
      print("Yes")
    else:
      print("No")