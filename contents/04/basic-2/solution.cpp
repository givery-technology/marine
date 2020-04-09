
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i, m, n) for (int i = (m); i < (n); i++)

struct RollingHash {
    private:
        ll N, base, mod;
        vector<ll> hash, power;
    public:
        RollingHash(string S) {
            N = S.size();
            base = 1007;
            mod = 1e9 + 7;
            hash.assign(N+1, 0);
            power.assign(N+1, 1);
            rep(i,0,N){
                hash[i+1] = (hash[i] * base + S[i]) % mod;
                power[i+1] = (power[i] * base) % mod;
            }

        }

        ll get(int lv, int rv){
            return (hash[rv] - hash[lv] * power[rv-lv] % mod + mod) % mod;
        }

};

int main(){
    string S,T;
    cin >> S >> T;
    RollingHash rh_s(S), rh_t(T);
    int ns = S.size(), nt = T.size();
    ll hash_T = rh_t.get(0, nt);
    rep(i,0,ns-nt+1){
        if(hash_T == rh_s.get(i, i+nt)){
            cout << i << "\n";
        }
    }

}