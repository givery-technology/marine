#include<bits/stdc++.h>

using namespace std;

template<typename T>
struct BinaryHeap {
	int n;
	int r;
	vector<T>dat;
	BinaryHeap(const int Q) {
		n = 1;
		r = 0;
		while (n<Q)n *= 2;
		dat.assign(n * 2, 0);
	}
	void push(T x) {
		dat[r] = x; 
		int pos = r;
		r++;
		while (pos > 0 && dat[(pos - 1) / 2] < dat[pos]) {
			swap(dat[(pos - 1) / 2], dat[pos]);
			pos = (pos - 1) / 2;
		}
	}
	int pop() {
		int ret = dat[0];
		dat[0] = dat[r-1]; 
		dat[r-1] = 0; r--;
		int pos = 0;
		while (true) {
			int vl = dat[pos * 2 + 1];
			int vr = dat[pos * 2 + 2];
			if (vl > vr) {
				if (vl > dat[pos]) {
					swap(dat[pos], dat[pos * 2 + 1]);
					pos = pos*2+1;
				}
				else break;
			}
			else {
				if (vr > dat[pos]) {
					swap(dat[pos], dat[pos * 2 + 2]);
					pos = pos*2+2;
				}
				else break;
			}
		}
		return ret;
	}
};

void solve() {
	int Q;cin>>Q;
	BinaryHeap<int>heap(Q);
	while(Q--){
		int sign;cin>>sign;
		if(sign==1){
			int x;cin>>x;
			heap.push(x);
		}
		else{
			cout<<heap.pop()<<endl;
		}
	}
}

signed main() {
	solve();
}
