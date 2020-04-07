S = input()
T = input()

ns = len(S)
nt = len(T)


table = [0] * 10010
j = -1
table[0] = -1
for i in range(nt):
    while j >= 0 and T[i] != T[j]:
        j = table[j]
    table[i+1] = j+1
    j += 1

m = 0
i = 0
while m + i < ns:
    if T[i] == S[m+i]:
        i += 1
        if nt == i:
            print(m)
            exit()
    else:
        m += i - table[i]
        if i > 0:
            i = table[i]
print(-1)

