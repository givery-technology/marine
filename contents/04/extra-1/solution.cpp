#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using lpair = pair<ll, ll>;
#define rep(i,m,n) for(ll i=(m);i<(n);i++)
#define rrep(i,m,n) for(ll i=(m);i>=(n);i--)

struct HashData {
	ll h1, h2;
	bool operator==(const HashData& rhs) const {
		return h1 == rhs.h1 && h2 == rhs.h2;
	}
	bool operator!=(const HashData& rhs) const { return !(*this == rhs); }
};

class RollingHash {
	template<const ll B, const ll M>
	class RollingHashPart {
	private:
		size_t len;
		vector<ll> pow_b, hash;
	public:
		RollingHashPart() {}
		template<typename T>
		RollingHashPart(const T& s) : len(s.size()), pow_b(s.size() + 1), hash(s.size() + 1) {
			pow_b[0] = 1;
			hash[0] = 0;
			for (ll i = 0; i < len; i++) {
				pow_b[i + 1] = pow_b[i] * B % M;
				hash[i + 1] = (hash[i] * B + s[i]) % M;
			}
		}
		// [l, r)
		ll get(ll l, ll r) const {
			ll res = (hash[r] - hash[l] * pow_b[r - l]) % M;
			if (res < 0) res += M;
			return res;
		}
	};
public:
	RollingHashPart<1033, 1000000007> rh1;
	RollingHashPart<6037, 999999937> rh2;
 
	RollingHash() {}
	template<typename T> RollingHash(const T & s) : rh1(s), rh2(s) {}
	// [l, r)
	HashData get(ll l, ll r) const {
		return (HashData){ rh1.get(l, r), rh2.get(l, r) };
	}

	lpair getPair(ll l, ll r) const {
		return make_pair(rh1.get(l,r) , rh2.get(l, r));
	}
	// [l1, r1), [l2, r2)
	ll lcp(const RollingHash & rhs, ll l1, ll r1, ll l2, ll r2) const {
		ll lb = 0, ub = min(r1 - l1, r2 - l2) + 1;
		while (ub - lb > 1) {
			ll md = (lb + ub) >> 1;
			(get(l1, l1 + md) == rhs.get(l2, l2 + md) ? lb : ub) = md;
		}
		return lb;
	}
};

int main(){
    ll N;
    cin >> N;
    string S;
    cin >> S;
    string T = S;
    reverse(T.begin(), T.end());
    RollingHash rh(S), rh2(T);
    ll len = 0;
    rep(i,1,N/2+1){
        if(S[i-1] != T[i-1]){
            break;
        }else{
            len = i;
        }
    }
    if(len*2 == N){
        cout << S.size() << endl;
        return 0;
    }
    ll lv = len, rv = N-len-1;// [lv,rv]
    ll max_len = 1;

    rrep(i,rv-lv+1,2){
        ll half = i/2;
        lpair left_hash = rh.getPair(lv, lv+half);
        lpair right_hash = rh2.getPair(N-1-(lv+i-1), N-1-(lv+i-half) + 1);
        if(left_hash == right_hash){
            max_len = i;
            break;
        }
    }
    ll max_len2 = 1;
    rrep(i,rv-lv+1,2){
        ll half = i/2;
        lpair left_hash = rh.getPair(rv-i+1, rv-i+1+half);
        lpair right_hash = rh2.getPair(N-1-rv,N-1-(rv-half+1)+1);
        if(left_hash == right_hash){
            max_len2 = i;
            break;
        }
    }
    string ans = "";
    if(max_len >= max_len2){
        ans = S.substr(0, len + max_len) + S.substr(N-len, len);
    }else{
        ans = S.substr(0, len) + S.substr(N-len-max_len2, len + max_len2);
    }
    cout << ans.size() << endl;


    

}