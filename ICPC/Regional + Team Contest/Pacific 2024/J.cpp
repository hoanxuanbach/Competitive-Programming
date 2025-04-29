/*
#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx2,fma,bmi,bmi2,sse4.2,popcnt,lzcnt")
*/

#include <bits/stdc++.h>
#define taskname ""
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define i64 long long
#define int long long
#define pb push_back
#define ff first
#define ss second
#define isz(x) (int)x.size()
using namespace std;

const int mxN = 1e5 + 5;
const int mod = 1e9 + 7;
const i64 oo = 1e18;

vector<pair<int, int>> G[mxN];
int n, m, dis[mxN], disn[mxN], trace[mxN];

void dijkstra() {
    fill(dis + 1, dis + n + 1, LLONG_MAX);
    priority_queue<pair<int, int>> pq;
    dis[1] = 0; pq.emplace(0, 1);
    while (not pq.empty()) {
        auto [w, v] = pq.top(); pq.pop(); w = -w;
        if (w != dis[v]) continue;
        for (auto [u, w1] : G[v]) {
            if (w + w1 < dis[u]) {
                dis[u] = w + w1;
                trace[u] = v;
                pq.emplace(-dis[u], u);
            }
        }
    }
}

void dijkstra2() {
    fill(disn + 1, disn + n + 1, LLONG_MAX);
    priority_queue<pair<int, int>> pq;
    disn[n] = 0; pq.emplace(0, n);
    while (not pq.empty()) {
        auto [w, v] = pq.top(); pq.pop(); w = -w;
        if (w != disn[v]) continue;
        for (auto [u, w1] : G[v]) {
            if (w + w1 < disn[u]) {
                disn[u] = w + w1;
                pq.emplace(-disn[u], u);
            }
        }
    }
}

void solve() {
    cin >> n >> m;
    for (int i = 1; i <= m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        G[u].emplace_back(v, w);
        G[v].emplace_back(u, w);
    }
    
    dijkstra();
    dijkstra2();

    if (dis[n] == LLONG_MAX) {
        cout << -1 << endl;
        return;
    }

    int cur = n, nxt = 0, res2 = LLONG_MAX;
    while (cur) {
        int pre = trace[cur];
        for (auto [v, w] : G[cur]) if (v != pre and v != nxt) {
            res2 = min(res2, dis[cur] + w + disn[v]);
        }
        nxt = cur, cur = pre;
    }
    if (res2 == LLONG_MAX) {
        cout << -1 << endl;
        return;
    }
    cout << dis[n] + res2 << endl;
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
