#include <bits/stdc++.h>

using namespace std;

const int N = 5e5 + 5;

#define int long long

int n, k, a[N], res[N];
string s;


#define sz(a) (int) (a.size())

const int mod = (119 << 23) + 1, root = 62;

typedef vector<int> vl;

int modpow(int a, int p) {
    int r = 1;
    for (; p; p >>= 1, a = (a * a) % mod) {
        if (p & 1) {
            r = (r * a) % mod;
        }
    }
    return r;
}

void ntt(vl &a) {
    int n = sz(a), L = 31 - __builtin_clz(n);
    static vl rt(2, 1);

    for (static int k = 2, s = 2; k < n; k *= 2, s++) {
        rt.resize(n);
        int z[] = {1, modpow(root, mod >> s)};
        for (int i = k; i < 2 * k; i ++) {
            rt[i] = rt[i / 2] * z[i & 1] % mod;
        }
    }

    vl rev(n);
    for (int i = 0; i < n; i++) {
        rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
    }
    for (int i = 0; i < n; i++) {
        if (i < rev[i]) {
            swap(a[i], a[rev[i]]);
        }
    }
    for (int k = 1; k < n; k *= 2) {
        for (int i = 0; i < n; i += 2 * k) {
            for (int j = 0; j < k; j++) {
                int z = rt[j + k] * a[i + j + k] % mod, &ai = a[i + j];
                a[i + j + k] = ai - z + (z > ai ? mod : 0);
                ai += (ai + z >= mod ? z - mod : z);
            }
        }
    }
}

vl conv(const vl &a, const vl &b) {
    if (a.empty() || b.empty()) return {};
    int s = sz(a) + sz(b) - 1, B = 32 - __builtin_clz(s), n = 1 << B;

    int inv = modpow(n, mod - 2);

    vl L(a), R(b), out(n);
    L.resize(n), R.resize(n);

    ntt(L), ntt(R);
    for (int i = 0; i < n; i++) {
        out[-i & (n - 1)] = L[i] * R[i] % mod * inv % mod;
    }
    ntt(out);
    return {out.begin(), out.begin() + s};
}

void solve() {
    cin >> n >> k >> s;

    int sum = 0, sumpair = 0;

    for (int i = 0; i < n; i++) {
        a[i] = s[i] - '0';
        sum += a[i];
    }

    for (int i = 1; i < n; i++) {
        if (a[i] && a[i - 1]) {
            sumpair += a[i] + a[i - 1];
        }
    }

    int sumL = 0, sumR = 0;

    for (int w = 1; w <= n; w++) {
        sumL += a[w - 1];
        sumR += a[n - w];

        int cursumpair = sumpair;
        res[w] = 4 * sum - sumL - sumR;

        // cout << "SOLVE " << w << '\n';

        // cout << sumL << ' ' << sumR << '\n';

        // cout << res[w] << '\n';

        for (int i = 0; i < n; i += w) {
            res[w] -= a[i];
            if (i && a[i - 1]) {
                cursumpair -= a[i];
            }
        }

        for (int i = w - 1; i < n; i += w) {
            res[w] -= a[i]; 
            if (i + 1 < n && a[i + 1]) {
                cursumpair -= a[i];
            }
        }

        if (n % w != 0) {
            // off
            res[w] -= a[n - 1];
        }

        res[w] -= cursumpair;
    }

    vector<int> A(a, a + n), B(n, 0);
    for (int i = 0; i < n; i++) {
        if (a[n - i - 1])
            B[i] = 1;
    }

    vector<int> C = conv(A, B);

    for (int k = 0; k < C.size(); k++) {
        int d = k - n + 1;
        res[abs(d)] -= C[k];
    }

    // for (int i = 1; i <= n; i++) {
    //     cout << i << " -> " << res[i] << '\n';
    // }

    sort(res + 1, res + n + 1, greater<int>());

    cout << res[k] << '\n';
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