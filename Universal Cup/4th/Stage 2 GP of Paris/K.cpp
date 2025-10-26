#pragma GCC optimize("O3,unroll-loops")
#include <bits/stdc++.h>

using namespace std;
const int N = 2e5 + 7;
const int Q = 5e5 + 7;
const int mod = 998244353;

struct Query {
    int l, r;
    int miss = 1;
    long long need = 0;
    long long k;
}queries[Q];

struct BinaryIndexTree {
    vector<long long> sum;
    int n;

    BinaryIndexTree(int _n = 0) {
        n = _n;
        sum.assign(n + 7, 0);
    }

    void update(int i, int x) {
        for (; i <= n; i += (i & -i)) {
            sum[i] += x;
        }
    }

    long long getSum(int i) {
        long long res = 0;
        for (; i >= 1; i -= (i & -i)) {
            res += sum[i];
        }
        return res;
    }

    long long getSum(int l, int r) {
        return getSum(r) - getSum(l - 1);
    }
};

void add(int &x, const int &y) {
    x += y;
    if (x >= mod) {
        x -= mod;
    }
}

void sub(int &x, const int &y) {
    x -= y;
    if (x < 0) {
        x += mod;
    }
}

int product(int x, int y) {
    return 1LL * x * y % mod;
}

struct SegmentTree {
    vector<int> tree;
    int n;
    SegmentTree(int _n = 0) {
        n = _n;
        tree.assign(n * 4 + 7, 1);
    }

    void update(int id, int l, int r, int x, int v) {
        if (l == r) {
            tree[id] = v;
            return;
        }
        int mid = (l + r) / 2;
        if (x <= mid) {
            update(id * 2, l, mid, x, v);
        } else {
            update(id * 2 + 1, mid + 1, r, x, v);
        }
        tree[id] = product(tree[id * 2], tree[id * 2 + 1]);
    }

    void update(int x, int v) {
        update(1, 1, n, x, v);
    }

    int get(int id, int l, int r, int u, int v) {
        if (l > v || r < u) {
            return 1;
        }
        if (u <= l && r <= v) {
            return tree[id];
        }
        int mid = (l + r) / 2;
        int tmp1 = get(id * 2, l, mid, u, v);
        int tmp2 = get(id * 2 + 1, mid + 1, r, u, v);
        return product(tmp1, tmp2);
    }

    int get(int l, int r) {
        return get(1, 1, n, l, r);
    }
};

int n, q, a[N], sorted_a[N], pos[Q];
long long sum[N];
int res[Q];

long long getSum(int l, int r) {
    return sum[r] - (l == 0 ? 0 : sum[l - 1]);
}

void init() {
    a[0] = 0;
    sum[0] = 0;
    for (int i = 1; i <= n; ++i) {
        sum[i] = sum[i - 1] + a[i];
    }

    sort(sorted_a + 1, sorted_a + n + 1, [&](const int &x, const int &y) {
        if (a[x] == a[y]) {
            return x < y;
        }
        return a[x] > a[y];
    });

    int loop = log2(n) + 1;
    vector<int> l(q + 1, 0);
    vector<int> r(q + 1, n);

    for (int i = 1; i <= q; ++i) {
        pos[i] = n;
    }

    while(loop--) {
        vector<vector<int>> vt(n + 1, vector<int>());
        for (int i = 1; i <= q; ++i) {
            if (l[i] > r[i]) {
                continue;
            }
            int mid = (l[i] + r[i]) / 2;
            vt[mid].push_back(i);
        }

        BinaryIndexTree bit1 = BinaryIndexTree(n);
        BinaryIndexTree bit2 = BinaryIndexTree(n);
        for (int i = 0; i <= n; ++i) {
            if (i != 0) {
                bit1.update(sorted_a[i], a[sorted_a[i]]);
                bit2.update(sorted_a[i], 1);
            }
            for (int qid : vt[i]) {
                int ql = queries[qid].l;
                int qr = queries[qid].r;
                int cnt = qr - ql + 1 - bit2.getSum(ql, qr);
                long long need = getSum(ql, qr) - bit1.getSum(ql, qr) - cnt;
                // cout << qid << " " << need << " " << queries[qid].k << '\n';
                if (need <= queries[qid].k) {
                    queries[qid].need = need;
                    pos[qid] = i;
                    r[qid] = i - 1;
                } else {
                    l[qid] = i + 1;
                }
            }
        }
    }

    // for (int i = 1; i <= n; ++i) {
    //     cout << sorted_a[i] << " " << a[sorted_a[i]] << '\n';
    // }
    for (int i = 1; i <= q; ++i) {
        // cout << "POS: " << i << " " << pos[i] << '\n';
        if (pos[i] == 0) {
            continue;
        }
        long long tmp = queries[i].k - queries[i].need;
        queries[i].miss = a[sorted_a[pos[i]]] - tmp;
    }
}

void solve() {
    cin >> n >> q;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        sorted_a[i] = i;
    }
    for (int i = 1; i <= q; ++i) {
        cin >> queries[i].l >> queries[i].r >> queries[i].k;
    }
    init();

    vector<vector<int>> vt(n + 1);
    for (int i = 1; i <= q; ++i) {
        if (pos[i] == 0) {
            res[i] = 1;
            continue;
        }
        vt[pos[i]].push_back(i);
    }

    SegmentTree it = SegmentTree(n);
    for (int i = 1; i <= n; ++i) {
        for (int id : vt[i]) {
            res[id] = it.get(queries[id].l, queries[id].r);
            res[id] = product(res[id], queries[id].miss);
        }
        it.update(sorted_a[i], a[sorted_a[i]]);
    }

    for (int i = 1; i <= q; ++i) {
        cout << res[i] << "\n";
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