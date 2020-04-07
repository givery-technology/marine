T = int(input())

for t in range(T):
  x,y,p,q = map(int, input().split())
  INF = 10000000000
  lv = -1
  rv = INF
  amari = (q - y % q) % q
  while rv - lv > 1:
    mid = (rv + lv) // 2
    diff = amari + q * mid
    bunbo = y + diff
    bunshi = p * (bunbo / q)
    if bunshi >= x and bunshi- x <= diff:
      rv = mid
    else:
      lv = mid
  if rv == INF:
    print(-1)
  else:
    print(amari + q * rv)

  