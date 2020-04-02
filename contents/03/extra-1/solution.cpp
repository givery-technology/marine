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

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    ll T;
    cin >> T;
    while(T--){
        ll x,y,p,q;
        cin >> x >> y >> p >> q;
        ll lv = -1, rv = 1000000001;
        ll amari = (q - y % q) % q;
        while(rv - lv > 1){
            ll mid = (rv + lv) / 2;
            ll diff = amari + q * mid;
            ll bunbo = y + diff;
            ll bunshi = p * (bunbo / q);
            // print(mid,bunbo, bunshi);
            bool ok = true;
            if(bunshi >= x && bunshi - x <= diff){
                ok = true;
            }else{
                ok = false;
            }
            if(ok){
                rv = mid;
            }else{
                lv = mid;
            }
        }
        if(rv == 1000000001){
            print(-1);
        }else{
            print(amari + q * rv);
        }
    }
    

}