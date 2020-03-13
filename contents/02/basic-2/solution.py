class BinaryHeap:

    def __init__(self, num_node):
        n = 1
        self.vacant_idx = 0
        while n < num_node:
            n *= 2
        self.dat = [0]*(n*2)

    def push(self, x, dat=None):
        if dat == None:
            dat = self.dat
        dat[self.vacant_idx] = x
        cur = self.vacant_idx
        self.vacant_idx += 1
        par = (cur-1)//2
        while cur > 0 and dat[par] < dat[cur]:
            dat[par], dat[cur] = dat[cur], dat[par]
            cur = par
            par = (cur-1)//2

    def pop(self, dat=None):
        if dat == None:
            dat = self.dat
        ret = dat[0]
        self.vacant_idx -= 1
        dat[0], dat[self.vacant_idx] = dat[self.vacant_idx], 0
        cur = 0
        while True:
            vl = dat[cur*2+1]
            vr = dat[cur*2+2]
            if vl > vr and vl > dat[cur]:
                dat[cur], dat[cur*2+1] = dat[cur*2+1], dat[cur]
                cur = cur*2+1
            elif vr > dat[cur]:
                dat[cur], dat[cur*2+2] = dat[cur*2+2], dat[cur]
                cur = cur*2+2
            else:
                break
        return ret


Q = int(input())
heap = BinaryHeap(Q)
for _ in range(Q):
    lis = list(map(int, input().split()))
    if lis[0] == 1:
        heap.push(lis[1])
    else:
        res = heap.pop()
        print(res)
