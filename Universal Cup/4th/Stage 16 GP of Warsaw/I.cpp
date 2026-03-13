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

inline int binpow(int a, int x, int mod) {
    int r = 1;
    for (; x; a = a * a % mod, x >>= 1) {
        if (x & 1) {
            r = r * a % mod;
        }
    }
    return r;
}

void Hollwo_Pelw(){
    int n, q, mod;

    cin >> n >> q >> mod;

    priority_queue<int> pq;

    vector<int> a(q);
    for (int i = 0, x; i < q; i++) {
        cin >> x;
        a[i] = x;
        pq.push(x);
    }

    int cnt = n - a[q - 1];

    while (pq.size() >= 2) {
        int x = pq.top(); pq.pop();
        int y = pq.top(); pq.pop();

        if (y * 2 <= x) {
            cnt += (x - y * 2 + 1) / 2;
            pq.push(y);
        } else if (x == y) {
            pq.push(y);
            continue;
        } else {
            int d = x - y;
            int z = pq.empty() ? 0 : pq.top();

            // x - d * a, y - d * a

            int a = max(1ll, (y - z) / d);
            pq.push(x - d * a);
            pq.push(y - d * a);
        }
    }

    cnt += (pq.top() + 1) / 2;

    cout << binpow(2, cnt, mod) << '\n';
}