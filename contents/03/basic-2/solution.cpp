#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main(){
	int N,M;
	cin >> N >> M;
	ll A[3010];
	for(int i = 0; i < N; i++){
		cin >> A[i];
	}
	ll max_val = -1, idx = -1;
	for(int i = 0; i < N-M+1; i++){
		ll sum = 0;
		for(int j = 0; j < M; j++){
			sum += A[i + j];
		}
		if(sum > max_val){
			idx = i+1;
			max_val = sum;
		}
	}
	cout << max_val << " " << idx << endl;
}