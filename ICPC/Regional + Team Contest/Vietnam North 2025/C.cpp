#pragma GCC optimize("O3,unroll-loops")
#include <bits/stdc++.h>

using namespace std;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
const int N = 5005;
const int MAX = 1e7;

struct Position {
    int x, y, z;
}pos[N];

int x, y, z, ans, sz;
bool px[N], py[N], pz[N];

bool check(int ptr) {
    int i = pos[ptr].x, j = pos[ptr].y, k = pos[ptr].z;
    return px[i] | py[j] | pz[k];
}

void back_track(int num, int ptr = 0) {
    while (ptr < sz && check(ptr)) {
        ++ptr;
    }

    if (ptr == sz) {
        ans = min(ans, num);
        return;
    }

    if (num + 1 >= ans) return;

    int i = pos[ptr].x, j = pos[ptr].y, k = pos[ptr].z;
    // cout << ptr << ' ' << i << ' ' << j << ' ' << k << '\n';
    int old_px = px[i], old_py = py[j], old_pz = pz[k];

    px[i] = true;
    back_track(num + 1, ptr + 1);
    px[i] = old_px;


    py[j] = true;
    back_track(num + 1, ptr + 1);
    py[j] = old_py;

    pz[k] = true;
    back_track(num + 1, ptr + 1);
    pz[k] = old_pz;
}

void solve() {
    cin >> x >> y >> z;

    vector<vector<vector<int>>> a(x + 1, vector<vector<int>>(y + 1, vector<int>(z + 1)));
    vector<vector<vector<int>>> idx(x + 1, vector<vector<int>>(y + 1, vector<int>(z + 1)));
    int cur = 0;
    vector<Position> candidates;
    for (int i = 1; i <= x; ++i) {
        for (int j = 1; j <= y; ++j) {
            for (int k = 1; k <= z; ++k) {
                cin >> a[i][j][k];
                if (a[i][j][k]) {
                    candidates.push_back({i, j, k});
                    idx[i][j][k] = cur;
                    pos[cur] = {i, j, k};
                    ++cur;
                }
            }
        }
    }
    sz = (int)candidates.size();
    memset(px, 0, sizeof(px));
    memset(py, 0, sizeof(py));
    memset(pz, 0, sizeof(pz));

    ans = min(x, min(y, z));
    back_track(0);
    cout << ans << '\n';
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
#ifdef LOCAL
    freopen("main.inp", "r", stdin);
    freopen("main.out", "w", stdout);
#endif
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
