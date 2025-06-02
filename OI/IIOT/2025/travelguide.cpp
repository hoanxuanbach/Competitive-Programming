#include<bits/stdc++.h>
using namespace std;

#define endl '\n'
#define fi first
#define se second
#define setmax(x, y) x = max(x, (y))

const int NM = 4e5 + 5;

vector<int> g1[NM], g2[NM];
int ans[NM], n, q, sz[NM], timer, tin1[NM], tout1[NM], tin2[NM], tout2[NM], eu[NM];
vector<pair<int, int>> Q[NM];

struct node
{
    bool ok = 1;
    int L = -1, R = -1;
    node operator+(const node& o)
    {
        node res;
        res.ok = (ok && o.ok && (L == -1 || o.L == -1 || R < o.L));
        res.L = (L == -1 ? o.L : L);
        res.R = (o.R == -1 ? R : o.R);
        return res;
    }
}dt[4 * NM];

void upd(int i, int v, int x = 1, int l = 1, int r = n)
{
    // if (x == 1)
    // {
    //     cout << i << ' ' << v << endl;
    // }
    if (l == r)
    {
        dt[x] = {1, v, v};
        return;
    }
    int m = l + r >> 1;
    if (i <= m)
        upd(i, v, x << 1, l, m);
    else 
        upd(i, v, x << 1 | 1, m + 1, r);
    dt[x] = dt[x << 1] + dt[x << 1 | 1];
}

void del(int x = 1, int l = 1, int r = n)
{
    dt[x] = {1, -1, -1};
    if (l == r)
        return;
    int m = l + r >> 1;
    if (dt[x << 1].L != -1)
        del(x << 1, l, m);
    if (dt[x << 1 | 1].L != -1)
        del(x << 1 | 1, m + 1, r);
}

node get(int l, int r, int x = 1, int lx = 1, int rx = n)
{
    if (l > rx || lx > r)
        return {1, -1, -1};
    if (lx >= l && rx <= r)
        return dt[x];
    int m = lx + rx >> 1;
    return get(l, r, x << 1, lx, m) + get(l, r, x << 1 | 1, m + 1, rx);
}

void dfs1(int u)
{
    sz[u] = 1;
    eu[++timer] = u;
    tin1[u] = timer;
    for (int v : g1[u])
    {
        dfs1(v);
        sz[u] += sz[v];
    }
    tout1[u] = timer;
}

void dfs2(int u)
{
    tin2[u] = ++timer;
    for (int v : g2[u])
        dfs2(v);
    tout2[u] = timer;
}

void calc(int u, bool keep)
{
    pair<int, int> bc = {0, -1};
    for (int v : g1[u])
        setmax(bc, make_pair(sz[v], v));
    for (int v : g1[u])
        if (v != bc.se)
            calc(v, 0);
    if (bc.se != -1)
        calc(bc.se, 1);
    upd(tin2[u], tin1[u]);
    for (int v : g1[u])
        if (v != bc.se)
            for (int i = tin1[v]; i <= tout1[v]; i++)
                upd(tin2[eu[i]], tin1[eu[i]]);
    for (auto t : Q[u])
    {
        // for (int i = tin2[t.fi]; i <= tout2[t.fi]; i++)
        //     cout << get(i, i).L << ' ';
        // cout << endl;
        ans[t.se] = get(tin2[t.fi], tout2[t.fi]).ok;
    }
    if (!keep)
        del();
}

void solve()
{
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int t;
        cin >> t;
        while (t--)
        {
            int u;
            cin >> u;
            g1[i].push_back(u);  
        }
    }
    for (int i = 0; i < n; i++)
    {
        int t;
        cin >> t;
        while (t--)
        {
            int u;
            cin >> u;
            g2[i].push_back(u);   
        }
    }
    dfs1(0);
    timer = 0;
    dfs2(0);
    cin >> q;
    for (int i = 1; i <= q; i++)
    {
        int u, v;
        cin >> u >> v;
        Q[u].emplace_back(v, i);
    }
    calc(0, 0);
    for (int i = 1; i <= q; i++)
        cout << (ans[i] ? "YES" : "NO") << endl;
}

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int tc = 1;
    while (tc--)
        solve();
}