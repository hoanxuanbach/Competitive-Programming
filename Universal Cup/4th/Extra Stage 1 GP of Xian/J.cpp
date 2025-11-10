#pragma GCC optimize("O3,unroll-loops")
#include <bits/stdc++.h>
#define BIT(x, i) (((x) >> (i)) & 1)

using namespace std;
const int N = 3e5 + 7;

int n, m;
int c[N];
long long sum[N];
int f[N];
vector<vector<pair<int, int>>> adj;
int time_in[N], time_out[N], timer;


void dfs(int u, int par) {
    time_in[u] = ++timer;
    if ((int)adj[u].size() == 1) {
        f[u] = c[u];
        time_out[u] = timer;
        return;
    }
    for (int i = 0; i < (int)adj[u].size(); ++i) {
        if (adj[u][i].second == par) {
            adj[u].erase(adj[u].begin() + i);
            break;
        }
    }
    for (auto [c, v] : adj[u]) {
        dfs(v, u);
    }
    for (int i = 0; i < (int)adj[u].size(); ++i) {
        int v = adj[u][i].second;
        adj[u][i].first = f[v];
    }
    sort (adj[u].begin(), adj[u].end());
    f[u] = c[u];
    f[u] = min(f[u], adj[u][0].first + adj[u][1].first);
    time_out[u] = timer;
}

void init(int u, int par) {
    if ((int)adj[u].size() == 1) {
        return;
    }
    for (auto [c, v] : adj[u]) {
        if (v == par) continue;
        sum[v] = sum[u];
        if (v == adj[u][0].second) {
            sum[v] += adj[u][1].first;
        } else {
            sum[v] += adj[u][0].first;
        }
        init(v, u);
    }
}

bool isPar(int u, int v) {
    return time_in[u] <= time_in[v] && time_out[v] <= time_out[u];
}

void solve() {
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        cin >> c[i];
    }
    adj.assign(n + 1, vector<pair<int, int>>());
    for (int i = 1; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(make_pair(c[v], v));
        adj[v].push_back(make_pair(c[u], u));
    }

    timer = 0;
    dfs(1, -1);
    sum[1] = 0;
    init(1, -1);

    for (int i = 1; i <= m; ++i) {
        int x, y;
        cin >> x >> y;
        if (x == y) {
            cout << 0 << '\n';
            continue;
        }
        if (!isPar(y, x)) {
            cout << -1 << '\n';
            continue;
        }
        cout << sum[x] - sum[y] << '\n';
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
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}