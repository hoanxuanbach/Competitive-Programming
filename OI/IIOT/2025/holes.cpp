#include <iostream>
using namespace std;
long long int f[1000005], g[1000005], mod, d[1000005], ff[1000005];
long long int power(long long int x, long long int y) {
    long long int res = 1;
    while (y) {
        if (y & 1) res = res * x % mod;
        x = x * x % mod;
        y >>= 1;
    }
    return res;
}
long long int C(long long int n, long long int k) {
    return f[n] * g[k] % mod * g[n - k] % mod;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int n;
    cin >> n >> mod;
    f[0] = 1;
    for (int i = 1; i <= n; i++) {
        f[i] = f[i - 1] * i % mod;
    }
    g[n] = power(f[n], mod - 2);
    for (int i = n - 1; i >= 0; i--) {
        g[i] = g[i + 1] * (i + 1) % mod;
    }
    d[0] = ff[0] = 1;
    long long int c = 0;
    for (int i = 1; i <= n; i++) {
        c = (c + ff[i - 1]) % mod;
        d[i] = c * f[i - 1] % mod;
        ff[i] = d[i] * g[i] % mod;
        c = c * 2 % mod;
    }
    for (int i = 0; i <= n; i++) {
        cout << C(n, i) * d[i] % mod * d[n - i] % mod << " ";
    }
}
