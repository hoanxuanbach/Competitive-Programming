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

bool vis[2005];
vector<pair<int, int>> v;
int n, a[2005], dp[2005], trace[2005];
vector<int> res[2];

void solve() {
    cin >> n;
    for (int i = 1; i <= n * 2; ++i) cin >> a[i];
    for (int i = 1; i <= n * 2;) {
        int ptr = i;
        while (ptr <= n * 2 && a[i] >= a[ptr]) ++ptr;
        v.emplace_back(i, ptr); i = ptr;
    }
    dp[0] = 1;
    for (int i = 0; i < isz(v); ++i) {
        int len = v[i].ss - v[i].ff;
        for (int j = n; j >= len; --j) if (!dp[j] && dp[j - len]) {
            dp[j] = 1;
            trace[j] = i;
        }
    }
    if (!dp[n]) {
        cout << -1 << endl;
        return;
    }
    int cur = n;
    while (cur) {
        int cidx = trace[cur];
        vis[cidx] = true;
        cur -= v[cidx].ss - v[cidx].ff;
    }
    for (int i = 0; i < isz(v); ++i) {
        for (int j = v[i].ff; j < v[i].ss; ++j) {
            res[vis[i]].emplace_back(a[j]);
        }
    }
    for (int val : res[0]) cout << val << " \n"[val == res[0].back()];
    for (int val : res[1]) cout << val << " \n"[val == res[1].back()];
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
