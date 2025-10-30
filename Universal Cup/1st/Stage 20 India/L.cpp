#pragma GCC optimize("O3,unroll-loops")
#include <bits/stdc++.h>

using namespace std;

void solve() {
    int n;
    int cnt1 = 0, cnt2 = 0;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        int x; cin >> x;
        if (x == 1) {
            ++cnt1;
        } else {
            ++cnt2;
        }
    }

    if (cnt2 >= 2) {
        cout << "Grundy\n";
    } else if (cnt2 == 0) {
        cout << (n % 3 == 1 ? "Sprague" : "Grundy") << '\n';
    } else {
        cout << (cnt1 % 3 == 1 ? "Grundy" : "Sprague") << '\n';
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
#ifdef LOCAL
    freopen("main.inp", "r", stdin);
    freopen("main.out", "w", stdout);
#endif
    int t = 1;
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}
