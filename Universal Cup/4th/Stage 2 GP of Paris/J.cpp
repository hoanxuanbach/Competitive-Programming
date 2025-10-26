#pragma GCC optimize("O3,unroll-loops")
#include <bits/stdc++.h>
#define int long long

using namespace std;
const int N = 1e5 + 7;
const long long INF = 5e18 + 7;

struct Query {
    int pos;
    long long value;
}queries[N];

struct SegmentTree {
    vector<long long> tree;
    vector<long long> lazy;
    int n;

    SegmentTree(int _n = 0) {
        n = _n;
        tree.assign(n * 4 + 7, 0);
        lazy.assign(n * 4 + 7, 0);
    }

    void down(int id) {
        for (int i = id * 2; i <= id * 2 + 1; ++i) {
            tree[i] += lazy[id];
            lazy[i] += lazy[id];
        }
        lazy[id] = 0;
    }

    void update(int id, int l, int r, int u, int v, long long value) {
        if (l > v || r < u) {
            return;
        }
        if (u <= l && r <= v) {
            tree[id] += value;
            lazy[id] += value;
            // cout << "UPDATE: " << l << " " << r << " " << u << " " << v << " " << value << " " << tree[id] << '\n';
            return;
        }
        down(id);
        int mid = (l + r) / 2;
        update(id * 2, l, mid, u, v, value);
        update(id * 2 + 1, mid + 1, r, u, v, value);
        tree[id] = min(tree[id * 2], tree[id * 2 + 1]);
    }
    void update(int l, int r, long long value) {
        update(1, 1, n, l, r, value);
    }

    long long get(int id, int l, int r, int k) {
        if (l == r) {
            return tree[id];
        }
        down(id);
        int mid = (l + r) / 2;
        if (k <= mid) {
            return get(id * 2, l, mid, k);
        }
        return get(id * 2 + 1, mid + 1, r, k);
    }
    long long get(int k) {
        return get(1, 1, n, k);
    }

    int findFirst(int id, int l, int r, long long value) {
        if (l == r) {
            return l - 1;
        }
        down(id);
        int mid = (l + r) / 2;
        if (tree[id * 2] <= value) {
            return findFirst(id * 2, l, mid, value);
        }
        return findFirst(id * 2 + 1, mid + 1, r, value);
    }
    int findFirst(long long value) {
        if (tree[1] > value) {
            return n;
        }
        return findFirst(1, 1, n, value);
    } 
};

int n, q;
long long u, r;
long long s[N];

void solve() {
    cin >> n >> u >> r;
    for (int i = 1; i <= n; ++i) {
        cin >> s[i];
    }
    cin >> q;
    for (int i = 1; i <= q; ++i) {
        cin >> queries[i].pos >> queries[i].value;
    }

    if (u >= n - 1) {
        long long sum = 0;
        for (int i = 1; i <= n; ++i) {
            sum += s[i];
        }
        cout << sum << '\n';
        for (int i = 1; i <= q; ++i) {
            sum += queries[i].value - s[queries[i].pos];
            s[queries[i].pos] = queries[i].value;
            cout << sum << '\n';
        }
        return;
    }

    SegmentTree it1 = SegmentTree(n); // i -> i - u
    SegmentTree it2 = SegmentTree(n); // 1 -> i

    it1.update(1, u + 1, INF);
    for (int i = 1; i <= n; ++i) {
        it2.update(i, n, s[i]);
        it1.update(i + 1, (i + u >= n ? n : i + u), s[i]);
    }

    cout << it2.get(it1.findFirst(r)) << '\n';

    for (int i = 1; i <= q; ++i) {
        // cout << "=============\n";
        it2.update(queries[i].pos, n, queries[i].value - s[queries[i].pos]);
        it1.update(queries[i].pos + 1, (queries[i].pos + u >= n ? n : queries[i].pos + u), queries[i].value - s[queries[i].pos]);
        s[queries[i].pos] = queries[i].value;
        // cout << it1.findFirst(r) << '\n';
        cout << it2.get(it1.findFirst(r)) << '\n';
    }

}

signed main() {
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