#include <bits/stdc++.h>
using namespace std;

#define rep(i,n) for(long long i = 0; i < (long long)(n); i++)
#define all(x) (x).begin(), (x).end()

using ll = long long; using vll = vector<ll>; using vvll = vector<vll>; using P = pair<ll, ll>;

int main(int argc, char** argv)
{
    ll n; cin >> n;
    assert(2 <= n && n <= 100000);
    vll a(n);
    rep(i, n) {
        cin >> a[i];
        assert(1<=a[i]&&a[i]<=1e9);
    }
    sort(all(a));

    rep(i, n) cout << a[i];
    cout << endl;

    return 0;
}
