#include <bits/stdc++.h>
#include "app.hpp"
using namespace std;

string sort_and_concat_integers(long n, vector<long> a) {
    sort(a.begin(), a.end());
    string ret;
    for (auto& x : a) {
        ret += to_string(x);
    }
    return ret;
}
