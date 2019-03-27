// Abstract         ソートして整数を文字列として変換して連結する
// Expected scores  満点
// Complexity       O(n (log n + log max(a)))
//
// 数列aの最小値、最大値を計算することはO(n)で可能。
// また小さい方から連結するのは、
//
// - aをソートして、
// - ひとつひとつ文字列に変換して、
// - 連結すればよい

#include <bits/stdc++.h>
using namespace std;

#define rep(i,n) for(long long i = 0; i < (long long)(n); i++)
#define all(x) (x).begin(), (x).end()
#define ldout fixed << setprecision(40) 

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
    
    cout << ldout << *min_element(all(a)) << " " << *max_element(all(a)) << endl;
    rep(i, n) cout << a[i];
    cout << endl;

    return 0;
}



