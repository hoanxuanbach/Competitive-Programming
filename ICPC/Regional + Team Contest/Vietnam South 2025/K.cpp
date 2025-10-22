#pragma GCC optimize("O3,unroll-loops")
#include <bits/stdc++.h>
#define int long long

using namespace std;

void solve() {
    int n;
    cin >> n;
    int left = 0, right = 0;
    for (int i = 1; i <= n; ++i) {
        int x;
        cin >> x;
        if (i <= n / 2) {
            left += x;
        } else {
            right += x;
        }
    }

    cout << abs(left - right);
}

signed main() {
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