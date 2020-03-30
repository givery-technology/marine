class Hash:
    def __init__(self, _mod):
        self.mod = _mod
        self.used = [False]*_mod
        self.table = [0]*_mod
    
    def insert(self, x):
        #開番地を線形走査する
        for i in range(self.mod):
            idx = (x + i) % self.mod
            if not self.used[idx]:
                self.used[idx] = True
                self.table[idx] = x
                return
            elif self.table[idx] == x:
                return
    
    def search(self, x):
        for i in range(self.mod):
            idx = (x + i) % self.mod
            if not self.used[idx]:
                return False
            if self.table[idx] == x:
                return True
        return False


Q = int(input())
hash = Hash(100003)
for _ in range(Q):
    sign, x = map(int,input().split())
    if sign == 0:
        hash.insert(x)
    else:
        if hash.search(x):
            print("found")
        else:
            print("not found")
