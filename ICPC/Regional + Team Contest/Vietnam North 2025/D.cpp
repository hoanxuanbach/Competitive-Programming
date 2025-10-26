#pragma GCC optimize("O3,unroll-loops")
#include <bits/stdc++.h>

using namespace std;
long long n, m, k, mod;

void add(long long &x, const long long &y) {
    x += y;
    if (x >= mod) x -= mod;
}
void sub(long long &x, const long long &y) {
    x -= y;
    if (x < 0) x += mod;
}
long long mul(long long x, const long long &y) {
    x %= mod;
    x = (x * (y % mod)) % mod;
    return x;
}
long long power(long long x, long long y) {
    x %= mod;
    long long res = 1;
    while (y) {
        if (1 & y) {
            res = mul(res, x);
        }
        x = mul(x, x);
        y /= 2;
    }
    return res;
}

void solve() {
    cin >> n >> k >> m >> mod;
    if (k == 1) {
        cout << n % mod;
        return;
    }

    long long res = n;
    res = mul(res, power(m, k - 1));
    long long tmp = m * (m + 1) / 2 % mod;
    tmp = mul(tmp, k - 1);
    tmp = mul(tmp, power(m, k - 2));
    sub(res, tmp);
    cout << res;
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
