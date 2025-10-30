#pragma GCC optimize("O3,unroll-loops")
#include <bits/stdc++.h>

using namespace std;

int get(string bit) {
    int ans = 0;
    for (int i = 0; i < (int)bit.length(); ++i) {
        ans += (1 << i) * (bit[i] - '0');
    }
    return ans;
}

void solve() {
    int n, d;
    cin >> n >> d;

    string bit = "";
    do {
        bit += '0' + (d % 2);
        d /= 2;
    } while(d > 0);

    string empty = "";
    while ((int)empty.length() < (int)bit.length()) {
        empty += '0';
    }

    for (int i = 1; i <= n; ++i) {
        cout << 0 << " " << get(bit) << " " << get(bit + bit) << " " << get(bit + bit + bit) << " " << get(empty + bit) << " " << get(empty + bit + bit) << '\n';
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
    // cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}
