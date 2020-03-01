N,K=map(int,input().split())
S=input()
c=0
cnt=0
for i in range(len(S)):
    if S[i]=='(':
        c+=1
    else:
        c-=1
    if c==0:cnt+=1
print(K//cnt)