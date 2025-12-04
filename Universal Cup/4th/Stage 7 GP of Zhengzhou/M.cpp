#include <bits/stdc++.h>
#define pii pair<int, int>
#define fi first
#define se second
#define CNT(mask) __builtin_popcount(mask)

using namespace std;
const int INF = 1e9 + 7;

string calc(string &s, int pos) {
    string x, y;
    int n = (int)s.length();
    for (int i = 0; i < pos; ++i) {
        x += s[i];
    }
    for (int i = pos + 1; i < n; ++i) {
        y += s[i];
    }

    reverse(x.begin(), x.end());
    reverse(y.begin(), y.end());
    while ((int)x.length() > 1 && x.back() == '0') x.pop_back();
    while ((int)y.length() > 1 && y.back() == '0') y.pop_back();
    string res = x;
    for (int i = 0; i < (int)y.length(); ++i) {
        if (i >= (int)x.length()) {
            res += y[i];
        } else {
            int xi = x[i] - '0', yi = y[i] - '0';
            res[i] = '0' + (xi ^ yi);
        }
    }
    while ((int)res.length() > 1 && res.back() == '0') res.pop_back();
    reverse(res.begin(), res.end());
    return res;
}

string maximize(string &x, string y) {
    if ((int)x.length() > (int)y.length()) return x;
    if ((int)x.length() < (int)y.length()) return y;
    return max(x, y);
}

void solve() {
    string s;
    cin >> s;
    int n = (int)s.length();
    int first_one = n, last_one = -1;
    for (int i = 2; i < n; ++i) {
        if (s[i] == '1') {
            first_one = min(first_one, i);
            last_one = max(last_one, i);
        }
    }

    string res = "0";
    if (first_one != n)  res = maximize(res, calc(s, first_one - 1));
    if (last_one != -1) res = maximize(res, calc(s, last_one - 1));
    res = maximize(res, calc(s, 1));
    res = maximize(res, calc(s, n - 2));
    cout << res << '\n';
}

signed main() {
#ifdef LOCAL
    freopen("main.inp", "r", stdin);
    freopen("main.out", "w", stdout);
#endif
    cin.tie(0), cout.tie(0)->sync_with_stdio(0);
    int testcases = 1;
    cin >> testcases;
    for (int test = 1; test <= testcases; test++) {
        solve();
    }
}
