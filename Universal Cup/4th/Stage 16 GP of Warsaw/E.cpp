#include <bits/stdc++.h>
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/trie_policy.hpp>
// #include <ext/rope>

using namespace std;
// using namespace __gnu_cxx;
// using namespace __gnu_pbds;

void Hollwo_Pelw();

signed main(){
#ifndef hollwo_pelw_local
    if (fopen(".inp", "r"))
        assert(freopen(".inp", "r", stdin)), assert(freopen(".out", "w", stdout));
#else
    using namespace chrono;
    auto start = steady_clock::now();
#endif
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
    int testcases = 1;
    // cin >> testcases;
    for (int test = 1; test <= testcases; test++){
        // cout << "Case #" << test << ": ";
        Hollwo_Pelw();
    }
#ifdef hollwo_pelw_local
    auto end = steady_clock::now();
    cout << "\nExecution time : " << duration_cast<milliseconds> (end - start).count() << "[ms]" << endl;
#endif
}

#define int long long

const int mod = 1e9 + 7;

void Hollwo_Pelw(){
    int n;
    cin >> n;
    string s;
    cin >> s;

    vector<int> pw(n + 1, 1);
    for (int i = 1; i <= n; i++) {
        pw[i] = pw[i - 1] * 3 % mod;
    }

    vector<int> dp(n + 1); // sum (all)
    vector<int> f(n + 1); // sum (after last +)
    vector<int> g(n + 1); // sum (after last *) // init to 1 if last sign = +
    vector<int> h(n + 1); // sum (before last +)

    dp[1] = f[1] = s[0] - '0';
    g[1] = 1;

    for (int i = 1; i < n; i++) {
        // choose +
        (dp[i + 1] += dp[i] + (s[i] - '0') * pw[i - 1] % mod) %= mod;
        // choose *
        (dp[i + 1] += (s[i] - '0') * f[i] % mod + h[i]) %= mod;
        // choose _
        (dp[i + 1] += 10 * f[i] % mod + (s[i] - '0') * g[i] + h[i]) %= mod;

        (f[i + 1] += (s[i] - '0') * pw[i - 1]) %= mod;
        (f[i + 1] += f[i] * (s[i] - '0')) %= mod;;
        (f[i + 1] += f[i] * 10 + (s[i] - '0') * g[i]) %= mod;

        (g[i + 1] += pw[i - 1]) %= mod;
        (g[i + 1] += f[i]) %= mod;
        (g[i + 1] += g[i]) %= mod;

        h[i + 1] = (2 * h[i] + dp[i]) % mod;

        // cout << dp[i + 1] << ' ' << f[i + 1] << ' ' << g[i + 1] << ' ' << h[i + 1] << '\n';
    }

    cout << dp[n] << '\n';
}