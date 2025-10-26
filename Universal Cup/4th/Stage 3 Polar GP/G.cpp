#pragma GCC optimize("O3,unroll-loops")
#include <bits/stdc++.h>

using namespace std;
const int K = 500;
const int N = 1e5 + 7;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int randnum(int l, int r) {
    return rng() % (r - l + 1) + l;
}

int n, m, q;
int dist[K][N], nodes[K];
vector<vector<int>> adj;
bool vis[N];

struct DisjointSet {
    vector<int> lab;
    int n;
    DisjointSet(int n) : n(n) {
        lab.assign(n + 1, -1);
    }
    int root(int u) {
        return lab[u] < 0 ? u : lab[u] = root(lab[u]);
    }
    bool merge(int u, int v) {
        u = root(u); v = root(v);
        if (u == v) return false;
        if (lab[u] > lab[v]) swap(u, v);
        lab[u] += lab[v];
        lab[v] = u;
        return true;
    }
    bool same(int u, int v) {
        return root(u) == root(v);
    }
};

void bfs(int idx) {
    memset(dist[idx], 0x3f, sizeof(dist[idx]));
    queue<int> q;
    dist[idx][nodes[idx]] = 0;
    q.push(nodes[idx]);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : adj[u]) {
            if (dist[idx][v] > dist[idx][u] + 1) {
                dist[idx][v] = dist[idx][u] + 1;
                q.push(v);
            }
        }
    }
}

void solve() {
    cin >> n >> m >> q;
    adj.assign(n + 1, vector<int>());
    DisjointSet dsu(n);
    for (int i = 1; i <= m; ++i) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        dsu.merge(u, v);
    }

    for (int i = 0; i < K; ++i) {
        for (int j = 1; j <= 10; ++j) {
            nodes[i] = randnum(1, n);
            if (!vis[nodes[i]]) {
                vis[nodes[i]] = true;
                break;
            }
        }
        bfs(i);
    }

    while(q--) {
        int u, v;
        cin >> u >> v;
        if (u == v) {
            cout << "NO\n";
            continue;
        }
        if (!dsu.same(u, v)) {
            cout << "YES\n";
            continue;
        }
        int w = dsu.root(u);
        if (-dsu.lab[w] <= 20000) {
            cout << "NO\n";
            continue;
        }
        bool check = false;
        for (int i = 0; i < K; ++i) {
            if (dist[i][u] + dist[i][v] <= 20000) {
                check = true;
                break;
            }
        }
        if (!check) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
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