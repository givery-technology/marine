
#include <bits/stdc++.h>
using namespace std;
#define rep(i, m, n) for (int i = (m); i < (n); i++)

int main()
{
    string S, T;
    cin >> S >> T;
    int ns = S.size(), nt = T.size();

    int table[10010] = {};
    int j = -1;
    table[0] = -1;
    rep(i, 0, nt)
    {
        while (j >= 0 && T[i] != T[j])
            j = table[j];
        table[i + 1] = j + 1;
        j++;
    }

    int m = 0, i = 0;
    while (m + i < ns)
    {
        if (T[i] == S[m + i])
        {
            i++;

            if (nt == i)
            {
                cout << m << endl;
                return 0;
            }
        }
        else
        {
            m += i - table[i];
            if (i > 0)
                i = table[i];
        }
    }
    cout << -1 << endl;
}