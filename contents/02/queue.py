class Queue:
    def __init__(self, n):
        self.queue = [None] * n
        self.length = 0
        self.head = 0
        self.tail = 0
        self.data_size = n
    
    def enqueue(self, a):
        if self.length >= self.data_size:
            print("full")
        else:
            self.queue[self.tail] = a
            self.tail += 1
            self.tail %= self.data_size
            self.length += 1
    
    def dequeue(self):
        if self.length == 0:
            print("empty")
            return -1

        tmp = self.queue[self.head]
        self.queue[self.head] = None
        self.head += 1
        self.head %= self.data_size
        self.length -= 1
        return tmp

que = Queue(100010);
Q = int(input())
for _ in range(Q):
    t = list(map(int, input().split()))
    if len(t) == 1:
        print(que.dequeue())
    else:
        que.enqueue(t[1])