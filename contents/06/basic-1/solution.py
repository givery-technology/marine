N = int(input())
INF = int(2e9)
h = [int(x) for x in input().split()]
dp = [INF] * N
dp[0] = 0
for i in range(N-1):
    dp[i+1] = min(dp[i+1], dp[i] + abs(h[i] - h[i+1]))
    if i + 2 < N:
        dp[i+2] = min(dp[i+2], dp[i] + abs(h[i] - h[i+2]))

print(dp[N-1])
