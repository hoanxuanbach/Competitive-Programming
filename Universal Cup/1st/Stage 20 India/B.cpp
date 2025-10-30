#pragma GCC optimize("O3,unroll-loops")
#include <bits/stdc++.h>

using namespace std;
const int N = 1e6 + 7;
const int INF = 1e9 + 7;

int n, m, k;
int a[N], cost[N], dp[N];
vector<int> divs[N];

void sieve() {
    for (int i = 1; i < N; ++i) {
        for (int j = i; j < N; j += i) {
            divs[j].push_back(i);
        }
    }
}

bool check(int mid) {
    int sum = 0;
    for (int i = 1; i <= n / 2 + 1; ++i) {
        if (a[i] <= mid) {
            continue;
        }
        int tmp = mid == 0 ? a[i] + 1 : (a[i] / (mid + 1)) + 1;
        sum = min(INF, sum + dp[tmp]);
    }
    return sum <= k;
}

void solve() {
    cin >> n >> m >> k;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    sort(a + 1, a + n + 1);
    for (int i = 1; i <= m; ++i) {
        cin >> cost[i];
    }
    for (int i = m - 1; i >= 1; --i) {
        cost[i] = min(cost[i], cost[i + 1]);
    }

    for (int i = 0; i <= m + 1; ++i) {
        dp[i] = INF;
    }
    dp[0] = 0;
    dp[1] = 0;
    for (int i = 2; i <= m; ++i) {
        for (int d : divs[i]) {
            dp[i] = min(dp[i], dp[i / d] + cost[d]);
        }
    }
    for (int i = 2; i <= m; ++i) {
        int x = m / i + 1;
        dp[m + 1] = min(dp[m + 1], dp[i] + cost[x]);
    }
    for (int i = m; i >= 1; --i) {
        dp[i] = min(dp[i], dp[i + 1]);
    }

    int l = 0, r = m, res = m;
    while (l <= r) {
        int mid = (l + r) / 2;
        if (check(mid)) {
            res = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    cout << res << '\n';
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
#ifdef LOCAL
    freopen("main.inp", "r", stdin);
    freopen("main.out", "w", stdout);
#endif
    sieve();
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}