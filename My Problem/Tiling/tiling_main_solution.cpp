#include<bits/stdc++.h>
using namespace std;
#define int long long
#define pii pair<int,int>
const int inf = 1e18;

struct Solver{
    int n,m;
    vector<vector<pair<int,int>>> g;
    vector<int> fu,fv;

    vector<int> u, v;
    vector<int> p, way;

    Solver(int _n,int _m): n(_n),m(_m){
        g.assign(n+1, {});
        fu.assign(n+1,inf);
        fv.assign(m+1,inf);

        u.assign(n+1,0);
        v.assign(m+1,0);

        p.assign(m+1,0);
        way.assign(m+1,-1);

    }

    void addEdge(int a, int b, int w) {
        a++;b++;
        g[a].push_back({b, w});
        fu[a]=min(fu[a],w);
        fv[b]=min(fv[b],w);
    }

    int solve() {
        for(int a=1;a<=n;a++){
            for(int i=0;i<(int)g[a].size();i++){
                int b=g[a][i].first;
                g[a][i].second=max(0LL,fu[a]+fv[b]-g[a][i].second);
            }
        }

        for (int i = 1; i <= n; i++) {

            p[0] = i;

            vector<int> minv(m + 1, inf);
            vector<bool> used(m + 1, false);

            int j0 = 0;

            do {

                used[j0] = true;

                int i0 = p[j0];

                int delta = inf;
                int j1 = -1;

                for (auto [j,w] : g[i0]) {

                    if (used[j]) continue;

                    int cur = -w-u[i0]-v[j];

                    if (cur < minv[j]) {
                        minv[j] = cur;
                        way[j] = j0;
                    }

                    if (minv[j] < delta) {
                        delta = minv[j];
                        j1 = j;
                    }
                }

                if (j1 == -1) break;

                for (int j = 0; j <= m; j++) {

                    if (used[j]) {
                        u[p[j]] += delta;
                        v[j] -= delta;
                    }
                    else if (minv[j] < inf) {
                        minv[j] -= delta;
                    }
                }

                j0 = j1;

            } while (p[j0] != 0);

            while (j0 != 0) {
                int j1 = way[j0];
                p[j0] = p[j1];
                j0 = j1;
            }
        }

        vector<int> matchL(n + 1, -1);

        int cost = 0;

        for (int j = 1; j <= m; j++) {
            if (p[j]) {
                matchL[p[j]] = j;
            }
        }

        for (int i = 1; i <= n; i++) {
            if (matchL[i] != -1) {
                for (auto [j,w] : g[i]) {
                    if (j == matchL[i]) {
                        //cout << i << ' ' << j << ' ' << w << '\n';
                        cost += w;
                        break;
                    }
                }
            }
        }

        int total=0;
        for(int i=1;i<=n;i++) total+=fu[i];
        for(int i=1;i<=m;i++) total+=fv[i];

        return total-cost;
    }
};


void solve(){
    int n,m;cin >> n >> m;
    vector<vector<int>> a(n,vector<int>(m));
    for(int i=0;i<n;i++) for(int j=0;j<m;j++) cin >> a[i][j];

    int sw=0;
    if(n>m){
        swap(n,m);sw=1;
        vector<vector<int>> fa(n,vector<int>(m));
        for(int i=0;i<n;i++) for(int j=0;j<m;j++) fa[i][j]=a[j][i];
        swap(a,fa);
    }


    if(n==1){
        int val=0;
        for(int j=0;j<=m;j++){
            int k=0;
            if(j) k-=a[0][j-1];
            if(j<m) k+=a[0][j];
            if(k>0) val+=k;
        }
        cout << val << '\n';
        return;
    }


    int S=(n-1)*m,T=n*(m-1);
    Solver X(S,T);
    vector<vector<int>> f(n-1,vector<int>(m)),g(n,vector<int>(m-1));

    for(int i=0;i<n;i++) for(int j=0;j<m;j++){
        if(i && j) X.addEdge((i-1)*m+j,i*(m-1)+j-1,a[i][j]);
        if(i && j+1<m) X.addEdge((i-1)*m+j,i*(m-1)+j,a[i][j]);
        if(i+1<n && j) X.addEdge(i*m+j,i*(m-1)+j-1,a[i][j]);
        if(i+1<n && j+1<m) X.addEdge(i*m+j,i*(m-1)+j,a[i][j]);
    }

    int val=0;
    for(int i=0;i<n;i++) for(int j=0;j<m;j++) val+=a[i][j];
    val-=X.solve();

    cout << val << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test;cin >> test;
    while(test--) solve();
}