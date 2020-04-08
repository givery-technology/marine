
#include <bits/stdc++.h>
using namespace std;
#define rep(i, m, n) for (int i = (m); i < (n); i++)

int main()
{
    string S, T;
    cin >> S >> T;
    int ns = S.size(), nt = T.size();

    int table[30] = {};
    rep(i,0,26) table[i] = -1;
    rep(i,0,nt){
        table[T[i]-'a'] = nt - i - 1;
    }
    int i = nt-1, p = 0;
    while(i < ns){
        p = nt-1;
        while(p >= 0 && i < ns){
            cout << i << " " << p << endl;
            if(S[i] == T[p]){
                i--; p--;
            }else{
                break;
            }
        }
        // cout << i << " " << p << endl;
        if(p < 0){
            cout << p << endl;
            return 0;
            // cout << i+1 << endl;
        }

        int shift1 = 0;
        cout << p << endl;
        if(table[T[p]-'a'] == -1){
            shift1 = nt;
        }else{
            shift1 = table[T[p]-'a'];
        }
        int shift2 = nt - p;
        i += max(shift1, shift2);
    }
    cout << -1 << endl;
}