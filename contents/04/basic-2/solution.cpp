/*** author: yuji9511 ***/
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using lpair = pair<ll, ll>;
const ll MOD = 1e9+7;
const ll INF = 1e18;
#define rep(i,m,n) for(ll i=(m);i<(n);i++)
#define rrep(i,m,n) for(ll i=(m);i>=(n);i--)
#define printa(x,n) for(ll i=0;i<n;i++){cout<<(x[i])<<" \n"[i==n-1];};
void print() {}
template <class H,class... T>
void print(H&& h, T&&... t){cout<<h<<" \n"[sizeof...(t)==0];print(forward<T>(t)...);}
ll memo[10][1000010] = {};
ll maxN = 0, maxM = 0;
ll calc(ll m, ll n){
	ll &res = memo[m][n];
	maxN = max(maxN, n);
	maxM = max(maxM, m);
	print(maxM, maxN);

	if(res != -1) return res;
	res = 0;
	if(m == 0){
		return res = n+1;
	}else if(n == 0){
		return res = calc(m-1, 1);
	}else{
		ll v = calc(m, n-1);
		return res = calc(m-1, v);
	}
}

ll A(ll m, ll n){
	if(m == 0) return n+1;
	else if(n == 0) return A(m-1, 1);
	else return A(m-1, A(m, n-1));
}

int main(){
	cin.tie(0);
	ios::sync_with_stdio(false);
	memset(memo, -1, sizeof(memo));
	ll m,n;
	cin >> m >> n;
	print(calc(m, n));
	memo[0][0] = 1;
	// print(A(m,n));
	print(maxM, maxN);
	// rep(i,0,10){
	// 	rep(j,0,10){
	// 		cout << memo[i][j] << " ";
	// 	}
	// 	cout << endl;
	// }
	

}