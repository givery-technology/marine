#include "bits/stdc++.h"
using namespace std;

struct Hash {
	vector<int>table;
	vector<bool>used;
	int mod;

	Hash(int _mod) {
		mod = _mod;
		table.assign(_mod, 0);
		used.assign(_mod, false);
	}
	void insert(int x) {
		for (int i = 0; i < mod; i++) {
			int idx = (x + i) % mod;
			if (!used[idx]) {
				used[idx] = true;
				table[idx] = x;
				return;
			}
			else if (table[idx] == x)return;
		}
	}
	bool search(int x) {
		for (int i = 0; i < mod; i++) {
			int idx = (x + i) % mod;
			if (!used[idx])return false;
			if (table[idx] == x)return true;
		}
		return false;
	}
};

void solve() {
	Hash hash(100003);
	int q; cin >> q;
	while (q--) {
		int sign, x; cin >> sign >> x;
		if (sign == 0) {
			hash.insert(x);
		}
		else {
			if (hash.search(x))cout << "found" << endl;
			else cout << "not found" << endl;
		}
	}
}
signed main() {
	solve();
}