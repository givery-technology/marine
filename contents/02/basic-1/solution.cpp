#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main(){
	ll Q;
	queue<int> que;
	cin >> Q;
	for(int i = 0; i < Q; i++){
		ll T;
		cin >> T;
		if(T == 1){
			int X;
			cin >> X;
			que.push(X);
		}else{
			cout << que.front() << endl;
			que.pop();
		}
	}
}