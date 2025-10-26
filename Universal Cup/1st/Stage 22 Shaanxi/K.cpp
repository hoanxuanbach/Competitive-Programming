#pragma GCC optimize("O3,unroll-loops")
#include <bits/stdc++.h>

using namespace std;

void solve() {
    int n, m;
    cin >> n >> m;
    if (n == 1) {
        cout << (m + 2) / 2 << "\n";
        for (int i = 1; i <= m; ++i) {
            if (i == m && i % 2 == 0) {
                cout << 1 << " ";
                continue;
            }
            if (i % 2 == 1) {
                cout << 1 << " ";
            } else {
                cout << 0 << " ";
            }
        }
        return;
    }
    if (m == 1) {
        cout << (n + 2) / 2 << "\n";
        for (int i = 1; i <= n; ++i) {
            if (i == n && i % 2 == 0) {
                cout << 1 << "\n";
                continue;
            }
            if (i % 2 == 1) {
                cout << 1 << "\n";
            } else {
                cout << 0 << "\n";
            }
        }
        return;
    }
    cout << n / 2 + m / 2 + (n % 2 == 1 || m % 2 == 1) << "\n";
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (i == n && j == m && (n % 2 == 1 || m % 2 == 1)) {
                cout << 1 << " ";
                continue;
            }
            if (i != 1 && j != 1) {
                cout << 0 << " ";
            } else if (i == 1) {
                if (j % 2 == 0) {
                    cout << 1 << " ";
                } else {
                    cout << 0 << " ";
                }
            } else if (i % 2 == 0) {
                cout << 1 << " ";
            } else {
                cout << 0 << " ";
            }
        }
        cout << '\n';
    }
    
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