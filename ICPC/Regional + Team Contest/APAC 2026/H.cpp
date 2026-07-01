#include <bits/stdc++.h>

using namespace std;

#define int long long

const int N = 1e5 + 5;

int n, a[N], diff[N];

void solve() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    int g = 0;
    for (int i = 1; i < n; i++) {
        diff[i] = abs(a[i + 1] - a[i]);
        g = __gcd(g, diff[i]);
    }

    if (g == 0) {
        cout << a[1] << '\n';
        return ;
    }

    int a1 = a[1] % (2 * g);

    if (a1 == 0) {
        a1 += 2 * g;
    }

    for (int i = 1; i < n; i++) {
        a1 += diff[i];
    }

    cout << a1 << '\n';
}

signed main() {
#ifdef LOCAL
    freopen("main.inp", "r", stdin);
    freopen("main.out", "w", stdout);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int num_test = 1;
    // cin >> num_test;
    while (num_test--) {
        solve();
    }
}