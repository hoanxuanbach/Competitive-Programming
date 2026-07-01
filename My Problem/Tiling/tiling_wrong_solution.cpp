#include<bits/stdc++.h>
using namespace std;
#define int long long
#define pii pair<int,int>
const int inf = 1e18;

struct Solver{
    int n,m;
    vector<vector<pair<int,int>>> g; // left i -> (right j, cost)
    vector<int> fu,fv;

    vector<int> u, v;
    vector<int> p, way;

    vector<int> A, B;

    Solver(int _n,int _m): n(_n),m(_m){
        g.assign(n+1, {});
        fu.assign(n+1,inf);
        fv.assign(m+1,inf);
    }

    void addEdge(int a, int b, int w) {
        a++;b++;
        //cout << "addEdge " << a << ' ' << b << ' ' << w << '\n';
        g[a].push_back({b, w});
        //fu[a]=min(fu[a],w);
        //fv[b]=min(fv[b],w);
    }

    int solve() {
        
        /*
        for(int a=1;a<=n;a++){
            for(int i=0;i<(int)g[a].size();i++){
                int b=g[a][i].first;
                g[a][i].second=max(0LL,fu[a]+fv[b]-g[a][i].second);
                //cout << "newEdge " << a << ' ' << b << ' ' << g[a][i].second << '\n';
            }
        }
        */

        u.assign(n+1, 0);
        v.assign(m+1, 0);
        p.assign(m+1, 0);
        way.assign(m+1, 0);

        for (int i = 1; i <= n; i++) {
            p[0] = i;

            vector<int> minv(m+1, inf);
            vector<bool> used(m+1, false);

            int j0 = 0;
            bool flag=true;
            do {
                used[j0] = true;
                int i0 = p[j0];
                int delta = inf;
                int j1 = 0;

                // only sparse edges from i0
                for (auto [j, cost] : g[i0]) {
                    if (used[j]) continue;
                    int cur = cost - u[i0] - v[j];
                    if (cur < minv[j]) {
                        minv[j] = cur;
                        way[j] = j0;
                    }
                    if (minv[j] < delta) {
                        delta = minv[j];
                        j1 = j;
                    }
                }

                // if disconnected => no perfect matching
                if (delta == inf){
                    flag = false;
                    break;
                }

                for (int j = 0; j <= m; j++) {
                    if (used[j]) {
                        u[p[j]] += delta;
                        v[j] -= delta;
                    } else if (minv[j] < inf) {
                        minv[j] -= delta;
                    }
                }

                j0 = j1;

            } while (p[j0] != 0);
            if(flag){
                do {
                    int j1 = way[j0];
                    p[j0] = p[j1];
                    j0 = j1;
                } while (j0);
            }
        }

        // matching: p[j] matched to j

        A.assign(n,0);
        B.assign(m,0);

        int cost = 0;
        for(int i=1;i<=n;i++) cost+=u[i];
        for(int i=1;i<=m;i++) cost+=v[i];
        //for(int i=0;i<n;i++) A[i]=fu[i+1]+u[i+1],cost+=A[i];
        //for(int i=0;i<m;i++) B[i]=fv[i+1]+v[i+1],cost+=B[i];

        // primal optimum = dual optimum
        return cost;
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

    vector<array<int,5>> res;

    if(n==1){
        int val=0;
        vector<pii> S;
        for(int j=0;j<=m;j++){
            int k=0;
            if(j) k-=a[0][j-1];
            if(j<m) k+=a[0][j];
            if(k>0) S.push_back({k,j}),val+=k;
            else{
                k=-k;
                while(!S.empty() && S.back().first<=k){
                    res.push_back({0,0,S.back().second,j-1,S.back().first});
                    k-=S.back().first;S.pop_back();
                }
                if(!S.empty() && k){
                    res.push_back({0,0,S.back().second,j-1,k});
                    S[(int)S.size()-1].first-=k;
                }
            }
        }
        cout << val << '\n';
        //for(auto [t,x,l,r,d]:res) cout << t << ' ' << x+1 << ' ' << l+1 << ' ' << r+1 << ' ' << d << '\n';
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

    /*

    for(int i=0;i<S;i++) f[i/m][i%m]=X.A[i];
    for(int i=0;i<T;i++) g[i/(m-1)][i%(m-1)]=X.B[i];
    vector<vector<int>> F(n,vector<int>(m)),G(n,vector<int>(m,0));
    for(int j=0;j<m;j++) F[0][j]+=f[0][j],F[n-1][j]+=f[n-2][j];
    for(int i=1;i<n-1;i++){
        for(int j=0;j<m;j++) F[i][j]+=max(f[i-1][j],f[i][j]);
    }

    for(int i=0;i<n;i++) G[i][0]+=g[i][0],G[i][m-1]+=g[i][m-2];
    for(int i=0;i<n;i++){
        for(int j=1;j<m-1;j++) G[i][j]+=max(g[i][j],g[i][j-1]);
    }
    
    for(int j=0;j<m;j++){
        vector<pii> S;
        for(int i=0;i<=n;i++){
            int k=0;
            if(i) k-=F[i-1][j];
            if(i<n) k+=F[i][j];
            if(k==0) continue;
            if(k>0) S.push_back({k,i});
            else{
                k=-k;
                while(!S.empty() && S.back().first<=k){
                    res.push_back({1,j,S.back().second,i-1,S.back().first});
                    k-=S.back().first;S.pop_back();
                }
                if(!S.empty() && k){
                    res.push_back({1,j,S.back().second,i-1,k});
                    S[(int)S.size()-1].first-=k;
                }
            }
        }
    }
    for(int i=0;i<n;i++){
        vector<pii> S;
        for(int j=0;j<=m;j++){
            int k=0;
            if(j) k-=G[i][j-1];
            if(j<m) k+=G[i][j];
            if(k>0) S.push_back({k,j});
            else{
                k=-k;
                while(!S.empty() && S.back().first<=k){
                    res.push_back({0,i,S.back().second,j-1,S.back().first});
                    k-=S.back().first;S.pop_back();
                }
                if(!S.empty() && k){
                    res.push_back({0,i,S.back().second,j-1,k});
                    S[(int)S.size()-1].first-=k;
                }
            }
        }
    }

    for(int i=0;i<n;i++) for(int j=0;j<m;j++){
        int k=F[i][j]+G[i][j];
        //assert(k<=a[i][j]);
        if(k<a[i][j]) res.push_back({0,i,j,j,a[i][j]-k});
    }

    cout << (int)res.size() << '\n';
    for(auto [t,x,l,r,d]:res) cout << (t^sw) << ' ' << x+1 << ' ' << l+1 << ' ' << r+1 << ' ' << d << '\n';
    */
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test;cin >> test;
    while(test--) solve();
}