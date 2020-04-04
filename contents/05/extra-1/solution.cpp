#include<bits/stdc++.h>
using namespace std;

using ll = long long;

constexpr ll MOD = 1e9+7;

ll mult(ll x, ll y) {
	return (x * y) % MOD;
}
ll bin_pow(ll x, ll p) {
	if (p == 0) return 1;
	if (p & 1) return mult(x, bin_pow(x, p - 1));
	return bin_pow(mult(x, x), p / 2);
}

void solve() {
	int N; cin >> N;
	vector<ll>A(N), B(N), C(N);
	for(int i=0;i<N;i++) {
		cin >> A[i];
		C[i] = A[i] * (i + 1)*(N - i);
	}
	for(int i=0;i<N;i++) {
		cin >> B[i];
	}
	sort(C.begin(),C.end());
	sort(B.rbegin(),B.rend());
	ll ans = 1;
	for(int i=0;i<N;i++) {
		ans = mult(ans, bin_pow(B[i], C[i]));
	}
	cout << ans << endl;
}



signed main() {
	solve();
}


