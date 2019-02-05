#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv)
{
    int n = atoi(argv[1]);
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        a[i] = atoi(argv[2+i]);
        assert(1<=a[i]&&a[i]<=1e9);
    }
    sort(a.begin(), a.end());

    cout << *min_element(a.begin(), a.end()) << " " << *max_element(a.begin(), a.end()) << endl;
    for (int i = 0; i < n; i++) {
        cout << a[i];
    }
    cout << endl;

    return 0;
}

