#pragma GCC optimize("O3,unroll-loops")
#include <bits/stdc++.h>

using namespace std;
const int INF = 1e9 + 7;
const int N = 2e5 + 7;
const int K = 330;

struct Query {
    int type, u, v;
}queries[N];

int n, m, q;
bitset<K * 2 + 7> bs[N];
vector<int> adj[N], newAdj[N];
int idx[N];
int low[N], num[N], in[N], timer, cnt;
bool visited[N];
stack<int> st;

void tarjan(int u) {
    low[u] = num[u] = ++timer;
    st.push(u);
    for (int v : adj[u]) {
        if (num[v]) {
            low[u] = min(low[u], num[v]);
        } else {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        }
    }

    if (low[u] == num[u]) {
        int v;
        ++cnt;
        do {
            v = st.top();
            st.pop();
            low[v] = num[v] = INF;
            in[v] = cnt;
        } while(v != u);
    }
}

void init(int u) {
    visited[u] = true;
    for (int v : newAdj[u]) {
        if (!visited[v]) {
            init(v);
        }
        bs[u] |= bs[v];
    }
    if (idx[u] != -1) {
        bs[u].set(idx[u]);
    }
}

void solve() {
    cin >> n >> m;
    for (int i = 1; i <= m; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
    }
    cin >> q;
    for (int i = 1; i <= q; ++i) {
        cin >> queries[i].type >> queries[i].u >> queries[i].v;
        if (queries[i].type == 1) {
            int u, v;
            if (queries[i].v == 0) {
                u = queries[i].u, v = ++n;
            } else {
                u = ++n, v = queries[i].u;
            }
            queries[i].u = u;
            queries[i].v = v;
        }
    }
    memset(idx, -1, sizeof(idx));
    for (int i = 1; i <= q; i += K) {
        for (int u = 1; u <= n; ++u) {
            low[u] = num[u] = 0;
            newAdj[u].clear();
            visited[u] = false;
            bs[u].reset();
            idx[u] = -1;
            in[u] = 0;
        }
        cnt = 0, timer = 0;
        for (int u = 1; u <= n; ++u) {
            if (!num[u]) {
                tarjan(u);
            }
        }

        vector<int> nodes;
        for (int j = i; j <= min(q, i + K - 1); ++j) {
            nodes.push_back(in[queries[j].u]);
            nodes.push_back(in[queries[j].v]);
        }
        sort(nodes.begin(), nodes.end());
        nodes.erase(unique(nodes.begin(), nodes.end()), nodes.end());
        int sz = (int)nodes.size();
        for (int j = 0; j < sz; ++j) {
            idx[nodes[j]] = j;
        }

        for (int u = 1; u <= n; ++u) {
            for (int v : adj[u]) {
                newAdj[in[u]].push_back(in[v]);
            }
        }
        for (int u = 1; u <= n; ++u) {
            if (!visited[u]) {
                init(u);
            }
        }

        for (int j = i; j <= min(q, i + K - 1); ++j) {
            if (queries[j].type == 1) {
                int u = queries[j].u;
                int v = queries[j].v;
                adj[u].push_back(v);

                u = in[u], v = in[v];
                bs[u] |= bs[v];
                for (int x : nodes) {
                    if (bs[x][idx[u]]) {
                        bs[x] |= bs[u];
                    }
                }
            } else {
                int u = queries[j].u, v = queries[j].v;
                u = in[u], v = in[v];
                if (bs[u][idx[v]]) {
                    cout << "Yes\n";
                } else {
                    cout << "No\n";
                }
            }
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