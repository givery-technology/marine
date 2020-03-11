#include<iostream>
#include<string>
#include<stack>

using namespace std;

int main() {
	int N, K;
	string S;
	cin >> N >> K >> S;
	int cnt = 0;
	stack<int>st;
	for (int i = 0; i < N; i++) {
		if (S[i] == '(')st.push(i);
		else st.pop();
		if (st.empty())cnt++;
	}
	int ans = K / cnt;
	cout << ans << endl;
	return 0;
}