#include <bits/stdc++.h>
#define pii pair<int, int>
#define fi first
#define se second

using namespace std;
const int N = 303;
const int M = N * N;
const long long INF = 1e18 + 7;

int n;
vector<pii> adj[M];
long long dist[M];
int par[M];
map<int, pii> value;

int encode(int i, int j) {
    int x = (i - 1) * i / 2 + j;
    value[x] = {i, j};
    return x;
}

pii decode(int x) {
    return value[x];
}

void dijkstra() {
    for (int i = 1; i <= n * (n + 1) / 2; ++i) {
        dist[i] = INF;
    }
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
    dist[1] = 0;
    pq.push({0, 1});
    while (!pq.empty()) {
        long long d = pq.top().first;
        int u = pq.top().second;
        pq.pop();
        if (d > dist[u]) continue;
        for (auto [v, w] : adj[u]) {
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                par[v] = u;
                pq.push({dist[v], v});
            }
        }
    }
}

void removeEdge(int x, int y) {
    // cout << "removeEdge " << x << ' ' << y << '\n';
    for (int i = 0; i < adj[x].size(); ++i) {
        if (adj[x][i].first == y) {
            adj[x].erase(adj[x].begin() + i);
            break;
        }
    }
    for (int i = 0; i < adj[y].size(); ++i) {
        if (adj[y][i].first == x) {
            adj[y].erase(adj[y].begin() + i);
            break;
        }
    }
}

void init() {
    dijkstra();
    vector<int> nodes;
    int t = n * (n + 1) / 2;
    while (t != 1) {
        nodes.push_back(t);
        t = par[t];
    }
    nodes.push_back(1);
    reverse(nodes.begin(), nodes.end());
    for (int i = 0; i + 1 < nodes.size(); ++i) {
        // cout << "init " << nodes[i] << ' ' << nodes[i + 1] << '\n';
        removeEdge(nodes[i], nodes[i + 1]);
    }
}

vector<int> eulerTour() {
    stack<int> st;
    st.push(1);
    vector<int> res;
    while (!st.empty()) {
        int v = st.top();
        if (adj[v].empty()) {
            res.push_back(v);
            st.pop();
        } else {
            auto [u, w] = adj[v].back();
            st.push(u);
            removeEdge(v, u);
        }
    }
    reverse(res.begin(), res.end());
    return res;
}

void solve() {
    cin >> n;
    value.clear();
    long long sum = 0;
    for (int i = 1; i < n; ++i) {
        for(int j = 1; j <= i; ++j) {
            int w;
            cin >> w;
            sum += w;
            adj[encode(i, j)].push_back({encode(i + 1, j), w});
            adj[encode(i + 1, j)].push_back({encode(i, j), w});
        }
    }

    for (int i = 1; i < n; ++i) {
        for (int j = 1; j <= i; ++j) {
            int w;
            cin >> w;
            sum += w;
            adj[encode(i, j)].push_back({encode(i + 1, j + 1), w});
            adj[encode(i + 1, j + 1)].push_back({encode(i, j), w});
        }
    }

    for (int i = 1; i < n; ++i) {
        for (int j = 1; j <= i; ++j) {
            int w;
            cin >> w;
            sum += w;
            adj[encode(i + 1, j)].push_back({encode(i + 1, j + 1), w});
            adj[encode(i + 1, j + 1)].push_back({encode(i + 1, j), w});
        }
    }

    init();
    vector<int> tour = eulerTour();
    sum -= dist[n * (n + 1) / 2];
    cout << sum << '\n';
    cout << tour.size() << '\n';
    for (int x : tour) {
        auto [i, j] = decode(x);
        cout << i << ' ' << j << ' ';
    }
    cout << '\n';
}

int main() {
#ifdef LOCAL
    freopen("main.inp", "r", stdin);
    freopen("main.out", "w", stdout);
#endif
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
