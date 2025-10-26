#pragma GCC optimize("O3,unroll-loops")
#include <bits/stdc++.h>

using namespace std;
const int N = 1e5 + 7;

string check(string x) {
    int pos = x.find(',');
    string s = x.substr(0, pos);
    if (x == s + ", " + s + " " + s + "ity " + s) {
        return s;
    }
    return "";
}

int n = 0;
string str[N];

void solve() {
    string s;
    while (getline(cin, s)) {
        str[++n] = s;
    }

    int res = -1;
    for (int i = 1; i <= n; ++i) {
        string tmp = check(str[i]);
        if (str[i+1] != "i said " + str[i]) {
            continue;
        }
        int j = i + 1;
        int len = 1;
        while (j + 2 <= n && str[j + 1] == str[i] && str[j + 2] == str[i + 1]) {
            j += 2;
            ++len;
        }
        res = max(res, ((int)str[i].length() + (int)str[i+1].length() + 2) * len);
        i = j;
    }
    cout << res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
#ifdef LOCAL
    freopen("main.inp", "r", stdin);
    freopen("main.out", "w", stdout);
#endif
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}