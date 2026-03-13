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
    cin >> testcases;
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

const int N = 1e5 + 5, mod = 998244353;

int n, m, a[N], cnt[N];

void Hollwo_Pelw(){
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    if (a[1] != 0) {
        return cout << 0 << '\n', (void) 0;
    }

    for (int i = 2; i <= n; i++) {
        if (a[i] > a[i - 1] + 1) {
            return cout << 0 << '\n', (void) 0;
        }
    }

    for (int i = 0; i < n; i++) {
        cnt[i] = (a[i + 1] == 0) + (i > 0 ? cnt[a[i]] : 0);
    }

    int res = m % mod;

    for (int i = 2; i <= n; i++) {
        if (a[i] == 0) {
            res = res * max(0ll, m - cnt[a[i - 1]]) % mod;
        } else {
            if (a[i] != a[i - 1] + 1) {
                int p = a[i - 1];
                for (; p && p + 1 > a[i]; p = a[p]) {
                    if (a[p + 1] == a[i]) {
                        return cout << 0 << '\n', (void) 0;
                    }
                }
                if (p + 1 != a[i]) {
                    return cout << 0 << '\n', (void) 0;
                }
            }
        }
    }

    cout << res << '\n';
}