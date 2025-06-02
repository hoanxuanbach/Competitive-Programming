#include <bits/stdc++.h>
using namespace std;

#define int long long
#define isz(a) (int)(a).size()

const int NM = 1e5, inf = 1e18;

struct flow_edge{
    int v, c;
    flow_edge(int _v, int _c){
        v = _v, c = _c;
    }
};

struct dinic{
    int n;
    vector <int> g[15];
    vector <flow_edge> E;
    queue <int> q;
    int level[15], ptr[15];

    void reset(int k){
        n = k;
        for (int i = 0; i < k; i++)
            g[i].clear();
        E.clear();
    }
    void add_edge(int u, int v, int c){
        E.push_back(flow_edge(v, c));
        g[u].push_back(isz(E)-1);
        E.push_back(flow_edge(u, 0));
        g[v].push_back(isz(E)-1);
    }
    bool bfs(int s, int t){
        while (!q.empty()) q.pop();
        q.push(s);
        memset(level, -1, sizeof(level));
        level[s] = 0;
        while (!q.empty()){
            int u = q.front(); q.pop();
            for (int i = 0; i < isz(g[u]); i++){
                int v = E[g[u][i]].v, c = E[g[u][i]].c;
                if (c == 0 || level[v] != -1) continue;
                level[v] = level[u]+1;
                q.push(v);
            }
        }
        return level[t] != -1;
    }
    int dfs(int t, int u, int pushed){
        if (u == t || pushed == 0) return pushed;
        for (; ptr[u] < isz(g[u]); ptr[u]++){
            int v = E[g[u][ptr[u]]].v, c = E[g[u][ptr[u]]].c;
            if (c == 0 || level[v] != level[u]+1) continue;
            int tmp = dfs(t, v, min(pushed, c));
            if (tmp == 0) continue;
            E[g[u][ptr[u]]].c -= tmp;
            E[g[u][ptr[u]]^1].c += tmp;
            return tmp;
        }
        return 0;
    }
    int get(int s, int t){
        int res = 0;
        while (bfs(s, t)){
            memset(ptr, 0, sizeof(ptr));
            int tmp;
            while ((tmp = dfs(t, s, +inf)) > 0){
                res += tmp;
            }
        }
        return res;
    }
} D;

int N, K, M = 0, A[NM+5], sz = 0, B[NM+5];
vector <int> arr[10];
int msk[10];
int ans[NM+5][4];

void trace(int x, int y, int c){
    int cur = c;
    for (int t : arr[x]){
        int tmp = min(cur, A[t]);
        ans[t][y] += tmp;
        A[t] -= tmp;
        cur -= tmp;
    }
}

void check(){
    D.reset(sz+6);

    int s = sz+4, t = sz+5;
    for (int i = 0; i < sz; i++) D.add_edge(s, i, B[i]);
    D.add_edge(sz, t, K);
    D.add_edge(sz+1, t, K);
    D.add_edge(sz+2, t, M-K);
    D.add_edge(sz+3, t, M-K);

    for (int i = 0; i < sz; i++){
        D.add_edge(i, sz+((msk[i]>>1)&1), +inf);
        D.add_edge(i, sz+2+(msk[i]&1), +inf);
    }
    int opt = D.get(s, t);
    if (opt != 2*M) return;
    for (int u = sz; u < sz+4; u++)
        for (int i = 0; i < isz(D.g[u]); i++){
            int v = D.E[D.g[u][i]].v, c = D.E[D.g[u][i]].c;
            if (v < sz){
                trace(v, u-sz, c);
            }
        }
    for (int i = 0; i < N; i++){
        for (int j = 0; j < 4; j++)
            cout << ans[i][j] << ' ';
        cout << '\n';
    }
    exit(0);
}

void back(int i){
    for (int j = 0; j < 4; j++){
        msk[i] = j;
        if (i == sz-1){
            check();
        }
        else{
            back(i+1);
        }
    }
}

signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> K;
    for (int i = 0; i < N; i++){
        cin >> A[i];
        M += A[i];
    }
    M /= 2;

    for (int i = 0; i < N; i++)
        if (B[sz]+A[i] <= M){
            arr[sz].push_back(i);
            B[sz] += A[i];
        }
        else{
            sz++;
            arr[sz].push_back(i);
            B[sz] += A[i];
        }
    sz++;
    back(0);
    return 0;
}