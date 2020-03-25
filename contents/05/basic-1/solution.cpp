#include <bits/stdc++.h>

using namespace std;

void bubble_sort(vector<int>&v,int N){
	for(int i=0;i<N-1;i++){
		for(int j=i;j<N-1-i;j++){
			if(v[j]>v[j+1])swap(v[j],v[j+1]);
		}
	}
}

void solve() {
	int N;cin>>N;
	vector<int>v(N);
	for(int i=0;i<N;i++)cin>>v[i];
	bubble_sort(v,N);
	for(int i=0;i<N;i++){
		cout<<v[i];
		if(i<N-1)cout<<" ";
	}
	cout<<endl;
}

signed main() {
	solve();
}
