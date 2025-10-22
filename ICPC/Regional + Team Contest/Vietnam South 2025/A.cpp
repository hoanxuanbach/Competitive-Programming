#pragma GCC optimize("O3,unroll-loops")
#include <bits/stdc++.h>
#define int long long

using namespace std;
const int N = 1e5 + 7;
const int INF = 1e10 + 7;

int n, c, d;
int a[N], b[N];
int na[N], nb[N];
int res;

bool check(int mid) {
    for (int i = 1; i <= n; ++i) {
        na[i] = a[i];
        nb[i] = b[i];
    }

    int sum = 0;
    for (int i = 1; i <= n; ++i) {
        if (na[i] <= mid) {
            int tmp = mid - na[i];
            na[i] += tmp;
            nb[i] += tmp;
            sum += tmp;
        }
    }

    int cur_max = *max_element(nb + 1, nb + n + 1);
    int exp_min = cur_max - d;
    for (int i = 1; i <= n; ++i) {
        if (nb[i] <= exp_min) {
            int tmp = exp_min - nb[i];
            na[i] += tmp;
            nb[i] += tmp;
            sum += tmp;
        }
    }

    int max_a = *max_element(na + 1, na + n + 1);
    int min_a = *min_element(na + 1, na + n + 1);
    int max_b = *max_element(nb + 1, nb + n + 1);
    int min_b = *min_element(nb + 1, nb + n + 1);

    if (max_a - min_a <= c && max_b - min_b <= d && min_a == mid) {
        res = sum;
        return true;
    }
    return false;
}

void solve() {
    cin >> n >> c >> d;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    for (int i = 1; i <= n; ++i) {
        cin >> b[i];
    }

    res = -1;
    int l = *min_element(a + 1, a + n + 1), r = INF;
    while (l <= r) {
        int mid = (l + r) / 2;
        if (check(mid)) {
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }

    cout << res << '\n';
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
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}