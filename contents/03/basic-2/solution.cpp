#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i,m,n) for(ll i=(m);i<(n);i++)

int main(){
	int N;
	cin >> N;
	int A[100010];
	rep(i,0,N) cin >> A[i];
	int Q;
	cin >> Q;
	while(Q--){
		int x;
		cin >> x;
		int lv = -1, rv = N;
		while(rv - lv > 1){
			int mid = (lv + rv) / 2;
			if(A[mid] >= x){
				rv = mid;
			}else{
				lv = mid;
			}
		}
		int pos = rv;
		if(pos == N){
			cout << "No" << endl;
		}else{
			if(A[pos] == x){
				cout << "Yes" << endl;
			}else{
				cout << "No" << endl;
			}
		}
	}
}