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

const int N = 1e5 + 5;

int n, a[N], b[N];

void Hollwo_Pelw(){
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> b[i];
    }

    set<pair<int, int>> cur, can;
    int sum = 0, res = 0;

    for (int i = 1; i <= n; i++) {
        can.insert({a[i], i});
    }


    map<int, vector<int>> mp;

    for (int i = 1; i <= n; i++) {
        mp[b[i]].push_back(i);
    }



    for (auto [bb, vc] : mp) {
        while (!can.empty() && sum + can.begin()->first <= bb * (int) (cur.size() + 1)) {
            int i = can.begin()->second;
            can.erase(can.find({a[i], i}));
            cur.insert({a[i], i});

            sum += a[i];
        }

        // cout << "SOLVE " << bb << "\n";

        // cout << "CUR: ";
        // for (auto [x, i] : cur) { cout << i << " "; }
        // cout << '\n';

        // cout << "CNA: ";
        // for (auto [x, i] : can) { cout << i << " "; }
        // cout << '\n';

        res = max<int>(res, cur.size());

        for (int i : vc) {

            // cout << "REMOVE " << i << '\n';

            if (can.find({a[i], i}) != can.end()) {
                can.erase(can.find({a[i], i}));
            } else if (cur.find({a[i], i}) != cur.end()) {
                cur.erase(cur.find({a[i], i}));
                sum -= a[i];
            } else {
                // cout << "SUSUS " << i << '\n';
            }

        }
    }

    cout << res << '\n';
}