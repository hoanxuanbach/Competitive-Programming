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

vector<int> p = {0, 1, 3, 5, 7, 9};

inline int cnt(int x) {
    return x / 3;
}

void Hollwo_Pelw(){
    int pw = 10;
    for (int i = 1; i < 18; i++) {
        if (i % 2 == 1) {
            for (int j = 3; j < 10; j += 2) {
                p.push_back(pw * j - 1);
            }
        } else {
            for (int j = 2; j <= 10; j += 2) {
                p.push_back(pw * j - 1);
            }            
        }
        pw *= 10;
    }

    int q; cin >> q;
    for (int l, r; q --; ) {
        cin >> l >> r;
        int c = 0;
        for (int i : p) {
            if (i >= l && i <= r && i % 3 == 0) {
                c ++;
            }
        }
        cout << cnt(r) - cnt(l - 1) - c << '\n';
    }
}



/*

0 -> FALSSE
1 -> FALSSE
3 -> FALSSE
5 -> FALSSE
7 -> FALSSE
9 -> FALSSE
29 -> FALSSE
49 -> FALSSE
69 -> FALSSE
89 -> FALSSE
199 -> FALSSE
399 -> FALSSE
599 -> FALSSE
799 -> FALSSE
999 -> FALSSE
2999 -> FALSSE
4999 -> FALSSE
6999 -> FALSSE
8999 -> FALSSE
19999 -> FALSSE
39999 -> FALSSE
59999 -> FALSSE
79999 -> FALSSE
99999 -> FALSSE

Execution time : 345[ms]

*/