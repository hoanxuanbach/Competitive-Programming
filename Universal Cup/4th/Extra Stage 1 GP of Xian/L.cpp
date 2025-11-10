#pragma GCC optimize("O3,unroll-loops")
#include <bits/stdc++.h>
#define BIT(x, i) (((x) >> (i)) & 1)

using namespace std;
const int N = 2e5 + 7;

int n, a[N], pos[N];
long long sum[N];

long long getSum(int l, int r) {
    return sum[r] - sum[l - 1];
}

void solve() {
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    sort (a + 1, a + n + 1);
    for (int i = 1; i <= n; ++i) {
        sum[i] = sum[i - 1] + a[i];
        pos[i] = 0;
    }

    for (int i = 3; i <= n; ++i) {
        int l = 1, r = i - 1;
        while (l <= r) {
            int mid = (l + r) / 2;
            if (getSum(mid, i - 1) > a[i]) {
                pos[i - mid + 1] = max(pos[i - mid + 1], i);
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
    }

    for (int i = 3; i <= n; ++i) {
        pos[i] = max(pos[i], pos[i - 1]);
    }
    for (int i = 1; i <= n; ++i) {
        // cout << i << "+" << pos[i] << '\n';
        if (pos[i] < i) {
            cout << 0 << ' ';
        } else {
            cout << getSum(pos[i] - i + 1, pos[i]) << ' ';
        }
    }
    cout << '\n';
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
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
