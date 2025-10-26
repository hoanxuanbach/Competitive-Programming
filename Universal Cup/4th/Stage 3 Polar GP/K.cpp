#pragma GCC optimize("O3,unroll-loops")
#include <bits/stdc++.h>

using namespace std;
const int INF = 1e9 + 7;

int calc_gcd(int a, int b) {
    if (b == 0) return a;
    if (a == 0) return b;
    if (a > b) return calc_gcd(a % b, b);
    return calc_gcd(a, b % a);
}

void solve() {
    int n;
    int maxa = 0, g = 0;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        int a; cin >> a;
        maxa = max(maxa, a);
        g = calc_gcd(g, a);
    }

    int sz = maxa / g;
    if ((sz - n) % 3 == 0) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
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