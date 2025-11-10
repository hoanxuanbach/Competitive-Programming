#pragma GCC optimize("O3,unroll-loops")
#include <bits/stdc++.h>

using namespace std;
const int N = 2e5 + 7;

struct Node {
    int cnt[2];
    int rem[2];
    multiset<int> s;
    Node() {
        cnt[0] = cnt[1] = 0;
        rem[0] = rem[1] = 0;
    }

    Node(int x, int y) {
        cnt[0] = cnt[1] = 0;
        rem[0] = rem[1] = 0;
        if (x == y && x != 0) {
            return;
        }
        if (x == 0) {
            cnt[0] = 1;
        } else {
            s.insert(x);
            rem[0] = 1;
        }

        if (y == 0) {
            cnt[1] = 1;
        } else {
            s.insert(-y);
            rem[1] = 1;
        }
    }
};

int n, a[N], b[N], res[N];
vector<vector<int>> adj;
vector<Node> nodes;

void dfs(int u, int par) {
    nodes[u] = Node(a[u], b[u]);
    for (int v : adj[u]) {
        if (v == par) continue;
        dfs(v, u);

        if (nodes[u].s.size() < nodes[v].s.size()) {
            swap(nodes[u], nodes[v]);
        }

        for (int x: nodes[v].s) {
            auto itr = nodes[u].s.lower_bound(-x);
            if (itr != nodes[u].s.end() && *itr == -x) {
                nodes[u].s.erase(itr);
                if (x < 0) {
                    nodes[u].rem[0]--;
                } else {
                    nodes[u].rem[1]--;
                }
            } else {
                nodes[u].s.insert(x);
                if (x < 0) {
                    nodes[u].rem[1]++;
                } else {
                    nodes[u].rem[0]++;
                }
            }
        }

        nodes[u].cnt[0] += nodes[v].cnt[0];
        nodes[u].cnt[1] += nodes[v].cnt[1];
    }

    if (nodes[u].cnt[0] >= nodes[u].rem[1] && nodes[u].cnt[1] >= nodes[u].rem[0]) {
        res[u] = 1;
    } else {
        res[u] = 0;
    }

    // cout << u << ":\n";
    // for (auto x: nodes[u].s) {
    //     cout << x << " ";
    // }
    // cout << '\n';
    // cout << nodes[u].cnt[0] << " " << nodes[u].cnt[1] << " " << nodes[u].rem[0] << " " << nodes[u].rem[1] << '\n';
}

void solve() {
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    for (int i = 1; i <= n; ++i) {
        cin >> b[i];
    }
    adj.assign(n + 1, vector<int>());
    nodes.assign(n + 1, Node());
    for (int i = 1; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(1, 0);
    for (int i = 1; i <= n; ++i) {
        cout << res[i];
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
