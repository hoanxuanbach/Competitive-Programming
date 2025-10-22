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

void Hollwo_Pelw(){
    int n; cin >> n;
    vector<int> a(n);

    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    int sg = 1, zr = 0;
    sort(a.begin(), a.end());
    for (int i = 0; i < n; i++) {
        if (a[i] == 0) {
            zr ++;
        } else if (a[i] < 0) {
            sg *= -1;
        }
    }

    if (zr > 1) { // always zero
        cout << a.back() << ' ' << a[0] << '\n';
    } else if (zr == 1) {
        // rem zr -> make sg 

        if (sg == -1) {
            // not rem zr
            cout << (a.back() == 0 ? a[a.size() - 2] : a.back()) << ' ' << a[0] << '\n';
            // a[0] alway < 0
        } else { // to rem zr
            cout << 0 << ' ' << 0 << '\n';
        }
    } else {
        vector<int> pos, neg;
        for (int i : a) {
            if (i > 0) pos.push_back(i);
            if (i < 0) neg.push_back(i);
        }
        if (sg == -1) {
            // rm < 0, largest
            cout << neg.back() << ' ' << neg.back() << '\n';
        } else if (pos.size() > 0) {
            // rm > 0
            cout << pos[0] << ' ' << pos[0] << '\n';
        } else {
            // rm < 0
            cout << neg[0] << ' ' << neg[0] << '\n';
        }
    }
}