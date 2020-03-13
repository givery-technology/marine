import sys

from collections import deque

Q = int(input())
d = deque()
for i in range(Q):
  arr = list(map(int, input().split()))
  if arr[0] == 1:
    d.append(arr[1])
  else:
    print(d.popleft())
