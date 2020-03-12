N,M = map(int, input().split())

A = list(map(int, input().split()))

idx = -1
max_val = -1
for i in range(N - M + 1):
    m_sum = 0
    for j in range(M):
        m_sum += A[i + j]
    if max_val < m_sum:
        max_val = m_sum
        idx = i+1
print(max_val, idx)
