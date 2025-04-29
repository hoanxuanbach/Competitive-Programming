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

string s[5005];
vector<int> vec[5005][26];
int n, m, k, cnt[5005][5005];
int rb = -1, ra = -1;

void solve() {
    cin >> n >> m >> k;
    for (int i = 1; i <= n; ++i) cin >> s[i];
    for (int b = 1; b <= n; ++b) {
        if (rb != -1) break;
        for (int i = 0; i < m; ++i) if (s[b][i] != '.') {
            int ch = s[b][i] - 'A';
            for (int v : vec[i][ch]) {
                if (++cnt[v][b] == k) {
                    rb = b;
                    ra = max(ra, v);
                }
            }
            vec[i][ch].emplace_back(b);
        }
    }
    if (rb == -1) cout << -1 << endl;
    else cout << ra << " " << rb << endl;
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
   cout << "Check array size pls sir" << endl;
#endif

}
