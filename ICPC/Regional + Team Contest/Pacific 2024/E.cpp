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

vector<int> row, col;
int n, a[105][105];

bool check_row(int idx) {
    vector<int> cnt(n + 1);
    for (int i = 1; i <= n; ++i) {
        if (cnt[a[idx][i]]) return false;
        ++cnt[a[idx][i]];
    }
    return true;
}

bool check_col(int idx) {
    vector<int> cnt(n + 1);
    for (int i = 1; i <= n; ++i) {
        if (cnt[a[i][idx]]) return false;
        ++cnt[a[i][idx]];
    }
    return true;
}

vector<tuple<int, int, int>> op;

void change(int x, int y, int val) {
    assert(a[x][y] != val);
    op.emplace_back(x, y, val);
    a[x][y] = val;
}

void fix_row(int idx) {
    for (int j = 1; j <= n; ++j) {
        vector<int> cnt(n + 1);
        for (int i = 1; i <= n; ++i) ++cnt[a[i][j]];
        if (cnt[a[idx][j]] > 2 or cnt[a[idx][j]] == 1) {
            change(idx, j, a[idx][j] == 1 ? n : a[idx][j] - 1);
            return;
        }
        if (cnt[a[idx][j]] == 2) {
            int tmp = -1;
            for (int i = 1; i <= n; ++i) if (i != a[idx][j] and cnt[i]) {
                tmp = i;
                break;
            }
            change(idx, j, tmp);
            return;
        }
    }
    assert(false);
}

void fix_col(int idx) {
    for (int j = 1; j <= n; ++j) {
        vector<int> cnt(n + 1);
        for (int i = 1; i <= n; ++i) ++cnt[a[j][i]];
        if (cnt[a[j][idx]] > 2 or cnt[a[j][idx]] == 1) {
            change(j, idx, a[j][idx] == 1 ? n : a[j][idx] - 1);
            return;
        }
        if (cnt[a[j][idx]] == 2) {
            int tmp = -1;
            for (int i = 1; i <= n; ++i) if (i != a[j][idx] and cnt[i]) {
                tmp = i;
                break;
            }
            change(j, idx, tmp);
            return;
        }
    }
    assert(false);
}

void solve() {
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            cin >> a[i][j];
        }
    }
    row.clear(); col.clear(); op.clear();
    for (int i = 1; i <= n; ++i) if (check_row(i)) row.emplace_back(i);
    for (int i = 1; i <= n; ++i) if (check_col(i)) col.emplace_back(i);
    while (!row.empty() and !col.empty()) {
        int r = row.back(); row.pop_back();
        int c = col.back(); col.pop_back();
        change(r, c, (a[r][c] == 1 ? n : a[r][c] - 1));
    }
    // for (int i = 1; i <= n; ++i) {
    //     for (int j = 1; j <= n; ++j) {
    //         cout << a[i][j] << " \n"[j == n];
    //     }
    // }
    // cout << isz(row) << " " << isz(col) << endl;
    for (int idx : row) fix_row(idx);
    for (int idx : col) fix_col(idx);
    // for (int i = 1; i <= n; ++i) {
    //     for (int j = 1; j <= n; ++j) {
    //         cout << a[i][j] << " \n"[j == n];
    //     }
    // }
    cout << isz(op) << "\n";
    for (auto [r, c, val] : op) cout << r << " " << c << " " << val << "\n";
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
   cout << "Check array size pls sir" << endl;
#endif

}
