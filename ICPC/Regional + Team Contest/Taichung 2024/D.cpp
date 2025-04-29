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
    int n, m;
    cin >> n >> m;

    array<int, 2> st;
    vector<vector<char>> a(n, vector<char>(m));
    for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) {
        cin >> a[i][j];
        if (a[i][j] == 'S') {
            st = {i, j};
        }
    }

    vector<array<int, 2>> dir = {
        {0, -1},
        {0, 1},
        {-1, 0},
        {1, 0},
    };

    auto check = [&](int x, int y) -> bool {
        return 0 <= x and x < n and 0 <= y and y < m and a[x][y] != '#';
    };

    vector dis(n, vector(m, vector(4, vector(4, -1))));

    queue<array<int, 5>> q;
    q.push({st[0], st[1], -1, -1, 0});

    while (not q.empty()) {
        auto cur = q.front(); q.pop();
        int x = cur[0], y = cur[1], prv = cur[2], step = cur[3], d = cur[4];
        if (a[x][y] == 'T') {
            cout << d << endl;
            return;
        }
        for (int idx = 0; idx < 4; ++idx) {
            int nx = x + dir[idx][0];
            int ny = y + dir[idx][1];
            int nprv = idx;
            int nstep = (prv == nprv ? (step + 1) : 1);
            int nd = d + 1;
            if (check(nx, ny) and nstep <= 3 and dis[nx][ny][nprv][nstep] == -1) {
                dis[nx][ny][nprv][nstep] = nd;
                q.push({nx, ny, nprv, nstep, nd});
            }
        }
    }
    cout << -1 << endl;
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
