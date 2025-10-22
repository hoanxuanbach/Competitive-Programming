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

const int N = 1e6 + 5;

int n, a[N];

void Hollwo_Pelw(){
    cin >> n;
    
    int cnt = 0;

    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    for (int i = 0; i < n - 1; i += 2) {
        int x = a[i], y = a[i + 1];
        int g = __gcd(x, y);
        if (g == x || g == y || g == 1) {
            continue;
        }
        cnt ++;
    }

    if ((n + cnt) % 2 == 1) cnt ++;

    cout << (n + cnt) / 2 + cnt  << '\n';
}