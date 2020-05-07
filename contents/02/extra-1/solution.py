N, K = map(int, input().split())
S = input()

stack = []
cnt = 0
for i in range(len(S)):
    if S[i]=='(':
        stack.append(S[i])
    else:
        stack.pop()
    if len(stack) == 0:
        cnt += 1

print(K//cnt)