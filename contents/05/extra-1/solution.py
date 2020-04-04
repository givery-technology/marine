def modpow(x,p,MOD):
  if p == 0:return 1
  if p%2: return x*modpow(x,p-1,MOD)%MOD
  return modpow((x*x)%MOD, p//2,MOD)

MOD = int(1e9+7)
N = int(input())
A = [int(x) for x in input().split()]
B = [int(x) for x in input().split()]
C = [0]*N
for i in range(N):
  C[i]=A[i]*(i+1)*(N-i)
C.sort()
B.sort(reverse = True)
ans = 1
for i in range(N):
  ans*=modpow(B[i],C[i],MOD)
  ans%=MOD
print(ans)