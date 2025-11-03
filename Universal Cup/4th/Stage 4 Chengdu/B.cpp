#pragma GCC optimize("O3,unroll-loops")
#include <bits/stdc++.h>
#define BIT(x, i) (((x) >> (i)) & 1)

using namespace std;
const int N = 6;
const long long INF = 1e18 + 7;

struct Matrix {
    int n;
    vector<vector<long long>> a;

    Matrix(int _n = 0) {
        n = _n;
        a.assign(n, vector<long long>(n, 0));
    }

    Matrix operator * (const Matrix &other) const {
        Matrix res(n);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                for (int k = 0; k < n; ++k) {
                    res.a[i][j] = max(res.a[i][j], a[i][k] + other.a[k][j]);
                }
            }
        }
        return res;
    }

    Matrix power(int k) const {
        if (k == 1) {
            return *this;
        }
        Matrix tmp = power(k / 2);
        if (k & 1) {
            return tmp * tmp * (*this);
        }
        return tmp * tmp;
    }
};

int n, m, k, r;
int a[N], c[N];

void solve() {
    cin >> n >> m >> k >> r;
    for (int i = 0; i < n; ++i) {
        cin >> a[i] >> c[i];
    }

    Matrix base(1 << n);
    for (int mask1 = 0; mask1 < (1 << n); ++mask1) {
        for (int mask2 = 0; mask2 < (1 << n); ++mask2) {
            int cost = 0, damage = 0;
            for (int i = 0; i < n; ++i) {
                if (BIT(mask2, i)) {
                    damage += a[i];
                    if (BIT(mask1, i)) {
                        cost += c[i] + k;
                    } else {
                        cost += c[i];
                    }
                }
            }
            if (cost > m) {
                base.a[mask1][mask2] = -INF;
            } else {
                base.a[mask1][mask2] = damage;
            }
        }
    }
    Matrix tmp = base.power(r);
    long long res = 0;
    for (int mask = 0; mask < (1 << n); ++mask) {
        res = max(res, tmp.a[0][mask]);
    }

    cout << res << '\n';
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