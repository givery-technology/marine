#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i,m,n) for(ll i=(m);i<(n);i++)

int main(){
	int N;
	cin >> N;
	int A[100010];
	rep(i,0,N) cin >> A[i];
	sort(A, A+N);
	int Q;
	cin >> Q;
	rep(i,0,Q){
		int l,r;
		cin >> l >> r;
		int res = upper_bound(A, A+N, r) - lower_bound(A, A+N, l);
		cout << res << "\n";

	}
}