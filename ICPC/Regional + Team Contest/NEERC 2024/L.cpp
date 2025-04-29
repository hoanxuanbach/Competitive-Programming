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

bool rlt[505][505];
int n, m, a[505][505], ans[505 * 505], enc[505][505], indeg[505 * 505];
vector<int> G[505 * 505];

int encode(int x, int y) {
    return (x - 1) * n + y;
}

void solve() {
    cin >> n >> m;
    for (int i = 1; i < n; ++i) {
        for (int j = 1; j < m; ++j) {
            char c; cin >> c;
            a[i][j] = c - '0';
        }
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            enc[i][j] = (i - 1) * m + j;
            // cout << enc[i][j] << " \n"[j == m];
        }
    }
    // return;

    for (int i = 1; i < n; ++i)
        rlt[i][1] = 0;

#define A i - 1, j - 1
#define B i - 1, j
#define C i, j - 1
#define D i, j

    auto add_edge = [&](int x1, int y1, int x2, int y2) -> void {
        // cout << x1 << " " << y1 << " -> " << x2 << " " << y2 << endl;
        G[enc[x1][y1]].emplace_back(enc[x2][y2]);
        ++indeg[enc[x2][y2]];
    };

    for (int j = 2; j <= m; ++j) {
        int cur = 1;
        for (int i = 2; i <= n; ++i) {
            // cout << a[i - 1][j - 1] << " " << rlt[i - 1][j - 1] << " " << cur << "\n";
            if (a[i - 1][j - 1] == 1) {
                if (rlt[i - 1][j - 1] == 0) {
                    if (cur == 0) {
                        add_edge(B, A);
                        add_edge(A, D);
                        add_edge(D, C);
                        rlt[i - 1][j] = 0;
                        cur = 0;
                    }
                    else {
                        add_edge(A, B);
                        add_edge(B, C);
                        add_edge(C, D);
                        rlt[i - 1][j] = 0;
                        cur = 1;
                    }
                }
                else {
                    if (cur == 0) {
                        add_edge(B, C);
                        add_edge(C, D);
                        add_edge(D, A);
                        rlt[i - 1][j] = 0;
                        cur = 1;
                    }
                    else {
                        add_edge(C, D);
                        add_edge(D, A);
                        add_edge(A, B);
                        rlt[i - 1][j] = 1;
                        cur = 1;
                    }
                }
            }
            else if (a[i - 1][j - 1] == 2) {
                if (rlt[i - 1][j - 1] == 0) {
                    if (cur == 0) {
                        add_edge(B, A);
                        add_edge(A, C);
                        add_edge(C, D);
                        rlt[i - 1][j] = 0;
                        cur = 1;
                    }
                    else {
                        add_edge(A, C);
                        add_edge(C, D);
                        add_edge(D, B);
                        rlt[i - 1][j] = 1;
                        cur = 1;
                    }
                }
                else {
                    if (cur == 0) {
                        add_edge(B, D);
                        add_edge(D, C);
                        add_edge(C, A);
                        rlt[i - 1][j] = 0;
                        cur = 0;
                    }
                    else {
                        add_edge(C, A);
                        add_edge(A, B);
                        add_edge(B, D);
                        rlt[i - 1][j] = 0;
                        cur = 1;
                    }
                }
            }
            else {
                if (rlt[i - 1][j - 1] == 0) {
                    if (cur == 0) {
                        add_edge(B, D);
                        add_edge(D, A);
                        add_edge(A, C);
                        rlt[i - 1][j] = 0;
                        cur = 0;
                    }
                    else {
                        add_edge(A, C);
                        add_edge(C, B);
                        add_edge(B, D);
                        rlt[i - 1][j] = 0;
                        cur = 1;
                    }
                }
                else {
                    if (cur == 0) {
                        add_edge(D, B);
                        add_edge(B, C);
                        add_edge(C, A);
                        rlt[i - 1][j] = 1;
                        cur = 0;
                    }
                    else {
                        add_edge(C, A);
                        add_edge(A, D);
                        add_edge(D, B);
                        rlt[i - 1][j] = 1;
                        cur = 1;
                    }
                }
            }
            // cout << endl;
        }
    }

    int cnt = 0;
    queue<int> q;
    for (int i = 1; i <= n * m; ++i)
        if (indeg[i] == 0) q.emplace(i);

    while (not q.empty()) {
        int v = q.front(); q.pop();
        ans[v] = ++cnt;
        for (int u : G[v]) {
            if (--indeg[u] == 0) {
                q.emplace(u);
            }
        }
    }
    // cout << cnt << endl;
    assert(cnt == n * m);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            cout << ans[enc[i][j]] << " \n"[j == m];
        }
    }
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
    int t = 1; //cin >> t;
    while(t--) solve();

#ifdef CDuongg
   auto end = chrono::high_resolution_clock::now();
   cout << "\n"; for(int i = 1; i <= 100; ++i) cout << '=';
   cout << "\nExecution time: " << chrono::duration_cast<chrono::milliseconds> (end - start).count() << "[ms]" << endl;
#endif

}
