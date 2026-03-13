#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 7;
const int C = 1e6 + 7;
const int logn = 18;

int n, c[N], value[N], prime[C];
vector<vector<int>> adj;
int time_in[N], time_out[N], timer = 0;
int FAI[N], euler[N * 2][logn+1], h[N], idx;
vector<vector<int>> nodes;

struct Query {
    int a, u, v;
} q[N];

struct BinaryIndexTree {
    vector<int> tree;
    int n;
    BinaryIndexTree(int _n = 0) {
        n = _n;
        tree.assign(n+1, 0);
    }

    void update(int l, int r, int x) {
        for (int i = l; i <= n; i += i & -i) {
            tree[i] += x;
        }
        for (int i = r+1; i <= n; i += i & -i) {
            tree[i] -= x;
        }
    }

    int get(int p) {
        int res = 0;
        for (int i = p; i > 0; i -= i & -i) {
            res += tree[i];
        }
        return res;
    }
}bit;

void sieve() {
    for (int i = 2; i < C; ++i) {
        if (prime[i]) continue;
        prime[i] = i;
        for (long long j = 1LL * i * i; j < C; j += i) {
            if (!prime[j]) prime[j] = i;
        }
    }

}

void init(int u) {
    time_in[u] = ++timer;
    euler[++idx][0] = u;
    FAI[u] = idx;

    for (int v : adj[u]) {
        h[v] = h[u] + 1;
        init(v);
        euler[++idx][0] = u;
    }
    time_out[u] = timer;
}

int choice(int u, int v) {
    return h[u] < h[v] ? u : v;
}

int lca(int u, int v) {
    int l = FAI[u], r = FAI[v];
    if (l > r) swap(l, r);
    int k = log2(r - l + 1);
    return choice(euler[l][k], euler[r - (1 << k) + 1][k]);
}

int calc(int u, int v) {
    int w = lca(u, v);
    return bit.get(time_in[u]) + bit.get(time_in[v]) - 2 * bit.get(time_in[w]) + value[w];
}

vector<pair<int, int>> split(int x) {
    vector<pair<int, int>> res;
    while (x > 1) {
        int p = prime[x];
        int cnt = 0;
        while (x % p == 0) {
            x /= p;
            cnt++;
        }
        res.push_back({p, cnt});
    }
    return res;
}

void solve() {
    cin >> n >> c[1];
    adj.assign(n+1, vector<int>());
    nodes.assign(C, vector<int>());
    for (int i = 2; i <= n; ++i) {
        int u, v, a; cin >> a >> u >> v;
        q[i] = {a, u, v};
        c[i] = a;
        adj[v].push_back(i);
    }

    timer = 0;
    idx = 0;
    init(1);
    for (int j = 1; (1 << j) <= idx; ++j) {
        for (int i = 1; i + (1 << j) - 1 <= idx; ++i) {
            euler[i][j] = choice(euler[i][j-1], euler[i + (1 << (j-1))][j-1]);
        }
    }

    vector<vector<pair<int, int>>> prime_factor(n + 1);
    for (int i = 1; i <= n; ++i) {
        prime_factor[i] = split(c[i]);
    }

    set<int> unique_primes;
    for (int i = 1; i <= n; ++i) {
        for (auto [p, _] : prime_factor[i]) {
            unique_primes.insert(p);
        }
    }

    for (int p : unique_primes) {
        nodes[p].clear();
    }
    for (int i = 1; i <= n; ++i) {
        for (auto [p, _] : prime_factor[i]) {
            nodes[p].push_back(i);
        }
    }

    bit = BinaryIndexTree(n);

    for (int p : unique_primes) {
        for (int i : nodes[p]) {
            int cur = 0;
            for (auto [prime, exp] : prime_factor[i]) {
                if (prime == p) {
                    cur = exp;
                    break;
                }
            }
            if (i == 1) {
                value[i] = cur;
                bit.update(time_in[i], time_out[i], cur);
            } else {
                int tmp = calc(q[i].u, q[i].v);
                int g = min(cur, tmp);
                value[i] = cur - g;
                for (int j = 1; j <= g; ++j) {
                    c[i] /= p;
                }
                bit.update(time_in[i], time_out[i], value[i]);
            }
        }

        for (int i : nodes[p]) {
            bit.update(time_in[i], time_out[i], -value[i]);
            value[i] = 0;
        }
    }

    for (int i = 1; i <= n; ++i) {
        cout << c[i] << " ";
    }
    cout << '\n';
}

int main(){
#ifdef LOCAL
    freopen("main.inp", "r", stdin);
    freopen("main.out", "w", stdout);
#endif
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    sieve();
    int num_test = 1; //cin >> num_test;
    while (num_test--) {
        solve();
    }
}