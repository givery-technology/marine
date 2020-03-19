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

// verify: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_B&lang=ja
int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    string T,P;
    cin >> T >> P;
    ll nt = T.size(), np = P.size();

    ll table[10010] = {};
    ll j = -1;
    table[0] = -1;
    rep(i,0,np){
        while(j >= 0 && P[i] != P[j]) j = table[j];
        table[i+1] = j+1;
        j++;
    }

    vector<ll> ret;
    ll m = 0, i = 0, n = T.size();
    ll cnt = 0;
    while(m + i < n){
        if(P[i] == T[m+i]){
            i++;

            if(np == i){
				print(m);
				return 0;
                ret.push_back(m);
                // print(i,m);
                m += i - table[i];
                i = table[i];
                // print(i,m);
                cnt++;
            }
        }else{
            m += i - table[i];
            if(i > 0) i = table[i];
            cnt++;
        }
    }
	print(-1);


    

}