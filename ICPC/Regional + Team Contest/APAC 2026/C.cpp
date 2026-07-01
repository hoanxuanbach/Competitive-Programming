#include <bits/stdc++.h>
#define pii pair<int, int>
#define fi first
#define se second
#define int long long

using namespace std;
const int N = 2e5 + 7;
const int MAX = 1e9;
const int INF = 1e18 + 7;

struct Edge {
    int u, v, w;
} edges[N];

int n, m, ok, vis[N], pos[N];
int s[N], dist[N];
vector<vector<pii>> adj;

int timer;

void dfs(int u) {
    vis[u] = ++ timer;
    if (s[timer] != u) {
        ok = 0;
        return;
    }

    // cout << "dfs " << u << '\n';

    vector<pair<int, int>> ed;

    for (auto [v, i] : adj[u]) {
        if (vis[v]) continue ;
        ed.push_back({v, i});
    }

    sort(ed.begin(), ed.end(), [&](const pair<int, int>&a, const pair<int, int>& b){
        return pos[a.first] < pos[b.first];
    });

    int ww = ed.size();

    for (auto [v, i] : ed) {
        edges[i].w = ww;
        ww --;
        if (vis[v]) continue;
        dfs(v);
    }
}

void solve() {
    cin >> n >> m;
    adj.assign(n + 1, vector<pii>());
    ok = 1;
    for (int i = 1; i <= m; ++i) {
        cin >> edges[i].u >> edges[i].v;
        edges[i].w = 1;
        adj[edges[i].u].push_back(make_pair(edges[i].v, i));
        adj[edges[i].v].push_back(make_pair(edges[i].u, i));
    }

    for (int i = 1; i <= n; ++i) cin >> s[i], pos[s[i]] = i;

    dfs(1);

    if (ok) {
        for (int i = 1; i <= m; i++) {
            cout << edges[i].w << ' ';
        }
    } else {
        cout << "impossible\n";
    }
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