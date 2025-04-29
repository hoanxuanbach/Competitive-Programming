/*
#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx2,fma,bmi,bmi2,sse4.2,popcnt,lzcnt")
*/

#include <bits/stdc++.h>
#define taskname ""
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define i64 long long
#define pb push_back
#define ff first
#define ss second
#define isz(x) (int)x.size()
using namespace std;

const int mxN = 2e5 + 5;
const int mod = 1e9 + 7;
const i64 oo = 1e18;

int n;

void solve() {
    cin >> n;
    set<pair<int, int>> s;
    map<int, vector<int>> roww, dia, coll;
    map<int, int> row, col, dia1, dia2;
    for (int i = 1; i <= n; ++i) {
        int x, y;
        cin >> x >> y;
        roww[x].emplace_back(y);
        coll[y].emplace_back(x);
        dia[x + y].emplace_back(x);
        row[x]++, col[y]++, dia1[x - y]++, dia2[x + y]++;
    }

    int cnt = n, ptr = 0;

    function<bool(int, int)> check = [&](int x, int y) {
        int res = 0;
        // cout << x + y << " ";
        res += (row.find(x) != row.end() ? row[x] : 0);
        res += (col.find(y) != col.end() ? col[y] : 0); // cout << res << " ";
        res += (dia1.find(x - y) != dia1.end() ? dia1[x - y] : 0); // cout << res << " ";
        res += (dia2.find(x + y) != dia2.end() ? dia2[x + y] : 0); // cout << res << "\n";
        return res == cnt;
    };

    for (auto &[x, vec] : roww) {
        for (int y : vec) {
            --cnt;
            --row[x], --col[y], --dia1[x - y], --dia2[x + y];
        }

        if (cnt == 0) {
            cout << "YES\n";
            cout << x << " 0\n";
            return;
        }

        pair<int, int> cur = (ptr == 0 ? pair{roww.rbegin()->first, roww.rbegin()->second[0]} : pair{roww.begin()->first, roww.begin()->second[0]});
        if (check(x, cur.ss)) {
            cout << "YES" << "\n";
            cout << x << " " << cur.ss << "\n";
            return;
        }
        if (check(x, cur.ff + cur.ss - x)) {
            cout << "YES" << "\n";
            cout << x << " " << cur.ff + cur.ss - x << "\n";
            return;
        }
        if (check(x, x - (cur.ff - cur.ss))) {
            cout << "YES" << "\n";
            cout << x << " " << x - (cur.ff - cur.ss) << "\n";
            return;
        }

        for (int y : vec) {
            ++cnt;
            ++row[x];
            ++col[y];
            ++dia1[x - y];
            ++dia2[x + y];
            s.insert({x, y});
        }
        ++ptr;
    }

    ptr = 0, cnt = n;
    for (auto &[y, vec] : coll) {
        for (int x : vec) {
            --cnt;
            --row[x], --col[y], --dia1[x - y], --dia2[x + y];
        }

        if (s.empty()) {
            cout << "YES\n";
            cout << 0 << " " << y << "\n";
            return;
        }

        pair<int, int> cur = (ptr == 0 ? pair{coll.rbegin()->second[0], coll.rbegin()->first} : pair{coll.begin()->second[0], coll.begin()->first});
        if (check(cur.ff, y)) {
            cout << "YES" << "\n";
            cout << cur.ff << " " << y << "\n";
            return;
        }
        if (check(cur.ff + cur.ss - y, y)) {
            cout << "YES" << "\n";
            cout << cur.ff + cur.ss - y << " " << y << "\n";
            return;
        }
        if (check(cur.ff - cur.ss + y, y)) {
            cout << "YES" << "\n";
            cout << cur.ff - cur.ss + y << " " << y << "\n";
            return;
        }

        for (int x : vec) {
            ++cnt;
            ++row[x];
            ++col[y];
            ++dia1[x - y];
            ++dia2[x + y];
        }
        ++ptr;
    }

    cnt = n, ptr = 0;
    for (auto &[diff, vec] : dia) {
        for (int x : vec) {
            int y = diff - x;
            --cnt;
            --row[x], --col[y], --dia1[x - y], --dia2[x + y];
        }

        if (s.empty()) {
            cout << "YES\n";
            cout << diff << " 0\n";
            return;
        }

        pair<int, int> cur;
        auto it = ptr == 0 ? prev(dia.end()) : dia.begin();
        cur.ff = it->second[0], cur.ss = it->first - cur.ff;

        // cout << cur.ff << " " << cur.ss << endl;

        if (check(cur.ff, diff - cur.ff)) {
            cout << "YES" << "\n";
            cout << cur.ff << " " << diff - cur.ff << "\n";
            return;
        }
        if (check(diff - cur.ss, cur.ss)) {
            cout << "YES" << "\n";
            cout << diff - cur.ss << " " << cur.ss << "\n";
            return;
        }
        if ((cur.ff - cur.ss - diff) % 2 == 0 && check((cur.ff - cur.ss + diff) / 2, diff - (cur.ff - cur.ss + diff) / 2)) {
            cout << "YES" << "\n";
            cout << (cur.ff - cur.ss + diff) / 2 << " " << diff - (cur.ff - cur.ss + diff) / 2 << "\n";
            return;
        }

        for (int x : vec) {
            int y = diff - x;
            ++cnt;
            ++row[x];
            ++col[y];
            ++dia1[x - y];
            ++dia2[x + y];
        }
        ++ptr;
    }

    cout << "NO\n";
}

signed main() {

#ifndef CDuongg
    if(fopen(taskname".inp", "r"))
        assert(freopen(taskname".inp", "r", stdin)), assert(freopen(taskname".out", "w", stdout));
#else
    freopen("bai3.inp", "r", stdin);
    freopen("bai3.out", "w", stdout);
    auto start = chrono::high_resolution_clock::now();
#endif

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1; cin >> t;
    while(t--) solve();

#ifdef CDuongg
   auto end = chrono::high_resolution_clock::now();
   cout << "\n"; for(int i = 1; i <= 100; ++i) cout << '=';
   cout << "\nExecution time: " << chrono::duration_cast<chrono::milliseconds> (end - start).count() << "[ms]" << endl;
#endif

}