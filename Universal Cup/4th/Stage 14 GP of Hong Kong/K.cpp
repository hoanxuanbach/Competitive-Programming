#include<bits/stdc++.h>

using namespace std;
const int N = 1e6 + 7;
const int mod = 998244353;
const int base = 10000019;
const int logn = 20;

void add(int &x, const int &y) {
    x += y;
    if (x >= mod) x -= mod;
}

void sub(int &x, const int &y) {
    x -= mod;
    if (x < 0) x += mod;
}

int product(int x, int y) {
    return 1LL * x * y % mod;
}

int power(int x, int y) {
    int res = 1;
    while (y) {
        if (y & 1) res = product(res, x);
        x = product(x, x);
        y >>= 1;
    }
    return res;
}

int n, a[N], g[N], nxt[N];
int pw[N], sum[N], st[N][logn + 1], v[N][logn + 1];

int get_value(int x, int len, int pref) {
    return product(x, product(sum[len], pw[pref]));
}

int get_hash(int pos, int len) {
    int res = 0;
    int mx = pos + len - 1;
    int pref = 0;
    for (int i = logn; i >= 0; --i) {
        if (st[pos][i] < mx) {
            res = res + product(pw[pref], v[pos][i]);
            if (res >= mod) res -= mod;
            pref += st[pos][i] - pos;
            pos = st[pos][i];
        }
    }

    int rem = mx - pos;
    res = res + get_value(a[pos], rem, pref);
    if (res >= mod) res -= mod;
    return res;
}

int get_pref(int pos, int len) {
    int mx = pos + len - 1;
    for (int i = logn; i >= 0; --i) {
        if (st[pos][i] < mx) {
            pos = st[pos][i];
        }
    }
    return a[pos];
}

void solve() {
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        a[i + n] = a[i];
    }

    for (int i = 2 * n; i >= 1; --i) {
        g[i] = i + 1;
        while (g[i] <= 2 * n && a[g[i]] <= a[i]) g[i] = g[g[i]];
    }

    pw[0] = 1;
    sum[0] = 1;
    for (int i = 1; i <= 2 * n; ++i) {
        pw[i] = product(pw[i - 1], base);
        sum[i] = sum[i - 1] + pw[i];
        if (sum[i] >= mod) sum[i] -= mod;
    }
    g[2 * n + 1] = 2 * n + 1;
    for (int i = 2 * n + 1; i >= 1; --i) {
        st[i][0] = g[i];
        v[i][0] = get_value(a[i], g[i] - i, 0);
        for (int j = 1; j <= logn; ++j) {
            st[i][j] = st[st[i][j - 1]][j - 1];
            v[i][j] = v[i][j - 1] + product(pw[st[i][j-1] - i], v[st[i][j - 1]][j - 1]);
            if (v[i][j] >= mod) v[i][j] -= mod;
        }
    }

    int mi = *min_element(a + 1, a + n + 1);
    int best = -1;
    for (int i = 1; i <= n; ++i) {
        if (a[i] != mi) continue;
        if (best == -1) {
            best = i;
            continue;
        }

        int l = 1, r = n, len = n + 1;
        while (l <= r) {
            int mid = (l + r) / 2;
            if (get_hash(best, mid) != get_hash(i, mid)) {
                len = mid;
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }

        if (get_pref(best, len) > get_pref(i, len)) {
            best = i;
        }
    }

    int mx = a[best];
    for (int i = 1; i <= n; ++i) {
        mx = max(mx, a[best + i - 1]);
        cout << mx << " ";
    }
    cout << '\n';
}
 
signed main(){
#ifdef LOCAL
    freopen("main.inp", "r", stdin);
    freopen("main.out", "w", stdout);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1; cin >> test;
    while(test--) solve();
}