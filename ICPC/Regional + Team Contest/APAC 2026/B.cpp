#include <bits/stdc++.h>

using namespace std;

const int N = 5e5 + 5;

int n, p[N], a[N], b[N], dp[N];
vector<int> adj[N];

void dfs(int u) {
    dp[u] = b[u];
    for (int v : adj[u]) {
        dfs(v);
        if (dp[v] > 0)
            dp[u] ++;
        else if (dp[v] < 0)
            dp[u] --;
    }
}

bool check(int mid) {
    for (int i = 1; i <= n; i++) {
        if (a[i]) {
            b[i] = a[i] <= mid ? -1 : 1;
        }
    }

    dfs(1);
    return dp[1] <= 0;
}

void solve() {
    cin >> n;
    for (int i = 2; i <= n; i++) {
        cin >> p[i];
        a[i] = i;
        a[p[i]] = 0;
        adj[p[i]].push_back(i);
    }

    int l = 1, r = n;
    while (l < r) {

        int mid = (l + r) / 2;

        if (check(mid)) {
            r = mid;
        } else {
            l = mid + 1;
        }

    }
    cout << r << '\n';
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