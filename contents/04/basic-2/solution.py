class RollingHash:
    def __init__(self, S):
        N = len(S)
        self.N = N
        self.base1 = 1007
        self.mod1 = 10**9 + 7
        self.hash1 = [0] * (N+1)
        self.power1 = [1] * (N+1)

        for i, e in enumerate(S):
            self.hash1[i+1] = (self.hash1[i] * self.base1 + ord(e)) % self.mod1
            self.power1[i+1] = (self.power1[i] * self.base1) % self.mod1
    
    def get(self, lv, rv):
        return (self.hash1[rv] - self.hash1[lv] * self.power1[rv-lv] % self.mod1) % self.mod1

S = input()
T = input()
rh_s = RollingHash(S)
rh_t = RollingHash(T)
ns = len(S)
nt = len(T)

for i in range(ns - nt+1):
    if rh_t.get(0,nt) == rh_s.get(i, i+nt):
        print(i)




    