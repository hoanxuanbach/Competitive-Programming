/*
#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx2,fma,bmi,bmi2,sse4.2,popcnt,lzcnt")
*/

#include <bits/stdc++.h>
#define taskname ""
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define i64 long long
#define isz(x) (int)x.size()
using namespace std;

void solve() {
    int n;
    cin >> n;

    vector a(n, vector(n, vector(n, 0)));
    for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) for (int k = 0; k < n; ++k) {
        cin >> a[i][j][k];
    }

    vector mask(n + 1, vector<int>());
    for (int i = 0; i < 1 << n; ++i) {
        mask[__builtin_popcount(i)].emplace_back(i);
    }

    vector dp(1 << n, vector(1 << n, (int)1e9));
    dp[0][0] = 0;
    for (int i = 0; i < n; ++i) {
        for (int m1 : mask[i]) for (int x = 0; x < n; ++x) if (~m1 >> x & 1)
        for (int m2 : mask[i]) for (int y = 0; y < n; ++y) if (~m2 >> y & 1) {
            dp[m1 ^ (1 << x)][m2 ^ (1 << y)] = min(dp[m1 ^ (1 << x)][m2 ^ (1 << y)], dp[m1][m2] + a[i][x][y]);
        }
    }
    cout << dp[(1 << n) - 1][(1 << n) - 1] << endl;
}

signed main() {

#ifndef CDuongg
    if (fopen(taskname".inp", "r"))
        assert(freopen(taskname".inp", "r", stdin)), assert(freopen(taskname".out", "w", stdout));
#else
    freopen("bai3.inp", "r", stdin);
    freopen("bai3.out", "w", stdout);
    auto start = chrono::high_resolution_clock::now();
#endif

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1; //cin >> t;
    while(t--) solve();

#ifdef CDuongg
   auto end = chrono::high_resolution_clock::now();
   cout << "\n"; for(int i = 1; i <= 100; ++i) cout << '=';
   cout << "\nExecution time: " << chrono::duration_cast<chrono::milliseconds> (end - start).count() << "[ms]" << endl;
#endif

}
